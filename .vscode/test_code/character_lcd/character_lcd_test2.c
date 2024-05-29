// 2. character lcd에 문자 출력하기
#include<stdio.h>

#include<stdlib.h>

#include<fcntl.h>

#include<string.h>



#define clcd "/dev/clcd"

#define MAX_LEN	 20



int main()

{

	int clcd_d , str_len;

	char str[MAX_LEN];

	clcd_d = open(clcd , O_RDWR);

	

	if(clcd_d <0)

	{

		printf("디바이스 드라이버가 없습니다.\n");

		return 0;	

	}

	

	fgets(str , sizeof(str)-1 , stdin);

	//1.디스크립터  2.문자들 3.문자들의 크기

	str_len = write(clcd_d , str , 12);

	str[str_len-1] = '\0';



	close(clcd_d);

	return 0;

}