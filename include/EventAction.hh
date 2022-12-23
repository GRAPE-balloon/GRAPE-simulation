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
/// \file EventAction.hh
/// \brief Definition of the EventAction class

#ifndef EventAction_h
#define EventAction_h 1

#include "globals.hh"
#include "G4UserEventAction.hh"

#include "ScintHit.hh"
#include "Constants.hh"

#include <array>
#include <vector>

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  //****************************************************************************
  /// Event action class
  ///
  //****************************************************************************
  class EventAction : public G4UserEventAction
  {
    public:
      EventAction();
      ~EventAction() override;

      // methods from base class
      void  BeginOfEventAction(const G4Event* ) override;
      void    EndOfEventAction(const G4Event* ) override;

      // methods
      std::vector<G4int>& GetID() { return fID; }
      std::vector<G4double>& GetEdep() { return fEdep; }
      std::vector<G4double>& GetGEB() { return fGEB; }
      std::vector<G4double>& GetTime() { return fTime; }

    private:      
      // methods
      G4double BroadenEnergy(const G4String& type, G4double energy);

      // data members
      G4int  fScintHCID = -1;

      std::vector<G4int> fID;
      std::vector<G4double> fEdep;
      std::vector<G4double> fGEB;
      std::vector<G4double> fTime;
      // std::vector<G4double> fEdep = std::vector<G4double>(kDim);
      // std::vector<G4double> fGEB = std::vector<G4double>(kDim);
      // std::vector<G4double> fTime = std::vector<G4double>(kDim);
  };
                     
}
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

    
