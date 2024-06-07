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

// 1/600�ʸ� ����
#define TIME_QUANTUM 1667
using namespace std;

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
    printf("DIP input received: %d\n", b);
    switch (b) {
    case 1: //�ܺ� 1�� ��ư
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
    case 128: //�ܺ� 8�� ��ư
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
    printf("TACT input received: %d\n", b);
    switch (b) {
    case 1: // ���� 1�� ��ư
        return 1;
    case 2: // ���� 2�� ��ư
        return 2;
    case 3: // ���� �ݱ� ��ư
        return 0;
    case 4: // ���� 3�� ��ư
        return 3;
    case 5: // ���� 4�� ��ư
        return 4;
    case 7: // ���� 5�� ��ư
        return 5;
    case 8: // ���� 6�� ��ư
        return 6;
    case 10: // ���� 7�� ��ư
        return 7;
    case 11: // ���� 8�� ��ư
        return 8;
    case 12: // ���� ���� ��ư
        return 400;
    default:
        return -1;
    }
}

// CLCD�� ���
void printCLCD(string S) {
    char* cstr = new char[S.length() + 1];
    strcpy(cstr, S.c_str());
    int clcd_fd = open(CLCD, O_WRONLY);
    write(clcd_fd, cstr, 32);
    close(clcd_fd);
    delete[] cstr;
    printf("CLCD Output: %s\n", S.c_str());
}

// CLCD�� ������ �־� ����� �� �����
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
    vector<int> target_floors;

    EV() : current_floor(1) {
        printf("Elevator initialized at floor %d\n", current_floor);
    }

    void addTarget(int floor) {
        if (find(target_floors.begin(), target_floors.end(), floor) == target_floors.end()) {
            target_floors.push_back(floor);
            sort(target_floors.begin(), target_floors.end());
            printf("Target floor added: %d\n", floor);
        }
    }

    void move() {
        while (!target_floors.empty()) {
            printf("Starting to move. Current floor: %d, Target floor: %d\n", current_floor, target_floors.front());
            if (current_floor < target_floors.front()) {
                while (current_floor < target_floors.front()) {
                    current_floor++;
                    EV_moving_CLCD(current_floor);
                    usleep(TIME_QUANTUM);
                }
            }
            else if (current_floor > target_floors.front()) {
                while (current_floor > target_floors.front()) {
                    current_floor--;
                    EV_moving_CLCD(current_floor);
                    usleep(TIME_QUANTUM);
                }
            }
            printf("Arrived at floor: %d\n", current_floor);
            target_floors.erase(target_floors.begin());
        }
        EV_Idle_CLCD(current_floor);
    }
};

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
            if (tact_input == 0) {
                // �� �ݱ� ��ư
                elevator.move();
            }
            else {
                elevator.addTarget(tact_input);
            }
        }

        elevator.move();
    }
    return 0;
}
