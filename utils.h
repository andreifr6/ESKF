//
// Created by andre on 16/05/2024.
//

#ifndef UTILS_H
#define UTILS_H
#include "Eigen/Dense"

Eigen::Matrix3d q2R(Eigen::Vector4d q, bool scalFirst = true);
Eigen::Matrix3d crossMatrix(Eigen::Vector3d a);
Eigen::Vector4d zerothOrderIntegration(Eigen::Vector3d angularRate, double dt,bool scalFirst = true, double tol=1e-12);
Eigen::Vector4d qProduct(Eigen::Vector4d p, Eigen::Vector4d q, bool scalFirst = true);
Eigen::Vector4d theta2q(Eigen::Vector3d theta, bool scalFirst = true, double tol=1e-12);
#endif //UTILS_H
