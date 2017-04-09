#include "TimerSensor.h"

TimerSensor::TimerSensor() :
    _time(0.0f),
    _onTimeoutCallback([](){}),
    _isRunned(false)
{}

void TimerSensor::setTime(float time)
{
    _time = time;
}

void TimerSensor::setOnTimeoutCallback(const OnTimeoutCallback& onTimeoutCallback)
{
    _onTimeoutCallback = onTimeoutCallback;
}

void TimerSensor::start()
{
    _clock.restart();
    _isRunned = true;
}

void TimerSensor::stop()
{
    _isRunned = false;
}

void TimerSensor::update()
{
    if (!_isRunned)
        return;

    if (_clock.getElapsedTime().asMilliseconds() < _time)
        return;

    _onTimeoutCallback();
    _isRunned = false;
}
