#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <string.h>
#include <stdio.h> 
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdlib>
#include <cstdio>
#include <math.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h> 
#include <time.h>  
#include <ctime>
#include <algorithm>

#define CLCD "/dev/clcd"
#define DOT "/dev/dot"
#define TACT "/dev/tactsw"
#define DIP "/dev/dipsw"

// 1/600초를 정의
#define TIME_QUANTUM 1667
using namespace std;

void printVector(const std::vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        printf("%d ", vec[i]);
    }
    printf("\n");
}

int getDIP() {
    unsigned char b;
    int dip = -1;
    dip = open(DIP, O_RDONLY);
    if (dip < 0) {
        printf("dip device error\n");
        return -1;
    }
    read(dip, &b, sizeof(b));
    close(dip);
    switch (b) {
    case 1: //외부 1층 버튼
        return 1;
    case 2:
        return 2;
    case 4:
        return 3;
    case 8:
        return 4;
    case 16:
        return 5;
    case 32:
        return 6;
    case 64:
        return 7;
    case 128: //외부 8층 버튼
        return 8;
    default:
        return -1;
    }
}

int getTACT() {
    unsigned char b;
    int tactswFd = -1;
    tactswFd = open(TACT, O_RDONLY);
    if (tactswFd < 0) {
        printf("tact device error\n");
        return -1;
    }
    read(tactswFd, &b, sizeof(b));
    close(tactswFd);
    switch (b) {
    case 1: // 내부 1번 버튼
        return 1;
    case 2: // 내부 2번 버튼
        return 2;
    case 3: // 내부 닫기 버튼
        printf("close button pushed!\n");
        return 200;
    case 4: // 내부 3번 버튼
        return 3;
    case 5: // 내부 4번 버튼
        return 4;
    case 7: // 내부 5번 버튼
        return 5;
    case 8: // 내부 6번 버튼
        return 6;
    case 10: // 내부 7번 버튼
        return 7;
    case 11: // 내부 8번 버튼
        return 8;
    case 12: // 내부 종료 버튼
        return 400;
    default:
        return -1;
    }
}

// CLCD에 출력
void printCLCD(string S) {
    char* cstr = new char[S.length() + 1];
    strcpy(cstr, S.c_str());
    int clcd_fd = open(CLCD, O_WRONLY);
    write(clcd_fd, cstr, 32);
    close(clcd_fd);
    delete[] cstr;
    printf("CLCD Output: %s\n", S.c_str());
}

// CLCD에 변수를 넣어 출력할 때 도우미
string CLCDHelper(int I, int space) {
    char s[10];
    sprintf(s, "%d", I);
    string STR(s);

    for (int i = STR.length(); i < space; i++) {
        STR = '0' + STR;
    }
    return STR;
}

void EV_moving_CLCD(int current_floor) {
    string s1 = "  EV is moving  ";
    string s2 = "Current : " + CLCDHelper(current_floor, 4) + "  ";

    printCLCD(s1 + s2);
}

void EV_Idle_CLCD(int current_floor) {
    string s1 = "  EV is stopped ";
    string s2 = "Current : " + CLCDHelper(current_floor, 4) + "  ";

    printCLCD(s1 + s2);
}

class EV {
public:
    int current_floor;
    vector<int> upArr;
    vector<int> downArr;
    bool isDirectionUp;
    bool isMoving;

    EV() {
        current_floor = 1;
        isDirectionUp = true;
        isMoving = false;
        printf("Elevator initialized at floor %d\n", current_floor);
        EV_Idle_CLCD(current_floor);
    }

    void addTarget(int floor) {
        if (floor > current_floor) { 
            if (find(upArr.begin(), upArr.end(), floor) == upArr.end()) {
                upArr.push_back(floor);
                sort(upArr.begin(), upArr.end());
                printf("Target floor added(upArr): %d\n", floor);
                printVector(upArr);
            }
        }
        else if(floor < current_floor) {
            if (find(downArr.begin(), downArr.end(), floor) == downArr.end()) {
                downArr.push_back(floor);
                sort(downArr.begin(), downArr.end(), std::greater<int>()); // error warning !!!!! : cpp grammar 
                printf("Target floor added(downArr): %d\n", floor);
                printVector(downArr);
            }
        }

        
    }

