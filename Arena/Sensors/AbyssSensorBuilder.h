#ifndef ABYSSSENSORBUILDER_H
#define ABYSSSENSORBUILDER_H

class b2Body;

class AbyssSensor;

class AbyssSensorBuilder
{
public:
    AbyssSensorBuilder();

    AbyssSensorBuilder& setDx(float dx);
    AbyssSensorBuilder& setDy(float dy);

    AbyssSensorBuilder& setBody(b2Body* body);

    AbyssSensor* build();

private:
    float _dx;
    float _dy;

    b2Body* _body;
};

#endif // ABYSSSENSORBUILDER_H
