#pragma once
#include <iostream>
#include <future>
#include <thread>
#include <fstream>
#include <chrono>

#include "boost/date_time.hpp"
#include "boost/date_time/posix_time/posix_time_types.hpp"
#define DEBUG

namespace bene
{

template <typename Fn, typename... Args>
auto do_async_log(std::ostream& os, Fn&& fn, Args&&... args) ->
	std::future<decltype(fn(args...))>
{
	os << "[TID=" << std::this_thread::get_id()
	   << "] Starting to invoke function..." << std::endl;
	auto bound = std::bind(fn, std::forward<Args&&...>(args...));
	return std::async([b=move(bound),&os]() mutable {
		auto result = b();
		os << "[TID=" << std::this_thread::get_id()
		   << "] ...invocation done, returning " << result << std::endl;
		return result;
	});
}

class Logger
{
        int loglvl;

        std::ofstream out;
    public:
        enum LogLevel {
            Crit, Error, Warning, Msg, Debug, Trace, NUM_LEVELS,
        };

        static Logger& Instance()
        {
            static Logger instance;
            return instance;
        }

        int GetLogLevel() const
        {
            return loglvl;
        }

        void SetLogLevel(int lvl)
        {
            loglvl = lvl;
        }

        std::ostream& GetStream(int lvl);

    private:
        Logger();
        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;
};

};

#ifdef DEBUG
	#define LOG(lvl_, msg_) \
	    do { \
	        bene::Logger& L_ = bene::Logger::Instance(); \
	        L_.GetStream(bene::Logger::lvl_) << msg_ << std::endl; \
	    } while (0)
#else
	#define LOG(lvl_, msg_)
#endif
