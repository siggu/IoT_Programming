[https://cccding.tistory.com/58]

# 컴파일 방법 및 테스트

## 1. Tera term으로 컴파일 및 테스트(Windows 환경)

- sudo apt-get install gcc-4.4 g++-4.4 g++-4.4-multilib gcc-4.4-multilib lib32z1

- 우분투에서 파일명.c로 소스파일 작성

- /opt/gnueabi/opt/ext-toolchain/bin/arm-linux-gnueabihf-gcc [파일명].c -o [실행파일명] (arm계열로 컴파일)

- window(메인 OS)로 실행파일 복사

- Tera term에서 포트 설정 후 설정 -> 시리얼 포트 -> 속도를 115220으로 설정

- Hybus-Smart4412 장비 부팅

- 메뉴 -> 전송 -> ZMODEM -> 보내기

  - 실행파일 선택

  - chmod 777 [실행파일명] (실행파일 권한 설정)

  - ./[실행파일명] (실행 후 테스트)

(★중요 : 만약 소스파일을 수정 했다면 Tera Term 에서 먼저 rm [실행파일명] 을 한 뒤 다시 ZMODEM -> 보내기 에서 실행파일 선택 후 chmod 777 [실행파일명] 와 ./[실행파일명] 다시 실행)

## 2. ubuntu에서 컴파일 및 테스트(Linux 환경)

- sudo apt-get install gcc-4.4 g++-4.4 g++-4.4-multilib gcc-4.4-multilib lib32z1

- 우분투에서 파일명.c 로 소스파일 작성

- /opt/gnueabi/opt/ext-toolchain/bin/arm-linux-gnueabihf-gcc [파일명].c -o [실행파일명] (arm계열로 컴파일)

- sudo apt-get install minicom

- USB를 설정해준다(FTDI FT232R USB UART [0600]을 체크해준다)

- lsusb (USB 확인)

- dmesg | grep tty (tty번호 확인 , 일반적으로 ttyUSB0)

- sudo minicom -s

- Serial port setup 으로 이동해서 들어간다

```
     A - Serial Device      : /dev/ttyUSB0

     B - Lockfile Location     : /var/lock

     C - Callin Program      :

     D - Callout Program      :

     E -  Bps/Par/Bits       : 115200 8N1

     F -  Hardware Flow Control : No

     G - Software Flow Control : No
```

- 위와 같이 설정

- Save setup as dfl 로 이동한 뒤 엔터를 누른다

- Exit로 이동해서 나온다

- ctrl+A를 누른 다음 Z ,X를 차례대로 누른다음 yes를 선택하여 minicom에서 빠져나온다.

- sudo minicom -w

- ctrl+A를 누른다음 S를 누른 뒤 zmodem으로 들어간다.

- 실행파일이 저장된 경로로 들어간다(디렉토리에 들어갈때는 스페이스를 두번 누른다)

- 해당 실행파일은 찾은 뒤 스페이스를 한번 눌러 선택하고 엔터를 누른다

- 엔터를 한번 더 누른 뒤 ./[실행파일명]을 실행한다

- 테스트가 제대로 되는지 확인한다.

- minicom을 빠져나올 때는 ctrl+A를 누른 다음 Z ,X를 차례대로 누른다

(★중요 : 만약 소스파일을 수정 했다면 먼저 rm [실행파일명] 을 한 뒤 다시 sudo minicom -w부터 시작한다)
