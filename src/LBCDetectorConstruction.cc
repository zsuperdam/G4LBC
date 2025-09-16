#include "LBCDetectorConstruction.hh"

LBCDetectorConstruction::LBCDetectorConstruction(){
}

LBCDetectorConstruction::~LBCDetectorConstruction(){
}

G4VPhysicalVolume *LBCDetectorConstruction::Construct(){
    G4bool checkOverlaps = true;

    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *materialAluminum = nist->FindOrBuildMaterial("G4_Al");

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

    // Aluminum
    G4double rmin_Al = 0. * cm; // Inner radius
    G4double rmax_Al = 1.5 * cm; // Outer radius
    G4double z_Al = 0.8 * cm; // length
    G4double startPhi_Al = 0. * deg; // Start angle
    G4double deltaPhi_Al = 360. * deg; // Full angle

    G4Tubs *solidAluminum = new G4Tubs("solidAluminum", rmin_Al, rmax_Al, z_Al/2, startPhi_Al, deltaPhi_Al);
    G4LogicalVolume *logicAluminum = new G4LogicalVolume(solidAluminum, materialAluminum, "logicalAluminum");
    G4RotationMatrix *rotation = new G4RotationMatrix();
    rotation->rotateY(90. * deg);
    G4VPhysicalVolume *physAluminum = new G4PVPlacement(rotation, G4ThreeVector(-z_Al/2, 0., 0.), logicAluminum, "physAluminum", logicWorld, false, 0, checkOverlaps);

    // LBC
    G4double rmin_LBC = 0. * cm; // Inner radius
    G4double rmax_LBC = 2.5 / 2 * cm; // Outer radius
    G4double z_LBC = 2.5 * cm; // length
    G4double startPhi_LBC = 0. * deg; // Start angle
    G4double deltaPhi_LBC = 360. * deg; // Full angle

    G4Tubs *solidDetector = new G4Tubs("solidDetector", rmin_LBC, rmax_LBC, z_LBC/2, startPhi_LBC, deltaPhi_LBC);
    logicDetector = new G4LogicalVolume(solidDetector, materialLBC, "logicalDetector");
    G4RotationMatrix *rotationLBC = new G4RotationMatrix();
    rotationLBC->rotateY(90. * deg);
    G4VPhysicalVolume *physLBC = new G4PVPlacement(rotationLBC, G4ThreeVector(-z_Al-z_LBC/2, 0., 0.), logicDetector, "physLBC", logicWorld, false, 0, checkOverlaps);

    G4VisAttributes *lbcVisAtt = new G4VisAttributes(G4Color(1.0, 0.5, 0.0, 0.5));
    lbcVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(lbcVisAtt);

    // Glass
    G4double rmin_Glass = 0. * cm; // Inner radius
    G4double rmax_Glass = 1.5 * cm; // Outer radius
    G4double z_Glass = 0.27 * cm; // length
    G4double startPhi_Glass = 0. * deg; // Start angle
    G4double deltaPhi_Glass = 360. * deg; // Full angle

    G4Tubs *solidGlass = new G4Tubs("solidGlass", rmin_Glass, rmax_Glass, z_Glass/2, startPhi_Glass, deltaPhi_Glass);
    G4LogicalVolume *logicGlass = new G4LogicalVolume(solidGlass, sio2, "logicalGlass");
    G4VPhysicalVolume *physGlass = new G4PVPlacement(rotation, G4ThreeVector(-z_Al-z_LBC-z_Glass/2, 0., 0.), logicGlass, "physGlass", logicWorld, false, 0, checkOverlaps);

    G4VisAttributes *glassVisAtt = new G4VisAttributes(G4Color(0.8, 0.8, 0.8, 0.5));
    glassVisAtt->SetForceSolid(true);
    logicGlass->SetVisAttributes(glassVisAtt);


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