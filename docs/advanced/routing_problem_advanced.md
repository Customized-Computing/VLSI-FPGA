# 布线——进阶

<mark>注意：进阶要求是面向大作业的，同学们选择布线作为大作业主题时，可以选择完成以下提到的要求。</mark><br>
<mark>注意：连同代码和论文一起提交，并且写一个简要的README文件，说明如何复现你的实验结果。</mark><br>
在这个实验中，你需要优化你的布线(routing)算法。
> 完成的需求越多，你的大作业成绩也会越高。需求3的权重最高，你可以只完成需求3获得所有作业分数，你可以完全copy对应baseline的代码，然后在它的基础上进行改进。实验报告中突出你的改进即可。

## 1. 并行化你的布线算法

改造实验三中实现的算法，使得它适应多线程计算。

在大作业论文中，你需要说明你的并行化思路，以及并行化的加速比。<br>
<mark>注意，算法稳定性也是布线器的重要衡量指标，要求固定随机数种子的情况下，你的算法输出应该是一致的。</mark>

## 2. 改进你的布线算法

改造实验三中实现的算法，提高算法在低布线资源下的可路由性。报告对于实验三的数据集，各自能布线成功的最少channel width(并记录为$W_{min}$)。

在大作业论文中你可以提交下表的实验结果，同时报告$W_{min}$的结果。<br>
| 测试样例 | Channel Width | RRNode使用量 | 运行时间(s) | 内存消耗(MB) |
|---|---|---|---|---|
| small_dense | $W_{min}$ | | | |
| small_dense | $W_{min}+30\%$ | | | |
| med_dense | $W_{min}$ | | | |
| med_dense | $W_{min}+30\%$ | | | |
| large_dense | $W_{min}$ | | | |
| large_dense | $W_{min}+30\%$ | | | |
| xl | $W_{min}$ | | | |
| xl | $W_{min}+30\%$ | | | |
| huge | $W_{min}$ | | | |
| huge | $W_{min}+30\%$ | | | |

> 记录运行时间，可以采用linux提供的命令 `/usr/bin/time -v <command>`。也可以自行编写一个监控脚本，或者采用附录中的监控脚本。

## 3. PCB布线设计

### 问题描述

PCB布线分为两个步骤：第一步芯片下的逃逸布线(escape routing)；第二步是芯片间的总线布线(bus routing)。

<img width=400 alt="CAFE router" src="/VLSI-FPGA/advanced/img/PCB-routing-illustrate.png" style="margin:auto; display:flex;">

不过在这里我们仅考虑总线布线的问题。你需要<mark>设计一个PCB布线器</mark>，读入芯片数据，输出每一对引脚之间的布线结果。
布线器需要考虑的约束在附录章节的“总线布线约束”中有详细介绍。

> 问题比较复杂，不能全部布通是很正常的一件事情。

### 输入文件说明

