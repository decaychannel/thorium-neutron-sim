//
// ********************************************************************
// * Materials Implementation                                          *
// ********************************************************************
//

#include "Materials.hh"
#include "G4SystemOfUnits.hh"

Materials::Materials()
{
    fNistManager = G4NistManager::Instance();
    DefineMaterials();
    DefineCustomMaterials();
}

Materials::~Materials()
{
    // Materials are managed by Geant4, no need to delete
}

void Materials::DefineMaterials()
{
    // Define commonly used NIST materials
    // These can be accessed using GetMaterial("G4_XXX")
    
    // Gases
    fMaterialsMap["G4_AIR"] = fNistManager->FindOrBuildMaterial("G4_AIR");
    fMaterialsMap["G4_Galactic"] = fNistManager->FindOrBuildMaterial("G4_Galactic");
    
    // Metals
    fMaterialsMap["G4_Al"] = fNistManager->FindOrBuildMaterial("G4_Al");
    fMaterialsMap["G4_Fe"] = fNistManager->FindOrBuildMaterial("G4_Fe");
    fMaterialsMap["G4_Cu"] = fNistManager->FindOrBuildMaterial("G4_Cu");
    fMaterialsMap["G4_Pb"] = fNistManager->FindOrBuildMaterial("G4_Pb");
    fMaterialsMap["G4_W"] = fNistManager->FindOrBuildMaterial("G4_W");
    
    // Semiconductors
    fMaterialsMap["G4_Si"] = fNistManager->FindOrBuildMaterial("G4_Si");
    fMaterialsMap["G4_Ge"] = fNistManager->FindOrBuildMaterial("G4_Ge");
    
    // Scintillators
    fMaterialsMap["G4_PLASTIC_SC_VINYLTOLUENE"] = fNistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    fMaterialsMap["G4_SODIUM_IODIDE"] = fNistManager->FindOrBuildMaterial("G4_SODIUM_IODIDE");
    fMaterialsMap["G4_BGO"] = fNistManager->FindOrBuildMaterial("G4_BGO");
    
    // Common materials
    fMaterialsMap["G4_WATER"] = fNistManager->FindOrBuildMaterial("G4_WATER");
    fMaterialsMap["G4_CONCRETE"] = fNistManager->FindOrBuildMaterial("G4_CONCRETE");
}

void Materials::DefineCustomMaterials()
{   
    //
    // Thorium-232 (fertile material)
    //
    G4double thDensity = 11.7*g/cm3;  // Thorium metal density
    
    G4Isotope* Th232 = new G4Isotope("Th232", 90, 232, 232.038*g/mole);
    
    G4Element* thoriumElement = new G4Element("Thorium", "Th", 1);
    thoriumElement->AddIsotope(Th232, 100.0*perCent);
    
    G4Material* Th232_material = new G4Material("Th232", thDensity, 1);
    Th232_material->AddElement(thoriumElement, 1);
    
    fMaterialsMap["Th232"] = Th232_material;
}

G4Material* Materials::GetMaterial(const G4String& name)
{
    // First check if material is in our map
    auto it = fMaterialsMap.find(name);
    if (it != fMaterialsMap.end()) {
        return it->second;
    }
    
    // If not found, try to get it from NIST
    G4Material* material = fNistManager->FindOrBuildMaterial(name);
    if (material) {
        fMaterialsMap[name] = material;
        return material;
    }
    
    G4cerr << "Material " << name << " not found!" << G4endl;
    return nullptr;
}
