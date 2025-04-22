# 布局——进阶

<mark>注意：进阶要求是面向大作业的，同学们选择划分作为大作业内容时，可以选择完成以下提到的要求。</mark><br>
<mark>注意：连同代码和论文一起提交，并且写一个简要的README文件，说明如何复现你的实验结果。</mark><br>
在这个实验中，你需要优化你的布局(placement)算法。
> 完成的需求越多，你的大作业成绩也会越高。需求3的权重最高，你可以完全copy对应baseline的代码，然后在它的基础上进行改进。实验报告中突出你的改进即可。

## 1. 并行化你的划分算法

改造实验二中实现的算法，使得它适应多线程计算。

在大作业论文中，你需要说明你的并行化思路，以及并行化的加速比。<br>
<mark>注意，算法稳定性是重要衡量指标，要求固定随机数种子的情况下，你的算法输出应该是一致的。</mark>

## 2. 元件重叠

改造实验二中的算法，使得它适应模块重叠的设计约束。

在大作业论文中，你需要简要说明你的算法思路。

修改文件`Arch.h`中的`MAX_BLOCK_CAPACITY`，设置为一个大于1的值，例如8。你的布局算法仍然能够实现问题的布局。

## 3. 布局约束
### 问题描述

实际上，FPGA的布局问题并不像实验二中的例子那么简单，所有的资源都可以任意摆放，而且没有任何的约束关系。<br>
FPGA上的资源按照类型可以划分为SLICE、DSP、BRAM、IO资源，每种不同的资源能够容纳的模块对象有限制。<br>
例如，SLICE资源仅能容纳LUT、FF、CARRY8的模块对象，那么在布局时，就不能够把RAM、DSP和IO类型的模块放到SLICE的资源上。

### 输入文件说明

