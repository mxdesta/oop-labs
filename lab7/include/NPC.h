#ifndef NPC_H
#define NPC_H

#include <string>
#include <cmath>

class NPC {
protected:
    std::string name;
    int x, y;
    bool isDead; // Новое поле для отслеживания, мертв NPC или нет

public:
    NPC(std::string name, int x, int y) : name(std::move(name)), x(x), y(y), isDead(false) {}
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    virtual int getMovementDistance() const = 0;
    virtual int getKillingRange() const = 0;
    virtual bool fight(NPC &opponent) = 0;

    const std::string &getName() const { return name; }
    int getX() const { return x; }
    int getY() const { return y; }

    void move(int dx, int dy) {
        x = std::max(0, std::min(x + dx, 100));
        y = std::max(0, std::min(y + dy, 100));
    }

    double distanceTo(const NPC &other) const {
        return std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    }

    // Новые методы
    bool isAlive() const { return !isDead; } // Проверка, жив ли NPC
    void markAsDead() { isDead = true; }    // Пометить как мертвого
};

#endif
