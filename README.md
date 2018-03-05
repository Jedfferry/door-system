# 智能门禁系统

### 开发时间：2015年09月--2015年12月
### 开发环境：`Keil uvsion4` 
### 开发语言：`C` `C++`
### 项目背景：
本智能门禁系统是利用C51单片机作为处理器、RC522非接触式读写卡作为数据输入、欧太力变压器控制器作为电源而制作出的低电压、低成本、体积小的非接触式智能门禁系统。利用非接触式卡片通信，使门禁系统变得更加便捷与安全。目前此智能门禁系统已在校内多个实验室、办公室使用。
### 开发人员
  
* 莫云明（项目负责人）

* 范昌富

### 本人负责的内容

1.负责门禁锁模块开发，利用BCC校验对门号位求出门号校验序列，再添加门号校验序列来对门号进行验证；<br>
2.使用了哈希算法将各用户ID和门号校验序列散列计算，然后映射到EEPROM不同地址上，缩短开锁时间。

