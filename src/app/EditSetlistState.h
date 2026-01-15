#pragma once
#include "StateInterface.h"
#include "DiContainerInterface.h"
#include "Program.h"

// Forward declarations
class StateMachineInterface;

class EditSetlistState : public StateInterface {
private:
    DiContainerInterface* diContainer;
    StateMachineInterface* stateMachine;
    Program currentSetlist[16];
    int selectedIndex;
    bool isEditMode;
    int editedProgramNumber;

public:
    explicit EditSetlistState(DiContainerInterface* container);
    
    virtual ~EditSetlistState() = default;
    
    void enter() override;
    void exit() override;
    void update() override;
    StateInterface* setStateMachine(StateMachineInterface* stateMachine) override;
};