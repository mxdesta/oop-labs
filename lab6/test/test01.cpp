#include "../include/NPCFactory.h"
#include "../include/BattleVisitor.h"
#include "../include/ConsoleLogger.h"
#include <gtest/gtest.h>


TEST(NPCFactoryTest, CreateWanderingKnight) {
    auto knight = NPCFactory::createNPC("WanderingKnight", "Knight1", 100, 100);
    EXPECT_EQ(knight->getType(), "WanderingKnight");
    EXPECT_EQ(knight->getName(), "Knight1");
    EXPECT_EQ(knight->getX(), 100);
    EXPECT_EQ(knight->getY(), 100);
}

TEST(NPCFactoryTest, CreateElf) {
    auto elf = NPCFactory::createNPC("Elf", "Elf1", 200, 200);
    EXPECT_EQ(elf->getType(), "Elf");
    EXPECT_EQ(elf->getName(), "Elf1");
    EXPECT_EQ(elf->getX(), 200);
    EXPECT_EQ(elf->getY(), 200);
}

TEST(NPCFactoryTest, CreateDragon) {
    auto dragon = NPCFactory::createNPC("Dragon", "Dragon1", 150, 150);
    EXPECT_EQ(dragon->getType(), "Dragon");
    EXPECT_EQ(dragon->getName(), "Dragon1");
    EXPECT_EQ(dragon->getX(), 150);
    EXPECT_EQ(dragon->getY(), 150);
}

TEST(NPCFactoryTest, UnknownTypeThrowsException) {
    EXPECT_THROW(NPCFactory::createNPC("UnknownType", "InvalidNPC", 0, 0), std::invalid_argument);
}


TEST(BattleVisitorTest, ConductBattleAllNPCDie) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(NPCFactory::createNPC("WanderingKnight", "Knight1", 100, 100));
    npcs.push_back(NPCFactory::createNPC("Dragon", "Dragon1", 101, 101));

    BattleVisitor battle;
    auto logger = std::make_shared<ConsoleLogger>();
    battle.addObserver(logger);

    battle.conductBattle(npcs, 10.0);

    EXPECT_EQ(npcs.size(), 0);
}


TEST(BattleVisitorTest, ObserverNotification) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(NPCFactory::createNPC("WanderingKnight", "Knight1", 100, 100));
    npcs.push_back(NPCFactory::createNPC("Dragon", "Dragon1", 101, 101));

    BattleVisitor battle;
    auto logger = std::make_shared<ConsoleLogger>();
    battle.addObserver(logger);

    EXPECT_NO_THROW(battle.conductBattle(npcs, 10.0));
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
