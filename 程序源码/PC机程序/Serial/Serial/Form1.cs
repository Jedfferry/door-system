/*************************************************
 *   FineName:   Form1                           *
 *   Created:    2015.1.1                        *
 *   LastChange: 2015.1.15                       *
 *   Author:     FanChangFu                      *
 *   Development Tools:                          * 
 * ***********************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using System.IO;

namespace Serial
{
    public partial class Form1 : Form
    {
        SerialPort sp = new SerialPort();//定义一个串口类对象
        bool isOpen=false;               //标记串口是否处于打开状态
        UInt16 flag = 0;                 //标记用户按下了哪个按键控件 读卡、读块、写块、按钮等
        Byte[] buf = new Byte[500];      //用于接收串口数据
        int num = 0;                     //接收串口数据的字节数
        string FileNameRead;             //读取文件的文件名
        string FileNameWrite;            //写文件的文件名
        StreamReader sr;                 //定义一个用于操作文件读写的类对象
        enum A                           //定义一个枚举类型
        {
            SUCCESS=1,
            FAIL=0,
        }

        /*---类的构造函数---*/
        public Form1()
        {
            InitializeComponent();
 
        }

        /*---窗体加载---*/
        private void Form1_Load(object sender, EventArgs e)
        {
            int i;
            //列出串口端口
            for (i = 1; i <= 10; i++)
            {
                cbx_ComPort.Items.Add("COM" + i.ToString());
            }
            cbx_ComPort.SelectedIndex = 0;

            //列出写秘钥标识
            comb_KeyTypeW.Items.Add("AKey");
            comb_KeyTypeW.Items.Add("BKey");
            comb_KeyTypeW.SelectedIndex = 0;

            //列出读秘钥标识
            comb_KeyTypeR.Items.Add("AKey");
            comb_KeyTypeR.Items.Add("BKey");
            comb_KeyTypeR.SelectedIndex = 0;

            //列出写块号
            for (i = 0; i < 60; i++)
            {
                comb_BlockNumberW.Items.Add(i.ToString());
            }
            comb_BlockNumberW.SelectedIndex = 0;

            //列出读块号
            for (i = 0; i < 60; i++)
            {
                comb_BlockNumberR.Items.Add(i.ToString());
            }
            comb_BlockNumberR.SelectedIndex = 0;

            //列出扇区号
            for (i = 1; i <= 4; i++)
            {
                comb_SectorNumberW.Items.Add(i.ToString());
                com_EraseSector.Items.Add(i.ToString());
                comb_SectorNumberR.Items.Add(i.ToString());
            }
            comb_SectorNumberW.SelectedIndex = 0;
            com_EraseSector.SelectedIndex = 0;
            comb_SectorNumberR.SelectedIndex = 0;

            //串口数据到来时触发DataReceivedHandler函数
            sp.DataReceived += new SerialDataReceivedEventHandler(DataReceivedHandler);
        }

        /*---打开串口的函数---*/
        private A OpenSerial()
        {
           try
           {
               SetComPort(); //配置串口参数：波特率、开始位等
               sp.Open();    //打开串口
               isOpen = true;//标记串口打开
               return A.SUCCESS;
           }
           catch (Exception)
           {
               return A.FAIL;
           }   
        }

        /*---关闭串口的函数---*/
        private A CloseSerial()
        {
            try
            {
                sp.Close();      //关闭串口
                isOpen = false;  //标记串口关闭
                return A.SUCCESS;
            }
            catch (Exception)
            {
                return A.FAIL;
            }
        }

        /*---设置串口参数的函数---*/
        private void SetComPort()
        {        
            //设置端口
            sp.PortName = cbx_ComPort.Text.Trim();

            //设置波特率
            sp.BaudRate = 19200;

            //设置数据位
            sp.DataBits = 8;

            //设置校验位
            sp.Parity = Parity.None;

            //设置停止位
            sp.StopBits = StopBits.One;

            //设置超时读取时间
            sp.ReadTimeout = -1;
        }
  
        /*------------------------------------按钮单击事件--------------------------------------*/        
        /*---打开串口按钮单击事件---*/
        private void btn_OpenCom_Click(object sender, EventArgs e)
        {
            if (isOpen == false)
            {
                if (OpenSerial() == A.SUCCESS)
                {
                    btn_OpenCom.Text = "关闭串口";
                }
            }
            else
            {
                if (CloseSerial() == A.SUCCESS)
                {
                    btn_OpenCom.Text = "打开串口";
                }

            }
        }

        /*---退出按钮单击事件---*/
        private void btb_exit_Click(object sender, EventArgs e)
        {
            if (isOpen == true)
            {
                sp.Close();
            }
            this.Close();
        }

        /*---读卡序列号按钮单击事件---*/
        private void btn_readcardsn_Click(object sender, EventArgs e)
        {
            Byte []data={0xaa,0xbb,0x02,0x20,0x22};//读卡序列号指令
            if (isOpen == false)
            {
                MessageBox.Show("请先打开串口!");  
                return;
            }
            try
            {
               sp.Write(data, 0, 5);              //通过串口发送指令
            }
            catch (Exception)
            {
                MessageBox.Show("读卡序列号失败");
                return;
            }
            flag = 1;                            //标记用户按下的是读卡按钮
            this.txt_CardSn.Text = "";
            num = 0;
        }

        /*---写块按钮单击事件---*/
        private void btn_WriteBlock_Click(object sender, EventArgs e)
        {
            Byte[] data = new Byte[29];
            if (isOpen == false)
            {
                MessageBox.Show("请先打开串口!");//若串口未打开，提示先打开串口
                return;
            }
            //构造写块指令
            data[0] = 0xaa;
            data[1] = 0xbb;
            data[2] = 0x1a;
            data[3] = 0x22;
            if (comb_KeyTypeW.Text.Trim() == "AKey")//获取秘钥类型
            {
                data[4] = 0x00;
            }
            else
            {
                data[4] = 0x01;
            }
            data[5] = Convert.ToByte(comb_BlockNumberW.Text.Trim(), 10); //获取块号
            string key = txt_KeyW.Text.Trim();    //获取秘钥
            key = key.Replace(" ", "");
            if (key.Length != 12)
            {
                MessageBox.Show("请输入6个字节的秘钥");
                return;
            }
            for (int i = 0; i < 6; i++)
            {
                data[i+6] = Convert.ToByte(key.Substring(i * 2, 2), 16);
            }
            string da = txt_WriteDate.Text.Trim(); //获取写入的数据
            da = da.Replace(" ", "");
            if (da.Length != 32)
            {
                MessageBox.Show("请输入16字节的数据");
                return;
            }
            for (int i = 0; i < 16; i++)
            {
                data[i + 12] = Convert.ToByte(da.Substring(i * 2, 2), 16);
            }
            int su = 0x00;               //产生校验码
            for (int i = 2; i < 28; i++)
            {
                su = su ^ (int)data[i];
            }
            data[28] = (Byte)su;

            sp.Write(data, 0, 29);//通过串口发送写块指令
            flag = 3;             //标记用户按下的是写块按钮
            num = 0;
        }

        /*---读块按钮单击事件---*/
        private void btn_ReadBlock_Click(object sender, EventArgs e)
        {
            Byte[] data = new Byte[13];
            if (isOpen == false)
            {
                MessageBox.Show("请先打开串口!");
                return;
            }
            //构造读块指令
            data[0] = 0xaa;
            data[1] = 0xbb;
            data[2] = 0x0a;
            data[3] = 0x21;
            if (comb_KeyTypeR.Text.Trim() == "AKey")//获取秘钥类型
            {
                data[4] = 0x00;
            }
            else
            {
                data[4] = 0x01;
            }
            data[5] = Convert.ToByte(comb_BlockNumberR.Text.Trim(), 10); //获取块号          
            string key = txt_KeyR.Text.Trim();                           //获取秘钥
            key = key.Replace(" ", "");
            if (key.Length != 12)
            {
                MessageBox.Show("请输入6个字节的秘钥");
                return;
            }
            for (int i = 0; i < 6; i++)
            {
                data[i + 6] = Convert.ToByte(key.Substring(i * 2, 2), 16);
            }
            int su = 0x00;    //产生校验码
            for (int i = 2; i < 12; i++)
            {
                su = su ^ (int)data[i];
            }
            data[12] = (Byte)su;

            sp.Write(data, 0, 13);//发送读块指令
            flag = 2;             //标记用户按下的是读块指令
            num = 0;
            txt_ReadData.Text = "";
        }
        /*---读EEPROM中卡序列号单击事件---*/
        private void btn_ReadSn_Click(object sender, EventArgs e)
        {
            Byte[] data = new Byte[7];
            if (isOpen == false)
            {
                MessageBox.Show("请先打开串口!");   //若串口未打开，提示先打开串口
                return;
            }

            //构造读EEPROM中卡的序列号的指令
            data[0] = 0xaa;
            data[1] = 0xbb;
            data[2] = 0x04;
            data[3] = 0x50;

            string index = txt_SnIndexR.Text.Trim();//获取卡索引号
            index = index.Replace(" ", "");
            if (index.Length != 4)
            {
                MessageBox.Show("请输入2个字节的索引号");
                return;
            }
            for (int i = 0; i < 2; i++)
            {
                data[4 + i] = Convert.ToByte(index.Substring(i * 2, 2), 16);
            }
            int su = 0x00;                        //构造校验码
            for (int i = 0; i < 4; i++)
            {
                su = su ^ (int)data[i + 2];
            }
            data[6] = (Byte)su;

            sp.Write(data, 0, 7);               //发送读EEPROM中卡的序列号指令
            flag = 4;                           //标记用户按下的是读序列号指令
            num = 0;
            txt_SnR.Text = "";

        }

        /*---向EEPROM中写卡的序列号的按钮单击事件---*/
        private void btn_WriteSn_Click(object sender, EventArgs e)
        {

            Byte[] data = new Byte[11];
            if (isOpen == false)
            {
                MessageBox.Show("请先打开串口!"); //若串口未打开，提示先打开串口
                return;
            }

            //构造向EEPROM中写卡的序列号的指令
            data[0] = 0xaa;
            data[1] = 0xbb;
            data[2] = 0x08;
            data[3] = 0x52;
            string Sn = txt_SnW.Text.Trim();         //获取卡序列号
            Sn = Sn.Replace(" ", "");
            if (Sn.Length != 8)
            {
                MessageBox.Show("请输入4个字节的卡序列号");
                return;
            }
            for (int i = 0; i < 4; i++)
            {
                data[i + 4] = Convert.ToByte(Sn.Substring(i * 2, 2), 16);
            }
            string index = txt_SnIndexW.Text.Trim();//获取卡索引号
            index = index.Replace(" ", "");
            if (index.Length != 4)
            {
                MessageBox.Show("请输入2个字节的索引号");
                return;
            }
            for (int i = 0; i < 2; i++)
            {
                data[i + 8] = Convert.ToByte(index.Substring(i * 2, 2), 16);
            }
            int su = 0x00;                          //产生校验码
            for (int i = 0; i < 8; i++)
            {
                su = su ^ (int)data[i + 2];
            }
            data[10] = (Byte)su;

            sp.Write(data, 0, 11);//发送读EEPROM中卡的序列号指令
            flag = 5;             //标记用户按下的是读序列号指令
            num = 0;
        }

        /*---擦除EEPROM中扇区的按钮单击事件---*/
        private void btn_Erase_Click(object sender, EventArgs e)
        {
            Byte[] data = new Byte[6];
            if (isOpen == false)
            {
                MessageBox.Show("请先打开串口!"); //若串口未打开，提示先打开串口
                return;
            }

            //构造擦除EEPROM扇区的指令
            data[0] = 0xaa;
            data[1] = 0xbb;
            data[2] = 0x03;
            data[3] = 0x54;
            data[4] = Convert.ToByte(com_EraseSector.Text.Trim(), 10); //获取扇区号
            int su = 0x00;                                             //产生校验码
            for (int i = 0; i < 3; i++)
            {
                su = su ^ (int)data[i + 2];
            }
            data[5] = (Byte)su;

            sp.Write(data, 0, 6);//发送擦除扇区指令
            flag = 6;            //标记用户按下的是擦除按钮
            num = 0;
        }
   
        /*---编程扇区的写入按钮单击事件---*/
        private void btn_WriteSector_Click(object sender, EventArgs e)
        {
            string str;
            Byte[] data = new Byte[11];
            if (isOpen == false)
            {
                MessageBox.Show("请先打开串口!"); //若串口未打开，提示先打开串口
                return;
            }
            if (FileNameRead == "")
            {
                MessageBox.Show("请先选择文件!");//若未现在文件，提示先选择文件
                return;
            }

            sr = new StreamReader(FileNameRead);//读取文件内容的第一行数据
            str = sr.ReadLine();
            if (str == null)
            {
                MessageBox.Show("文件内容空");  //提示文件无内容
                return;
            }
            if (str.Length != 12)
            {
                MessageBox.Show("文件数据内容格式错误");//提示文件内容格式错误
                return;
            }
            //将读取的第一行数据封装成命令帧的形式通过串口发送给单片机
            data[0] = 0xaa;
            data[1] = 0xbb;
            data[2] = 0x08;
            data[3] = 0x52;
            for (int i = 0; i < 2; i++)    //从文件中获取索引号
            {
                data[i + 8] = Convert.ToByte(str.Substring(i * 2, 2), 16);
            }
            for (int i = 0; i < 4; i++)   //从文件中获取卡序列号
            {
                data[i + 4] = Convert.ToByte(str.Substring((i + 2) * 2, 2), 16);
            }
            int su = 0x00;                //产生校验码
            for (int i = 0; i < 8; i++)
            {
                su = su ^ (int)data[i + 2];
            }
            data[10] = (Byte)su;

            sp.Write(data, 0, 11);      //将第一行数据发送给单片机，文件的剩余数据的发送在DataReceivedHandler函数中完成
            flag = 7;                   //标记用户按下的是编程扇区的写入按钮
            num = 0;
        }


        /*---编程扇区的文件选择按钮单击事件---*/
        private void btn_SelectFileRead_Click(object sender, EventArgs e)
        {
            OpenFileDialog MyopenFileDialog = new OpenFileDialog();
            MyopenFileDialog.Filter = "(*.txt)|*.txt";
            if (MyopenFileDialog.ShowDialog() == DialogResult.OK)   //产生打开文件对话框
            {
                FileNameRead = MyopenFileDialog.FileName;
                this.txt_FileNameR.Text = FileNameRead;
            }
        }

        /*---读取扇区的按钮单击事件(还没实现)---*/
        private void btn_ReadSector_Click(object sender, EventArgs e)
        {

        }
        /*---读取扇区的文件选择按钮单击事件(还没实现)---*/
        private void btn_SelectFileWrite_Click(object sender, EventArgs e)
        {

        }


        /*---读取EEPROM中一个字节的读取按钮单击事件---*/
        private void btn_ReadOneByte_Click(object sender, EventArgs e)
        {

            Byte[] data = new Byte[7];
            if (isOpen == false)
            {
                MessageBox.Show("请先打开串口!"); //若串口未打开，提示先打开串口
                return;
            }
            //构造读取EEPROM中一个字节的指令
            data[0] = 0xaa;
            data[1] = 0xbb;
            data[2] = 0x04;
            data[3] = 0x58;
            string addr = txt_addrR.Text.Trim();//获取要读取的地址
            addr = addr.Replace(" ", "");
            if (addr.Length != 4)
            {
                MessageBox.Show("请输入2个字节的地址");
                return;
            }
            for (int i = 0; i < 2; i++)
            {
                data[i + 4] = Convert.ToByte(addr.Substring(i * 2, 2), 16);
            }
            int su = 0x00;                   //产生校验码
            for (int i = 0; i < 4; i++)
            {
                su = su ^ (int)data[i + 2];
            }
            data[6] = (Byte)su;

            sp.Write(data, 0, 7);          //发送读取EEPROM中一个字节的指令
            flag = 8;                      //标记用户按下的是读取EEPROM中一个字节的按钮
            num = 0;
            this.txt_OneByteR.Text = "";
        }

        /*---往EEPROM中写一个字节的按钮单击事件---*/
        private void btn_WriteOneByte_Click(object sender, EventArgs e)
        {
            Byte[] data = new Byte[8];
            if (isOpen == false)
            {
                MessageBox.Show("请先打开串口!");          //若串口未打开，提示先打开串口
                return;
            }
            data[0] = 0xaa;
            data[1] = 0xbb;
            data[2] = 0x05;
            data[3] = 0x5a;
            string addr = txt_addrW.Text.Trim();          //获取要写入的EEPROM地址
            addr = addr.Replace(" ", "");
            if (addr.Length != 4)
            {
                MessageBox.Show("请输入2个字节的地址");
                return;
            }
            for (int i = 0; i < 2; i++)
            {
                data[i + 4] = Convert.ToByte(addr.Substring(i * 2, 2), 16);
            }
            string OneByteData = txt_OneByteW.Text.Trim(); //获取要写入EEPROM中的数据
            OneByteData = OneByteData.Replace(" ", "");
            if (OneByteData.Length != 2)
            {
                MessageBox.Show("请输入1个字节的数据");
                return;
            }
            data[6] = Convert.ToByte(OneByteData, 16);
            int su = 0x00;                                //产生校验码
            for (int i = 0; i < 5; i++)
            {
                su = su ^ (int)data[i + 2];
            }
            data[7] = (Byte)su;

            sp.Write(data, 0, 8); //发送往EEPROM中写一个字节的指令
            flag = 9;             //标记用户按下的往EEPROM中写一个字节的按钮
            num = 0;
        }

      
        /*---串口数据到来时触发该函数---*/
        private void DataReceivedHandler(object sender, SerialDataReceivedEventArgs e)
        {
            //读接收缓存区中的数据
            num = num+this.sp.Read(buf, num,sp.BytesToRead);
            string str1;
            Byte []data=new Byte[11];

            if (flag == 1) //用户单击了读卡按钮
            {
                if (num == 9)
                {
                    num=0;
                    flag=0;
                    if((buf[0] == 0xaa) && (buf[1] == 0xbb) && (buf[2] == 0x06) && (buf[3] == 0x20))
                    {
                        int CheckNum = 0x00;
                        for (int i = 0; i < 7; i++)
                        {
                            CheckNum = CheckNum ^ (int)buf[i + 2];
                        }
                        if (CheckNum == 0x00)
                        {
                            this.txt_CardSn.Invoke
                            (
                                new MethodInvoker
                               (
                                  delegate
                                  {
                                      string str = "";
                                      for (int i = 0; i < 4; i++)
                                      {
                                          str = str + buf[i + 4].ToString("X2");
                                          //str = str + " ";
                                      }
                                      this.txt_CardSn.AppendText(str);//输出到主窗口文本控件                                                                             
                                  }
                               )
                             );
                        }
                    }
                }
            }

            else if (flag == 2) //用户单击了读块按钮
            {
                if (num == 21)
                {
                    num=0;
                    flag=0;
                    if ((buf[0] == 0xaa) && (buf[1] == 0xbb) && (buf[2] == 0x12) && (buf[3] == 0x21))
                    {
                        int CheckNum = 0x00;
                        for (int i = 0; i < 19; i++)
                        {
                            CheckNum = CheckNum ^ (int)buf[i + 2];
                        }
                        if (CheckNum == 0x00)
                        {
                            this.txt_ReadData.Invoke
                            (
                                new MethodInvoker
                               (
                                  delegate
                                  {
                                      string str = "";
                                      for (int i = 0; i < 16; i++)
                                      {
                                          str = str + buf[i + 4].ToString("X2");
                                          str = str + " ";
                                      }
                                      this.txt_ReadData.AppendText(str);//输出到主窗口文本控件                                       
                                  }
                               )
                             );
                        }
                    }
                }
            }

            else if (flag == 3)  //用户单击了写块按钮
            {
                if (num == 5)
                {
                    num=0;
                    flag=0;
                    if (buf[0] == 0xaa && buf[1] == 0xbb && buf[2] == 0x02 && buf[3] == 0x22 && buf[4] == 0x20)
                    {
                        MessageBox.Show("写卡成功");                       
                    }
                    if (buf[0] == 0xaa && buf[1] == 0xbb && buf[2] == 0x02 && buf[3] == 0xDD && buf[4] == 0xDF)
                    {
                        MessageBox.Show("写卡失败");                        
                    }
                }
            }

            else if (flag == 4)  //用户单击了读EEPROM中的卡序列号的按钮
            {
                if (num == 9)
                {
                    num=0;
                    flag=0;
                    if((buf[0] == 0xaa) && (buf[1] == 0xbb) && (buf[2] == 0x06) && (buf[3] == 0x50))
                    {
                        int CheckNum = 0x00;
                        for (int i = 0; i < 7; i++)
                        {
                            CheckNum = CheckNum ^ (int)buf[i + 2];
                        }
                        if (CheckNum == 0x00)
                        {
                            this.txt_SnR.Invoke
                            (
                                new MethodInvoker
                               (
                                  delegate
                                  {
                                      string str = "";
                                      for (int i = 0; i < 4; i++)
                                      {
                                          str = str + buf[i + 4].ToString("X2");
                                          str = str + " ";
                                      }
                                      this.txt_SnR.AppendText(str);//输出到主窗口文本控件                                     
                                  }
                               )
                             );
                        }
                    }
                }
            }
            
            else if (flag == 5)  //用户单击了往EEPROM中写一个卡的序列号的按钮
            {
                if (num == 5)
                {
                    num=0;
                    flag=0;
                    if (buf[0] == 0xaa && buf[1] == 0xbb && buf[2] == 0x02 && buf[3] == 0x52 && buf[4] == 0x50)
                    {
                        MessageBox.Show("写入成功");   
                    }
                }
            }

            else if (flag == 6)  //用户单击了擦除EEPROM中一个扇区的按钮
            {
                if (num == 5)
                {
                    num = 0;
                    flag = 0;
                    if (buf[0] == 0xaa && buf[1] == 0xbb && buf[2] == 0x02 && buf[3] == 0x54 && buf[4] == 0x56)
                    {
                        MessageBox.Show("擦除成功");                  
                    }        
                }
            }

            else if (flag == 7)  //用户单击了编程EEPROM扇区的按钮
            {
                if (num == 5)
                {
                    num = 0;                 
                    if(buf[0] == 0xaa && buf[1] == 0xbb && buf[2] == 0x02 && buf[3] == 0x52 && buf[4] == 0x50)
                    {
                        str1 = sr.ReadLine();
                        //str1.Replace(" ", "");
                        if(str1==null)
                        {
                            MessageBox.Show("编程成功");
                            return;
                        }
                        if (str1.Length != 12)
                        {
                            MessageBox.Show("文件内容格式错误");
                            return;
                        }
                        //构造发送指令
                        data[0] = 0xaa;
                        data[1] = 0xbb;
                        data[2] = 0x08;
                        data[3] = 0x52;
                        //索引号
                        for (int i = 0; i < 2; i++)
                        {
                            data[i + 8] = Convert.ToByte(str1.Substring(i * 2, 2), 16);
                        }
                        //序列号
                        for (int i = 0; i < 4; i++)
                        {
                            data[i + 4] = Convert.ToByte(str1.Substring((i + 2) * 2, 2), 16);
                        }
                        //校验码
                        int su = 0x00;
                        for (int i = 0; i < 8; i++)
                        {
                            su = su ^ (int)data[i + 2];
                        }
                        data[10] = (Byte)su;
                        //发送数据
                        sp.Write(data, 0, 11);
                        num = 0;                       
                    }
                }          
            }

            else if (flag == 8) //用户单击了读取EEPROM中一个字节的按钮
            {
                if (num == 6)
                {
                    num = 0;
                    flag = 0;
                    if ((buf[0] == 0xaa) && (buf[1] == 0xbb) && (buf[2] == 0x03) && (buf[3] == 0x58))
                    {
                        int CheckNum = 0x00;
                        for (int i = 0; i < 4; i++)
                        {
                            CheckNum = CheckNum ^ (int)buf[i + 2];
                        }
                        if (CheckNum == 0x00)
                        {
                            this.txt_OneByteR.Invoke
                            (
                                new MethodInvoker
                               (
                                  delegate
                                  {
                                      string str = buf[4].ToString("X2");
                                      this.txt_OneByteR.AppendText(str);//输出到主窗口文本控件                                     
                                  }
                               )
                             );
                        }
                    }
                }
            }

            else if (flag == 9) //用户单击了往EEPROM中写一个字节的按钮
            {
                if (num == 5)
                {
                    num = 0;
                    if (buf[0] == 0xaa && buf[1] == 0xbb && buf[2] == 0x02 && buf[3] == 0x5a && buf[4] == 0x58)
                    {
                        MessageBox.Show("写入成功");
                    }
                }
            }
            
            else
            {
                num = 0;
                flag = 0;
            }          
        }                                                      
    }
}
