#include <optional>
#include <iostream>

//maybeGetValue（也许会拿到一个值）
//bool returnValue()（是否返回值）
std::optional<int> maybeGetValue(bool returnValue){
    if(returnValue){
        return 100;//返回100
    }
    return std::nullopt;//return empty value
}

int main(){
    //1.创建
    std::optional<int> opt1=10;//有参数
    std::optional<int> opt2;//无参数
    std::optional<int> opt3=std::nullopt;//空值

    //2、检查是否有值
    if(opt1.has_value()){
        std::cout<<"opt1 has value."<<opt1.value()<<std::endl;
    }else{
        std::cout<<"opt1 has no value."<<std::endl;
    }
    if(opt2){//bool转换，等价于has_value()
        std::cout<<"opt2 has value or default value."<<opt2.value()<<std::endl;
    }else{
        std::cout<<"opt2 has no value."<<std::endl;
    }
    if(opt3){//bool转换，等价于has_value()
        std::cout<<"opt3 has value."<<opt3.value()<<std::endl;
    }else{
        std::cout<<"opt3 has no value."<<std::endl;
    }

    //解引用*opt对于optional是“未定义行为”
    //如果opt为空，解引用会抛出std::bad_optional异常，如果要用，需要先if(opt)检查是否有值

    //4、修改值
    opt1=14;
    opt1.reset();//清空opt1

    //5、调用函数返回optional（可选择的，包含一个值或为空）
    auto val=maybeGetValue(true);
    if(val){
        std::cout<<"get value is:"<<*val<<std::endl;
        //*val解引用，获取值,val.value()是获取值的另一种方式（直接获取值）
        //val->value()（通过指针获取）
    }

    //6、解引用
    auto val2=maybeGetValue(true);
    if(val2){
        std::cout<<"dereferenced get value is:"<<*val2<<std::endl;
    }
}
