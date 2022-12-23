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
/// \file EventAction.cc
/// \brief Implementation of the EventAction class

#include "EventAction.hh"
#include "ScintSD.hh"
#include "ScintHit.hh"
#include "Constants.hh"
#include "PrimaryGeneratorAction.hh"

#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace {
  //****************************************************************************
  // Utility function which finds a hit collection with the given Id
  // and print warnings if not found
  //****************************************************************************
  G4VHitsCollection* GetHitCollection(const G4Event* event, G4int hcID ) 
  {
    auto hce = event->GetHCofThisEvent();
    if (!hce) {
        G4ExceptionDescription msg;
        msg << "No hits collection of this event found." << G4endl;
        G4Exception("EventAction::GetHitsCollection()",
                    "Code001", JustWarning, msg);
        return nullptr;
    }
    
    auto hc = hce->GetHC(hcID);
    if ( ! hc) {
      G4ExceptionDescription msg;
      msg << "Cannot access hitsCollection ID " << hcID; 
      G4Exception("EventAction::GetHitsCollection()",
        "Code0001", JustWarning, msg);
    }         

    return hc;
  }    
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  //****************************************************************************
  // Constructor
  //****************************************************************************
  EventAction::EventAction()
  {}

  //****************************************************************************
  // Destructor
  //****************************************************************************
  EventAction::~EventAction()
  {}

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void EventAction::BeginOfEventAction(const G4Event* /*event*/)
  {}

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void EventAction::EndOfEventAction(const G4Event* event)
  {  
    
    auto sdManager = G4SDManager::GetSDMpointer();

    // Get hits collections IDs (only once)
    if ( fScintHCID == -1 ) {
      fScintHCID = sdManager->GetCollectionID("grapeDet/ScintCollection");
    }

    // Get hits collection
    auto scintHC = GetHitCollection( event, fScintHCID );
    if ( ! scintHC ) return;

    // get number of hits
    auto nHits = scintHC->GetSize();

    // Check if there were any hits in instrument
    if ( nHits > 0 ){
      // G4cout << "Scint hits: " << nHits << G4endl;
 
      // get analysis manager
      auto analysisManager = G4AnalysisManager::Instance();

      // Fill Ntuple
      auto col = 0; // ntuple column number
      analysisManager->FillNtupleIColumn(col++, event->GetEventID());

      auto primaryE = event->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy()/keV;
      analysisManager->FillNtupleDColumn(col++, primaryE);

      // Add number of hits
      analysisManager->FillNtupleIColumn(col++, nHits);

      // Data for each hit element
      // auto fID = -1;
      // fEdep = std::vector<G4double>(kDim, NAN);
      // fGEB = std::vector<G4double>(kDim, NAN);
      // fTime = std::vector<G4double>(kDim, NAN);
      
      fID = std::vector<G4int>(nHits, NAN);
      fEdep = std::vector<G4double>(nHits, NAN);
      fGEB = std::vector<G4double>(nHits, NAN);
      fTime = std::vector<G4double>(nHits, NAN);
      for (unsigned long i=0; i<nHits; i++ ) {
          auto hit = static_cast<ScintHit*>(scintHC->GetHit(i));

          // fID = hit->GetID();
          // fEdep[fID] = hit->GetEdep()/keV;
          // fGEB[fID] = BroadenEnergy( hit->GetType(), hit->GetEdep()/keV );
          // fTime[fID] = hit->GetTime()/ns;

          fID[i] = hit->GetID();
          fEdep[i] = hit->GetEdep()/keV;
          fGEB[i] = BroadenEnergy( hit->GetType(), hit->GetEdep()/keV );
          fTime[i] = hit->GetTime()/ns;
      }

      // Finish event
      analysisManager->AddNtupleRow();  

    }

  }  

  //****************************************************************************
  // Method
  //****************************************************************************
  G4double EventAction::BroadenEnergy(const G4String& type, G4double energy)
  {
    // Expects energy in keV
    //     Updated energy broadening (2016-09-09)
    if ( type == "Plastic" ) {
      // auto sigma = -8.3195 + ( 3.1992 * sqrt( energy ) ); // old GEANT4 sims
      // auto sigma = sqrt( 0.5692 + ( 2.837 * energy ) ); // fit to GRAPE calibration data
      // auto sigma = ( 0.478 / 2.35 ) * sqrt( 60. * energy ); // Peter's old numbers ( 47.8% at 60 keV )
      auto sigma = -1.035 + ( 1.66 * sqrt( energy ) ); // fit to GRAPE calibration data
      energy = G4RandGauss::shoot( energy, sigma) ;
    }

    else if ( type == "CsI" ) { 
      // auto sigma = 1.89 + 1.20 * sqrt( energy ); // old GEANT4 sims
      // auto sigma = sqrt( -83.43 + ( 4.88 * energy ) ); // fit to calibration data
      // auto sigma = ( 0.14 / 2.35 ) * sqrt( 662. * energy ); // 14% at 662 keV
      // auto sigma = 0.1146 + ( 1.662 * sqrt( energy ) ); // fit to GRAPE calibration data
      auto sigma = 1.3846 + ( 1.2179 * sqrt( energy ) ); // fit to GRAPE calibration data 5/10/22
      // auto sigma = ( 0.116 / 2.35 ) * sqrt( 662. * energy ); // 11.6% at 662 keV 5/10/22
      energy = G4RandGauss::shoot( energy, sigma );
    }

    else if ( type == "Stilbene" ) { 
      auto sigma = 1.42 + 0.90 * sqrt( energy ) ; // Needs updated
      energy = G4RandGauss::shoot( energy, sigma );
    }

    else if ( type == "p-Terphenyl" ) { 
      auto sigma = 1.42 + 0.90 * sqrt( energy ) ; // Needs updated
      energy = G4RandGauss::shoot( energy, sigma );
    }
    
    else if ( type == "GAGG" ) { 
      auto sigma = 1.42 + 0.90 * sqrt( energy ) ;
      energy = G4RandGauss::shoot( energy, sigma );
    }

    return energy;
  }
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
