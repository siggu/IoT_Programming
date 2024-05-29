// 7. dot matrix 표정 다른 스마일 2초 반복해보기
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define dot "/dev/dot"

int main()
{
	int dot_d,i;
	unsigned char zero[2][8]={{0x00, 0x42, 0xA5, 0xA5, 0x00, 0x42, 0x3C, 0x00},
				{0x00, 0x00, 0xE7, 0x00, 0x00, 0x3C, 0x42, 0x00}};
	dot_d = open(dot, O_RDWR);
	if(dot_d<0)
	{
		printf("error\n");
		return 0;
	}
	for(i=0; i<100; i++)
	{
		if(i%2==1)
		{
			write(dot_d, &zero[0], sizeof(zero[0]));
			sleep(2);
		}
		else
		{
			write(dot_d, &zero[1], sizeof(zero[1]));
			sleep(2);
		}
	}
	close(dot);
	return 0;
}