    void move() {
        if (upArr.size() + downArr.size() > 0) {
            printf("Starting to move.\n");
            printf("upArr : ");
            printVector(upArr);
            printf("downArr : ");
            printVector(downArr);
            printf("current floor : %d\n",current_floor);
            if (isMoving) {
                if (isDirectionUp) {
                    // 위로 상승
                    if (current_floor < upArr.front()) {
                        current_floor++;
                        EV_moving_CLCD(current_floor);
                        usleep(TIME_QUANTUM);
                        if (current_floor == upArr.front()) {
                            upArr.erase(upArr.begin());
                            isMoving = false;
                            if (upArr.empty()) {
                                isDirectionUp = false;
                                printf("direction Changed(1) (up -> down)\n");
                            }
                            EV_Idle_CLCD(current_floor);
                        }
                    }
                    // 지금 층 == 목적지
                    else if (current_floor == upArr.front()) {
                        upArr.erase(upArr.begin());
                        isMoving = false;
                        if (upArr.empty()) {
                            isDirectionUp = false;
                            printf("direction Changed(2) (up -> down)\n");
                        }
                        EV_Idle_CLCD(current_floor);
                        printf("Arrived at floor: %d\n", current_floor);
                    }
                    // 아래로 하강(더 이상 위로 못감)
                    else {
                        isDirectionUp = false;
                        printf("direction Changed(3) (up -> down)\n");
                        current_floor--;
                        EV_moving_CLCD(current_floor);
                        usleep(TIME_QUANTUM);
                        if (current_floor == downArr.front()) {
                            downArr.erase(downArr.begin());
                            isMoving = false;
                            if (downArr.empty()) {
                                isDirectionUp = true;
                                printf("direction Changed(4) (down -> up)\n");
                            }
                            EV_Idle_CLCD(current_floor);
                            printf("Arrived at floor: %d\n", current_floor);
                        }
                    }
                }
                else {
                    // 아래로 하강
                    if (current_floor > downArr.front()) {
                        current_floor--;
                        EV_moving_CLCD(current_floor);
                        usleep(TIME_QUANTUM);
                        if (current_floor == downArr.front()) {
                            downArr.erase(downArr.begin());
                            isMoving = false;
                            if (downArr.empty()) {
                                isDirectionUp = true;
                                printf("direction Changed(5) (down -> up)\n");
                            }
                            EV_Idle_CLCD(current_floor);
                        }
                    }
                    // 지금 층 == 목적지
                    else if (current_floor == downArr.front()) {
                        downArr.erase(downArr.begin());
                        isMoving = false;
                        if (downArr.empty()) {
                            isDirectionUp = true;
                            printf("direction Changed(6) (down -> up)\n");
                        }
                        EV_Idle_CLCD(current_floor);
                        printf("Arrived at floor: %d\n", current_floor);
                    }
                    // 위로 상승(더 이상 아래로 못감)
                    else {
                        isDirectionUp = true;
                        printf("direction Changed(7) (down -> up)\n");
                        current_floor++;
                        EV_moving_CLCD(current_floor);
                        usleep(TIME_QUANTUM);
                        if (current_floor == upArr.front()) {
                            upArr.erase(upArr.begin());
                            isMoving = false;
                            if (upArr.empty()) {
                                isDirectionUp = true;
                                printf("direction Changed(8) (up -> down)\n");
                            }
                            EV_Idle_CLCD(current_floor);
                            printf("Arrived at floor: %d\n", current_floor);
                        }
                    }
                }
            }
        }
        else {
            printf("no target!\n");
            printf("upArr : ");
            printVector(upArr);
            printf("downArr : ");
            printVector(downArr);
            printf("current floor : %d\n", current_floor);
            printf("isMoving : %d\n", isMoving);
            printf("isDirectionUp : %d\n", isDirectionUp);
        }
        
    }
};
void init() {
    
}

int main() {
    EV elevator;
    while (true) {
        int dip_input = getDIP();
        int tact_input = getTACT();

        if (dip_input != -1) {
            elevator.addTarget(dip_input);
        }

        if (tact_input == 400) {
            printf("Program exit command received.\n");
            break;
        }
        else if (tact_input != -1) {
            if (tact_input == 200) {
                // 문 닫기 버튼
                elevator.isMoving = true;
            }
            else {
                elevator.addTarget(tact_input);
            }
        }
        if(elevator.isMoving){
            elevator.move();
        }
        

    }
    return 3;
}
