#include <iostream>



class Solution {
public:
    char findTheDifference(std::string s, std::string t) {
        char res = 0;
        char *i = &s[0];
        char *j = &t[0];

        //遍历s全部字符
        while(*i != '\0'){
            res ^= *i;
            i++;
            std::cout <<"i:" <<*i<< "  res:" << res << std::endl;

        }
        //遍历t全部字符
        while(*j != '\0'){
            res ^= *j;
            j++;
            std::cout <<"j:"<<*j<< "  res:" << res << std::endl;
        }
        return res;
    }
};

int main() {
    Solution s;
    std::cout << s.findTheDifference("abcd", "abcde") << std::endl;
    return 0;
}
