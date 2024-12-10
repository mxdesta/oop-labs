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
constexpr int GAME_DURATION = 30; // seconds

std::mutex cout_mutex;

// Функция для печати карты
void printMap(const std::vector<std::unique_ptr<NPC>>& npcs, std::shared_mutex& mtx) {
    const int mapWidth = MAP_WIDTH;
    const int mapHeight = MAP_HEIGHT;

    // Создаём пустую карту
    std::vector<std::string> map(mapHeight, std::string(mapWidth, ' '));

    // Синхронизируем доступ к NPC
    std::shared_lock<std::shared_mutex> lock(mtx);

    // Добавляем NPC на карту
    for (const auto& npc : npcs) {
        int x = npc->getX();
        int y = npc->getY();

        // Игнорируем NPC за пределами карты
        if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight) {
            continue;
        }

        // Определяем символ для NPC
        char symbol = 'N';
        if (npc->getType() == "WanderingKnight") symbol = 'W';
        else if (npc->getType() == "Elf") symbol = 'E';
        else if (npc->getType() == "Dragon") symbol = 'D';

        // Размещаем символ на карте
        map[y][x] = symbol;
    }

    // Печатаем карту с рамкой
    std::lock_guard<std::mutex> coutLock(cout_mutex);
    std::cout << "+" << std::string(mapWidth, '-') << "+\n";
    for (const auto& row : map) {
        std::cout << "|" << row << "|\n";
    }
    std::cout << "+" << std::string(mapWidth, '-') << "+\n";
}

// Функция генерации NPC
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

    // Add a console logger
    auto logger = std::make_shared<ConsoleLogger>();
    observers.push_back(logger);

    generateNPCs(npcs, mtx);

    // Threads
    std::thread movementThread(movementThreadFunction, std::ref(npcs), std::ref(mtx), std::ref(battleQueue), std::ref(battleCV), std::ref(game_over));
    std::thread battleThread(battleThreadFunction, std::ref(npcs), std::ref(mtx), std::ref(battleQueue), std::ref(battleCV), std::ref(game_over), std::ref(observers));

    // Main game loop
    auto start_time = std::chrono::steady_clock::now();
    while (std::chrono::steady_clock::now() - start_time < std::chrono::seconds(GAME_DURATION)) {
        printMap(npcs, mtx); // Печать только карты
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Обновляем карту каждую секунду
    }

    // End the game
    game_over = true;
    battleCV.notify_all();

    // Join threads
    movementThread.join();
    battleThread.join();

    // Print remaining NPCs
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
