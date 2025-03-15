#include <iostream>
#include "unitTests.h"
#include "Eigen/Dense"
#include "Eigen/src/Core/functors/TernaryFunctors.h"
#include "utils.h"

int main() {
    std::cout << "Hello World!" << std::endl;

    // Unit Tests
    //testIMU();
    //testRW();
    //testSYSCMD();
    //countTime();

    // Integration Testsuj8p
    //generatePath();
    //testEKFFunctions();

    // System Tests
    testEKF();
    return 0;
}
