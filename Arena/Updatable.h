#ifndef UPDATABLE_H
#define UPDATABLE_H

/// @brief Базовый класс обновляемого объекта.
class Updatable
{
public:
    Updatable();
    virtual ~Updatable();

    virtual void update() = 0;
};

#endif // UPDATABLE_H
