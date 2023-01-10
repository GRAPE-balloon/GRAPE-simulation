//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
//  Gamma-RAy Polarimeter Experiment (GRAPE)
//  August 2023 Balloon Flight Campaign
//  (V1) Created: Mar 2, 2022 by Camden Ertley
//  (V2) Created: September 23, 2022 by Camden Ertley
//  (V3) same as V2
//
//
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//
/// \file PhysicsList.cc
/// \brief Implementation of the PhysicsList class

#include "PhysicsList.hh"
#include "PhysicsListMessenger.hh"

#include "G4SystemOfUnits.hh"




//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  //****************************************************************************
  // Constructor
  //****************************************************************************
  PhysicsList::PhysicsList()
  {
    fPhyMessenger = new PhysicsListMessenger(this);

    verboseLevel = 1;
    SetVerboseLevel(verboseLevel);

    // default
    PhysicsList0();
  }

  //****************************************************************************
  // Destructor
  //****************************************************************************
  PhysicsList::~PhysicsList()
  {
    delete fPhyMessenger;

    delete fParticleList;
    delete fEmPhysicsList;  
    for(size_t i=0; i<fHadronPhys.size(); i++) {
      delete fHadronPhys[i];
    }    
  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void PhysicsList::ConstructParticle()
  {
    fParticleList->ConstructParticle();
  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void PhysicsList::ConstructProcess()
  {
    AddTransportation();
    fEmPhysicsList->ConstructProcess();
    fParticleList->ConstructProcess();
    for(size_t i=0; i<fHadronPhys.size(); i++) {
      fHadronPhys[i]->ConstructProcess();
    }
  }

  //****************************************************************************
  // Method
  //****************************************************************************
  void PhysicsList::SetPhysicsList(const G4String& name)
  {
    if (verboseLevel>0) {
      G4cout << "PhysicsList::AddPhysicsList: <" << name << ">" << G4endl;
    }

    if (name == "Option0") {
      PhysicsList0();

    } else if (name == "Option1") {
      PhysicsList1();

    } else if (name == "Option2") {
      PhysicsList2();

    } else {

      G4cout << "PhysicsList::AddPhysicsList: <" << name << ">"
             << " is not defined"
             << G4endl;
    }
  }

  //****************************************************************************
  // Method
  //****************************************************************************
  void PhysicsList::List()
  {
    G4cout << G4endl;
    G4cout << "=======================================================================" << G4endl;
    G4cout << "======                 Physics Lists available                 ========" << G4endl;
    G4cout << "=======================================================================" << G4endl;
    G4cout << "### Option0: Electromagnetic" << G4endl;
    G4cout << "    G4DecayPhysics" << G4endl;
    G4cout << "    G4EmLivermorePolarizedPhysics" << G4endl;
    G4cout << "### Option1: Electromagnetic & Hadronic" << G4endl;
    G4cout << "    G4DecayPhysics" << G4endl;
    // G4cout << "    G4EmStandardPhysics_option4" << G4endl;
    G4cout << "    G4EmLivermorePolarizedPhysics" << G4endl;
    G4cout << "    G4HadronPhysicsFTFP_BERT" << G4endl;
    G4cout << "    G4HadronElasticPhysics" << G4endl;
    G4cout << "    G4IonPhysics" << G4endl;
    G4cout << "    G4StoppingPhysics" << G4endl;
    G4cout << "    G4EmExtraPhysics" << G4endl;
    G4cout << "    G4RadioactiveDecayPhysics" << G4endl;
    G4cout << "### Option2: Electromagnetic & Hadronic with high precision option" << G4endl;
    G4cout << "    G4DecayPhysics" << G4endl;
    G4cout << "    G4EmLivermorePolarizedPhysics" << G4endl;
    // G4cout << "    G4EmStandardPhysics_option4" << G4endl;
    G4cout << "    G4HadronPhysicsFTFP_BERT_HP" << G4endl;
    G4cout << "    G4HadronElasticPhysicsHP" << G4endl;
    G4cout << "    G4IonPhysicsXS" << G4endl;
    G4cout << "    G4IonElasticPhysics" << G4endl;
    G4cout << "    G4StoppingPhysics" << G4endl;
    G4cout << "    G4NeutronTrackingCut" << G4endl;
    G4cout << "    G4EmExtraPhysics" << G4endl;
    G4cout << "    G4RadioactiveDecayPhysics" << G4endl;
    G4cout << G4endl;

  }

  //****************************************************************************
  // Method
  //****************************************************************************
  void PhysicsList::PhysicsList0()
  {
    //------------------------------------------//
    // Clear old physics
    //------------------------------------------//
    fHadronPhys.clear();

    //------------------------------------------//
    // Set physics
    //------------------------------------------//
    // Decay
    //
    fParticleList = new G4DecayPhysics(verboseLevel);

    // EM
    //
    // fEmPhysicsList = new G4EmStandardPhysics(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option1(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option2(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option3(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option4(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysicsGS(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysicsSS(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysicsWVI(verboseLevel);
    // fEmPhysicsList = new G4EmLowEPPHysics(verboseLevel);
    // fEmPhysicsList = new G4EmLivermorePhysics(verboseLevel);
    fEmPhysicsList = new G4EmLivermorePolarizedPhysics(verboseLevel);
    // fEmPhysicsList = new G4EmPenelopePhysics(verboseLevel);
    
  }

  //****************************************************************************
  // Method
  //****************************************************************************
  void PhysicsList::PhysicsList1()
  {
    //------------------------------------------//
    // Clear old physics
    //------------------------------------------//
    fHadronPhys.clear();

    //------------------------------------------//
    // Set physics
    //------------------------------------------//
    // Decay
    //
    fParticleList = new G4DecayPhysics(verboseLevel);

    // EM
    //
    // fEmPhysicsList = new G4EmStandardPhysics(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option1(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option2(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option3(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option4(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysicsGS(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysicsSS(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysicsWVI(verboseLevel);
    // fEmPhysicsList = new G4EmLowEPPHysics(verboseLevel);
    // fEmPhysicsList = new G4EmLivermorePhysics(verboseLevel);
    fEmPhysicsList = new G4EmLivermorePolarizedPhysics(verboseLevel);
    // fEmPhysicsList = new G4EmPenelopePhysics(verboseLevel);
    
    // Hadron Inelastic Physics
    //
    fHadronPhys.push_back( new G4HadronPhysicsFTFP_BERT(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC_HP(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC_AllHP(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronInelasticQBBC(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronPhysicsINCLXX(verboseLevel) );
    
    // Hadron Elastic scattering
    //
    fHadronPhys.push_back( new G4HadronElasticPhysics(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronElasticPhysicsHP(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronElasticPhysicsXS(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronElasticPhysicsLEND(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronDElasticPhysics(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronHElasticPhysics(verboseLevel) );
    
    // Ion Inelastic physics
    //
    fHadronPhys.push_back( new G4IonPhysics(verboseLevel) );
    // fHadronPhys.push_back( new G4IonPhysicsXS(verboseLevel) );
    // fHadronPhys.push_back( new G4IonINCLXXPhysics(verboseLevel) );
    
    // Ion Elastic scattering
    //
    // fHadronPhys.push_back( new G4IonElasticPhysics(verboseLevel) );
    
    // Stopping Particles
    //
    fHadronPhys.push_back( new G4StoppingPhysics(verboseLevel) );

    // Neutron Tracking
    //
    // fHadronPhys.push_back( new G4NeutronTrackingCut(verboseLevel) );
        
    // Gamma-Nuclear Physics
    //   
    fHadronPhys.push_back( new G4EmExtraPhysics() );

    // Radioactive decay
    //
    fHadronPhys.push_back( new G4RadioactiveDecayPhysics(verboseLevel) );  

  }

  //****************************************************************************
  // Method
  //****************************************************************************
  void PhysicsList::PhysicsList2()
  {
    //------------------------------------------//
    // Clear old physics
    //------------------------------------------//
    fHadronPhys.clear();

    //------------------------------------------//
    // Set physics
    //------------------------------------------//
    // Decay
    //
    fParticleList = new G4DecayPhysics(verboseLevel);

    // EM
    //
    // fEmPhysicsList = new G4EmStandardPhysics(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option1(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option2(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option3(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysics_option4(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysicsGS(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysicsSS(verboseLevel);
    // fEmPhysicsList = new G4EmStandardPhysicsWVI(verboseLevel);
    // fEmPhysicsList = new G4EmLowEPPHysics(verboseLevel);
    // fEmPhysicsList = new G4EmLivermorePhysics(verboseLevel);
    fEmPhysicsList = new G4EmLivermorePolarizedPhysics(verboseLevel);
    // fEmPhysicsList = new G4EmPenelopePhysics(verboseLevel);
    
    // Hadron Inelastic Physics
    //
    // fHadronPhys.push_back( new G4HadronPhysicsFTFP_BERT(verboseLevel) );
    fHadronPhys.push_back( new G4HadronPhysicsFTFP_BERT_HP(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC_HP(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronPhysicsQGSP_BIC_AllHP(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronInelasticQBBC(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronPhysicsINCLXX(verboseLevel) );
    
    // Hadron Elastic scattering
    //
    // fHadronPhys.push_back( new G4HadronElasticPhysics(verboseLevel) );
    fHadronPhys.push_back( new G4HadronElasticPhysicsHP(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronElasticPhysicsXS(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronElasticPhysicsLEND(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronDElasticPhysics(verboseLevel) );
    // fHadronPhys.push_back( new G4HadronHElasticPhysics(verboseLevel) );
    
    // Ion Inelastic physics
    //
    // fHadronPhys.push_back( new G4IonPhysics(verboseLevel) );
    fHadronPhys.push_back( new G4IonPhysicsXS(verboseLevel) );
    // fHadronPhys.push_back( new G4IonINCLXXPhysics(verboseLevel) );
    
    // Ion Elastic scattering
    //
    fHadronPhys.push_back( new G4IonElasticPhysics(verboseLevel) );
    
    // Stopping Particles
    //
    fHadronPhys.push_back( new G4StoppingPhysics(verboseLevel) );

    // Neutron Tracking
    //
    fHadronPhys.push_back( new G4NeutronTrackingCut(verboseLevel) );
        
    // Gamma-Nuclear Physics
    //   
    fHadronPhys.push_back( new G4EmExtraPhysics() );

    // Radioactive decay
    //
    fHadronPhys.push_back( new G4RadioactiveDecayPhysics(verboseLevel) );  

  }

  //****************************************************************************
  // Method from base class
  //****************************************************************************
  void PhysicsList::SetCuts()
  {
    SetCutValue(0*mm, "proton");
    SetCutValue(1*mm, "e-");
    SetCutValue(1*mm, "e+");
    SetCutValue(1*mm, "gamma");      
  }

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

