#include "Arena/Sensors/TimerSensor.h"
#include "Arena/Sensors/TimerSensorBuilder.h"

TimerSensorBuilder::TimerSensorBuilder() :
    _time(0.0f),
    _onTimeoutCallback([](){})
{}

TimerSensorBuilder& TimerSensorBuilder::setTime(float time)
{
    _time = time;
    return *this;
}

TimerSensorBuilder& TimerSensorBuilder::setOnTimeoutCallback(const std::function<void ()>& callback)
{
    _onTimeoutCallback = callback;
    return *this;
}

TimerSensor* TimerSensorBuilder::build()
{
    TimerSensor* sensor = new TimerSensor;
    sensor->setTime(_time);
    sensor->setOnTimeoutCallback(_onTimeoutCallback);
    return sensor;
}
