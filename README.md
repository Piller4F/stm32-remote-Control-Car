# <center>基于stm32的体感遥控小车</center>

<img src="https://i.loli.net/2021/03/28/mzxGL9q5tAeHF7Q.jpg" alt="手势识别小车.jpg" style="zoom: 67%;" />

## 第一章 项目概述

### 1.1 项目简介

​		手势识别小车是一款基于STM32开发的智能设备，集成了嵌入式系统和智能手带设备的可靠、高效、便捷的优势。项目由两大部分组成。智能小车和手带设备，可以使用手带设备转角的变化控制智能小车的直行与转向。

### 1.2 项目背景

​		当今社会，嵌入式产品已经渗透到我们生活的各个领域，几乎很难找到哪个领域没有它足迹。如智能仪表、实时工控、通讯设备、导航系统、家用电器等，这些都是较为常见的嵌入式系统应用。



![嵌入式系统应用.png](https://i.loli.net/2021/03/28/gZw9SHKcv6fniJB.png)

​		嵌入式系统是以应用为中心，以计算机技术为基础，适用于应用系统对功能、可靠性、成本、体积和功耗有严格要求的专用计算机系统。相比通用计算机专门化，具有针对性的设计、合理的运算速度、高可靠性和较低的成本。因此嵌入式的学习、开发与应用将造就一批计算机应用与智能化控制的工程师和专家。因此为了跟随时代发展，我们有必要做的与时俱进。

​		来自国外权威机构IDC的数据显示，2012-2017年全球可穿戴设备的出货量不断增加，2015年以前出货量年均增速均在150%以上，实现较大规模的增加。2015年以后随着市场相对成熟的发展，全球可穿戴设备的出货量增速下降，但至2017年其出货量仍为11540万部，较上年同期同比增加12.70%，2018年截至至第二季度，全球可穿戴设备的出货量为8040万部，在可穿戴设备产品认可度不断提升的影响下，预计全年全球设备的出货量约增加至12.26亿部，较2017年同比增加6.24%。![可穿戴设备出货率.png](https://i.loli.net/2021/03/28/RgNXHBeGYoWyczZ.png)

### 1.3 应用前景

​		随着5G时代的到来，嵌入式、物联网在人们日常中的应用会更加广泛。并且随着智能穿戴设备普及，已逐渐开始向社会服务、医疗、娱乐等多个领取发展。本项目设计的手势识别小车可以加深对嵌入式系统的理解，为后续项目实践奠定基础。

## 第二章 系统方案

​		本项目使用一块手带设备控制小车的行走，因此该项目需要两块主控，一个用于获取手势数据，另一个则用于控制小车。对于手带设备要求必须小巧、稳定，因此采用STM32F103C8T6作为主控，获取手势数据并进行相应处理。小车的功能较多，从而需要相对多的引脚，本次采用STM32F103RCT6作为小车的主控，控制小车行走以及人机交互。

# ![系统总体设计概念图.png](https://i.loli.net/2021/03/28/5szcvKrWVZi63Ap.png)

​		手带设备主要由STM32F103CT86最小系统板、MPU6050三维角度加速度陀螺仪传感器、HC-05蓝牙模块、降压模块组成。最小系统板可以读取MPU6050经DMP姿态解算后的欧拉角数据，将其以数据帧的形式通过HC-05发送给小车。

# ![手带设备架构图.png](https://i.loli.net/2021/03/28/6cLojqMpWngRz82.png)

### 2.2 小车架构

​		STM32小车主要由一个STM32F103RCT6作为主控，并使用两个直流电机作为动力。人机交互使用一块8×8点阵LED模块，用于显示当前小车的行驶状态。小车接收到手带设备发送的数据帧后进行解析，得到欧拉角从而控制小车的行驶。

# ![小车架构图.png](https://i.loli.net/2021/03/28/5XcZof2Ri7ALVnI.png)

### 2.3 软件架构

​		该项目的软件架构由手带设备和单片机小车两部分组成。手带设备则主要使用MPU6050获取数据并进行姿态解算。单片机小车则需要完成小车的行驶、人机交互。该系统软件架构如图2-4所示。

![系统软件架构.png](https://i.loli.net/2021/03/28/WNx8mL27Og6kHti.png)

### 2.4 系统软件架构

## 第三章 系统硬件设计

### 2.3 手带设备

#### 3.1.1 STM32F103C8T6最小系统板

​		最小系统为能够使单片机能够正常运行，且必须使用最少必须器件组成的系统。一般单片机最小系统上电之后，单片机可以正常复位、下载运行程序，除此之外没有任何功能。因此一般我们可以在最小系统板的基础上添加其它功能模块或器件，使单片机具有实际功能。本次项目手带设备只需要进行数据读取以及发送即可，并不需要多余的外设，因此使用C8T6型号的最小系统板完全能够满足需求。最小系统板的价格相对低廉，大大降低了该项目开发成本。

# ![STM32F103C8T6最小系统板引脚图.png](https://i.loli.net/2021/03/28/UYyTPLMwtJKNfVR.png)

#### 3.1.2 MPU6050模块

# ![MPU6050模块.png](https://i.loli.net/2021/03/28/Sc5mUf9EMhgOlaZ.png)

​		MPU-60X0将3轴陀螺仪，3轴加速度计和数字运动处理器（DMP）组合在一起。通过I2C总线可以接受外部3轴罗盘的输入，提供9轴输出。MPU-60X0具有三个用于数字化陀螺仪输出的16位ADC转换器和三个用于数字化加速度计输出的16位ADC转换器。在本项目中该模块是手带设备的核心，STM32最小系统板获取MPU6050经过DMP姿态解算后的欧拉角作为小车行驶的依据。

# ![MPU6050参数.png](https://i.loli.net/2021/03/28/jieo84mZAH1NrIR.png)

#### 3.1.3 LM2596S降压模块
# ![LM2596S降压模块.jpg](https://i.loli.net/2021/03/28/Iw59uAfkCKeUpbZ.jpg)

​		电源模块采用7.4V可充电锂电池作为主要供电，开发板电压需要在5V以下，所以需要使用LM2596S模块进行降压处理.，该模块顺时针调节升压，逆时针调节降压。

# ![LM2596S降压模块参数.png](https://i.loli.net/2021/03/28/Imo5KgRjk4NXSCZ.png)

​		由于开发板支持5V电压输入，需要将电压降至不大于5V。输入电压可以为3.2至35V，输出电压1.25至30V，注意输入电压需高于输出电压1.5V，不可用于升压。顺时针调节升压，逆时针调节降压。

#### 3.1.4 HC-05蓝牙模块

# ![HC-05蓝牙模块.png](https://i.loli.net/2021/03/28/IDWucwFMvUhNs6O.png)

​		HC-05蓝牙模块是主从一体的蓝牙串口模块，通常当蓝牙设备配对连接成功后，我们可忽略蓝牙内部的通信协议，直接把蓝牙当做串口使用。建立连接后，两个设备共同使用一个串口，一个设备发送数据到通道中，另一个设备便可以接受通道中的数据。

​		该蓝牙模块具有两种工作模式：命令响应工作模式和自动连接工作模式，在自动连接工作模式下模块又可分为主（Master）、从（Slave）和回环（Loopback）三种工作角色。当模块处于自动连接工作模式时，将自动根据事先设定的方式连接的数据传输；当模块处于命令响应工作模式时能执行下述所有 AT 命令，用户可向模块发送各种 AT 指令，为模块设定控制参数或发布控制命令。通过控制模块外部按键，可以实现模块工作状态的动态转换。其中LED的闪烁状态代表这蓝牙模块当前工作状态。

# ![HC-05蓝牙模块指示灯.png](https://i.loli.net/2021/03/28/7E9L6pighjwcAQo.png)

### 3.2 智能小车

#### 3.2.1 STM32F103RCT6开发板

# ![STM32F103RCT6开发板.png](https://i.loli.net/2021/03/28/FdvNV72gtimf1De.png)

​		本次智能小车使用ALIENYEK MiniSTM32开发板作为主控板，主芯片为STM32F103RCT6(64)引脚，芯片FLASH:256K，芯片SRAM:48K，板内软、硬件资源丰富、操作简单。从成本、复杂程度综合进行考量，使用该开发板制作智能小车是不错的选择。

#### 3.2.2 TB6612FNG

# ![Tb6612fng模块.png](https://i.loli.net/2021/03/28/uWEl9OeRM8TKCvX.png)

​		TB6612FNG是东芝半导体公司生产的一款直流电机驱动器件，它具有大电流MOSFET-H桥结构，双通道电路输出，可同时驱动2个电机。TB6612FNG每通道输出高1A的连续驱动电流，启动峰值电流达2A/3A(连续脉冲/单脉冲)。

​		4种电机驱动模式：正转/反转/制动/停止。PWM支持频率高达100kHz，待机状态。片内低电压检测电路与热停机保护电路。

# ![Tb6612fng逻辑真值表.png](https://i.loli.net/2021/03/28/ULOu52nYxpZatIi.png)

#### 3.2.3 8X8点阵LED

# ![8X8点阵LED模块.png](https://i.loli.net/2021/03/28/kVjr5G9OUK6ibzc.png)

​		本次项目中智能小车部分将使用8*8点阵LED作为显示模块，根据小车的行驶状态会有相应的图案显示。使用的共阳点阵LED模块的原理如图3-7所示。

# ![8X8点阵LED原理图.png](https://i.loli.net/2021/03/28/Lg6uSQJt3qnjZU9.png)

## 第四章 系统软件设计

### 4.1 MPU6050姿态解算

#### 4.1.1 I2C通信协议

​		IIC 即 Inter-Integrated Circuit(集成电路总线），这种总线类型是由飞利浦半导体公司在八十年代初设计出来的，主要是用来连接整体电路(ICS) ，IIC 是一种多向控制总线，也就是说多个芯片可以连接到同一总线结构下，同时每个芯片都可以作为实时数据传输的控制源。这种方式简化了信号传输总线接口。

​		IIC 最初为音频和视频设备开发，如今主要在服务器管理中使用，其中包括单个组件状态的通信。例如管理员可对各个组件进行查询，以管理系统的配置或掌握组件的功能状态，如电源和系统风扇。可随时监控内存、硬盘、网络、系统温度等多个参数，增加了系统的安全性，方便了管理。

​		IIC 的主要构成只有两个双向的信号线，一个是数据线 SDA,一个是时钟线 SCL。MPU6050与MCU通过I2C总线进行通信，用软件模拟的方式实现 I2C 底层基本时序函数，包括起始、停止信号的产生，以及发送/接收单字节数据、检测/发送应答信号。

# ![IIC总线图.png](https://i.loli.net/2021/03/28/UvF1pycjsh82Xix.png)

#### 4.1.2 MPU6050原始数据读取

使用I2C读取MPU6050原始数据时需要将MPU6050内部寄存器恢复默认值，然后配置该模块的一些参数。根据I2C数据传输格式，读取相关寄存器，得到加速度传感器、角速度传感器和温度传感器的数据。

# ![IIC数据传输格式.png](https://i.loli.net/2021/03/28/c6amUbOt8hgvCDZ.png)

以读取MPU6050中某一寄存器为例，数据获取的流程图如图4-3所示。

# <img src="https://i.loli.net/2021/03/28/DFBT6iPLpn2KyCc.jpg" alt="MPU6050数据读取.jpg" style="zoom: 50%;" />

#### 4.1.3 DMP姿态解算

​		读取的MPU6050原始数据并不能直接使用，我们需要的时姿态数据即欧拉角：航向角（yaw）、横滚角（roll）、和俯仰角（pitch）。要得到欧拉角数据，需利用我们得到的原始数据，进行姿态融合解算，直接计算是比较复杂的，但MPU6050 自带了数字运动处理器 DMP，并且，InvenSense 提供了一个 MPU6050 的嵌入式运动驱动库，结合 MPU6050 的 DMP，可以将得到的原始数据，直接转换成四元数输出，而得到四元数之后，就可以很方便的计算出欧拉角，从而得到 yaw、 roll 和 pitch。

# ![欧拉角.png](https://i.loli.net/2021/03/28/wfZl6UgbsGeArh2.png)

​		通过 MPU6050 的 DMP 输出的四元数是 q30 格式的，也就是浮点数放大了 2 的 30 次方倍。在换算成欧拉角之前，必须先将其转换为浮点数，也就是除以 2 的 30 次方，然后再进行计算，计算公式为：

# ![公式.png](https://i.loli.net/2021/03/28/AucFQqRZUoVkmxj.png)

# ![欧拉角参数.png](https://i.loli.net/2021/03/28/xK6YE3zWtDIAXgQ.png)

### 4.2 姿态数据帧封装及解析

#### 4.2.1 HC-05通信

​		HC-05蓝牙模块在接口技术上使用的是USART通信，因此我们只需要配置相应的USART即可正常的使用蓝牙模块。在本项目中我们自己制定了一个简单的数据传输协议，当两个数据接收的时间间隔大于10ms时则认为当前的一个数据款传输完毕。该协议中接收数据的流程如图4-5所示。

# <img src="https://i.loli.net/2021/03/28/wAgzs7YB3f2Cky6.jpg" alt="数据接受协议.jpg" style="zoom:50%;" />

#### 4.2.2 姿态数据封装

​		该项目中手带设备需要将获取的手势姿态数据通过蓝牙发送给小车。姿态数据为欧拉角，则是由航向角（yaw）、横滚角（roll）、和俯仰角（pitch）组成。因此需要将这三个数据封装成一个数据帧发送给智能小车。我们规定一个数据帧的组成如图4-6所示。

# ![姿态数据帧.png](https://i.loli.net/2021/03/28/CX3rUgD2uNTM9G6.png)

​		一个姿态数据由以逗号分隔的三个浮点数组成，将该数据转化为一个字符串作为姿态数据帧。

#### 4.2.3 姿态数据解析

​		智能小车接收姿态数据帧后，需要将该数据帧进行解析，把字符串分隔三个字串，将其分别转化为浮点数保存到变量中。然后使用解析后的欧拉角来决定小车的行驶方式。该算法的流程如图4-7所示。

# ![姿态数据解算.png](https://i.loli.net/2021/03/28/lSE6YmKQnqL7Oe5.png)

### 4.3 智能小车控制

#### 4.3.1 8×8点阵LED图案显示

​		本次项目设计中智能小车部分的人机交互模块使用8×8点阵LED，该模块会显示小车的行驶状态。模块显示图案时需要不断的进行动态刷新，因此该功能需要使用中断的方式进行处理。

​		点阵模块显示的图案数据需要被存储到数组中，小车的行驶状态有：直行、后退、左转、右转、停止五种。因此点阵LED的花型至少需要五种，我们可以使用行数为五的二维数组存储花型。

#### 4.3.2 智能小车行走控制

​		PWM是脉冲宽度调制的简称，用于将一段信号编码为脉冲信号（一般是方波信号）。是在数字电路中达到模拟输出效果的一种手段。通过调节占空比的变化来调节信号、能量等的变化，占空比就是指在一个周期内，信号处于高电平的时间占据整个信号周期的百分比。例如一个周期内高电平10V持续二分之一的周期，则最终等效出的平均电压就为5V。本次实验使用PWM作为输出控制电机转速。

​		小车收到姿态数据帧并解析完毕后可以获得手带设备的欧拉角，行驶方式则跟着手带设备角度的变化而变化。该程序流程如图4-8所示。

# <img src="https://i.loli.net/2021/03/28/2aoS7B4DeAu5jI3.jpg" alt="小车控制流程.jpg" style="zoom:50%;" />

## 第五章 系统测试

### 5.1 手带设备姿态数据获取测试

# ![手带设备正面图.jpg](https://i.loli.net/2021/03/28/LuPx4gOTjBJ1IX8.jpg)

# ![手带设备背面图.jpg](https://i.loli.net/2021/03/28/xfutQRwTYWCom42.jpg)

​		测试方案：佩戴并开启手带设备，等待MPU6050初始化完毕后，转动手腕并观察当前串口调试助手中的数值变化。尽可能幅度较大的转动以检查该设备在实际运用中的效果。

​		功能指标：可以正确的显示手带设备转动时的欧拉角数据。

​		结果分析：测试的过程中发现，有概率发生数据传送失误，明显可以看出在转动手腕时，部分数据变化幅度较大，因此可以使用软件滤波解决该问题。

# ![手带设备欧拉角获取.png](https://i.loli.net/2021/03/28/WjogCd7NphJFD8v.png)

### 5.2 手势控制小车测试

​		测试方案：佩戴并打开手带设备、智能小车，通过转动手腕观察小车是否按照预期行驶、以及人机交互显示模块是否可以正常显示。

​		功能指标：小车可以正确的根据手带设备的转动行走。

​		结果分析：由于使用蓝牙传输的过程中会有部分数据传送失败，因此需要将错误数据全部去除，从而到时手带设备与小车直接的数据传输有70ms左右的延迟。

# ![手势控制小车测试.png](https://i.loli.net/2021/03/28/zvkIrKSZTOl2Hxg.png)

# ![手势控制小车测试2.png](https://i.loli.net/2021/03/28/yc83XISJHwDlQ9G.png)

## 参考文献

[1]  STM32不完全手册_寄存器版本_V3.1

[2]  STM32中文参考手册_V10

