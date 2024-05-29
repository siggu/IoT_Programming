/*
2. tact버튼을 누를 경우 lcd 화면에 문자를 띄운다.

ex) A    B    C

      D    E    F

      G    H    초기화

      증가 감소 종료
*/

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <asm/ioctls.h>

#define tact_d "/dev/tactsw"
#define led_d "/dev/led"

void ChaseAdd(int led, unsigned char *chase);

int tact, led;

int main()
{
    unsigned char c;
    unsigned char buf=0xff, chase=0xff;

    if((tact = open(tact_d,O_RDWR)) < 0)
    {
        perror("tact open");
        exit(1);
    }

    if((led = open(led_d,O_RDWR)) < 0)
    {
        perror("led open");
        exit(1);
    }

    while(1)
    {
        while(1)
        {
            read(tact,&c,sizeof(c));
            if(c)
                break;
        }

        switch(c)
        {
            case 1: buf = ~(0x01);
                write(led,&buf,sizeof(buf));
                break;
            case 2: buf = ~(0x02);
                write(led,&buf,sizeof(buf));
                break;
            case 3: buf = ~(0x04);
                write(led,&buf,sizeof(buf));
                break;
            case 4: buf = ~(0x08);
                write(led,&buf,sizeof(buf));
                break;
            case 5: buf = ~(0x10);
                write(led,&buf,sizeof(buf));
                break;
            case 6: buf = ~(0x20);
                write(led,&buf,sizeof(buf));
                break;
            case 7: buf = ~(0x40);
                write(led,&buf,sizeof(buf));
                break;
            case 8: buf = 0x7f;
                write(led,&buf,sizeof(buf));
                break;
            case 9: buf = 0x00;
                write(led,&buf,sizeof(buf));
                break;
            case 10: ChaseAdd(led,&chase);
                break;
            case 11: write(led,&chase,sizeof(chase));
                break;
            case 12: exit(1); 
        }
        sleep(1);
        buf = 0xff;
        write(led,&buf,sizeof(buf));
    }

    close(tact);
    close(led);
    return 0;
}

void ChaseAdd(int led,unsigned char *chase)
{
    sleep(1);
    unsigned char d=0;
    printf("input\n");
    while(1)
    {
        while(1)
        {
            read(tact,&d,sizeof(d));
            if(d)
                break;
        }
        
        printf("%d\n",d);
        switch(d)
        {
            case 1: *chase &= ~(0x01);
                break;
            case 2: *chase &= ~(0x02);
                break;
            case 3: *chase &= ~(0x04);
                break;
            case 4: *chase &= ~(0x08);
                break;
            case 5: *chase &= ~(0x10);
                break;
            case 6: *chase &= ~(0x20);
                break;
            case 7: *chase &= ~(0x40);
                break;
            case 8: *chase &= ~(0x80);
                break;
            case 10: return;
                break;
            case 12: exit(1);
        }
        sleep(1);
        d=0;
    }
    printf("chase end\n");   
}