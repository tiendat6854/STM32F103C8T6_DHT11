#include "stm32f10x.h"                  // Device header
#include "timer2.h"
#include "dht11.h"

void GPIO_Init_PC13(void)
{
  RCC->APB2ENR |= (1 << 4);
	GPIOC->CRH &= ~(15 << 20);
	GPIOC->CRH |= (3 << 20);
}

void GPIO_Init_PB6(void)
{
  GPIO_InitTypeDef gpioInit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_Out_OD;
	gpioInit.GPIO_Pin = GPIO_Pin_6;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOB, &gpioInit);
}

void GPIO_Init_PA0(void)
{
  GPIO_InitTypeDef gpioInit;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	gpioInit.GPIO_Mode = GPIO_Mode_Out_PP;
	gpioInit.GPIO_Pin = GPIO_Pin_0;
	gpioInit.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA, &gpioInit);
}

int main()
{
  GPIO_Init_PC13();
	timer2_Init();
	GPIO_Init_PB6();
	GPIO_Init_PA0();
	
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	
	while(1)
	{
		DHT11();
		
		/* da doc duoc nhiet do va do am */
		
		// do am: byte 0
		// delay 24ms
		// nhiet do: byte 2
		
		ReadData();  // du lieu do am, nhieu do doc duoc
		
	  GPIOC->ODR |= (1 << 13);
		delay_ms(100);
		GPIOC->ODR &= ~(1 << 13);
		delay_ms(200);
	}
}
