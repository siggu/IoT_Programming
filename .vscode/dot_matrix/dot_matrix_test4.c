// 4. dot matrix와 tact switch를 이용한 사칙연산
#include<termios.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<asm/ioctls.h>

#define tact_d "/dev/tactsw"
#define dot "/dev/dot"

void showcalc(int *num, char op, int *i);
void result(int res);

int main()
{
	int tact, i=0;
	unsigned char c;
	int num[2];
	char op;
	
	tact=open(tact_d, O_RDWR);

	if(tact<0)
	{
		printf("open failed\n");
	}
	while(1)
	{
		while(1)
		{
			read(tact, &c, sizeof(unsigned char));	//보드에서 입력 넣을때
			usleep(100000);
			if(c)
				break;
		}
 
		switch(c)
		{
			case 1:printf("Input >> 1\n");num[i]=1;i++;result(1);sleep(1);break;
			case 2:printf("Input >> 2\n");num[i]=2;i++;result(2);sleep(1);break;
			case 3:printf("Input >> 3\n");num[i]=3;i++;result(3);sleep(1);break;
			case 4:printf("Input >> 4\n");num[i]=4;i++;result(4);sleep(1);break;
			case 5:printf("Input >> 5\n");num[i]=5;i++;result(5);sleep(1);break;
			case 6:printf("Input >> 6\n");num[i]=6;i++;result(6);sleep(1);break;
			case 7:printf("Input >> +\n");op='+';result(10);sleep(1);break;
			case 8:printf("Input >> -\n");op='-';result(11);sleep(1);break;
			case 9:printf("Input >> *\n");op='*';result(12);sleep(1);break;
			case 10:printf("Input >> /\n");op='/';result(13);sleep(1);break;
			case 11:showcalc(num, op, &i);break;
			case 12:printf("program shutdown\n");return;
		}
	}
	close(tact);
	return 0;
}
	
void showcalc(int *num, char op, int *i)
{
	int res;
	switch(op)
	{
	
		case '+':printf("Output >> %d\n", num[0]+num[1]);res=num[0]+num[1];break;
		case '-':printf("Output >> %d\n", num[0]-num[1]);res=num[0]-num[1];break;
		case '*':printf("Output >> %d\n", num[0]*num[1]);res=num[0]*num[1];break;
		case '/':printf("Output >> %d\n", num[0]/num[1]);res=num[0]/num[1];break;
	}
	*i=0;
	result(res);
}

void result(int res)
{
	int dot_d;
	unsigned char zero[14][8] ={{0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, //zero
			{0x18, 0x38, 0x78, 0x18, 0x18, 0x18, 0x7E, 0x00}, //one
			{0x3C, 0x66, 0x06, 0x1C, 0x30, 0x60, 0x7E, 0x00}, //two
			{0x3C, 0x66, 0x06, 0x1C, 0x06, 0x66, 0x3C, 0x00}, //three
			{0x0C, 0x1C, 0x3C, 0X6C, 0x7E, 0x0C, 0x0C, 0x00}, //four
			{0x7E, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C, 0x00}, //five
			{0x1C, 0x30, 0x60, 0x7C, 0x66, 0x66, 0x3C, 0x00}, //six
			{0x7E, 0x06, 0x0C, 0x18, 0x30, 0x30, 0x30, 0x00}, //seven
			{0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x3C, 0x00}, //eight
			{0x3C, 0x66, 0x66, 0x3E, 0x06, 0x0C, 0x38, 0x00}, //nine
			{0x18, 0x18, 0x18, 0xff, 0xff, 0x18, 0x18, 0x18},
			{0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00},
			{0xC3, 0x66, 0x3C, 0x18, 0x18, 0x3C, 0x66, 0xC3},
			{0x03, 0x06, 0x0C, 0x18, 0x30, 0x60, 0xC0, 0x80}};
	dot_d = open(dot, O_RDWR);
	

	write(dot_d, &zero[res], sizeof(zero[res]));
	usleep(450000);
	
	close(dot_d);
}