#ifndef NPCTHREADS_H
#define NPCTHREADS_H

#include <vector>
#include <thread>
#include <condition_variable>
#include <shared_mutex>
#include <queue>
#include <memory>
#include <string>
#include "NPC.h"
#include "Observer.h"

void battleThreadFunction(
    std::vector<std::unique_ptr<NPC>>& npcs,
    std::shared_mutex& mtx,
    std::queue<std::pair<std::string, std::string>>& battleQueue,
    std::condition_variable_any& battleCV,
    bool& game_over,
    std::vector<std::shared_ptr<Observer>>& observers);

void movementThreadFunction(
    std::vector<std::unique_ptr<NPC>>& npcs,
    std::shared_mutex& mtx,
    std::queue<std::pair<std::string, std::string>>& battleQueue,
    std::condition_variable_any& battleCV,
    bool& game_over);

#endif 
