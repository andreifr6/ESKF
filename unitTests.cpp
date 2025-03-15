//
// Created by andre on 16/05/2024.
//

#include "unitTests.h"
#include "IMU.h"
#include "CAM.h"
#include "KF.h"
#include "RWSW.h"
#include <iostream>
#include <fstream>
#include "PPC.h"
#include "SYSCMD.h"
#include <chrono>
#include <thread>
#include <iomanip>

int countTime() {
    auto tic = std::chrono::high_resolution_clock::now();
    //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    auto toc = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = toc - tic;
    std::cout<< "Time count: " << elapsed.count() << std::endl;
    return 0;
}

int testSYSCMD(){
    std::string filename = "commands.csv";
    SYSCMD systemCMD(filename);
    if (!systemCMD.isCommandEmpty()) {
        systemCMD.printCommands();
    } else {
        std::cerr << "Algo aconteceu" << std::endl;
    }

    systemCMD.getCommand(0);
    systemCMD.printCommand();

    systemCMD.getCommand(5);
    systemCMD.printCommand();

    systemCMD.getCommand(10);
    systemCMD.printCommand();

    systemCMD.getCommand(11);
    systemCMD.printCommand();

    systemCMD.getCommand(25);
    systemCMD.printCommand();

    systemCMD.getCommand(35);
    systemCMD.printCommand();

    systemCMD.getCommand(100);
    systemCMD.printCommand();

    systemCMD.getCommand(500);
    systemCMD.printCommand();
    return 0;
}

int testIMU() {
    // Create initial values
    Eigen::Matrix3d wVarIni = Eigen::Matrix3d::Identity()*1;
    Eigen::Matrix3d aVarIni = Eigen::Matrix3d::Identity()*0.1;
    Eigen::Vector3d wBiasIni;
    wBiasIni << 0,0,0;
    Eigen::Vector3d aBiasIni;
    aBiasIni << 0,0,0;
    double samplingTimeIni = 0.010f;

    // Create IMU
    IMU IMUsensor(aVarIni,wVarIni,aVarIni,wVarIni,aBiasIni, wBiasIni, samplingTimeIni);
    IMUsensor.getInfo();

    // Measurement test
    Eigen::Vector3d wTrue;
    wTrue << 1, 2, 3;
    Eigen::Vector3d aTrue;
    aTrue << 1, 2, 9.81;
    Eigen::Vector4d qTrue;
    qTrue << 1,0,0,0;
    Eigen::Vector3d gTrue;
    gTrue << 0, 0, -9.81f;
    IMUsensor.getMeasurement(aTrue,wTrue);
    IMUsensor.getInfo();

    std::ofstream IMUmeasPPC;
    IMUmeasPPC.open("IMUmeasPPC.csv");
    makeCollumsIMU(&IMUmeasPPC);

    double dt = 0.001f;
    // In 0.025 should have 2 measurements
    for(int i = 0;i<25;i++) {
        IMUsensor.updateClock(dt);
        if(IMUsensor.checkTimeout()) {
            IMUsensor.getMeasurement(aTrue,wTrue);
            std::cout << "Meas:\n" << IMUsensor.getLastMeasurement() << std::endl;
        }
    }
    return 0;
}

int testRW() {
    // INITIALIZATION
    // Init RWSW
    std::cout << "Initianting test RWSW!" << std::endl;
    Eigen::Vector3d pRWSWIni = Eigen::Vector3d::Zero(3,1);
    Eigen::Vector3d vRWSWIni = Eigen::Vector3d::Zero(3,1);
    Eigen::Vector4d qRWSWIni;
    qRWSWIni << 1,0,0,0;
    Eigen::Vector3d abRWSWIni;
    abRWSWIni << 0,0,0;
    Eigen::Vector3d wbRWSWIni;
    wbRWSWIni << 0,0,0;
    RW RWSW(pRWSWIni, vRWSWIni, qRWSWIni, abRWSWIni, wbRWSWIni);

    // Commands
    Eigen::Vector3d aCmd;
    aCmd << 0.1, 0.2, 10;
    Eigen::Vector3d wCmd;
    wCmd << 1, -1, 2;

    // Time steps
    double dt = 0.001;
    // Total simulation time
    double simTimeEnd = 10;
    // Number of simulation iterations
    int numPoints = (int) (simTimeEnd/dt);
    // Current simulation time
    double simTime = 0;
    std::cout << "Num of steps: " << numPoints << std::endl;

    // Creating csv for results
    std::cout << "Creating .csv..." << std::endl;
    std::ofstream trueStatePPC;
    trueStatePPC.open("trueStatePPC.csv");
    makeCollumsTrue(&trueStatePPC);
    saveTrueStates(&trueStatePPC,simTime,RWSW.getTrueState());

    for(int i =0;i<numPoints;++i) {
        std::cout << "Interation: " << i << std::endl;
        // Update RWSW
        std::cout << "Updating RWSW..." << std::endl;
        RWSW.updateX(aCmd,wCmd,dt);
        saveTrueStates(&trueStatePPC,RWSW.getTime(),RWSW.getTrueState());
    }
    RWSW.getInfo();
    trueStatePPC.close();
    return 0;
}

