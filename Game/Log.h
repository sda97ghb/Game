#ifndef LOG_H
#define LOG_H

#include <list>
#include <string>

class Log
{
public:
    static Log& instance();

    void push(const std::string& line);

    const std::list<std::string>& lines() const;

    int logSize() const;
    void setLogSize(int logSize);

private:
    Log();

    std::list<std::string> _messages;

    int _logSize;
};

#endif // LOG_H
