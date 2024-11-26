#include "include/NPCFactory.h"
#include "include/BattleVisitor.h"
#include "include/ConsoleLogger.h"
#include "include/FileLogger.h"
#include <iostream>
#include <string>

void printNPCList(const std::vector<std::unique_ptr<NPC>> &npcs) {
    std::cout << "\nСписок NPC:\n";
    for (const auto &npc : npcs) {
        std::cout << npc->getType() << " " << npc->getName() 
                  << " (" << npc->getX() << ", " << npc->getY() << ")\n";
    }
}

int main() {
    std::vector<std::unique_ptr<NPC>> npcs;

    std::cout << "Добро пожаловать в редактор подземелья!\n";
    std::cout << "Вы можете добавлять персонажей: WanderingKnight, Elf, Dragon.\n";
    std::cout << "Для завершения ввода введите 'exit'.\n";

    while (true) {
        std::string type, name;
        int x, y;

        std::cout << "\nВведите тип персонажа (WanderingKnight, Elf, Dragon) или 'exit' для завершения: ";
        std::cin >> type;

        if (type == "exit") {
            break;
        }

        std::cout << "Введите имя персонажа: ";
        std::cin >> name;

        std::cout << "Введите координаты (x y) [0 <= x, y <= 500]: ";
        std::cin >> x >> y;

        if (x < 0 || x > 500 || y < 0 || y > 500) {
            std::cerr << "Координаты должны быть в пределах 0 <= x, y <= 500. Попробуйте снова.\n";
            continue;
        }

        try {
            npcs.push_back(NPCFactory::createNPC(type, name, x, y));
            std::cout << type << " " << name << " успешно добавлен.\n";
        } catch (const std::invalid_argument &e) {
            std::cerr << "Ошибка: " << e.what() << "\n";
        }
    }


    auto consoleLogger = std::make_shared<ConsoleLogger>();
    auto fileLogger = std::make_shared<FileLogger>("log.txt");

    BattleVisitor battle;
    battle.addObserver(consoleLogger);
    battle.addObserver(fileLogger);
    printNPCList(npcs);


    std::cout << "\nЗапуск боевого режима...\n";
    battle.conductBattle(npcs, 100.0);
    printNPCList(npcs);

    return 0;
}
