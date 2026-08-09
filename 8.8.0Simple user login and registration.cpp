#include <iostream>
#include <vector>
#include <string>
#include <cctype>    //字符分类函数(判断字符属性)
#include <optional>  //可选值头文件
#include <fstream>   //文件流头文件
#include <sstream>   //字符串流头文件
#include <stdexcept> //异常处理头文件提供runtime_error异常
#include <chrono>    //c++11时间头文件
#include <ctime>     //c时间头文件，提供time()函数

#define AGAINONCE                              \
    std::string tmp;                           \
    std::cout << "重试？(y/n) " << std::flush; \
    std::getline(std::cin, tmp);               \
    if (tmp == "y" || tmp == "Y")              \
    {                                          \
        index++;                               \
        continue;                              \
    }                                          \
    else                                       \
    {                                          \
        return;                                \
    }

// get current(当前) time function
std::string currentTime()
{
    auto nowTime = std::chrono::system_clock::now();
    std::time_t formatTime /*format 格式化*/ = std::chrono::system_clock::to_time_t(nowTime);
    char buf /*buffer 缓冲区*/[32]; // 缓冲区，用于存储格式化后的时间字符串
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&formatTime));
    // 将时间戳转换为本地时间，格式化为YYYY-MM-DD HH:MM:SS
    return buf;
}

// 日志类
class Logger
{
public:
    explicit Logger(const std::string &filename) : file_(filename, std::ios::app)
    {
    }
    Logger(const Logger &) = delete;                                               // 禁止 Logger log2 = log1; 拷贝构造
    Logger &operator/*[操作员]用于拷贝赋值运算符重载*/ =(const Logger &) = delete; // 禁止 log2 = log1; 赋值

    void write(const std::string &tag /*已经全写，tag标签*/, const std::string &msg)
    {
        if (file_.is_open())
        {
            file_ << "[" << currentTime() << "]" << "[" << tag << "]" << msg << std::endl;
        }
    }
    void info(const std::string &msg)
    {
        write("INFO", msg);
    }
    void warning(const std::string &msg)
    {
        write("WARNING", msg);
    }
    void error(const std::string &msg)
    {
        write("ERROR", msg);
    }

private:
    std::ofstream file_; // 必须是文件流，才能用 is_open() 和 << 写入文件
};

// 用户数据（struct）
struct User
{
    std::string username;
    std::string password;
};

//=========authSystem(Auth认证)交互类
class AuthSystem
{
public:
    void run()
    {
        loadUser(); // 首先调用读取函数将users读取到内存
        while (true)
        {
            std::cout << "\n==== user login and register system ====" << std::endl;
            std::cout << "1.user register" << std::endl;
            std::cout << "2.user login" << std::endl;
            std::cout << "0.exit program" << std::endl;
            int index = 0;
            std::string buf = "";
            int bufInt=0;
            while (true)
            {
                if (index > 0)
                {
                    std::cout << "please agin input:" << std::flush;
                }
                std::cout << "\n=>:" << std::flush;
                std::getline(std::cin, buf);
                if (buf.empty())
                {
                    logger_.warning("system input is empty");
                    index++;
                    continue;
                }
                try
                {
                    bufInt = std::stoi(buf);
                }
                catch (const std::exception &e)
                {
                    logger_.error("input error: " + std::string(e.what()));
                    std::cout << "input error! " << std::endl;
                    index++;
                    continue;
                }
                switch (bufInt){
                    case 1:registerUser();index=0;break;
                    case 2:login();index=0;break;
                    case 0:
                        logger_.info("input '0' program exit");
                        std::cout<<"bey~"<<std::endl;
                        return;
                    default:
                        logger_.error("system input '"+buf+"' is invalid.");
                        std::cout<<"invalid(无效的) selection(选择)"<<std::endl;
                        index=0;
                        break;
                }
                break;
            }
        }
    }

private:
    std::vector<User> users_;
    Logger logger_{"8.8.0auth.log"};

