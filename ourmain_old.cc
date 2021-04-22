#include <iostream>
#include "G4Types.hh"
#include "globals.hh"

// HERE 
#include "G4NistManager.hh"
#include "G4Element.hh"
#include "YourDeterctorConstruction.hh"
#
using namespace CLHEP;
// CLHEP: :
int main() {
  
  // the code must go here
  // Tarea 1.1
  // 1. elemento a elegir 
	G4Element* elC = new G4Element("Carbon", "C", 6., 12.01*g/mole); 
	
  // 2. Definir uranio enriquecido como 90% of U235 and 10% of U238: 
	// 2.1 create the isotopes: iz = number of protons and n=number of nucleons 
	G4Isotope* U5 = new G4Isotope("U235", 92, 235); 
	G4Isotope* U8 = new G4Isotope("U238", 92, 238);
	// 2.2 create the element and build up by adding the isotopes with their abundance:  
    G4Element* elU = new G4Element("Enriched Uranium", "U", 2); 
	elU->AddIsotope(U5,90.*perCent); 
	elU->AddIsotope(U8,10.*perCent);
	
  // 3. Crear materiales con G4Material:
	//G4Material* matU = new G4Material("Uranium", 92., 238.03*g/mole, 18.950*g/cm3); 
	G4Element* elH = new G4Element("Hydrogen", "H", 1.00, 1.01*g/mole); 
	G4Element* elO = new G4Element("Oxygen", "O", 8.00, 16*g/mole);  
	G4Element* elSi = new G4Element("Silicon", "Si", 14.00, 28.086*g/mole);
	// 3.1 Definir agua 
	G4Material* matH2O = new G4Material("water", 1.0*g/cm3, 2);  
	// 3.1.1 add the elements to the material with their composition number:  
	matH2O->AddElement(elH,2); 
	matH2O->AddElement(elO,1); 
	
	// 3.1 Definir SiO2
	G4Material* matSiO2 = new G4Material("SiO2", 2.65*g/cm3, 2);  
	// 3.1.1 add the elements to the material with their composition number:  
	matSiO2->AddElement(elSi,1); 
	matSiO2->AddElement(elO,2); 
	
	//3.2 Creer material "aire" como una mezcla 70-30% de los elementos N y O 
	G4Element* elN = new G4Element("Nytrogen", "N", 7.00, 14.0067*g/mole); 
	//G4Element* elO = new G4Element("Oxygen", "O", 8.00, 16*g/mole); lo quito porque ya aparece
	// en la línea 30 
	//3.2.1 create the air material (name, density, number of components):  
	G4Material* matAir = new G4Material("Air", 1.290*mg/cm3, 2);  
	// 3.2.2 add the elements to the material with their composition number:  
	matAir->AddElement(elN,0.7); 
	matAir->AddElement(elO,0.3); 
	// 3.3 Create aerogel material as 62.5 % silicon dioxide (SiO2), 
	// 37.4% water (H2O) and 0.1 % carbon element. We will assume that
	// the materials (matSiO2 and matH2O) as well as the carbon element (elC) have already been created 
	// create aerogel material: 
	G4Material* matAerog = new G4Material("Aerogel", 0.2*g/cm3, 3);  
	// 3.3.1 add the elements to the material with their fractional mass:  
	matAerog->AddMaterial(matSiO2,62.5*perCent); 
	matAerog->AddMaterial(matH2O, 37.4*perCent); 
	matAerog->AddElement(elC, 0.1*perCent); 
	
  ////4. Usar la base de datos NIST:
	//G4NistManager* nistMGR = G4NistManager::Instance(); 
	////4.1 get the pre-defined liquid argon (“G4_lAr”) from the NIST DB 
	//G4Material* matLAr = nistMGR->FindOrBuildMaterial("G4_lAr") 
	//4.2 get the pre-defined concrete (“G4_CONCRETE”) from the NIST DB 
	//G4Material* matConcr = nistMGR->FindOrBuildMaterial("G4_CONCRETE"); 
	
	
	
  // this is some example to play with
  // try here all the commands that we saw in class
  
  const G4String elName = "Al";
  G4NistManager::Instance()->PrintElement(elName);
  
  const G4String matCName = "simple";
  G4NistManager::Instance()->ListMaterials(matCName);
  
  const G4String matName = "G4_Si_askjgd asdgh";
  const G4Material* theSi = G4NistManager::Instance()->FindOrBuildMaterial(matName);
  if (theSi != nullptr) {
    G4cout << theSi << G4endl;
  } else {
    G4cout << " nothing: " << matName << G4endl;
  }
  
  return 0;
}
