#ifndef DRAGON_H
#define DRAGON_H

#include "NPC.h"
#include <string>

class Dragon : public NPC {
public:
    Dragon(const std::string& name, int x, int y);

    std::string getType() const override;       
    int getMovementDistance() const override;   
    int getKillingRange() const override;       
    bool fight(NPC& opponent) override;         
};

#endif
