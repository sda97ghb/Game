#ifndef TIMERSENSORBUILDER_H
#define TIMERSENSORBUILDER_H

#include <functional>

class TimerSensor;

class TimerSensorBuilder
{
public:
    TimerSensorBuilder();

    TimerSensorBuilder& setTime(float time);
    TimerSensorBuilder& setOnTimeoutCallback(const std::function<void()>& callback);

    TimerSensor* build();

private:
    float _time;
    std::function<void()> _onTimeoutCallback;
};

#endif // TIMERSENSORBUILDER_H
