//
// Created by andre on 16/05/2024.
//

#include "utils.h"
#include <iostream>

Eigen::Matrix3d q2R(Eigen::Vector4d q, bool scalFirst)
{
    double qw, qx, qy, qz;
    if(scalFirst) {
        qw = q(0);
        qx = q(1);
        qy = q(2);
        qz = q(3);
    }
    else {
        qw = q(3);
        qx = q(0);
        qy = q(1);
        qz = q(2);
    }
    Eigen::Matrix3d R;
    R << qw*qw + qx*qx - qy*qy - qz*qz, 2*(qx*qy - qw*qz),             2*(qx*qz + qw*qy),
     2*(qx*qy + qw*qz),                 qw*qw - qx*qx + qy*qy - qz*qz, 2*(qy*qz - qw*qx),
     2*(qx*qz - qw*qy),                 2*(qy*qz + qw*qx),           qw*qw - qx*qx - qy*qy + qz*qz;
    return R;
}

Eigen::Matrix3d crossMatrix(Eigen::Vector3d a)
{
    double ax, ay, az;
    ax = a(0);
    ay = a(1);
    az = a(2);
    Eigen::Matrix3d X;
    X << 0, -az, ay, az, 0, -ax, -ay, ax, 0;
    return X;
}

Eigen::Vector4d zerothOrderIntegration(Eigen::Vector3d angularRate, double dt, bool scalFirst,double tol)
{
    Eigen::Vector4d q;
    double angularRateNorm = angularRate.norm();
    if(angularRateNorm<tol) {
        Eigen::Vector3d qv;
        qv << 0,0,0;
        double qw = 1;
        if(scalFirst) {
            q(0) = qw;
            q.block<3,1>(1,0) = qv;
        }
        else {
            q.block<3,1>(0,0) = qv;
            q(3) = qw;
        }
        return q;
        //std::cout << angularRateNorm << std::endl;
        //throw std::runtime_error("zerothOrderIntegration: Norma menor que a tolerância!");
    }
    Eigen::Vector3d qv= (angularRate/angularRateNorm)*sin(angularRateNorm*dt/2);
    double qw = cos(angularRateNorm*dt/2);
    if(scalFirst) {
        q(0) = qw;
        q.block<3,1>(1,0) = qv;
    }
    else {
        q.block<3,1>(0,0) = qv;
        q(3) = qw;
    }
    q = q.normalized();
    return q;
}

Eigen::Vector4d qProduct(Eigen::Vector4d p, Eigen::Vector4d q, bool scalFirst){
    double pw,qw,resw;
    Eigen::Vector3d pv, qv, resv;
    if(scalFirst) {
        pw = p(0);
        qw = q(0);
        pv = p.block<3,1>(1,0);
        qv = q.block<3,1>(1,0);
    }
    else {
        pv = p.block<3,1>(0,0);
        qv = q.block<3,1>(0,0);
        pw = p(3);
        qw = q(3);
    }
    resw = pw*qw - pv.dot(qv);
    resv = pw*qv + qw*pv + pv.cross(qv);
    Eigen::Vector4d res;
    if(scalFirst) {
        res(0) = resw;
        res.block<3,1>(1,0) = resv;
    }
    else {
        res.block<3,1>(0,0) = resv;
        res(3) = resw;
    }
    res = res.normalized();
    return res;
}

Eigen::Vector4d theta2q(Eigen::Vector3d theta, bool scalFirst, double tol){
    double thetaNorm = theta.norm();
    if(thetaNorm<tol) {
        std::cout << thetaNorm << std::endl;
        throw std::runtime_error("Norma menor que a tolerancia!");
    }
    Eigen::Vector4d q;
    Eigen::Vector3d qv= (theta/thetaNorm)*sin(thetaNorm/2);
    double qw = cos(thetaNorm/2);
    if(scalFirst) {
        q(0) = qw;
        q.block<3,1>(1,0) = qv;
    }
    else {
        q.block<3,1>(0,0) = qv;
        q(3) = qw;
    }
    q = q.normalized();
    return q;
}