// 3. dot matrix A~Z 출력해보기
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define dot "/dev/dot"

int main()
{
	int dot_d,i;
	unsigned char alpha[26][8]=
	{
		{0x3C, 0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x00}, //A
		{0x7C, 0x66, 0x66, 0x7C, 0x66, 0x66, 0x7C, 0x00}, //B
		{0x3C, 0x66, 0x60, 0x60, 0x60, 0x66, 0x3C, 0x00}, //C
		{0x78, 0x6C, 0x66, 0x66, 0x66, 0x6C, 0x78, 0x00}, //D
		{0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x7E, 0x00}, //E
		{0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60, 0x00}, //F
		{0x3C, 0x66, 0x60, 0x7E, 0x66, 0x66, 0x3E, 0x00}, //G
		{0x66, 0x66, 0x66, 0x7E, 0x66, 0x66, 0x66, 0x00}, //H
		{0x3C, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3C, 0x00}, //I
		{0x1E, 0x0C, 0x0C, 0x0C, 0x6C, 0x6C, 0x38, 0x00}, //J
		{0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x00}, //K
		{0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x00}, //L
		{0x66, 0xFF, 0xFF, 0xDB, 0xDB, 0xC3, 0xC3, 0x00}, //M
		{0x66, 0x66, 0x76, 0x7E, 0x6E, 0x66, 0x66, 0x00}, //N
		{0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, //O
		{0x7C, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x00}, //P
		{0x3C, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x3C, 0x06}, //Q
		{0x7C, 0x66, 0x66, 0x7C, 0x78, 0x6C, 0x66, 0x00}, //R
		{0x3C, 0x66, 0x60, 0x3C, 0x06, 0x66, 0x3C, 0x00}, //S
		{0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00}, //T
		{0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x00}, //U
		{0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x00}, //V
		{0xC3, 0xC3, 0xC3, 0xDB, 0xDB, 0xFF, 0x66, 0x00}, //W
		{0x66, 0x66, 0x3C, 0x18, 0x3C, 0x66, 0x66, 0x00}, //X
		{0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18, 0x00}, //Y
		{0x7E, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x7E, 0x00}  //Z
	};
	dot_d = open(dot, O_RDWR);
	if(dot_d<0)
	{
		printf("error\n");
		return 0;
	}
	for(i=0; i<26; i++)
	{
		write(dot_d, &alpha[i], sizeof(alpha[i]));
		sleep(1);
	}
	close(dot);
	return 0;
}