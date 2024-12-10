#include "../include/WanderingKnight.h"

bool WanderingKnight::fight(NPC &opponent) {
    // Реализация метода fight
    return this->getKillingRange() > opponent.getKillingRange();
}
