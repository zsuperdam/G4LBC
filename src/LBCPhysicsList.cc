#include "LBCPhysicsList.hh"

LBCPhysicsList::LBCPhysicsList(){
    // EM physics
    RegisterPhysics(new G4EmStandardPhysics());

    // Radioactive decay physics
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    
    // Decay physics
    RegisterPhysics(new G4DecayPhysics());
}

LBCPhysicsList::~LBCPhysicsList(){
}
