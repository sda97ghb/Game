#ifndef OBJECTCOUNTER_H
#define OBJECTCOUNTER_H

#include <algorithm>
#include <list>

/**
 *  @brief Подсчитывает количество объектов указанного типа и возвращает
 *  их список.
 *
 *  Использование:
 *  -# В каждом конструкторе класса, объекты которого надо подсчитывать:
 *      @code ObjectCounter<your class name>::addObject(this); @endcode
 *
 *  -# В дестркторе класса, объекты которого надо подсчитывать:
 *      @code ObjectCounter<your class name>::removeObject(this); @endcode
 *
 *  -# В любом месте, где вам это нужно:
 *      - Узнать количество объектов:
 *          @code ObjectCounter<your class name>::count() @endcode
 *      - Получить список всех объектов:
 *          @code ObjectCounter<your class name>::objects()
 *              // => std::list<your class name pointer> @endcode
 *
 *  @note
 *      Этот класс не может подсчитывать объекты, которые не используют
 *      @a addObject и @a removeObject в их конструкторах и деструкторе.
 *      Например вы не можете при помощи этого класса узнать список всех
 *      std::string или int использованных в вашей программе.
 */

template <typename T>
class ObjectCounter
{
public:
    /// @brief Возвращает список всех объектов указаного типа.
    static const std::list<T*> objects()
    {
        return _objects;
    }

    /// @brief Запоминает указанный объект.
    static void addObject(T* object)
    {
        _objects.push_back(object);
    }

    /// @brief Забывает указанный объект.
    static void removeObject(T* object)
    {
        _objects.erase(std::find(_objects.begin(), _objects.end(), object));
    }

    /// @brief Возвращает количество объектов указанного типа.
    static size_t count()
    {
        return _objects.size();
    }

private:
    static std::list<T*> _objects; ///< Объекты указанного типа.
};

template <typename T>
std::list<T*> ObjectCounter<T>::_objects;

#define OBJECT_COUNTER_ADD_THIS \
    using this_t_ptr = decltype(this); \
    using this_t = std::remove_pointer<this_t_ptr>::type; \
    ObjectCounter<this_t>::addObject(this);

#define OBJECT_COUNTER_REMOVE_THIS \
    using this_t_ptr = decltype(this); \
    using this_t = std::remove_pointer<this_t_ptr>::type; \
    ObjectCounter<this_t>::removeObject(this);

#endif // OBJECTCOUNTER_H
