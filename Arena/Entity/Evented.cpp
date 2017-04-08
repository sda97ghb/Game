#include <algorithm>
#include <iostream>

#include "Arena/Entity/Evented.h"

void Evented::setEventCallback(const Event& event, EventCallback callback)
{
    _events[event] = callback;
}

const EventCallback& Evented::eventCallback(const Event& event) const
{
    try
    {
        return _events.at(event);
    }
    catch (std::out_of_range&)
    {
        return DO_NOTHING_CALLBACK;
    }
}

void Evented::callEventCallback(const Event& event)
{
    const EventCallback& callback = eventCallback(event);
    callback();
}
