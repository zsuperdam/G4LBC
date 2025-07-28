#include "LBCPhysicsList.hh"

LBCPhysicsList::LBCPhysicsList(){

    G4HadronicParameters::Instance()->SetTimeThresholdForRadioactiveDecay( 1.0e+60*CLHEP::year );
    G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(1.0 * ns);
    
    // EM physics
    RegisterPhysics(new G4EmStandardPhysics());

    // Radioactive decay physics
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    
    // Decay physics
    RegisterPhysics(new G4DecayPhysics());
}

LBCPhysicsList::~LBCPhysicsList(){
}