    // 注册 用户名唯一，密码强度检测
    void registerUser()
    { // register(登记簿)
        User u;
        std::cout << "Welcome you registering" << std::endl;

        {
            std::cout << "input your register username:" << std::flush;
            int index = 0;
            while (true)
            {
                if (index > 0)
                {
                    std::cout << "again input:" << std::flush;
                }
                std::cout << "\n=>" << std::flush;
                std::getline(std::cin, u.username);
                if (u.username.empty())
                {
                    std::cout << "input is empty!" << std::flush;
                    index++;
                    continue;
                }

                if (findUser(u.username).has_value())
                {
                    logger_.warning("registration failed!username already(已经、早已 ) exists(存在)");
                    std::cout << "registration failed!username already(已经、早已 ) exists(存在)"<<std::endl;
                    // registration（注册）failed（失败过去时）
                    AGAINONCE;
                }
                break;
            }
        }

        // 密码输入+校验循环（do while:至少问一次，3.5.1）
        {
            int index = 0;
            do
            {
                std::cout << "input your register password:" << std::flush;
                if (index > 0)
                {
                    std::cout << "again input:" << std::flush;
                }
                std::cout << "\n=>" << std::flush;
                std::getline(std::cin, u.password);

                if (!isStrongPassword(u.password))
                {
                    std::cout << "your password must be at least 6characters(字符) long and letters(字母) and numbers!" << std::endl;
                    AGAINONCE; // y:continue n:return
                }
            } while (!isStrongPassword(u.password));
            users_.push_back(u);
            saveUser();
            logger_.info("New user : '" + u.username + "' registered。");
            std::cout << "you registered pass！" << std::endl;
        }
    }
    // user login(用户登录)optional(可选的)找不到用户返回空
    void login()
    {
        std::string name, pwd;
        {
            int index = 0;
            std::cout << "please input username:" << std::flush;
            while (true)
            {
                if (index > 0)
                {
                    std::cout << "please again input:" << std::flush;
                }
                std::cout << "\n=>:" << std::flush;
                std::getline(std::cin, name);
                if (name.empty())
                {
                    index++;
                    continue;
                }
                break;
            }
        }
        // 密码
        {
            int index = 0;
            std::cout << "please input password:" << std::flush;
            while (true)
            {
                if (index > 0)
                {
                    std::cout << "please again input:" << std::flush;
                }
                std::cout << "\n=>:" << std::flush;
                std::getline(std::cin, pwd);
                if (pwd.empty())
                {
                    index++;
                    continue;
                }
                auto user = findUser(name);
                if (!user.has_value() || user->password != pwd)
                {
                    logger_.warning("Incorrect username or password！" + name);
                    std::cout << "Incorrect username or password!" << std::endl;
                    AGAINONCE;
                }
                break;

            }
            logger_.info("Login successful!" + name);
            std::cout << "Welcome back!" << name << std::endl;
        }
    }

    // 密码强度合格检查：
    bool isStrongPassword(const std::string &pwd) const
    {
        if (pwd.size() < 6)
            return false;
        bool hasLetter /*有字母*/ = false, hasDigit /*有数字*/ = false;
        for (unsigned char c : pwd)
        {
            if (std::isalpha(c))
                hasLetter = true;
            if (std::isdigit(c))
                hasDigit = true;
        }
        return hasLetter && hasDigit;//&&同时满足才为true
    }

    // 查找用户
    std::optional<User> findUser(const std::string &name) const
    {
        for (const auto &u : users_)
        {
            if (u.username == name)
            {
                return u;
            }
        }
        return std::nullopt; // 不是空指针nullptr
    }

    // 持久化保存
    void saveUser()
    {
        std::ofstream file("8.8.0users.csv");
        for (const auto &u : users_)
        {
            file << u.username << "," << u.password << "\n";
        }
    }
    void loadUser()
    {
        std::ifstream file("8.8.0users.csv");
        std::string loadLine;
        while (std::getline(file, loadLine))
        {
            std::istringstream iss(loadLine);
            User u;
            std::getline(iss, u.username, ',');//需要用''char 字符,""是const char*字符串
            std::getline(iss, u.password, ',');
            users_.push_back(u);
        }
    }
};

int main()
{
    AuthSystem auth;
    auth.run();
    return 0;
}
