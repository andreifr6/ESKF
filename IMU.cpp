//
// Created by andre on 16/05/2024.
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "IMU.h"
#include "utils.h"

using namespace std;
// Meas: [a,w]^T

IMU::IMU(Eigen::Matrix3d aVarIni, Eigen::Matrix3d wVarIni, Eigen::Matrix3d aBiasVarIni, Eigen::Matrix3d wBiasVarIni, Eigen::Vector3d aBiasIni, Eigen::Vector3d wBiasIni, double samplingTimeIni)
{
    aMeas << 0,0,0;
    wMeas << 0,0,0;

    aVar = aVarIni;
    wVar = wVarIni;

    aBias = aBiasIni;
    wBias = wBiasIni;

    aBiasVar = aBiasVarIni;
    wBiasVar = wBiasVarIni;

    samplingTime = samplingTimeIni;
    clock = 0;
    validMeasurement = true;
}

Eigen::VectorXd IMU::getMeasurement(Eigen::Vector3d aCmd, Eigen::Vector3d wCmd)
{
    // aCMD in BODY
    Eigen::Vector3d aNoise;
    for(int i = 0;i<3;i++) {
        std::normal_distribution<double> normal_distribution(0,sqrt(aVar(i,i)));
        aNoise(i) = normal_distribution(generator);
    }
    Eigen::Vector3d wNoise;
    for(int i = 0;i<3;i++) {
        std::normal_distribution<double> normal_distribution(0,sqrt(wVar(i,i)));
        wNoise(i) = normal_distribution(generator);
    }

    Eigen::Vector3d aBiasNoise;
    for(int i = 0;i<3;i++) {
        std::normal_distribution<double> normal_distribution(0,sqrt(aBiasVar(i,i)));
        aBiasNoise(i) = normal_distribution(generator);
    }
    Eigen::Vector3d wBiasNoise;
    for(int i = 0;i<3;i++) {
        std::normal_distribution<double> normal_distribution(0,sqrt(wBiasVar(i,i)));
        wBiasNoise(i) = normal_distribution(generator);
    }

    aMeas = aCmd + aBias + aNoise;
    wMeas = wCmd + wBias + wNoise;

    aBias = aBias + aBiasNoise*samplingTime;
    wBias = wBias + wBiasNoise*samplingTime;

    Eigen::VectorXd measurement(6);
    measurement.block<3,1>(0,0) = aMeas;
    measurement.block<3,1>(3,0) = wMeas;
    return measurement;
}

Eigen::VectorXd IMU::getLastMeasurement()
{
    Eigen::VectorXd measurement(6);
    measurement.block<3,1>(0,0) = aMeas;
    measurement.block<3,1>(3,0) = wMeas;
    return measurement;
}

Eigen::Matrix3d IMU::getWVar()
{
    return wVar;
}

Eigen::Matrix3d IMU::getAVar()
{
    return aVar;
}

void IMU::getInfo()
{
    cout << "Last measurements:\n"
         << wMeas << endl
         << aMeas << endl;
    cout << "Paremeters:\n"
         << "Angular Velocity variance:\n" << wVar << endl
         << "Acceleration bias:\n" << wBias << endl
         << "Acceleration variance:\n" << aVar << endl
         << "Acceleration bias:\n" <<aBias << endl;
}

bool IMU::isDetecting()
{
    return validMeasurement;
}

void IMU::detecting()
{
    validMeasurement = true;
}

void IMU::failing()
{
    validMeasurement = false;
}

void IMU::updateClock(double dt)
{
    clock = clock + dt;
}

bool IMU::checkTimeout()
{
    if(clock>=samplingTime)
    {
        clock = clock - samplingTime;
        return true;
    }
    return false;

}