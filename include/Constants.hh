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
/// \file Constants.hh
/// \brief Definition of the Constants class


#ifndef Constants_h
#define Constants_h 1

#include "globals.hh"
#include "G4SystemOfUnits.hh"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
namespace grape
{
  //****************************************************************************
  /// Constants to define geometry.
  ///
  //****************************************************************************
  constexpr auto kNumKeep = 8;
  constexpr auto kDim = 245;
  constexpr auto kNumC = 145;
  constexpr auto kNumP = 100;

  //--------------------------------------------------------
  // SCINTILLATOR
  //--------------------------------------------------------
  constexpr auto kScint_Xsize = 12.5*mm;
  constexpr auto kScint_Ysize = 12.5*mm;
  constexpr auto kScint_Zsize = 12.5*mm;

  constexpr auto kScint_Xpitch = 21.1*mm;
  constexpr auto kScint_Ypitch = 21.1*mm;
  constexpr auto kScint_Zpitch = 20.0*mm;

  constexpr auto kNumScint_X = 7;
  constexpr auto kNumScint_Y = 7;
  constexpr auto kNumScint_Z = 5;

  constexpr auto kNumScint = kNumScint_X * kNumScint_Y * kNumScint_Z;

  //--------------------------------------------------------
  // CALIBRATION SOURCE
  //--------------------------------------------------------
  constexpr auto kCal_Rmin = 0.0*mm;
  constexpr auto kCal_Rmax = 5.0*mm;
  constexpr auto kCal_Zsize = 10.0*mm;

  //--------------------------------------------------------
  // Optical Pad
  //--------------------------------------------------------
  constexpr auto kOpticalPad_Xsize = kScint_Xsize;
  constexpr auto kOpticalPad_Ysize = kScint_Ysize;
  constexpr auto kOpticalPad_Zsize = 1.0*mm;

  //--------------------------------------------------------
  // SiPM (Hamamatsu S13361-3050NE-04)
  //--------------------------------------------------------
  constexpr auto kSiPM_Xsize = 13.0*mm;
  constexpr auto kSiPM_Ysize = 13.0*mm;
  constexpr auto kSiPM_Zsize = 1.35*mm;

  //--------------------------------------------------------
  // SiPM Power Board
  //--------------------------------------------------------
  constexpr auto kSiPM_PCB_Xsize = kSiPM_Xsize;
  constexpr auto kSiPM_PCB_Ysize = kSiPM_Xsize;
  constexpr auto kSiPM_PCB_Zsize = 1.6*mm;

  // constexpr auto kDet_Gap = 2.0*mm;
  constexpr auto kDet_Gap = ( 107.0*mm - 
                  5 * ( kScint_Zsize + 
                    kOpticalPad_Zsize + 
                    kSiPM_Zsize + 
                    kSiPM_PCB_Zsize ) ) / 5;

  //--------------------------------------------------------
  // DETECTOR Element
  //--------------------------------------------------------
  constexpr auto kDetElement_Xsize = kSiPM_Xsize;
  constexpr auto kDetElement_Ysize = kSiPM_Xsize;
  constexpr auto kDetElement_Zsize = 
                  kScint_Zsize +
                  kOpticalPad_Zsize +
                  kSiPM_Zsize +
                  kSiPM_PCB_Zsize +
                  kDet_Gap;

  //--------------------------------------------------------
  // SCINTILLATOR CASE
  //--------------------------------------------------------
  constexpr auto kScint_Case_Thickness = 2.0*mm;

  constexpr auto kScint_Case_Top_Xsize = kSiPM_Xsize + kScint_Case_Thickness;
  constexpr auto kScint_Case_Top_Ysize = kSiPM_Ysize + kScint_Case_Thickness;
  constexpr auto kScint_Case_Top_Zsize = 10.0*mm;

  constexpr auto kScint_Case_Bot_Xsize = kSiPM_Xsize + kScint_Case_Thickness;
  constexpr auto kScint_Case_Bot_Ysize = kSiPM_Ysize + kScint_Case_Thickness;
  constexpr auto kScint_Case_Bot_Zsize = 8.0*mm;

  constexpr auto kScint_Case_Xsize = kSiPM_Xsize + 2*kScint_Case_Thickness;
  constexpr auto kScint_Case_Ysize = kSiPM_Ysize + 2*kScint_Case_Thickness;
  // constexpr auto kScint_Case_Zsize = 107*mm;
  constexpr auto kScint_Case_Zsize = 
                  kDetElement_Zsize * kNumScint_Z +
                  kScint_Case_Thickness -
                  kScint_Case_Top_Zsize - 
                  kScint_Case_Bot_Zsize;

  //--------------------------------------------------------
  // Module Interface Board (MIB)
  //--------------------------------------------------------
  // constexpr auto kMIB_Xsize = 164.0*mm;
  // constexpr auto kMIB_Ysize = 164.0*mm;
  constexpr auto kMIB_Xsize = 152.0*mm;
  constexpr auto kMIB_Ysize = 152.0*mm;
  constexpr auto kMIB_Zsize = 1.5*mm;

  //--------------------------------------------------------
  // Analog Power Board (APB)
  //--------------------------------------------------------
  constexpr auto kAPB_Xsize = 1.5*mm;
  constexpr auto kAPB_Ysize = 147.0*mm;
  constexpr auto kAPB_Zsize = 120.0*mm;

  constexpr auto kAPB_Zoffset = 4.0*mm; // baseplate offset
  constexpr auto kAPB_MIB_Zoffset = 2.0*mm;

  //--------------------------------------------------------
  // APB - MIB Connectors
  //--------------------------------------------------------
  constexpr auto kAPB_Con_Xsize = 5.0*mm;
  constexpr auto kAPB_Con_Ysize = 75.0*mm;
  constexpr auto kAPB_Con_Zsize = 10.0*mm;

