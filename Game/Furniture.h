/// \file
/// \brief Содержит базовый класс предметов взаимодействия.

#ifndef FURNITURE_H
#define FURNITURE_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

/// \brief Базовый класс для всех предметов с которыми
/// может взаимодействовать игрок или которые могут
/// взаимодействовать с игроком.
/// \note При создании предметов, являющихся жидкостями
/// наследуйтесь не от этого класса, а от Liquids.
class Furniture
{
public:
    Furniture();

    /// \brief Устанавливает текстуру. Текстура предполагается зацикленной.
    void setTexture(const std::string& filename);

    /// \brief Возвращает ссылку на текстуру.
    sf::Texture& texture();

    /// \brief Проверяет, если игрок находится перед объектом,
    /// то совершает определенное действие, в зависимости от
    /// конкретного объекта взаимодействия.
    virtual void testPlayerOnIt() = 0;

private:
    sf::Texture _texture; ///< Текстура.
};

#endif // FURNITURE_H
