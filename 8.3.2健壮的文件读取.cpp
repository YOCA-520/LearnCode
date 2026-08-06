#include<iostream>
#include<fstream>
#include<string>
// 异常处理exception(除某某以外)
#include<stdexcept>//
#include<vector>


//读取文件内容，失败时抛出异常
std::vector<std::string> readFilelines/*线条，行*/(const std::string& filename ){
    //打开已有文件
    std::ifstream file(filename);//打开文件流 ，如果文件不存在，会抛出异常
    //如果文件流打开失败，会返回false
    //如果文件流打开成功，会返回true
    if(!file){
        throw/*投出*/std::runtime_error("open " + filename + " failed");//failed(失败的)

    }

    //定义一个vector，用于存储文件的每一行
    std::vector<std::string> lines;
    std::string line;
    //写入文件的每一行
    while(std::getline(file,line)){
    // std::getline(file, line) 从文件流中每次读一整行（读到换行符为止）存入 line。
    //它返回文件流本身，当读到文件末尾（EOF）时返回 false，循环结束。
        lines.push_back(line);
    }

    if(file.bad()){
        throw std::runtime_error("读取文件时发生错误"+filename);
    }
    return lines;

}
int main(){
    std::cout<<"请输入文件名：";
    std::string filename;
    std::getline(std::cin,filename);
    try{
        auto lines =readFilelines(filename);
        std::cout<<"文件"<<filename<<"有"<<lines.size()<<"行"<<std::endl;
        for(const auto& line:lines){
            std::cout<<line<<std::endl;

        }
    }catch(const std::runtime_error& e){
        std::cerr<<"读取文件失败："<<e.what()<<std::endl;

    }catch(const std::exception& e){//exception(异常)其他的异常
        std::cerr<<"未知错误："<<e.what()<<std::endl;

    }
    std::cout<<"程序正常结束"<<std::endl;
    return 0;

}
