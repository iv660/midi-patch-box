#pragma once

// Forward declarations
class SplashScreenViewInterface;
class IoDriverInterface;
class StateFactoryInterface;

class DiContainerInterface {
public:
    virtual ~DiContainerInterface() = default;
    
    virtual SplashScreenViewInterface* getSplashScreenView() const = 0;
    virtual IoDriverInterface* getIoDriver() const = 0;
    virtual StateFactoryInterface* getStateFactory() const = 0;
};