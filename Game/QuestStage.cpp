#include "Game/QuestStage.h"
#include <iostream>

const std::wstring& QuestStage::getDescription() const
{
    return _description;
}
const QuestTarget& QuestStage::getTarget() const
{
    return _target;
}
const QuestReward& QuestStage::getReward() const
{
    return _reward;
}

void QuestStage::setDescription(std::wstring description)
{
    _description = description;
}
void QuestStage::setTarget(QuestTarget&& target)
{
    _target = std::move(target);
}
void QuestStage::setReward(QuestReward&& reward)
{
    _reward = std::move(reward);
}

void QuestStage::showAll()
{
    std::wcout << getDescription() << std::endl;
    for (auto tk : _target.getTargetKill())
        std::wcout << tk.first << " " << tk.second << std::endl;
    for (auto tc : _target.getTargetCollect())
        std::wcout << tc.first << " " << tc.second << std::endl;

    std::wcout << _reward.getExperience() << std::endl;
    std::wcout << _reward.getMoney() << std::endl;

    for (auto i : _reward.getItems())
        std::wcout << i.first << " " << i.second << std::endl;

    std::wcout << std::endl;
}
