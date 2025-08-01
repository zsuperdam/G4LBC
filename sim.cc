#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4NuclideTable.hh"
#include "G4UIExecutive.hh"

#include "LBCPhysicsList.hh"
#include "LBCDetectorConstruction.hh"
#include "LBCActionInitialization.hh"

int main(int argc, char** argv) {
    G4UIExecutive *ui = 0;

    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager = new G4MTRunManager;
    #else
        G4RunManager *runManager = new G4RunManager;
    #endif

    G4NuclideTable::GetInstance()->SetThresholdOfHalfLife(200.0 * year);

    // Physics list
    runManager->SetUserInitialization(new LBCPhysicsList());

    // Detector construction
    runManager->SetUserInitialization(new LBCDetectorConstruction());

    // Action initialization
    runManager->SetUserInitialization(new LBCActionInitialization());

    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if (ui) {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
    } else {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    return 0;
}