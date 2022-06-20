# singletonOfSpdlog
基于 `spdlog` 的简单单例封装日志库,使用时需要先初始化
```
myLog::getInstance()->init("hfg's log","../logs/znxb.txt");
```
 打印日志时可以直接调用设定的宏，例如
```
LTrace("log level {}","trace");
```
通过定义宏 `STDOUT_FOR_DEBUG` 设置是否将日志打印到控制台，便于调试 
