//*****************************************************   
//*     FineName£º    Main.c                          *
//*     Created:      2015.1.1                        * 
//*     Last Change:  2015.1.15                        *
//*     Author:       FanChangFu                      *         
//*     Compiler:     KEIL C51 uVision4.0             *
//*     CPU:          STC89C52RC                      *
//*     Description:  DoorSystems                     *     				
//*     OSC use 12MHz crystal.                        *
//*****************************************************

#include "Main.h"

/*----------------Ö÷º¯Êı------------------------------*/
void main()
{
    SystemInit();                     //ÏµÍ³³õÊ¼»¯
		user_number=ReadEEPROM(0x26,0x00);//¶ÁÏµÍ³ÓÃ»§Êı
		WDTFunction();                    //Î¹¹·
		while(1)
		{
		   
			 if(find_card==TRUE)                        //Èç¹ûÓĞ¿¨½øÈëÉäÆµÄ£¿éÇøÓò£¬×öÏÂÃæ´¦Àí
			 {
			    ET1=0;                                  //½ûÖ¹¶¨Ê±Æ÷1ÖĞ¶Ï£¬±ÜÃâ¸ÉÈÅ             
					SearchCardData();                       //ÏòÉäÆµÄ£¿é·¢ËÍ¶ÁÈ¡¿¨Æ¬EEPROMÖ¸Áî			
					TR0=1;                                  //Æô¶¯¶¨Ê±Æ÷1£¨¶¨Ê±Æ÷1¶¨Ê±Ô¼300ms£©
					while( tf0_flag==FALSE);                //Ò»Ö±whileÑ­»·£¬µÈ´ı300ms£¨300msºó£¬¶¨Ê±Æ÷1ÖĞ¶Ï´¦Àíº¯ÊıÖĞ»áÉèÖÃtf0_flag=TRUE)£»ÑÓÊ±300msÄ¿µÄÊÇµÈ´ı´®¿Ú½ÓÊÕÍêÉäÆµÄ£¿é·¢»ØÀ´µÄÊı¾İ¡£
					tf0_flag=FALSE;                         //tf0_flagÖØĞÂ±ê¼ÇÎªFALSE
					if(recv_command_success_flag==SUCCESS)  //ÈçºÎÕıÈ·½ÓÊÕµ½ÉäÆµÄ£¿é·¢»ØÀ´µÄÊı¾İ£¨¿¨ĞòÁĞºÅ),×öÏÂÃæ´¦Àí¡£
					{					   
						 if(MatchCardData()==SUCCESS)         //Êı¾İÆ¥Åä
					   {						 
								 SearchCard();                    //ÏòÉäÆµÄ£¿é·¢ËÍÑ°¿¨Ö¸Áî
								 TR0=1;                  
					       while( tf0_flag==FALSE);
					       tf0_flag=FALSE;
								 if(recv_command_success_flag==SUCCESS)
								 {								 
										if(MatchCardSN()==SUCCESS)   //Æ¥Åä¿¨ĞòÁĞºÅ
								    {
					             OpenDoor();               //¿ªÃÅ
								    }
								 }
					   }	 
			    }
					find_card=FALSE;                       //find_cardÖØĞÂ±ê¼ÇÎªFALSE
					ET1=1;                                 //ÖØĞÂ¿ªÆô¶¨Ê±Æ÷1ÖĞ¶Ï
			 }
		}
}
/*-----------------------------------------------------*/


/*-------------------------------------------------  ÏµÍ³³õÊ¼»¯ÉèÖÃ-------------------------------------------------------------*/
/*---ÏµÍ³³õÊ¼»¯º¯Êı---*/
void SystemInit()
{
    BaudRateSetup();   //ÉèÖÃ²¨ÌØÂÊ
    SerialPortSetup(); //ÉèÖÃ´®¿Ú
    INT0Setup();       //ÉèÖÃÍâ²¿ÖĞ¶Ï0
		IpSetup();         //ÉèÖÃÖĞ¶ÏÓÅÏÈ¼¶
		Tf0AndTf1Setup();  //ÉèÖÃ¶¨Ê±Æ÷0¡¢¶¨Ê±Æ÷1
		
		find_card=FALSE;//È«¾Ö±äÁ¿³õÊ¼»¯
		recv_aa=FALSE;
		led_flag=FALSE;
		recv_num=0;
		recv_command_success_flag=FAIL;
		tf1_num=0;
		tf0_num=0;
		tf0_flag=FALSE;
		
		TR2=1;//Æô¶¯²¨ÌØÂÊ·¢ÉúÆ÷
		TR1=1;//Æô¶¯¶¨Ê±Æ÷1
		ES=1; //Æô¶¯´®¿ÚÖĞ¶Ï
	  EA=1; //¿ª·ÅËùÓĞÖĞ¶Ï
} 


/*---ÉèÖÃ²¨ÌØÂÊ---*/
  //¶¨Ê±Æ÷2×÷Îª²¨ÌØÂÊ·¢ÉúÆ÷Ê±£¬²¨ÌØÂÊ¼ÆËã¹«Ê½£º²¨ÌØÂÊ=Õñµ´Æ÷ÆµÂÊ/32[65536-(RCAP2H*256+RCAP2L)]
  //¶¨Ê±Æ÷2×÷Îª²¨ÌØÂÊ·¢ÉúÆ÷Ê±£¬»á×Ô¶¯ÖØ×°RCAP2H/RCAP2Lµ½TH2/TL2
