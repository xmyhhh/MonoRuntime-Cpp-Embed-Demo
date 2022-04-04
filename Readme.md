## Introduction

A demo of a c++ embedded Mono runtime calling C# exposed methods for studying the scripting mechanism of the Unity engine

[中文文档](./Readme_chinese.md_)
## Dependencies

- Mono [download address](http://www.mono-project.com/download/)

> Note that I have copied the Mono x64 runtime library to the `\dependency\mono` directory, so only the C++ code can be compiled without installing Mono.
I have compiled the C# code in advance to generate MainTest.dll, so you still need to install Mono in order to recompile the C# code.

## Compiler's Guide
### C++ compile to generate exe needs to be configured as follows.

* Compile include:
\\dependency\mono\include\mono-2.0`

* Linker lib path:
`\dependency\mono\lib`

* Linker lib:
`mono-2.0-sgen.lib`


### C# compile to generate dll (On Windows)
* After installing Mono, add the \Mono\bin` folder to the PATH of the environment variable
* 64-bit installation will be completed in: C:\Program Files\Mono\bin. 32-bit in C:\Program Files (x86)\Mono\bin
* In cmd go to the directory where the Program.cs file is stored
  
* mcs Program.cs -t:library


## Running Guide
If you encounter the error that the dll cannot be found, here I list a few possible solutions
#### How can I solve the problem of not finding mono-2.0-sgen.dll?

The file `mono-2.0-sgen.dll` is actually in the `\dependency\mono\lib` directory, a few solutions.
* Install Mono: `mono-2.0-sgen.dll` will be registered in the system when you install Mono, and the program can find the dll automatically, as follows
`"Simple-Demo.exe"(Win32): "C:\Program Files\Mono\bin\mono-2.0-sgen.dll" has been loaded. Symbols have been loaded. \ If you don't want to install Mono, you can take the following approach

* Copy mono-2.0-sgen.dll to the same directory as `Simple-Demo.vcxproj`: vs studio will add the directory where the `.vcxproj` file is located to the debug object's environment when debugging, so that `mono-2.0-sgen.dll` can be found and you can see the program in my case Normal loading dll `"Simple-Demo.exe"(Win32): loaded "C:\Users\xmy\Desktop\MonoRuntime-Cpp-Embed-Demo\Simple- Demo\mono-2.0-sgen.dll"`

#### How to solve the problem of not finding mscorlib.dll?
* The directory set by `mono_set_dirs(monoLibPath.c_str(), monoEtcPath.c_str())` is not correct, please set the first parameter to `/dependency/mono/lib`

