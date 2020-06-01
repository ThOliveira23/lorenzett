#ifndef DetectorScintiConstruction_h
#define DetectorScintiConstruction_h

#include "GaugiKernel/MsgStream.h"
#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"
#include "G4ThreeVector.hh"
#include "G4Region.hh"
#include "globals.hh"

// Class definitions
// The physical volume can be translated or rotated and the logical volume carries the volume itself
class G4VPhysicalVolume;
class G4GlobalMagFieldMessenger;

// Derive your own concrete class from the G4VUserDetectorConstruction abstract base class
class DetectorScintiConstruction : public G4VUserDetectorConstruction, public MsgService
{
// The method construct()
// Construct all necessary material
// Define shapes/solids required to describe the geometry
// Construct and place volumes of your detector geometry

  public:
    DetectorScintiConstruction(std::string);
    virtual ~DetectorScintiConstruction();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
    
    // Get methods
    const G4VPhysicalVolume* GetAbsorberPV() const;
    const G4VPhysicalVolume* GetGapPV() const;
    
  private:
    
    // Methods
    void DefineMaterials();
    
    G4VPhysicalVolume* DefineVolumes();
    
    // Creating the regions of the detector
    void CreateBarrel( G4LogicalVolume *worldLV,
                       std::string name,
                       G4Material *defaultMaterial,
                       G4Material *absorberMaterial,
                       G4Material *gapMaterial,
                       int nofLayers,
                       double absoThickness,
                       double gapThickness,
                       double calorRmin,
                       double calorZ,
                       G4ThreeVector center_pos,
                       G4Region* region);
    
    static G4ThreadLocal G4GlobalMagFieldMessenger* m_magFieldMessenger; // Magnetic Field Messenger
    bool m_checkOverlaps; // option to activate checking of volumes overlaps
    
};

#endif

