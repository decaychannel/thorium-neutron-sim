//
// ********************************************************************
// * DetectorConstruction Implementation                               *
// ********************************************************************
//

#include "DetectorConstruction.hh"
#include "Materials.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VisAttributes.hh"

DetectorConstruction::DetectorConstruction()
    : G4VUserDetectorConstruction(),
      fMaterials(nullptr),
      fWorldLogical(nullptr),
      fWorldPhysical(nullptr),
      fWorldSizeX(2.0*m),
      fWorldSizeY(2.0*m),
      fWorldSizeZ(2.0*m)
{
}

DetectorConstruction::~DetectorConstruction()
{
    delete fMaterials;
}

void DetectorConstruction::DefineMaterials()
{
    fMaterials = new Materials();
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{
    DefineMaterials();
    return DefineVolumes();
}

G4VPhysicalVolume* DetectorConstruction::DefineVolumes()
{
    // Get materials
    G4Material* worldMaterial = fMaterials->GetMaterial("G4_AIR");

    //
    // World
    //
    auto worldSolid = new G4Box("World",
                                fWorldSizeX/2,
                                fWorldSizeY/2,
                                fWorldSizeZ/2);

    fWorldLogical = new G4LogicalVolume(worldSolid,
                                        worldMaterial,
                                        "World");

    fWorldPhysical = new G4PVPlacement(nullptr,              // no rotation
                                       G4ThreeVector(),      // at (0,0,0)
                                       fWorldLogical,        // logical volume
                                       "World",              // name
                                       nullptr,              // mother volume
                                       false,                // no boolean operation
                                       0,                    // copy number
                                       true);                // check overlaps

    // World visualization - wireframe style
    auto worldVisAtt = new G4VisAttributes(G4Colour(0.5, 0.5, 0.5, 0.3));
    worldVisAtt->SetVisibility(true);
    worldVisAtt->SetForceWireframe(true);
    fWorldLogical->SetVisAttributes(worldVisAtt);

    //
    // Th-232 Fuel Rod (Thorium)
    //
    G4Material* fuelMaterial = fMaterials->GetMaterial("Th232");
    
    G4double rodRadius = 1.0*cm;
    G4double rodLength = 20.0*cm;
    
    auto fuelRodSolid = new G4Tubs("FuelRod",
                                    0.,              // inner radius
                                    rodRadius,       // outer radius
                                    rodLength/2,     // half length
                                    0.*deg,          // start angle
                                    360.*deg);       // spanning angle
    
    auto fuelRodLogical = new G4LogicalVolume(fuelRodSolid, 
                                               fuelMaterial,
                                               "FuelRod");
    
    new G4PVPlacement(nullptr,                    // no rotation
                      G4ThreeVector(0, 0, 0),     // position at center
                      fuelRodLogical,             // logical volume
                      "FuelRod",                  // name
                      fWorldLogical,              // mother volume
                      false,                      // no boolean operation
                      0,                          // copy number
                      true);                      // check overlaps
    
    // Fuel rod visualization - green solid color
    auto fuelVisAtt = new G4VisAttributes(G4Colour(0.0, 0.8, 0.0, 0.8));
    fuelVisAtt->SetVisibility(true);
    fuelVisAtt->SetForceSolid(true);
    fuelRodLogical->SetVisAttributes(fuelVisAtt);

    return fWorldPhysical;
}
