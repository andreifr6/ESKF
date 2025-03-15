//
// Created by andre on 29/05/2024.
//

#include <iostream>
#include "RWSW.h"
#include "utils.h"

using namespace std;

RW::RW(Eigen::Vector3d pIni,Eigen::Vector3d vIni, Eigen::Vector4d qIni, Eigen::Vector3d abIni, Eigen::Vector3d wbIni)
{
   time = 0;
   x.block<3,1>(0,0) = pIni;
   x.block<3,1>(3,0) = vIni;
   x.block<4,1>(6,0) = qIni;
   x.block<3,1>(10,0) = abIni;
   x.block<3,1>(13,0) = wbIni;
   g << 0,0,-9.81;
}

void RW::updateTime(double dt) {
   time = time + dt;
}

void RW::updateX(Eigen::Vector3d aCmd, Eigen::Vector3d wCmd, double dt)
{
   Eigen::Vector3d p = getPosition();
   Eigen::Vector3d v = getVelocity();
   Eigen::Vector4d q = getOrientation();
   Eigen::Vector3d ab = getAccelerationBias();
   Eigen::Vector3d wb = getAngularRateBias();

   Eigen::Matrix3d R = q2R(q);
   //p = p + v*dt + 0.5*(R*(aCmd-ab) + g)*dt*dt;
   p = p + v*dt + 0.5*(R*(aCmd) + g)*dt*dt;
   //v = v + (R*(aCmd-ab) + g)*dt;
   v = v + (R*(aCmd) + g)*dt;
   //q = qProduct(q,zerothOrderIntegration((wCmd-wb),dt));
   q = qProduct(q,zerothOrderIntegration((wCmd),dt));
   x.block<3,1>(0,0) = p;
   x.block<3,1>(3,0) = v;
   x.block<4,1>(6,0) = q;
}

Eigen::Matrix<double, 16, 1> RW::getTrueState()
{
   return x;
}

Eigen::Vector3d RW::getPosition()
{
   return x.block<3,1>(0,0);
}

Eigen::Vector3d RW::getVelocity()
{
   return x.block<3,1>(3,0);
}

Eigen::Vector4d RW::getOrientation()
{
   return x.block<4,1>(6,0);
}

Eigen::Vector3d RW::getAccelerationBias()
{
   return x.block<3,1>(10,0);
}

Eigen::Vector3d RW::getAngularRateBias()
{
   return x.block<3,1>(13,0);
}

Eigen::Vector3d RW::getGravity()
{
   return g;
}

double RW::getTime() {
   return time;
}

void RW::getInfo()
{
   cout << " True State:\n" << x << endl;
}