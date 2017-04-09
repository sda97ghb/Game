#ifndef TIMERSENSOR_H
#define TIMERSENSOR_H

#include <functional>

#include "SFML/System/Clock.hpp"

#include "Arena/Updatable.h"

class TimerSensor : public Updatable
{
public:
    using OnTimeoutCallback = std::function<void()>;

    TimerSensor();

    void setTime(float time);
    void setOnTimeoutCallback(const OnTimeoutCallback& onTimeoutCallback);

    void start();
    void stop();

    void update();

private:
    float _time;

    OnTimeoutCallback _onTimeoutCallback;

    bool _isRunned;

    sf::Clock _clock;
};

#endif // TIMERSENSOR_H
