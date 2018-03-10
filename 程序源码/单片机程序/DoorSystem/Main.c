#include "Main.h"

/*----------------主函数------------------------------*/
void main()
{
    SystemInit();                     //系统初始化
		user_number=ReadEEPROM(0x26,0x00);//读系统用户数
		WDTFunction();                    //喂狗
		while(1)
		{
		   
			 if(find_card==TRUE)                        //如果有卡进入射频模块区域，做下面处理
			 {
			    ET1=0;                                  //禁止定时器1中断，避免干扰             
					SearchCardData();                       //向射频模块发送读取卡片EEPROM指令			
					TR0=1;                                  //启动定时器1（定时器1定时约300ms）
					while( tf0_flag==FALSE);                //一直while循环，等待300ms（300ms后，定时器1中断处理函数中会设置tf0_flag=TRUE)；延时300ms目的是等待串口接收完射频模块发回来的数据。
					tf0_flag=FALSE;                         //tf0_flag重新标记为FALSE
					if(recv_command_success_flag==SUCCESS)  //如何正确接收到射频模块发回来的数据（卡序列号),做下面处理。
					{					   
						 if(MatchCardData()==SUCCESS)         //数据匹配
					   {						 
								 SearchCard();                    //向射频模块发送寻卡指令
								 TR0=1;                  
					       while( tf0_flag==FALSE);
					       tf0_flag=FALSE;
								 if(recv_command_success_flag==SUCCESS)
								 {								 
										if(MatchCardSN()==SUCCESS)   //匹配卡序列号
								    {
					             OpenDoor();               //开门
								    }
								 }
					   }	 
			    }
					find_card=FALSE;                       //find_card重新标记为FALSE
					ET1=1;                                 //重新开启定时器1中断
			 }
		}
}
/*-----------------------------------------------------*/


/*-------------------------------------------------  系统初始化设置-------------------------------------------------------------*/
/*---系统初始化函数---*/
void SystemInit()
{
    BaudRateSetup();   //设置波特率
    SerialPortSetup(); //设置串口
    INT0Setup();       //设置外部中断0
		IpSetup();         //设置中断优先级
		Tf0AndTf1Setup();  //设置定时器0、定时器1
		
		find_card=FALSE;//全局变量初始化
		recv_aa=FALSE;
		led_flag=FALSE;
		recv_num=0;
		recv_command_success_flag=FAIL;
		tf1_num=0;
		tf0_num=0;
		tf0_flag=FALSE;
		
		TR2=1;//启动波特率发生器
		TR1=1;//启动定时器1
		ES=1; //启动串口中断
	  EA=1; //开放所有中断
} 


/*---设置波特率---*/
  //定时器2作为波特率发生器时，波特率计算公式：波特率=振荡器频率/32[65536-(RCAP2H*256+RCAP2L)]
  //定时器2作为波特率发生器时，会自动重装RCAP2H/RCAP2L到TH2/TL2
void BaudRateSetup()
{
    RCLK=1;     //设置定时器T2作为波特率发生器
	  TCLK=1;
		TH2=255;    //波特率为19200,定时器初值要设为255*256+236
		TL2=236;
	  RCAP2H=255; //设置自动重装值，与初值相同
	  RCAP2L=236;
		C_T2=0;     //定时器2采用定时方式（C_T2=1是对外部引脚脉冲计数)
}


/*---设置串口---*/
void SerialPortSetup()
{
    SM0=0; //串口工作方式:10位异步收发(8位数据位，一位开始位，一位停止位)
	  SM1=1;
		REN=1;
	  ES=1;  //允许串行口中断，串口数据的收发采用中断方式
}


/*---外部中断0设置---*/		
void INT0Setup()
{
    IT0=1; //下降沿触发
    EX0=1; //允许外部中断0中断
}


/*---定时器0和定时器1设置---*/
  //定时器1定时3s（需要定时器中断45次），定时器0定时250毫秒（需要定时器中断4次)
void Tf0AndTf1Setup()
{
   TMOD=0x11;//定时器0和定时器1都使用工作模式1：16位计数，最大计数次数65536
	 TH0=0;    //定时器0初始计数值设为0
	 TL0=0;
	 TH1=0;    //定时器1初始计数值设为1
	 TL1=0;
	 ET0=1;    //允许定时器0、定时器1中断
	 ET1=1; 
}


