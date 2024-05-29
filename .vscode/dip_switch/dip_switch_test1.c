// 1. dip switch 테스트
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

#define dip "/dev/dipsw"

int main()
{
	int dip_d;
	unsigned char c;
	dip_d = open(dip, O_RDWR);
	while(1)
	{
		read(dip_d , &c , sizeof(c));
		if(c)
		  break;
	}

	printf("%d\n",c);
	return 0;
}