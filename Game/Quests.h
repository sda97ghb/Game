#ifndef QUESTS_H
#define QUESTS_H

#include <map>

#include "Game/Quest.h"

class Quests
{
public:
    static Quests& instance()
    {
        static Quests instance;
        return instance;
    }

    Quests(Quests const&) = delete;
    Quests(Quests&&) = delete;
    Quests& operator=(Quests const&) = delete;
    Quests& operator=(Quests &&) = delete;

    std::map<uint32_t, Quest> getQuest();//id
    Quest& createQuests(uint32_t);

private:
    Quests(){}
    ~Quests(){}
    //bool _quests = true;
    std::map<uint32_t, Quest> _quests;
};

#endif // QUESTS_H