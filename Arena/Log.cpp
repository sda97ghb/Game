#include "Arena/Log.h"

Log::Log() :
    _logSize(10)
{
}

Log& Log::instance()
{
    static Log instance;
    return instance;
}

int Log::logSize() const
{
    return _logSize;
}

void Log::setLogSize(int logSize)
{
    _logSize = logSize;
    _messages.clear();
}

void Log::addMessage(const std::string& line)
{
    if (_messages.size() >= _logSize)
        _messages.pop_front();
    _messages.push_back(line);
}

const std::list<std::string>& Log::lines() const
{
    return _messages;
}
