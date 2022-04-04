## 简介

一个 c++嵌入 Mono 运行时调用 C#暴露的方法的 demo，用于研究 Unity 引擎的脚本机制

## 依赖

- Mono [下载地址](http://www.mono-project.com/download/)

>注意，我已经把 Mono 的 x64 运行库相关文件拷贝到了`\dependency\mono` 目录下，因此仅编译C++代码可以不用安装 Mono。
C#代码我已经提前编译好生成MainTest.dll了，要想重新编译C#代码仍然需要安装 Mono

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
如果遇到找不到dll的错误，这里我列出几个可能的解决方案
#### 如何解决找不到mono-2.0-sgen.dll？

`mono-2.0-sgen.dll`这个文件其实就在`\dependency\mono\lib`目录下，几个解决方法：
* 安装Mono：安装Mono的时候`mono-2.0-sgen.dll`会被注册在系统中，程序可以自动找到dll，如下
`“Simple-Demo.exe”(Win32): 已加载“C:\Program Files\Mono\bin\mono-2.0-sgen.dll”。已加载符号。` 如果你不想安装Mono，可以采取下面的方法

* 把mono-2.0-sgen.dll复制到和`Simple-Demo.vcxproj`同目录：vs studio在调试的时候，会把`.vcxproj`文件所在的目录加入调试对象的环境，这样`mono-2.0-sgen.dll`就可以被找到，在我这里可以看到程序正常加载dll`“Simple-Demo.exe”(Win32): 已加载“C:\Users\xmy\Desktop\MonoRuntime-Cpp-Embed-Demo\Simple-Demo\mono-2.0-sgen.dll”`

#### 如何解决找不到mscorlib.dll？
* `mono_set_dirs(monoLibPath.c_str(), monoEtcPath.c_str())`设置的目录不对，第一个参数请设置为`/dependency/mono/lib`


