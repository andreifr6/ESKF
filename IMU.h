//
// Created by andre on 16/05/2024.
//

#ifndef IMU_H
#define IMU_H
#include "Eigen/Dense"
#include <random>

class IMU{
private:
    Eigen::Vector3d aMeas;
    Eigen::Vector3d wMeas;
    Eigen::Matrix3d aVar;
    Eigen::Matrix3d wVar;
    Eigen::Vector3d aBias;
    Eigen::Vector3d wBias;
    Eigen::Matrix3d aBiasVar;
    Eigen::Matrix3d wBiasVar;
    std::default_random_engine generator;
    bool validMeasurement;
    double clock;
    double samplingTime;

public:
    IMU(Eigen::Matrix3d aVarIni, Eigen::Matrix3d wVarIni,Eigen::Matrix3d aBiasVarIni, Eigen::Matrix3d wBiasVarIni, Eigen::Vector3d aBiasIni, Eigen::Vector3d wBiasIni, double samplingTimeIni);
    Eigen::VectorXd getMeasurement(Eigen::Vector3d aTrue, Eigen::Vector3d wTrue);
    Eigen::VectorXd getLastMeasurement();

    Eigen::Matrix3d getAVar();
    Eigen::Matrix3d getWVar();

    void getInfo();

    bool isDetecting();
    void detecting();
    void failing();
    void updateClock(double dt);
    bool checkTimeout();
};
#endif //IMU_H
