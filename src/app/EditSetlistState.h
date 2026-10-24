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

    // State checking methods
    bool isInEditMode() const;
    bool isInNavigationMode() const;
    
    // Input condition checking methods
    bool encoderRotatedClockwise();
    bool encoderRotatedCounterClockwise();
    bool encoderButtonPressed();
    
    // Mode handlers
    void handleEditModeInput();
    void handleNavigationModeInput();
    
    // Edit mode operations
    void handleEditModeEncoderRotation();
    void incrementEditedProgram();
    void decrementEditedProgram();
    void updateEditedProgramDisplay();
    void saveEditedProgram();
    void exitEditMode();
    
    // Navigation mode operations
    void handleNavigationModeEncoderRotation();
    void moveSelectionUp();
    void moveSelectionDown();
    void updateSelectionDisplay();
    void enterEditMode();
    
    // Utility methods
    const char* getProgramDisplayName(int programNumber);
    void updateProgramInSetlist(int index, int programNumber);
    void updateViewAfterEdit();

public:
    explicit EditSetlistState(DiContainerInterface* container);
    
    virtual ~EditSetlistState() = default;
    
    void enter() override;
    void exit() override;
    void update() override;
    StateInterface* setStateMachine(StateMachineInterface* stateMachine) override;
};