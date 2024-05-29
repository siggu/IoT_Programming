1. 초기설정

sudo apt-get install gcc-4.4 g++-4.4 g++-4.4-multilib gcc-4.4-multilib lib32z1

2. 컴파일

/opt/gnueabi/opt/ext-toolchain/bin/arm-linux-gnueabihf-gcc spin.c -o spin

3. Test

- 윈도우(메인 OS)로 실행파일 복사

- Tera Term에서 포트 설정 후 설정 -> 시리얼 포트 -> 속도를 115200으로 설정

- Hybus-Smart4412 장비 부팅

- 메뉴 -> 전송 -> ZMODEM -> 보내기 에서 실행파일 선택

- chmod 777 [실행파일명] (실행파일 권한 설정)

- ./[실행파일명] (실행 후 테스트)

(★중요 : 만약 소스파일을 수정 했다면 Tera Term 에서 먼저 rm [실행파일명] 을 한 뒤 다시 ZMODEM -> 보내기 에서 실행파일 선택 후 chmod 777 [실행파일명] 와 ./[실행파일명] 다시 실행)