void BaudRateSetup()
{
    RCLK=1;     //ÉèÖÃ¶¨Ê±Æ÷T2×÷Îª²¨ÌØÂÊ·¢ÉúÆ÷
	  TCLK=1;
		TH2=255;    //²¨ÌØÂÊÎª19200,¶¨Ê±Æ÷³õÖµÒªÉèÎª255*256+236
		TL2=236;
	  RCAP2H=255; //ÉèÖÃ×Ô¶¯ÖØ×°Öµ£¬Óë³õÖµÏàÍ¬
	  RCAP2L=236;
		C_T2=0;     //¶¨Ê±Æ÷2²ÉÓÃ¶¨Ê±·½Ê½£¨C_T2=1ÊÇ¶ÔÍâ²¿Òı½ÅÂö³å¼ÆÊı)
}


/*---ÉèÖÃ´®¿Ú---*/
void SerialPortSetup()
{
    SM0=0; //´®¿Ú¹¤×÷·½Ê½:10Î»Òì²½ÊÕ·¢(8Î»Êı¾İÎ»£¬Ò»Î»¿ªÊ¼Î»£¬Ò»Î»Í£Ö¹Î»)
	  SM1=1;
		REN=1;
	  ES=1;  //ÔÊĞí´®ĞĞ¿ÚÖĞ¶Ï£¬´®¿ÚÊı¾İµÄÊÕ·¢²ÉÓÃÖĞ¶Ï·½Ê½
}


/*---Íâ²¿ÖĞ¶Ï0ÉèÖÃ---*/		
void INT0Setup()
{
    IT0=1; //ÏÂ½µÑØ´¥·¢
    EX0=1; //ÔÊĞíÍâ²¿ÖĞ¶Ï0ÖĞ¶Ï
}


/*---¶¨Ê±Æ÷0ºÍ¶¨Ê±Æ÷1ÉèÖÃ---*/
  //¶¨Ê±Æ÷1¶¨Ê±3s£¨ĞèÒª¶¨Ê±Æ÷ÖĞ¶Ï45´Î£©£¬¶¨Ê±Æ÷0¶¨Ê±250ºÁÃë£¨ĞèÒª¶¨Ê±Æ÷ÖĞ¶Ï4´Î)
void Tf0AndTf1Setup()
{
   TMOD=0x11;//¶¨Ê±Æ÷0ºÍ¶¨Ê±Æ÷1¶¼Ê¹ÓÃ¹¤×÷Ä£Ê½1£º16Î»¼ÆÊı£¬×î´ó¼ÆÊı´ÎÊı65536
	 TH0=0;    //¶¨Ê±Æ÷0³õÊ¼¼ÆÊıÖµÉèÎª0
	 TL0=0;
	 TH1=0;    //¶¨Ê±Æ÷1³õÊ¼¼ÆÊıÖµÉèÎª1
	 TL1=0;
	 ET0=1;    //ÔÊĞí¶¨Ê±Æ÷0¡¢¶¨Ê±Æ÷1ÖĞ¶Ï
	 ET1=1; 
}


/*---ÖĞ¶ÏÓÅÏÈ¼¶ÉèÖÃ---*/
  //´®¿ÚÖĞ¶Ï¡¢Íâ²¿ÖĞ¶ÏÓÅÏÈ¼¶±ğÉèÎª1£¬¶¨Ê±Æ÷0¡¢¶¨Ê±Æ÷1ÖĞ¶ÏÓÅÏÈ¼¶±ğÉèÖÃÎª0
void IpSetup()
{
    PS=1;
		PX0=1;
		PT0=0;
		PT1=0;
} 
/*------------------------------------------------------------------------------------------------------------------------------*/





/*---------------------------------------------------ÖĞ¶Ï´¦Àíº¯Êı----------------------------------------------------------------*/
/*---¶¨Ê±Æ÷1ÖĞ¶Ï´¦Àíº¯Êı---*/
  //ÔÚ¸Ãº¯ÊıÖĞ¿ØÖÆÉäÆµÄ£¿éµÄLedµÆµÄÉÁË¸£¬Ô¼3sÉÁË¸Ò»´Î
  //¶¨Ê±Æ÷ÖĞ¶Ï45´ÎµÄÊ±¼äÔ¼Îª3s
Tf1_interrupt() interrupt 3
{
   WDTFunction();//Î¹¹·
   tf1_num=tf1_num+1;  //¶¨Ê±Æ÷Ã¿ÖĞ¶ÏÒ»´Îºó¼Ó1
	 if(tf1_num>45)
	 {
	    TR1=0;          //ÏÈÍ£Ö¹¶¨Ê±Æ÷1¹¤×÷
      SetLedOn();     //µãÁÁLedµÆ
	    Delay(1000,10); //ÑÓÊ±Ò»¶ÎÊ±¼ä
	    SetLedOff();    //¹Ø±ÕLedµÆ
			TR1=1;          //ÖØĞÂÆô¶¯¶¨Ê±Æ÷1
			tf1_num=0;      //tf1_numÇåÁã£¬¿ªÊ¼ÏÂÒ»ÂÖ¼ÆÊı
	 }
	 TH1=0;   //¶¨Ê±Æ÷ÖĞ¶Ïºó£¬ÖØĞÂÉè¶¨ÏÂÒ»´Î¼ÆÊ±µÄ³õÖµ±
	 TL1=0;
}


/*---¶¨Ê±Æ÷0ÖĞ¶Ï´¦Àíº¯Êı---*/
  //ÔÚmainº¯ÊıÖĞµ÷ÓÃSearchCard()ºÍSearchCardData()º¯ÊıºóÆô¶¯¶¨Ê±Æ÷0£¬ÑÓÊ±Ô¼300ms£¬µÈ´ı½ÓÊÕÍêÉäÆµÄ£¿é·¢¹ıÀ´µÄÊı¾İ¡£
  //¶¨Ê±Æ÷ÖĞ¶Ï4´ÎµÄÊ±¼äÔ¼Îª300ms
