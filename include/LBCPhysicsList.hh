#ifndef LBCPHYSICSLIST_HH
#define LBCPHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"

class LBCPhysicsList : public G4VModularPhysicsList{
    public:
        LBCPhysicsList();
        ~LBCPhysicsList();
};

#endif