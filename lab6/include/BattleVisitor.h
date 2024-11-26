#ifndef BATTLEVISITOR_H
#define BATTLEVISITOR_H

#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>

class BattleVisitor {
private:
    std::vector<std::shared_ptr<Observer>> observers;

    void notify(const std::string &event);

public:
    void addObserver(std::shared_ptr<Observer> observer);
    void conductBattle(std::vector<std::unique_ptr<NPC>> &npcs, double range);
};

#endif