Tf0_interrupt() interrupt 1
{
    WDTFunction();//Î¹¹·
    tf0_num=tf0_num+1;  //¶¨Ê±Æ÷Ã¿ÖĞ¶ÏÒ»´Îºó¼Ó1
		if(tf0_num>=4)
		{
		   TR0=0;           //¹Ø±Õ¶¨Ê±Æ÷0£¨¶¨Ê±Æ÷0ÔÚmainº¯Êıµ÷ÓÃSearchCard()ºÍSearchCardData()º¯ÊıºóÆô¶¯£©
			 tf0_flag=TRUE;   //±ê¼ÇÉèÎªTRUE¸æËßmainº¯ÊıÊı¾İ½ÓÊÕÍê±Ï£¬·ñÔòmainº¯Êı»áÔÚwhile( tf0_flag==FALSE)Óï¾äÖĞ²»¶ÏÑ­»·
			 tf0_num=0;       //ÇåÁã
		}
}		 
	
	
/*---Íâ²¿ÖĞ¶Ï0ÖĞ¶Ï´¦Àíº¯Êı---*/
  //µ±ÓĞ¿¨¿¿½üÉäÆµÄ£¿éÊ±£¬SIGÒı½Å³öÏÖµÍµçÆ½£¬´¥·¢µ¥Æ¬»úµÄÍâ²¿ÖĞ¶Ï0·¢ÉúÖĞ¶Ï
Int0_interrupt() interrupt 0
{
    EA=0;          //Îª±ÜÃâ¸ÉÈÅ£¬ÏÈ¹Ø±Õ×ÜÖĞ¶Ï
    find_card=TRUE;//±ê¼ÇÓĞ¿¨¿¿½üÉäÆµÄ£¿é
		EA=1;          //ÖØĞÂ¿ªÖĞ¶Ï
}


/*---´®¿ÚÖĞ¶Ï´¦Àíº¯Êı---*/
  //ÔÚ¸Ãº¯ÊıÖĞÍê³É´®¿ÚÊı¾İµÄ½ÓÊÕ£¨´®¿ÚÊı¾İ½ÓÊÕ²ÉÓÃÖĞ¶Ï·½Ê½£©
  //¸ù¾İYHY502C_v2.5_CN.pfdÎÄµµÖĞµÄÉäÆµÄ£¿é·¢ËÍÊı¾İµÄ¸ñÊ½£¬Èôµ±Ç°µ¥Æ¬»úÊÕµ½µÄ×Ö½ÚÎª0xaa,½ô½Ó×ÅÊÕµ½µÄ×Ö½ÚÖ»ÓĞÁ½ÖÖÇé¿ö£º0xbb(±íÊ¾0xaaºÍ0xbbÊÇÖ¡ÃüÁîÍ·),0x00(±íÊ¾0xaaÊÇÊı¾İ£¬²»ÊÇÖ¡ÃüÁîÍ·)
