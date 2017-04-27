#ifndef CONTACTSENSORBUILDER_H
#define CONTACTSENSORBUILDER_H

#include <cstdint>

class b2Body;
class b2Shape;

class ContactSensor;

class ContactSensorBuilder
{
public:
    ContactSensorBuilder();

    ContactSensorBuilder& setType(uint32_t type);
    ContactSensorBuilder& setPosition(float dx, float dy);
    ContactSensorBuilder& setSize(float width, float height);
    ContactSensorBuilder& setBody(b2Body* body);
    ContactSensorBuilder& setShape(b2Shape* shape);

    ContactSensor* build();

private:
    uint32_t _type;

    float _dx;
    float _dy;

    float _width;
    float _height;

    b2Body* _body;

    b2Shape* _shape;
};

#endif // CONTACTSENSORBUILDER_H
