#include "hongwai.h"
#include "sys.h"

//#define LHONG PCin(3)
//#define RHONG PBin(14)

void Hong_Wai_Init(void) {
	RCC->APB2ENR|=1<<4;
	RCC->APB2ENR|=1<<3;
	
	GPIOB->CRH&=0xF0FFFFFF;
	GPIOB->CRH|=0x08000000;
	
	GPIOC->CRL&=0xFFFF0FFF;
	GPIOC->CRL|=0x00008000;
	
	GPIOB->ODR|=1<<14;
	GPIOC->ODR|=1<<3;
}








