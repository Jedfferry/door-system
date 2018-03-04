//*****************************************************  
//*     FileName:     Main.h                          *
//*     Created:      2015.1.1                       * 
//*     Last Change:  2015.1.15                       *
//*     Author:       FanChangFu                      *         
//*     Compiler:     KEIL C51 uVision4.0             * 
//*     CPU:          STC89C52RC                      *
//*     Description:  DoorSystems                     *     				
//*     OSC use 12MHz crystal.                        *
//*****************************************************


#include "reg52.h"
/*-----------------���Ͷ���--------------------*/
typedef enum bool
{
	 FALSE=0,
	 TRUE=1
}bool;

typedef enum error
{
   FAIL=0,
	 SUCCESS=1
}error;
/*--------------------------------------------*/



/*----------------���Ŷ���--------------------*/
sbit Speaker=P2^7;       //���Ʒ�����
sbit Relay=P1^4;         //���Ƽ̵���
sbit Led=P1^2;           //����Led��
sfr WDT=0xe1;            //���Ź�������

sfr ISP_DATA=0xe2;       //EEPROM��ؼĴ���
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;
/*--------------------------------------------*/


/*---------------����Ԥ����--------------------*/
void SystemInit();      //ϵͳ��ʼ��
void BaudRateSetup();   //���ò�����
void SerialPortSetup(); //���ô���
void INT0Setup();       //�����ⲿ�ж�0
void Tf0AndTf1Setup();  //��ʱ��0�Ͷ�ʱ��1����
void IpSetup();         //�ж����ȼ�����
void SetLedOn();        //����Ƶģ���Led��
void SetLedOff();       //�ر���Ƶģ���Led��
void SearchCard();      //����Ƶģ�鷢��Ѱ��ָ��
error MatchCardSN();    //������Ƶģ�鷢�����Ŀ����к��ڵ�ǰϵͳ���Ƿ����
void SearchCardData();  //����Ƶģ�鷢�Ͷ���ƬEPPROM�е�����
error MatchCardData();  //У�鿨Ƭ�е������Ƿ���ȷ
void BuzzerRang();      //��������
void OpenDoor();        //����
void OpenLed();
void ClearBuf();        //recv_buf��������
void Delay(int m,int n);//��ʱ����
void WDTFunction();

unsigned char ReadEEPROM(unsigned char Haddr,unsigned char Laddr);             //��EEPROM��ز�������
void ProgramEEPROM(unsigned char Haddr,unsigned char Laddr,unsigned char da);
void EraseEEPROM(unsigned char Haddr,unsigned char Laddr);
void ReadCardSnFromEppromToPC();
void WriteCardSnToEeprom();
void EraseSectorOfEpprom();
bool EppromHandle();
void ReadOneByteFromEpprom();
void WriteOneByteToEpprom();
/*--------------------------------------------*/


/*----------------����ȫ�ֱ���-----------------*/
#define max_num 20              //��ϵͳ����У�����Ƶģ��ʱ���ص����ݳ������Ϊ 0x12 + 0x1��������֡����ͷ��
bool find_card;                 //���ⲿ�ж�0����ʱ����find_cardֵ����1����ʾ�п�������Ƶ������Ƭ������Ѱ��ָ��
unsigned char recv_buf[max_num];//��Ƭ�����ڽ�����Ƶģ�鷢�����ݵĻ������
bool recv_aa;                   //�ڴ����жϺ�����ʹ�ã�ָʾ���ڵ�ǰ���յ����ݵ�ǰһ���ֽ��Ƿ���0xaa
unsigned recv_num;              //�ڴ����жϺ�����ʹ�ã�ָʾ���ڵ�ǰ���յ����ݵ��ֽ���������������ͷ0xaa��0xbb
error recv_command_success_flag;//�ڴ����жϺ�����ʹ�ã�ָʾ�����Ƿ�ɹ�������Ƶģ�鷢��������
bool led_flag;
unsigned int tf1_num;           //��ʱ��1�жϴ���,���жϴ����ﵽ45��(��ʱ3s)������Ƶģ�鷢�ʹ�led�Ƶ�ָ��
unsigned int tf0_num;           //��ʱ��0�жϴ�������ʱԼ300ms�����ڴ������ݽ��յ���ʱ��
bool tf0_flag;                  //���ڿ���main������ʱ300ms
unsigned short index;           //����ϵͳ�û��е�����
unsigned char user_number=0;    //����
/*-------------------------------------------*/
