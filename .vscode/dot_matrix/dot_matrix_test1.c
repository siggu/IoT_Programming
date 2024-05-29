// 1. dot matrix 점멸하기
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

#define dot "/dev/dot"

int main()
{
	int dot_d;
	unsigned char c[8] = {0x80 , 0x80 , 0x00 , 0x00,
			      0x00 , 0x00 , 0x00 , 0x00};

	dot_d = open(dot , O_RDWR);
	if(dot_d<0)
	{
		printf("Error\n");
		return 0;
	}

	write(dot_d , &c, sizeof(c));
	sleep(2);
	return 0;
}