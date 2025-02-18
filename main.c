#include"GPIO.h"
#include<stdint.h>
#include <stdio.h>
volatile uint32_t input = 0;
volatile uint32_t count = 0;

struct state{
    uint32_t PortBH_Val;
    uint32_t PortBL_Val;
    uint32_t Wait;
    uint32_t Next[8];
};

typedef const struct state state_t;
#define allStopW 0
#define goS 1
#define waitS 2
#define allStopS 3
#define walk 4
#define white 5
#define redOn1 6
#define redOff1 7
#define redOn2 8
#define redOff2 9
#define allStopWalk 10
#define goW 11
#define waitW 12


state_t FSM[13] ={
    {0x09, 0x1, 0, {allStopW, goW, goS, goS, walk, walk, goS, goS}},
    {0x0C, 0x1, 10, {waitS, waitS, goS, waitS, waitS, waitS, waitS, waitS}},
    {0x0A, 0x1, 5, {allStopS,allStopS,allStopS,allStopS,allStopS,allStopS,allStopS,allStopS}},
    {0x09, 0x1, 0, {allStopS, goW, goS, goW, walk, walk, walk, walk}},
    {0x09, 0x2, 10, {white, white, white, white, walk, white, white, white}},
		{0x09, 0x2, 1, {redOn1, redOn1, redOn1, redOn1, redOn1, redOn1, redOn1, redOn1}},
    {0x09, 0x1, 2, {redOff1, redOff1,redOff1,redOff1,redOff1,redOff1,redOff1,redOff1}},
    {0x09, 0x0, 3, {redOn2, redOn2, redOn2,redOn2,redOn2,redOn2,redOn2,redOn2}},
    {0x09, 0x1, 4, {redOff2, redOff2,redOff2,redOff2,redOff2,redOff2,redOff2,redOff2}},
    {0x09, 0x0, 5, {allStopWalk,allStopWalk,allStopWalk,allStopWalk,allStopWalk,
    allStopWalk,allStopWalk,allStopWalk}},
    {0x09, 0x1, 0, {allStopWalk, goW, goS, goW, walk, goW, goS, goW}},
    {0x21, 0x1, 10, {waitW, goW, waitW,waitW,waitW,waitW,waitW,waitW,}},
    {0x11, 0x1, 5, {allStopW,allStopW,allStopW,allStopW,allStopW,allStopW,allStopW,allStopW}},
    
};

void delay1s(uint32_t time){
	char c[5];
	if(time==0){
		count=0;
		sprintf(c,"%02d",count);
		lcd_printf(c);
	}
	else{
		while(count < time){
	        sprintf(c, "%02d", count + 1);
	        lcd_printf(c);
			SysTick_Wait100us(10000); ;
	        count++; 
   		}
	}
}

void EXTI0_IRQHandler(void) {
    // Ð?c giá tr? PA0
    input = (input&~(1U << 0)) | (GPIOA->IDR&0x01);
    
    // Ki?m tra xem c? ng?t cho EXTI0 có dang du?c set không
    if (EXTI->PR & (1U << 0)) {
        EXTI->PR |= (1U << 0);
    }
}

void EXTI1_IRQHandler(void) {
     // Ð?c giá tr? PA1
    input = (input&~(1U << 1)) | (GPIOA->IDR&0x02);
    
    // Ki?m tra xem c? ng?t cho EXTI1 có dang du?c set không
    if (EXTI->PR & (1U << 1)) {
        EXTI->PR |= (1U << 1);
    }
}

void EXTI2_IRQHandler(void) {
     // Ð?c giá tr? PA2
    input = (input&~(1U << 2)) | (GPIOA->IDR&0x04);
    
    // Ki?m tra xem c? ng?t cho EXTI2 có dang du?c set không
    if (EXTI->PR & (1U << 2)) {
        EXTI->PR |= (1U << 2);
    }
}

int main(){
    uint32_t CS; // Current state
    SysTick_Init();
    /*enable clock*/
	RCC->APB2ENR=0x0D;//enable port A B and AFIO
	GPIOA->CRL=0x888; //A0,1,2 (Walk-South-West)
	GPIOA->ODR=0x00;
	
	GPIOB->CRL=0x22000022; //B0,1 (Walk leds R-G) vs B6,7 (Rs, E LCD)
	GPIOB->CRH=0x0222222; //B8,9,10,11,12,13 (South-West Leds R-Y-G)
	
	GPIOA->CRH=0x2222; // A8,9,10,11 -> D4-D7 LCD
	
	AFIO->EXTICR1=0x00;
	
	EXTI->IMR |= 1;
	EXTI->IMR |= 1<<1;
	EXTI->IMR |= 1<<2;
	
	EXTI->RTSR |= 1;
	EXTI->RTSR |= 1<<1;
	EXTI->RTSR |= 1<<2;
	
	EXTI->FTSR |= 1;
	EXTI->FTSR |= 1<<1;
	EXTI->FTSR |= 1<<2;
	
	NVIC->ISER[0]|=1<<6;
	NVIC->ISER[0]|=1<<7;
	NVIC->ISER[0]|=1<<8;
	lcd_initialize();

    CS = allStopW;
    while(1){
        // 1) Output
        GPIOB->ODR = (GPIOB->ODR & (~0x003)) | (FSM[CS].PortBL_Val); // Output Walk led (B0, B1)
        GPIOB->ODR = (GPIOB->ODR & (~0x3F00)) | (FSM[CS].PortBH_Val << 8); // Output South/West led (B8 - B13)
        
        //2) Wait
        if (CS == white || CS == redOn1 || CS == redOn2 || CS == redOff1 || CS == redOff2){
        	char c[5];
			sprintf(c, "%02d", FSM[CS].Wait);
			lcd_printf(c);
			SysTick_Wait100us(10000);
			 
        }
        else{
        	delay1s(FSM[CS].Wait);
			if(CS==goS||CS==goW||CS==walk){
				while(FSM[CS].Next[input]==goS||FSM[CS].Next[input]==goW||FSM[CS].Next[input]==walk){
					char c[5];
					sprintf(c, "%02d", count + 1);
					lcd_printf(c);
					SysTick_Wait100us(10000);  
					count++;
				}
			}
			count = 0;
        }
		
        
        //3) Next state
        CS = FSM[CS].Next[input];
    }
	
	
}