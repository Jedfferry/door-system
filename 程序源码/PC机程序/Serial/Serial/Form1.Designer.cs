namespace Serial
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.btn_OpenCom = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.cbx_ComPort = new System.Windows.Forms.ComboBox();
            this.btb_exit = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.txt_WriteDate = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.btn_WriteBlock = new System.Windows.Forms.Button();
            this.txt_KeyW = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.comb_BlockNumberW = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.comb_KeyTypeW = new System.Windows.Forms.ComboBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btn_readcardsn = new System.Windows.Forms.Button();
            this.btn_ReadBlock = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label9 = new System.Windows.Forms.Label();
            this.txt_ReadData = new System.Windows.Forms.TextBox();
            this.txt_KeyR = new System.Windows.Forms.TextBox();
            this.comb_BlockNumberR = new System.Windows.Forms.ComboBox();
            this.comb_KeyTypeR = new System.Windows.Forms.ComboBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.txt_CardSn = new System.Windows.Forms.TextBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.label10 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.groupBox12 = new System.Windows.Forms.GroupBox();
            this.label20 = new System.Windows.Forms.Label();
            this.txt_OneByteW = new System.Windows.Forms.TextBox();
            this.btn_WriteOneByte = new System.Windows.Forms.Button();
            this.txt_addrW = new System.Windows.Forms.TextBox();
            this.label21 = new System.Windows.Forms.Label();
            this.groupBox11 = new System.Windows.Forms.GroupBox();
            this.label19 = new System.Windows.Forms.Label();
            this.txt_OneByteR = new System.Windows.Forms.TextBox();
            this.btn_ReadOneByte = new System.Windows.Forms.Button();
            this.txt_addrR = new System.Windows.Forms.TextBox();
            this.label18 = new System.Windows.Forms.Label();
            this.groupBox10 = new System.Windows.Forms.GroupBox();
            this.comb_SectorNumberR = new System.Windows.Forms.ComboBox();
            this.label17 = new System.Windows.Forms.Label();
            this.btn_ReadSector = new System.Windows.Forms.Button();
            this.btn_SelectFileWrite = new System.Windows.Forms.Button();
            this.txt_FileNameW = new System.Windows.Forms.TextBox();
            this.groupBox9 = new System.Windows.Forms.GroupBox();
            this.comb_SectorNumberW = new System.Windows.Forms.ComboBox();
            this.label16 = new System.Windows.Forms.Label();
            this.btn_WriteSector = new System.Windows.Forms.Button();
            this.btn_SelectFileRead = new System.Windows.Forms.Button();
            this.txt_FileNameR = new System.Windows.Forms.TextBox();
            this.label15 = new System.Windows.Forms.Label();
            this.txt_SnR = new System.Windows.Forms.TextBox();
            this.groupBox8 = new System.Windows.Forms.GroupBox();
            this.com_EraseSector = new System.Windows.Forms.ComboBox();
            this.btn_Erase = new System.Windows.Forms.Button();
            this.label14 = new System.Windows.Forms.Label();
            this.groupBox7 = new System.Windows.Forms.GroupBox();
            this.btn_WriteSn = new System.Windows.Forms.Button();
            this.txt_SnIndexW = new System.Windows.Forms.TextBox();
            this.txt_SnW = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.groupBox6 = new System.Windows.Forms.GroupBox();
            this.btn_ReadSn = new System.Windows.Forms.Button();
            this.txt_SnIndexR = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.groupBox12.SuspendLayout();
            this.groupBox11.SuspendLayout();
            this.groupBox10.SuspendLayout();
            this.groupBox9.SuspendLayout();
            this.groupBox8.SuspendLayout();
            this.groupBox7.SuspendLayout();
            this.groupBox6.SuspendLayout();
            this.SuspendLayout();
            // 
            // btn_OpenCom
            // 
            this.btn_OpenCom.Font = new System.Drawing.Font("宋体", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_OpenCom.Location = new System.Drawing.Point(52, 73);
            this.btn_OpenCom.Name = "btn_OpenCom";
            this.btn_OpenCom.Size = new System.Drawing.Size(81, 23);
            this.btn_OpenCom.TabIndex = 0;
            this.btn_OpenCom.Text = "打开串口";
            this.btn_OpenCom.UseVisualStyleBackColor = true;
            this.btn_OpenCom.Click += new System.EventHandler(this.btn_OpenCom_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label1.Location = new System.Drawing.Point(6, 27);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(47, 19);
            this.label1.TabIndex = 1;
            this.label1.Text = "端口";
            // 
            // cbx_ComPort
            // 
            this.cbx_ComPort.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.cbx_ComPort.FormattingEnabled = true;
            this.cbx_ComPort.Location = new System.Drawing.Point(52, 27);
            this.cbx_ComPort.Name = "cbx_ComPort";
            this.cbx_ComPort.Size = new System.Drawing.Size(81, 23);
            this.cbx_ComPort.TabIndex = 6;
            // 
            // btb_exit
            // 
            this.btb_exit.Font = new System.Drawing.Font("宋体", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btb_exit.Location = new System.Drawing.Point(52, 111);
            this.btb_exit.Name = "btb_exit";
            this.btb_exit.Size = new System.Drawing.Size(81, 23);
            this.btb_exit.TabIndex = 16;
            this.btb_exit.Text = "退出";
            this.btb_exit.UseVisualStyleBackColor = true;
            this.btb_exit.Click += new System.EventHandler(this.btb_exit_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.txt_WriteDate);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.btn_WriteBlock);
            this.groupBox1.Controls.Add(this.txt_KeyW);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.comb_BlockNumberW);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.comb_KeyTypeW);
            this.groupBox1.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox1.Location = new System.Drawing.Point(12, 363);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(420, 315);
            this.groupBox1.TabIndex = 38;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "写块";
            // 
            // txt_WriteDate
            // 
            this.txt_WriteDate.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_WriteDate.Location = new System.Drawing.Point(6, 126);
            this.txt_WriteDate.Name = "txt_WriteDate";
            this.txt_WriteDate.Size = new System.Drawing.Size(408, 25);
            this.txt_WriteDate.TabIndex = 51;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 95);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(104, 19);
            this.label5.TabIndex = 50;
            this.label5.Text = "写入数据：";
            // 
            // btn_WriteBlock
            // 
            this.btn_WriteBlock.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_WriteBlock.Location = new System.Drawing.Point(153, 160);
            this.btn_WriteBlock.Name = "btn_WriteBlock";
            this.btn_WriteBlock.Size = new System.Drawing.Size(75, 23);
            this.btn_WriteBlock.TabIndex = 42;
            this.btn_WriteBlock.Text = "写块";
            this.btn_WriteBlock.UseVisualStyleBackColor = true;
            this.btn_WriteBlock.Click += new System.EventHandler(this.btn_WriteBlock_Click);
            // 
            // txt_KeyW
            // 
            this.txt_KeyW.Font = new System.Drawing.Font("宋体", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_KeyW.Location = new System.Drawing.Point(93, 60);
            this.txt_KeyW.Name = "txt_KeyW";
            this.txt_KeyW.Size = new System.Drawing.Size(121, 22);
            this.txt_KeyW.TabIndex = 49;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(44, 61);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(47, 19);
            this.label4.TabIndex = 48;
            this.label4.Text = "秘钥";
            // 
            // comb_BlockNumberW
            // 
            this.comb_BlockNumberW.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comb_BlockNumberW.FormattingEnabled = true;
            this.comb_BlockNumberW.Location = new System.Drawing.Point(272, 32);
            this.comb_BlockNumberW.Name = "comb_BlockNumberW";
            this.comb_BlockNumberW.Size = new System.Drawing.Size(127, 23);
            this.comb_BlockNumberW.TabIndex = 47;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(226, 32);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(47, 19);
            this.label3.TabIndex = 46;
            this.label3.Text = "块号";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 32);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(85, 19);
            this.label2.TabIndex = 45;
            this.label2.Text = "秘钥标识";
            // 
            // comb_KeyTypeW
            // 
            this.comb_KeyTypeW.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comb_KeyTypeW.FormattingEnabled = true;
            this.comb_KeyTypeW.Location = new System.Drawing.Point(93, 32);
            this.comb_KeyTypeW.Name = "comb_KeyTypeW";
            this.comb_KeyTypeW.Size = new System.Drawing.Size(127, 23);
            this.comb_KeyTypeW.TabIndex = 44;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.cbx_ComPort);
            this.groupBox2.Controls.Add(this.btb_exit);
            this.groupBox2.Controls.Add(this.btn_OpenCom);
            this.groupBox2.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox2.Location = new System.Drawing.Point(12, 12);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(139, 149);
            this.groupBox2.TabIndex = 39;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "串口设置";
            // 
            // btn_readcardsn
            // 
            this.btn_readcardsn.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_readcardsn.Location = new System.Drawing.Point(79, 111);
            this.btn_readcardsn.Name = "btn_readcardsn";
            this.btn_readcardsn.Size = new System.Drawing.Size(75, 23);
            this.btn_readcardsn.TabIndex = 41;
            this.btn_readcardsn.Text = "读卡";
            this.btn_readcardsn.UseVisualStyleBackColor = true;
            this.btn_readcardsn.Click += new System.EventHandler(this.btn_readcardsn_Click);
            // 
            // btn_ReadBlock
            // 
            this.btn_ReadBlock.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_ReadBlock.Location = new System.Drawing.Point(144, 159);
            this.btn_ReadBlock.Name = "btn_ReadBlock";
            this.btn_ReadBlock.Size = new System.Drawing.Size(75, 23);
            this.btn_ReadBlock.TabIndex = 43;
            this.btn_ReadBlock.Text = "读块";
            this.btn_ReadBlock.UseVisualStyleBackColor = true;
            this.btn_ReadBlock.Click += new System.EventHandler(this.btn_ReadBlock_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label9);
            this.groupBox4.Controls.Add(this.txt_ReadData);
            this.groupBox4.Controls.Add(this.txt_KeyR);
            this.groupBox4.Controls.Add(this.btn_ReadBlock);
            this.groupBox4.Controls.Add(this.comb_BlockNumberR);
            this.groupBox4.Controls.Add(this.comb_KeyTypeR);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.label6);
            this.groupBox4.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox4.Location = new System.Drawing.Point(12, 164);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(420, 188);
            this.groupBox4.TabIndex = 52;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "读块";
           
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 95);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(104, 19);
            this.label9.TabIndex = 54;
            this.label9.Text = "读出数据：";
            // 
            // txt_ReadData
            // 
            this.txt_ReadData.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_ReadData.Location = new System.Drawing.Point(10, 126);
            this.txt_ReadData.Name = "txt_ReadData";
            this.txt_ReadData.ReadOnly = true;
            this.txt_ReadData.Size = new System.Drawing.Size(404, 25);
            this.txt_ReadData.TabIndex = 53;
            // 
            // txt_KeyR
            // 
            this.txt_KeyR.Font = new System.Drawing.Font("宋体", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_KeyR.Location = new System.Drawing.Point(89, 64);
            this.txt_KeyR.Name = "txt_KeyR";
            this.txt_KeyR.Size = new System.Drawing.Size(121, 22);
            this.txt_KeyR.TabIndex = 52;
            // 
            // comb_BlockNumberR
            // 
            this.comb_BlockNumberR.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comb_BlockNumberR.FormattingEnabled = true;
            this.comb_BlockNumberR.Location = new System.Drawing.Point(271, 32);
            this.comb_BlockNumberR.Name = "comb_BlockNumberR";
            this.comb_BlockNumberR.Size = new System.Drawing.Size(127, 23);
            this.comb_BlockNumberR.TabIndex = 4;
            // 
            // comb_KeyTypeR
            // 
            this.comb_KeyTypeR.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comb_KeyTypeR.FormattingEnabled = true;
            this.comb_KeyTypeR.Location = new System.Drawing.Point(89, 32);
            this.comb_KeyTypeR.Name = "comb_KeyTypeR";
            this.comb_KeyTypeR.Size = new System.Drawing.Size(121, 23);
            this.comb_KeyTypeR.TabIndex = 3;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label8.Location = new System.Drawing.Point(39, 65);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(47, 19);
            this.label8.TabIndex = 2;
            this.label8.Text = "秘钥";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label7.Location = new System.Drawing.Point(221, 32);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(47, 19);
            this.label7.TabIndex = 1;
            this.label7.Text = "块号";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.label6.Location = new System.Drawing.Point(1, 32);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(85, 19);
            this.label6.TabIndex = 0;
            this.label6.Text = "秘钥标识";
            // 
            // txt_CardSn
            // 
            this.txt_CardSn.Font = new System.Drawing.Font("宋体", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_CardSn.Location = new System.Drawing.Point(10, 58);
            this.txt_CardSn.Name = "txt_CardSn";
            this.txt_CardSn.ReadOnly = true;
            this.txt_CardSn.Size = new System.Drawing.Size(253, 22);
            this.txt_CardSn.TabIndex = 53;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.label10);
            this.groupBox3.Controls.Add(this.btn_readcardsn);
            this.groupBox3.Controls.Add(this.txt_CardSn);
            this.groupBox3.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox3.Location = new System.Drawing.Point(163, 12);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(269, 149);
            this.groupBox3.TabIndex = 54;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "读卡序列号";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(6, 27);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(95, 19);
            this.label10.TabIndex = 54;
            this.label10.Text = "卡序列号:";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.groupBox12);
            this.groupBox5.Controls.Add(this.groupBox11);
            this.groupBox5.Controls.Add(this.groupBox10);
            this.groupBox5.Controls.Add(this.groupBox9);
            this.groupBox5.Controls.Add(this.label15);
            this.groupBox5.Controls.Add(this.txt_SnR);
            this.groupBox5.Controls.Add(this.groupBox8);
            this.groupBox5.Controls.Add(this.groupBox7);
            this.groupBox5.Controls.Add(this.groupBox6);
            this.groupBox5.Font = new System.Drawing.Font("宋体", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.groupBox5.Location = new System.Drawing.Point(438, 12);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Size = new System.Drawing.Size(504, 666);
            this.groupBox5.TabIndex = 55;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "操作STC89C52的EEPROM";
            // 
            // groupBox12
            // 
            this.groupBox12.Controls.Add(this.label20);
            this.groupBox12.Controls.Add(this.txt_OneByteW);
            this.groupBox12.Controls.Add(this.btn_WriteOneByte);
            this.groupBox12.Controls.Add(this.txt_addrW);
            this.groupBox12.Controls.Add(this.label21);
            this.groupBox12.Location = new System.Drawing.Point(260, 522);
            this.groupBox12.Name = "groupBox12";
            this.groupBox12.Size = new System.Drawing.Size(236, 138);
            this.groupBox12.TabIndex = 11;
            this.groupBox12.TabStop = false;
            this.groupBox12.Text = "往EEPROM写一个字节";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(6, 74);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(95, 19);
            this.label20.TabIndex = 15;
            this.label20.Text = "写入数据:";
            // 
            // txt_OneByteW
            // 
            this.txt_OneByteW.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_OneByteW.Location = new System.Drawing.Point(102, 72);
            this.txt_OneByteW.Name = "txt_OneByteW";
            this.txt_OneByteW.Size = new System.Drawing.Size(128, 25);
            this.txt_OneByteW.TabIndex = 14;
            // 
            // btn_WriteOneByte
            // 
            this.btn_WriteOneByte.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_WriteOneByte.Location = new System.Drawing.Point(131, 106);
            this.btn_WriteOneByte.Name = "btn_WriteOneByte";
            this.btn_WriteOneByte.Size = new System.Drawing.Size(75, 23);
            this.btn_WriteOneByte.TabIndex = 13;
            this.btn_WriteOneByte.Text = "写入";
            this.btn_WriteOneByte.UseVisualStyleBackColor = true;
            // 
            // txt_addrW
            // 
            this.txt_addrW.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_addrW.Location = new System.Drawing.Point(102, 35);
            this.txt_addrW.Name = "txt_addrW";
            this.txt_addrW.Size = new System.Drawing.Size(128, 25);
            this.txt_addrW.TabIndex = 12;
            // 
            // label21
            // 
            this.label21.AutoSize = true;
            this.label21.Location = new System.Drawing.Point(44, 37);
            this.label21.Name = "label21";
            this.label21.Size = new System.Drawing.Size(57, 19);
            this.label21.TabIndex = 11;
            this.label21.Text = "地址:";
            // 
            // groupBox11
            // 
            this.groupBox11.Controls.Add(this.label19);
            this.groupBox11.Controls.Add(this.txt_OneByteR);
            this.groupBox11.Controls.Add(this.btn_ReadOneByte);
            this.groupBox11.Controls.Add(this.txt_addrR);
            this.groupBox11.Controls.Add(this.label18);
            this.groupBox11.Location = new System.Drawing.Point(10, 522);
            this.groupBox11.Name = "groupBox11";
            this.groupBox11.Size = new System.Drawing.Size(236, 138);
            this.groupBox11.TabIndex = 10;
            this.groupBox11.TabStop = false;
            this.groupBox11.Text = "读取EEPROM一个字节";
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(6, 72);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(95, 19);
            this.label19.TabIndex = 15;
            this.label19.Text = "读出数据:";
            // 
            // txt_OneByteR
            // 
            this.txt_OneByteR.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_OneByteR.Location = new System.Drawing.Point(102, 70);
            this.txt_OneByteR.Name = "txt_OneByteR";
            this.txt_OneByteR.ReadOnly = true;
            this.txt_OneByteR.Size = new System.Drawing.Size(128, 25);
            this.txt_OneByteR.TabIndex = 14;
            // 
            // btn_ReadOneByte
            // 
            this.btn_ReadOneByte.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_ReadOneByte.Location = new System.Drawing.Point(128, 106);
            this.btn_ReadOneByte.Name = "btn_ReadOneByte";
            this.btn_ReadOneByte.Size = new System.Drawing.Size(75, 23);
            this.btn_ReadOneByte.TabIndex = 13;
            this.btn_ReadOneByte.Text = "读取";
            this.btn_ReadOneByte.UseVisualStyleBackColor = true;
            // 
            // txt_addrR
            // 
            this.txt_addrR.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_addrR.Location = new System.Drawing.Point(102, 33);
            this.txt_addrR.Name = "txt_addrR";
            this.txt_addrR.Size = new System.Drawing.Size(128, 25);
            this.txt_addrR.TabIndex = 12;
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(41, 36);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(57, 19);
            this.label18.TabIndex = 11;
            this.label18.Text = "地址:";
            // 
            // groupBox10
            // 
            this.groupBox10.BackColor = System.Drawing.SystemColors.Control;
            this.groupBox10.Controls.Add(this.comb_SectorNumberR);
            this.groupBox10.Controls.Add(this.label17);
            this.groupBox10.Controls.Add(this.btn_ReadSector);
            this.groupBox10.Controls.Add(this.btn_SelectFileWrite);
            this.groupBox10.Controls.Add(this.txt_FileNameW);
            this.groupBox10.Location = new System.Drawing.Point(9, 401);
            this.groupBox10.Name = "groupBox10";
            this.groupBox10.Size = new System.Drawing.Size(487, 108);
            this.groupBox10.TabIndex = 9;
            this.groupBox10.TabStop = false;
            this.groupBox10.Text = "读扇区";
            // 
            // comb_SectorNumberR
            // 
            this.comb_SectorNumberR.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comb_SectorNumberR.FormattingEnabled = true;
            this.comb_SectorNumberR.Location = new System.Drawing.Point(144, 75);
            this.comb_SectorNumberR.Name = "comb_SectorNumberR";
            this.comb_SectorNumberR.Size = new System.Drawing.Size(121, 23);
            this.comb_SectorNumberR.TabIndex = 4;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(12, 76);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(133, 19);
            this.label17.TabIndex = 3;
            this.label17.Text = "读取的扇区号:";
            // 
            // btn_ReadSector
            // 
            this.btn_ReadSector.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_ReadSector.Location = new System.Drawing.Point(385, 76);
            this.btn_ReadSector.Name = "btn_ReadSector";
            this.btn_ReadSector.Size = new System.Drawing.Size(75, 23);
            this.btn_ReadSector.TabIndex = 2;
            this.btn_ReadSector.Text = "读取";
            this.btn_ReadSector.UseVisualStyleBackColor = true;
            // 
            // btn_SelectFileWrite
            // 
            this.btn_SelectFileWrite.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_SelectFileWrite.Location = new System.Drawing.Point(386, 35);
            this.btn_SelectFileWrite.Name = "btn_SelectFileWrite";
            this.btn_SelectFileWrite.Size = new System.Drawing.Size(75, 23);
            this.btn_SelectFileWrite.TabIndex = 1;
            this.btn_SelectFileWrite.Text = "保存位置";
            this.btn_SelectFileWrite.UseVisualStyleBackColor = true;
            // 
            // txt_FileNameW
            // 
            this.txt_FileNameW.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_FileNameW.Location = new System.Drawing.Point(20, 33);
            this.txt_FileNameW.Name = "txt_FileNameW";
            this.txt_FileNameW.ReadOnly = true;
            this.txt_FileNameW.Size = new System.Drawing.Size(353, 25);
            this.txt_FileNameW.TabIndex = 0;
            // 
            // groupBox9
            // 
            this.groupBox9.BackColor = System.Drawing.SystemColors.Control;
            this.groupBox9.Controls.Add(this.comb_SectorNumberW);
            this.groupBox9.Controls.Add(this.label16);
            this.groupBox9.Controls.Add(this.btn_WriteSector);
            this.groupBox9.Controls.Add(this.btn_SelectFileRead);
            this.groupBox9.Controls.Add(this.txt_FileNameR);
            this.groupBox9.Location = new System.Drawing.Point(10, 278);
            this.groupBox9.Name = "groupBox9";
            this.groupBox9.Size = new System.Drawing.Size(487, 108);
            this.groupBox9.TabIndex = 8;
            this.groupBox9.TabStop = false;
            this.groupBox9.Text = "编程扇区";
            // 
            // comb_SectorNumberW
            // 
            this.comb_SectorNumberW.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.comb_SectorNumberW.FormattingEnabled = true;
            this.comb_SectorNumberW.Location = new System.Drawing.Point(144, 75);
            this.comb_SectorNumberW.Name = "comb_SectorNumberW";
            this.comb_SectorNumberW.Size = new System.Drawing.Size(121, 23);
            this.comb_SectorNumberW.TabIndex = 4;
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(12, 76);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(133, 19);
            this.label16.TabIndex = 3;
            this.label16.Text = "写入的扇区号:";
            // 
            // btn_WriteSector
            // 
            this.btn_WriteSector.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_WriteSector.Location = new System.Drawing.Point(384, 76);
            this.btn_WriteSector.Name = "btn_WriteSector";
            this.btn_WriteSector.Size = new System.Drawing.Size(75, 23);
            this.btn_WriteSector.TabIndex = 2;
            this.btn_WriteSector.Text = "写入";
            this.btn_WriteSector.UseVisualStyleBackColor = true;
            // 
            // btn_SelectFileRead
            // 
            this.btn_SelectFileRead.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_SelectFileRead.Location = new System.Drawing.Point(385, 34);
            this.btn_SelectFileRead.Name = "btn_SelectFileRead";
            this.btn_SelectFileRead.Size = new System.Drawing.Size(75, 23);
            this.btn_SelectFileRead.TabIndex = 1;
            this.btn_SelectFileRead.Text = "选择文件";
            this.btn_SelectFileRead.UseVisualStyleBackColor = true;
          
            // 
            // txt_FileNameR
            // 
            this.txt_FileNameR.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_FileNameR.Location = new System.Drawing.Point(20, 33);
            this.txt_FileNameR.Name = "txt_FileNameR";
            this.txt_FileNameR.ReadOnly = true;
            this.txt_FileNameR.Size = new System.Drawing.Size(353, 25);
            this.txt_FileNameR.TabIndex = 0;
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(21, 111);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(85, 19);
            this.label15.TabIndex = 7;
            this.label15.Text = "读出数据";
            // 
            // txt_SnR
            // 
            this.txt_SnR.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_SnR.Location = new System.Drawing.Point(108, 108);
            this.txt_SnR.Name = "txt_SnR";
            this.txt_SnR.ReadOnly = true;
            this.txt_SnR.Size = new System.Drawing.Size(109, 25);
            this.txt_SnR.TabIndex = 6;
            // 
            // groupBox8
            // 
            this.groupBox8.Controls.Add(this.com_EraseSector);
            this.groupBox8.Controls.Add(this.btn_Erase);
            this.groupBox8.Controls.Add(this.label14);
            this.groupBox8.Location = new System.Drawing.Point(10, 194);
            this.groupBox8.Name = "groupBox8";
            this.groupBox8.Size = new System.Drawing.Size(487, 68);
            this.groupBox8.TabIndex = 5;
            this.groupBox8.TabStop = false;
            this.groupBox8.Text = "擦除EEPROM";
            // 
            // com_EraseSector
            // 
            this.com_EraseSector.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.com_EraseSector.FormattingEnabled = true;
            this.com_EraseSector.Location = new System.Drawing.Point(82, 35);
            this.com_EraseSector.Name = "com_EraseSector";
            this.com_EraseSector.Size = new System.Drawing.Size(107, 23);
            this.com_EraseSector.TabIndex = 9;
            // 
            // btn_Erase
            // 
            this.btn_Erase.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_Erase.Location = new System.Drawing.Point(204, 36);
            this.btn_Erase.Name = "btn_Erase";
            this.btn_Erase.Size = new System.Drawing.Size(75, 23);
            this.btn_Erase.TabIndex = 8;
            this.btn_Erase.Text = "擦除";
            this.btn_Erase.UseVisualStyleBackColor = true;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(6, 35);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(76, 19);
            this.label14.TabIndex = 7;
            this.label14.Text = "扇区号:";
            // 
            // groupBox7
            // 
            this.groupBox7.Controls.Add(this.btn_WriteSn);
            this.groupBox7.Controls.Add(this.txt_SnIndexW);
            this.groupBox7.Controls.Add(this.txt_SnW);
            this.groupBox7.Controls.Add(this.label13);
            this.groupBox7.Controls.Add(this.label12);
            this.groupBox7.Location = new System.Drawing.Point(259, 35);
            this.groupBox7.Name = "groupBox7";
            this.groupBox7.Size = new System.Drawing.Size(238, 148);
            this.groupBox7.TabIndex = 1;
            this.groupBox7.TabStop = false;
            this.groupBox7.Text = "向EEPROM中写入卡序列号";
            // 
            // btn_WriteSn
            // 
            this.btn_WriteSn.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_WriteSn.Location = new System.Drawing.Point(134, 110);
            this.btn_WriteSn.Name = "btn_WriteSn";
            this.btn_WriteSn.Size = new System.Drawing.Size(75, 23);
            this.btn_WriteSn.TabIndex = 2;
            this.btn_WriteSn.Text = "写入";
            this.btn_WriteSn.UseVisualStyleBackColor = true;
            // 
            // txt_SnIndexW
            // 
            this.txt_SnIndexW.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_SnIndexW.Location = new System.Drawing.Point(100, 73);
            this.txt_SnIndexW.Name = "txt_SnIndexW";
            this.txt_SnIndexW.Size = new System.Drawing.Size(109, 25);
            this.txt_SnIndexW.TabIndex = 3;
            // 
            // txt_SnW
            // 
            this.txt_SnW.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_SnW.Location = new System.Drawing.Point(100, 36);
            this.txt_SnW.Name = "txt_SnW";
            this.txt_SnW.Size = new System.Drawing.Size(109, 25);
            this.txt_SnW.TabIndex = 4;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(3, 76);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(104, 19);
            this.label13.TabIndex = 1;
            this.label13.Text = "卡索引号：";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(6, 38);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(104, 19);
            this.label12.TabIndex = 0;
            this.label12.Text = "卡序列号：";
            // 
            // groupBox6
            // 
            this.groupBox6.Controls.Add(this.btn_ReadSn);
            this.groupBox6.Controls.Add(this.txt_SnIndexR);
            this.groupBox6.Controls.Add(this.label11);
            this.groupBox6.Location = new System.Drawing.Point(10, 34);
            this.groupBox6.Name = "groupBox6";
            this.groupBox6.Size = new System.Drawing.Size(241, 149);
            this.groupBox6.TabIndex = 0;
            this.groupBox6.TabStop = false;
            this.groupBox6.Text = "读EEPRCOM中卡的序列号";
            // 
            // btn_ReadSn
            // 
            this.btn_ReadSn.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.btn_ReadSn.Location = new System.Drawing.Point(133, 110);
            this.btn_ReadSn.Name = "btn_ReadSn";
            this.btn_ReadSn.Size = new System.Drawing.Size(75, 23);
            this.btn_ReadSn.TabIndex = 57;
            this.btn_ReadSn.Text = "读序列号";
            this.btn_ReadSn.UseVisualStyleBackColor = true;
            this.btn_ReadSn.Click += new System.EventHandler(this.btn_ReadSn_Click);
            // 
            // txt_SnIndexR
            // 
            this.txt_SnIndexR.Font = new System.Drawing.Font("宋体", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.txt_SnIndexR.Location = new System.Drawing.Point(98, 39);
            this.txt_SnIndexR.Name = "txt_SnIndexR";
            this.txt_SnIndexR.Size = new System.Drawing.Size(109, 25);
            this.txt_SnIndexR.TabIndex = 56;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(11, 43);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(85, 19);
            this.label11.TabIndex = 55;
            this.label11.Text = "卡索引号";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(948, 690);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Cursor = System.Windows.Forms.Cursors.Default;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(2000, 1500);
            this.MinimumSize = new System.Drawing.Size(408, 334);
            this.Name = "Form1";
            this.Text = "射频读写卡软件--FanChangFu";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.groupBox12.ResumeLayout(false);
            this.groupBox12.PerformLayout();
            this.groupBox11.ResumeLayout(false);
            this.groupBox11.PerformLayout();
            this.groupBox10.ResumeLayout(false);
            this.groupBox10.PerformLayout();
            this.groupBox9.ResumeLayout(false);
            this.groupBox9.PerformLayout();
            this.groupBox8.ResumeLayout(false);
            this.groupBox8.PerformLayout();
            this.groupBox7.ResumeLayout(false);
            this.groupBox7.PerformLayout();
            this.groupBox6.ResumeLayout(false);
            this.groupBox6.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btn_OpenCom;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox cbx_ComPort;
        private System.Windows.Forms.Button btb_exit;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Button btn_readcardsn;
        private System.Windows.Forms.Button btn_WriteBlock;
        private System.Windows.Forms.TextBox txt_WriteDate;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox txt_KeyW;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comb_BlockNumberW;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox comb_KeyTypeW;
        private System.Windows.Forms.Button btn_ReadBlock;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.TextBox txt_KeyR;
        private System.Windows.Forms.ComboBox comb_BlockNumberR;
        private System.Windows.Forms.ComboBox comb_KeyTypeR;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox txt_CardSn;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox txt_ReadData;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.Button btn_Erase;
        private System.Windows.Forms.GroupBox groupBox8;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.GroupBox groupBox7;
        private System.Windows.Forms.Button btn_WriteSn;
        private System.Windows.Forms.TextBox txt_SnIndexW;
        private System.Windows.Forms.TextBox txt_SnW;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.GroupBox groupBox6;
        private System.Windows.Forms.Button btn_ReadSn;
        private System.Windows.Forms.TextBox txt_SnIndexR;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.ComboBox com_EraseSector;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox txt_SnR;
        private System.Windows.Forms.GroupBox groupBox9;
        private System.Windows.Forms.Button btn_WriteSector;
        private System.Windows.Forms.Button btn_SelectFileRead;
        private System.Windows.Forms.TextBox txt_FileNameR;
        private System.Windows.Forms.ComboBox comb_SectorNumberW;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.GroupBox groupBox10;
        private System.Windows.Forms.ComboBox comb_SectorNumberR;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Button btn_ReadSector;
        private System.Windows.Forms.Button btn_SelectFileWrite;
        private System.Windows.Forms.TextBox txt_FileNameW;
        private System.Windows.Forms.GroupBox groupBox11;
        private System.Windows.Forms.TextBox txt_addrR;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.GroupBox groupBox12;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.TextBox txt_OneByteW;
        private System.Windows.Forms.Button btn_WriteOneByte;
        private System.Windows.Forms.TextBox txt_addrW;
        private System.Windows.Forms.Label label21;
        private System.Windows.Forms.Label label19;
        private System.Windows.Forms.TextBox txt_OneByteR;
        private System.Windows.Forms.Button btn_ReadOneByte;
    }
}

