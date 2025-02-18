#include<stdio.h>
#include<stdint.h>
#include "GPIO.h"

// void SysTick_Init(void){
//   NVIC_ST_CTRL_R = 0;               // disable SysTick during setup
//   NVIC_ST_CTRL_R = 0x00000005;      // enable SysTick with core clock
// }

// // The delay parameter is in units of the 80 MHz core clock. (12.5 ns)

// void SysTick_Wait(uint32_t delay){
//   NVIC_ST_RELOAD_R = delay-1;  // number of counts to wait
//   NVIC_ST_CURRENT_R = 0;       // any value written to CURRENT clears
//   while((NVIC_ST_CTRL_R&0x00010000)==0){ // wait for count flag
//   }
// }

// // 800000*12.5ns equals 10ms

// void SysTick_Wait10ms(uint32_t delay){
//   uint32_t i;
//   for(i=0; i<delay; i++){
//     SysTick_Wait(800000);  // wait 10ms
//   }
// }

void SysTick_Init(){
	SysTick->CTRL=0;
	SysTick->LOAD=0xFFFFFF;
	SysTick->VAL=0;
	SysTick->CTRL=0x05;
}
void SysTick_Wait(uint32_t delay){
	SysTick->LOAD = delay-1; // number of counts to wait
	SysTick->VAL = 0; // any value written to CURRENT clears
	while((SysTick->CTRL&0x010000)==0){ // wait for count flag
	}
} 
void SysTick_Wait100us(uint32_t delay){
	uint32_t i;
	for(i=0; i<delay; i++){
		SysTick_Wait(7200); 
	}
}

void lcd_pulse()
{
	eset();
	SysTick_Wait100us(2);
	eclear();
	SysTick_Wait100us(2);
}
void lcd_sendcommand(uint32_t cmd)
{
	commandport&=~(0x1<<rs);
	dataport=(dataport&~0xF00)|((cmd&0xF0)<<4);
	lcd_pulse();
	dataport=(dataport&~0xF00)|((cmd&0x0F)<<8);
	lcd_pulse();
	commandport|=(0x01<<rs);
}
void lcd_senddata(uint32_t data)
{
	commandport|=(0x01<<rs);
	dataport=(dataport&~0xF00)|((data&0xF0)<<4);
	lcd_pulse();
	dataport=(dataport&~0xF00)|((data&0x0F)<<8);
	lcd_pulse();
}
void lcd_initialize()
{
	SysTick_Wait100us(400);
	lcd_sendcommand(0x30);
	SysTick_Wait100us(45);
	lcd_sendcommand(0x30);
	SysTick_Wait100us(2);
	lcd_sendcommand(0x30);
	SysTick_Wait100us(2);
	lcd_sendcommand(0x20);
	SysTick_Wait100us(1);
	lcd_sendcommand(0x20);
	SysTick_Wait100us(1);
	lcd_sendcommand(0x08);
	SysTick_Wait100us(1);
	lcd_sendcommand(0x01);
	SysTick_Wait100us(20);
	lcd_sendcommand(0x06);
	SysTick_Wait100us(1);
	lcd_sendcommand(0x0f);
	SysTick_Wait100us(1);
}
void lcd_printf(char c[])
{
	int i=0;
	SysTick_Wait100us(1);
	lcd_sendcommand(0x01);
	SysTick_Wait100us(20);
	lcd_sendcommand(0x06);
	SysTick_Wait100us(1);
	lcd_sendcommand(0x0f);
	SysTick_Wait100us(1);
	while(c[i]!='\0')
		{
			lcd_senddata(c[i]);
			i++;
		}
}