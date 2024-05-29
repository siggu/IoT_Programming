// 3. 번호를 누룰때마다 숫자가 왼쪽으로 추가되며 출력되게 하고, 만약 10자를 넘을 경우 가장 왼쪽 숫자가 사라지게 만들자
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <asm/ioctls.h>

#define tact_d "/dev/tactsw"
#define lcd_d "/dev/clcd"

int main()
{
    int tact, lcd, flag=0;
    char op;
    unsigned char data[10];
    unsigned char c;

    if((tact = open(tact_d,O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }

    if((lcd = open(lcd_d,O_RDWR)) < 0)
    {
        perror("open 2");
        exit(1);
    }

    memset(data,0,sizeof(data));

    while(1)
    {
        while(1)
        {
            read(tact,&c,sizeof(c));
            if(c)
                break;
        }

        if(flag >= 10)
        {
            strcpy(data,data+1);
        }

        switch(c)
        {
            case 1: strcat(data,"1");
                write(lcd,&data,sizeof(data));
                flag++;
                break;
            case 2: strcat(data,"2");
                write(lcd,&data,sizeof(data));
                flag++;
                break;
            case 3: strcat(data,"3");
                write(lcd,&data,sizeof(data));
                flag++;
                break;
            case 4: strcat(data,"4");
                write(lcd,&data,sizeof(data));
                flag++;
                break;
            case 5: strcat(data,"5");
                write(lcd,&data,sizeof(data));
                flag++;
                break;
            case 6: strcat(data,"6");
                write(lcd,&data,sizeof(data));
                flag++;
                break;
            case 7: strcat(data,"7");
                write(lcd,&data,sizeof(data));
                flag++;
                break;
            case 8: strcat(data,"8");
                write(lcd,&data,sizeof(data));
                flag++;
                break;
            case 9: strcat(data,"9");
                write(lcd,&data,sizeof(data));
                flag++;
                break;
            case 10: strcat(data,"0");
                write(lcd,&data,sizeof(data));
                flag++;
                break;
            case 11: exit(1);
            case 12: exit(1); 
        }

        sleep(1);
        c=0;
    }

    close(tact);
    return 0;
}