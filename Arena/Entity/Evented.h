#ifndef EVENTED_H
#define EVENTED_H

#include <functional>
#include <list>
#include <map>

using Event = const std::string;
using EventCallback = std::function<void()>;

#define EVENT(eventName) \
    Event eventName##Event = #eventName;

#define METHOD_CALLBACK(methodName) [&](){methodName();}

class Evented
{
public:
    void addEventCallback(const Event& event, EventCallback callback);
    std::list<EventCallback>& eventCallbacks(const Event& event);

    void callEventCallbacks(const Event& event);

private:
    std::map<Event, std::list<EventCallback>> _events;
};

#endif // EVENTED_H