数据集下载连接：[校内链接](http://172.18.233.211:5244/d/VLSI%E8%AF%BE%E4%BB%B6/dataset/routing/final_case_1002.zip?sign=d7gcY4XXzwKVGbP_t63PEVgAmTJ8UbnuU-z5oyqQLJ4=:0)和[~~校外链接~~]()。

打开输入文本文件`example/example.input`，文本文件分为5个部分，第一部分是用于衡量布线结果质量的参数，本大作业用不上。
```txt
RUNTIME 1
ALPHA 5
BETA 1
GAMMA 5
DELTA 8
EPSILON 200
```

第二部分，限定PCB的布线空间，最大不超过UINT_MAX。例如这里布线空间限制在(0,0)和(1000,1000)这个范围内。
```txt
DESIGN_BOUNDARY (0 0) (1000 1000)
```

第三部分，关于PCB每一层布线资源的说明。`LAYERS`关键字后跟着一个数字，表示当前PCB设计一共有两层PCB。第一层称为`L1`，是垂直方向的布线资源，然后跟一个数字，标记在这一层布线必须距离布线边界和障碍物超过20。第二层称为`L2`，是水平方向的布线资源，30表示在这一层布线必须距离布线边界和障碍物超过30。

`TRACKS`关键字后跟着数字表明一共有34条可布线通道，一共有34行输入。第一行`L1 (100 0) (100 1000) 10`说明，这一条通道在`L1`层PCB上，位置从(100,0)延伸到(100,1000)，允许布线宽度为10。而`L1 (360 0) (360 1000) 6`说明布线宽度为6，不能容纳比6更宽的总线。
```txt
LAYERS 2
L1 vertical 20
L2 horizontal 30
ENDLAYERS
TRACKS 34
L1 (100 0) (100 1000) 10
L1 (140 0) (140 1000) 10
L1 (180 0) (180 1000) 10
L1 (220 0) (220 1000) 10
L1 (260 0) (260 1000) 10
L1 (360 0) (360 1000) 6
L1 (400 0) (400 1000) 6
...
L2 (450 850) (1000 850) 10
L2 (450 900) (1000 900) 10
ENDTRACKS
```

第四部分，关于需要互联的引脚说明。
* `BUSES 1`说明要布线的总线数量为1个。
* `BUS B1`这是一个名为`B1`的总线，数字3表示这个总线有3对引脚需要互联，数字2表示每个引脚位置由2个坐标给出。实际上是引脚有宽高属性。
* `WIDTH`关键字后跟着的数字一定和总PCB层数相等，例如这里是2。然后输入2个数字标记这个总线在不同层布线宽度资源需求，这里两个10说明在L1层和L2层都需要10宽度的布线资源。
* `BIT`每个bit都表示这是总线`B1`一对需要互联的引脚，`L2 (0 795) (30 805)`第一个引脚在L2层，左下角在(0,795)，是一个宽为30高为10的引脚，`L2 (970 595) (1000 605)`与它互联的引脚也在L2层，左下角在(970,595)，是一个宽为30高为10的引脚。<mark>引脚的位置可能与通道位置不对齐，但只要覆盖了，我们就认为可以互联。</mark>
```txt
BUSES 1
BUS B1
3
2
WIDTH 2
10
10
ENDWIDTH
BIT 0
L2 (0 795) (30 805)
L2 (970 595) (1000 605)
ENDBIT
BIT 1
L2 (0 745) (30 755)
L2 (970 695) (1000 705)
ENDBIT
BIT 2
L2 (0 645) (30 655)
L2 (970 745) (1000 755)
ENDBIT
ENDBUS
ENDBUSES
```

第五部分，关于障碍物位置说明。
* `OBSTACLES`后跟着17，表明一共有17个障碍物，输入也有17行。每一行`L1 (175 245) (185 255)`表示这个障碍物在L1层PCB上，左下角坐标(175,245)，右上角坐标(185,255)。
```txt
OBSTACLES 17
L1 (175 245) (185 255)
L1 (175 395) (185 405)
L1 (355 145) (365 155)
L1 (355 295) (365 305)
L1 (355 445) (365 455)
L1 (515 245) (515 255)
L1 (525 395) (525 405)
L1 (735 195) (925 505)
L2 (175 245) (185 255)
L2 (175 395) (185 405)
L2 (355 145) (365 155)
L2 (355 295) (365 305)
L2 (355 445) (365 455)
L2 (515 245) (515 255)
L2 (525 395) (525 405)
L2 (255 595) (450 900)
L2 (735 195) (925 505)
ENDOBSTACLES
```

### 输出文件说明

打开文件`example/example.output`，是`example.input`的解，画成图如下所示。

<img width=400 alt="ICCAD2018-Problem-B" src="/VLSI-FPGA/advanced/img/PCB-routing-bus-example.png" style="margin:auto; display:flex;">

## 附录

### 总线布线约束

总线布线约束(bus routing)分为两类，一类是与信号传输时差有关的线长匹配约束(Length-matching constraint)和精确匹配(exact-matching constraint)。其中精确匹配是在线长匹配约束的基础上考虑更加切合实际情况。另一类则和通道相关。

另外障碍物约束也需要纳入到布线约束。

#### 信号偏斜约束

线长匹配约束，原自总线布线的需要保证信号同时传输的特别需要，要求属于同一个总线的布线线长必须相同。较短的线网必须在布线区域内绕圈，使得较短的线网实际布线长度和较长的线网一致[[1]](https://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=6930748)。

而精确匹配约束考虑到不同的PCB层可能导致线间距不同，进而导致同样的线长，但电气特性不一致的情况[[2]](https://ieeexplore.ieee.org/abstract/document/5361288)。<br>
这里简化问题，只考虑线长的因素，不考虑线网的电气特性差别。

> 不要为了保证线长一致刻意绕远路，允许一定程度的线长不一致。

#### 通道约束

PCB是多层印刷板合并得到，为了便于PCB的制造，每一层印刷板只允许特定方向的线路布局，例如第一层只有垂直方向的布线资源，第二层只有水平方向的布线资源，第三层又只有垂直方向的布线资源……以此类推。

<img width=400 alt="layer-track" src="/VLSI-FPGA/advanced/img/PCB-routing-layer-track-resource-example.png" style="margin: auto; display: flex;">

> 可以从上图发现：每一层的障碍物可以不相同，设计数据结构时需要考虑到这一点。<br>
> 另外，多层PCB不一定是一层水平、一层垂直的交叉排布，有可能出现连续两层都是水平的或垂直的。

#### 布线宽度约束

通道存在一定的宽度限制，而互联的总线有宽度的需求。总线在布线到特定通道时，必须满足通道的宽度限制大于等于总线的需求。例如在输入文件`example.input`中，`BUS B1`的布线资源宽度需求都是10，那么在L1层上的`L1 (360 0) (360 1000) 6`就无法被利用。

#### 拓扑约束

> 这个约束实际上在简化问题。

对于属于同一个总线的多个不同引脚对，它们互联时需要保证一个拓扑约束。
* 同一个总线的每一对引脚之间互联的线段数量一致。
* 同一个总线的每一对引脚之间经过的PCB层序列一致，例如都是$L_1,L_2,L_1,L_2$的顺序。
* 同一个总线的每一对引脚之间布线方向一致，如下左图蓝色部分布线方向不一致，违反约束算布线失败。而右图部分，如果一处是T型连接，那么其他引脚布线序列上相同位置也要是T型连接。

<img width=600 alt="failed-topo-routing" src="/VLSI-FPGA/advanced/img/PCB-routing-failed-bus-example.png" style="margin: auto; display: flex;">

* 以及下面左图所示，同一个总线(BUS)的不同引脚数量互联线段数不同算布线失败。右图所示是连接错误，没有按照顺序互联。

<img width=600 alt="failed-topo-routing2" src="/VLSI-FPGA/advanced/img/PCB-routing-failed-bus-example2.png" style="margin: auto; display: flex;">

### 监控脚本

在使用前需要修改`cmd`变量，改成你要执行的指令。

```python
import time
import psutil
from concurrent.futures import ThreadPoolExecutor
import subprocess

time_use = []
children_threads = []
peak_memory_use = []
CASE_COUNT = 4 # 总测试集数量

print("输入 -1 运行所有测试集")
choice = int(input("Your choice: "))

def monitorThread(pid, flag):
    max_mem = 0
    max_children = 0
    while (flag[0]):
        try:
            children = psutil.Process(pid).threads()
            mem = psutil.Process(pid).memory_info()
            max_mem = max(max_mem, mem)
            max_children = max(max_children, children)
            time.sleep(0.1)
        except psutil.NoSuchProcess as e:
            print("进程已结束")
            break
    return max_children, max_mem

pool = ThreadPoolExecutor()

for i in range(1, CASE_COUNT+1):
    if (choice != -1):
        i = choice # 否则只运行特定测试集
    cmd = []
    start = time.time()
    p = subprocess.Popen(cmd)
    max_mem = 0
    max_children = 0
    flag = [true]
    try:
        t = pool.submit(monitorThread, pid=p.pid, flag=flag)
        p.wait()
    except KeyboardInterrupt as e:
        p.terminate()
        choice = CASE_COUNT+1
    flag[0] = False
    end = time.time()
    max_children, max_mem = t.result()
    children_threads.append(max_childre)
    peak_memory_use.append(max_mem/1024/1024)
    time_use.append(end-start)

print("所有样例用时(s): "+str(time_use))
print("所有样例使用线程数量: "+str(children_threads))
print("内存使用(MB): "+str(peak_memory_use))

```

### Baseline

数据集情况介绍
| 测试样例 | Bus 数量 | Layer 数量 | Net 数量 | Track 数量 | 障碍物数量 | 
|---|---|---|---|---|---|
| beta_1 | 34 | 3 | 1260 | 49209 | 159 |
| beta_2 | 26 | 3 | 1262 | 49209 | 0 |
| beta_3 | 60 | 3 | 665 | 22732 | 555108 |
| beta_4 | 62 | 3 | 698 | 22732 | 0 |
| beta_5 | 6 | 4 | 1964 | 54150 | 0 |
| final_1 | 18 | 3 | 1032 | 81226 | 0 |
| final_2 | 70 | 3 | 1285 | 14209 | 0 |
| final_3 | 47 | 4 | 852 | 21379 | 0 |

最优解取自论文[《Obstacle-Avoiding Length-Matching Bus Routing  Considering Nonuniform Track Resources》](https://ieeexplore.ieee.org/document/9085342)。其中$C_f$表示布线失败的情况，$WL_{diff}$表示多个BUS累计线长差异。

| 测试样例 | $C_f$ | $WL_{diff}$ | Time(s) |
|---|---|---|---|
| beta_1 | 0 | 1047740 | 45 |
| beta_2 | 0 | 1172440 | 28 |
| beta_3 | 0 | 2879040 | 68 |
| beta_4 | 0 | 4111920 | 26 |
| beta_5 | 0 | 9070700 | 98 |
| final_1 | 0 | 7526640 | 887 |
| final_2 | 0 | 6294400 | 62 |
| final_3 | 0 | 10286480 | 10 |