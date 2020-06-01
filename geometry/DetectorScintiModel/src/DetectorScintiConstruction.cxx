#include "DetectorScintiConstruction.h"
#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4UniformMagField.hh"
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include <string>
#include <sstream>

G4ThreadLocal
G4GlobalMagFieldMessenger* DetectorScintiConstruction::m:magFieldMessenger = 0;

DetectorScintiConstruction::DetectorScintiConstruction(std::string name)
  :
   IMsgService(name),
    G4UserDetectorConstruction(),
    m_checkOverlaps(true)
 {
     MSG_INFO( "DetectorConstruction was created" );
 }

DetectorScintiConstruction::~DetectorScintiConstruction()
{;}

G4PhysicalVolume* DetectorScintiConstruction::Construct()
{
    // Define materials
    DefineMaterials();
    // Define volumes
    return DefineVolumes();
    
}
