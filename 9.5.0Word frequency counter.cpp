// Word frequency counter
// 统计单词出现的次数
#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>   //字符串流
#include <algorithm> //算法
#include <cctype>    //字符类型char type

// convert string to lowercase //convert[转换]//lowercase[小写]//将字符串转换为小写
std::string toLower(const std::string &str)
{
    std::string result = str;
    // unsigned[无符号]
    // transform(作用域起始位置,作用域结束位置,写入目标.位置,转换函数)
    std::transform(result.begin(), result.end(), result.begin(), [](unsigned char c)
                   { return std::tolower(c); });
    return result;
}

int main()
{
    std::string text =
        "The quick brown fox jumps over the lazy dog. " // brown[棕色]//lazy[懒惰]
        "The dog barks, and the fox runs away. "         // bark[叫]//fox[狐狸]
        "Quick thinking, quick action.";                 // action[行动]

    std::unordered_map<std::string, int> wordCount;

    // split string into words by space//split[分割]
    std::istringstream iss(text);
    std::string word;
    while (iss >> word)
    {
        // remove punctuation characters//punctuation[标点符号]//characters[字符]//移除标点符号
        // erase(作用域起始位置,作用域结束位置)
        // remove_if(作用域起始位置,作用域结束位置,判断函数)
        // 判断函数(字符)
        // 返回值:删除后的起始位置
        word.erase(std::remove_if(
                       word.begin(),
                       word.end(),
                       [](unsigned char c)
                       {
                           return std::ispunct(c); // ispunct[是否标点符号]//判断字符是否为标点符号
                       }),
                   word.end());
        // convert string to lowercase//convert[转换]//lowercase[小写]//将字符串转换为小写
        word = toLower(word);
        if (!word.empty())
        {
            wordCount[word]++; // if word is empty, 自动创建并且初始化为0, 然后自增
        }
    }

    // Output frequency statistics//output[输出]//frequency[频率]//statistics[统计]//输出统计结果
    std::cout << "=====Word frequency statistics=====" << std::endl;
    // distinct words[不同单词]//统计不同单词的数量
    std::cout << "tatol of:" << wordCount.size() << "distinct words." << std::endl;
    std::cout << "==================" << std::endl;
    for (const auto &[word, count] : wordCount)
    {
        std::cout << word << " tatol of" << ":" << count << std::endl;
    }

    // find the word that occurs most frequently//find[查找]//occurs[出现]//most frequently[最频繁]
    std::string mostFrequentWord;
    int maxCount = 0;
    for (const auto &[word, count] : wordCount)
    {
        if (count > maxCount)
        {
            maxCount = count;
            mostFrequentWord = word;
        }
    }
    std::cout << "The most frequent word is:" << mostFrequentWord << ", it occurs " << maxCount << " times." << std::endl;

    return 0;
}
