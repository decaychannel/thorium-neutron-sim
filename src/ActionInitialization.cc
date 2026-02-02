//
// ********************************************************************
// * ActionInitialization Implementation                               *
// ********************************************************************
//

#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
// #include "RunAction.hh"
// #include "EventAction.hh"
#include "SteppingAction.hh"

ActionInitialization::ActionInitialization()
    : G4VUserActionInitialization()
{
}

ActionInitialization::~ActionInitialization()
{
}

void ActionInitialization::BuildForMaster() const
{
    // For multi-threaded mode
    // SetUserAction(new RunAction());
}

void ActionInitialization::Build() const
{
    // Primary generator
    SetUserAction(new PrimaryGeneratorAction());

    // Stepping action for logging neutron interactions
    SetUserAction(new SteppingAction());

    // Optional user actions
    // SetUserAction(new RunAction());
    // SetUserAction(new EventAction());
}
