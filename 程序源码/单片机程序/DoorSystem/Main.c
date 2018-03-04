//*****************************************************   
//*     FineName��    Main.c                          *
//*     Created:      2015.1.1                        * 
//*     Last Change:  2015.1.15                        *
//*     Author:       FanChangFu                      *         
//*     Compiler:     KEIL C51 uVision4.0             *
//*     CPU:          STC89C52RC                      *
//*     Description:  DoorSystems                     *     				
//*     OSC use 12MHz crystal.                        *
//*****************************************************

#include "Main.h"

/*----------------������------------------------------*/
void main()
{
    SystemInit();                     //ϵͳ��ʼ��
		user_number=ReadEEPROM(0x26,0x00);//��ϵͳ�û���
		WDTFunction();                    //ι��
		while(1)
		{
		   
			 if(find_card==TRUE)                        //����п�������Ƶģ�����������洦��
			 {
			    ET1=0;                                  //��ֹ��ʱ��1�жϣ��������             
					SearchCardData();                       //����Ƶģ�鷢�Ͷ�ȡ��ƬEEPROMָ��			
					TR0=1;                                  //������ʱ��1����ʱ��1��ʱԼ300ms��
					while( tf0_flag==FALSE);                //һֱwhileѭ�����ȴ�300ms��300ms�󣬶�ʱ��1�жϴ������л�����tf0_flag=TRUE)����ʱ300msĿ���ǵȴ����ڽ�������Ƶģ�鷢���������ݡ�
					tf0_flag=FALSE;                         //tf0_flag���±��ΪFALSE
					if(recv_command_success_flag==SUCCESS)  //�����ȷ���յ���Ƶģ�鷢���������ݣ������к�),�����洦��
					{					   
						 if(MatchCardData()==SUCCESS)         //����ƥ��
					   {						 
								 SearchCard();                    //����Ƶģ�鷢��Ѱ��ָ��
								 TR0=1;                  
					       while( tf0_flag==FALSE);
					       tf0_flag=FALSE;
								 if(recv_command_success_flag==SUCCESS)
								 {								 
										if(MatchCardSN()==SUCCESS)   //ƥ�俨���к�
								    {
					             OpenDoor();               //����
								    }
								 }
					   }	 
			    }
					find_card=FALSE;                       //find_card���±��ΪFALSE
					ET1=1;                                 //���¿�����ʱ��1�ж�
			 }
		}
}
/*-----------------------------------------------------*/


/*-------------------------------------------------  ϵͳ��ʼ������-------------------------------------------------------------*/
/*---ϵͳ��ʼ������---*/
void SystemInit()
{
    BaudRateSetup();   //���ò�����
    SerialPortSetup(); //���ô���
    INT0Setup();       //�����ⲿ�ж�0
		IpSetup();         //�����ж����ȼ�
		Tf0AndTf1Setup();  //���ö�ʱ��0����ʱ��1
		
		find_card=FALSE;//ȫ�ֱ�����ʼ��
		recv_aa=FALSE;
		led_flag=FALSE;
		recv_num=0;
		recv_command_success_flag=FAIL;
		tf1_num=0;
		tf0_num=0;
		tf0_flag=FALSE;
		
		TR2=1;//���������ʷ�����
		TR1=1;//������ʱ��1
		ES=1; //���������ж�
	  EA=1; //���������ж�
} 


/*---���ò�����---*/
  //��ʱ��2��Ϊ�����ʷ�����ʱ�������ʼ��㹫ʽ��������=����Ƶ��/32[65536-(RCAP2H*256+RCAP2L)]
  //��ʱ��2��Ϊ�����ʷ�����ʱ�����Զ���װRCAP2H/RCAP2L��TH2/TL2
void BaudRateSetup()
{
    RCLK=1;     //���ö�ʱ��T2��Ϊ�����ʷ�����
	  TCLK=1;
		TH2=255;    //������Ϊ19200,��ʱ����ֵҪ��Ϊ255*256+236
		TL2=236;
	  RCAP2H=255; //�����Զ���װֵ�����ֵ��ͬ
	  RCAP2L=236;
		C_T2=0;     //��ʱ��2���ö�ʱ��ʽ��C_T2=1�Ƕ��ⲿ�����������)
}


