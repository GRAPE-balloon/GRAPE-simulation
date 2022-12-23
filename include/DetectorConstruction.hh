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
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"

class G4VPhysicalVolume;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{

  class DetectorMessenger;

  //****************************************************************************
  /// Detector construction class to define materials and geometry.
  ///
  //****************************************************************************
  class DetectorConstruction : public G4VUserDetectorConstruction
  {
    public:
      DetectorConstruction();
      ~DetectorConstruction() override;

      // methods from base class
      G4VPhysicalVolume* Construct() override;
      void ConstructSDandField() override;
      
      // set methods
      void SetOverlapFlag( G4bool flag ) {fCheckOverlaps = flag;};          
 
    private:
      // methods
      void DefineMaterials();
      G4VPhysicalVolume* DefineVolumes();
    
      // data members
      DetectorMessenger* fDetMessenger = nullptr;   // messenger

      G4bool fCheckOverlaps = true; // option to activate checking of volumes overlaps
  };
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif

