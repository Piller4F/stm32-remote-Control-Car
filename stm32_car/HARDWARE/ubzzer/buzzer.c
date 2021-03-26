#include "buzzer.h"
#include "sys.h"

void Buzzer_Init(void) {
	RCC->APB2ENR|=1<<2;      //ʹ��GPIOA
	GPIOA->CRH&=0x0FFFFFFF;  //PA2����Ϊ���
	GPIOA->CRH|=0x30000000;  
	
	BUZZER=0;                //����������
}


