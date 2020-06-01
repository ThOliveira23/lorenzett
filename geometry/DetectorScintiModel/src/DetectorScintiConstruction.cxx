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
G4GlobalMagFieldMessenger* DetectorScintiConstruction::m_magFieldMessenger = 0;

DetectorScintiConstruction::DetectorScintiConstruction(std::string name)
  :
   IMsgService(name),
    G4VUserDetectorConstruction(),
    m_checkOverlaps(true)
 {
    MSG_INFO( "DetectorConstruction was created" );
 }

DetectorScintiConstruction::~DetectorScintiConstruction()
{;}

G4VPhysicalVolume* DetectorScintiConstruction::Construct()
{
    // Define materials
    DefineMaterials();
    // Define volumes
    return DefineVolumes();
    
}

void DetectorScintiConstruction::DefineMaterials()
{
    // Lead Material defined using NIST Manager
    G4NistManager* nistManager = G4NistManager::Instance();
    nistManager->FindOrBuildMaterial("G4_Pb");
    nistManager->FindOrBuildMaterial("G4_Fe");
    nistManager->FindOrBuildMaterial("G4_Al");
    nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    nistManager->FindOrBuildMaterial("PLASTIC SCINTILLATOR");
    
    // Elements for scintillator and steel
    // G4Element* el = new G4Element("name", "symbol", Z, density);
    
    // For scintillator
    G4Element* elH = new G4Element("Hydrogen", "H", 1., 1.0079*g/mole);
    G4Element* elC = new G4Element("Carbon", "C", 6., 12.011*g/mole);
    
    // For steel
    G4Element* elSi = new G4Element("Silicon", "Si", 14., 28.09*g/mole);
    G4Element* elCr = new G4Element("Chromiun", "Cr", 24., 52.00*g/mole);
    G4Element* elMn = new G4Element("Manganese", "Mn", 25., 54.94*g/mole);
    G4Element* elFe = new G4Element("Iron", "Fe", 26., 55.85*g/mole);
    G4Element* elNi = new G4Element("Nickel", "Ni", 28., 58.70*g/mole);
    
   // Scintillator
   G4Material* scinti = new G4Material("PLASTIC SCINTILLATOR", 1.032*g/cm3, 2); // name, density, no of atoms
    scinti->AddElement(elH, 0.085);
    scinti->AddElement(elC, 0.915);
    
    // Stainless Steel
    G4Material* steel = new G4Material("Stainless Steel", 8.02*g/cm3, 5);
    steel->AddElement(elMn, 0.02);
    steel->AddElement(elSi, 0.01);
    steel->AddElement(elCr, 0.19);
    steel->AddElement(elNi, 0.10);
    steel->AddElement(elFe, 0.68);
    
    G4double a,z,density;
    
    // Liquid Argon
    new G4Material("liquidArgon", 18., 39.95*g/mole, 1.390*g/cm3);
    
    // Vacuum
    new G4Material("Galactic", z=1., a=1.01*g/mole,density= universe_mean_density,kStateGas, 2.73*kelvin, 3.e-18*pascal);
    
    // Print Materials
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

G4VPhysicalVolume* DetectorScintiConstruction::DefineVolumes()
{
    
    // Get materials
    G4Material* defaultMaterial = G4Material::GetMaterial("Galactic");
    
    
    // Defining the world
    G4VSolid* worldS = new G4Tubs( "World",       // its name
                                    0,            // R min
                                    5000*cm,      // R max
                                    10000*cm,     // Z max
                                    0*deg,        // phi_min
                                    360*deg);     // phi_max
    
    G4LogicalVolume* worldLV = new G4LogicalVolume(
                                   worldS,              // its solid
                                   defaultMaterial,     // its material
                                   "World");            // its name
    
    G4VPhysicalVolume* worldPV = new G4PVPlacement(
                   0,                 // no rotation
                   G4ThreeVector(),   // at (0,0,0)
                   worldLV,           // its logical volume
                   "World",           // its name
                   0,                 // its mother
                   false,             // no boolean operation
                   0,                 // copy number
                   m_checkOverlaps);  // checking overlaps
    
    
}
