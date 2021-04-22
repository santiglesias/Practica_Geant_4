#ifndef YOURRUNACTION_HH
#define YOURRUNACTION_HH

#include "G4UserRunAction.hh"

#include "G4String.hh"

// forward declarations
class YourPrimaryGeneratorAction;
class G4Run;


class YourRunAction : public G4UserRunAction {

  // Method declaration:
  public:
    
    YourRunAction(YourPrimaryGeneratorAction* prim = nullptr);
    virtual ~YourRunAction();

    // Virtial method that is called by the RunManager before the first event starts
    virtual void   BeginOfRunAction(const G4Run*);

    // Virtual method that is called by the RunManager after the last event finished
    virtual void   EndOfRunAction(const G4Run*);

  // Data member declarations:
  private:

  	YourPrimaryGeneratorAction*  fYourPrimary;     
};

#endif
