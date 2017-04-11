#ifndef QUEST_H
#define QUEST_H

#include <cstdint>
#include <string>
#include <vector>

#include "Game/QuestStage.h"

class Quest
{
public:
    Quest()
    {
    }
    Quest(uint32_t id) :
        _id(id),
        _currentStage(0),
        _isActive(false)
    {
    }

    const uint32_t getId() const;
    const std::string getType() const;
    const std::vector<QuestStage> getStage() const;

    void setId(uint32_t id);
    void setType(std::string type);
    void setStage(QuestStage stage);

    void showAllAttribute();
private:
    bool _isActive;
    uint32_t _currentStage;
    uint32_t _id;
    std::string _type;
    std::vector<QuestStage> _stage;
};

#endif // QUEST_H