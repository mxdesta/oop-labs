#include "../include/NPCThreads.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <iostream>

void battleThreadFunction(
    std::vector<std::unique_ptr<NPC>>& npcs,
    std::shared_mutex& mtx,
    std::queue<std::pair<std::string, std::string>>& battleQueue,
    std::condition_variable_any& battleCV,
    bool& game_over,
    std::vector<std::shared_ptr<Observer>>& observers) {
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> die(1, 6);

    while (!game_over) {
        std::unique_lock<std::shared_mutex> lock(mtx);
        battleCV.wait(lock, [&]{ return !battleQueue.empty() || game_over; });

        if (game_over) {
            break;
        }

        auto battlePair = battleQueue.front();
        battleQueue.pop();
        lock.unlock();

        auto findNPC = [&](const std::string& name) -> std::unique_ptr<NPC>* {
            for (auto& npcPtr : npcs) {
                if (npcPtr->getName() == name) {
                    return &npcPtr;
                }
            }
            return nullptr;
        };

        std::unique_lock<std::shared_mutex> lock2(mtx);
        auto npc1Ptr = findNPC(battlePair.first);
        auto npc2Ptr = findNPC(battlePair.second);

        if (npc1Ptr && npc2Ptr && (*npc1Ptr) && (*npc2Ptr)) {
            int attack1 = die(gen);
            int defense2 = die(gen);
            int attack2 = die(gen);
            int defense1 = die(gen);

            if (attack1 > defense2) {
                npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
                    [&](const std::unique_ptr<NPC>& npc) { return npc->getName() == battlePair.second; }), npcs.end());
            }

            if (attack2 > defense1) {
                npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
                    [&](const std::unique_ptr<NPC>& npc) { return npc->getName() == battlePair.first; }), npcs.end());
            }

            if (attack1 > defense2 && attack2 > defense1) {
                npcs.erase(std::remove_if(npcs.begin(), npcs.end(),
                    [&](const std::unique_ptr<NPC>& npc) { return npc->getName() == battlePair.first || npc->getName() == battlePair.second; }), npcs.end());
            }

            std::string eventMessage;
            if (attack1 > defense2 && attack2 > defense1) {
                eventMessage = battlePair.first + " and " + battlePair.second + " killed each other.";
            } else if (attack1 > defense2) {
                eventMessage = battlePair.first + " killed " + battlePair.second;
            } else if (attack2 > defense1) {
                eventMessage = battlePair.second + " killed " + battlePair.first;
            }

            for (auto& observer : observers) {
                observer->logEvent(eventMessage);
            }
        }
        lock2.unlock();
    }
}

void movementThreadFunction(
    std::vector<std::unique_ptr<NPC>>& npcs,
    std::shared_mutex& mtx,
    std::queue<std::pair<std::string, std::string>>& battleQueue,
    std::condition_variable_any& battleCV,
    bool& game_over) {
    
    std::random_device rd;
    std::mt19937 gen(rd());

    while (!game_over) {
        // Перемещение NPC
        {
            std::shared_lock<std::shared_mutex> lock(mtx);
            for (auto& npc : npcs) {
                int movementDistance = npc->getMovementDistance();
                std::uniform_int_distribution<> dxDist(-movementDistance, movementDistance);
                std::uniform_int_distribution<> dyDist(-movementDistance, movementDistance);
                int dx = dxDist(gen);
                int dy = dyDist(gen);

                // Обновление позиции NPC
                npc->move(dx, dy);
            }
        }

        // Вывод текущего состояния NPC

        // Проверка на близость NPC для инициирования битвы
        {
            std::unique_lock<std::shared_mutex> lock(mtx);
            for (size_t i = 0; i < npcs.size(); ++i) {
                for (size_t j = i + 1; j < npcs.size(); ++j) {
                    if (npcs[i]->distanceTo(*npcs[j]) <= npcs[i]->getKillingRange() ||
                        npcs[j]->distanceTo(*npcs[i]) <= npcs[j]->getKillingRange()) {
                        
                        // Добавление NPC в очередь битв
                        battleQueue.push({npcs[i]->getName(), npcs[j]->getName()});
                    }
                }
            }
        }

        // Уведомление о новой битве
        battleCV.notify_one();

        // Задержка между итерациями
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
