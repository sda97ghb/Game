#include <iostream>
#include <string>

#include "Game/MyUtf8.h"
#include "Game/QuestsLoader.h"

using namespace tinyxml2;

namespace section
{
    const char* QUESTS = "quests";
    const char* QUEST = "quest";
    const char* ID = "id";
    const char* TYPE = "type";
    const char* MAIN = "main";
    const char* USUAL = "usual";
    const char* UNIFORMAUTO = "uniformauto";
    const char* STAGE = "stage";
    const char* DESCRIPTION = "description";
    const char* TARGET = "target";
    const char* KILL = "kill";
    const char* COLLECT = "collect";
    const char* COUNT = "count";
    const char* REWARD = "reward";
    const char* EXPERIENCE = "experience";
    const char* MONEY = "money";
    const char* ITEM = "item";
    const char* VALUE = "value";
}

void QuestsLoader::load(std::string filename)
{
   // try
    
        _documentQuestsUniformauto.LoadFile(filename.c_str());
        if (_documentQuestsUniformauto.Error())
        {
            _documentQuestsUniformauto.PrintError();
            std::cout << "Error";
        }
        const XMLElement* questsElement = _documentQuestsUniformauto.RootElement();

        for (const XMLElement* questElement = questsElement->FirstChildElement(section::QUEST);
            questElement != nullptr; questElement = questElement->NextSiblingElement(section::QUEST))
        {
            loadQuest(*questElement);
        }
    
    //catch ()
    
}

void QuestsLoader::loadQuest(const tinyxml2::XMLElement& questElement)
{
    std::string type = questElement.Attribute(section::TYPE);

    if (type == section::UNIFORMAUTO)
        loadUniformQuest(questElement);
    
    if (type == section::USUAL)
        loadUsualQuest(questElement);
    
}

void QuestsLoader::loadUniformQuest(const tinyxml2::XMLElement& questUniformauto)
{
}

void QuestsLoader::loadUsualQuest(const tinyxml2::XMLElement& questUsual)
{
    uint32_t id = questUsual.IntAttribute(section::ID);

    Quest& quest = Quests::instance().createQuests(id);
    quest.setId(id);
    quest.setType(questUsual.Attribute(section::TYPE));

    for (const XMLElement* questStage = questUsual.FirstChildElement(section::STAGE);
        questStage != nullptr; questStage = questStage->NextSiblingElement(section::STAGE))
    {
        quest.setStage(loadStage(*questStage));
    }

    quest.showAllAttribute();
}

QuestStage QuestsLoader::loadStage(const tinyxml2::XMLElement& questStage)
{
    QuestStage stage;

    loadDescription(stage, questStage);
    loadTarget(stage, questStage);
    loadReward(stage, questStage);

    return stage;
}

void QuestsLoader::loadDescription(QuestStage& stage, const tinyxml2::XMLElement& questStage)
{
    std::string description = questStage.FirstChildElement(section::DESCRIPTION)->GetText();
    stage.setDescription(my_utf8::convertToWString(description));
}

void QuestsLoader::loadTarget(QuestStage& stage, const tinyxml2::XMLElement& questStage)
{
    QuestTarget target;
    const XMLElement* targetElement = questStage.FirstChildElement(section::TARGET);
    for (const XMLElement* killElement = targetElement->FirstChildElement(section::KILL);
        killElement != nullptr; killElement = killElement->NextSiblingElement(section::KILL))
    {
        uint32_t id = killElement->IntAttribute(section::ID);
        uint32_t count = killElement->IntAttribute(section::COUNT);
        if (count == 0) count = 1;
        target.setTargetKill(std::move(id), std::move(count));
    }
    for (const XMLElement* collectElement = targetElement->FirstChildElement(section::COLLECT);
        collectElement != nullptr; collectElement = collectElement->NextSiblingElement(section::COLLECT))
    {
        uint32_t id = 0;
        XMLError error = collectElement->QueryUnsignedAttribute(section::ID, &id);
        if (error == XMLError::XML_NO_ATTRIBUTE)
            throw;
        if (error == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
            throw;
        uint32_t count = collectElement->IntAttribute(section::COUNT);
        if (count == 0) count = 1;
        target.setTargetCollect(std::move(id), std::move(count));
    }
    stage.setTarget(std::move(target));
}

void QuestsLoader::loadReward(QuestStage& stage, const tinyxml2::XMLElement& questStage)
{
    QuestReward reward;
    const XMLElement* rewardElement = questStage.FirstChildElement(section::REWARD);
    uint32_t experience = rewardElement->FirstChildElement(section::EXPERIENCE)
        ->IntAttribute(section::VALUE);
    uint32_t money = rewardElement->FirstChildElement(section::MONEY)
        ->IntAttribute(section::VALUE);
    reward.setExperience(std::move(experience));
    reward.setMoney(std::move(money));
    for (const XMLElement* itemsElement = rewardElement->FirstChildElement(section::ITEM);
        itemsElement != nullptr; itemsElement = itemsElement->NextSiblingElement(section::ITEM))
    {
        uint32_t id = itemsElement->IntAttribute(section::ID);
        uint32_t count = itemsElement->IntAttribute(section::COUNT);
        if (count == 0) count = 1;
        reward.setItems(std::move(id), std::move(count));
    }
    stage.setReward(std::move(reward));
}