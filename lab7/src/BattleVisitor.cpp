#include "../include/BattleVisitor.h"

void BattleVisitor::notify(const std::string &event) {
    for (auto &observer : observers) {
        observer->logEvent(event);
    }
}

void BattleVisitor::addObserver(std::shared_ptr<Observer> observer) {
    observers.push_back(observer);
}

void BattleVisitor::conductBattle(std::vector<std::unique_ptr<NPC>> &npcs, double range) {
    for (size_t i = 0; i < npcs.size(); ++i) {
        for (size_t j = i + 1; j < npcs.size();) {
            if (npcs[i]->distanceTo(*npcs[j]) <= range) {
                bool firstWins = npcs[i]->fight(*npcs[j]);
                bool secondWins = npcs[j]->fight(*npcs[i]);

                if (firstWins && secondWins) {
                    notify(npcs[i]->getName() + " и " + npcs[j]->getName() + " погибли.");
                    npcs.erase(npcs.begin() + j);
                    npcs.erase(npcs.begin() + i);
                    --i; // Уменьшаем индекс, так как мы удалили два элемента
                    break;
                } else if (firstWins) {
                    notify(npcs[i]->getName() + " убил " + npcs[j]->getName() + ".");
                    npcs.erase(npcs.begin() + j);
                } else if (secondWins) {
                    notify(npcs[j]->getName() + " убил " + npcs[i]->getName() + ".");
                    npcs.erase(npcs.begin() + i);
                    --i; // Уменьшаем индекс, так как удален элемент на индексе i
                    break;
                } else {
                    ++j;
                }
            } else {
                ++j;
            }
        }
    }
}