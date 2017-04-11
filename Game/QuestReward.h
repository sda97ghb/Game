#ifndef QUESTREWARD_H
#define QUESTREWARD_H

#include <list>
#include <cstdint>

class QuestReward
{
public:
    QuestReward()
    {
    }

    const uint32_t getExperience() const;
    const uint32_t getMoney() const;
    const std::list<std::pair<uint32_t, uint32_t>> getItems() const;

    void setExperience(uint32_t&& experience);
    void setMoney(uint32_t&& money);
    void setItems(uint32_t&& id, uint32_t&& count);

private:
    uint32_t _experience;
    uint32_t _money;
    std::list<std::pair<uint32_t, uint32_t>> _items;
};

#endif // QUESTREWARD_H