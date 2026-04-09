#pragma once
#include "app/StateFactoryInterface.h"
#include "app/StateInterface.h"

class MockStateFactory : public StateFactoryInterface {
private:
    bool createMainApplicationStateCalled = false;
    bool createConfigMenuStateCalled = false;
    bool createSetlistMenuStateCalled = false;
    StateInterface* mockMainApplicationState = nullptr;
    StateInterface* mockConfigMenuState = nullptr;
    StateInterface* mockSetlistMenuState = nullptr;

public:
    StateInterface* createMainApplicationState() override {
        createMainApplicationStateCalled = true;
        return mockMainApplicationState;
    }

    StateInterface* createConfigMenuState() override {
        createConfigMenuStateCalled = true;
        return mockConfigMenuState;
    }

    StateInterface* createSetlistMenuState() override {
        createSetlistMenuStateCalled = true;
        return mockSetlistMenuState;
    }

    bool createMainApplicationStateWasCalled() const { return createMainApplicationStateCalled; }
    bool createConfigMenuStateWasCalled() const { return createConfigMenuStateCalled; }
    bool createSetlistMenuStateWasCalled() const { return createSetlistMenuStateCalled; }

    void setMockMainApplicationState(StateInterface* state) { mockMainApplicationState = state; }
    void setMockConfigMenuState(StateInterface* state) { mockConfigMenuState = state; }
    void setMockSetlistMenuState(StateInterface* state) { mockSetlistMenuState = state; }
};
