//
// Created by andre on 29/05/2024.
//

#ifndef PPC_H
#define PPC_H
#include "Eigen/Dense"
void makeCollumsTrue(std::ofstream* results);
void makeCollumsError(std::ofstream* results);
void makeCollumsStates(std::ofstream* results);
void makeCollumsIMU(std::ofstream* results);
void makeCollumsCAM(std::ofstream* results);
void makeCollumsCovariance(std::ofstream* results);
void makeCollumsCompTimePred(std::ofstream* results);
void makeCollumsCompTimeUp(std::ofstream* results);


void saveTrueStates(std::ofstream* results, double current_time,Eigen::Matrix<double, 16, 1> xTrue) ;
void saveErrorStates(std::ofstream* results, double current_time,Eigen::Matrix<double, 15, 1> errorPredict);
void saveStates(std::ofstream* results, double current_time,Eigen::Matrix<double, 16, 1> x);
void saveMeasIMU(std::ofstream* results, double current_time, Eigen::Matrix<double, 6, 1> IMUmeas);
void saveMeasCAM(std::ofstream* results, double current_time, Eigen::Matrix<double, 7, 1> CAMmeas);
void saveCovariance(std::ofstream* results, double current_time,Eigen::Matrix<double, 15, 15> P);
void saveMeasCompTimePred(std::ofstream* results, double current_time, double Fxtime, double predXtime, double predPtime);
void saveMeasCompTimeUp(std::ofstream* results, double current_time, double Htime, double update_time, double inject_time, double reset_time, double recovery_time, double repropagate_time, double erase_time);

#endif //PPC_H
