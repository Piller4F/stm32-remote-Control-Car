#include "sys.h"
#include "usart.h"
#include "delay.h"
#include "remote.h"
#include "car.h"
#include "tb6612.h"
#include "88led.h"
#include "buzzer.h"
#include "timer.h"
#include "echo.h"
#include "hc06.h"
#include "stdlib.h"
#include "math.h"

int main() {
	int i,len;
	float pre_pitch=0,pre_roll=0,pre_yaw=0;
	float pitch,roll,yaw;
	char buf[3][100]={0};
	int cnt,elen;
	Stm32_Clock_Init(9);         //ϵͳʱ�ӳ�ʼ��
	delay_init(72);              //��ʱ��ʼ��
	//uart_init(72,9600);          //���ڳ�ʼ��
	Car_Init();                  //С��������ʼ��
	Remote_Init();               //���ⰴ����ʼ��
	Tb6612_Init();               //�������ģ���ʼ��
	LED_Init();                  //8*8����LED��ʼ��
	Echo_Init();                 //��������ʼ��
	Buzzer_Init();               //��������ʼ��
    Tim4_Pwm_Init(MAX_SPEED,0);  //����pwm
    TIM3_Int_Init(10,7199);	     //88ledˢ���ʳ�ʼ��
	Tim2_Cap_Init(65535,72);
	uart_init(72,38400);
	USART2_Init(36,38400);
	LSPEED=0;
	RSPEED=0;
	while(1) {
		if(USART2_RX_STA&0x8000) {
			len=USART2_RX_STA&0x7FFF;
			cnt=0,elen=0;
			for(i=0;i<len;++i) {
				if(USART2_RX_BUF[i]==',') {
					buf[cnt][elen]=0;
					cnt++;
					elen=0;
				} else { 
					buf[cnt][elen++]=USART2_RX_BUF[i];
				}
//				USART1->DR=USART2_RX_BUF[i];
//				while((USART1->SR&0x40)==0);
			}
			pitch=(float)atof(buf[0]); 
			roll=(float)atof(buf[1]); 
			yaw=(float)atof(buf[2]); 
			printf("pitch:%f roll:%f yaw:%f\r\n",pitch,roll,yaw);
			USART2_RX_STA=0;
		}
		
		if(pitch>=55) {
			LSPEED=MAX_SPEED*0.4;
		    RSPEED=MAX_SPEED*0.4;
			GO_Left();	
			car.status=GOLEFT;
		} else if(pitch<=-65) {
			LSPEED=MAX_SPEED*0.4;
		    RSPEED=MAX_SPEED*0.4;
			GO_Right();
			car.status=GORIGHT;
		} else if(roll>=30) {
			LSPEED=MAX_SPEED*0.5;
		    RSPEED=MAX_SPEED*0.5;
			GO_Sharp();		
			car.status=GOUP;			
		} else if(roll<=-30) {
			LSPEED=MAX_SPEED*0.5;
		    RSPEED=MAX_SPEED*0.5;
			GO_Back();	
			car.status=GOBACK;
		} else {
			LSPEED=0;
			RSPEED=0;
		    GO_Stop();
			car.status=CHOOSE;
		}
//		if(fabs(pre_pitch-pitch)<50&&fabs(pre_roll-roll)<50&&fabs(pre_yaw-yaw)<50) {
//			printf("pitch:%f roll:%f yaw:%f\r\n",pitch,roll,yaw);
//			if(pitch>=30) {
//				
//				LSPEED=MAX_SPEED*0.5;
//			    RSPEED=MAX_SPEED*0.5;
//				GO_Sharp();
//			} else if(yaw>=30) {
//				
//				LSPEED=MAX_SPEED*0.5;
//			    RSPEED=MAX_SPEED*0.5;
//				GO_Left();
//			} else if(yaw<=-30) {
//				
//				LSPEED=MAX_SPEED*0.5;
//			    RSPEED=MAX_SPEED*0.5;
//				GO_Right();
//			} else if(pitch<=-30) {
//				
//				LSPEED=MAX_SPEED*0.5;
//			    RSPEED=MAX_SPEED*0.5;
//				GO_Back();
//			} else {
//				
//				LSPEED=0;
//				RSPEED=0;
//				GO_Stop();
//			}
//		}
//		Change_Status();
//		if(car.status==CHOOSE) {
//			Car_Init();
//			continue;
//		}
		//printf("%d\r\n",car.status);
	}
}








