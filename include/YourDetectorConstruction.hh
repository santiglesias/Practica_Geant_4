
#ifndef YOURDETECTORCONSTRUCTION_HH
#define YOURDETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
class YourDetectorMessenger;
class G4Material;
class G4String;
class G4LogicalVolume;

class YourDetectorConstruction : public G4VUserDetectorConstruction {
public: 
   YourDetectorConstruction();
   virtual ~YourDetectorConstruction();
  
   virtual G4VPhysicalVolume* Construct();
  
   void SetTargetThickness(const G4double thick) {fTargetThickness = thick; }
   G4double GetTargetThickness() const { return fTargetThickness ;}
   
   void SetTargetMaterial(const G4String& matName);
   const G4Material* GetTargetMaterial() const { return fTargetMaterial ; }
   
   G4double GetGunXPosition() {return fGunXPosition; }
   
   const G4VPhysicalVolume* GetTargetPhysicalVolume() const {
	   return fTargetPhysicalVolume;
   }
  
private:
  YourDetectorMessenger* fDetMessenger;
  
  G4Material* fTargetMaterial;  
  
  G4VPhysicalVolume* fTargetPhysicalVolume; 
  
  G4double    fTargetThickness;
  
  G4double fGunXPosition;
  
};

#endif
