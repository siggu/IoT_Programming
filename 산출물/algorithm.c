#include <stdio.h>
#include <stdbool.h>

#define MAX_FLOORS 8 // 엘리베이터가 이동할 수 있는 최대 층수
#define MAX_REQUESTS 100 // 최대 요청 수

typedef struct {
    int floor; // 요청된 층수
} Request;

typedef struct {
    int current_floor; // 엘리베이터의 현재 층
    bool direction; // 엘리베이터의 이동 방향 (true: 위로, false: 아래로)
    bool requests[MAX_FLOORS]; // 각 층의 호출 상태
} Elevator;

// 엘리베이터 호출을 추가하는 함수
void add_request(Elevator *elevator, int floor) {
    if (floor < 1 || floor > MAX_FLOORS) { // 유효하지 않은 층 요청인지 확인
        printf("Invalid floor request: %d\n", floor);
        return;
    }
    elevator->requests[floor - 1] = true; // 호출된 층을 요청 목록에 추가
    printf("Request added for floor %d\n", floor);
}

// 엘리베이터가 요청된 층을 처리하는 함수
void process_requests(Elevator *elevator) {
    while (1) {
        bool has_requests = false; // 처리할 요청이 있는지 여부

        // 위로 가는 요청 처리
        for (int i = elevator->current_floor; i < MAX_FLOORS; i++) {
            if (elevator->requests[i]) { // 해당 층에 요청이 있는지 확인
                printf("Stopping at floor %d\n", i + 1); // 층에 도착했음을 출력
                elevator->current_floor = i; // 현재 층을 갱신
                elevator->requests[i] = false; // 요청을 처리했음을 표시
                has_requests = true; // 요청이 처리되었음을 표시
                break; // 다음 요청을 처리하기 위해 루프를 탈출
            }
        }

        // 아래로 가는 요청 처리
        for (int i = elevator->current_floor; i >= 0; i--) {
            if (elevator->requests[i]) { // 해당 층에 요청이 있는지 확인
                printf("Stopping at floor %d\n", i + 1); // 층에 도착했음을 출력
                elevator->current_floor = i; // 현재 층을 갱신
                elevator->requests[i] = false; // 요청을 처리했음을 표시
                has_requests = true; // 요청이 처리되었음을 표시
                break; // 다음 요청을 처리하기 위해 루프를 탈출
            }
        }

        if (!has_requests) { // 더 이상 처리할 요청이 없으면 루프 종료
            break;
        }
    }
}

int main() {
    Elevator elevator = {0, true, {false}}; // 엘리베이터 초기화 (현재 0층, 위로 이동 중, 모든 층 요청 없음)
    char command; // 사용자 명령을 저장할 변수
    int floor; // 호출된 층을 저장할 변수

    while (true) {
        printf("Enter command (c to call, q to quit): "); // 명령어 입력 요청
        scanf(" %c", &command); // 사용자로부터 명령어 입력 받기

        if (command == 'q') { // 'q' 명령어가 입력되면
            break; // 프로그램 종료
        } else if (command == 'c') { // 'c' 명령어가 입력되면
            printf("Enter floor to call: "); // 호출할 층 입력 요청
            scanf("%d", &floor); // 사용자로부터 호출할 층 입력 받기
            add_request(&elevator, floor); // 엘리베이터 호출 추가
        }

        process_requests(&elevator); // 엘리베이터 요청 처리
    }

    return 0; // 프로그램 정상 종료
}
