#ifndef QUESTSLOADER_H
#define QUESTSLOADER_H

#include "TinyXml2/tinyxml2.h"

#include "Game/Quests.h"
#include "Game/Quest.h"
#include "Game/QuestStage.h"
#include "Game/QuestTarget.h"
#include "Game/QuestReward.h"

class QuestsLoader
{
public:
    QuestsLoader()
    {
    }

    void load(std::string filename);
    void loadQuest(const tinyxml2::XMLElement& questElement);
    void loadUniformQuest(const tinyxml2::XMLElement& questUniformauto);
    void loadUsualQuest(const tinyxml2::XMLElement& questUsual);

    QuestStage loadStage(const tinyxml2::XMLElement& questStage);
    void loadDescription(QuestStage& stage, const tinyxml2::XMLElement& questStage);
    void loadTarget(QuestStage& stage, const tinyxml2::XMLElement& questStage);
    void loadReward(QuestStage& stage, const tinyxml2::XMLElement& questStage);

private:
    tinyxml2::XMLDocument _documentQuestsUniformauto;

};

#endif // QUESTSLOADER_H