数据集下载链接：[校内链接](http://172.18.233.211:5244/d/VLSI%E8%AF%BE%E4%BB%B6/dataset/placement/ISPD2016-Benchmarks.zip?sign=RAxap8L73aqc81WTd-qn3kyva7Z_rcWFN3GEt8vmiKw=:0)和[校外链接（ISPD2016-FPGA Placement Contest）](https://www.ispd.cc/contests/16/ispd2016_contest.html)。

`ISPD2016-Benchmarks.zip`包含四个文件，每个文件都代表一个具体的数据集。以`FPGA1-example1.tar.gz`为例，它包含10个文件。<br>
其中，`design.aux`文件指出哪些文件包含具体的数据。你的程序要读取以下文件`design.nodes`、`design.nets`、`design.wts`、`design.pl`、`design.scl`、`design.lib`。
```text
# version 3.1    02/08/2016
design : design.nodes design.nets design.wts design.pl design.scl design.lib
```

---
打开第一个文件`design.nodes`，存放有关电路的元件信息，它的内容如下：
```text
inst_2 RAMB36E2
inst_3 RAMB36E2
inst_4 BUFGCE
inst_5 DSP48E2
inst_6 DSP48E2
inst_7 FDRE
inst_8 FDRE
inst_9 FDRE
inst_10 FDRE
inst_11 FDRE
inst_12 FDRE
...
```
第一列是inst的名称，第二列是元件的类型。

---
打开第二个文件`design.nets`，存放有关电路的网表信息，它的内容如下：
```text
net net_1031 4
	inst_1341 I1
	inst_2834 I1
	inst_2221 I2
	inst_2255 O
endnet
net net_1032 6
	inst_1799 I0
	inst_1802 I0
	inst_2828 I0
	inst_2250 I2
	inst_2255 I2
	inst_276 Q
endnet
...
```
`net`关键字表明这是一条新的net数据输入，`endnet`关键字表明这是一条net输入的结束。紧随其后是net的名称以及包含多少个节点连接信息。例如`net_1031`连接4个inst，`net_1032`连接6个inst。<br>
每一行都是具体的连接信息，第一个是inst的名称，第二个是inst的端口。

---
打开第三个文件`design.wts`，文件为空可以不关心。

---
打开第四个文件`design.pl`，是固定约束，它的内容如下：
```text
inst_3330 103 0 25 FIXED
inst_1272 103 90 23 FIXED
inst_1269 103 90 24 FIXED
inst_1270 103 90 25 FIXED
inst_1317 103 90 0 FIXED
inst_3331 103 0 24 FIXED
inst_3328 103 0 29 FIXED
inst_3329 103 0 28 FIXED
inst_3326 103 0 33 FIXED
inst_3327 103 0 32 FIXED
inst_3324 103 0 37 FIXED
...
```
存放关于固定约束的设计，第一列是inst的名称，第二列是x坐标，第三列是y坐标，第四列是z坐标（一个FPGA资源节点可以存放多个同类元件，z坐标表示该元件在该节点的位置）。

---
打开第五个文件`design.scl`，它的内容如下：
```text
SITE SLICE
  LUT 16
  FF 16
  CARRY8 1
END SITE

SITE DSP
  DSP48E2 1
END SITE

SITE BRAM
  RAMB36E2 1
END SITE

SITE IO
  IO 64
END SITE

RESOURCES
  LUT LUT1 LUT2 LUT3 LUT4 LUT5 LUT6
  FF  FDRE
  CARRY8 CARRY8
  DSP48E2 DSP48E2
  RAMB36E2 RAMB36E2
  IO IBUF OBUF BUFGCE
END RESOURCES

SITEMAP 168 480
0 0 IO
0 60 IO
0 120 IO
0 180 IO
0 240 IO
0 300 IO
0 360 IO
0 420 IO
1 0 SLICE
1 1 SLICE
1 2 SLICE
...
```
* `SITEMAP`之前介绍FPGA布局约束，例如`SITE DSP`开始表示标记为DSP的FPGA节点只能存放1个DSP类型的电路元件。`SITE IO`开始表示标记为IO的FPGA节点只能存放64个IO类型的电路元件。
  * `SLICE`是比较特殊的FPGA节点，它可以存放三种类型的电路元件：LUT、FF、CARRY8。
* `RESOURCES`开始，标记了FPGA资源的类型和可存放的实例类型。例如`LUT`就可以存放`LUT1`、`LUT2`、`LUT3`、`LUT4`、`LUT5`、`LUT6`类型的电路元件,`IO`可以存放`IBUF`、`OBUF`、`BUFGCE`类型的电路元件。
* `SITEMAP`之后，是FPGA的布局资源图，(168,480)分别代表资源图的宽和高。例如`0 0 IO`表示FPGA位置(0,0)处是IO类型的FPGA节点；`1 0 SLICE`表示FPGA位置(1,0)处是SLICE类型的FPGA节点。
* 关于LUT和FF更加细节的布局约束，可以参考附录的“LUT和FF的布局约束”一节。
> 这部分在4个数据集中均不会变化，你可以写死在代码中。

---
打开第六个文件`design.lib`，是元件的库文件，它的内容如下：
```text
CELL FDRE
  PIN Q OUTPUT
  PIN D INPUT
  PIN C INPUT CLOCK
  PIN R INPUT CTRL
  PIN CE INPUT CTRL
END CELL 

CELL LUT6
  PIN O OUTPUT
  PIN I0 INPUT
  PIN I1 INPUT
  PIN I2 INPUT
  PIN I3 INPUT
  PIN I4 INPUT
  PIN I5 INPUT
END CELL
...
```
存放元件的库文件，例如元件类型为`FDRE`有5个引脚，其中4个是输入型的，1个是输出型，与`design.nets`文件对应。
> 这部分在4个数据集中均不会变化，你可以写死在代码中。

### 输出文件格式

要求布局算法的输出是一个文件，命名格式为`benchmark_name_placement.txt`，例如`FPGA1-example1_placement.txt`。
第一列是inst的名称，第二列是x坐标，第三列是y坐标，第四列是z坐标，中间用一个空格隔开。

## 附录

### LUT和FF的布局约束

原始约束含义说明在[这里](https://www.ispd.cc/contests/16/Legalization.html)。

* LUT部分
  * 如果要放置一个`LUT6`类型的元件，那么它的z坐标必须是奇数，并且要求z-1的位置不能放任何LUT。例如LUT6可以放在1号位(0号位置必须为空)，也可以放置在3号位(2号位置必须为空)……放置在15号位置(14号位置必须为空)。
  * 如果放置两个`LUT5`类型的元件，那么它们的放置必须相邻，例如0号位和1号位，或者2号位和3号位……（注意，放置在1号位和2号位置不合法，它们并不相邻）。要求这两个`LUT5`的输入“一致”，输出不同，本质上是因为单个0号位置和1号位置的LUT资源一共只有6个输入引脚，限制共享的两个LUT必须连接的外部线网数量不超过6。
    * 假设其中一个LUT5的模块a输入线网为12345，另一个模块b输入线网为12346，他们之间共享输入1234，总共有6个输入，满足约束，可以布局。
    * 假设其中一个LUT5的模块a输入线网为12345，另一个模块b输入线网为12367，他们之间共享输入123，总共有7个输入，不满足约束，不可以布局。
  * 对于其他类型的LUT组合，只要满足总输入引脚数量不超过6，就可以共享一个LUT资源。
* FF部分
  * 以下图例能够更好的表现FF之间的引脚共享关系。
<img width=250 alt="FFPacking" src="/VLSI-FPGA/advanced/img/FFPacking.jpg" style="margin:auto; display:flex;">

### baseline

取自DREAMPlaceFPGA的实际运行结果，你可以参考。运行平台为I7-12700K，运行时间仅供参考。

> 离baseline越近，对于你的最后的成绩有益处。

| 数据集 | 线长(HPWL) | 运行时间 |
|---|---|---|
| FPGA-example1 | 13562 | 248.13s |
| FPGA-example2 | 2914068 | 427.69s |
| FPGA-example3 | 7781857 | 367.88s |
| FPGA-example4 | 8221614 | 511.66s |
