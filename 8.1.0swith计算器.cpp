#include <iostream>
#include <string>

enum class Op{
    Add=1,
    Substract=2,
    Multiply=3,
    Divide=4,
    Exit=5
};

double add(double a,double b){return a+b;}
double substract(double a,double b){return a-b;}
double multiply(double a,double b){return a*b;}
double divide(double a,double b){return a/b;}

int main(){
    std::string input;
    int operatorNum;
    Op choice;     
    while(true){
        std::cout<<"======欢迎使用简单计算器====="<<std::endl;
        std::cout<<"1. 加法"<<std::endl;
        std::cout<<"2. 减法"<<std::endl;
        std::cout<<"3. 乘法"<<std::endl;
        std::cout<<"4. 除法"<<std::endl;
        std::cout<<"5. 退出"<<std::endl;
        std::cout<<"选择你需要的运算符:"<<std::flush;
        std::getline(std::cin,input);
        if(input==""){
            continue;
        }else if(input=="1"||input=="2"||input=="3"||input=="4"){
            operatorNum=stoi(input);
            choice=static_cast<Op>(operatorNum);
        }else if(input=="5"){
            choice=Op::Exit;
        }else{
            std::cout<<"输入了不能运行的东西呢。"<<std::endl;
            std::cout<<"按任意键继续..."<<std::flush;
            std::getline(std::cin,input);
            continue;

        }

        switch(choice){
            case Op::Exit:
                std::cout<<"再见~"<<std::endl;
                return 0;
            case Op::Add:
                // std::cout<<"你选择的是加法"<<std::endl;

            case Op::Substract:
                // std::cout<<"你选择的是减法"<<std::endl;
        
            case Op::Multiply:
                // std::cout<<"你选择的是乘法"<<std::endl;
                
            case Op::Divide:{
                // std::cout<<"你选择的是除法"<<std::endl;
                
                std::string input;

                double a,b;
                std::cout<<"请输入第一个数:"<<std::flush;
                try{
                    std::getline(std::cin,input);
                    a=stod(input);
                }catch(const std::exception& e){
                    std::cout <<"输入的第一个数有误:"<<std::endl<< e.what() << '\n';
                    std::cout<<"按任意键继续..."<<std::flush;
                    std::getline(std::cin,input);
                    continue;
                }
                std::cout<<"请输入第二个数:"<<std::flush;
                try{
                    std::getline(std::cin,input);
                    b=stod(input);
                }catch(const std::exception& e){
                    std::cout <<"输入的第二个数有误:"<<std::endl<< e.what() << '\n';
                    std::cout<<"按任意键继续..."<<std::flush;
                    std::getline(std::cin,input);
                    continue;
                }
                
                if (choice==Op::Divide&&b==0){
                    std::cout<<"除数不能为0"<<std::endl;
                    std::cout<<"按任意键继续..."<<std::flush;
                    std::getline(std::cin,input);
                    break;
                }
                double result=0;
                if(choice==Op::Add){result=add(a,b);}
                else if(choice==Op::Substract){result=substract(a,b);}
                if(choice==Op::Multiply){result=multiply(a,b);}
                if(choice==Op::Divide){result=divide(a,b);}
                std::cout<<"结果为:"<<result<<std::endl;
                std::cout<<"按任意键继续..."<<std::flush;
                std::getline(std::cin,input);
                break;

            }
            default:
                std::cout<<"输入了不能运行的东西呢。"<<std::endl;
                std::cout<<"按任意键继续..."<<std::flush;
                std::getline(std::cin,input);
                break;
            
            
        }

    }
}
