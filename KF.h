//
// Created by andre on 28/05/2024.
//

#ifndef KF_H
#define KF_H

#include "Eigen/Dense"
#include <vector>
#include <deque>
#include "CAM.h"

struct StateInfo {
    Eigen::Matrix<double, 16, 1> x; // Nominal States
    Eigen::Matrix<double, 6, 1> u; // Input states
    Eigen::Matrix<double,15,15> P; // Covariance matrix
    double timestamp;
    double dt;
};

typedef std::deque<StateInfo> StateBuffer;

class KF{
private:
    Eigen::Matrix<double, 16, 1> x; // Nominal States
    Eigen::Matrix<double, 15, 1> error; // Error States
    Eigen::Matrix<double, 6, 1> u; // Input states
    Eigen::Matrix<double, 12, 12> perturbations; // Perturbations
    Eigen::Matrix<double, 15, 15> Fx; // Jacobian of deterministic part of f
    Eigen::Matrix<double, 15, 12> Fi; // Jacobian of stochstic part of f
    Eigen::Matrix<double, 12, 12> Qi; // Process covariance matrix

    Eigen::Matrix<double, 7, 15> H; // Jacobian of h
    Eigen::Matrix<double, 7, 7> V; // Meas covariance matrix
    Eigen::Matrix<double,15,15> P; // Covariance matrix

    Eigen::Matrix<double,3,1> g;

    Eigen::Matrix<double,15,15> G; //Reset covariance matrix
    double clock;
    double samplingTime;

    StateBuffer stateBuffer;
    int bufferSize;
public:
    KF(Eigen::Matrix<double, 16, 1>  initial_x, double anVar, double wnVar, double awVar, double wwVar,double pVar, double qVar, double dt);
    Eigen::Matrix<double,15,15> updatedFx(Eigen::Vector3d am, Eigen::Vector3d wm, double dt);
    Eigen::Matrix<double,7,15> updatedH(Eigen::Vector4d q);
    Eigen::Matrix<double, 7, 1> computeh();
    void predictError();
    void predictState(const Eigen::Vector3d am, const Eigen::Vector3d wm, double dt);
    void predictStep(const Eigen::Vector3d am, const Eigen::Vector3d wm, double time, double dt, std::ofstream* timePPC);

    void updateCAM(Eigen::Matrix<double, 7, 1> meas);
    void updateCamWithDelayCorrection(MeasurementData CAMdata, double currentTime, std::ofstream* errorPPC,std::ofstream* statePPC,std::ofstream* covPPC,std::ofstream* camPPC, std::ofstream* timePPC);
    void errorInjection();
    void reset();

    Eigen::Matrix<double, 16, 1> getX();
    Eigen::Matrix<double, 15, 1> getErrorState();

    Eigen::Vector3d getPosition();
    Eigen::Vector3d getVelocity();
    Eigen::Vector4d getOrientation();
    Eigen::Vector3d getAccelerationBias();
    Eigen::Vector3d getAngularRateBias();
    Eigen::Vector3d getGravity();
    Eigen::Matrix<double,15,15> getP();
    void getInfo();
    void updateClock(double dt);
    bool checkTimeout();

    int findLastIndexBeforeTime(double aquisitionTime);
};

#endif //KF_H
