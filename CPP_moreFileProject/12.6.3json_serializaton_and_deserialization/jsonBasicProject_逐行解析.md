# jsonBasicProject.cpp 逐行解析

> nlohmann::json 序列化/反序列化演示：C++ 对象 ↔ JSON 文本 ↔ 文件。

## 一、头文件与别名（第 1–8 行）

| 行 | 代码 | 解析 |
|----|------|------|
| 1 | `#include <fstream>` | 文件读写流：`ofstream`（写）、`ifstream`（读） |
| 2 | `#include <iostream>` | 控制台输入输出：`cout` / `cerr` / `endl` |
| 3 | `#include <stdexcept>` | 标准异常类：`invalid_argument`（参数无效）、`runtime_error`（运行时错误） |
| 4 | `#include <string>` | `std::string` 字符串 |
| 6 | `#include <nlohmann/json.hpp>` | 第三方 JSON 库头文件 |
| 8 | `using json = nlohmann::json;` | 起别名，后面用 `json` 代替一长串名字 |

## 二、Pet 结构体（第 10–15 行）

| 行 | 代码 | 解析 |
|----|------|------|
| 10 | `struct Pet {` | 定义宠物结构体 |
| 11 | `std::string name;` | 名字。`std::string` 是类类型，**自动初始化**为空串 |
| 12 | `std::string breed;` | 品种，同上自动初始化 |
| 13 | `int age{};` | 年龄。内置类型**不会**自动初始化，`{}` 让它初始化为 0 |
| 14 | `bool adopted{};` | 是否被领养，`{}` 初始化为 `false` |
| 15 | `};` | 结构体结束 |

> 关键点：C++ 内置类型（int/bool/指针）不写 `{}` 就是"未初始化"（垃圾值），类类型（string）会自动初始化。

## 三、to_json：C++ 对象 → JSON（第 17–28 行）

| 行 | 代码 | 解析 |
|----|------|------|
| 21 | `void to_json(json& j, const Pet& pet)` | **固定函数名** `to_json`，nlohmann 库遇到 `{"pet", pet}` 这种写法会自动调用它，把 `pet` 打包成 JSON |
| 22 | `j = {` | 把结果写入引用 `j`（所以是 `json&` 而非 `json`，要改的是外面的对象） |
| 23–26 | `{"name",...},{"breed",...},{"age",...},{"adopted",...}` | 用"键值对"初始化器列表生成 JSON 对象，键名与字段一一对应 |
| 26 | `{"adopted", pet.adopted}` | 直接写 bool 值，序列化出来是 `"adopted": false` |
| 27 | `};` | 结束初始化 |

> `to_json` 相当于给库一个"自定义类型怎么转 JSON"的说明书。

## 四、from_json：JSON → C++ 对象（第 30–52 行）

| 行 | 代码 | 解析 |
|----|------|------|
| 32 | `void from_json(const json& j, Pet& pet)` | 与 `to_json` 对应的固定函数名，`j.get<Pet>()` 时自动调用 |
| 33 | `if (!j.is_object()` | 先校验：不是对象就直接报错（防御性编程） |
| 34–37 | `\|\| !j.contains("name") ...` | `contains` 检查每个必填键是否存在，缺任何一个都不合格 |
| 40 | `throw std::invalid_argument("PET_FIELDS_INCOMPLETE");` | 校验失败 → 抛"参数无效"异常，带上错误信息 |
| 48–51 | `pet.xxx = j.at("键").get<类型>();` | **契约式读取**：先 `at()` 按键取值（键不存在抛 `out_of_range`），再 `.get<T>()` 按类型转换（类型不对抛 `type_error`） |
| 51 | `.get<bool>()` | `adopted` 按 bool 读，和 to_json 里写的 bool 对应 |

> 设计思路：**先校验（contains）→ 再取契约值（at + get）**，任何一步失败都进异常边界。

## 五、main 主函数：第 1 步——构造并序列化（第 54–79 行）

| 行 | 代码 | 解析 |
|----|------|------|
| 55 | `try {` | 整个流程包在 try 里，任何一步抛异常都会被底部 catch 接住 |
| 56–58 | `const Pet pet{"旺财","柯基",2,false};` | 按结构体成员顺序初始化一个宠物对象 |
| 62–74 | `json document = {...};` | 手动构造 JSON 文档，展示了多种 JSON 类型：|
| 63 | `{"version",1}` | 数字 |
| 64 | `{"pet",pet}` | 自定义对象 → **触发 to_json** |
| 66 | `{"tags",json::array({...})}` | 数组：用 `json::array()` 显式构造 |
| 68 | `{"rating",4.5}` | 浮点数 |
| 72 | `{"enable",true}` | 布尔 |
| 73 | `{"note",nullptr}` | 空值 null |
| 79 | `document.dump(4, ' ', false)` | 序列化成字符串：`4`=缩进 4 空格、`' '`=缩进字符、`false`=不转义 UTF-8（中文原样输出） |

## 六、第 2 步——读取字段（第 81–98 行）

