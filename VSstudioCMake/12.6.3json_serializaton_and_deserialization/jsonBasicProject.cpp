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
//to_json只要你定义了这个名字固定为 to_json 的函数，
// 后续遇到 json document = {{"pet", pet}}; 时，
// 库就会自动调用这个函数把 pet 结构体打包成 JSON。
void to_json(json& j, const Pet& pet) {
	j = {
		{"name",pet.name},
		{"breed",pet.breed},
		{"age",pet.age},
		{"adopted",pet.adopted}
	};
}

//与 to_json 对应，当你想要把 JSON 转回 Pet 对象
// （如 Pet p = j.get<Pet>(); ）时，库会自动调用它。
void from_json(const json& j, Pet& pet) {
	if (!j.is_object()
		|| !j.contains("name")/*contains[包含]*/
		|| !j.contains("breed")
		|| !j.contains("age")
		|| !j.contains("adopted")) {
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
	try {
		const Pet pet{
			"旺财","柯基",2,false
		};

		//serialization c++ -> json
		//document[文档]
		json document = {
			{"version",1},
			{"pet",pet},
			//tags[标签]
			{"tags",json::array({"friendly","vaccinated"})},
			//rating[等级、评分]
			{"rating",4.5},
			//enable[启用，生效]
			// //"enable": true 表示“该宠物档案已启用/正在生效中”
			// ；如果是 false 则表示“已停用/已冻结”。
			{"enable",true},
			{"note",nullptr}
		};

		std::cout << "serialization result :\n"
                  //indentation[缩进]                       //escape[转义]
			//dump(indentation size , indentation character , whether to escape UTF-8)
			<< document.dump(4, ' ', false) << "\n";

		//2.access character :先访问边界，在按契约取value
				//contains[饱含]
		if (!document.contains("pet")) {
			throw std::invalid_argument("missing pet filed");
		}

		const json& pet_json = document.at("pet");

										//json_obj.value( 键名 , 默认备用值 )
		//value非必填
		const std::string name = pet_json.value("name", std::string("not name"));
		//age 使用 at() —— 必填字段（Strict / Required）
		const int age = pet_json.at("age").get<int>();//no found throw out_of_range
		const bool adopted = pet_json.value("adopted", false);
		const double rating = document.value("rating", 0.);

		std::cout << "read the filed :" << name << ", age :" << age
			<< ", rating :" << rating << ", adopted :" << (adopted ? "yes" : "no") << "\n";

		int tag_count = 0;
		//contains[包含]
		if (document.contains("tags")) {
			//在循环中提取出来的 tag 依然是 JSON 自己的专属类型（nlohmann::json），
			// 而不是 C++ 原生的 std::string 字符串
			//所以需要用get<std::string>()方法
			for (const auto& tag : document.at("tags")) {
				std::cout << "tag :" << tag.get<std::string>() << "\n";
				++tag_count;
			}
		}

		if (document.contains("note") && document.at("note").is_null()) {
			std::cout << "note is null \n";
		}

		//get<T> user from_json 把json object 还原成 c++ object
			//restored[恢复]
		const Pet restored = pet_json.get<Pet>();
		std::cout << "restored object :" << restored.name << ", " << restored.breed << "\n";

		//generate[生成]
		//write file :dump generate UtF-8 json text
		const std::string filename = "12.6.0-pet.json";
		{
			std::ofstream output(filename, std::ios::binary);
			if (!output) {
				throw std::runtime_error("cannot open json output file");
			}
			output << document.dump(4, ' ', false) << "\n";
			if (!output) {
				throw std::runtime_error("failed to write file json");
			}
		}

		// 4. 读文件：parse 把 JSON 文本反序列化为 json 值
		json loaded;
		{
			std::ifstream input(filename, std::ios::binary);
			if (!input) {
				throw std::runtime_error("无法打开 JSON 输入文件");
			}
			loaded = json::parse(input);
		}

		if (!loaded.is_object() || !loaded.contains("pet")) {
			throw std::invalid_argument("JSON 文件缺少 pet 对象");
		}

		const Pet loaded_pet = loaded.at("pet").get<Pet>();
		std::cout << "文件读取成功：" << loaded_pet.name
			<< "，标签数量：" << tag_count << "\n";
	}
	catch (const json::parse_error& error) {
		std::cerr << "JSON 格式错误：" << error.what() << std::endl;
		return 1;
	}
	catch (const json::type_error& error) {
		std::cerr << "JSON 类型错误：" << error.what() << std::endl;
		return 1;
	}
	catch (const json::out_of_range& error) {
		std::cerr << "JSON 字段越界或缺失：" << error.what() << std::endl;
		return 1;
	}
	catch (const std::exception& error) {
		std::cerr << "读取或校验失败：" << error.what() << std::endl;
		return 1;
	}

	return 0;
}

