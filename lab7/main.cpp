#include "../include/NPCFactory.h"
#include "../include/BattleVisitor.h"
#include "../include/ConsoleLogger.h"
#include "../include/NPCThreads.h"
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include <chrono>
#include <random>
#include <iostream>

constexpr int MAP_WIDTH = 100;
constexpr int MAP_HEIGHT = 100;
constexpr int NPC_COUNT = 50;
constexpr int GAME_DURATION = 30; 

std::mutex cout_mutex;


void printMap(const std::vector<std::unique_ptr<NPC>>& npcs, std::shared_mutex& mtx) {
    const int mapWidth = MAP_WIDTH;
    const int mapHeight = MAP_HEIGHT;


    std::vector<std::string> map(mapHeight, std::string(mapWidth, ' '));


    std::shared_lock<std::shared_mutex> lock(mtx);


    for (const auto& npc : npcs) {
        int x = npc->getX();
        int y = npc->getY();

        if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
            continue;
        }

        char symbol = 'N';
        if (npc->getType() == "WanderingKnight") symbol = 'W';
        else if (npc->getType() == "Elf") symbol = 'E';
        else if (npc->getType() == "Dragon") symbol = 'D';


        map[y][x] = symbol;
    }


    std::lock_guard<std::mutex> coutLock(cout_mutex);
    std::cout << "+" << std::string(mapWidth, '-') << "+\n";
    for (const auto& row : map) {
        std::cout << "|" << row << "|\n";
    }
    std::cout << "+" << std::string(mapWidth, '-') << "+\n";
}

void generateNPCs(std::vector<std::unique_ptr<NPC>>& npcs, std::shared_mutex& mtx) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDist(0, MAP_WIDTH - 1);
    std::uniform_int_distribution<> yDist(0, MAP_HEIGHT - 1);

    for (int i = 0; i < NPC_COUNT; ++i) {
        int x = xDist(gen);
        int y = yDist(gen);
        std::string name = "NPC" + std::to_string(i);
        std::string type;

        switch (i % 3) {
            case 0: type = "WanderingKnight"; break;
            case 1: type = "Elf"; break;
            case 2: type = "Dragon"; break;
        }

        std::unique_lock<std::shared_mutex> lock(mtx);
        npcs.push_back(NPCFactory::createNPC(type, name, x, y));
    }
}

int main() {
    std::vector<std::unique_ptr<NPC>> npcs;
    std::queue<std::pair<std::string, std::string>> battleQueue;
    std::vector<std::shared_ptr<Observer>> observers;
    std::shared_mutex mtx;
    std::condition_variable_any battleCV;
    bool game_over = false;


    auto logger = std::make_shared<ConsoleLogger>();
    observers.push_back(logger);

    generateNPCs(npcs, mtx);


    std::thread movementThread(movementThreadFunction, std::ref(npcs), std::ref(mtx), std::ref(battleQueue), std::ref(battleCV), std::ref(game_over));
    std::thread battleThread(battleThreadFunction, std::ref(npcs), std::ref(mtx), std::ref(battleQueue), std::ref(battleCV), std::ref(game_over), std::ref(observers));


    auto start_time = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start_time < std::chrono::seconds(GAME_DURATION)) {
        printMap(npcs, mtx);
        std::this_thread::sleep_for(std::chrono::seconds(1)); 
    }


    game_over = true;
    battleCV.notify_all();

    movementThread.join();
    battleThread.join();


    {
        std::lock_guard<std::mutex> coutLock(cout_mutex);
        std::cout << "\nSurviving NPCs:\n";
        std::shared_lock<std::shared_mutex> lock(mtx);
        for (const auto& npc : npcs) {
            std::cout << npc->getName() << " (" << npc->getType() << ") at (" << npc->getX() << ", " << npc->getY() << ")\n";
        }
    }

    return 0;
}
