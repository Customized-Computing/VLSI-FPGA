# 实验3

## 简介

在本次实验中，你将设计一个布线算法，探索每个数据集的最小布线通道宽度，并输出相应的routing segments数量。

* 实现你的算法，但**暂时不提交**代码。（大作业时统一收三次实验代码）。
* **提交**实验报告说明你是如何做的，实验报告应该包含以下内容：
  * <mark>学号+姓名</mark>
  * 算法逻辑和实现思路
    * 你采用的算法是什么算法？
    * 你是如何设计算法的？
    * 你的算法有无特别之处、创新之处。
    * 等等。
  * 你的算法运行结果表格，报告每一个数据集的最小布线通道宽度和对应的routing segments数量。
  * 实验总结。说明你的方法存在的优缺点，下一步改进的方向是什么？
  * <mark>非必要，报告中不包含实验代码。实验代码和截图不计入总页数。</mark>

## FPGA架构说明

下图描述简化版本的FPGA架构。

每个`Logic block`共有4个引脚，其中，引脚1和2与左边相邻通道的所有轨道连接，引脚3和4与上边相邻通道的所有轨道连接，通道的轨道数即为通道的宽度W。

<img width=400 alt="switch-block" src="/VLSI-FPGA/lab3/img/arch.png" style="margin:auto; display:flex;">

开关块(switch block)是双向的，使用Wilton拓扑连接水平和垂直方向的导线，其中W为通道宽度。

从左到右和从右到左保持相同的轨道序号，具体线路编号和连接规则如下图所示：
* 从左到上则是`i`到`W-i`
* 从上到右则是`i`到`(i+1)%W`
* 从右到下则是`i`到`(2W-2-i)%W`
* 从下到左则是`i`到`(i+1)%W`

<img width=700 alt="route-track" src="/VLSI-FPGA/lab3/img/routing_tracks.png" style="margin:auto; display:flex;" />

## 代码说明

为了降低同学们非核心算法的代码量，助教为各位同学提供了一个初始代码，你只需要实现一个布线算法。

初始代码包括了`FPGA`、`FpgaTile`、`Design`、`Net`、`RRNode`等基本类，你需要在`Solution.cpp`中实现你的算法，然后在`main.cpp`中调用你的算法。

* `main.cpp`：主可执行文件，需要两个命令行参数——电路文件的路径和通道布线宽度。
* `Design.cpp/.h`：包含设计中所有线网的类。
* `FPGA.cpp/.h`：包含FPGA大小，通道宽度和一个包含所有FPGA块的列表，`getNumSegmentsUsed`函数可以获得routing segments的数量。
* `FpgaTile.cpp/.h`：表示FPGA块的类，包含指向相邻FPGA块的指针，以及指向块中`RRNode`引脚和导线的指针，这里的FPGA块包括开关块，开关块右边的导线`hWire`，开关块下面的导线`vWire`，以及`logic block`（只有开关块的右边和下面都有开关块的时候才存在）的4个`cbWire`。
* `Net.cpp/.h`：表示线网的类，包含一个源`RRNode`和目标`RRNode`列表。
* `RRNode.cpp/.h`：表示单个布线资源节点（导线或引脚）的类，带有指向所有连接的`RRNode`的指针。要使用`RRNode`分配一个线网进行布线，你可以调用`RRNode->setNet()`。
* `Solution.cpp/.h`：包含一个`Router`空类，你需要在此基础上实现一个`MyRouter`类，**并实现你的布线算法**，你需要为每个线网分配相应的`RRNode`。

在`Design.cpp`中以下函数`verifyRouting()`会验证每一条Net是否正确连接，通过观察`verifyRouting()`的行为可以确定你要做的事情。函数实现如下所示：

