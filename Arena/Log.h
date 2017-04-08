/// \file
/// \brief Содержит класс лога (чата).

#ifndef LOG_H
#define LOG_H

#include <cstdint>
#include <list>
#include <string>

/// \brief Класс лога (чата).
/// \note Вы можете обратиться к логу из любого места вызвав Log::instance()
class Log
{
public:
    /// \brief Возвращает ссылку на объект лога.
    static Log& instance();

    /// \brief Добавляет новое сообщение.
    void push(const std::string& line);

    /// \brief Возвращает константный список всех сообщений.
    const std::list<std::string>& lines() const;

    /// \brief Возвращает максимальное количество сообщений, которое может
    /// находится одновременно в логе.
    int logSize() const;

    /// \brief Устанавливает максимальное количество одновременных сообщений.
    void setLogSize(int logSize);

private:
    Log();

    std::list<std::string> _messages; ///< сообщения

    uint32_t _logSize; ///< максимально возможное число одновременных сообщений
};

#endif // LOG_H
