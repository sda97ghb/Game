#include <Game/QuestTarget.h>
#include <iostream>

const std::list<std::pair<uint32_t, uint32_t>> QuestTarget::getTargetKill() const
{
    return _targetKill;
}
const std::list<std::pair<uint32_t, uint32_t>> QuestTarget::getTargetCollect() const
{
    return _targetCollect;
}

void QuestTarget::setTargetKill(uint32_t&& id, uint32_t&& count)
{
    _targetKill.push_back(std::pair<uint32_t, uint32_t>(std::move(id), std::move(count)));
}
void QuestTarget::setTargetCollect(uint32_t&& id, uint32_t&& count)
{
    _targetCollect.push_back(std::pair<uint32_t, uint32_t>(std::move(id), std::move(count)));
}