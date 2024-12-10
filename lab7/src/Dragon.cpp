#include "../include/Dragon.h"
#include <random>
#include <iostream>

Dragon::Dragon(const std::string& name, int x, int y)
    : NPC(name, x, y) {}

std::string Dragon::getType() const {
    return "Dragon";
}

int Dragon::getMovementDistance() const {
    return 3; 
}

int Dragon::getKillingRange() const {
    return 5;
}

bool Dragon::fight(NPC& opponent) {
    if (!opponent.isAlive()) return false;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dice(1, 6);

    int attack = dice(gen);
    int defense = dice(gen);

    std::cout << "Dragon " << getName() << " attacks " << opponent.getName()
              << " with attack roll: " << attack << ", defense roll: " << defense << "\n";

    if (attack > defense) {
        std::cout << opponent.getName() << " has been defeated by " << getName() << "\n";
        opponent.markAsDead();
        return true;
    }
    return false;
}
