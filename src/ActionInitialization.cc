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
/// \file ActionInitialization.cc
/// \brief Implementation of the ActionInitialization class

#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"

#include "G4GeneralParticleSource.hh"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{


  //****************************************************************************
  // Constructor
  //****************************************************************************
  ActionInitialization::ActionInitialization()
  {}


  //****************************************************************************
  // Destructor
  //****************************************************************************
  ActionInitialization::~ActionInitialization()
  {}


  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void ActionInitialization::BuildForMaster() const
  {
    auto eventAct = new EventAction();
    auto runAct = new RunAction( eventAct );
    SetUserAction( runAct );
  }


  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void ActionInitialization::Build() const
  {
    auto priGenAct = new PrimaryGeneratorAction();
    SetUserAction( priGenAct );

    auto eventAct = new EventAction();
    SetUserAction( eventAct );

    auto runAct = new RunAction( eventAct );
    SetUserAction( runAct );

  }  

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
