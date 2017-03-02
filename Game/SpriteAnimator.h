/// \file
/// \brief Содержит класс, ответственный за анимацию спрайтов.

#ifndef SPRITEANIMATOR_H
#define SPRITEANIMATOR_H

#include <map>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"

/// \brief Класс, ответственный за анимацию спрайтов.
class SpriteAnimator
{
public:
    struct NoAnimationGroupException : std::logic_error
    {
        NoAnimationGroupException(const std::string& groupname) :
            std::logic_error(
                std::string("this animator have no group with name \"") + groupname + "\"")
        {}
    };

    /// \brief Группа кадров, относящихся к одной анимации.
    struct AnimationGroup
    {
        int x; ///< координа левого верхнего пикселя первого кадра по X
        int y; ///< координа левого верхнего пикселя первого кадра по Y
        int frameWidth; ///< ширина кадра
        int frameHeight; ///< высота кадра
        int numberOfFrames; ///< число кадров
        enum {
            vertical,  ///< кадры расположены вертикально
            horizontal ///< кадры расположены горизонтально
        } orientation; ///< ориентация развертки
    };

    SpriteAnimator();

    /// \brief Возвращает заготовку спрайта с наложенной текстурой текущего кадра.
    sf::Sprite& sprite();

    /// \brief Устанавливает текстуру, из которой потом будут выбираться группы
    void setTexture(const std::string& filename);

    /// \brief Добавляет или изменяет группу анимации.
    /// \param [in] name имя группы
    /// \param [in] x,y координата левого верхнего пикселя первого кадра
    /// \param [in] frameWidth ширина кадра
    /// \param [in] frameHeight высота кадра
    /// \param [in] numberOfFrames число кадров
    /// \param [in] isHorizontal true для горизонтальной развертки, false для вертикальной
    void setAnimationGroup(const std::string& name,
                           int x, int y, int frameWidth, int frameHeight,
                           int numberOfFrames, bool isHorizontal = true);

    /// \brief Устанавлиает зацикленное воспроизведение указанной группы.
    void setCurrentGroup(const std::string& groupname);

    /// \brief Воспроизводит указанную группу один раз и возвращается к предыдущей
    void playGroup(const std::string& groupname);

    /// \brief Переходит к следующему кадру.
    void nextFrame();

    /// \brief Если с предыдущего обновления прошло достаточно времени
    /// переходит к следующему кадру.
    void update();

    /// \brief Имя текущей группы.
    const std::string& currentGroup() const;

    /// \brief Останавливает аниматор.
    void stop();

private:
    /// \brief Возвращается к предыдущей группе.
    void restoreGroup();

    sf::Texture _texture; ///< Текстура
    sf::Sprite _sprite; ///< Анимируемый спрайт

    std::map<std::string, AnimationGroup> _animationGroups; ///< Группы анимаций

    std::string _currentGroup; ///< Текущая группа
    int _currentFrame; ///< Текущий кадр

    std::string _previousGroup; ///< Запомненная группа
    bool _playOnce; ///< Воспроизвести текущую группу один раз или зацикленно

    int _animationDelay; ///< Задержка перед показом следующего кадра в мс.

    sf::Clock _clock; ///< Таймер, для рассчета задержки.

    bool _isStopped;
};

#endif // SPRITEANIMATOR_H