int generatePath() {
    // INITIALIZATION
    std::cout << "Initianting test Generate Path!" << std::endl;

    // Init System Command
    std::string filename = "commands.csv";
    SYSCMD systemCMD(filename);
    if (!systemCMD.isCommandEmpty()) {
        systemCMD.printCommands();
    } else {
        std::cerr << "Ops, some problem with commands.csv" << std::endl;
    }

    Eigen::Vector3d aCmd;
    aCmd << 0, 0, 0;
    Eigen::Vector3d wCmd;
    wCmd << 0, 0, 0;

    // Init RWSW
    Eigen::Vector3d pRWSWIni = Eigen::Vector3d::Zero(3,1);
    Eigen::Vector3d vRWSWIni = Eigen::Vector3d::Zero(3,1);
    Eigen::Vector4d qRWSWIni;
    qRWSWIni << 1,0,0,0;
    Eigen::Vector3d abRWSWIni;
    abRWSWIni << 0,0,0;
    Eigen::Vector3d wbRWSWIni;
    wbRWSWIni << 0,0,0;
    RW RWSW(pRWSWIni, vRWSWIni, qRWSWIni, abRWSWIni, wbRWSWIni);

    // Time steps
    double dt = 0.0002;
    // Total simulation time
    double simTimeEnd = 100;
    // Number of simulation iterations
    int numPoints = (int) (simTimeEnd/dt);
    // Current simulation time
    double simTime = 0;
    std::cout << "Num of steps: " << numPoints << std::endl;

    // Creating csv for results
    std::cout << "Creating .csv..." << std::endl;
    std::ofstream trueStatePPC;
    trueStatePPC.open("trueStatePPC.csv");
    makeCollumsTrue(&trueStatePPC);
    saveTrueStates(&trueStatePPC,simTime,RWSW.getTrueState());
    for(int i =0;i<numPoints;++i) {
        //std::cout << "Interation: " << i << std::endl;
        // Update RWSW
        //std::cout << "Updating RWSW..." << std::endl;

        RWSW.updateTime(dt);
        systemCMD.getCommand(RWSW.getTime());
        aCmd[0] = systemCMD.cmd.ax;
        aCmd[1] = systemCMD.cmd.ay;
        aCmd[2] = systemCMD.cmd.az;
        wCmd[0] = systemCMD.cmd.wx;
        wCmd[1] = systemCMD.cmd.wy;
        wCmd[2] = systemCMD.cmd.wz;
        RWSW.updateX(aCmd,wCmd,dt);
        saveTrueStates(&trueStatePPC,RWSW.getTime(),RWSW.getTrueState());
        if(i%1000 == 0) {
            std::cout << "Time " << RWSW.getTime() << std::endl;
        }
    }
    RWSW.getInfo();
    trueStatePPC.close();
    return 0;
}

