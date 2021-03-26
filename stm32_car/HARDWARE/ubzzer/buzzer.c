#include "buzzer.h"
#include "sys.h"

void Buzzer_Init(void) {
	RCC->APB2ENR|=1<<2;      //使能GPIOA
	GPIOA->CRH&=0x0FFFFFFF;  //PA2配置为输出
	GPIOA->CRH|=0x30000000;  
	
	BUZZER=0;                //蜂鸣器不响
}


