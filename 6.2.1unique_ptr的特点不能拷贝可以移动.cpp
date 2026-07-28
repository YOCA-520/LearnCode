#include <iostream>
#include <memory>//智能指针头文件

int main(){
    //用unique_ptr创建智能指针
    auto ptr1 = std::make_unique<int>(24);
    std::unique_ptr<int> ptr2;//定义一个空指针
    //不能拷贝
    //auto ptr2 = ptr1;会编译报错
    //智能指针是独有，不能拷贝，但是可以移动

      if(!ptr1){
        std::cout<<"移动前:ptr1不在拥有对象"<<std::endl;
    }else{
        std::cout<<"移动前:ptr1拥有对象:"<<*ptr1<<std::endl;
    }

    if(ptr2){
        std::cout<<"移动前:ptr2拥有对象:"<<*ptr2<<std::endl;
    }else{
        std::cout<<"移动前:ptr2不在拥有对象"<<std::endl;
    }

    //可以移动，转移所有权

    ptr2 = std::move(ptr1);//将ptr1的所有权移动给ptr2
    //赋值操作，ptr1会失去所有权，ptr2会获得所有权

    //效果：ptr1不在拥有对象，ptr2拥有对象
    if(!ptr1){
        std::cout<<"移动后:ptr1不在拥有对象"<<std::endl;
    }else{
        std::cout<<"移动后:ptr1拥有对象"<<*ptr1<<std::endl;
    }

    if(ptr2){
        std::cout<<"移动后:ptr2拥有对象:"<<*ptr2<<std::endl;
    }else{
        std::cout<<"移动后:ptr2不在拥有对象"<<std::endl;
    }

    return 0;

    
}