/*---���ô���---*/
void SerialPortSetup()
{
    SM0=0; //���ڹ�����ʽ:10λ�첽�շ�(8λ����λ��һλ��ʼλ��һλֹͣλ)
	  SM1=1;
		REN=1;
	  ES=1;  //�����п��жϣ��������ݵ��շ������жϷ�ʽ
}


/*---�ⲿ�ж�0����---*/		
void INT0Setup()
{
    IT0=1; //�½��ش���
    EX0=1; //�����ⲿ�ж�0�ж�
}


/*---��ʱ��0�Ͷ�ʱ��1����---*/
  //��ʱ��1��ʱ3s����Ҫ��ʱ���ж�45�Σ�����ʱ��0��ʱ250���루��Ҫ��ʱ���ж�4��)
void Tf0AndTf1Setup()
{
   TMOD=0x11;//��ʱ��0�Ͷ�ʱ��1��ʹ�ù���ģʽ1��16λ����������������65536
	 TH0=0;    //��ʱ��0��ʼ����ֵ��Ϊ0
	 TL0=0;
	 TH1=0;    //��ʱ��1��ʼ����ֵ��Ϊ1
	 TL1=0;
	 ET0=1;    //����ʱ��0����ʱ��1�ж�
	 ET1=1; 
}


/*---�ж����ȼ�����---*/
  //�����жϡ��ⲿ�ж����ȼ�����Ϊ1����ʱ��0����ʱ��1�ж����ȼ�������Ϊ0
void IpSetup()
{
    PS=1;
		PX0=1;
		PT0=0;
		PT1=0;
} 
/*------------------------------------------------------------------------------------------------------------------------------*/





/*---------------------------------------------------�жϴ�����----------------------------------------------------------------*/
/*---��ʱ��1�жϴ�����---*/
  //�ڸú����п�����Ƶģ���Led�Ƶ���˸��Լ3s��˸һ��
  //��ʱ���ж�45�ε�ʱ��ԼΪ3s
Tf1_interrupt() interrupt 3
{
   WDTFunction();//ι��
   tf1_num=tf1_num+1;  //��ʱ��ÿ�ж�һ�κ��1
	 if(tf1_num>45)
	 {
	    TR1=0;          //��ֹͣ��ʱ��1����
      SetLedOn();     //����Led��
	    Delay(1000,10); //��ʱһ��ʱ��
	    SetLedOff();    //�ر�Led��
			TR1=1;          //����������ʱ��1
			tf1_num=0;      //tf1_num���㣬��ʼ��һ�ּ���
	 }
	 TH1=0;   //��ʱ���жϺ������趨��һ�μ�ʱ�ĳ�ֵ�
	 TL1=0;
}


/*---��ʱ��0�жϴ�����---*/
  //��main�����е���SearchCard()��SearchCardData()������������ʱ��0����ʱԼ300ms���ȴ���������Ƶģ�鷢���������ݡ�
  //��ʱ���ж�4�ε�ʱ��ԼΪ300ms
Tf0_interrupt() interrupt 1
{
    WDTFunction();//ι��
    tf0_num=tf0_num+1;  //��ʱ��ÿ�ж�һ�κ��1
		if(tf0_num>=4)
		{
		   TR0=0;           //�رն�ʱ��0����ʱ��0��main��������SearchCard()��SearchCardData()������������
			 tf0_flag=TRUE;   //�����ΪTRUE����main�������ݽ�����ϣ�����main��������while( tf0_flag==FALSE)����в���ѭ��
			 tf0_num=0;       //����
		}
}		 
	
	
/*---�ⲿ�ж�0�жϴ�����---*/
  //���п�������Ƶģ��ʱ��SIG���ų��ֵ͵�ƽ��������Ƭ�����ⲿ�ж�0�����ж�
Int0_interrupt() interrupt 0
{
    EA=0;          //Ϊ������ţ��ȹر����ж�
    find_card=TRUE;//����п�������Ƶģ��
		EA=1;          //���¿��ж�
}


