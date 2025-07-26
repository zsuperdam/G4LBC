#include "LBCDetectorConstruction.hh"

LBCDetectorConstruction::LBCDetectorConstruction(){
}

LBCDetectorConstruction::~LBCDetectorConstruction(){
}

G4VPhysicalVolume *LBCDetectorConstruction::Construct(){
    G4bool checkOverlaps = true;

    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4double halfxWorld = 0.2 * m;
    G4double halfyWorld = 0.2 * m;
    G4double halfzWorld = 0.2 * m;

    G4Box *solidWorld = new G4Box("solidWorld", halfxWorld, halfyWorld, halfzWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, checkOverlaps);


    //#####//
    // LBC //
    //#####//

    G4Element *elLa = new G4Element("Lanthanum", "La", 57, 138.905*g/mole);
    G4Element *elBr = new G4Element("Bromine", "Br", 35, 79.904*g/mole);
    G4Element *elCl = new G4Element("Chlorine", "Cl", 17, 35.453*g/mole);

    G4double density = 4.90 * g/cm3;
    G4int nComponents = 3;

    G4Material *materialLBC = new G4Material("LBC", density, nComponents);
    materialLBC->AddElement(elLa, 0.373451);
    materialLBC->AddElement(elBr, 0.6122);
    materialLBC->AddElement(elCl, 0.014349);

    
    //#######//
    // Glass //
    //#######//

    G4Element *elSi = nist->FindOrBuildElement("Si");
    G4Element *elO = nist->FindOrBuildElement("O");

    // SiO2
    density = 2.65 * g/cm3;
    nComponents = 2;
    G4int nAtoms;
    G4Material *sio2 = new G4Material("SiO2", density, nComponents);
    sio2->AddElement(elSi,nAtoms=1);
    sio2->AddElement(elO, nAtoms=2);

    //###########//
    // Placement //
    //###########//

    // Glass
    G4double rmin = 0. * cm; // Inner radius
    G4double rmax = 1.5 * cm; // Outer radius
    G4double z = 0.27 * cm; // length
    G4double startPhi = 0. * deg; // Start angle
    G4double deltaPhi = 360. * deg; // Full angle

    G4Tubs *solidGlass = new G4Tubs("solidGlass", rmin, rmax, z/2, startPhi, deltaPhi);
    G4LogicalVolume *logicGlass = new G4LogicalVolume(solidGlass, sio2, "logicalGlass");
    G4RotationMatrix *rotation = new G4RotationMatrix();
    rotation->rotateY(90. * deg);
    G4VPhysicalVolume *physGlass = new G4PVPlacement(rotation, G4ThreeVector(-0.27/2*cm, 0., 0.), logicGlass, "physGlass", logicWorld, false, 0, checkOverlaps);

    G4VisAttributes *glassVisAtt = new G4VisAttributes(G4Color(0.8, 0.8, 0.8, 0.5));
    glassVisAtt->SetForceSolid(true);
    logicGlass->SetVisAttributes(glassVisAtt);

    // LBC
    rmin = 0. * cm; // Inner radius
    rmax = 2.5 / 2 * cm; // Outer radius
    z = 2.5 * cm; // length
    startPhi = 0. * deg; // Start angle
    deltaPhi = 360. * deg; // Full angle

    G4Tubs *solidDetector = new G4Tubs("solidDetector", rmin, rmax, z/2, startPhi, deltaPhi);
    logicDetector = new G4LogicalVolume(solidDetector, materialLBC, "logicalDetector");
    G4RotationMatrix *rotationLBC = new G4RotationMatrix();
    rotationLBC->rotateY(90. * deg);
    G4VPhysicalVolume *physLBC = new G4PVPlacement(rotationLBC, G4ThreeVector(-0.27*cm-1.25*cm, 0., 0.), logicDetector, "physLBC", logicWorld, false, 0, checkOverlaps);

    G4VisAttributes *lbcVisAtt = new G4VisAttributes(G4Color(1.0, 0.5, 0.0, 0.5));
    lbcVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(lbcVisAtt);
    // Source
    G4double sourceRadius = 1. * mm;

    G4Sphere *solidSource = new G4Sphere("solidSource", 0., sourceRadius, 0., 360. * deg, 0., 180. * deg);
    G4LogicalVolume *logicSource = new G4LogicalVolume(solidSource, worldMat, "logicalSource");
    G4VPhysicalVolume *physSource = new G4PVPlacement(0, G4ThreeVector(5. * cm, 0., 0.), logicSource, "physical_source", logicWorld, false, 0, checkOverlaps);
    
    G4VisAttributes *sourceVisAtt = new G4VisAttributes(G4Color(0.0, 1.0, 0.0, 0.5));
    sourceVisAtt->SetForceSolid(true);
    logicSource->SetVisAttributes(sourceVisAtt);

    return physWorld;
}

void LBCDetectorConstruction::ConstructSDandField(){
    LBCSensitiveDetector *sensDet = new LBCSensitiveDetector("SensitiveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}