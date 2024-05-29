#include <iostream>
#include <set>
#include <vector>
#include <thread>
#include <chrono>

enum ElevatorState {
    // 엘리베이터 상태(멈춤, 움직임-위/아래, 문-열림/닫힘)
    STOPPED,
    MOVING_UP,
    MOVING_DOWN,
    DOOR_OPEN,
    DOOR_CLOSED
};

class Elevator {
public:
    Elevator(int totalFloors) : currentFloor(1), state(STOPPED), totalFloors(totalFloors) {}

    // 엘리베이터 외부 호출
    void callElevator(int floor) {
        
        // 1~8층 사이의 층에서 호출했을 때
        if (floor >= 1 && floor <= totalFloors) {

            // 엘리베이터를 호출한 층과 엘리베이터의 현재 층이 일치할 때
            if (floor == currentFloor) {

                // 문열림
                openDoor();

                // 움직일 층을 고르라는 문구가 뜸
                std::cout << "Please select the floor to move: ";

                // 입력할 층을 입력받음
                int selectedFloor;
                std::cin >> selectedFloor;

                // 선택한 층이 1~8층 사이에 있고, 엘리베이터의 현재 층과 다를 때
                if (selectedFloor >= 1 && selectedFloor <= totalFloors && selectedFloor != currentFloor) {

                    // 내부 층 입력 함수로 입력 층을 넘겨줌
                    selectFloor(selectedFloor);
                }

            // 엘리베이터를 호출한 층과 엘리베이터의 현재 층이 일치하지 않을 때
            } else {

                // 엘리베이터가 이동할 층에 추가함
                targetFloors.insert(floor);

                // 엘리베이터의 상태를 업데이트함
                updateState();
            }
        }
    }


    // 엘리베이터 내부 층 선택
    void selectFloor(int floor) {

        // 선택된 층이 1~8층 사이인지 확인

        if (floor >= 1 && floor <= totalFloors) {

            // 선택된 층이 엘리베이터의 현재 층과 일치하는 경우
            if (floor == currentFloor) {

                // 이미 선택된 층을 다시 누르면 취소
                if (targetFloors.find(floor) != targetFloors.end()) {
                    targetFloors.erase(floor);

                    // 취소한 목적지 층이 최종 목적지인지 확인
                    if (targetFloors.empty()) {

                        // 다른 목적지가 없으면 문을 엽니다.
                        openDoor(); 
                    }
                }
            } else {
                // 선택된 층을 이동 목적지로 추가하고 엘리베이터 상태를 업데이트합니다.
                targetFloors.insert(floor);
                updateState();
            }
        }
    }



    // 엘리베이터 이동
    void move() {

        // 현재 상태가 "멈춤"일 때
        if (state == STOPPED) return;


        // 현재 상태가 "움직임-위"일 때
        if (state == MOVING_UP) {

            // 엘리베이터의 현재 층수를 하나 올림
            currentFloor++;

        // 현재 상태가 "움직임-아래"일 때
        } else if (state == MOVING_DOWN) {

            // 엘리베이터의 현재 층수를 하나 내림
            currentFloor--;
        }

        // 움직임 이후 도착했다는 문구가 뜸
        std::cout << "Elevator is at floor " << currentFloor << std::endl;

        // 현재 층이 목적지 층이면 멈춤
        if (targetFloors.find(currentFloor) != targetFloors.end()) {
            targetFloors.erase(currentFloor);
            openDoor();
        }

        updateState();
    }

    // 엘리베이터의 상태 업데이트
    void updateState() {

        // 목적지 층이 없는 경우
        if (targetFloors.empty()) {

            // "멈춤" 상태로 업데이트
            state = STOPPED;
            displayStatus("Stopped");

        // 목적지 층이 있는 경우
        } else {

            // 다음 목적지 층을 계산함
            int nextTarget = *targetFloors.begin();

            // 다음 목적지 층이 엘리베이터의 현재 층보다 클 때
            if (nextTarget > currentFloor) {

                // "움직임-위" 상태로 업데이트
                state = MOVING_UP;
                displayStatus("Moving Up");

            // 다음 목적지 층이 엘리베이터의 현재 층보다 작을 때
            } else if (nextTarget < currentFloor) {

                // "움직임-아래" 상태로 업데이트
                state = MOVING_DOWN;
                displayStatus("Moving Down");
            }
        }
    }

    // 엘리베이터 동작을 계속 수행
    void run() {
        while (true) {
            move();
            if (state == STOPPED) break;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

private:
    int currentFloor; // 현재 층
    ElevatorState state; // 엘리베이터의 현재 상태
    int totalFloors; // 엘리베이터의 총 층수
    std::set<int> targetFloors; // 목적지 층들의 집합

    void openDoor() {
        state = DOOR_OPEN;
        displayStatus("Door Open");
        std::this_thread::sleep_for(std::chrono::seconds(2)); // 문 열림 상태 유지
        closeDoor();
    }

    void closeDoor() {
        state = DOOR_CLOSED;
        displayStatus("Door Closed");
        std::this_thread::sleep_for(std::chrono::seconds(2)); // 문 닫힘 상태 유지
    }

    void displayStatus(const char* status) {
        std::cout << "Status: " << status << std::endl;
    }
};

int main() {
    // 총 8층의 엘리베이터 생성
    Elevator elevator(8);

    // 외부에서 엘리베이터 호출
    elevator.callElevator(3);
    elevator.callElevator(5);

    // 내부에서 층수 선택
    elevator.selectFloor(7);
    elevator.selectFloor(2);

    // 선택한 층수 취소
    elevator.selectFloor(7);

    // 엘리베이터 동작 시작
    elevator.run();

    return 0;
}
