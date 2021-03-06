#include "reg52.h"
/*-----------------类型定义--------------------*/
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



/*----------------引脚定义--------------------*/
sbit Speaker=P2^7;       //控制蜂鸣器
sbit Relay=P1^4;         //控制继电器
sbit Led=P1^2;           //控制Led灯
sfr WDT=0xe1;            //看门狗控制器

sfr ISP_DATA=0xe2;       //EEPROM相关寄存器
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;
/*--------------------------------------------*/


/*---------------函数预定义--------------------*/
void SystemInit();      //系统初始化
void BaudRateSetup();   //设置波特率
void SerialPortSetup(); //设置串口
void INT0Setup();       //设置外部中断0
void Tf0AndTf1Setup();  //定时器0和定时器1设置
void IpSetup();         //中断优先级设置
void SetLedOn();        //打开射频模块的Led灯
void SetLedOff();       //关闭射频模块的Led灯
void SearchCard();      //向射频模块发送寻卡指令
error MatchCardSN();    //检验射频模块发回来的卡序列号在当前系统中是否存在
void SearchCardData();  //向射频模块发送读卡片EPPROM中的数据
error MatchCardData();  //校验卡片中的数据是否正确
void BuzzerRang();      //蜂蜜器响
void OpenDoor();        //开门
void OpenLed();
void ClearBuf();        //recv_buf缓存清零
void Delay(int m,int n);//延时函数
void WDTFunction();

unsigned char ReadEEPROM(unsigned char Haddr,unsigned char Laddr);             //与EEPROM相关操作函数
void ProgramEEPROM(unsigned char Haddr,unsigned char Laddr,unsigned char da);
void EraseEEPROM(unsigned char Haddr,unsigned char Laddr);
void ReadCardSnFromEppromToPC();
void WriteCardSnToEeprom();
void EraseSectorOfEpprom();
bool EppromHandle();
void ReadOneByteFromEpprom();
void WriteOneByteToEpprom();
/*--------------------------------------------*/


/*----------------定义全局变量-----------------*/
#define max_num 20              //此系统设计中，读射频模块时返回的数据长度最大为 0x12 + 0x1（不包含帧命令头）
bool find_card;                 //在外部中断0发生时设置find_card值等于1，表示有卡进入射频区，单片机发送寻卡指令
unsigned char recv_buf[max_num];//单片机串口接收射频模块发来数据的缓存区�
bool recv_aa;                   //在串口中断函数中使用，指示串口当前接收的数据的前一个字节是否是0xaa
unsigned recv_num;              //在串口中断函数中使用，指示串口当前接收的数据的字节数，不包括命令头0xaa、0xbb
error recv_command_success_flag;//在串口中断函数中使用，指示串口是否成功接收射频模块发来的命令
bool led_flag;
unsigned int tf1_num;           //定时器1中断次数,当中断次数达到45次(定时3s)，向射频模块发送打开led灯的指令
unsigned int tf0_num;           //定时器0中断次数，定时约300ms，用于串口数据接收的延时。
bool tf0_flag;                  //用于控制main函数延时300ms
unsigned short index;           //卡在系统用户中的索引
unsigned char user_number=0;    //人数
/*-------------------------------------------*/
