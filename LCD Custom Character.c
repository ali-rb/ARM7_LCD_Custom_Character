/*
  16x2 LCD custom character generation using LPC2148(ARM7)
  Ali Ranjbar
*/

#include <lpc214x.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

void delay_ms(uint16_t j) 
{
    uint16_t x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<6000; x++);
	}
}

void LCD_CMD(char command)
{
	IO0PIN = ( (IO0PIN & 0xFFFF00FF) | (command<<8) ); 
	delay_ms(2);
	IO0SET = 0x00000040; 
	IO0CLR = 0x00000030; 
	delay_ms(2);
	IO0CLR = 0x00000040; 
	delay_ms(5);
}

void LCD_INIT(void)
{
	IO0DIR = 0x0000FFF0;
	delay_ms(20);
	LCD_CMD(0x38);  
	LCD_CMD(0x0C);  
	LCD_CMD(0x06);  
	LCD_CMD(0x01);  
	LCD_CMD(0x80);  
}

void LCD_STRING (char* msg)
{
	uint8_t i=0;
	while(msg[i]!=0)
	{
		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | (msg[i]<<8) );
		IO0SET = 0x00000050; 
		IO0CLR = 0x00000020; 
		delay_ms(2);
		IO0CLR = 0x00000040; 
		delay_ms(5);
		i++;
	}
}

void LCD_CHAR (char msg)
{
		IO0PIN = ( (IO0PIN & 0xFFFF00FF) | (msg<<8) ); 
		delay_ms(2);
		IO0SET = 0x00000050; 
		IO0CLR = 0x00000020; 
		delay_ms(2);
		IO0CLR = 0x00000040; 
		delay_ms(5);
}

void LCD_BUILD_CUST_CHAR(unsigned char location, unsigned char *data)
{
	uint8_t i;
	if(location<8)
	{
		LCD_CMD((0x40 + (8*location))); 
		for(i=0;i<8;i++)
		LCD_CHAR(data[i]);
	}
}

int main(void)
{
	LCD_INIT();
	unsigned char cust_char0[8] = {0x00, 0x1F, 0x0A, 0x0A, 0x0A, 0x0A, 0x09, 0x00}; 
	unsigned char cust_char1[8] = {0x11, 0x19, 0x1D, 0x1F, 0x1F, 0x19, 0x11, 0x00}; 
	unsigned char cust_char2[8] = {0x12, 0x14, 0x18, 0x10, 0x18, 0x15, 0x13, 0x17}; 
	LCD_BUILD_CUST_CHAR(3,cust_char0);
	LCD_BUILD_CUST_CHAR(4,cust_char1);
	LCD_BUILD_CUST_CHAR(5,cust_char2);
	LCD_CMD(0x80);
	LCD_STRING("Cust Char :");
	LCD_CMD(0xC0);
	LCD_CHAR(5); 
	LCD_CHAR(' ');
	LCD_CHAR(3); 
	LCD_CHAR(' ');
	LCD_CHAR(4); 
	LCD_CHAR(' ');
	return 0;
}

