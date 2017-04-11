#include <Game/Quests.h>

std::map<uint32_t, Quest> Quests::getQuest()
{
    return _quests;
}

Quest& Quests::createQuests(uint32_t id)
{
    _quests.emplace(id, Quest(id));
    return _quests[id];
}