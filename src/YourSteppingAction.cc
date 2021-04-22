#include "YourSteppingAction.hh"

#include "YourDetectorConstruction.hh"
#include "YourEventAction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"

YourSteppingAction::YourSteppingAction(YourDetectorConstruction* det, YourEventAction* evtAction) 
:   G4UserSteppingAction(), 
    fYourDetector(det),
    fYourEventAction(evtAction) { }


YourSteppingAction::~YourSteppingAction() {}


void YourSteppingAction::UserSteppingAction(const G4Step* theStep) {
  
  if (theStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume() 
      != fYourDetector->GetTargetPhysicalVolume() )  return; 

  // energy deposit
  auto eDep   = theStep->GetTotalEnergyDeposit();
  
  // track length (only for charged particles)
  auto trackL = 0.;   
  if ( theStep->GetTrack()->GetDefinition()->GetPDGCharge() != 0. ) {
    trackL = theStep->GetStepLength(); 
  }
  
  // place the information inside the event action
  fYourEventAction->Add( eDep, trackL );
}