/*---中断优先级设置---*/
  //串口中断、外部中断优先级别设为1，定时器0、定时器1中断优先级别设置为0
void IpSetup()
{
    PS=1;
		PX0=1;
		PT0=0;
		PT1=0;
} 
/*------------------------------------------------------------------------------------------------------------------------------*/





/*---------------------------------------------------中断处理函数----------------------------------------------------------------*/
/*---定时器1中断处理函数---*/
  //在该函数中控制射频模块的Led灯的闪烁，约3s闪烁一次
  //定时器中断45次的时间约为3s
Tf1_interrupt() interrupt 3
{
   WDTFunction();//喂狗
   tf1_num=tf1_num+1;  //定时器每中断一次后加1
	 if(tf1_num>45)
	 {
	    TR1=0;          //先停止定时器1工作
      SetLedOn();     //点亮Led灯
	    Delay(1000,10); //延时一段时间
	    SetLedOff();    //关闭Led灯
			TR1=1;          //重新启动定时器1
			tf1_num=0;      //tf1_num清零，开始下一轮计数
	 }
	 TH1=0;   //定时器中断后，重新设定下一次计时的初值?
	 TL1=0;
}


/*---定时器0中断处理函数---*/
  //在main函数中调用SearchCard()和SearchCardData()函数后启动定时器0，延时约300ms，等待接收完射频模块发过来的数据。
  //定时器中断4次的时间约为300ms
Tf0_interrupt() interrupt 1
{
    WDTFunction();//喂狗
    tf0_num=tf0_num+1;  //定时器每中断一次后加1
		if(tf0_num>=4)
		{
		   TR0=0;           //关闭定时器0（定时器0在main函数调用SearchCard()和SearchCardData()函数后启动）
			 tf0_flag=TRUE;   //标记设为TRUE告诉main函数数据接收完毕，否则main函数会在while( tf0_flag==FALSE)语句中不断循环
			 tf0_num=0;       //清零
		}
}		 
	
	
/*---外部中断0中断处理函数---*/
  //当有卡靠近射频模块时，SIG引脚出现低电平，触发单片机的外部中断0发生中断
Int0_interrupt() interrupt 0
{
    EA=0;          //为避免干扰，先关闭总中断
    find_card=TRUE;//标记有卡靠近射频模块
		EA=1;          //重新开中断
}


/*---串口中断处理函数---*/
  //在该函数中完成串口数据的接收（串口数据接收采用中断方式）
  //根据YHY502C_v2.5_CN.pfd文档中的射频模块发送数据的格式，若当前单片机收到的字节为0xaa,紧接着收到的字节只有两种情况：0xbb(表示0xaa和0xbb是帧命令头),0x00(表示0xaa是数据，不是帧命令头)
