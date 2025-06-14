# 大作业

## 大作业内容

从已有的四个大作业方向(划分、布图、布局、布线)选择一个，完成其中部分或全部的要求，并写作一篇8页左右的论文作为实验报告上交。
> 你也可以选择发在群里的比赛题目作为大作业的选题。

* 论文模板为latex模板，在这个链接给出[IEEE格式论文模板-校内下载链接](http://172.18.233.211:5244/d/VLSI%E8%AF%BE%E4%BB%B6/dataset/conference-latex-template.zip?sign=DdYSLcB8FEa9w1W-OFYdcRvbNmgDwIfrpmnxwAWn6yA=:0)。

## 大作业要求

### 评价指标

大作业占本课程总成绩的60%，以下是大作业的基本评价指标，望同学们仔细阅读并重视。

评价体系分为两部分，代码部分(占25分)+论文部分(35分)。
* 代码部分
  * (10分)代码可执行(就能拿到6分)。
  * (5分)代码质量，模块化/关键代码注释。
  * (10分)优化实现(二选一)
    * (10分)对比基线方法有特定指标改进，如线长、面积等等(有提高就能拿到8分以上)。
    * (10分)运行效率改进，如并行化、访存加速等等(有提高就能拿到8分以上)。
* 论文部分
  * (15分)结构与逻辑
    * (4分)论文结构完整(摘要/引言/方法/实验/结论共5个章节都有)，可根据实际需求进行适当扩展章节数量。
    * (3分)研究的问题准确描述和定义。
    * (3分)引言研究动机的合理性，例如为什么做出以下创新？观察到现有方法存在什么问题。
    * (5分)逻辑连贯性，观察到的问题，引出对应的方法，从方法引出结果。需要写明针对观察到的问题，提出怎样改进，这些改进如何在结果中展现。
  * (10分)实验分析
    * (4分)实验设计合理性。
    * (6分)理论与理论分析匹配度。
  * (10分)学术规范
    * (4分)引用文献的规范，正确引用文献在2022年后且大于等于3篇。
    * (6分)论文长度符合要求。

<mark>论文长度要求</mark>：例如在第8页第二列文字超过中线的一半才算论文有第8页。<br>
建议论文章节长度安排，摘要+引言1页半到2页半、方法2页到3页、实验+结论2页、引用1页。<br>
下图是一个论文长度不规范的示例。

<img width=300 alt="论文长度不足示例" src="/VLSI-FPGA/advanced/img/paper-length-rule.png" style="margin: auto; display: flex;">

### 如何提交

大作业上交时一同上交前三次普通作业的代码，每份代码用一个单独的文件夹存放。然后压缩成"学号-姓名-大作业.zip"文件夹上交。

助教打开压缩包时希望见到的文件目录是下图所示，<mark>不要把数据集打包进来，而应该在README.md中写明如何存放数据集，然后运行你的程序</mark>，另外在每份实验报告内都写上自己的姓名和学号。

```bash
-***.zip
|--- lab1/
|   |--- main.cpp
|   |--- xxx.cpp
|   |--- MakeFile
|   |--- README.md // 记录如何复现你的实验结果
|   |--- run.sh // 或者直接给出对应的运行脚本更佳
|   |--- 实验报告.pdf
|--- lab2/
|   |--- main.cpp
|   |--- xxx.cpp
|   |--- Makefile
|   |--- README.md
|   |--- 实验报告.pdf
|--- lab3/
|   |--- main.cpp
|   |--- ...
|--- labFinal/
    |--- 大作业论文.pdf
    |--- ...
```

发送到助教邮箱（可在主页找到）<br>
<mark>截止日期：2025年6月30日23时59分</mark><br>
后期会统计以及收到作业的同学，并发在群里。如果上传作业后有更新，请命名为V2、V3……，并在助教统计作业上交情况时注意是否收到最新版本。

