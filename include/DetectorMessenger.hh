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
/// \file DetectorMessenger.cc
/// \brief Definition of the DetectorMessenger class

#ifndef DetectorMessenger_h
#define DetectorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class G4UIdirectory;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithoutParameter;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  class DetectorConstruction;

  //****************************************************************************
  /// Detector Messenger Class
  ///
  //****************************************************************************
  class DetectorMessenger: public G4UImessenger
  {
    public:
      DetectorMessenger( DetectorConstruction* );
      ~DetectorMessenger() override;

      // methods from base class
      void SetNewValue(G4UIcommand*, G4String) override;
      
    private:
      // data members
      DetectorConstruction* fDetectorConstruction = nullptr;
      
      G4UIdirectory* fUSERDir = nullptr;
      G4UIdirectory* fDetDir = nullptr;
      
      G4UIcmdWithABool* fOverlapCmd = nullptr;

  };

}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif
