#pragma once
#include "DiContainerInterface.h"
#include "SplashScreenViewInterface.h"
#include "IoDriverInterface.h"
#include "StateFactoryInterface.h"

class DiContainer : public DiContainerInterface {
private:
    SplashScreenViewInterface* splashScreenView = nullptr;
    IoDriverInterface* ioDriver = nullptr;
    StateFactoryInterface* stateFactory = nullptr;

public:
    DiContainer() = default;
    virtual ~DiContainer() = default;
    
    // Setters
    DiContainer* setSplashScreenView(SplashScreenViewInterface* view) {
        this->splashScreenView = view;
        return this;
    }
    
    DiContainer* setIoDriver(IoDriverInterface* driver) {
        this->ioDriver = driver;
        return this;
    }
    
    DiContainer* setStateFactory(StateFactoryInterface* factory) {
        this->stateFactory = factory;
        return this;
    }
    
    // Getters (implementing interface)
    SplashScreenViewInterface* getSplashScreenView() const override {
        return splashScreenView;
    }
    
    IoDriverInterface* getIoDriver() const override {
        return ioDriver;
    }
    
    StateFactoryInterface* getStateFactory() const override {
        return stateFactory;
    }
};