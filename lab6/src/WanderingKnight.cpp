#include "../include/WanderingKnight.h"

bool WanderingKnight::fight(NPC &opponent) {
    return opponent.getType() == "Dragon"; 
}