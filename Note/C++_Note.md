# C++笔记
## 开始
### C++和C的区别
- C强调算法，C++强调数据
- C面向过程，C++面向对象，过程编程首先要确定计算机采取的操作，然后使用编程语言来实现这些操作。
- OPP：面向对象编程
>struct student可以直接写为student
>C语言中：若有const int a = 10;
>①可以利用指向a的指针修改a的值
>②变长数组int arr[a]是会报错的
>
>C++中：若有const int a = 10;
>①被const修饰的变量a成为了真正的常量，无法被指针修改内容
>也不可被取地址,若强行取地址会临时开辟一片指针大小的空间
>②变长数组int arr[a]不会报错
>
>枚举不再能和整型值混为一谈
>
>定义一个引用和常变量一定要初始化
>
>引用的本质与常量指针类似
>
>const int *p1 
>int * const p1 常量指针，与引用类似
>
>void fun(int &a); === void fun(int &(*x))，a等价于*x
>
>fun(int a, int)	函数占位参数
>
### IDE:集成开发环境
- 如：Microsoft Visual C++，Apple Xcode
### Unix和Linux编译
- Unix：`CC file.C`
  - `./a.out`
- Linux: `g++ file .cpp`
  - `./a.out`
- a.out文件会被新生成的a.out所覆盖
### 标准头文件：iostream
- `#include <iostream>`
### C++的输入与输出
- 输入：`cin>>xx`
- 输出：`cout<<"hello world"<<endl`
  - cout可以智能识别输出类型，这个优点源自于C++的OPP
  - endl：换行，也可以使用C的\n包含在字符串中，如`cout<<"hello\n"`，区别是endl可以在程序继续运行前刷新输出，使缓冲区内的内容立即显示在屏幕上。
  ```c++
    #include <iostream>
    int main()
    {
        using namespace std;
        int carrots;
        cout << "How many carrots do you have?" << endl;
        cin >> carrots; //cin获取输入内容
        cout << "Now you have " //cout的拼接输出
            << carrots
            << " carrots."
            << endl;
        return 0;
    }
### 命名空间namespace
- 存在意义：为了避免已封装好的产品中，出现变量或函数重名的情况。
- 只有头文件没有.h后缀时，namespace的机制才会被启用，cout变量实际上是`std::cout`，endl实际上是`std::endl`
- 语法：
  - `using namespace std;`，在这句声明后的所有std变量都不需要加前缀来调用
  - `using std::xxx`，变量xxx在这句声明后被调用时无需加`std::`前缀
    - `using std::cout`
    - `using std::cin`
    - `using std::endl`
  - 如果不进行namespace声明，则在每次调用变量时需加前缀`std::xxx`
    - `std::cout`
    - `std::cin`
    - `std::endl`
### 运算符重载
- 如<<在C++中即可以表示插入，也能表示左移，这就是一个运算符重载的例子，还有像&的取地址和位与，*的解引用和乘以...这种一个符号有多重含义的就叫运算符重载。
### C++的代码格式化
- C++中，回车的作用和空格和制表符一样，为了排版方便才使用不同的效果。
### 为什么变量必须声明
- 方便编译器进行查错
# 处理数据
### 求变量类型的最大范围
- `#include <climits>`，包含该头文件即可使用下面宏定义使用数据范围
```c++
CHAR_BIT    //char的位数
CHAR_MAX    //char的最大值
CHAR_MIN    //char的最小值
SCHAR_MAX   //signed char 的最大值
SCHAR_MIN   //signed char的最小值
UCHAR_MAX   //unsigned char的最大值
SHRT_MAX    //short的最大值
SHRT_MIN    //short的最小值
USHRT_MAX   //unsigned short的最大值
INT_MAX     //int的最大值
INT_MIN     //int的最小值
UINT_MAX    //unsigned int的最大值
LONG_MAX    //long的最大值
LONG_MIN    //long的最小值
ULONG_MAX   //unsigned long的最大值
LLONG_MAX   //long long的最大值
LLONG_MIN   //long long的最小值
ULLONG_MAX  //unsigned long long 的最大值
```
### C++的初始化方式
```c++
方式1：int emus{7}; //可以不使用=进行赋值，{}称为大括号初始化器
方式2：int rheas(7);//同样可以赋值，但是用大括号会更严格
方式3：int num{};   //num的数据会被初始化为0
```
- 以{}初始化时进行的转换(C++11)
  - 与方式2相比，方式1对类型转换的要求更为严格，具体地说，列表初始化不允许缩窄，只要转换的变量大小可以被正确表达，那么就会被允许。例如：`char c{31325};`这样是不行的，因为超出了char的表示范围，数据无法被正确传递。
  - `char x = A; char c{x};`，这种语句是错误的，因为x在编译器眼中是一个变量，其值可以非常大，因此不被允许存在变量。
### 多种进制数的表示方式
- 如果数字常量的第一位为0，第二位为1~7，则判定为8进制
- 如果数字常量的第一位为1~9，则判定为10进制
- 如果前两位为0x或OX，则判定为16进制
- cout的进制输出方式
  - `cout<<hex` //以16进制输出
  - `cout<<oct` //以8进制输出
### C++如何确定常量的类型
- 默认所有的整型常量会以int型的身份被识别
- 2022L ——long
- 2022UL——unsigned long
- 2022LL——long long
- 2022f ——float
- 2022F ——float
- 20.20 ——double
- 20.2L ——long double
### C++字符类型
- 成员函数cout.put()  //cout为对象，put()为函数，它们都输入类的范围领域内
- `\b`：退格的转义代码
  - `cout << "Enter your agent code:________\b\b\b\b\b\b\b\b";`
