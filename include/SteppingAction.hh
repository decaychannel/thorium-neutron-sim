//
// ********************************************************************
// * SteppingAction Header                                             *
// ********************************************************************
//

#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4Step;

class SteppingAction : public G4UserSteppingAction
{
public:
    SteppingAction();
    ~SteppingAction() override;

    void UserSteppingAction(const G4Step* step) override;
};

#endif
