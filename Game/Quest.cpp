#include "Game/Quest.h"
#include <iostream>
#include "MyUtf8.h"

const uint32_t Quest::getId() const
{
    return _id;
}
const std::string Quest::getType() const
{
    return _type;
}
const std::vector<QuestStage> Quest::getStage() const
{
    return _stage;
}

void Quest::showAllAttribute()
{
    std::wcout << getId() << " " << my_utf8::convertToWString(getType()) << std::endl;
    
    for (auto s : _stage)
    {
        s.showAll();
    }
}

void Quest::setId(uint32_t id)
{
    _id = id;
}
void Quest::setType(std::string type)
{
    _type = type;
}
void Quest::setStage(QuestStage stage)
{
    _stage.push_back(stage);
}