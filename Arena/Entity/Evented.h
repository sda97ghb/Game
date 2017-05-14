#ifndef EVENTED_H
#define EVENTED_H

#include <functional>
#include <list>
#include <map>

using Event = const std::string;
using EventCallback = std::function<void()>;

#define EVENT(eventName) \
    Event eventName##Event = #eventName;

#define METHOD_CALLBACK(methodName) \
    std::bind(&methodName, this)
//    [&](){methodName();}

/// @brief Добавляет возможность использования механизма событий
/// для объектов какого-либо класса.
/// @details Для этого класс должен быть унаследован от Evented.
/// Все существа наследуются от этого класса.
class Evented
{
public:
    /// @brief Добавляет функцию обработки события.
    void addEventCallback(const Event& event, EventCallback callback);

    /// @brief Список всех коллбэков для события.
    std::list<EventCallback>& eventCallbacks(const Event& event);

    /// @brief Вызвать событие.
    void callEventCallbacks(const Event& event);

private:
    std::map<Event, std::list<EventCallback>> _events; ///< соответствие между событиями и их коллбэками
};

#endif // EVENTED_H
