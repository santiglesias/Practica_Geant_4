#ifndef YOURSTEPPINGACTION_HH
#define YOURSTEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

// forward declarations
class YourDetectorConstruction;
class YourEventAction;
class G4VPhysicalVolume;

class YourSteppingAction : public G4UserSteppingAction {

  // Method declaration:
  public:
    YourSteppingAction(YourDetectorConstruction* det, YourEventAction* evtAction);
    virtual ~YourSteppingAction();

    // Virtual method called by the kernel after each step
    virtual void UserSteppingAction(const G4Step* step);

    

  // Data member declarations:
  private:

  	YourDetectorConstruction*    fYourDetector;

  	YourEventAction*             fYourEventAction;
};

#endif

