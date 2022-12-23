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
/// \file PhysicsList.hh
/// \brief Definition of the PhysicsList class

#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "globals.hh"
#include "G4VModularPhysicsList.hh"

class G4VPhysicsConstructor;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  class PhysicsListMessenger;

  //****************************************************************************
  /// Physics list class
  ///
  //****************************************************************************
  class PhysicsList: public G4VModularPhysicsList
  {
    public:

      PhysicsList();
      ~PhysicsList() override;

      // methods from base class
      void ConstructParticle() override;
      void ConstructProcess() override;    
      void SetCuts() override;

      // set methods
      void SetPhysicsList(const G4String& name);
      void List();

    private:
      // methods
      void PhysicsList0();
      void PhysicsList1();
      void PhysicsList2();

      // data members
      G4VPhysicsConstructor*  fEmPhysicsList = nullptr;
      G4VPhysicsConstructor*  fParticleList = nullptr;
      std::vector<G4VPhysicsConstructor*>  fHadronPhys;

      PhysicsListMessenger* fPhyMessenger = nullptr;
  
  };

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

