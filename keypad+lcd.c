#define F_CPU 8000000ul
#include <avr/io.h>
#include <util/delay.h>
#include <avr/lcd4.h>
#define r0 PC0
#define r1 PC1
#define r2 PC2
#define r3 PC3
#define c0 PC4
#define c1 PC5
#define c2 PC6
#define c3 PC7

unsigned char saved_password[]={'6','0','1','4'};
unsigned char enter_password[];
unsigned char i, count;	
	
int main()
  {
  DDRB=0XFF;//Lcd 4bit mode
  lcdini();//START LCD
//  lcdcmd(0x0c);//display on , cursor off
//  lcdcmd(0x80);
//  lcdstring("ENTER PASSWORD");
//  lcdcmd(0xc0);
while (1)
     {
	  keyscan();  	
     }
return 0;
}

void keyscan()
 {
	DDRC=0Xf0;//keypad 4*4 matrix
	PORTC=0X0f;
//column0 741on
PORTC=PORTC&~(1<<c0);//c0=0
PORTC=PORTC|(1<<c1)|(1<<c2)|(1<<c3);//c1=c2=c3=1
if (!(PINC&(1<<r0)))
  {
	lcdstring("7");
	enter_password[i]='7';
	i++;
  }
if ((PINC&(1<<r1))==0)
{
	lcdstring("4");
	enter_password[i]='4';
	i++;
}
if (!(PINC&(1<<r2)))
{
	lcdstring("1");
	enter_password[i]='1';
	i++;
}
if (!(PINC&(1<<r3)))
{
	lcdstring(" ");
	enter_password[i]=' ';
	i++;
}

//column1 8520
PORTC=PORTC&~(1<<c1);//c1=0
PORTC=PORTC|(1<<c0)|(1<<c2)|(1<<c3);//c0=c2=c3=1
if (!(PINC&(1<<r0)))
{
	lcdstring("8");
	enter_password[i]='8';
	i++;
}
if ((PINC&(1<<r1))==0)
{
	lcdstring("5");
	enter_password[i]='5';
	i++;
}
if (!(PINC&(1<<r2)))
{
	lcdstring("2");
	enter_password[i]='2';
	i++;
}
if (!(PINC&(1<<r3)))
{
	lcdstring("0");
	enter_password[i]='0';
	i++;
}

//column2 963=
PORTC=PORTC&~(1<<c2);//c2=0
PORTC=PORTC|(1<<c0)|(1<<c1)|(1<<c3);//c0=c1=c3=1
if (!(PINC&(1<<r0)))
{
	lcdstring("9");
	enter_password[i]='9';
	i++;
}
if ((PINC&(1<<r1))==0)
{
	lcdstring("6");
	enter_password[i]='6';
	i++;
}
if (!(PINC&(1<<r2)))
{
	lcdstring("3");
	enter_password[i]='3';
	i++;
}
if (!(PINC&(1<<r3)))
{
	lcdstring("=");
	enter_password[i]='=';
	i++;
}

//column3 /*-+
PORTC=PORTC&~(1<<c3);//c3=0
PORTC=PORTC|(1<<c1)|(1<<c2)|(1<<c0);//c1=c2=c0=1
if (!(PINC&(1<<r0)))
{
	lcdstring("/");
	enter_password[i]='/';
	i++;
}
if ((PINC&(1<<r1))==0)
{
	lcdstring("*");
	enter_password[i]='*';
	i++;
}
if (!(PINC&(1<<r2)))
{
	lcdstring("-");
	enter_password[i]='-';
	i++;
}
if (!(PINC&(1<<r3)))
{
	lcdstring("+");
	enter_password[i]='+';
	i++;
}
	if(i==4)
	{
		password_check();
		i=0;
	}
}

void password_check()
{
 int flag=0;
 for (int i=0;i<4;i++)
 {
	if(saved_password[i]==enter_password[i])
	  flag++;
	else
	  flag--;  
}
if(flag==4)
  {
	lcdcmd(0x80);	
	lcdstring("Correct Password");	
	lcdcmd(0xc0);
	lcdstring("Welcome user !!!");
	
 }
else
  {
	lcdcmd(0x80);
	lcdstring("Incorrect");
	lcdcmd(0xc0);
	lcdstring("Try again");
    lcdstring(0xc0);
  }
     
}