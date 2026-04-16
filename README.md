# VLSI-FPGA
VLSI课程作业代码仓库。

对应课程网页[链接](https://customized-computing.github.io/VLSI-FPGA/)。

## 内容
本课程的作业由 4 个任务组成：
1. [图划分算法实践](https://customized-computing.github.io/VLSI-FPGA/#/lab1/lab1_problem)
2. [布局算法实践](https://customized-computing.github.io/VLSI-FPGA/#/lab2/lab2_problem)
3. [布线算法实践](https://customized-computing.github.io/VLSI-FPGA/#/lab3/lab3_problem)
4. [大作业](https://customized-computing.github.io/VLSI-FPGA/#/labFinal)

> 链接给出各自实验的具体要求。

# 🔨开发人员

> 面向后面接手这个项目的助教，或其他参考本项目的课程代码设计实践。

## 文档Web搭建

采用[docisfy](https://docsify.js.org/)部署文档静态网页。<br>
需要使用NPM进行安装，[NPM安装](https://npm.nodejs.cn/cli/v11/configuring-npm/install)这里找到对应版本，本项目使用nodejs的版本为`v22.11.0`，npm的版本为`11.1.0`，docsify的版本为`4.13.1`。

使用`npm install docsify`安装docsify包，安装完成后在终端执行以下指令：
```shell
docsify
```
如果出现以下内容说明安装完成：
```shell
Usage: docsify <init|serve> <path>

Commands:
  docsify init [path]      Creates new docs                         [aliases: i]
  docsify serve [path]     Run local server to preview site.        [aliases: s]
  docsify start <path>     Server for SSR
  docsify generate <path>  Docsify's generators                     [aliases: g]

Global Options
  --help, -h     Show help                                             [boolean]
  --version, -v  Show version number                                   [boolean]

Documentation:
  https://docsifyjs.github.io/docsify
  https://docsifyjs.github.io/docsify-cli

Development:
  https://github.com/docsifyjs/docsify-cli/blob/master/CONTRIBUTING.md


[ERROR] 0 arguments passed. Please specify a command
```

这时候cd到库的`/docs`目录下，使用指令`docsify init`初始化目录，然后执行`docsify s`在本地启动web服务，打开`http://localhost:3000`就可以看到文档了。

### 插入图片

建议按照html写法插入图片。其中用`[]`括起来的部分根据实际情况填写。需要在本地检查确定图片插入正常，大小合适。
```markdown
<img width=[250] alt="[any-title]" src="[/lab1/img/xxx.jpg]" style="margin:auto; display:flex;">
```
<mark>注意</mark>，正式部署前需要在所有的`src`关键字插入远程库名以保证部署后能正确引用图片。<br>
例如本代码仓库的名字叫做`VLSI-FPGA`，假设图片在本地部署时路径为`/lab1/img/xxx.jpg`（注意是相对路径），那么改成以下形式：
```markdown
<img width=250 alt="any-title" src="/lab1/img/xxx.jpg" style="margin:auto; display:flex;">
改成以下形式
<img width=250 alt="any-title" src="/VLSI-FPGA/lab1/img/xxx.jpg" style="margin:auto; display:flex;">
```

> 此时本地预览会提示图片路径错误，这是正常的。因此务必确保在本地预览时图片正确显示，然后再修改src关键字。<br>
> 建议新章节除了文件标题用一级标题外，其他位置不使用一级标题。

### 加入新章节

假设将来有作业4，在docs目录下创建一个`lab4`文件目录，在`lab4`内部创建`img`目录用于存放lab4的图片，然后创建markdown文件。
形成的结构目录如下所示：
```shell
/docs
|--- ...
|--- lab3/
|    |--- img/
|    |--- lab3_problem.md
|--- lab4/
     |--- img/
     |--- lab4_problem.md
```

然后为新章节加入访问入口。打开`/docs/_sidebar.md`文件，找一个合适的位置添加入口，并添加连接。

### 修改主页

打开`/docs/README.md`文件，修改其中内容。

### 其他显示设置

比如修改侧边栏的标题层级、主题等，建议参考[docsify文档](https://docsify.js.org/#/)。

## 代码部分

检查对应作业文档。
