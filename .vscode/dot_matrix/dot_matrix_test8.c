// dot matrix로 전광판 만들기
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <asm/ioctls.h>

#define tact_d "/dev/tactsw"
#define dot "/dev/dot"

void menu();
void streaming();

int main()
{
	int tact, i = 0;
	unsigned char c;

	tact = open(tact_d, O_RDWR);
	if(tact<0)
	{
		printf("open failed\n");
	}

	while(1)
	{
		menu();
		while(1)
		{
			read(tact, &c, sizeof(unsigned char));
			usleep(100000);
			if(c)	break;
		}

		switch(c)
		{
			case 1:streaming();break;
			case 12:printf("Shutdown!\n");return;
		}

	}
	close(tact);
	return 0;
}

void menu()	//tact 선택 목록
{
	puts("*********Dot Dot Menu*********");
	puts("* 1.     S T R E A M         *");
	puts("* 12.     E X I T            *");
	puts("******************************");
}

void streaming()
{
	int dot_d, i, j, k;
	unsigned char tmp[16][8]={0};
	unsigned char num[15][8]=
	{
		{0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C, 0x00}, //C
		{0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00}, //H
		{0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, //O
		{0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}, //I
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0
		{0x1E, 0x0C, 0x0C, 0x0C, 0x6C, 0x6C, 0x38, 0x00}, //J
		{0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, //O
		{0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, //O
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0
		{0x3C, 0x66, 0x60, 0x3C, 0x06, 0x66, 0x3C, 0x00}, //S
		{0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x7E, 0x00}, //E
		{0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, //O
		{0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x00}, //K
		{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, //0
	};
	dot_d = open(dot, O_RDWR);
	
	for(k=7; k>0; k--)
	{
		for(j=0; j<9; j++)
			tmp[0][j]=num[0][j]>>k;	
		write(dot_d, &tmp[0], sizeof(tmp[0]));
		usleep(80000);
	}

	for(i=1; i<15; i++)
	{
		for(k=0; k<7; k++){
			for(j=0; j<9; j++){
				tmp[i][j]=num[i-1][j]<<k;
				tmp[i][j]|=num[i][j]>>6-k;
			}
			write(dot_d, &tmp[i], sizeof(tmp[i]));
			usleep(80000);
		}
	}

	for(k=0; k<7; k++)
	{
		for(j=0; j<9; j++){
			tmp[i][j]=num[i-1][j]<<k;
		}
		write(dot_d, &tmp[i-1], sizeof(tmp[i]));
		usleep(80000);
	}

	close(dot_d);
}
