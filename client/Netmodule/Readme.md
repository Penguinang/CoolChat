1. 使用 cxxmina 过程中，发现了一个问题，cxxmina 和 qt 都有一个 uchar 的定义，而且都在头文件里，qt定义使用typedef， cxxmina使用#define，因此有冲突。
    可以直接将 #define 或typedef 去掉，保存一个即可，改掉cxxmina更简单。
    188行 EBase.hh
2. 在qt里QString类定义了一个静态常量变量 null, 在cxxmina里定义了一个宏 #define null nullptr，这个就很麻烦了，改cxxmina的话要改很多文件，改qt也有改很多。想到一个不错的方法，使用static void* null 代替宏定义，这样作为全局变量在qt的类内会被类内变量遮蔽，static 保证在其他编译单元内无法引用
    152行 Ebase.hh