  //--------------------------------------------------------
  // Enclosure (ENCL) Base Plate 
  //--------------------------------------------------------
  constexpr auto kENCL_Thickness = 5.0*mm;
  constexpr auto kENCL_Bot_Xsize = 162.0*mm;
  constexpr auto kENCL_Bot_Ysize = 162.0*mm;
  constexpr auto kENCL_Bot_Zsize = kENCL_Thickness;

  //--------------------------------------------------------
  // Enclosure (ENCL) Top
  //--------------------------------------------------------
  constexpr auto kENCL_Top_Xsize = kScint_Xpitch;
  constexpr auto kENCL_Top_Ysize = kScint_Ypitch;
  constexpr auto kENCL_Top_Zsize = 7.5*mm;

  constexpr auto kENCL_Top_Hole_Xsize = kScint_Case_Top_Xsize;
  constexpr auto kENCL_Top_Hole_Ysize = kScint_Case_Top_Ysize;
  constexpr auto kENCL_Top_Hole_Zsize = 2*kENCL_Top_Zsize;

  constexpr auto kENCL_Top_Zoffset = 0.75*mm;

  //--------------------------------------------------------
  // Enclosure (ENCL) Top Edge
  //--------------------------------------------------------
  constexpr auto kENCL_TopEdge_Xsize = kENCL_Bot_Xsize;
  constexpr auto kENCL_TopEdge_Ysize = kENCL_Bot_Ysize;
  constexpr auto kENCL_TopEdge_Zsize = kENCL_Top_Zsize;

  constexpr auto kENCL_TopEdge_Hole_Xsize = kNumScint_X * kScint_Xpitch;
  constexpr auto kENCL_TopEdge_Hole_Ysize = kNumScint_Y * kScint_Ypitch;
  constexpr auto kENCL_TopEdge_Hole_Zsize = 2*kENCL_TopEdge_Zsize;

  //--------------------------------------------------------
  // MIB Plate
  //--------------------------------------------------------
  constexpr auto kMIBP_Xsize = kScint_Xpitch;
  constexpr auto kMIBP_Ysize = kScint_Ypitch;
  constexpr auto kMIBP_Zsize = 10.5*mm;

  // holes
  constexpr auto kMIBP_Hole_Xsize = kScint_Case_Bot_Xsize;
  constexpr auto kMIBP_Hole_Ysize = kScint_Case_Bot_Ysize;
  constexpr auto kMIBP_Hole_Zsize = 2*kMIBP_Zsize;

  constexpr auto kMIBP_Zoffset = 1.5*mm;

  //--------------------------------------------------------
  // MIB Plate Edge
  //--------------------------------------------------------
  constexpr auto kMIBP_Edge_Xsize = kENCL_Bot_Xsize;
  constexpr auto kMIBP_Edge_Ysize = kENCL_Bot_Ysize;
  constexpr auto kMIBP_Edge_Zsize = kMIBP_Zsize;

  constexpr auto kMIBP_Edge_Hole_Xsize = kNumScint_X * kScint_Xpitch;
  constexpr auto kMIBP_Edge_Hole_Ysize = kNumScint_Y * kScint_Ypitch;
  constexpr auto kMIBP_Edge_Hole_Zsize = 2*kMIBP_Edge_Zsize;

  //--------------------------------------------------------
  // DETECTOR Column
  //--------------------------------------------------------
  constexpr auto kDetColumn_Xsize = kScint_Xpitch;
  constexpr auto kDetColumn_Ysize = kScint_Ypitch;
  constexpr auto kDetColumn_Zsize = 
                  kMIBP_Zoffset +
                  kMIBP_Zsize +
                  kScint_Case_Zsize +
                  kScint_Case_Top_Zsize;

  //--------------------------------------------------------
  // MODULE
  //--------------------------------------------------------
  constexpr auto kModule_Xsize = kENCL_Bot_Xsize + 2*kENCL_Thickness;
  constexpr auto kModule_Ysize = kENCL_Bot_Ysize + 2*kENCL_Thickness;
  constexpr auto kModule_Zsize = 
                  kENCL_Bot_Zsize +
                  kAPB_Zoffset +
                  kAPB_Zsize +
                  kAPB_MIB_Zoffset +
                  kMIB_Zsize +
                  kDetColumn_Zsize;

  //--------------------------------------------------------
  // Enclosure (ENCL) Side
  //--------------------------------------------------------
  constexpr auto kENCL_Side1_Xsize = kENCL_Thickness;
  constexpr auto kENCL_Side1_Ysize = kENCL_Bot_Ysize + 2*kENCL_Thickness;
  constexpr auto kENCL_Side1_Zsize = 
                  kENCL_Bot_Zsize +
                  kAPB_Zoffset +
                  kAPB_Zsize +
                  kAPB_MIB_Zoffset +
                  kMIB_Zsize +
                  kMIBP_Zoffset +
                  kMIBP_Zsize +
                  kScint_Case_Zsize +
                  kENCL_Top_Zoffset +
                  kENCL_Top_Zsize;

  constexpr auto kENCL_Side2_Xsize = kENCL_Bot_Ysize;
  constexpr auto kENCL_Side2_Ysize = kENCL_Thickness;
  constexpr auto kENCL_Side2_Zsize = kENCL_Side1_Zsize;


  //--------------------------------------------------------
  // WORLD
  //--------------------------------------------------------
  constexpr auto kWorld_Xsize = 5.0*m;
  constexpr auto kWorld_Ysize = 5.0*m;
  constexpr auto kWorld_Zsize = 5.0*m;
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#endif
