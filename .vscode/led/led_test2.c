// 2. LED 점멸하기 2
#include<stdio.h>

#include<stdlib.h>

#include<unistd.h>

#include<fcntl.h>

#include<sys/types.h>

#include<sys/ioctl.h>

#include<sys/stat.h>



//디바이스 드라이버가 들어있는 경로 위치를 적어논것

#define led "/dev/led"



void LedUp(int dev);

void LedDown(int dev);

void LedAll(int dev);

void LedOddEven(int dev);

void LedInside(int dev);

void LedOutside(int dev);

int main()

{

	int dev , i , num;

	unsigned char data;



	//1. 해당 드라이버 경로

	//2. O_RDWR

	dev = open(led,O_RDWR);

	if(dev <0)

	{

		printf("열수 없습니다.\n");

		exit(0);

	}

	

	while(1)

	{

		puts("**********JooSeok Menu**********");

		puts("* 1.	LED UP	  Shift	     *");	

		puts("* 2.	LED DOWN  Shift	     *");	

		puts("* 3.	A   L   L	     *");	

		puts("* 4.	O D D _ E V E N	     *");	

		puts("* 5.	I N S I D E	     *");	

		puts("* 6.	O U T S I D E	     *");	

		puts("* 0.	E  X  I  T	     *");

		puts("********************************");

		fputs("Select the menu number : " , stdout);

		scanf("%d" , &num);



		switch(num)

		{

			case 1:

			  LedUp(dev);

			  break;

			case 2:

			  LedDown(dev);

			  break;

			case 3:

			  LedAll(dev);

			  break;

			case 4:

			  LedOddEven(dev);

			  break;

			case 5:

			  LedInside(dev);

			  break;

			case 6:

			  LedOutside(dev);

			  break;

			case 0:

			  close(dev);

			  return 0;

		} 

		putchar('\n');	

	}

	return 0;

}



void LedUp(int dev)

{

	int i;

	unsigned char data;

	for(i=1 ; i<9 ; ++i)

	{

		data = 0xff<<i;

		usleep(100000);

		//1. 파일의 디스크립트

		//2. 데이터 전달

		//3. 크기를 넣어준다.

		write(dev , &data , sizeof(unsigned char));

		usleep(100000);

	}

}

void LedDown(int dev)

{

	int i;

	unsigned char data;

	for(i=1 ; i<9 ; ++i)

	{

		data = 0xff>>i;

		usleep(100000);

		//1. 파일의 디스크립트

		//2. 데이터 전달

		//3. 크기를 넣어준다.

		write(dev , &data , sizeof(unsigned char));

		usleep(100000);

	}

}

void LedAll(int dev)

{

	int i;

	unsigned char data;

	for(i=1 ; i<15 ; ++i)

	{

		if(i%2 == 1)

		{

			data = 0x00;  // led 켜짐

		}

		else

		{

			data = 0xff;

		}

		//1. 파일의 디스크립트

		//2. 데이터 전달

		//3. 크기를 넣어준다.

		write(dev , &data , sizeof(unsigned char));

		usleep(100000);

	}

}



void LedOddEven(int dev)

{

	int i , j;

	unsigned char data;

	for(i=1 ; i<15 ; ++i)

	{

		if(i%2 == 1)

		{

			data = 0x55;

		}

		else

		{	data = 0xAA;



		}

		usleep(100000);

		write(dev , &data , sizeof(unsigned char));

		usleep(100000);

	}

}

void LedInside(int dev)

{

	int i;

	unsigned char data;

	for(i=1 ; i<5 ; ++i)

	{

		data = (0xFF>>i) & (0xFF<<i);

		usleep(100000);

		write(dev , &data , sizeof(unsigned char));

		usleep(100000);

	}

}

void LedOutside(int dev)

{

	int i;

	unsigned char data;

	for(i=4 ; i>=0 ; --i)

	{

		data = ~((0xFF>>i) & (0xFF<<i));

		usleep(100000);

		write(dev , &data , sizeof(unsigned char));

		usleep(100000);

	}

}