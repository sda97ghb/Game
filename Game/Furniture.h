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

    sf::Sprite& sprite();

    /// \brief Возвращает ссылку на текстуру.
    sf::Texture& texture();

    virtual void testPlayerOnIt() = 0;

private:
    sf::Sprite _sprite;
    sf::Texture _texture; ///< Текстура.
};

#endif // FURNITURE_H