int testEKFFunctions() {
    // INITIALIZATION
    // Init RWSW
    std::cout << "Initianting test EKF!" << std::endl;
    Eigen::Vector3d pRWSWIni = Eigen::Vector3d::Zero(3,1);
    Eigen::Vector3d vRWSWIni = Eigen::Vector3d::Zero(3,1);
    Eigen::Vector4d qRWSWIni;
    qRWSWIni << 1,0,0,0;
    Eigen::Vector3d abRWSWIni;
    abRWSWIni << 0.01,0.02,0.03;
    Eigen::Vector3d wbRWSWIni;
    wbRWSWIni << 0.01,0.02,0.03;
    RW RWSW(pRWSWIni, vRWSWIni, qRWSWIni, abRWSWIni, wbRWSWIni);

    // Create initial values for IMU
    std::cout << "Initianting IMU" << std::endl;
    Eigen::Matrix3d wVarIMUIni = Eigen::Matrix3d::Identity()*1;
    Eigen::Matrix3d aVarIMUIni = Eigen::Matrix3d::Identity()*0.1;
    Eigen::Vector3d wBiasIMUIni;
    wBiasIMUIni << 0,0,0;
    Eigen::Vector3d aBiasIMUIni;
    aBiasIMUIni << 0.1,0,0;
    double samplingTimeIMUIni = 0;
    // Create IMU
    IMU IMUsensor(aVarIMUIni, wVarIMUIni, aVarIMUIni, wVarIMUIni, aBiasIMUIni, wBiasIMUIni, samplingTimeIMUIni);
    // IMU measurement
    Eigen::Matrix<double, 6, 1> IMUmeasurement;

    // Create initial values for CAM
    std::cout << "Initianting CAM" << std::endl;
    Eigen::Matrix3d pVarCAMIni = Eigen::Matrix3d::Identity()*0.1;
    Eigen::Matrix4d qVarCAMIni = Eigen::Matrix4d::Identity()*0.1;
    double samplingTimeCAMIni = 0;
    // Create CAM
    CAM CAMsensor(pVarCAMIni,qVarCAMIni,samplingTimeCAMIni,20.0e-3);
    // CAM measurement
    Eigen::Matrix<double, 7, 1> CAMmeasurement;

    // Create initial values for EKF
    std::cout << "Initianting EKF" << std::endl;
    Eigen::Matrix<double, 16, 1>  initialEKFx = Eigen::Matrix<double, 16, 1>::Zero(16,1);
    double anEKFVar = 1;
    double wnEKFVar = 2;
    double awEKFVar = 1;
    double wwEKFVar = 2;
    double EKFdt = 0.1;
    double pnEKFVar = 0.1;
    double qnEKFVar = 0.1;
    initialEKFx(6) = 1;
    // Create EKF
    KF EKF(initialEKFx, anEKFVar, wnEKFVar, awEKFVar, wwEKFVar, pnEKFVar, qnEKFVar, EKFdt);
    EKF.getInfo();

    // Commands
    Eigen::Vector3d aCmd;
    aCmd << 0.1, 0.2, 10;
    Eigen::Vector3d wCmd;
    wCmd << 0, 0, 0.4;

    // Time steps
    double dt = 0.001;
    // Total simulation time
    double simTimeEnd = 1;
    // Number of simulation iterations
    int numPoints = (int) simTimeEnd/dt;
    // Current simulation time
    double simTime = 0;
    std::cout << "Num of steps: " << numPoints << std::endl;

    std::cout << "Interation: " << 1 << std::endl;
    // Update RWSW
    std::cout << "Updating RWSW..." << std::endl;
    RWSW.updateX(aCmd,wCmd,dt);

    // Measurement of IMU
    IMUsensor.updateClock(dt);
    if(IMUsensor.checkTimeout()) {
        // If the measurement exists:
        // Get measurement at the current time
        std::cout << "Getting IMU measurement..." << std::endl;
        IMUmeasurement = IMUsensor.getMeasurement(aCmd,wCmd);
        // Update Fx matrix
        EKF.updatedFx(IMUmeasurement.block<3,1>(0,0),IMUmeasurement.block<3,1>(3,0),dt);
        // Execute ESKF prediction step, updating the error;
        EKF.predictError();
    }
    else {
        // if there is no new measurement
        IMUmeasurement = IMUsensor.getLastMeasurement();
    }
    std::cout << "Saving IMU telemetry" << std::endl;

    // Measurement of CAM
    CAMsensor.updateClock(dt);
    if(CAMsensor.checkTimeoutSampling()) {
        std::cout << "Getting CAM measurement..." << std::endl;
        //CAMmeasurement = CAMsensor.getMeasurement(RWSW.getPosition(),RWSW.getOrientation());
        EKF.updatedH(CAMmeasurement.block<4,1>(3,0));
        //EKF.updateCAM(CAMmeasurement.block<3,1>(0,0), CAMmeasurement.block<4,1>(3,0),EKF.getX());
    }
    else {
        CAMmeasurement = CAMsensor.getLastMeasurement();
    }
    std::cout << "Saving CAM telemetry" << std::endl;
    EKF.errorInjection();
    return 0;
}

