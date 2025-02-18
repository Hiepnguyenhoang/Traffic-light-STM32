#include<stdio.h>
#include<stdint.h>

typedef struct{
    volatile uint32_t CR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t APB2RSTR;
    volatile uint32_t APB1RSTR;
    volatile uint32_t AHBENR;
    volatile uint32_t APB2ENR;
}RCC_Typedef;

#define RCC ((RCC_Typedef*)0x40021000)

typedef struct{

	volatile uint32_t CRL;
	volatile uint32_t CRH;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t BRR;
}GPIO_Typedef;

#define GPIOA ((GPIO_Typedef*) 0x40010800)
#define GPIOB ((GPIO_Typedef*) 0x40010C00)

typedef struct
{
	volatile uint32_t EVCR;
	volatile uint32_t MAPR;
	volatile uint32_t EXTICR1;
}AFIO_Typedef;

#define AFIO ((AFIO_Typedef*) 0x40010000)

typedef struct
{
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
}EXTI_Typedef;

#define EXTI ((EXTI_Typedef*) 0x40010400)

typedef struct
{
    volatile uint32_t ISER[3];               
}NVIC_Typedef;

#define NVIC ((NVIC_Typedef*) 0xE000E100)

enum IRQn_Type
{
	EXTI0=6,
	EXTI1=7,
	EXTI2=8,
};

typedef struct
{
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile const uint32_t CALIB;
}SysTick_Typedef;

#define SysTick ((SysTick_Typedef*) 0xE000E010)

void SysTick_Init();
void SysTick_Wait(uint32_t delay);
void SysTick_Wait100us(uint32_t delay);

#define commandport GPIOB->ODR
#define rs 7
#define e 6
#define dataport GPIOA->ODR
#define eset() GPIOB->BSRR|=(1<<e)
#define eclear() GPIOB->BRR|=(1<<e)
void lcd_pulse();
void lcd_sendcommand(uint32_t cmd);
void lcd_senddata(uint32_t data);
void lcd_initialize();
void lcd_printf(char c[]);