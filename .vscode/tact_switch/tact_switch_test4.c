// 4. tactsw를 눌렀을 경우 dipsw가 켜져있을 경우 led불이 켜지게 만든다.
#include <termios.h>

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <asm/ioctls.h>

#define tact_d "/dev/tactsw"
#define dip_d "/dev/dipsw"
#define led_d "/dev/led"

void ChaseAdd(int led, int tact, unsigned char *chase);

int main()
{
    int tact, dip, led, flag=0;
    char op;
    unsigned char data, chase=0xff, chase2=0xff;
    unsigned char c,t;

    if((tact = open(tact_d,O_RDWR)) < 0)
    {
        perror("open");
        exit(1);
    }

    if((dip = open(dip_d,O_RDWR)) < 0)
    {
        perror("open 3");
        exit(1);
    }

    if((led = open(led_d,O_RDWR)) < 0)
    {
        perror("open 2");
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
        read(dip,&t,sizeof(t));

        switch(c)
        {
            case 1: if((t & 0x01) == 0x01)
                {
                    data = 0xfe;
                    write(led,&data,sizeof(unsigned char));
                }
                break;
            case 2: if((t & 0x02) == 0x02)
                {
                    data = 0xfd;
                    write(led,&data,sizeof(unsigned char));
                }
                break;
            case 3: if((t & 0x04) == 0x04)
                {
                    data = 0xfb;
                    write(led,&data,sizeof(unsigned char));
                }
                break;
            case 4: if((t & 0x08) == 0x08)
                { 
                    data = 0xf7;
                    write(led,&data,sizeof(unsigned char));
                }
                break;
            case 5: if((t & 0x10) == 0x10)
                {
                    data = 0xef;
                    write(led,&data,sizeof(unsigned char));
                }
                break;
            case 6: if((t & 0x20) == 0x20)
                {
                    data = 0xdf;
                    write(led,&data,sizeof(unsigned char));
                }
                break;
            case 7: if((t & 0x40) == 0x40)
                {
                    data = 0xbf;
                    write(led,&data,sizeof(unsigned char));
                }
                break;
            case 8: if((t & 0x80) == 0x80)
                {
                    data = 0x7f;
                    write(led,&data,sizeof(unsigned char));
                }
                break;
            case 9: data = ~t;
                write(led,&data,sizeof(unsigned char));
                break;
            case 10: ChaseAdd(led,tact,&chase);
                break;
            case 11: chase2 = ~(~chase & t);
                 write(led,&chase2,sizeof(unsigned char));
                break;
            case 12: exit(1); 
        }

        sleep(1);
        c=0;
    }

    close(tact);
    close(dip);
    close(led);
    return 0;
}

void ChaseAdd(int led, int tact, unsigned char *chase)
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