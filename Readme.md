## 简介

一个 c++嵌入 Mono 运行时调用 C#暴露的方法的 demo，用于研究 Unity 引擎的脚本机制

## 依赖

- Mono [下载地址](http://www.mono-project.com/download/)

>注意，我已经把 Mono 的 x64 运行库文件拷贝到了`\dependency\mono` 目录下，因此仅编译C++代码可以不用安装 Mono，但要编译C#代码到 dll 文件任然需要安装 Mono

## 编译指南
### C++编译生成exe需要配置如下：

* Compile include:
`\dependency\mono\include\mono-2.0`

* Linker lib path:
`\dependency\mono\lib`

* Linker lib:
`mono-2.0-sgen.lib`

### C#编译生成dll (On Windows)
* 安装Mono以后，把`\Mono\bin`文件夹添加到环境变量的PATH中
> 64位安装完成后将在：C:\Program Files\Mono\bin。32位在C:\Program Files (x86)\Mono\bin
* 在cmd中进入到存放Program.cs文件的目录
  
* mcs Program.cs -t:library
## 运行指南
直接运行大概率会报找不到dll的错误


## 说明

仅暂时保存一下代码，依赖的库和代码还需要再整理一下 ,有空再完善文档
