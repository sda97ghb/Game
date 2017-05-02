#include <algorithm>
#include <iostream>

#include "Arena/Entity/Evented.h"

void Evented::addEventCallback(const Event& event, EventCallback callback)
{
    try
    {
        _events.at(event).push_back(callback);
    }
    catch (std::out_of_range&)
    {
        _events.emplace(event, std::list<EventCallback>{callback});
    }
}

std::list<EventCallback>& Evented::eventCallbacks(const Event& event)
{
    try
    {
        return _events.at(event);
    }
    catch (std::out_of_range&)
    {
        static std::list<EventCallback> emptyCallbackList {};
        return emptyCallbackList;
    }
}

void Evented::callEventCallbacks(const Event& event)
{
    for (EventCallback& callback : eventCallbacks(event))
        callback();
}
