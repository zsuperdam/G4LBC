#ifndef LBCPHYSICSLIST_HH
#define LBCPHYSICSLIST_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4DecayPhysics.hh"
#include "G4NuclideTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4HadronicParameters.hh"

class LBCPhysicsList : public G4VModularPhysicsList{
    public:
        LBCPhysicsList();
        ~LBCPhysicsList();
};

#endif