SerialPort_interrupt() interrupt 4
{
    unsigned char recv_byte;  //¸Ã±äÁ¿ÓÃÓÚÔİÊ±±£´æ´®¿Ú½ÓÊÕµÄÒ»¸ö×Ö½ÚÊı¾İÚ
		unsigned char check_sum;  //Ò»Ö¡Êı¾İ½ÓÊÕÍê±Ïºó£¬¸Ã±äÁ¿ÓÃÓÚÒì»òĞ£Ñé
		int i;
		EA=0;     //Îª·ÀÖ¹¸ÉÈÅ£¬ÏÈ¹Ø±Õ×ÜÖĞ¶Ï  
		if(RI==1) //ÅĞ¶ÏÊÇ·ñÊÇ´®¿ÚÊÕµ½Êı¾İ¶øÒı·¢´®¿ÚÖĞ¶Ï£¬ÊÇµÄ»°ÔÚÕâÀïÍê³ÉÊı¾İµÄ½ÓÊÕ¹¤×÷
		{
		   recv_byte=SBUF;//¿½±´´®¿Ú½ÓÊÕ»º´æÖĞµÄÊı¾İ
			 RI=0;          //ÇåÁã£¬ÓÃÓÚÏÂÒ»´ÎÅĞ¶Ï
		   if(recv_aa==TRUE)   //ÅĞ¶ÏÉÏÒ»´Î½ÓÊÕµÄÊı¾İÊÇ·ñÊÇ0xaa
			 {
			    if(recv_byte==0xbb)  //ÉÏ´Î½ÓÊÕµÄ0xaaÊÇÖ¡ÃüÁîÍ·
					{
					    recv_aa=FALSE;   //±ê¼ÇFALSE,ÏÂÒ»´ÎÅĞ¶ÏÊ±ÓÃÓÚÖ¸Ê¾Ç°Ò»´Î½ÓÊÕµÄ²»ÊÇ0xaaÏ
							recv_num=0;      //»º´ærecv_buf²»±£´æÃüÁîÍ·0xaa0xbb,recv_numÖµÉèÎª0Ïàµ±Çå³ıµôÖ®Ç°±£´æµÄ0xaa0xbb
			    }
			    else if(recv_byte==0x00) //ÉÏ´Î½ÓÊÕµÄ0xaaÊÇÊı¾İ£¨0x00ÊÇÎªÁËÇø±ğÖ¡ÃüÁîÍ·0xaa0xbb¶øÌí¼Ó½øÈ¥£¬²»ÊÇÎÒÃÇĞèÒªµÄÊı¾İ)
			    {  
					    recv_aa=FALSE;   //±ê¼ÇFALSE,ÏÂÒ»´ÎÅĞ¶ÏÊ±ÓÃÓÚÖ¸Ê¾Ç°Ò»´Î½ÓÊÕµÄ²»ÊÇ0xaa
			    }
					else                 //ÆäËûÒâÍâÇé¿ö£¬Õı³£Çé¿öÏÂÖ»»áÊÇ0xbbºÍ0x00
					{
					    recv_aa=FALSE;   //±ê¼ÇFALSE,ÏÂÒ»´ÎÅĞ¶ÏÊ±ÓÃÓÚÖ¸Ê¾Ç°Ò»´Î½ÓÊÕµÄ²»ÊÇ0xaa
					}
			 }
			 else   //ÉÏÒ»´Î½ÓÊÕµÄÊı¾İ²»ÊÇ0xaa
			 {
			    if(recv_byte==0xaa)  //ÅĞ¶Ïµ±Ç°½ÓÊÕµÄÊı¾İÊÇ·ñÊÇ0xaa£¬ÈôÊÇÔò½øĞĞ±ê¼Ç
					{
					   recv_aa=TRUE;
					}
					recv_buf[recv_num]=recv_byte;//½«½ÓÊÕµ½µÄÊı¾İ±£´æµ½»º´ærecv_buf
					recv_num=recv_num+1;         //Ã¿½ÓÊÕ±£´æÒ»¸ö×Ö½ÚÊı¾İ£¬recv_numÔö1
					if(recv_num>recv_buf[0])     //recv_buf±£´æµÄÊÇÊı¾İÖ¡µÄ³¤¶È×Ö£¬µ±recv_num´óÓÚ³¤¶È×ÖÊ±£¬Ïàµ±ÓÚµ±Ç°½ÓÊÕµÄÊı¾İÊÇÖ¡µÄ×îºóÒ»¸ö×Ö½ÚÊı¾İ£¬¼´Ò»Ö¡Êı¾İ½ÓÊÕÍê±Ïİ
			    {
					    check_sum=0;
							for(i=0;i<recv_buf[0]+1;i++) //¶ÔÒ»Ö¡Êı¾İ½øĞĞÒì»òĞ£Ñé
							{
							   check_sum=check_sum^recv_buf[i];
							}
							if(check_sum==0)            //Ö¡µÄ×îºóÒ»¸ö×Ö½ÚÎª¼ìÑéÂë£¬ÉÏÃæ½«Ğ£ÑéÂëÒ»Æğ½øĞĞÒì»òÔËËã£¬Èô½ÓÊÕµÄÊı¾İÃ»ÓĞ´íÎó£¬ÄÇcheck_sumµÃÖµÒ»¶¨ÊÇ0
							{
							   if(EppromHandle()==FALSE)
								 {
							      recv_command_success_flag=SUCCESS; //±ê¼Ç³É¹¦½ÓÊÕÒ»Ö¡Êı¾İ£¬¹©mainº¯Êı×öÅĞ¶ÏÊ¹ÓÃ¡£
								 }
							}
							recv_num=0;
							recv_aa=FALSE;
					}
					if(recv_num>=max_num)   //ÅĞ¶Ï½ÓÊÕµÄÊı¾İ×Ö½ÚÊıÊÇ·ñ´óÓÚ»º´ærecv_buf£¬·ÀÖ¹ÄÚ´æÒç³öÚ
					{
					   recv_num=0;
						 recv_aa=FALSE;
					}
			 }	
			 
		   
		}
		if(TI==1) //±íÊ¾´®¿Ú·¢ËÍÊı¾İÒı·¢´®¿ÚÖĞ¶Ï,ÔÚ±¾ÏµÍ³ÖĞ²»Ê¹ÓÃÖĞ¶Ï·½Ê½·¢ËÍÊı¾İ£¬Ê¹ÓÃ²éÑ¯·½Ê½·¢ËÍÊı¾İ
		{
		   TI=0;
		}
		EA=1; //ÖØĞÂ¿ªÖĞ¶Ï    
}
/*---------------------------------------------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------ÏòÉäÆµÄ£¿é·¢ËÍÖ¸Áî--------------------------------------------------------------------*/
/*---ÉäÆµÄ£¿é·¢ËÍ´ò¿ªLEDµÆÖ¸Áî---*/
  //ÉäÆµÄ£¿éµÄOUT1Òı½ÅÓëLedÕı¼«ÏàÁ¬
