//
// ********************************************************************
// * SteppingAction Implementation                                     *
// ********************************************************************
//

#include "SteppingAction.hh"

#include "G4Step.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4AutoLock.hh"

namespace { G4Mutex convergeMutex = G4MUTEX_INITIALIZER; }

SteppingAction::SteppingAction()
    : G4UserSteppingAction()
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    // Get track and particle info
    G4Track* track = step->GetTrack();
    G4String particleName = track->GetParticleDefinition()->GetParticleName();
    
    // Get process that defined the step
    const G4VProcess* process = step->GetPostStepPoint()->GetProcessDefinedStep();
    if (!process) return;
    
    G4String processName = process->GetProcessName();
    
    // Check for neutron interactions
    if (particleName == "neutron") {
        // Fission
        if (processName == "nFission") {
            G4AutoLock lock(&convergeMutex);
            G4cout << "=== FISSION ===" << G4endl;
            G4cout << "  Neutron Energy: " << step->GetPreStepPoint()->GetKineticEnergy()/MeV << " MeV" << G4endl;
            G4cout << "  Position: " << step->GetPostStepPoint()->GetPosition()/cm << " cm" << G4endl;
            
            // Count secondaries
            auto secondaries = step->GetSecondaryInCurrentStep();
            if (secondaries) {
                G4cout << "  Secondary particles: " << secondaries->size() << G4endl;
                for (auto sec : *secondaries) {
                    G4cout << "    - " << sec->GetParticleDefinition()->GetParticleName()
                           << " E=" << sec->GetKineticEnergy()/MeV << " MeV" << G4endl;
                }
            }
            G4cout << G4endl;
        }
        // Capture
        else if (processName == "nCapture") {
            G4AutoLock lock(&convergeMutex);
            G4cout << "=== CAPTURE ===" << G4endl;
            G4cout << "  Neutron Energy: " << step->GetPreStepPoint()->GetKineticEnergy()/eV << " eV" << G4endl;
            G4cout << "  Position: " << step->GetPostStepPoint()->GetPosition()/cm << " cm" << G4endl;
            
            auto secondaries = step->GetSecondaryInCurrentStep();
            if (secondaries && secondaries->size() > 0) {
                G4cout << "  Secondary particles: " << secondaries->size() << G4endl;
                for (auto sec : *secondaries) {
                    G4cout << "    - " << sec->GetParticleDefinition()->GetParticleName()
                           << " E=" << sec->GetKineticEnergy()/keV << " keV" << G4endl;
                }
            }
            G4cout << G4endl;
        }
    }
}
