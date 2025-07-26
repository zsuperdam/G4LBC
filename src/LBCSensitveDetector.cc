#include "LBCSensitiveDetector.hh"

LBCSensitiveDetector::LBCSensitiveDetector (G4String name): G4VSensitiveDetector(name){
    fTotalEnergyDeposited = 0.;
}

LBCSensitiveDetector::~LBCSensitiveDetector() {
}

void LBCSensitiveDetector::Initialize(G4HCofThisEvent *) {
    fTotalEnergyDeposited = 0.;
}

void LBCSensitiveDetector::EndOfEvent(G4HCofThisEvent *HCE) {
        // G4cout << "Deposited energy: " << fTotalEnergyDeposited << G4endl;
        G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
        if (fTotalEnergyDeposited > 0){
            analysisManager->FillH1(0, fTotalEnergyDeposited);
        }     
}

G4bool LBCSensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *) {
    G4double fEnergyDeposited = aStep->GetTotalEnergyDeposit();
    if (fEnergyDeposited > 0){
        fTotalEnergyDeposited += fEnergyDeposited;
    }
    return true;
}