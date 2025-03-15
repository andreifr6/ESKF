//
// Created by andre on 29/05/2024.
//

#ifndef RWSW_H
#define RWSW_H
#include "Eigen/Dense"

class RW{
private:
    double time;
    Eigen::Matrix<double, 16, 1> x;
    Eigen::Vector3d g;

public:
    RW(Eigen::Vector3d pIni,Eigen::Vector3d vIni, Eigen::Vector4d qIni, Eigen::Vector3d abIni, Eigen::Vector3d wbIni);
    // You should update time, get the new commands, and then update X
    void updateTime(double dt);
    void updateX(Eigen::Vector3d aCmd, Eigen::Vector3d wCmd, double dt);
    Eigen::Matrix<double, 16, 1> getTrueState();
    Eigen::Vector3d getPosition();
    Eigen::Vector3d getVelocity();
    Eigen::Vector4d getOrientation();
    Eigen::Vector3d getAccelerationBias();
    Eigen::Vector3d getAngularRateBias();
    Eigen::Vector3d getGravity();
    double getTime();
    void getInfo();
};
#endif //RWSW_H
