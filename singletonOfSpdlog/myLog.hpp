/*************************************************************
 * 基于spdlog的简单封装，后续待完善
 * **********************************************************/
#include <spdlog/spdlog.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <mutex>

class myLog{
public:
    static myLog* getInstance(){
        if(!m_mylog){
            std::lock_guard<std::mutex> locker(m_mtx);
            if(nullptr == m_mylog){
                m_mylog = new myLog();
            }
        } 
        return m_mylog;   
    }

    // spdlog日志初始化
    // @name : 日志名
    // @filepath : 生成日志的路径
    void init(std::string name,std::string filepath){
        try{
#ifdef STDOUT_FOR_DEBUG
            // 通过定义宏控制是否将日志打印到控制台输出，用于调试
            auto sink_stdout = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
            sink_stdout->set_pattern("[%Y-%m-%d %H:%M.%S.%e][%n][%^%-8l%$][%s:%!:%#] %v");
            // sink_stdout->set_level(spdlog::level::trace);
            sinks.emplace_back(sink_stdout);
#endif
            auto sink_rotate = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(filepath,1024*1024*5,3);
            sink_rotate->set_pattern("[%Y-%m-%d %H:%M.%S.%e][%n][%-8l][%s:%!:%#] %v");
            // sink_rotate->set_level(spdlog::level::warn);
            sinks.emplace_back(sink_rotate);
            m_logger = std::make_shared<spdlog::logger>(name,sinks.begin(),sinks.end());

#ifdef STDOUT_FOR_DEBUG
            m_logger->set_level(spdlog::level::trace);
#else
            m_logger->set_level(spdlog::level::info);
#endif
            m_logger->set_error_handler([](const std::string& msg){
                throw std::runtime_error(msg);
            });
            m_logger->flush_on(spdlog::level::err);
            spdlog::register_logger(m_logger);
            spdlog::flush_every(std::chrono::seconds(3));
        }
        catch(const spdlog::spdlog_ex& ex){
            std::cout << "Log initialization failed: " << ex.what() << std::endl;
        }
    }

    // 刷新日志
    void flush(){
        m_logger->flush();
    }

    auto getLogger(){
        return m_logger;
    }

    static void unInstance(){
        if(m_mylog){
            std::lock_guard<std::mutex> locker(m_mtx);
            if(m_mylog){
                delete m_mylog;
                m_mylog = nullptr;
            }
        }
    }
    
protected:
    void stopLogger(){
        spdlog::shutdown();
    }

    myLog(){
        sinks.clear();
    }	

    ~myLog(){
        stopLogger();
    }

	myLog(const myLog&) = delete;
	myLog& operator=(const myLog&) = delete;
	
private:
    static myLog* m_mylog;
    static std::mutex m_mtx;
    std::shared_ptr<spdlog::logger> m_logger = nullptr;
    std::vector<spdlog::sink_ptr> sinks;
};

myLog* myLog::m_mylog = nullptr;
std::mutex myLog::m_mtx;

#define LTrace(...)     myLog::getInstance()->getLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::trace, __VA_ARGS__)
#define LDebug(...)     myLog::getInstance()->getLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::debug, __VA_ARGS__)
#define LInfo(...)      myLog::getInstance()->getLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::info, __VA_ARGS__)
#define LWarn(...)      myLog::getInstance()->getLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::warn, __VA_ARGS__)
#define LError(...)     myLog::getInstance()->getLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::err, __VA_ARGS__)
#define LCritical(...)  myLog::getInstance()->getLogger()->log(spdlog::source_loc{__FILE__, __LINE__, SPDLOG_FUNCTION}, spdlog::level::critical, __VA_ARGS__)