//
// Created by andre on 16/05/2024.
//
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "CAM.h"

#include "utils.h"

using namespace std;

CAM::CAM(Eigen::Matrix3d pVarIni, Eigen::Matrix4d qVarIni, double samplingTimeIni, double delayIni)
{
    lastData.pMeas << 0,0,0;
    lastData.qMeas << 1,0,0,0;
    lastData.meas.block<3,1>(0,0) = lastData.pMeas;
    lastData.meas.block<4,1>(3,0) = lastData.qMeas;
    clock = 0;
    samplingTime = samplingTimeIni;
    pVar = pVarIni;
    qVar = qVarIni;
    validMeasurement = true;
    delay = delayIni;
}

void CAM::samplingMeasurement(Eigen::Vector3d pTrue, Eigen::Vector4d qTrue, double time) {
    MeasurementData newData;

    Eigen::Vector3d pNoise;
    for (int i = 0; i < 3; i++) {
        std::normal_distribution<double> normal_distribution(0, sqrt(pVar(i, i)));
        pNoise(i) = normal_distribution(generator);
    }
    Eigen::Vector4d qNoise;
    qNoise(0)=1;
    for (int i = 1; i < 4; i++) {
        std::normal_distribution<double> normal_distribution(0, sqrt(qVar(i, i)));
        qNoise(i) = 0.5*normal_distribution(generator);
    }

    newData.pMeas = pTrue + pNoise;
    qNoise = qNoise.normalized();
    newData.qMeas = qProduct(qTrue,qNoise);
    newData.qMeas = newData.qMeas.normalized();
    newData.meas.block<3, 1>(0, 0) = newData.pMeas;
    newData.meas.block<4, 1>(3, 0) = newData.qMeas;
    newData.timestamp = time;
    newData.delay = delay;
    measurementBuffer.push(newData);
    // Print meas
    //std::cout << meas << std::endl;
}
/*
Eigen::Matrix<double, 7, 1> CAM::getMeasurement(Eigen::Vector3d pTrue,Eigen::Vector4d qTrue)
{
    if(validMeasurement)
    {
        Eigen::Vector3d pNoise;
        for(int i =0;i<3;i++) {
            std::normal_distribution<double> normal_distribution(0,sqrt(pVar(i,i)));
            pNoise(i) = normal_distribution(generator);
        }

        Eigen::Vector3d thetaNoise;
        for(int i =0;i<2;i++) {
            std::normal_distribution<double> normal_distribution(0,sqrt(qVar(i,i)));
            thetaNoise(i) = normal_distribution(generator);
        }

        Eigen::Vector4d qNoise;
        */
        /*
        for(int i =0;i<4;i++) {
            std::normal_distribution<double> normal_distribution(0,sqrt(qVar(i,i)));
            qNoise(i) = normal_distribution(generator);
        }
        */
        /*
        pMeas = pTrue + pNoise;
        qNoise = theta2q(thetaNoise);
        qMeas = qProduct(qTrue,qNoise);
        qMeas = qMeas.normalized();
        meas.block<3,1>(0,0) = pMeas;
        meas.block<4,1>(3,0) = qMeas;

        // Print meas
        //std::cout << meas << std::endl;
        return meas;
    }
    else {
        return meas;
    }
}
*/

MeasurementData CAM::getMeasurement() {
    lastData = measurementBuffer.front();
    measurementBuffer.pop();
    return lastData;
}

Eigen::Matrix<double, 7, 1> CAM::getLastMeasurement() {
    return lastData.meas;
}

Eigen::Matrix3d CAM::getPvar()
{
    return pVar;
}

Eigen::Matrix4d CAM::getQvar()
{
    return qVar;
}

void CAM::getInfo()
{
    cout << "Last measurements:\n"
         << lastData.meas << endl;
    cout << "Paremeters:\n"
         << "Position variance: " << pVar << endl
         << "Orientation variance: " << qVar << endl
         << "Sampling Time: " << samplingTime << endl
         << "Clck: " << clock  << endl;
}

bool CAM::isDetecting()
{
    return validMeasurement;
}

void CAM::detecting()
{
    validMeasurement = true;
}

void CAM::failing()
{
    validMeasurement = false;
}

void CAM::updateClock(double dt)
{
    clock = clock + dt;
}

bool CAM::checkTimeoutSampling() {
    if (clock >= samplingTime) {
        clock = clock - samplingTime;
        if(validMeasurement) {
            return true;
        }
    }
    return false;
}

bool CAM::checkTimeoutDelay(double time) {
    if (!measurementBuffer.empty()) {
        if (time >= measurementBuffer.front().timestamp + measurementBuffer.front().delay) {
            //std::cout << "\tTime Now: " << time << std::endl;
            //std::cout << "\tAquisition Time: " << measurementBuffer.front().timestamp << std::endl;
            //std::cout << "\tUpdate Time: " << measurementBuffer.front().timestamp + measurementBuffer.front().delay << std::endl;
            return true;
        }
    }
    return false;
}