- `wchar_t`,宽字符类型，它是一种整数类型，可以表示系统最大的扩展字符集，cout和cin将输入和输出看做char流，它不适用于处理wchar_t类型的数据，iostream可以使用wcin和wcout来处理wchar_t字符，另外，加上前缀L来指示字符常量和宽字符串，如：`wchar_t bob=L'p;'`，`wcout << L"tall"<<endl;`
- char16_t和char32_t
  - char16_t：无符号16位，可以加前缀u来表示，如：u'q'
  - char32_t：无符号32位，可以加前缀U来表示。
### 浮点数
- 计算机将浮点数分两部分保存，基数和放大倍数
- d.dddE+n表示小数右移n位，d.dddE-n表示小数左移n位，因此称之为浮点数。
- 可以从头文件cfloat或cfloat.h中查找浮点数的限制
- `cout.setf(ios_base::fixed, ios_base::floatfield); //使输出结果小数部分隐藏的0全部显示`
### 运算符优先级和结合性
- 见附录D，和C++ primer P51
### 类型分类和类型转换
- C++基本类型分类：
  - signed char，short，int，long统称为符号整型，它们的无符号版本同称为无符号整形，**符号整型和无符号整形统称为整型**，float，double，long double统称为浮点型。**整数和浮点型统称为算数类型**
- 类型转换：
  - 变量进行赋值时，程序会将赋值的变量大小扩展为被赋值的变量大小，且赋值的变量不会发生任何改变
  - 将一个很大的long值赋值给float会降低精度，因为float只有6位有效数字。
  - **总之，编译器通过校验表来确定在算术表达式中执行的转换。详情参考C++ primer P55(重要)**
- 强制类型转换的方式
  - `(long)data`  //C style
  - `long(data)`  //C++ style
  - `static_cast<long>(data)`，该强转方式比传统方式要求更为严格。
  - 强制类型转换不会修改data本身，而是创建一个新的指定类型的值，可以在表达式中使用这个值。
## 复合类型
### C++的数组初始化
```c++
double arr1[]{1,2,3,4,5,6};  //okay with c++11
float arr2[4]{}  //all elements set to 0
char arr3[4]{'h','k',11223322,'\0'}//错误，列表不允许缩窄变换
```
### 字符串输入
- cin使用空白(空格、制表符、回车)来确定字符串的结束位置，读取完单词后，cin会在该字符串结尾处自动添加结束符'\0'
- **问题**，如何防止录入字符串溢出？
### 行字符录入
istream中的类提供了一些面向行的累成员函数：getline()和get()
- getline()
  - 参数：参数1是数组名称，参数2是要读取的字符数（包括最后的结束符'\0'），若参数2为20，则实际读入19个字符，加上最后的结束符'\0'。
  - 用途：getline会读取到回车结束，需要注意的是getline会读取输入流的回车并将其替换为结束符'\0'。
  - 语法：`cin.getline(name,20)`
- get()
  - 参数：与getline相同
  - get()与getline()类似，不同的是它不会读取输入流的回车
  - 用法：
    ```c++
    //方式1
    cin.get(name,size);
    cin.get();  //读取存留的回车
    //方式2
    cin.get(name,size).get(); //cin.get(name,size)返回一个cin对象，所以可以用它再次调用get()
    //同样getline()也可以这么做
    ```
### string类
- string类包含在头文件string中
- string的初始化
  ```c++
  string data1 = {"hello"};
  string data2{"world"};
  string data3 = "hello";
  string data4;
  data4 = data3;  //支持直接赋值
  data4 += data2; //可以使用+=操作拼接字符串
  getline(cin,str4); //不能使用cin.getline(str4,size)，具体解释见P72
  ```
### 字符计数
- strlen 和 size()
  ```c++
  int len1 = str1.size();
  int len2 = strlen(str2);
  ```
### 其他形式的字符串字面值
  ```c++
  wchar_t name1[] = L"xxxxxxxxxxx";
  char16_t name2[] = u"xxxxxxxxxxx";
  char32_t name3[] = U"xxxxxxxxxxx";
  char name[] = R"(Jim "king","\n")";//原生字符串，"(...)"
  char name[] = R"+*(Jim "king","\n")+*";//原生字符串"+*(...)+*"
  ```
### C++中结构的位字段
  ```c++
  struct data{
    int SN : 4;
    int : 4;  //可以使用没有名称的字段来提供间距
    bool SU : 1;
  };
  ```
### 匿名共用体
  ```c++
  struct widget{
    char brand[20];
    int type;
    union{  //匿名共用体
      long id_num;
      char id_char[20];
    };
  };
  //调用id_num或id_char时可以用少加一个.
  ```
  ### 枚举
  ```c++
  enum data{red=2,blue,green,yello};
  data ex;
  red = blue+green//错误
  //枚举标量只能被赋予枚举变量的值，因此枚举不允许有+法运算，因为+会让数据变成整型
  ex = data(10);  //正确，枚举的强转
  red = data(10); //错误，red为常量，不能再被赋值
  ```
  ### new和delete
  - 对变量的操作
    ```c++
    //typeName *pointer_name = new typeName;
    int *pn = new int;  //为指针pn分配int大小空间
    delete pn;  //释放pn指向的内存
    double *pd = new double;  //为指针pd分配double大小空间
    delete pd;  //释放pd指向的内存
    delete pd;  //错误，不能重复释放
    int n=3;  //定义局部变量n
    delete n; //错误，不允许释放栈空间内存
    ```
  ### 对数组的操作
  - 创建动态数组
    - `int *psome = new int [10]  //创建10个int元素的数组`
    - delete [] psome;  //释放数组
    - 对空指针用delete是安全的
    - 不能使用sizeof来确定动态数组的字节数
  - 使用动态数组
    - psome[0]、psome[1]、psome[2]...调用数组各个元素


