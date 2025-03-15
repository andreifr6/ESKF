//
// Created by andre on 16/05/2024.
//

#ifndef CAM_H
#define CAM_H
#include "Eigen/Dense"
#include <random>
#include <queue>

struct MeasurementData {
    Eigen::Matrix<double, 7, 1> meas;
    Eigen::Matrix<double, 3, 1> pMeas;
    Eigen::Matrix<double, 4, 1> qMeas;
    double timestamp;
    double delay;
};

typedef std::queue<MeasurementData> MeasurementQueue;

class CAM{
private:
    Eigen::Matrix3d pVar;
    Eigen::Matrix4d qVar;
    MeasurementData lastData;

    MeasurementQueue measurementBuffer;

    std::default_random_engine generator;
    bool validMeasurement;
    bool newMeasurementAvailable;
    double clock;
    double samplingTime;
    double delay;

public:
    CAM(Eigen::Matrix3d pVarIni, Eigen::Matrix4d qVarIni, double samplingTimeIni, double delayIni);
    void samplingMeasurement(Eigen::Vector3d pTrue,Eigen::Vector4d qTrue, double time);
    MeasurementData getMeasurement();
    Eigen::Matrix<double, 7, 1> getLastMeasurement();
    Eigen::Matrix3d getPvar();
    Eigen::Matrix4d getQvar();
    void getInfo();
    bool isDetecting();
    void detecting();
    void failing();
    void updateClock(double dt);
    bool checkTimeoutSampling();
    bool checkTimeoutDelay(double time);
};

#endif //CAM_H
