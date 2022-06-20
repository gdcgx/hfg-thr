#include <iostream>
#include "myLog.hpp"

int main(){
    myLog::getInstance()->init("hfg's log","../logs/znxb.txt");
    LTrace("log level {}","trace");
    LDebug("log level {}","debug");
    LWarn("log level {}","warn");
    LInfo("log level {}","info");
    LError("log level {}","error");
    LCritical("log level {}","critical");

    char sre[12] = "hello world";
    LTrace("it is{}",sre);
    LTrace("it is {} , hello {}",123456 ,"world");
    char ch = 'z';
    LTrace("it is {}",ch);
    LTrace("{}",char(42));

    // std::vector<char> buf(80);
    // for (int i = 0; i < 80; i++)
    // {
    //     buf.push_back(static_cast<char>(i & 0xff));
    // }
    // LInfo("Binary example: {}", spdlog::to_hex(buf));
    // LInfo("Another binary example:{:n}", spdlog::to_hex(std::begin(buf), std::begin(buf) + 10));
    // LInfo("uppercase: {:X}", spdlog::to_hex(buf));    // 大写
    // LInfo("uppercase, no delimiters: {:Xs}", spdlog::to_hex(buf));    // 大写 且 不留空格
    // LInfo("uppercase, no delimiters, no position info: {:Xsp}", spdlog::to_hex(buf));    // 大写 且 不留空格 且 无位置信息
    // LInfo("hexdump style: {:a}", spdlog::to_hex(buf));    // 显示ASCII
    // LInfo("hexdump style, 20 chars per line {:a}", spdlog::to_hex(buf, 20));    // 显示ASCII, 20字符一行
    myLog::getInstance()->unInstance();
    return 0;
}
