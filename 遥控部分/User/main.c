#include "stm32f10x.h"                  // Device header
#include "xiaochekongzhi.h"

int8_t chary[9] = {0x12, 0x22, 0x33};//小车移动数据
int8_t wenshidu[4]={0x01}; //温湿度数据
extern float ypitch,yroll,yyaw;
extern uint16_t P;
uint16_t C=0,o=0;//C:开机动画 0:模式切换停止运动标志位
extern uint8_t WENSHIDU_P;
 
int main(void)
{
	kongzhi_Init();

	while (1)
	{	
//***************************************	***开机动画**************************************//		
		
		if(C==0)
		{
			kaijihuamian();//开机画面
			chongzhi();//开机动画等待稳定后 重置一次放置
			C=1;
		}
		
//******************************************结束残留控制************************************//
		
		if(P!=0&&o==0) //更换之前 结束小车残留控制
		{
			chary[1]=0;chary[2]=0;
			NRF24L01_SendBuf(chary);
			o=1;
		}	
//*****************************************MPU6050姿态角控制*********************************//		
		
		xiaochekongzhi();	
		chary[0]=P; //模式切换  0：小车  1：舵机  2：温湿度
		chary[6]=WENSHIDU_P;
		NRF24L01_SendBuf(chary);//最后稳定下来
		WENSHIDU_P=0;//重新按按钮播报
		
//*******************************************模式切换****************************************//
		
		switch(P)
		{
			case 0://控制移动		

			chary[1] = round(-yroll);//转换为整型，mpu放置角度问题导致要加上负号 （上下）	
			chary[2] = round(yyaw); //左正右负 （左右)	
			yidongtubiao();
			OLED_ShowChinese(0,0,"车");OLED_Update();
			break;
			case 1:
				//控制舵机	
			chary[3] = round(yyaw); //左正右负 （左右)  90度为中心
			chary[4] = round(yroll);//转换为整型，mpu放置角度问题导致要加上负号 （上下）	ypitch
			chary[5] = round(ypitch); //抓取
			yidongtubiao();
			OLED_ShowChinese(0,0,"舵");OLED_Update();
			break;
			case 2://温湿度播报  //代表喝水	
			//*****************温湿度反馈显示*************************//
				OLED_Clear ();OLED_ShowChinese(40,32,"温湿度");OLED_Update();
			break;


		}
	}	
}
























