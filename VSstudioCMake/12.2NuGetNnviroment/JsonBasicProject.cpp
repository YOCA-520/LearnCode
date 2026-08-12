#include <fstream>
#include <iostream >
#include <stdexcept>// 标准异常库
#include <string>

#include <nlohmann/json.hpp> //json

using json = nlohmann::json;// user sort name

struct Pet {
	std::string name;  //std::string 会自己初始化
	std::string breed;//品种
	int age{};  //内置基础类型不会自动初始化使用加{}初始化为0
	bool adopted{};//初始化为false
};

//c++object ->json object
void to_json(json& j, const Pet& pet) {
	j = {
		{"name",pet.name},
		{"breed",pet.breed},
		{"age",pet.age},
		{"adopted",pet.adopted ? std::string {"adopted"} 
			: std::string {"not adopted"}}
	};
}

void from_json(const json& j, Pet& pet) {
	if (!j.is_object()
		|| !j.contains("name")/*contains[包含]*/
		|| !j.contains("breed")
		|| !j.contains("age")
		|| !j.contains("adopted")){
		       //invallid[无效的]//argument[参数]
				//invalid_argument[标准错误库]
		throw/*投出*/ std::invalid_argument("PET_FIELDS_INCOMPLETE");
	}

	//at()read 必填字段 :字段缺失或者类型不对会进入异常边界
	// key不存在时抛出out_of_range[超出范围]
	// 语法格式：对象.at("键名")
	// 逻辑理解：相当于在 j 中查找 key（类似 at(j, key)）
	// 函数式逻辑：j.at("age") 相当于 at(j, "age")
	pet.name = j.at("name").get<std::string>();
	pet.breed = j.at("breed").get<std::string>();
	pet.age = j.at("age").get<int>();
	pet.adopted = j.at("adopted").get<bool>();
}

int main() {

}




