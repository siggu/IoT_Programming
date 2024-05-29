// 1. LED 점멸하기 1
#include<stdio.h>

#include<stdlib.h>

#include<unistd.h>

#include<fcntl.h>

#include<sys/types.h>

#include<sys/ioctl.h>

#include<sys/stat.h>



//디바이스 드라이버가 들어있는 경로 위치를 적어논것

#define led "/dev/led"

int main()

{

	int dev , i;

	unsigned char data;

	//1. 해당 드라이버 경로

	//2. O_RDWR

	dev = open(led,O_RDWR);

	

	if(dev <0)

	{

		printf("열수 없습니다.\n");

		exit(0);

	}

	

	for(i=0 ; i<8 ; ++i)

	{

		if(i%2 == 1)

		{

			data = 0xff;

		}

		else

		{

			data = 0x00;

		}

		//1. 파일의 디스크립트

		//2. 데이터 전달

		//3. 크기를 넣어준다.

		write(dev , &data , sizeof(unsigned char));

		usleep(100000);

	}

	close(dev);



	return 0;

}