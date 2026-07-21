// 类是 C++ 面向对象编程的基础。你可以把类理解为图纸，而根据图纸制造出来的具体物体叫做对象（或实例）

#include<iostream>
#include<string>

class Student{
public:
    //公开接口，谁都可以调用

    //构造函数：创建对象的时候自动调用
    // 构造函数的名称和类名相同，没有返回值（连void都没有）
    Student(const std::string& name,int age)
        //初始化对象的属性:把参数赋值给成员变量
        // 这里: name_(name) 意思是"用参数 name 初始化成员变量 name_"
        // 后面的小括号 () 里是"用来初始化的值"
        // 为什么不用 name_ = name 写在花括号 {} 里？
        // 因为初始化列表是"直接构造"，效率更高
        // 好比：初始化列表是"直接拿材料做蛋糕"，
        //花括号里赋值是"先做个空蛋糕再涂上奶油"
        : name_(name),age_(age){
            std::cout<<"学生"<<name_
                <<"入学了！"<<std::endl;
    }
    
    //成员函数，对象可以做的事情
    //这里的const关键字写在函数后面表示
    // "这个函数承诺不会修改任何成员变量"
    // 就像你只是"看一看"某个东西，不会去改变它
    // 加了 const 的函数，可以放心地调用——它不会搞乱你的数据
    void introduce() const{
        std::cout<<"我叫"<<name_<<",我今年"<<age_<<"岁"<<std::endl;

    }

private://私有成员变量，只有类的内部可以访问
    std::string name_;
    int age_;


};


int main(){
    //创建对象（实例化）
    Student stu1("小马",18);
    Student stu2("小红",19);

    //调用成员函数
    stu1.introduce();
    stu2.introduce();




}
