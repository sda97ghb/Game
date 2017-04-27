#ifndef UPDATABLE_H
#define UPDATABLE_H

class Updatable
{
public:
    Updatable();
    virtual ~Updatable();

    virtual void update() = 0;
};

#endif // UPDATABLE_H
