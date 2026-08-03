// 💡 为什么用 unsigned char？ 
// std::ispunct 和 std::tolower 要求参数是 unsigned char 或 EOF。
// 如果传 char（在有符号平台上可能是负数），会触发未定义行为。
// 所以 Lambda 参数写 unsigned char c 是安全做法。

// 你会在第 9 章的实战中看到这些函数的实际应用。



#include <iostream>
#include<cctype>//字符处理头文件
#include<string>
#include<algorithm>//算法头文件

int main(){
    std::string str="He l l o,  W o r ld!";
    std::cout<<"原始字符串："<<str<<std::endl;

    //移除标点符号（erase-remove 惯用法）
    //erase(擦除)remove(移除)
    //remove_if后erase(移除满足条件的元素)
    //remove(移除指定元素)
    str.erase(std::remove_if(str.begin(),str.end(),
        [](unsigned char c){
            return std::ispunct(c);//is punct (uation)判断是否为标点符号
        }),str.end());
    std::cout<<"标点处理结果："<<str<<std::endl;

    //转换小写
    std::transform(str.begin(),str.end(),str.begin(),
        [](unsigned char c){return std::tolower(c);});//tolower(转为小写)

    std::cout<<"小写转换结果："<<str<<std::endl;

    //转换大写
    std::transform(str.begin(),str.end(),str.begin(),
        [](unsigned char c){return std::toupper(c);});//toupper(转为大写)

    std::cout<<"大写转换结果："<<str<<std::endl;

    //擦除空格
    //erase参数（开始迭代器，结束迭代器，新字符串位置）
    //remove参数（开始迭代器，结束迭代器，要移除的元素）
    str.erase(std::remove(str.begin(),str.end(),' '),str.end());
    std::cout<<"空格擦除结果："<<str<<std::endl;

    //首字母大写
    std::transform(str.begin(),str.end(),str.begin(),
        [](unsigned char c){return std::tolower(c);});//tolower(转为小写)

    str[0]=std::toupper(str[0]);//toupper(转为大写)
    std::cout<<"首字母大写结果："<<str<<std::endl;

    
}

// 函数	    判断"是…吗"	                       例子
// isalpha	字母	                        'a'✅ '1'❌
// isdigit	数字 0-9	                    '7'✅ 'a'❌
// isalnum	字母 或 数字	                 'x'✅ '9'✅ '!'❌
// islower	小写字母	                     'a'✅ 'A'❌
// isupper	大写字母	                     'A'✅ 'a'❌
// isspace	空白（空格、\t、\n、\r 等）	      ' '✅ '\n'✅
// ispunct	标点	                         '!'✅ 'a'❌（你已用）
// isxdigit	十六进制数字	                  'f'✅ '9'✅ 'g'❌
// isprint	可打印字符	                      'a'✅ '\n'❌
// iscntrl	控制字符	                      '\n'✅
