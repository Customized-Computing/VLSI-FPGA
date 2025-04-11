# floorplan——进阶

<mark>注意：进阶要求是面向大作业，如果同学们选择布图规划作为大作业内容时，需要完成以下要求</mark><br>
<mark>注意：连同代码和论文一起提交，并且写一个简要的README文件，说明如何复现你的实验结果。</mark><br>
在这个实验中，你需要实现一个布图规划(floorplan)算法。
> 和其他大作业不同，本课题仅需要实现一个新算法的一个部分。<br>
> 你可以结合现有的开源代码实现，把你的奇思妙想和现有开源算法结合，得到一个不错的floorplan算法实现。<br>
> 你也可以设计LLM-in-loop的框架，尝试结合LLM与floorplan算法。

你需要完成以下课题之一。


## 1. 快速质量评估算法

> 这个课题不要求单独实现一个布图算法，可以结合现有的开源代码实现，
> 把你的质量评估算法实现嵌入到现有的floorplan优化算法中。<br>
> 你需要在你的论文报告中提到你的实现基于哪篇论文的算法。

你需要实现一个布图质量评估的算法，要求估计质量准确，效率高。评估指标一般有以下几种，需要在其中一种或多种预估准确度有提高，且其他预估指标没有显著下降：
1. 空白面积(whitespace)，即芯片布局中出现的无法利用的空白区域面积。
2. 布线长度(wirelength)，即芯片布局中所有线网的长度之和。
3. feedthrough数量，即net穿越模块A，但不与模块A产生任何的联系的线网数量。
4. 预估算法的运行速度。

难点：准确**高效**预估feedthrough、线长和空白面积。平衡效率和预估。

## 2. floorplan算法

> 这个课题要求从布图算法本身出发，优化已有的开源代码实现，
> 也可以是自己从头开始实现的新算法。

你需要实现一个优化后的布图规划算法，要求在其他指标不恶化（例如线长、芯片面积等）的前提下，完成以下一个或多个目标：
1. 减少空白区域面积。
2. 减少布线长度。
3. 减少feedthrough数量。
4. 提升优化算法的运行速度。

难点：大型宏模块与小型模块的混合布局，多阶段分层处理时不能考虑到后续的优化，导致结果的局部最优。<br>
如何让布图规划算法感知到feedthrough的存在，并进行相关优化。

## 3. LLM-in-loop实现

