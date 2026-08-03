#include<iostream>
#include<string>
#include<fstream>

//旧式写法：手动管理资源，容易忘记
void readFile(){
    FILE*file=fopen("data.txt","r");
    if(file==nullptr){
        return;
    }
    // 读取文件内容
    fclose(file);//如果忘记或者出错，资源泄露
    // 关闭文件后，资源就被释放了
}

//RAII写法：自动管理资源，避免忘记
void readFileRAII(){
    std::ifstream file("data.txt");
    //构造时自动打开文件
    if(!file.is_open()){
        std::cout<<"无法打开文件!"<<std::endl;
        return;
    }
    //函数结束时，dile对象自动析构，文件自动关闭！
    //不需要手动fclose()
}

