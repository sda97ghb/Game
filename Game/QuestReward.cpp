#include "Game/QuestReward.h"
#include <iostream>

const uint32_t QuestReward::getExperience() const
{
    return _experience;
}
const uint32_t QuestReward::getMoney() const
{
    return _money;
}
const std::list<std::pair<uint32_t, uint32_t>> QuestReward::getItems() const
{
    return _items;
}

void QuestReward::setExperience(uint32_t&& experience)
{
    _experience = std::move(experience);
}
void QuestReward::setMoney(uint32_t&& money)
{
    _money = std::move(money);
}
void QuestReward::setItems(uint32_t&& id, uint32_t&& count)
{
    _items.push_back(std::pair<uint32_t, uint32_t>(std::move(id), std::move(count)));
}