/*---�����жϴ�����---*/
  //�ڸú�������ɴ������ݵĽ��գ��������ݽ��ղ����жϷ�ʽ��
  //����YHY502C_v2.5_CN.pfd�ĵ��е���Ƶģ�鷢�����ݵĸ�ʽ������ǰ��Ƭ���յ����ֽ�Ϊ0xaa,�������յ����ֽ�ֻ�����������0xbb(��ʾ0xaa��0xbb��֡����ͷ),0x00(��ʾ0xaa�����ݣ�����֡����ͷ)
SerialPort_interrupt() interrupt 4
{
    unsigned char recv_byte;  //�ñ���������ʱ���洮�ڽ��յ�һ���ֽ������
		unsigned char check_sum;  //һ֡���ݽ�����Ϻ󣬸ñ����������У��
		int i;
		EA=0;     //Ϊ��ֹ���ţ��ȹر����ж�  
		if(RI==1) //�ж��Ƿ��Ǵ����յ����ݶ����������жϣ��ǵĻ�������������ݵĽ��չ���
		{
		   recv_byte=SBUF;//�������ڽ��ջ����е�����
			 RI=0;          //���㣬������һ���ж�
		   if(recv_aa==TRUE)   //�ж���һ�ν��յ������Ƿ���0xaa
			 {
			    if(recv_byte==0xbb)  //�ϴν��յ�0xaa��֡����ͷ
					{
					    recv_aa=FALSE;   //���FALSE,��һ���ж�ʱ����ָʾǰһ�ν��յĲ���0xaa�
							recv_num=0;      //����recv_buf����������ͷ0xaa0xbb,recv_numֵ��Ϊ0�൱�����֮ǰ�����0xaa0xbb
			    }
			    else if(recv_byte==0x00) //�ϴν��յ�0xaa�����ݣ�0x00��Ϊ������֡����ͷ0xaa0xbb����ӽ�ȥ������������Ҫ������)
			    {  
					    recv_aa=FALSE;   //���FALSE,��һ���ж�ʱ����ָʾǰһ�ν��յĲ���0xaa
			    }
					else                 //����������������������ֻ����0xbb��0x00
					{
					    recv_aa=FALSE;   //���FALSE,��һ���ж�ʱ����ָʾǰһ�ν��յĲ���0xaa
					}
			 }
			 else   //��һ�ν��յ����ݲ���0xaa
			 {
			    if(recv_byte==0xaa)  //�жϵ�ǰ���յ������Ƿ���0xaa����������б��
					{
					   recv_aa=TRUE;
					}
					recv_buf[recv_num]=recv_byte;//�����յ������ݱ��浽����recv_buf
					recv_num=recv_num+1;         //ÿ���ձ���һ���ֽ����ݣ�recv_num��1
					if(recv_num>recv_buf[0])     //recv_buf�����������֡�ĳ����֣���recv_num���ڳ�����ʱ���൱�ڵ�ǰ���յ�������֡�����һ���ֽ����ݣ���һ֡���ݽ�������
			    {
					    check_sum=0;
							for(i=0;i<recv_buf[0]+1;i++) //��һ֡���ݽ������У��
							{
							   check_sum=check_sum^recv_buf[i];
							}
							if(check_sum==0)            //֡�����һ���ֽ�Ϊ�����룬���潫У����һ�����������㣬�����յ�����û�д�����check_sum��ֵһ����0
							{
							   if(EppromHandle()==FALSE)
								 {
							      recv_command_success_flag=SUCCESS; //��ǳɹ�����һ֡���ݣ���main�������ж�ʹ�á�
								 }
							}
							recv_num=0;
							recv_aa=FALSE;
					}
					if(recv_num>=max_num)   //�жϽ��յ������ֽ����Ƿ���ڻ���recv_buf����ֹ�ڴ�����
					{
					   recv_num=0;
						 recv_aa=FALSE;
					}
			 }	
			 
		   
		}
		if(TI==1) //��ʾ���ڷ����������������ж�,�ڱ�ϵͳ�в�ʹ���жϷ�ʽ�������ݣ�ʹ�ò�ѯ��ʽ��������
		{
		   TI=0;
		}
		EA=1; //���¿��ж�    
}
/*---------------------------------------------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------����Ƶģ�鷢��ָ��--------------------------------------------------------------------*/
/*---��Ƶģ�鷢�ʹ�LED��ָ��---*/
  //��Ƶģ���OUT1������Led��������
