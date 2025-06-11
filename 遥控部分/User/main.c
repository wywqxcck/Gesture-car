#include "stm32f10x.h"                  // Device header
#include "xiaochekongzhi.h"

int8_t chary[9] = {0x12, 0x22, 0x33};//С���ƶ�����
int8_t wenshidu[4]={0x01}; //��ʪ������
extern float ypitch,yroll,yyaw;
extern uint16_t P;
uint16_t C=0,o=0;//C:�������� 0:ģʽ�л�ֹͣ�˶���־λ
extern uint8_t WENSHIDU_P;
 
int main(void)
{
	kongzhi_Init();

	while (1)
	{	
//***************************************	***��������**************************************//		
		
		if(C==0)
		{
			kaijihuamian();//��������
			chongzhi();//���������ȴ��ȶ��� ����һ�η���
			C=1;
		}
		
//******************************************������������************************************//
		
		if(P!=0&&o==0) //����֮ǰ ����С����������
		{
			chary[1]=0;chary[2]=0;
			NRF24L01_SendBuf(chary);
			o=1;
		}	
//*****************************************MPU6050��̬�ǿ���*********************************//		
		
		xiaochekongzhi();	
		chary[0]=P; //ģʽ�л�  0��С��  1�����  2����ʪ��
		chary[6]=WENSHIDU_P;
		NRF24L01_SendBuf(chary);//����ȶ�����
		WENSHIDU_P=0;//���°���ť����
		
//*******************************************ģʽ�л�****************************************//
		
		switch(P)
		{
			case 0://�����ƶ�		

			chary[1] = round(-yroll);//ת��Ϊ���ͣ�mpu���ýǶ����⵼��Ҫ���ϸ��� �����£�	
			chary[2] = round(yyaw); //�����Ҹ� ������)	
			yidongtubiao();
			OLED_ShowChinese(0,0,"��");OLED_Update();
			break;
			case 1:
				//���ƶ��	
			chary[3] = round(yyaw); //�����Ҹ� ������)  90��Ϊ����
			chary[4] = round(yroll);//ת��Ϊ���ͣ�mpu���ýǶ����⵼��Ҫ���ϸ��� �����£�	ypitch
			chary[5] = round(ypitch); //ץȡ
			yidongtubiao();
			OLED_ShowChinese(0,0,"��");OLED_Update();
			break;
			case 2://��ʪ�Ȳ���  //�����ˮ	
			//*****************��ʪ�ȷ�����ʾ*************************//
				OLED_Clear ();OLED_ShowChinese(40,32,"��ʪ��");OLED_Update();
			break;


		}
	}	
}
