SerialPort_interrupt() interrupt 4
{
    unsigned char recv_byte;  //该变量用于暂时保存串口接收的一个字节数据?
		unsigned char check_sum;  //一帧数据接收完毕后，该变量用于异或校验
		int i;
		EA=0;     //为防止干扰，先关闭总中断  
		if(RI==1) //判断是否是串口收到数据而引发串口中断，是的话在这里完成数据的接收工作
		{
		   recv_byte=SBUF;//拷贝串口接收缓存中的数据
			 RI=0;          //清零，用于下一次判断
		   if(recv_aa==TRUE)   //判断上一次接收的数据是否是0xaa
			 {
			    if(recv_byte==0xbb)  //上次接收的0xaa是帧命令头
					{
					    recv_aa=FALSE;   //标记FALSE,下一次判断时用于指示前一次接收的不是0xaa?
							recv_num=0;      //缓存recv_buf不保存命令头0xaa0xbb,recv_num值设为0相当清除掉之前保存的0xaa0xbb
			    }
			    else if(recv_byte==0x00) //上次接收的0xaa是数据（0x00是为了区别帧命令头0xaa0xbb而添加进去，不是我们需要的数据)
			    {  
					    recv_aa=FALSE;   //标记FALSE,下一次判断时用于指示前一次接收的不是0xaa
			    }
					else                 //其他意外情况，正常情况下只会是0xbb和0x00
					{
					    recv_aa=FALSE;   //标记FALSE,下一次判断时用于指示前一次接收的不是0xaa
					}
			 }
			 else   //上一次接收的数据不是0xaa
			 {
			    if(recv_byte==0xaa)  //判断当前接收的数据是否是0xaa，若是则进行标记
					{
					   recv_aa=TRUE;
					}
					recv_buf[recv_num]=recv_byte;//将接收到的数据保存到缓存recv_buf
					recv_num=recv_num+1;         //每接收保存一个字节数据，recv_num增1
					if(recv_num>recv_buf[0])     //recv_buf保存的是数据帧的长度字，当recv_num大于长度字时，相当于当前接收的数据是帧的最后一个字节数据，即一帧数据接收完毕?
			    {
					    check_sum=0;
							for(i=0;i<recv_buf[0]+1;i++) //对一帧数据进行异或校验
							{
							   check_sum=check_sum^recv_buf[i];
							}
							if(check_sum==0)            //帧的最后一个字节为检验码，上面将校验码一起进行异或运算，若接收的数据没有错误，那check_sum得值一定是0
							{
							   if(EppromHandle()==FALSE)
								 {
							      recv_command_success_flag=SUCCESS; //标记成功接收一帧数据，供main函数做判断使用。
								 }
							}
							recv_num=0;
							recv_aa=FALSE;
					}
					if(recv_num>=max_num)   //判断接收的数据字节数是否大于缓存recv_buf，防止内存溢出?
					{
					   recv_num=0;
						 recv_aa=FALSE;
					}
			 }	
			 
		   
		}
		if(TI==1) //表示串口发送数据引发串口中断,在本系统中不使用中断方式发送数据，使用查询方式发送数据
		{
		   TI=0;
		}
		EA=1; //重新开中断    
}
/*---------------------------------------------------------------------------------------------------------------------------------------*/




/*--------------------------------------------------向射频模块发送指令--------------------------------------------------------------------*/
/*---射频模块发送打开LED灯指令---*/
  //射频模块的OUT1引脚与Led正极相连
