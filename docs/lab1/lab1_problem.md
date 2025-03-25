# 实验1

## 简介

在本次实验中，你将设计一个图划分算法，输出两个划分$V_1$和$V_2$，并且$V_1$和$V_2$之间的割代价尽可能小。对于每个划分$V_i$，需要满足：
$$
\frac{1}{2}-\epsilon \le \frac{|V_i|}{|V|} \le \frac{1}{2}+\epsilon
$$
其中，$\epsilon=2\%$。$|V|$表示图顶点的数量。

* 实现你的算法，但**不提交**代码。
* **提交**实验报告说明你是如何做的。实验报告应该包含以下内容
  * 你的算法逻辑和实现思路
  * 你的算法运行结果截图
  * 实验总结

## 代码说明

为了降低同学们非核心算法的代码量，助教为各位同学提供了一个初始代码，你只需要实现一个图划分算法。

初始代码包括了Graph，Node和Net的基本类。你需要在`solution.cpp`内部实现你的算法，然后在`main.cpp`中调用你的算法。

* `main.cpp`：主可执行文件，需要一个命令行参数——电路文件的路径。
* `solution.cpp/.h`：表示解决方法的类，里面包含一个`read_benchmark`函数用于读取电路文件和构造网表。需要在这实现图划分算法。
* `Graph.cpp/.h`：表示图的类，包含图中顶点的集合和边的集合。
* `Node.cpp/.h`：表示顶点的类，其中有一个顶点连接的边的列表。
* `Net.cpp/.h`：表示边的类，其中有一个边连接的顶点的列表。
* `evaluate.cpp`：包含一个`calculate_cut`函数，用于计算两个划分的割。一个`evaluate`函数，用于评价划分结果。
> 助教们本来想写成一个单独的checker程序，用来评价同学们划分结果的好坏。后来觉得普通作业没有必要验证同学们的结果，于是就留下evaluate的实现，而没有完整的checker程序。

下面是如何访问Node列表和Net列表的示例：

访问图中的顶点信息示例

```cpp
vector<Node *> nodes = graph.get_nodes();
for(const auto &node : nodes) {
    cout << node->get_index() << ": ";
	for(const auto &net : node->get_nets()) {
        cout << net->get_index() << " ";
    }
    cout << endl;
}
```

访问图中边的信息示例

```cpp
vector<Net *> nets = graph.get_nets();
for(const auto &net : nets) {
    cout << net->get_index() << ": ";
	for(const auto &node : net->get_nodes()) {
        cout << node->get_index() << " ";
    }
    cout << endl;
}
```



### 测试集

下载连接：[校内链接](http://172.18.233.211:5244/VLSI%E8%AF%BE%E4%BB%B6/dataset)和[校外链接](https://github.com/Customized-Computing/VLSI-FPGA/releases/tag/lab1)

`ISPD_benchmark.zip`数据集中电路的大小如下表所示：


| Benchmark | 顶点数量  | 边数量  |
| --------- | ------ | ------ |
| IBM01     | 12752  | 14111  |
| IBM02     | 19601  | 19584  |
| IBM03     | 23136  | 27401  |
| IBM04     | 27507  | 31970  |
| IBM05     | 29347  | 28446  |
| IBM06     | 32498  | 34826  |
| IBM07     | 45926  | 48117  |
| IBM08     | 51309  | 50513  |
| IBM09     | 53395  | 60902  |
| IBM10     | 69429  | 75196  |
| IBM11     | 70558  | 81454  |
| IBM12     | 71076  | 77240  |
| IBM13     | 84199  | 99666  |
| IBM14     | 147605 | 152772 |
| IBM15     | 161570 | 186608 |
| IBM16     | 183484 | 190048 |
| IBM17     | 185495 | 189581 |
| IBM18     | 210613 | 201920 |

### 程序运行方法

1. 手动编译运行：

```bash
g++ -o main main.cpp solution.cpp Graph.cpp Net.cpp Node.cpp
./main benchmark_file
```

2. 使用`makefile`脚本编译运行（需要Linux环境）：
> 助教们推荐同学们学习如何编写`makefile`脚本，这对于日后工程开发非常有用。
> 
> cmakefile也是一个非常好用的脚本，但是助教们不推荐使用，对于这样一个简单的程序来说，cmake的学习成本有些过于高昂了。如果同学们学有余力，可以尝试把这个项目改造成一个cmake项目。
```bash
make all
./main benchmark_file
```

3. 兼容Vscode的`F5运行并调试`功能：

我们需要创建两个配置文件告诉Vscode如何执行项目的Debug工作。
1. 创建一个文件夹`.vscode`和两个文件`launch.json`和`task.json`。
2. `launch.json`填写以下内容：
> 注意`args`中的ibm01.hgr路径是否和你实际存放位置一致。
> 助教们本地测试设置的Vscode的工作路径是`~/VLSI-FPGA/lab1`，如果你的路径不是这个，请自行修正。

```json
{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
        "configurations": [
        {
            "name": "g++ - Build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${cwd}/main",
            "args": [
                "${cwd}/benchmark/ibm01.hgr"
            ],
            "stopAtEntry": false,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "build",
            "miDebuggerPath": "/usr/bin/gdb"
        }
    ]
}
```
3. `tasks.json`填写以下内容：

```json
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "make",
            "type": "shell",
            "command": "make",
            "args": [
                "all"
            ],
            "options": {
                "cwd": "${cwd}"
            }
        },
        {
            "label": "build",
            "dependsOn": ["make"]
        }
    ]
}
```

## 输入文件格式

> 如果你对于助教们写的数据读取模块性能不够满意，或者不支持你的奇思妙想，你可以自己写一个数据读取模块。

本章介绍的内容仅面向需要自行编写数据读取模块的同学。

第一行包括两个数字，第一个数字代表边的数量，第二个数字代表顶点的数量，<mark>顶点的编号从1开始</mark>。

下面每一行代表一条超边连接的顶点，一行可能会有多个数据：

```
edge_num node_num
node1 node2
node1 node2 ... noden
```


## 输出文件格式

要求图划分算法的输出是一个文件，命名格式为`benchmark_name_partition.txt`，例如`ibm01_partition.txt`。

每一行代表顶点划分的类，0代表划分到X，1代表划分到Y，格式如下：

```
0
1
1
0
...
```

## 如何提交

实验报告的命名格式为**学号\_姓名\_第一次作业.pdf**。

发送到助教邮箱：wangzh523@mail2.sysu.edu.cn<br>
后期会统计已经收到作业的同学，并发在群里。如果上传作业后有更新，请命名为V2、V3……，并在助教统计作业上交情况时注意是否收到最新版本。