提出一种LLM-in-loop的大模型布图规划工具，实现任务拆解、布图工具调用、布图质量分析、优化迭代等功能。<br>
可参考文献[《Towards LLM4Floorplan: Agents Can Do What Engineers Do in Chip Design》](https://openreview.net/forum?id=n7s9EwG6hW)[《ChipNeMo: Domain-Adapted LLMs for Chip Design》](https://arxiv.org/abs/2311.00176)

你需要结合LLM与floorplan算法，实现一个LLM-in-loop的布图规划工具，完成以下一个或多个目标：
1. LLM能够理解用户的指令含义，并做出正确的工具调用和优化。
2. LLM能接受工具的反馈，与用户指令需求进行比较，自行决定是否进一步优化。
3. LLM能根据用户指令，自动拆解任务，完成任务的优化。

难点：LLM的理解能力、工具调用的准确性、任务拆解的准确性、优化迭代的准确性。

## 附录

介绍一些基本背景和知识点，方便同学们更好地理解本课题，减少同学们的学习成本。

### FeedThrough

对于一个复杂的芯片设计，网表会被划分成多个具备一定功能的块(Block)，这些块按照一定的顺序连接实现芯片功能。
但是，因为一些设计布局的原因，互联的块在空间上不能相邻，为了数据能够在互联的块之间传输，需要建立一些 FeedThrough Path。

> 假设模块A与模块C之间存在许多的互联线路，net 1是其中一条。而模块B在布局空间上恰好处在模块A和模块C之间，此时 net 1 经过模块B，但没有与模块B产生任何的联系。我们就称 net 1 是 FeedThrough Path。

为了正确互联模块A和模块C，一种方法是在布线阶段，绕过模块B，在模块B周围找到合适的布线资源，如下图所示。

<img width=400 alt="feedthrough-path-routing" src="/VLSI-FPGA/advanced/./img/feedthrough1.png" style="margin: auto; display: flex;">

另一种方法则是使用模块B的端口创建 FeedThrough Path，如下图所示，模块A先连接到模块B上，然后由模块B中转再连接到模块C上。此时模块B上用于创建 FeedThrough Path 的端口称为 FeedThrough Port。模块B的功能不会影响 FeedThrough Port 的输出，就好像线网没有连接到模块B上。

<img width=400 alt="feedthrough-path-block" src="/VLSI-FPGA/advanced/./img/feedthrough2.png" style="margin: auto; display: flex;">

创建 FeedThrough Path 的优点：
* 减少布线资源的使用，从而降低模块的布线拥塞。
* 功耗优化。
* 芯片面积优化。

使用 FeedThrough 的缺点：
* 如果模块B附近有很多的 FeedThrough Path，那么会在模块B附近引起布线拥塞。
* 模块B引入的延迟可能导致数据一致性问题，需要在网表中引入寄存器解决这个问题。

### 数据集

以`GSRC.zip`为例，包含HARD和SOFT两个文件夹，代表硬模块的floorplan设计和软模块的floorplan设计。
> 同学们可以先实现硬模块的布图规划算法，然后实现软模块的布图规划。

数据集下载链接：[GSRC校外链接](http://vlsicad.eecs.umich.edu/BK/GSRCbench/)和[MCNC校外链接](http://vlsicad.eecs.umich.edu/BK/MCNCbench/)。[校内链接](http://172.18.233.211:5244/VLSI%E8%AF%BE%E4%BB%B6/dataset/floorplan)。

`GSRC.zip`数据集有n10，n30，n50，n100，n200，n300一共6个Benchmark。每个设计包含blocks文件，nets文件以及pl文件。<br>
`MCNC.zip`数据集有ami33，ami49，apte，hp，xero一共5个Benchmark。每个设计包含blocks文件，nets文件以及pl文件。<br>

blocks文件示例

```
UCSC blocks 1.0

NumSoftRectangularBlocks : 10	# 硬模块数量
NumHardRectilinearBlocks : 0	# 软模块数量
NumTerminals : 69				# 端口数量

sb0 softrectangular 16318 0.300 3.000	# 模块id 模块类型（软模块） 软模块面积 长宽比下限 长宽比上限
bk1 hardrectilinear 4 (0, 0) (0, 133) (336, 133) (336, 0) # 模块id 模块类型（硬模块） 顶点数 各个顶点的相对坐标
...

p1 terminal	# 端口id 端口标志 （注意terminal模块没有长宽，但在pl文件内规定布局位置）
...

```

nets文件示例

```
UCLA nets 1.0

NumNets : 118	# 连接数量
NumPins : 248	# 引脚数量

# 下面定义每个连接的度数以及连接的部分
NetDegree : 2 # 这个 Net 连接了 2 个引脚
p1 B # 引脚id （后面的B与本实验无关，可以不用理会）
sb6 B # 引脚id
NetDegree : 2
p2 B
sb8 B
...
```

pl文件示例，在`.blocks`文件中标记为`terminal`的模块不可以移动位置，其余模块可以移动位置。<br>
注意：pl文件内给出模块的布局位置，但是不一定是最优的布局位置。

```
UCSC blocks 1.0
# 定义了每个模块和每个端口的坐标位置
sb0	152	284 # 模块id 模块x坐标 模块y坐标
...
sb10 198 89

# ↑这里会有一个空行，表示下面都是terminal模块的位置
p1	0	900
...

```

### Baseline

最优解取自论文[《FTAFP: A Feedthrough-Aware Floorplanner for Hierarchical  Design of Large-Scale SoCs》](https://dl.acm.org/doi/10.1145/3658617.3697728)。

> 离baseline越近，对于你的大作业成绩是有好处的。

| 数据集 | HPWL | Feed through 数量 |
| --- | --- | --- |
| n10   | 43,625 | 138 |
| n30   | 142,507 | 454 |
| n50   | 182,524 | 744 |
| n100  | 304,584 | 1,358 |
| n200  | 549,286 | 2,802 |
| ami33 | 93,674  | 152   |
| ami49 | 1,047,228 | 597 |