#include <iostream>
#include <fstream>//文件流
#include <sstream>//字符串流
#include <string>
#include <vector>
#include <stdexcept>//异常处理头文件

struct/*结构体*/ Pet{
    std::string name;
    int age;
    std::string breed;//动物品种（繁育）
    bool adopted;//是否已被领养
};
//序列化：宠物=一行csv文本，格式：
std::string petToCsv(const Pet& p){
    return p.name+","+std::to_string(p.age)+","+p.breed+","
        +(p.adopted?"1":"0");
}

//反序列化：将csv文本转换为宠物对象
Pet csvToPet(const std::string& line){
    std::istringstream iss(line);//iss变量名全写为input string stream[istringstream]（输入字符串流）
    std::string name,breed/*品种*/,ageStr,adoptedStr;
    //getline(流,变量流,分隔符)
    //从流中提取一行，将该行赋值给变量流
    //std::getline(iss,name,',');
    //从流iss中提取一行，将该行赋值给变量流name。
    //一行的判定为：遇到分隔符（逗号）或流结束
    //读取的数据不包含分隔符。
    std::getline(iss,name,',');//提取名称
    std::getline(iss, ageStr, ','); // 提取年龄
    std::getline(iss,breed,',');//提取品种
    std::getline(iss,adoptedStr);//提取是否已被领养
    //stoi=string to integer：将字符串转换为整数
    //stoi(adoptedStr)==1 比较结果是 bool，避免 int→bool 的收窄警告
    return {name,stoi(ageStr),breed,stoi(adoptedStr)==1};
    
}

//保存整个列表（一行一个动物）
void savePetList(const std::vector<Pet>& pets ,const std::string& filename){
    std::ofstream file(filename);//RAII打开文件

    if(!file){
        throw std::runtime_error("failed to open file:"+filename);//异常处理
    }


    for(const auto& p:pets){
        file<<petToCsv(p)<<std::endl;
    }
    std::cout<<"save "<<pets.size()<<"pets to "<<filename<<std::endl;
}

//加载整个列表（一行一个动物）读回
std::vector<Pet> loadPets(const std::string& filename){
    std::vector<Pet> pets;
    std::ifstream file(filename);

    if(!file){
        throw std::runtime_error("failed to open file:"+filename);//异常处理
    }


    std::string line;
    while(std::getline(file,line)){//一行一行读取
        if(line.empty()) continue;
        pets.push_back(csvToPet(line));
    }
    return pets;
}

int main(){
    try{
        std::vector<Pet> pets = {
            {"Fluffy", 1, "Labrador", false},
            {"Spot", 2, "Labrador", false},
            {"旺财", 3, "金毛", true},
             {"咪咪", 4, "橘猫", true}
        };
        savePetList(pets,"8.7.0pets.csv");
        auto loaded =loadPets("8.7.0pets.csv");

        std::cout<<"=====loaded "<<loaded.size()<<" pets:====="<<std::endl;
        for(const auto& p:loaded){
            std::cout<<p.name<<","<<p.age<<","<<p.breed<<","<<(p.adopted?"adopted":"not adopt")<<std::endl;
        }
    }catch(const std::exception& e){//exception(其它异常)is any error
        std::cout<<"error:"<<e.what()<<std::endl;
    }
}