| 行 | 代码 | 解析 |
|----|------|------|
| 83–85 | `if (!document.contains("pet")) throw ...` | 读取前先确认键存在，缺了就抛异常 |
| 87 | `const json& pet_json = document.at("pet");` | `at()` 取子对象，用 **`const&` 引用**避免拷贝（只读） |
| 91 | `pet_json.value("name", std::string("not name"))` | `value(键, 默认值)`：**非必填**读取。键不存在或类型不匹配 → 返回默认值，不抛异常 |
| 93 | `pet_json.at("age").get<int>()` | 必填字段用 `at()`：键缺失抛 `out_of_range`，类型错抛 `type_error` |
| 94 | `pet_json.value("adopted", false)` | 可选读取，默认 false |
| 95 | `document.value("rating", 0.)` | 从顶层文档读 rating |
| 97–98 | `cout << ... (adopted ? "yes" : "no")` | 三元运算符：true 输出 yes，否则 no |

> 记住两条铁律：
> - **必填字段** → `at() + get<T>()`（抛异常，强制暴露问题）
> - **可选字段** → `value(键, 默认值)`（静默用默认值）

## 七、第 3 步——遍历数组（第 100–114 行）

| 行 | 代码 | 解析 |
|----|------|------|
| 100 | `int tag_count = 0;` | 计数器 |
| 102 | `if (document.contains("tags"))` | 先确认数组存在再遍历 |
| 106 | `for (const auto& tag : document.at("tags"))` | 范围 for 遍历数组，`auto&` 避免拷贝 |
| 107 | `tag.get<std::string>()` | 循环里拿到的元素**仍是 `json` 类型**，必须 `.get<std::string>()` 转成原生字符串 |
| 108 | `++tag_count;` | 计数 |
| 112 | `if (document.contains("note") && document.at("note").is_null())` | `contains` 短路判断 + `is_null()` 检查是否是 null 值 |
| 113 | `cout << "note is null"` | 输出提示 |

## 八、第 4 步——get<Pet> 反序列化回对象（第 116–119 行）

| 行 | 代码 | 解析 |
|----|------|------|
| 118 | `const Pet restored = pet_json.get<Pet>();` | **触发 from_json**：把 JSON 对象还原成 Pet 对象 |
| 119 | 打印 `restored.name` / `restored.breed` | 验证还原成功 |

## 九、第 5 步——写入文件（第 121–133 行）

| 行 | 代码 | 解析 |
|----|------|------|
| 123 | `const std::string filename = "12.6.0-pet.json";` | 文件名 |
| 124 | `{ ... }` | 用**独立代码块**包住流对象，让它在块结束时自动析构（自动关闭文件，RAII） |
| 125 | `std::ofstream output(filename, std::ios::binary);` | 打开文件用于写入（二进制模式） |
| 126–128 | `if (!output) throw std::runtime_error(...)` | 流对象能转 bool：打开失败时为 `false`，抛异常 |
| 129 | `output << document.dump(4, ' ', false) << "\n";` | 把 JSON 字符串写入文件 |
| 130–132 | `if (!output) throw ...` | **写入后再检查一次**：写盘失败（如磁盘满）会置为失败态 |
| 133 | `}` | 块结束，`output` 析构 → 文件自动关闭 |

## 十、第 6 步——读文件并解析（第 135–151 行）

| 行 | 代码 | 解析 |
|----|------|------|
| 136 | `json loaded;` | 声明空 json 对象 |
| 138 | `std::ifstream input(filename, std::ios::binary);` | 打开文件读取 |
| 139–141 | `if (!input) throw ...` | 打开失败抛异常 |
| 142 | `loaded = json::parse(input);` | `parse` 把 JSON **文本**反序列化成 json 值（与 dump 相反） |
| 145–147 | `if (!loaded.is_object() \|\| !loaded.contains("pet")) throw ...` | 校验读回来的文档结构 |
| 149 | `const Pet loaded_pet = loaded.at("pet").get<Pet>();` | 再触发一次 from_json，还原成对象 |
| 150–151 | 打印结果 + 标签数量 | 验证全链路成功 |

## 十一、异常处理（第 153–168 行）

按 **从特殊到一般** 的顺序 catch，nlohmann 的异常都继承自 `std::exception`：

| 行 | catch 类型 | 含义 | 典型触发场景 |
|----|-----------|------|-------------|
| 153 | `json::parse_error` | JSON 文本格式错误 | 文件里写了非法 JSON |
| 157 | `json::type_error` | 类型不匹配 | `get<bool>()` 但实际是字符串 |
| 161 | `json::out_of_range` | 键不存在/越界 | `at("不存在的键")` |
| 165 | `std::exception` | 兜底：其他一切异常 | `invalid_argument`、`runtime_error` 等 |

每个 catch 都打印中文提示 + `error.what()`（具体错误信息），并 `return 1` 表示非正常退出。

> catch 顺序很重要：子类异常必须写在父类前面，否则永远被父类接住。

## 十二、程序流程总结

```
Pet 对象
  │ to_json（自动）
  ▼
json document ──dump──▶ 控制台打印 JSON 文本
  │                        │
  │ at()/value() 读取字段    ▼
  │                    写入 .json 文件
  │ get<Pet>()（from_json）
  ▼
Pet 还原对象 ────────── 读文件 parse 还原
```

- 序列化链：**C++ 对象 → JSON 值 → JSON 文本（dump）→ 文件**
- 反序列化链：**文件 → JSON 文本 → JSON 值（parse）→ C++ 对象（get）**
- 核心套路：**to_json / from_json 两个固定函数名** + **contains 校验 + at/value 取值 + 分层 catch**
