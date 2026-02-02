//
// ********************************************************************
// * PrimaryGeneratorAction Implementation                             *
// ********************************************************************
//

#include "PrimaryGeneratorAction.hh"

#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"

PrimaryGeneratorAction::PrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(),
      fParticleGun(nullptr)
{
    G4int nParticles = 1;
    fParticleGun = new G4ParticleGun(nParticles);

    // Default particle settings
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle("neutron");
    
    fParticleGun->SetParticleDefinition(particle);
    fParticleGun->SetParticleEnergy(0.025*eV);  // Thermal neutron energy
    fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., -30.*cm));
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fParticleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    fParticleGun->GeneratePrimaryVertex(event);
}
