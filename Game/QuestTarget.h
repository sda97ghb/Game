#ifndef QUESTTARGET_H
#define QUESTTARGET_H

#include <list>
#include <cstdint>

class QuestTarget
{
public:
    QuestTarget()
    {
    }

    const std::list<std::pair<uint32_t, uint32_t>> getTargetKill() const;
    const std::list<std::pair<uint32_t, uint32_t>> getTargetCollect() const;

    void setTargetKill(uint32_t&& id, uint32_t&& count);
    void setTargetCollect(uint32_t&& id, uint32_t&& count);

private:
    std::list<std::pair<uint32_t, uint32_t>> _targetKill;
    std::list<std::pair<uint32_t, uint32_t>> _targetCollect;
};

#endif // QUESTTARGET_H