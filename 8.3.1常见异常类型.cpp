#include <iostream>
#include <string>
#include <stdexcept> //标准异常库
#include <fstream>   //文件流库
#include <vector>    //向量库

int main()
{
    // std::runtime_error:
    // 运行时异常：在程序运行时，由于程序逻辑错误或外部环境问题，导致程序无法继续执行。
    // 例如：除数为0、文件不存在等。
    try
    {
        throw /*throw(投掷)*/ std::runtime_error("A runtime error occurred(occur发生的过去式)!");
    }
    catch (const std::runtime_error &runE)
    {
        std::cout << "catch(捕获) a runtime error:" << runE.what() << std::endl;
    }

    // 2.std::out_of_range:越界访问
    try
    {
        std::vector<int> vec = {1, 2, 3, 4, 5};
        vec.at(10)=100;//at()方法会检查越界，如果越界会抛出out_of_range异常
        // operator[]运算符会直接访问内存，不会检查越界，不会抛出异常，不能被catch接住，程序会直接崩溃

        /*D:/Tool/msys64/ucrt64/include/c++/16.1.0/bits/stl_vector.h:1253:
        constexpr std::vector<_Tp, _Alloc>::reference std::vector<_Tp, _Alloc>::
        operator[](size_type) [with _Tp = int; _Alloc = std::allocator<int>;
         reference = int&; size_type = long long unsigned int]:
        Assertion '__n < this->size()' failed.*/

        // vec[12] = 1000;
    }
    catch (const std::out_of_range &outE)
    {
        std::cout << "catch a out_of_range error:" << outE.what() << std::endl;
    }

}
