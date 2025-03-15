//
// Created by andre on 11/09/2024.
//

#include "SYSCMD.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <chrono>
#include <thread>

// Construtor que lê o CSV e armazena os comandos
SYSCMD::SYSCMD(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file" << std::endl;
        return;
    }
    // Ignore the first line (header)
    std::getline(file, line);

    // Read each line of the file
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string deltaT_str, ax_str, ay_str, az_str, wx_str, wy_str, wz_str;

        // Extrair valores separados por ";"
        std::getline(ss, deltaT_str, ';');
        std::getline(ss, ax_str, ';');
        std::getline(ss, ay_str, ';');
        std::getline(ss, az_str, ';');
        std::getline(ss, wx_str, ';');
        std::getline(ss, wy_str, ';');
        std::getline(ss, wz_str, ';');

        // Processa deltaT (aceita 10pi como valor)
        double deltaT_value;
        if (deltaT_str.find("pi") != std::string::npos) {
            deltaT_str = deltaT_str.substr(0, deltaT_str.find("pi"));
            deltaT_value = std::stof(deltaT_str) * M_PI;
        } else {
            deltaT_value = std::stof(deltaT_str);
        }

        // Armazena os valores nos vetores
        deltaT.push_back(deltaT_value);
        ax.push_back(std::stof(ax_str));
        ay.push_back(std::stof(ay_str));
        az.push_back(std::stof(az_str));
        wx.push_back(std::stof(wx_str));
        wy.push_back(std::stof(wy_str));
        wz.push_back(std::stof(wz_str));
        cmd.t = 0;
        cmd.ax = ax[0];
        cmd.ay = ay[0];
        cmd.az = az[0];
        cmd.wx = wx[0];
        cmd.wy = wy[0];
        cmd.wz = wz[0];
    }
}

void SYSCMD::printCommands() {
    std::cout << "deltaT\tax\tay\taz\twx\twy\twz" << std::endl;
    for (size_t i = 0; i < deltaT.size(); ++i) {
        std::cout << deltaT[i] << '\t' << ax[i] << '\t' << ay[i] << '\t' << az[i] << '\t' << wx[i] << '\t' << wy[i] << '\t' << wz[i] << std::endl;
    }
}

// Função para simular a execução dos comandos ao longo do tempo
void SYSCMD::getCommand(double t){
    double time = 0;
    for (size_t i = 0; i < deltaT.size(); ++i) {
        if(t>time) {
            time = time + deltaT[i];
            cmd.t = t;
            cmd.ax = ax[i];
            cmd.ay = ay[i];
            cmd.az = az[i];
            cmd.wx = wx[i];
            cmd.wy = wy[i];
            cmd.wz = wz[i];
        }
    }
}

void SYSCMD::printCommand() {
    std::cout << "deltaT\tax\tay\taz\twx\twy\twz" << std::endl;
    std::cout << cmd.t << '\t' << cmd.ax << '\t' << cmd.ay << '\t' << cmd.az << '\t' << cmd.wx << '\t' << cmd.wy << '\t' << cmd.wz<< std::endl;
}

int SYSCMD::isCommandEmpty() {
    return deltaT.empty();
}