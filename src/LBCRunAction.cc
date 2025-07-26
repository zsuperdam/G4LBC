#include "LBCRunAction.hh"

LBCRunAction::LBCRunAction(){
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->CreateH1("Edep", "Energy deposit", 100, 0., 2. * MeV); // number of bins, min, max
}

LBCRunAction::~LBCRunAction(){
}

void LBCRunAction::BeginOfRunAction(const G4Run *run){
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    analysisManager->OpenFile("LBC_" + strRunID.str() + ".root");
}

void LBCRunAction::EndOfRunAction(const G4Run *run){
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
    G4int runID = run->GetRunID();
    G4cout << "Run " << runID << " ended" << G4endl;
}