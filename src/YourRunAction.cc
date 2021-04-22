
#include "YourRunAction.hh"

#include "YourDetectorConstruction.hh"
#include "YourPrimaryGeneratorAction.hh"

#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "YourAnalysis.hh"

YourRunAction::YourRunAction(YourPrimaryGeneratorAction* prim) 
  :   G4UserRunAction(),
      fYourPrimary(prim) 
{

 
  G4RunManager::GetRunManager()->SetPrintProgress(1);
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  // Create directories
  analysisManager->SetHistoDirectoryName("histograms");
  analysisManager->SetNtupleDirectoryName("ntuple");
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetNtupleMerging(true);
  // Note: merging ntuples is available only with Root output

  // Creating histograms
  analysisManager->CreateH1("Edep","Edep in target", 100, 0., 20*keV);
  analysisManager->CreateH1("trackL","trackL in target", 100, 0., 20*cm);

  // Creating ntuple
  //
  analysisManager->CreateNtuple("Test", "Edep and TrackL");
  analysisManager->CreateNtupleDColumn("Edep");
  analysisManager->CreateNtupleDColumn("trackL");
  analysisManager->FinishNtuple();
}

YourRunAction::~YourRunAction() { 
  /* histo manager must be deleted here then*/ 
  delete G4AnalysisManager::Instance();
}


void YourRunAction::BeginOfRunAction(const G4Run* /*run*/) {
  // Make sure that the Gun position is correct: the user can change the target
  // thickness between construction of objects and start of the run.  
  // note: primary generator is set in the CTR only for the Worker threads in the 
  //       ActionInitialization (left null for Master in the BuildForMaster())
  if ( fYourPrimary ) { 
    fYourPrimary->UpdatePosition();
  }

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();

  // Open an output file
  //
  G4String fileName = "YourApplication";
  analysisManager->OpenFile(fileName);
}


void YourRunAction::EndOfRunAction(const G4Run*) {
  // print histogram statistics
  //
  auto analysisManager = G4AnalysisManager::Instance();
  
  if ( analysisManager->GetH1(1) ) {
    G4cout << G4endl << " ----> print histograms statistic ";
    if(isMaster) {
      G4cout << "for the entire run " << G4endl << G4endl;
    }
    else {
      G4cout << "for the local thread " << G4endl << G4endl;
    }

    G4cout << " Edep : mean = "
	   << G4BestUnit(analysisManager->GetH1(0)->mean(), "Energy")
	   << " rms = "
	   << G4BestUnit(analysisManager->GetH1(0)->rms(),  "Energy") << G4endl;

    G4cout << " TrackL : mean = "
	   << G4BestUnit(analysisManager->GetH1(1)->mean(), "Length")
	   << " rms = "
	   << G4BestUnit(analysisManager->GetH1(1)->rms(),  "Length") << G4endl;

  }

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile(); 
}