void SetLedOn()
{
   unsigned char command_set_out1_0[6]={0xaa,0xbb,0x03,0x16,0x00,0x15}; //ָ�������Ƶģ���OUT1��������ߵ�ƽ?
	 int i;
	 ES=0;  //ʹ�ò�ѯ��ʽ���ʹ�������ʱ��Ҫ�رմ����жϣ������Ͳ���ȷ
   for(i=0;i<6;i++) //��ѯ��ʽ��������
	 {
	     TI=0;
	     SBUF=command_set_out1_0[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;
}


/*---����Ƶģ�鷢�͹ر�LED��ָ��---*/
void SetLedOff()
{
   unsigned char command_set_out1_1[6]={0xaa,0xbb,0x03,0x16,0x01,0x14}; //ָ�������Ƶģ���OUT1��������͵�ƽ
	 int i;
	 ES=0;                                                                //ʹ�ò�ѯ��ʽ���ʹ�������ʱ��Ҫ�رմ����жϣ������Ͳ���ȷ
   for(i=0;i<6;i++)                                                     //��ѯ��ʽ��������
	 {
	     TI=0;
	     SBUF=command_set_out1_1[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;
}


/*---����Ƶģ��ķ���Ѱ��ָ��---*/
void SearchCard()
{
   int i;
   unsigned char command_search_card[5]={0xaa,0xbb,0x02,0x20,0x22};//Ѱ��ָ��
	 recv_command_success_flag=FAIL;                                 //����ָ��֮ǰ������FAIL,�������жϴ���������ȷ����һ֡���ݺ�������ΪSUCCESS,��main�������ж�ʹ��
	 ClearBuf();                                                     //ͨ����������Ƶģ�鷢��ָ���������ݷ��أ���������ǰ�Ի���recv_buf����
	 ES=0;                                                           //ʹ�ò�ѯ��ʽ���ʹ�������ʱ��Ҫ�رմ����жϣ������Ͳ���ȷ
	 for(i=0;i<5;i++)                                                //��ѯ��ʽ���ʹ�������
	 {
	     TI=0;
	     SBUF=command_search_card[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;                                                          //����������¿��������ж�
}


/*---����Ƶģ�鷢�Ͷ���ƬEEPROM����---*/
  //����ƬEEPROM�еĵ�10,14,18,22���е����ݣ����б�������� xx xx xx xx xx xx xx fb 10 25 52 xx xx xx xx xx (xx��Ϊ�������ݣ�fb 10 25 52�����������ж�)
	//1���Ŷ�Ӧ��10�飬2���Ŷ�Ӧ��14�飬3���Ŷ�Ӧ��18�飬4���Ŷ�Ӧ��22��
void SearchCardData()
{
   int i;
	 //unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x0a, 0xff, 0xff, 0xcc, 0xff, 0x10, 0x26, 0x24};  //1����
   //unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x0e, 0xff, 0xff, 0xdd, 0xff, 0x10, 0x26, 0x31};  //2����
	   unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x12, 0xff, 0xff, 0xee, 0xff, 0x10, 0x26, 0x1e};  //3����
	 //unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x0a, 0xff, 0xff, 0xff, 0xff, 0x10, 0x26, 0x17};  //4����
	 
	 recv_command_success_flag=FAIL;           //����ָ��֮ǰ������FAIL,�������жϴ���������ȷ����һ֡���ݺ�������ΪSUCCESS,��main�������ж�ʹ��
	 ClearBuf();                               //ͨ����������Ƶģ�鷢��ָ���������ݷ��أ���������ǰ�Ի���recv_buf����
	 ES=0;                                     //ʹ�ò�ѯ��ʽ���ʹ�������ʱ��Ҫ�رմ����жϣ������Ͳ���ȷ
	 for(i=0;i<13;i++)                         //��ѯ��ʽ���ʹ�������
	 {
	     TI=0;
	     SBUF=command_search_card_data[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;                                    //����������¿��������ж�
}
/*----------------------------------------------------------------------------------------------------------------------------------*/




/*----------------------------------------------------����Ƶģ�鷢���������ݽ���У��--------------------------------------------------*/
/*---������Ƶģ�鷢�����Ŀ����к��ڵ�ǰϵͳ���Ƿ����---*/
error MatchCardSN()
{
	 int i;
	 unsigned char cardsn[4];
	 unsigned char Haddr;
	 unsigned char Laddr;
	 if(index>=user_number)  //����û����ԺŴ���ϵͳ�û�����˵�����û�����ϵͳ���û���ֱ���˳�
	 {
	     return FAIL;
	 }
	 
	 //��EEPROM�ж������к��
	 for(i=0;i<4;i++)
	 {
	    Haddr=0x20+(index*4+i)/256;
			Laddr=0x00+(index*4+i)%256;
	    cardsn[i]=ReadEEPROM(Haddr,Laddr);
	 }
	 //ƥ�俨���к�
	 if((recv_buf[2]==cardsn[0]) && (recv_buf[3]==cardsn[1]) && (recv_buf[4]==cardsn[2]) && (recv_buf[5]==cardsn[3]))
	 {
	     return SUCCESS;
	 }
	 else
	 {
	     return FAIL;
	 }  
}

/*---У�鿨Ƭ�е������Ƿ���ȷ---*/
  //����ȷ����EEPROM�е����ݣ�recv_buf[0:18]����������ǣ� ������ ������ xx xx xx xx xx xx xx fb 10 25 52 xx xx xx xx xx
error MatchCardData()
{
	 if((recv_buf[9]==0xfb)&&(recv_buf[10]==0x10)&&(recv_buf[11]==0x25)&&(recv_buf[12]==0x52)) //У�鿨Ƭ�е������Ƿ���ȷ����ȷ����SUCCESS,���󷵻�FAIL
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




/*-----------------------------------------��Ƶ��Ƭ�����кź�EEPROM����У��ͨ����Ĵ�����-----------------------------------------*/
/*---��������---*/
  //�͵�ƽ����
void BuzzerRang()
{
   Speaker=0;
	 Delay(1000,10);
	 Speaker=1;
	 
}


/*--���Ƽ̵�������---*/
//�͵�ƽ����
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


/*---��Led��---*/
void OpenLed()
{
   Led=0;
	 Delay(1000,10);
	 Led=1;
}
/*-------------------------------------------------------------------------------------------------------------------------------*/

 
	 
	 
/*-------------------------------------------------------EEPROM����--------------------------------------------------------------*/
/*----��EEPROM----*/
unsigned char ReadEEPROM(unsigned char Haddr,unsigned char Laddr)
{
    char i=0;
		unsigned char da;
    ISP_ADDRH=Haddr; //�͵�ַ
    ISP_ADDRL=Laddr; 
    EA=0;            //���ж�
    ISP_CONTR=0x81;  //���õȴ�ʱ��,����ISP/IAP����
		ISP_CMD=0x01;    //�Ͷ��ֽ�����
		ISP_TRIG=0x46;   //��������
		ISP_TRIG=0xb9;
		i=0;             //��ʱ
		i=0;
		da=ISP_DATA;     //ȡ����
		
		ISP_CONTR=0x00; //���ڰ�ȫ���ǣ���ֹISP/IAP�����
		ISP_CMD=0x00;
		ISP_TRIG=0x00;
		ISP_ADDRH=0x00;
		ISP_ADDRL=0x00;
		
		EA=1;            //���¿��ж�
		return da;       //��������
}


/*---���EEPROM---*/
void ProgramEEPROM(unsigned char Haddr,unsigned char Laddr,unsigned char da)
{
   ISP_DATA=da;    //������
	 ISP_ADDRH=Haddr;//�͵�ַ
	 ISP_ADDRL=Laddr;
	 EA=0;           //���ж�
	 ISP_CONTR=0x81; //���õȴ�ʱ��,����ISP/IAP����
	 ISP_CMD=0x02;   //�ͱ������
	 ISP_TRIG=0x46;   //��������
	 ISP_TRIG=0xb9;
	 
	 ISP_CONTR=0x00;  //���ڰ�ȫ���ǣ���ֹISP/IAP�����
	 ISP_CMD=0x00;
	 ISP_TRIG=0x00;
	 ISP_ADDRH=0x00;
	 ISP_ADDRL=0x00;
	 
	 EA=1;            //���¿��ж�
    
}


/*---����EEPROM---*/
void EraseEEPROM(unsigned char Haddr,unsigned char Laddr)
{
   
   ISP_ADDRH=Haddr; //�͵�ַ
	 ISP_ADDRL=Laddr;
 //EA=0;            //���ж�
	 ISP_CONTR=0x81;  //���õȴ�ʱ��,����ISP/IAP����
	 ISP_CMD=0x03;    //�ͱ������
	 ISP_TRIG=0x46;   //��������
	 ISP_TRIG=0xb9;
	 
	 ISP_CONTR=0x00; //���ڰ�ȫ���ǣ���ֹISP/IAP�����
	 ISP_CMD=0x00;
	 ISP_TRIG=0x00;
	 ISP_ADDRH=0x00;
	 ISP_ADDRL=0x00;
 //EA=1;           //���¿��ж�
	 
}

/*---��EPPROM�ж�һ���������к�,��ͨ�������ͻ�PC---*/
void ReadCardSnFromEppromToPC()
{
   int i;
   unsigned char cmd[9]={0xaa,0xbb,0x06,0x50,0x00,0x00,0x00,0x00,0x00};
	 unsigned char Haddr;
	 unsigned char Laddr;
	 unsigned char checksum=0x00;
	 unsigned short idx;
	 
	 idx=recv_buf[2]*256+recv_buf[3];//��ȡ��������
	 for(i=0;i<4;i++)                //��EEPROM�ж������к�,�������ָ��
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
	 
	 //ͨ�����ڻ��͸�PC
	 ES=0;            //ʹ�ò�ѯ��ʽ���ʹ�������ʱ��Ҫ�رմ����жϣ������Ͳ���ȷ
	 for(i=0;i<9;i++) //��ѯ��ʽ���ʹ�������
	 {
	     TI=0;
	     SBUF=cmd[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;           //����������¿��������ж� 
}

/*---��EEPROM��дһ���������к�---*/
void WriteCardSnToEeprom()
{
   unsigned char cmd[5]={0xaa,0xbb,0x02,0x52,0x50}; //����ָ��
   unsigned char Haddr;
	 unsigned char Laddr;
	 int i;
	 unsigned short idx;
	 
	 idx=recv_buf[6]*256+recv_buf[7];//���쿨������
   for(i=0;i<4;i++)                //��EEPROM�����һ���������к�
	 {
	    Haddr=0x20+(idx*4+i)/256;
			Laddr=0x00+(idx*4+i)%256;
	    ProgramEEPROM(Haddr,Laddr,recv_buf[i+2]);
	 }
	 //��PC����ָ��
	 ES=0;            //ʹ�ò�ѯ��ʽ���ʹ�������ʱ��Ҫ�رմ����жϣ������Ͳ���ȷ
   for(i=0;i<5;i++) //��ѯ��ʽ��������
	 {
	    TI=0;
	    SBUF=cmd[i];
			while(TI==0);
	 }
	 TI=0;
	 ES=1;           //����������¿��������ж� 
}
   
	 
/*---����EERPROM��һ������---*/
void EraseSectorOfEpprom()
{
   unsigned char cmd[5]={0xaa,0xbb,0x02,0x54,0x56};//���͸�PC��ָ��
	 int i;
	 unsigned char SectorOfNumber=recv_buf[2];       //��ȡҪ������������
   if(SectorOfNumber>=1&&SectorOfNumber<=4)
	 {
	    //��������
	    switch(SectorOfNumber)
			{
			   case 1:
				      EraseEEPROM(0x20,0x00);             //������һ������
							break;
				 case 2:
				      EraseEEPROM(0x22,0x00);             //�����ڶ�������
							break;
				 case 3:
				      EraseEEPROM(0x24,0x00);             //��������������
							break;
				 case 4:
				      EraseEEPROM(0x26,0x00);             //�������ĸ�����
							break;
			}
			
			//��pc����ָ��
			ES=0;            //ʹ�ò�ѯ��ʽ���ʹ�������ʱ��Ҫ�رմ����жϣ������Ͳ���ȷ
      for(i=0;i<5;i++) //��ѯ��ʽ��������
	    {
	       TI=0;
	       SBUF=cmd[i];
			   while(TI==0);
	    }
	    TI=0;
	    ES=1;
	}
}


/*---��EEPROM��дһ���ֽ�����---*/
void WriteOneByteToEpprom()
{
   unsigned char i;
   unsigned char cmd[5]={0xaa,0xbb,0x02,0x5a,0x58}; //����ָ��
   unsigned char Haddr;
	 unsigned char Laddr;
	 unsigned char da;
	 Haddr=recv_buf[2];
	 Laddr=recv_buf[3];
	 da=recv_buf[4];
	 ProgramEEPROM(Haddr,Laddr,da);
	 //��PC���ͻ���ָ��
	 ES=0;             //ʹ�ò�ѯ��ʽ���ʹ�������ʱ��Ҫ�رմ����жϣ������Ͳ���ȷ
   for(i=0;i<5;i++)  //��ѯ��ʽ��������
	 {
	     TI=0;
	     SBUF=cmd[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;
}


/*��EEPROM�ж�һ���ֽ�����---*/
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
		//����ָ��
	  ES=0;            //ʹ�ò�ѯ��ʽ���ʹ�������ʱ��Ҫ�رմ����жϣ������Ͳ���ȷ
    for(i=0;i<6;i++) //��ѯ��ʽ��������
	  {
	     TI=0;
	     SBUF=cmd[i];
			 while(TI==0);
	  }
	  TI=0;
	  ES=1;
}


/*---���EEPROM�Ĳ�����������---*/
bool EppromHandle()
{
   unsigned char CmdWord=recv_buf[1]; //��ȡָ���������
	 if(CmdWord==0x50)                  //����EEPROM�е�һ�������к�
	 {
	    ReadCardSnFromEppromToPC();
	    return TRUE;
	 }
	 else if(CmdWord==0x52)             //��EEPROM��дһ���������к�
	 {
	    WriteCardSnToEeprom();         
	    return TRUE;
	 }
	 else if(CmdWord==0x54)            //����EEPROM��һ������
	 {
	   EraseSectorOfEpprom();
	   return TRUE;
	 }
	 else if(CmdWord==0x58)            //��EEPROM�е�һ���ֽ�
	 {
	   ReadOneByteFromEpprom();
		 return TRUE;
	 }
	 else if(CmdWord==0x5a)
	 {
	    WriteOneByteToEpprom();        //��EEPROM�ж�һ���ֽ�
			return TRUE;
	 }
	 else
	 {
	    return FALSE;
	 }
}
/*-------------------------------------------------------------------------------------------------------------------------------*/




	 
/*-------------------------------------------------------------����--------------------------------------------------------------*/
/*---�Ի���recv_buf����---*/
  //������ϴν��յ�����
void ClearBuf()
{
    int i;
		for(i=0;i<max_num;i++)
		{
		    recv_buf[i]=0x0;
		}
}

/*---��ʱ����---*/
void Delay(int m,int n)
{
   int i,j;
   for(i=0;i<m;i++)
	 {
	    WDTFunction();//ι��
	    for(j=0;j<n;j++){}
	 }
}  

/*---���Ź�����---*/
void WDTFunction()
{
   WDT=0x3e;
}
/*------------------------------------------------------------------------------------------------------------------------------*/

