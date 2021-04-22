
#include "YourDetectorConstruction.hh"

#include "YourDetectorMessenger.hh"

// for geometry definitions 
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

// for material definitions
#include "G4Material.hh"
#include "G4NistManager.hh"

// for having units and constants
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"


// CTR
YourDetectorConstruction::YourDetectorConstruction()
:   G4VUserDetectorConstruction(), 
    fTargetMaterial(nullptr), 
    fTargetPhysicalVolume(nullptr) {
    // set default target material to be Silicon
    SetTargetMaterial("G4_Si");
    // set default thickness
    fTargetThickness = 1.0*CLHEP::cm; 
    fGunXPosition    = 0.0; // will be set properly automaticaly 
    // create detector messenger object (for your own detector UI commands)
    fDetMessenger    = new YourDetectorMessenger(this); 
}

// DTR
YourDetectorConstruction::~YourDetectorConstruction() {
    delete fDetMessenger;
}


void YourDetectorConstruction::SetTargetMaterial(const G4String& matName) {
    // try to find the material in the NIST DB
    fTargetMaterial = G4NistManager::Instance()->FindOrBuildMaterial(matName);
    if (!fTargetMaterial) {
      G4cerr<< "\n **** ERROR in YourDetectorConstruction::SetTargetMaterial() \n"
            << "        Material with the given name of < " << matName << " >  \n"
            << "        was not found in the G4 NIST material DB               \n"
            << G4endl;
      exit(-1);      
    }
}


G4VPhysicalVolume* YourDetectorConstruction::Construct() {
	
    // World
    G4double zet      = 1.0;
    G4double amass    = 1.01*CLHEP::g/CLHEP::mole;
    G4double density  = CLHEP::universe_mean_density;
    G4double pressure = 3.e-18*CLHEP::pascal;
    G4double tempture = 2.73*CLHEP::kelvin;
    G4Material* materialWorld  = new G4Material("Galactic", zet, amass, density,
                                               kStateGas, tempture, pressure);
    // target
    G4Material* materialTarget = fTargetMaterial;
    //
    //  geometry
    // target and world
    G4double targetXSize  = fTargetThickness;
    G4double targetYZSize = 1.25*targetXSize;
    G4double worldXSize   = 1.1*targetXSize;
    G4double worldYZSize  = 1.1*targetYZSize;
    fGunXPosition         = -0.25*( worldXSize + targetXSize );
    
    // world
    G4Box*              worldSolid   = new G4Box("solid-World",  // name
    	                                       0.5*worldXSize,   // half x-size
    	                                       0.5*worldYZSize,  // half y-size 
    	                                       0.5*worldYZSize); // half z-size
    G4LogicalVolume*    worldLogical = new G4LogicalVolume(worldSolid,     // solid
                                                           materialWorld,  // material
                                                           "logic-World"); // name
    G4VPhysicalVolume*  worldPhyscal = new G4PVPlacement(nullptr,                 // (no) rotation
                                                         G4ThreeVector(0.,0.,0.), // translation
                                                         worldLogical,            // its logical volume
                                                         "World",                 // its name
                                                         nullptr,                 // its mother volume
                                                         false,                   // not used
                                                         0);                      // cpy number
    // target
    G4Box*              targetSolid   = new G4Box("solid-Target",    // name
    	                                          0.5*targetXSize,   // half x-size
    	                                          0.5*targetYZSize,  // half y-size 
    	                                          0.5*targetYZSize); // half z-size
    G4LogicalVolume*    targetLogical = new G4LogicalVolume(targetSolid,    // solid
                                                           materialTarget,  // material
                                                           "logic-Target"); // name
    G4VPhysicalVolume*  targetPhyscal = new G4PVPlacement(nullptr,                 // (no) rotation
                                                          G4ThreeVector(0.,0.,0.), // translation
                                                          targetLogical,           // its logical volume
                                                          "Target",                // its name
                                                          worldLogical,            // its mother volume
                                                          false,                   // not used
                                                          0);                      // cpy number
    fTargetPhysicalVolume = targetPhyscal;

    return worldPhyscal;
}



