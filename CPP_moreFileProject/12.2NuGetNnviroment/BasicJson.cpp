#include <iostream>
#include <nlohmann/json.hpp>



//使用别名
using json = nlohmann::json;

int main() {
	const nlohmann::json demo = {
		{"message","NuGet works"},
		{"version", 1}
	};

	
	//dump[缩进]，调整json输出的缩进。
	std::cout << demo.dump(4) << std::endl;

	std::cout << "======================\n\n" << std::endl;
	
	//JSON write sex value type
	//1.object
	const json object = {
		{"name" ,"旺财"}
	};

	std::cout << object.dump(4) << "\n============" << std::endl;

	//2.array
	const json array = {
		{"柯基","英短","梨花","玳瑁"}
	};
	std::cout << array.dump(4) << "\n============" << std::endl;
	
	//3.string
	const json jsString = {
		{"I am gay"}
	};
	std::cout << jsString.dump(4) << "\n============" << std::endl;

	//4.number
	const json jsNum = {
		{1,2,3,4,5}
	};
	std::cout << jsNum.dump(4) << "\n============" << std::endl;
	
	//5.bool
	const json jsBool = {
		{true,false}//only lowercase[小写] literal[字面量]
	};
	std::cout << jsBool.dump(4) << "\n============" << std::endl;

	//6.null
	const json jsNoll = {
		{"null",nullptr}
	};
	std::cout << jsNoll.dump(4) << "\n============" << std::endl;



	std::cout << "\n\n===============================\n" << std::endl;


	

	return 0;


}
