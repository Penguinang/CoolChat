## Compile
1. Server
* 下载安装 `maven`
* 在server目录内执行`mvn test -U -e`命令运行单元测试，并编译
* 编译生成的类在target目录内
* 运行: mvn exec:java -Dexec.mainClass=CoolChat.Server.App

2. Client    
    2.1 依赖: CxxJDK, CxxMina, CxxLog4j，这三个项目都可以在 [CxxJava](https://github.com/cxxjava) 的github找到。本项目使用了静态链接库的方式使用这三个项目。所以应该先对这三个项目下载下来进行编译，然后打包为静态链接库，再放在 Netmodule 的lib目录下，准备妥当后使用 本项目提供的makefile文件进行编译。关于编译这三个项目还有点小问题，在后面几点中说明   
    2.2 CxxJDK/efc/libc/inc/eso_canonicalize.h 中定义 canonicalize 函数和标准库的一个函数名字相同，参数不同，但是编译器报错了 `/usr/include/bits/mathcalls.h:379:1: conflicting declaration of C function ‘int canonicalize(double*, const double*)’`，于是直接注释了这个，发现还是可以的。   
    2.3 使用 cxxmina 过程中，发现了一个问题，cxxmina 和 qt 都有一个 uchar 的定义，而且都在头文件里，qt定义使用typedef， cxxmina使用#define，因此有冲突。可以直接将 #define 或typedef 去掉，保存一个即可，改掉cxxmina更简单。在 EBase.hh:188行中。   
    2.4 在qt里QString类定义了一个静态常量变量 null, 在cxxmina里定义了一个宏 #define null nullptr，这个就很麻烦了，改cxxmina的话要改很多文件，改qt也有改很多。想到一个不错的方法，使用static void* null 代替宏定义，这样作为全局变量在qt的类内会被类内变量遮蔽，static 保证在其他编译单元内无法引用。这个在 Ebase.hh:152行 中。   
    2.5 主要的问题就是上面三点，第一点是可能是作者的问题，第二三点是qt和cxxmina的兼容问题。   
    2.6 上面三个项目每个都有静态链接库，其中cxxmina和log4j分别有一个，需要自己手动打包，cxxjdk有两个，作者已经编译好了，直接复制就行。除了这三个项目的库之外，还需要把 本项目中的NetModule部分进行编译打包。编译方法，在netmodule的test中有一个makefile，运行 make lib，会生成库并复制到lib中。   
    2.7 上面所有都准备好之后，进入 CoolChat的qt项目，make编译，即可。   

3. TODO   
    3.1 :heavy_check_mark: ~~`TODO`~~ 注意，暂时登录界面显示之前会先连接服务器，所以如果服务器没有运行，就不会显示，这个后面还要改。    
    3.2 :heavy_check_mark: ~~`TODO`~~ 数据库使用了本地的mysql，但是还没有重建~~  
    3.3 :heavy_check_mark: ~~`TODO`~~  ~~在客户端中大量使用回调，而且类型是很变态的bind返回的类型，应该想办法改掉。~~   原来可以直接用function    
    3.4 `TODO` 服务器的地址不应该直接写死在代码里，要改。    
      
    
本项目使用了 CxxMina 项目,
谢谢 [CxxJava](https://github.com/cxxjava) 提供的 CxxMina 实现和其他依赖