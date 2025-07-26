#ifndef LBCSENSITIVEDETECTOR_HH
#define LBCSENSITIVEDETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"

class LBCSensitiveDetector : public G4VSensitiveDetector {
    public:
        LBCSensitiveDetector(G4String);
        ~LBCSensitiveDetector();

    private:
        G4double fTotalEnergyDeposited;

        virtual void Initialize(G4HCofThisEvent *) override;
        virtual void EndOfEvent(G4HCofThisEvent *) override;

        virtual G4bool ProcessHits(G4Step *, G4TouchableHistory *);
};

#endif