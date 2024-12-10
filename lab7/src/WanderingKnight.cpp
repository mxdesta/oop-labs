#include "../include/WanderingKnight.h"

bool WanderingKnight::fight(NPC &opponent) {

    return this->getKillingRange() > opponent.getKillingRange();
}
