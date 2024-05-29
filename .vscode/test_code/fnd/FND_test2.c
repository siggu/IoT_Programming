// 2. FND에 소수점 표현하기
#include <stdio.h>

#include <stdlib.h>

#include <fcntl.h>

#include <string.h>



#define fnd "/dev/fnd"

unsigned char fnd_data[4];

void PrintFnd(char c,int i);

int main(){

	char data[6];



	int num, i, flag=1;

	int fnd_d;	

// 1 	 2 	3     4	     5	   6       7       8 	9     0     .

// 0xF9, 0xA4, 0xB0, 0x99, ~0x6D, ~0x7D, ~0x07, ~0x7F, 0x10, 0xC0, 0x80



	fnd_d=open(fnd, O_RDWR); // 해당 드라이버열기

	fnd_data[0]=0xFF;

	fnd_data[1]=0xFF;

	fnd_data[2]=0xFF;

	fnd_data[3]=0xFF;

	write(fnd_d, fnd_data ,sizeof(fnd_data));

	printf("Input=>");

	scanf("%s",  data);	



	for(i=0;i<5;i++){	



		if(data[i]=='\0')

			break;

		

		if(data[i]=='.'){	

			fnd_data[i-1]&= ~0x80;

			flag=0;

		}else if(flag)

			PrintFnd(data[i], i);

		else

			PrintFnd(data[i], i-1);



	}

	write(fnd_d, fnd_data ,sizeof(fnd_data));	

	sleep(2);

	close(fnd_d);

	return 0;

}



void PrintFnd(char c, int i){

	if(c=='0')

		fnd_data[i]=0xC0;

	if(c=='1')

		fnd_data[i]=0xF9;

	if(c=='2')

		fnd_data[i]=0xA4;

	if(c=='3')

		fnd_data[i]=0xB0;

	if(c=='4')

		fnd_data[i]=0x99;

	if(c=='5')

		fnd_data[i]=~0x6D;

	if(c=='6')

		fnd_data[i]=~0x7D;

	if(c=='7')

		fnd_data[i]=~0x07;

	if(c=='8')

		fnd_data[i]=~0x7F;

	if(c=='9')

		fnd_data[i]=0x10;

}