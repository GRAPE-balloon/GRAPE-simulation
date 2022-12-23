//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
//  Gamma-RAy Polarimeter Experiment (GRAPE)
//  2023 Balloon Flight Campaign
//  Created: September 23, 2022 by Camden Ertley
//
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
/// \file RunAction.cc
/// \brief Implementation of the RunAction class

#include "RunAction.hh"
#include "EventAction.hh"
#include "Constants.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Timer.hh"
#include "G4UIcommand.hh"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  //****************************************************************************
  // Constructor
  //****************************************************************************
  RunAction::RunAction( EventAction* eventAct )
   : fEventAction( eventAct )
  { 
    // set printing event number per each event
    G4RunManager::GetRunManager()->SetPrintProgress(100);     

    // Create analysis manager
    // The choice of the output format is done via the specified
    // file extension.
    auto analysisManager = G4AnalysisManager::Instance();


    // Create directories
    //
    //analysisManager->SetHistoDirectoryName("histograms");
    //analysisManager->SetNtupleDirectoryName("ntuple");

    // Default Settings
    //
    analysisManager->SetVerboseLevel(1);
    analysisManager->SetDefaultFileType("root");
      // Note: If the filename extension is not provided, the default file 
      // type (root) will be used for all files specified without extension.
    analysisManager->SetNtupleMerging(true);
      // Note: merging ntuples is available only with Root output

    // Default output file
    //
    G4String fileName = "../data/Test_ntuple.root";
    // Other supported output types:
    // G4String fileName = "../data/Test_ntuple.csv";
    // G4String fileName = "../data/Test_ntuple.hdf5";
    // G4String fileName = "../data/Test_ntuple.xml";
    analysisManager->SetFileName(fileName);

    // Creating ntuple
    //
    analysisManager->CreateNtuple("data", "ScintTest Data");
    analysisManager->CreateNtupleIColumn("EventNumber");
    analysisManager->CreateNtupleDColumn("PrimaryEnergy");
    analysisManager->CreateNtupleIColumn("Hits");

    analysisManager->CreateNtupleIColumn("ID", fEventAction->GetID());
    analysisManager->CreateNtupleDColumn("Edep", fEventAction->GetEdep());
    analysisManager->CreateNtupleDColumn("GEB", fEventAction->GetGEB());
    analysisManager->CreateNtupleDColumn("Time", fEventAction->GetTime());

    analysisManager->FinishNtuple();

    // Create run timer
    if (isMaster) {
      fTimer = new G4Timer;
    }

  }

  //****************************************************************************
  // Destructor
  //****************************************************************************
  RunAction::~RunAction()
  {
    delete fTimer;
  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void RunAction::BeginOfRunAction(const G4Run* /*run*/)
  { 
    // start timer
    //
    if (isMaster) {
      fTimer->Start();
    }

    // inform the runManager to save random number seed
    // G4RunManager::GetRunManager()->SetRandomNumberStore(true);
    
    // Get analysis manager
    auto analysisManager = G4AnalysisManager::Instance();

    // Open an output file
    // The default file name is set in RunAction::RunAction(),
    // it can be overwritten in a macro
    analysisManager->OpenFile();

  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void RunAction::EndOfRunAction(const G4Run* /*run*/)
  {
    auto analysisManager = G4AnalysisManager::Instance();

    // save histograms & ntuple
    //
    analysisManager->Write();
    analysisManager->CloseFile();

    // stop timer and print stats
    //
    if (isMaster) {
      fTimer->Stop();
      G4cout << G4endl;
      // G4cout << "  Events: " << iEvents << G4endl;
      // G4cout << "  Hits: " << iHits << G4endl;
      G4cout << "### Complete ###" << G4endl;
      G4cout << "  Timer: " << fTimer->GetRealElapsed() << " s" << G4endl;
      G4cout << G4endl;
    }

  }

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