int testEKF() {
    // INITIALIZATION
    // Init RWSW
    std::cout << "Initianting test EKF!" << std::endl;
    Eigen::Vector3d pRWSWIni = Eigen::Vector3d::Zero(3,1);
    Eigen::Vector3d vRWSWIni;
    vRWSWIni << 0,0,0;
    Eigen::Vector4d qRWSWIni;
    qRWSWIni << 1,0,0,0;
    Eigen::Vector3d abRWSWIni;

    abRWSWIni << 1.0e-3 ,-2.0e-3, 1.0e-3;
    Eigen::Vector3d wbRWSWIni;

    wbRWSWIni << 2.8e-5,1.0e-3,-5.0e-5;
    RW RWSW(pRWSWIni, vRWSWIni, qRWSWIni, abRWSWIni, wbRWSWIni);

    // Create initial values for IMU
    std::cout << "Initianting IMU" << std::endl;

    double wVarIMU = 7.47e-7; //(rad/s)^2
    double aVarIMU = 3.43e-6;
    double wBiasVarIMU = wVarIMU*1e-3;
    double aBiasVarIMU = aVarIMU*1e-3;
    Eigen::Matrix3d wVarIMUIni = Eigen::Matrix3d::Identity()*wVarIMU;
    Eigen::Matrix3d aVarIMUIni = Eigen::Matrix3d::Identity()*aVarIMU;
    Eigen::Matrix3d wBiasVarIMUIni = Eigen::Matrix3d::Identity()*wBiasVarIMU;
    Eigen::Matrix3d aBiasVarIMUIni = Eigen::Matrix3d::Identity()*aBiasVarIMU;
    Eigen::Vector3d wBiasIMUIni;
    wBiasIMUIni = wbRWSWIni;
    Eigen::Vector3d aBiasIMUIni;
    aBiasIMUIni = abRWSWIni;
    double samplingTimeIMUIni = 0.001;//(1.0f/1666.0f); // In high-performance mode 1666Hz
    // Create IMU
    IMU IMUsensor(aVarIMUIni,wVarIMUIni,aBiasVarIMUIni,wBiasVarIMUIni,aBiasIMUIni,wBiasIMUIni, samplingTimeIMUIni);
    // IMU measurement
    Eigen::Matrix<double, 6, 1> IMUmeasurement;
    IMUsensor.detecting();

    // Create initial values for CAM
    std::cout << "Initianting CAM" << std::endl;
    double pVarCAM = 1;
    double qVarCAM = 7.61e-10;
    Eigen::Matrix3d pVarCAMIni = Eigen::Matrix3d::Identity()*pVarCAM;
    Eigen::Matrix4d qVarCAMIni = Eigen::Matrix4d::Identity()*qVarCAM;
    double samplingTimeCAMIni = (1.0f/120.0f);
    // Create CAM
    double delayCAMIni = 50.0e-3;
    CAM CAMsensor(pVarCAMIni,qVarCAMIni,samplingTimeCAMIni,delayCAMIni);
    // CAM measurement
    Eigen::Matrix<double, 7, 1> CAMmeasurement;
    //CAMsensor.failing();
    CAMsensor.getInfo();


    // Create initial values for EKF
    std::cout << "Initianting EKF" << std::endl;
    Eigen::Matrix<double, 16, 1>  initialEKFx = Eigen::Matrix<double, 16, 1>::Zero(16,1);
    double anEKFVar = aVarIMU/(samplingTimeIMUIni*samplingTimeIMUIni); // an var: acceleration noise variance
    double wnEKFVar = wVarIMU/(samplingTimeIMUIni*samplingTimeIMUIni); // wn var: angular rate noise variance
    double awEKFVar = aBiasVarIMU/samplingTimeIMUIni; //aw var: acceleration bias variance (low value)
    double wwEKFVar = wBiasVarIMU/samplingTimeIMUIni; //ww var: acceleration bias variance (low value)

    double EKFdt = samplingTimeIMUIni;
    // Variances for V
    double pnEKFVar = pVarCAM;
    double qnEKFVar = qVarCAM;
    initialEKFx(6) = 1;
    initialEKFx(10) = 0;
    bool delayCorrection = 1;
    // Create EKF
    KF EKF(initialEKFx, anEKFVar, wnEKFVar, awEKFVar, wwEKFVar, pnEKFVar, qnEKFVar, EKFdt);
    EKF.getInfo();

    // Init System Command
    std::string filename = "commandsDelay.csv";
    SYSCMD systemCMD(filename);
    if (!systemCMD.isCommandEmpty()) {
        systemCMD.printCommands();
    } else {
        std::cerr << "Ops, some problem with commands.csv" << std::endl;
    }

    // Commands
    Eigen::Vector3d aCmd;
    aCmd << 0, 0, 0;
    Eigen::Vector3d wCmd;
    wCmd << 0, 0, 0;

    // Time steps
    double dt = 0.0001;
    // Total simulation time
    double simTimeEnd = 30;
    // Number of simulation iterations
    int numPoints = (int) (simTimeEnd/dt);
    // Current simulation time
    double simTime = 0;
    std::cout << "Num of steps: " << numPoints << std::endl;

    // Creating csv for results
    std::cout << "Creating .csv..." << std::endl;
    std::ofstream trueStatePPC;
    trueStatePPC << std::fixed << std::setprecision(10);
    trueStatePPC.open("trueStatePPC.csv");
    makeCollumsTrue(&trueStatePPC);
    saveTrueStates(&trueStatePPC,simTime,RWSW.getTrueState());

    std::ofstream errorStatePPC;
    errorStatePPC << std::fixed << std::setprecision(10);
    errorStatePPC.open("errorStatePPC.csv");
    makeCollumsError(&errorStatePPC);
    saveErrorStates(&errorStatePPC,simTime,EKF.getErrorState());

    std::ofstream errorStateDelayPPC;
    errorStateDelayPPC << std::fixed << std::setprecision(10);
    errorStateDelayPPC.open("errorStateDelayPPC.csv");
    makeCollumsError(&errorStateDelayPPC);
    saveErrorStates(&errorStateDelayPPC,simTime,EKF.getErrorState());

    std::ofstream statePPC;
    statePPC << std::fixed << std::setprecision(10);
    statePPC.open("statePPC.csv");
    makeCollumsStates(&statePPC);
    saveStates(&statePPC,simTime,EKF.getX());

    std::ofstream stateDelayPPC;
    stateDelayPPC << std::fixed << std::setprecision(10);
    stateDelayPPC.open("stateDelayPPC.csv");
    makeCollumsStates(&stateDelayPPC);
    saveStates(&stateDelayPPC,simTime,EKF.getX());

    std::ofstream IMUmeasPPC;
    IMUmeasPPC << std::fixed << std::setprecision(10);
    IMUmeasPPC.open("IMUmeasPPC.csv");
    makeCollumsIMU(&IMUmeasPPC);

    std::ofstream CAMmeasPPC;
    CAMmeasPPC << std::fixed << std::setprecision(10);
    CAMmeasPPC.open("CAMmeasPPC.csv");
    makeCollumsCAM(&CAMmeasPPC);

    std::ofstream CAMmeasDelayPPC;
    CAMmeasDelayPPC << std::fixed << std::setprecision(10);
    CAMmeasDelayPPC.open("CAMmeasDelayPPC.csv");
    makeCollumsCAM(&CAMmeasDelayPPC);

    std::ofstream covariancePPC;
    covariancePPC << std::fixed << std::setprecision(10);
    covariancePPC.open("covariancePPC.csv");
    makeCollumsCovariance(&covariancePPC);
    saveCovariance(&covariancePPC,simTime,EKF.getP());

    std::ofstream covarianceDelayPPC;
    covarianceDelayPPC << std::fixed << std::setprecision(10);
    covarianceDelayPPC.open("covarianceDelayPPC.csv");
    makeCollumsCovariance(&covarianceDelayPPC);
    saveCovariance(&covarianceDelayPPC,simTime,EKF.getP());

    std::ofstream timePredPPC;
    timePredPPC.open("timePredPPC.csv");
    makeCollumsCompTimePred(&timePredPPC);

    std::ofstream timeUpPPC;
    timeUpPPC.open("timeUpPPC.csv");
    makeCollumsCompTimeUp(&timeUpPPC);

    for(int i =0;i<numPoints;++i) {
        //std::cout << "Interation: " << i << std::endl;
        // Update RWSW
        //std::cout << "Updating RWSW..." << std::endl;
        RWSW.updateTime(dt);
        systemCMD.getCommand(RWSW.getTime());
        aCmd[0] = systemCMD.cmd.ax;
        aCmd[1] = systemCMD.cmd.ay;
        aCmd[2] = systemCMD.cmd.az;
        wCmd[0] = systemCMD.cmd.wx;
        wCmd[1] = systemCMD.cmd.wy;
        wCmd[2] = systemCMD.cmd.wz;
        RWSW.updateX(aCmd,wCmd,dt);
        saveTrueStates(&trueStatePPC,RWSW.getTime(),RWSW.getTrueState());
        if(i%1000 == 0) {
            std::cout << "Time " << RWSW.getTime() << std::endl;
        }
        // Measurement of IMU
        EKF.updateClock(dt);
        IMUsensor.updateClock(dt);
        CAMsensor.updateClock(dt);
        if(1) {
            if(IMUsensor.checkTimeout() && IMUsensor.isDetecting()) {
                // If the measurement exists:
                // Get measurement at the current time
                //std::cout << "Prediction step with IMU measurement..." << std::endl;
                IMUmeasurement = IMUsensor.getMeasurement(aCmd,wCmd);
                //std::cout << "IMU:\n"<< IMUmeasurement << std::endl;
                EKF.predictStep(IMUmeasurement.block<3,1>(0,0),IMUmeasurement.block<3,1>(3,0), RWSW.getTime(), EKFdt,&timePredPPC);
            }
            else {
                // if there is no new measurement
                //std::cout << "IMU measurement not available..." << std::endl;
                IMUmeasurement = IMUsensor.getLastMeasurement();
            }
            //std::cout << "Saving IMU telemetry" << std::endl;
            saveMeasIMU(&IMUmeasPPC,RWSW.getTime(),IMUmeasurement);

            // Measurement of CAM
            //CAMsensor.getInfo();
            if(CAMsensor.isDetecting() && CAMsensor.checkTimeoutSampling()) {
                //std::cout << "Camera sampling..." << std::endl;
                CAMsensor.samplingMeasurement(RWSW.getPosition(), RWSW.getOrientation(), RWSW.getTime());
            }
            if(CAMsensor.checkTimeoutDelay(RWSW.getTime())) {
                //std::cout << "Update Step..." << std::endl;
                MeasurementData CAMdata = CAMsensor.getMeasurement();
                saveMeasCAM(&CAMmeasPPC,RWSW.getTime(),CAMdata.meas);
                //saveErrorStates(&errorStatePPC,RWSW.getTime(),EKF.getErrorState());
                if(delayCorrection) {
                    EKF.updateCamWithDelayCorrection(CAMdata, RWSW.getTime() ,&errorStateDelayPPC,&stateDelayPPC,&covarianceDelayPPC,&CAMmeasDelayPPC,&timeUpPPC);
                }
                else {
                    EKF.updatedH(CAMdata.qMeas);
                    EKF.updateCAM(CAMdata.meas);
                    saveErrorStates(&errorStatePPC,RWSW.getTime(),EKF.getErrorState());
                    saveCovariance(&covariancePPC,RWSW.getTime(),EKF.getP());
                    EKF.errorInjection();
                    //saveStates(&statePPC,RWSW.getTime(),EKF.getX());
                    EKF.reset();
                }
            }
            else {
                //std::cout << "CAM measurement not available..." << std::endl;
                //CAMmeasurement = CAMsensor.getLastMeasurement();
            }
            //std::cout << "Saving CAM telemetry" << std::endl;
            saveStates(&statePPC,RWSW.getTime(),EKF.getX());
            saveCovariance(&covariancePPC,RWSW.getTime(),EKF.getP());
        }
    }
    RWSW.getInfo();
    trueStatePPC.close();
    return 0;
}