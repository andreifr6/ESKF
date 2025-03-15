//
// Created by andre on 29/05/2024.
//

#include "PPC.h"
#include <iostream>
#include <fstream>

void makeCollumsCovariance(std::ofstream* results) {
    *results << "t;P0;P1;P2;P3;P4;P5;P6;P7;P8;P9;P10;P11;P12;P13;P14\n";
}

void saveCovariance(std::ofstream* results, double current_time,Eigen::Matrix<double, 15, 15> P) {
    *results << current_time << ";";
    for(int i =0;i<14;i++) {
        *results << P(i,i) << ";";
    }
    *results << P(14,14) << "\n";
}

void makeCollumsTrue(std::ofstream* results) {
    *results << "t;p1;p2;p3;v1;v2;v3;q1;q2;q3;q4;ab1;ab2;ab3;wb1;wb2;wb3\n";
}

void saveTrueStates(std::ofstream* results, double current_time,Eigen::Matrix<double, 16, 1> xTrue) {
    *results << current_time << ";";
    for(int i =0;i<15;i++) {
        *results << xTrue(i) << ";";
    }
    *results << xTrue(15) << "\n";
}

void makeCollumsError(std::ofstream* results) {
    *results << "t;p1;p2;p3;v1;v2;v3;theta1;theta2;theta3;ab1;ab2;ab3;wb1;wb2;wb3\n";
}

void saveErrorStates(std::ofstream* results, double current_time,Eigen::Matrix<double, 15, 1> errorPredict) {
    *results << current_time << ";";
    for(int i =0;i<14;i++) {
        *results << errorPredict(i) << ";";
    }
    *results << errorPredict(14) << "\n";
}

void makeCollumsStates(std::ofstream* results) {
    *results << "t;p1;p2;p3;v1;v2;v3;q1;q2;q3;q4;ab1;ab2;ab3;wb1;wb2;wb3;\n";
}

void saveStates(std::ofstream* results, double current_time,Eigen::Matrix<double, 16, 1> x) {
    *results << current_time << ";";
    for(int i =0;i<15;i++) {
        *results << x(i) << ";";
    }
    *results << x(15) << "\n";
}

void makeCollumsIMU(std::ofstream* results) {
    *results << "t;a1;a2;a3;w1;w2;w3\n";
}

void saveMeasIMU(std::ofstream* results, double current_time, Eigen::Matrix<double, 6, 1> IMUmeas) {
    *results << current_time << ";";
    for(int i =0;i<5;i++) {
        *results << IMUmeas(i) << ";";
    }
    *results << IMUmeas(5) << "\n";
}

void makeCollumsCAM(std::ofstream* results) {
    *results << "t;p1;p2;p3;q1;q2;q3;q4\n";
}

void saveMeasCAM(std::ofstream* results, double current_time, Eigen::Matrix<double, 7, 1> CAMmeas) {
    *results << current_time << ";";
    for(int i =0;i<6;i++) {
        *results << CAMmeas(i) << ";";
    }
    *results << CAMmeas(6)<< "\n";
}

void makeCollumsCompTimePred(std::ofstream* results) {
    *results << "t;Fx;predX;predP\n";
}

void saveMeasCompTimePred(std::ofstream* results, double current_time, double Fxtime, double predXtime, double predPtime) {
    *results << current_time << ";";
    *results << Fxtime << ";";
    *results << predXtime << ";";
    *results << predPtime << "\n";
}

void makeCollumsCompTimeUp(std::ofstream* results) {
    *results << "t;H;up;inj;reset;recov;reprop;erase\n";
}

void saveMeasCompTimeUp(std::ofstream* results, double current_time, double Htime, double update_time, double inject_time, double reset_time, double recovery_time, double repropagate_time, double erase_time) {
    *results << current_time << ";";
    *results << Htime << ";";
    *results << update_time << ";";
    *results << inject_time << ";";
    *results << reset_time << ";";
    *results << recovery_time << ";";
    *results << repropagate_time << ";";
    *results << erase_time << "\n";
}