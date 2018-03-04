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
/*-----------------ÀàĞÍ¶¨Òå--------------------*/
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



/*----------------Òı½Å¶¨Òå--------------------*/
sbit Speaker=P2^7;       //¿ØÖÆ·äÃùÆ÷
sbit Relay=P1^4;         //¿ØÖÆ¼ÌµçÆ÷
sbit Led=P1^2;           //¿ØÖÆLedµÆ
sfr WDT=0xe1;            //¿´ÃÅ¹·¿ØÖÆÆ÷

sfr ISP_DATA=0xe2;       //EEPROMÏà¹Ø¼Ä´æÆ÷
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;
/*--------------------------------------------*/


/*---------------º¯ÊıÔ¤¶¨Òå--------------------*/
void SystemInit();      //ÏµÍ³³õÊ¼»¯
void BaudRateSetup();   //ÉèÖÃ²¨ÌØÂÊ
void SerialPortSetup(); //ÉèÖÃ´®¿Ú
void INT0Setup();       //ÉèÖÃÍâ²¿ÖĞ¶Ï0
void Tf0AndTf1Setup();  //¶¨Ê±Æ÷0ºÍ¶¨Ê±Æ÷1ÉèÖÃ
void IpSetup();         //ÖĞ¶ÏÓÅÏÈ¼¶ÉèÖÃ
void SetLedOn();        //´ò¿ªÉäÆµÄ£¿éµÄLedµÆ
void SetLedOff();       //¹Ø±ÕÉäÆµÄ£¿éµÄLedµÆ
void SearchCard();      //ÏòÉäÆµÄ£¿é·¢ËÍÑ°¿¨Ö¸Áî
error MatchCardSN();    //¼ìÑéÉäÆµÄ£¿é·¢»ØÀ´µÄ¿¨ĞòÁĞºÅÔÚµ±Ç°ÏµÍ³ÖĞÊÇ·ñ´æÔÚ
void SearchCardData();  //ÏòÉäÆµÄ£¿é·¢ËÍ¶Á¿¨Æ¬EPPROMÖĞµÄÊı¾İ
error MatchCardData();  //Ğ£Ñé¿¨Æ¬ÖĞµÄÊı¾İÊÇ·ñÕıÈ·
void BuzzerRang();      //·äÃÛÆ÷Ïì
void OpenDoor();        //¿ªÃÅ
void OpenLed();
void ClearBuf();        //recv_buf»º´æÇåÁã
void Delay(int m,int n);//ÑÓÊ±º¯Êı
void WDTFunction();

unsigned char ReadEEPROM(unsigned char Haddr,unsigned char Laddr);             //ÓëEEPROMÏà¹Ø²Ù×÷º¯Êı
void ProgramEEPROM(unsigned char Haddr,unsigned char Laddr,unsigned char da);
void EraseEEPROM(unsigned char Haddr,unsigned char Laddr);
void ReadCardSnFromEppromToPC();
void WriteCardSnToEeprom();
void EraseSectorOfEpprom();
bool EppromHandle();
void ReadOneByteFromEpprom();
void WriteOneByteToEpprom();
/*--------------------------------------------*/


/*----------------¶¨ÒåÈ«¾Ö±äÁ¿-----------------*/
#define max_num 20              //´ËÏµÍ³Éè¼ÆÖĞ£¬¶ÁÉäÆµÄ£¿éÊ±·µ»ØµÄÊı¾İ³¤¶È×î´óÎª 0x12 + 0x1£¨²»°üº¬Ö¡ÃüÁîÍ·£©
bool find_card;                 //ÔÚÍâ²¿ÖĞ¶Ï0·¢ÉúÊ±ÉèÖÃfind_cardÖµµÈÓÚ1£¬±íÊ¾ÓĞ¿¨½øÈëÉäÆµÇø£¬µ¥Æ¬»ú·¢ËÍÑ°¿¨Ö¸Áî
unsigned char recv_buf[max_num];//µ¥Æ¬»ú´®¿Ú½ÓÊÕÉäÆµÄ£¿é·¢À´Êı¾İµÄ»º´æÇøİ
bool recv_aa;                   //ÔÚ´®¿ÚÖĞ¶Ïº¯ÊıÖĞÊ¹ÓÃ£¬Ö¸Ê¾´®¿Úµ±Ç°½ÓÊÕµÄÊı¾İµÄÇ°Ò»¸ö×Ö½ÚÊÇ·ñÊÇ0xaa
unsigned recv_num;              //ÔÚ´®¿ÚÖĞ¶Ïº¯ÊıÖĞÊ¹ÓÃ£¬Ö¸Ê¾´®¿Úµ±Ç°½ÓÊÕµÄÊı¾İµÄ×Ö½ÚÊı£¬²»°üÀ¨ÃüÁîÍ·0xaa¡¢0xbb
error recv_command_success_flag;//ÔÚ´®¿ÚÖĞ¶Ïº¯ÊıÖĞÊ¹ÓÃ£¬Ö¸Ê¾´®¿ÚÊÇ·ñ³É¹¦½ÓÊÕÉäÆµÄ£¿é·¢À´µÄÃüÁî
bool led_flag;
unsigned int tf1_num;           //¶¨Ê±Æ÷1ÖĞ¶Ï´ÎÊı,µ±ÖĞ¶Ï´ÎÊı´ïµ½45´Î(¶¨Ê±3s)£¬ÏòÉäÆµÄ£¿é·¢ËÍ´ò¿ªledµÆµÄÖ¸Áî
unsigned int tf0_num;           //¶¨Ê±Æ÷0ÖĞ¶Ï´ÎÊı£¬¶¨Ê±Ô¼300ms£¬ÓÃÓÚ´®¿ÚÊı¾İ½ÓÊÕµÄÑÓÊ±¡£
bool tf0_flag;                  //ÓÃÓÚ¿ØÖÆmainº¯ÊıÑÓÊ±300ms
unsigned short index;           //¿¨ÔÚÏµÍ³ÓÃ»§ÖĞµÄË÷Òı
unsigned char user_number=0;    //ÈËÊı
/*-------------------------------------------*/