void SetLedOn()
{
   unsigned char command_set_out1_0[6]={0xaa,0xbb,0x03,0x16,0x00,0x15}; //指令，控制射频模块的OUT1引脚输出高电平?
	 int i;
	 ES=0;  //使用查询方式发送串口数据时，要关闭串口中断，否则发送不正确
   for(i=0;i<6;i++) //查询方式发送数据
	 {
	     TI=0;
	     SBUF=command_set_out1_0[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;
}


/*---向射频模块发送关闭LED灯指令---*/
void SetLedOff()
{
   unsigned char command_set_out1_1[6]={0xaa,0xbb,0x03,0x16,0x01,0x14}; //指令，控制射频模块的OUT1引脚输出低电平
	 int i;
	 ES=0;                                                                //使用查询方式发送串口数据时，要关闭串口中断，否则发送不正确
   for(i=0;i<6;i++)                                                     //查询方式发送数据
	 {
	     TI=0;
	     SBUF=command_set_out1_1[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;
}


/*---向射频模块的发送寻卡指令---*/
void SearchCard()
{
   int i;
   unsigned char command_search_card[5]={0xaa,0xbb,0x02,0x20,0x22};//寻卡指令
	 recv_command_success_flag=FAIL;                                 //发送指令之前先设置FAIL,当串口中断处理函数中正确接收一帧数据后再设置为SUCCESS,供main函数做判断使用
	 ClearBuf();                                                     //通过串口向射频模块发送指令后会与数据返回，在这里提前对缓存recv_buf清零
	 ES=0;                                                           //使用查询方式发送串口数据时，要关闭串口中断，否则发送不正确
	 for(i=0;i<5;i++)                                                //查询方式发送串口数据
	 {
	     TI=0;
	     SBUF=command_search_card[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;                                                          //发送完后重新开启串口中断
}


/*---向射频模块发送读卡片EEPROM数据---*/
  //读卡片EEPROM中的第10,14,18,22块中的数据，块中保存的数据 xx xx xx xx xx xx xx  10 25 52 xx xx xx xx xx (xx可为任意数据， 10 25 52才是用来做判断)
	//1号门对应第10块，2号门对应第14块，3号门对应第18块，4号门对应第22块
void SearchCardData()
{
   int i;
	 //unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x0a, 0xff, 0xff, 0xcc, 0xff, 0x10, 0x26, 0x24};  //1号门
   //unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x0e, 0xff, 0xff, 0xdd, 0xff, 0x10, 0x26, 0x31};  //2号门
	   unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x12, 0xff, 0xff, 0xee, 0xff, 0x10, 0x26, 0x1e};  //3号门
	 //unsigned char command_search_card_data[13]={0xaa, 0xbb, 0x0a, 0x21, 0x00, 0x0a, 0xff, 0xff, 0xff, 0xff, 0x10, 0x26, 0x17};  //4号门
	 
	 recv_command_success_flag=FAIL;           //发送指令之前先设置FAIL,当串口中断处理函数中正确接收一帧数据后再设置为SUCCESS,供main函数做判断使用
	 ClearBuf();                               //通过串口向射频模块发送指令后会与数据返回，在这里提前对缓存recv_buf清零
	 ES=0;                                     //使用查询方式发送串口数据时，要关闭串口中断，否则发送不正确
	 for(i=0;i<13;i++)                         //查询方式发送串口数据
	 {
	     TI=0;
	     SBUF=command_search_card_data[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;                                    //发送完后重新开启串口中断
}
/*----------------------------------------------------------------------------------------------------------------------------------*/




/*----------------------------------------------------对射频模块发回来的数据进行校验--------------------------------------------------*/
/*---检验射频模块发回来的卡序列号在当前系统中是否存在---*/
error MatchCardSN()
{
	 int i;
	 unsigned char cardsn[4];
	 unsigned char Haddr;
	 unsigned char Laddr;
	 if(index>=user_number)  //如果用户所以号大于系统用户数，说明该用户不是系统的用户，直接退出
	 {
	     return FAIL;
	 }
	 
	 //从EEPROM中读卡序列号?
	 for(i=0;i<4;i++)
	 {
	    Haddr=0x20+(index*4+i)/256;
			Laddr=0x00+(index*4+i)%256;
	    cardsn[i]=ReadEEPROM(Haddr,Laddr);
	 }
	 //匹配卡序列号
	 if((recv_buf[2]==cardsn[0]) && (recv_buf[3]==cardsn[1]) && (recv_buf[4]==cardsn[2]) && (recv_buf[5]==cardsn[3]))
	 {
	     return SUCCESS;
	 }
	 else
	 {
	     return FAIL;
	 }  
}

/*---校验卡片中的数据是否正确---*/
  //若正确读到EEPROM中的数据，recv_buf[0:18]保存的数据是： 长度字 命令字 xx xx xx xx xx xx xx  10 25 52 xx xx xx xx xx
error MatchCardData()
{
	 if((recv_buf[9]==0x)&&(recv_buf[10]==0x10)&&(recv_buf[11]==0x25)&&(recv_buf[12]==0x52)) //校验卡片中的数据是否正确，正确返回SUCCESS,错误返回FAIL
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




/*-----------------------------------------射频卡片的序列号和EEPROM数据校验通过后的处理函数-----------------------------------------*/
/*---蜂鸣器响---*/
  //低电平驱动
void BuzzerRang()
{
   Speaker=0;
	 Delay(1000,10);
	 Speaker=1;
	 
}


/*--控制继电器开门---*/
//低电平驱动
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


/*---打开Led灯---*/
void OpenLed()
{
   Led=0;
	 Delay(1000,10);
	 Led=1;
}
/*-------------------------------------------------------------------------------------------------------------------------------*/

 
	 
	 
/*-------------------------------------------------------EEPROM操作--------------------------------------------------------------*/
/*----读EEPROM----*/
unsigned char ReadEEPROM(unsigned char Haddr,unsigned char Laddr)
{
    char i=0;
		unsigned char da;
    ISP_ADDRH=Haddr; //送地址
    ISP_ADDRL=Laddr; 
    EA=0;            //关中断
    ISP_CONTR=0x81;  //设置等待时间,允许ISP/IAP操作
		ISP_CMD=0x01;    //送读字节命令
		ISP_TRIG=0x46;   //触发命令
		ISP_TRIG=0xb9;
		i=0;             //延时
		i=0;
		da=ISP_DATA;     //取数据
		
		ISP_CONTR=0x00; //出于安全考虑，防止ISP/IAP误操作
		ISP_CMD=0x00;
		ISP_TRIG=0x00;
		ISP_ADDRH=0x00;
		ISP_ADDRL=0x00;
		
		EA=1;            //重新开中断
		return da;       //返回数据
}


/*---编程EEPROM---*/
void ProgramEEPROM(unsigned char Haddr,unsigned char Laddr,unsigned char da)
{
   ISP_DATA=da;    //送数据
	 ISP_ADDRH=Haddr;//送地址
	 ISP_ADDRL=Laddr;
	 EA=0;           //关中断
	 ISP_CONTR=0x81; //设置等待时间,允许ISP/IAP操作
	 ISP_CMD=0x02;   //送编程命令
	 ISP_TRIG=0x46;   //触发命令
	 ISP_TRIG=0xb9;
	 
	 ISP_CONTR=0x00;  //出于安全考虑，防止ISP/IAP误操作
	 ISP_CMD=0x00;
	 ISP_TRIG=0x00;
	 ISP_ADDRH=0x00;
	 ISP_ADDRL=0x00;
	 
	 EA=1;            //重新开中断
    
}


/*---擦除EEPROM---*/
void EraseEEPROM(unsigned char Haddr,unsigned char Laddr)
{
   
   ISP_ADDRH=Haddr; //送地址
	 ISP_ADDRL=Laddr;
 //EA=0;            //关中断
	 ISP_CONTR=0x81;  //设置等待时间,允许ISP/IAP操作
	 ISP_CMD=0x03;    //送编程命令
	 ISP_TRIG=0x46;   //触发命令
	 ISP_TRIG=0xb9;
	 
	 ISP_CONTR=0x00; //出于安全考虑，防止ISP/IAP误操作
	 ISP_CMD=0x00;
	 ISP_TRIG=0x00;
	 ISP_ADDRH=0x00;
	 ISP_ADDRL=0x00;
 //EA=1;           //重新开中断
	 
}

/*---从EPPROM中读一个卡的序列号,并通过串口送回PC---*/
void ReadCardSnFromEppromToPC()
{
   int i;
   unsigned char cmd[9]={0xaa,0xbb,0x06,0x50,0x00,0x00,0x00,0x00,0x00};
	 unsigned char Haddr;
	 unsigned char Laddr;
	 unsigned char checksum=0x00;
	 unsigned short idx;
	 
	 idx=recv_buf[2]*256+recv_buf[3];//获取卡的索引
	 for(i=0;i<4;i++)                //从EEPROM中读卡序列号,构造回送指令
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
	 
	 //通过串口回送给PC
	 ES=0;            //使用查询方式发送串口数据时，要关闭串口中断，否则发送不正确
	 for(i=0;i<9;i++) //查询方式发送串口数据
	 {
	     TI=0;
	     SBUF=cmd[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;           //发送完后重新开启串口中断 
}

/*---往EEPROM中写一个卡的序列号---*/
void WriteCardSnToEeprom()
{
   unsigned char cmd[5]={0xaa,0xbb,0x02,0x52,0x50}; //回送指令
   unsigned char Haddr;
	 unsigned char Laddr;
	 int i;
	 unsigned short idx;
	 
	 idx=recv_buf[6]*256+recv_buf[7];//构造卡的索引
   for(i=0;i<4;i++)                //往EEPROM中添加一个卡的序列号
	 {
	    Haddr=0x20+(idx*4+i)/256;
			Laddr=0x00+(idx*4+i)%256;
	    ProgramEEPROM(Haddr,Laddr,recv_buf[i+2]);
	 }
	 //向PC回送指令
	 ES=0;            //使用查询方式发送串口数据时，要关闭串口中断，否则发送不正确
   for(i=0;i<5;i++) //查询方式发送数据
	 {
	    TI=0;
	    SBUF=cmd[i];
			while(TI==0);
	 }
	 TI=0;
	 ES=1;           //发送完后重新开启串口中断 
}
   
	 
/*---擦除EERPROM的一个扇区---*/
void EraseSectorOfEpprom()
{
   unsigned char cmd[5]={0xaa,0xbb,0x02,0x54,0x56};//回送给PC的指令
	 int i;
	 unsigned char SectorOfNumber=recv_buf[2];       //获取要擦除的扇区号
   if(SectorOfNumber>=1&&SectorOfNumber<=4)
	 {
	    //擦除扇区
	    switch(SectorOfNumber)
			{
			   case 1:
				      EraseEEPROM(0x20,0x00);             //擦除第一个扇区
							break;
				 case 2:
				      EraseEEPROM(0x22,0x00);             //擦除第二个扇区
							break;
				 case 3:
				      EraseEEPROM(0x24,0x00);             //擦除第三个扇区
							break;
				 case 4:
				      EraseEEPROM(0x26,0x00);             //擦除第四个扇区
							break;
			}
			
			//向pc回送指令
			ES=0;            //使用查询方式发送串口数据时，要关闭串口中断，否则发送不正确
      for(i=0;i<5;i++) //查询方式发送数据
	    {
	       TI=0;
	       SBUF=cmd[i];
			   while(TI==0);
	    }
	    TI=0;
	    ES=1;
	}
}


/*---向EEPROM中写一个字节数据---*/
void WriteOneByteToEpprom()
{
   unsigned char i;
   unsigned char cmd[5]={0xaa,0xbb,0x02,0x5a,0x58}; //回送指令
   unsigned char Haddr;
	 unsigned char Laddr;
	 unsigned char da;
	 Haddr=recv_buf[2];
	 Laddr=recv_buf[3];
	 da=recv_buf[4];
	 ProgramEEPROM(Haddr,Laddr,da);
	 //向PC发送回送指令
	 ES=0;             //使用查询方式发送串口数据时，要关闭串口中断，否则发送不正确
   for(i=0;i<5;i++)  //查询方式发送数据
	 {
	     TI=0;
	     SBUF=cmd[i];
			 while(TI==0);
	 }
	 TI=0;
	 ES=1;
}


/*从EEPROM中读一个字节数据---*/
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
		//回送指令
	  ES=0;            //使用查询方式发送串口数据时，要关闭串口中断，否则发送不正确
    for(i=0;i<6;i++) //查询方式发送数据
	  {
	     TI=0;
	     SBUF=cmd[i];
			 while(TI==0);
	  }
	  TI=0;
	  ES=1;
}


/*---针对EEPROM的操作请求处理函数---*/
bool EppromHandle()
{
   unsigned char CmdWord=recv_buf[1]; //获取指令的命令字
	 if(CmdWord==0x50)                  //读卡EEPROM中的一个卡序列号
	 {
	    ReadCardSnFromEppromToPC();
	    return TRUE;
	 }
	 else if(CmdWord==0x52)             //向EEPROM中写一个卡的序列号
	 {
	    WriteCardSnToEeprom();         
	    return TRUE;
	 }
	 else if(CmdWord==0x54)            //擦除EEPROM的一个扇区
	 {
	   EraseSectorOfEpprom();
	   return TRUE;
	 }
	 else if(CmdWord==0x58)            //读EEPROM中的一个字节
	 {
	   ReadOneByteFromEpprom();
		 return TRUE;
	 }
	 else if(CmdWord==0x5a)
	 {
	    WriteOneByteToEpprom();        //向EEPROM中读一个字节
			return TRUE;
	 }
	 else
	 {
	    return FALSE;
	 }
}
/*-------------------------------------------------------------------------------------------------------------------------------*/




	 
/*-------------------------------------------------------------其他--------------------------------------------------------------*/
/*---对缓存recv_buf清零---*/
  //清除掉上次接收的数据
void ClearBuf()
{
    int i;
		for(i=0;i<max_num;i++)
		{
		    recv_buf[i]=0x0;
		}
}

/*---延时函数---*/
void Delay(int m,int n)
{
   int i,j;
   for(i=0;i<m;i++)
	 {
	    WDTFunction();//喂狗
	    for(j=0;j<n;j++){}
	 }
}  

/*---看门狗函数---*/
void WDTFunction()
{
   WDT=0x3e;
}
/*------------------------------------------------------------------------------------------------------------------------------*/

