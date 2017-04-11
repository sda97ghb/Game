#ifndef QUESTSTAGE_H
#define QUESTSTAGE_H

#include <string>

#include "Game/QuestTarget.h"
#include "Game/QuestReward.h"

class QuestStage
{
public:
    QuestStage()
    {
    }

    const std::wstring& getDescription() const;
    const QuestTarget& getTarget() const;
    const QuestReward& getReward() const;

    void setDescription(std::wstring description);
    void setTarget(QuestTarget&& target);
    void setReward(QuestReward&& reward);

    void showAll();
private:
    std::wstring _description;
    QuestTarget _target;
    QuestReward _reward;
};

#endif // QUESTSTAGE_H