void SetLedOn()
{
   unsigned char command_set_out1_0[6]={0xaa,0xbb,0x03,0x16,0x00,0x15}; //Ö¸Áî£¬¿ØÖÆÉäÆµÄ£¿éµÄOUT1Òı½ÅÊä³ö¸ßµçÆ½?
	 int i;
	 ES=0;  //Ê¹ÓÃ²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İÊ±£¬Òª¹Ø±Õ´®¿ÚÖĞ¶Ï£¬·ñÔò·¢ËÍ²»ÕıÈ·
   for(i=0;i<6;i++) //²éÑ¯·½Ê½·¢ËÍÊı¾İ
	 {
	     TI=0;
	     SBUF=command_set_out1_0[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;
}


/*---ÏòÉäÆµÄ£¿é·¢ËÍ¹Ø±ÕLEDµÆÖ¸Áî---*/
void SetLedOff()
{
   unsigned char command_set_out1_1[6]={0xaa,0xbb,0x03,0x16,0x01,0x14}; //Ö¸Áî£¬¿ØÖÆÉäÆµÄ£¿éµÄOUT1Òı½ÅÊä³öµÍµçÆ½
	 int i;
	 ES=0;                                                                //Ê¹ÓÃ²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İÊ±£¬Òª¹Ø±Õ´®¿ÚÖĞ¶Ï£¬·ñÔò·¢ËÍ²»ÕıÈ·
   for(i=0;i<6;i++)                                                     //²éÑ¯·½Ê½·¢ËÍÊı¾İ
	 {
	     TI=0;
	     SBUF=command_set_out1_1[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;
}


/*---ÏòÉäÆµÄ£¿éµÄ·¢ËÍÑ°¿¨Ö¸Áî---*/
void SearchCard()
{
   int i;
   unsigned char command_search_card[5]={0xaa,0xbb,0x02,0x20,0x22};//Ñ°¿¨Ö¸Áî
	 recv_command_success_flag=FAIL;                                 //·¢ËÍÖ¸ÁîÖ®Ç°ÏÈÉèÖÃFAIL,µ±´®¿ÚÖĞ¶Ï´¦Àíº¯ÊıÖĞÕıÈ·½ÓÊÕÒ»Ö¡Êı¾İºóÔÙÉèÖÃÎªSUCCESS,¹©mainº¯Êı×öÅĞ¶ÏÊ¹ÓÃ
	 ClearBuf();                                                     //Í¨¹ı´®¿ÚÏòÉäÆµÄ£¿é·¢ËÍÖ¸Áîºó»áÓëÊı¾İ·µ»Ø£¬ÔÚÕâÀïÌáÇ°¶Ô»º´ærecv_bufÇåÁã
	 ES=0;                                                           //Ê¹ÓÃ²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İÊ±£¬Òª¹Ø±Õ´®¿ÚÖĞ¶Ï£¬·ñÔò·¢ËÍ²»ÕıÈ·
	 for(i=0;i<5;i++)                                                //²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İ
	 {
	     TI=0;
	     SBUF=command_search_card[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;                                                          //·¢ËÍÍêºóÖØĞÂ¿ªÆô´®¿ÚÖĞ¶Ï
}


/*---ÏòÉäÆµÄ£¿é·¢ËÍ¶Á¿¨Æ¬EEPROMÊı¾İ---*/
  //¶Á¿¨Æ¬EEPROMÖĞµÄµÚ10,14,18,22¿éÖĞµÄÊı¾İ£¬¿éÖĞ±£´æµÄÊı¾İ xx xx xx xx xx xx xx fb 10 25 52 xx xx xx xx xx (xx¿ÉÎªÈÎÒâÊı¾İ£¬fb 10 25 52²ÅÊÇÓÃÀ´×öÅĞ¶Ï)
	//1ºÅÃÅ¶ÔÓ¦µÚ10¿é£¬2ºÅÃÅ¶ÔÓ¦µÚ14¿é£¬3ºÅÃÅ¶ÔÓ¦µÚ18¿é£¬4ºÅÃÅ¶ÔÓ¦µÚ22¿é
void SearchCardData()
{
   int i;
	 //unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x0a, 0xff, 0xff, 0xcc, 0xff, 0x10, 0x26, 0x24};  //1ºÅÃÅ
   //unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x0e, 0xff, 0xff, 0xdd, 0xff, 0x10, 0x26, 0x31};  //2ºÅÃÅ
	   unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x12, 0xff, 0xff, 0xee, 0xff, 0x10, 0x26, 0x1e};  //3ºÅÃÅ
	 //unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x0a, 0xff, 0xff, 0xff, 0xff, 0x10, 0x26, 0x17};  //4ºÅÃÅ
	 
	 recv_command_success_flag=FAIL;           //·¢ËÍÖ¸ÁîÖ®Ç°ÏÈÉèÖÃFAIL,µ±´®¿ÚÖĞ¶Ï´¦Àíº¯ÊıÖĞÕıÈ·½ÓÊÕÒ»Ö¡Êı¾İºóÔÙÉèÖÃÎªSUCCESS,¹©mainº¯Êı×öÅĞ¶ÏÊ¹ÓÃ
	 ClearBuf();                               //Í¨¹ı´®¿ÚÏòÉäÆµÄ£¿é·¢ËÍÖ¸Áîºó»áÓëÊı¾İ·µ»Ø£¬ÔÚÕâÀïÌáÇ°¶Ô»º´ærecv_bufÇåÁã
	 ES=0;                                     //Ê¹ÓÃ²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İÊ±£¬Òª¹Ø±Õ´®¿ÚÖĞ¶Ï£¬·ñÔò·¢ËÍ²»ÕıÈ·
	 for(i=0;i<13;i++)                         //²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İ
	 {
	     TI=0;
	     SBUF=command_search_card_data[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;                                    //·¢ËÍÍêºóÖØĞÂ¿ªÆô´®¿ÚÖĞ¶Ï
}
/*----------------------------------------------------------------------------------------------------------------------------------*/




/*----------------------------------------------------¶ÔÉäÆµÄ£¿é·¢»ØÀ´µÄÊı¾İ½øĞĞĞ£Ñé--------------------------------------------------*/
/*---¼ìÑéÉäÆµÄ£¿é·¢»ØÀ´µÄ¿¨ĞòÁĞºÅÔÚµ±Ç°ÏµÍ³ÖĞÊÇ·ñ´æÔÚ---*/
error MatchCardSN()
{
	 int i;
	 unsigned char cardsn[4];
	 unsigned char Haddr;
	 unsigned char Laddr;
	 if(index>=user_number)  //Èç¹ûÓÃ»§ËùÒÔºÅ´óÓÚÏµÍ³ÓÃ»§Êı£¬ËµÃ÷¸ÃÓÃ»§²»ÊÇÏµÍ³µÄÓÃ»§£¬Ö±½ÓÍË³ö
	 {
	     return FAIL;
	 }
	 
	 //´ÓEEPROMÖĞ¶Á¿¨ĞòÁĞºÅİ
	 for(i=0;i<4;i++)
	 {
	    Haddr=0x20+(index*4+i)/256;
			Laddr=0x00+(index*4+i)%256;
	    cardsn[i]=ReadEEPROM(Haddr,Laddr);
	 }
	 //Æ¥Åä¿¨ĞòÁĞºÅ
	 if((recv_buf[2]==cardsn[0]) && (recv_buf[3]==cardsn[1]) && (recv_buf[4]==cardsn[2]) && (recv_buf[5]==cardsn[3]))
	 {
	     return SUCCESS;
	 }
	 else
	 {
	     return FAIL;
	 }  
}

/*---Ğ£Ñé¿¨Æ¬ÖĞµÄÊı¾İÊÇ·ñÕıÈ·---*/
  //ÈôÕıÈ·¶Áµ½EEPROMÖĞµÄÊı¾İ£¬recv_buf[0:18]±£´æµÄÊı¾İÊÇ£º ³¤¶È×Ö ÃüÁî×Ö xx xx xx xx xx xx xx fb 10 25 52 xx xx xx xx xx
error MatchCardData()
{
	 if((recv_buf[9]==0xfb)&&(recv_buf[10]==0x10)&&(recv_buf[11]==0x25)&&(recv_buf[12]==0x52)) //Ğ£Ñé¿¨Æ¬ÖĞµÄÊı¾İÊÇ·ñÕıÈ·£¬ÕıÈ··µ»ØSUCCESS,´íÎó·µ»ØFAIL
	 {
	    index=recv_buf[2]*256+recv_buf[3];
			if(index>=user_number)
			{
			    return FAIL;
			}
			else
			{
	       return SUCCESS;
		  }
	 }
	 else
	 {
	    return FAIL;
	 }
}
/*-------------------------------------------------------------------------------------------------------------------------------*/




/*-----------------------------------------ÉäÆµ¿¨Æ¬µÄĞòÁĞºÅºÍEEPROMÊı¾İĞ£ÑéÍ¨¹ıºóµÄ´¦Àíº¯Êı-----------------------------------------*/
/*---·äÃùÆ÷Ïì---*/
  //µÍµçÆ½Çı¶¯
void BuzzerRang()
{
   Speaker=0;
	 Delay(1000,10);
	 Speaker=1;
	 
}


/*--¿ØÖÆ¼ÌµçÆ÷¿ªÃÅ---*/
//µÍµçÆ½Çı¶¯
void OpenDoor()
{
   Relay=0;
 //Speaker=0;
	 Led=0;
	 Delay(8000,10);
	 Relay=1;
//Speaker=1;
	 Led=1;
}


/*---´ò¿ªLedµÆ---*/
void OpenLed()
{
   Led=0;
	 Delay(1000,10);
	 Led=1;
}
/*-------------------------------------------------------------------------------------------------------------------------------*/

 
	 
	 
/*-------------------------------------------------------EEPROM²Ù×÷--------------------------------------------------------------*/
/*----¶ÁEEPROM----*/
unsigned char ReadEEPROM(unsigned char Haddr,unsigned char Laddr)
{
    char i=0;
		unsigned char da;
    ISP_ADDRH=Haddr; //ËÍµØÖ·
    ISP_ADDRL=Laddr; 
    EA=0;            //¹ØÖĞ¶Ï
    ISP_CONTR=0x81;  //ÉèÖÃµÈ´ıÊ±¼ä,ÔÊĞíISP/IAP²Ù×÷
		ISP_CMD=0x01;    //ËÍ¶Á×Ö½ÚÃüÁî
		ISP_TRIG=0x46;   //´¥·¢ÃüÁî
		ISP_TRIG=0xb9;
		i=0;             //ÑÓÊ±
		i=0;
		da=ISP_DATA;     //È¡Êı¾İ
		
		ISP_CONTR=0x00; //³öÓÚ°²È«¿¼ÂÇ£¬·ÀÖ¹ISP/IAPÎó²Ù×÷
		ISP_CMD=0x00;
		ISP_TRIG=0x00;
		ISP_ADDRH=0x00;
		ISP_ADDRL=0x00;
		
		EA=1;            //ÖØĞÂ¿ªÖĞ¶Ï
		return da;       //·µ»ØÊı¾İ
}


/*---±à³ÌEEPROM---*/
void ProgramEEPROM(unsigned char Haddr,unsigned char Laddr,unsigned char da)
{
   ISP_DATA=da;    //ËÍÊı¾İ
	 ISP_ADDRH=Haddr;//ËÍµØÖ·
	 ISP_ADDRL=Laddr;
	 EA=0;           //¹ØÖĞ¶Ï
	 ISP_CONTR=0x81; //ÉèÖÃµÈ´ıÊ±¼ä,ÔÊĞíISP/IAP²Ù×÷
	 ISP_CMD=0x02;   //ËÍ±à³ÌÃüÁî
	 ISP_TRIG=0x46;   //´¥·¢ÃüÁî
	 ISP_TRIG=0xb9;
	 
	 ISP_CONTR=0x00;  //³öÓÚ°²È«¿¼ÂÇ£¬·ÀÖ¹ISP/IAPÎó²Ù×÷
	 ISP_CMD=0x00;
	 ISP_TRIG=0x00;
	 ISP_ADDRH=0x00;
	 ISP_ADDRL=0x00;
	 
	 EA=1;            //ÖØĞÂ¿ªÖĞ¶Ï
    
}


/*---²Á³ıEEPROM---*/
void EraseEEPROM(unsigned char Haddr,unsigned char Laddr)
{
   
   ISP_ADDRH=Haddr; //ËÍµØÖ·
	 ISP_ADDRL=Laddr;
 //EA=0;            //¹ØÖĞ¶Ï
	 ISP_CONTR=0x81;  //ÉèÖÃµÈ´ıÊ±¼ä,ÔÊĞíISP/IAP²Ù×÷
	 ISP_CMD=0x03;    //ËÍ±à³ÌÃüÁî
	 ISP_TRIG=0x46;   //´¥·¢ÃüÁî
	 ISP_TRIG=0xb9;
	 
	 ISP_CONTR=0x00; //³öÓÚ°²È«¿¼ÂÇ£¬·ÀÖ¹ISP/IAPÎó²Ù×÷
	 ISP_CMD=0x00;
	 ISP_TRIG=0x00;
	 ISP_ADDRH=0x00;
	 ISP_ADDRL=0x00;
 //EA=1;           //ÖØĞÂ¿ªÖĞ¶Ï
	 
}

/*---´ÓEPPROMÖĞ¶ÁÒ»¸ö¿¨µÄĞòÁĞºÅ,²¢Í¨¹ı´®¿ÚËÍ»ØPC---*/
void ReadCardSnFromEppromToPC()
{
   int i;
   unsigned char cmd[9]={0xaa,0xbb,0x06,0x50,0x00,0x00,0x00,0x00,0x00};
	 unsigned char Haddr;
	 unsigned char Laddr;
	 unsigned char checksum=0x00;
	 unsigned short idx;
	 
	 idx=recv_buf[2]*256+recv_buf[3];//»ñÈ¡¿¨µÄË÷Òı
	 for(i=0;i<4;i++)                //´ÓEEPROMÖĞ¶Á¿¨ĞòÁĞºÅ,¹¹Ôì»ØËÍÖ¸Áî
	 {
	    Haddr=0x20+(idx*4+i)/256;
			Laddr=0x00+(idx*4+i)%256;
	    cmd[i+4]=ReadEEPROM(Haddr,Laddr);
	 }
	 for(i=0;i<6;i++)
	 {
	    checksum=checksum^cmd[i+2];
	 }
	 cmd[8]=checksum;
	 
	 //Í¨¹ı´®¿Ú»ØËÍ¸øPC
	 ES=0;            //Ê¹ÓÃ²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İÊ±£¬Òª¹Ø±Õ´®¿ÚÖĞ¶Ï£¬·ñÔò·¢ËÍ²»ÕıÈ·
	 for(i=0;i<9;i++) //²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İ
	 {
	     TI=0;
	     SBUF=cmd[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;           //·¢ËÍÍêºóÖØĞÂ¿ªÆô´®¿ÚÖĞ¶Ï 
}

/*---ÍùEEPROMÖĞĞ´Ò»¸ö¿¨µÄĞòÁĞºÅ---*/
void WriteCardSnToEeprom()
{
   unsigned char cmd[5]={0xaa,0xbb,0x02,0x52,0x50}; //»ØËÍÖ¸Áî
   unsigned char Haddr;
	 unsigned char Laddr;
	 int i;
	 unsigned short idx;
	 
	 idx=recv_buf[6]*256+recv_buf[7];//¹¹Ôì¿¨µÄË÷Òı
   for(i=0;i<4;i++)                //ÍùEEPROMÖĞÌí¼ÓÒ»¸ö¿¨µÄĞòÁĞºÅ
	 {
	    Haddr=0x20+(idx*4+i)/256;
			Laddr=0x00+(idx*4+i)%256;
	    ProgramEEPROM(Haddr,Laddr,recv_buf[i+2]);
	 }
	 //ÏòPC»ØËÍÖ¸Áî
	 ES=0;            //Ê¹ÓÃ²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İÊ±£¬Òª¹Ø±Õ´®¿ÚÖĞ¶Ï£¬·ñÔò·¢ËÍ²»ÕıÈ·
   for(i=0;i<5;i++) //²éÑ¯·½Ê½·¢ËÍÊı¾İ
	 {
	    TI=0;
	    SBUF=cmd[i];
			while(TI==0);
	 }
	 TI=0;
	 ES=1;           //·¢ËÍÍêºóÖØĞÂ¿ªÆô´®¿ÚÖĞ¶Ï 
}
   
	 
/*---²Á³ıEERPROMµÄÒ»¸öÉÈÇø---*/
void EraseSectorOfEpprom()
{
   unsigned char cmd[5]={0xaa,0xbb,0x02,0x54,0x56};//»ØËÍ¸øPCµÄÖ¸Áî
	 int i;
	 unsigned char SectorOfNumber=recv_buf[2];       //»ñÈ¡Òª²Á³ıµÄÉÈÇøºÅ
   if(SectorOfNumber>=1&&SectorOfNumber<=4)
	 {
	    //²Á³ıÉÈÇø
	    switch(SectorOfNumber)
			{
			   case 1:
				      EraseEEPROM(0x20,0x00);             //²Á³ıµÚÒ»¸öÉÈÇø
							break;
				 case 2:
				      EraseEEPROM(0x22,0x00);             //²Á³ıµÚ¶ş¸öÉÈÇø
							break;
				 case 3:
				      EraseEEPROM(0x24,0x00);             //²Á³ıµÚÈı¸öÉÈÇø
							break;
				 case 4:
				      EraseEEPROM(0x26,0x00);             //²Á³ıµÚËÄ¸öÉÈÇø
							break;
			}
			
			//Ïòpc»ØËÍÖ¸Áî
			ES=0;            //Ê¹ÓÃ²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İÊ±£¬Òª¹Ø±Õ´®¿ÚÖĞ¶Ï£¬·ñÔò·¢ËÍ²»ÕıÈ·
      for(i=0;i<5;i++) //²éÑ¯·½Ê½·¢ËÍÊı¾İ
	    {
	       TI=0;
	       SBUF=cmd[i];
			   while(TI==0);
	    }
	    TI=0;
	    ES=1;
	}
}


/*---ÏòEEPROMÖĞĞ´Ò»¸ö×Ö½ÚÊı¾İ---*/
void WriteOneByteToEpprom()
{
   unsigned char i;
   unsigned char cmd[5]={0xaa,0xbb,0x02,0x5a,0x58}; //»ØËÍÖ¸Áî
   unsigned char Haddr;
	 unsigned char Laddr;
	 unsigned char da;
	 Haddr=recv_buf[2];
	 Laddr=recv_buf[3];
	 da=recv_buf[4];
	 ProgramEEPROM(Haddr,Laddr,da);
	 //ÏòPC·¢ËÍ»ØËÍÖ¸Áî
	 ES=0;             //Ê¹ÓÃ²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İÊ±£¬Òª¹Ø±Õ´®¿ÚÖĞ¶Ï£¬·ñÔò·¢ËÍ²»ÕıÈ·
   for(i=0;i<5;i++)  //²éÑ¯·½Ê½·¢ËÍÊı¾İ
	 {
	     TI=0;
	     SBUF=cmd[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;
}


/*´ÓEEPROMÖĞ¶ÁÒ»¸ö×Ö½ÚÊı¾İ---*/
void ReadOneByteFromEpprom()
{
    unsigned char i;
    unsigned char cmd[6]={0xaa ,0xbb,0x03,0x58,0x00,0x00};
		unsigned char checksum=0x00;
		unsigned char Haddr;
		unsigned char Laddr;
		unsigned char da;
		Haddr=recv_buf[2];
		Laddr=recv_buf[3];
		da=ReadEEPROM(Haddr,Laddr);
		cmd[4]=da;
		
		for(i=0;i<3;i++)
	  {
	     checksum=checksum^cmd[i+2];
	  }
	  cmd[5]=checksum;
		//»ØËÍÖ¸Áî
	  ES=0;            //Ê¹ÓÃ²éÑ¯·½Ê½·¢ËÍ´®¿ÚÊı¾İÊ±£¬Òª¹Ø±Õ´®¿ÚÖĞ¶Ï£¬·ñÔò·¢ËÍ²»ÕıÈ·
    for(i=0;i<6;i++) //²éÑ¯·½Ê½·¢ËÍÊı¾İ
	  {
	     TI=0;
	     SBUF=cmd[i];
			 while(TI==0);
	  }
	  TI=0;
	  ES=1;
}


/*---Õë¶ÔEEPROMµÄ²Ù×÷ÇëÇó´¦Àíº¯Êı---*/
bool EppromHandle()
{
   unsigned char CmdWord=recv_buf[1]; //»ñÈ¡Ö¸ÁîµÄÃüÁî×Ö
	 if(CmdWord==0x50)                  //¶Á¿¨EEPROMÖĞµÄÒ»¸ö¿¨ĞòÁĞºÅ
	 {
	    ReadCardSnFromEppromToPC();
	    return TRUE;
	 }
	 else if(CmdWord==0x52)             //ÏòEEPROMÖĞĞ´Ò»¸ö¿¨µÄĞòÁĞºÅ
	 {
	    WriteCardSnToEeprom();         
	    return TRUE;
	 }
	 else if(CmdWord==0x54)            //²Á³ıEEPROMµÄÒ»¸öÉÈÇø
	 {
	   EraseSectorOfEpprom();
	   return TRUE;
	 }
	 else if(CmdWord==0x58)            //¶ÁEEPROMÖĞµÄÒ»¸ö×Ö½Ú
	 {
	   ReadOneByteFromEpprom();
		 return TRUE;
	 }
	 else if(CmdWord==0x5a)
	 {
	    WriteOneByteToEpprom();        //ÏòEEPROMÖĞ¶ÁÒ»¸ö×Ö½Ú
			return TRUE;
	 }
	 else
	 {
	    return FALSE;
	 }
}
/*-------------------------------------------------------------------------------------------------------------------------------*/




	 
/*-------------------------------------------------------------ÆäËû--------------------------------------------------------------*/
/*---¶Ô»º´ærecv_bufÇåÁã---*/
  //Çå³ıµôÉÏ´Î½ÓÊÕµÄÊı¾İ
void ClearBuf()
{
    int i;
		for(i=0;i<max_num;i++)
		{
		    recv_buf[i]=0x0;
		}
}

/*---ÑÓÊ±º¯Êı---*/
void Delay(int m,int n)
{
   int i,j;
   for(i=0;i<m;i++)
	 {
	    WDTFunction();//Î¹¹·
	    for(j=0;j<n;j++){}
	 }
}  

/*---¿´ÃÅ¹·º¯Êı---*/
void WDTFunction()
{
   WDT=0x3e;
}
/*------------------------------------------------------------------------------------------------------------------------------*/

