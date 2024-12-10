#include "../include/Elf.h"

bool Elf::fight(NPC &opponent) {

    return this->getKillingRange() > opponent.getKillingRange();
}