```c++
bool Net::verifyRouting() {
    set<RRNode *> nodesReached;
    list<RRNode *> nodesToVisit;

    if(source.getNet() != this) { // 检查source引脚是否属于本Net，本质是在检查source这个RRNode类的Net*属性是否指向自己
        cout << "**Net source " << source << " is not marked as belonging to net " << idx << endl;
        return false;
    }
    else {
        nodesToVisit.push_back(&source);
    }

    while(nodesToVisit.size()) { // 依次检查从source出发的链路
        RRNode *node = nodesToVisit.front();
        nodesToVisit.pop_front();
        nodesReached.insert(node); // 把访问过的RRNode资源标记为已访问

        for(auto connection : node->getConnections()) {
            if(connection->getNet() == this && (nodesReached.find(connection) == nodesReached.end())) {
                // 与当前node相连的RRNode必须也属于本Net
                // && 后的代码是去掉已访问的RRNode资源
                nodesToVisit.push_back(connection);
            }
        }
    }

    // 最后检查当前Net所有需要连接的引脚是否均已经连接
    for(auto sink : sinks) {
        if(nodesReached.find(sink) == nodesReached.end()) {
            cout << "***Net " << idx << " with source " << source << " did not reach sink: " << *sink << endl;
            return false;
        }
    }

    return true;
}
```
<mark>布线算法只能依次设定FPGA上RRNode资源所属的Net。</mark>RRNode之间的连接关系已经确定，不可以修改。

### 数据集

下载链接：[校内链接(circuits.zip)](http://172.18.233.211:5244/d/VLSI%E8%AF%BE%E4%BB%B6/dataset/routing/circuits.zip?sign=_PReUHaMMGRJNm3A7aqg-KvFcuOpxh4_QY-SNmCw25A=:0)和[校外链接(lab3_benchmark.zip)](https://github.com/Customized-Computing/VLSI-FPGA/releases/download/lab3/lab3_benchmark.zip)。

数据集大小如下图所示：

| 数据集名称  | 网格大小 | 线网数量 |
| ----------- | -------- | -------- |
| huge        | 40       | ~900     |
| xl          | 30       | ~490     |
| large_dense | 20       | ~400     |
| lg_sparse   | 20       | ~140     |
| med_dense   | 12       | ~140     |
| med_sparse  | 12       | ~50      |
| small_dense | 6        | ~20      |
| tiny        | 4        | ~10      |

### 程序运行方法

1. 手动编译运行

```bash
g++ -std=c++17 -o main main.cpp Design.cpp FPGA.cpp FpgaTile.cpp Net.cpp RRNode.cpp Solution.cpp
./main.exe ./circuits/tiny 12
```

2. 使用`makefile`脚本编译运行

```bash
make all
```

3. 兼容Vscode的`F5运行并调试`功能：

操作方式类似于实验1，在`.vscode/launch.json`中配置`args`参数，使其适应lab3程序的参数需求即可。

## 输入文件格式

本节内容面向需要自行编写数据读取模块的同学。

* 第一行由一个整数n组成，其中n表示n×n的logic blocks网格，网格单元在每个维度中从0到n-1进行编号。

* 接下来的行的格式为：`XS YS PS XD1 YD1 PD1 XD2 YD2 PD2 ...`，其中XS，YS表示源点的坐标，PS表示源点的引脚，XD1，YD1表示目标点的坐标，PD1表示目标点的引脚。当读取到`-1 -1 -1 -1 -1 -1 `时停止。

示例输入文件：

```text
10                  表示(10 x 10)网格 
1 2 4 2 3 2         (1,2)块的引脚4连接(2,3)块的引脚2
0 0 4 1 2 3         (0,0)块的引脚4连接(1,2)块的引脚3
0 0 4 1 2 3 4 4 1   (0,0)块的引脚4连接(1,2)块的引脚3和(4,4)块的引脚1
-1 -1 -1 -1 -1 -1   表示读取终止
```

## 输出文件格式

要求布线算法的输出是一个文件，命名格式为`benchmark_name_routing.txt`，如`tiny_routing.txt`。

输出文件为两行，第一行为布线通道宽度，第二行为routing segments的数量，例如：

```text
12
48
```

## 如何提交

实验报告命名为**学号\_姓名\_第三次作业.pdf**。

发送到助教邮箱（可在主页找到）<br>
<mark>截止日期：2025年6月19日23时59分</mark><br>
后期会统计已经收到作业的同学，并发在群里。如果上传作业后有更新，请命名为V2、V3……，并在助教统计作业上交情况时注意是否收到最新版本。

