#ifndef EVENTED_H
#define EVENTED_H

#include <functional>
#include <map>

using Event = const std::string;
using EventCallback = std::function<void()>;
static const EventCallback DO_NOTHING_CALLBACK([](){});

#define EVENT(eventName) \
    Event eventName##Event = #eventName;

#define METHOD_CALLBACK(methodName) [&](){methodName();}

class Evented
{
public:
    void setEventCallback(const Event& event, EventCallback callback);
    const EventCallback& eventCallback(const Event& event) const;

    void callEventCallback(const Event& event);

private:
    std::map<Event, EventCallback> _events;
};

#endif // EVENTED_H
