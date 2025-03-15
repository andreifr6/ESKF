//
// Created by andre on 11/09/2024.
//

#ifndef SYSCMD_H
#define SYSCMD_H

#include <vector>
#include <string>

class SYSCMD {
private:
    std::vector<double> deltaT;
    std::vector<double> ax;
    std::vector<double> ay;
    std::vector<double> az;
    std::vector<double> wx;
    std::vector<double> wy;
    std::vector<double> wz;
public:
    // Estrutura para armazenar o comando
    struct Cmd {
        double t;
        double ax;
        double ay;
        double az;
        double wx;
        double wy;
        double wz;
    };
    Cmd cmd;

    // Read CSV and populate command data
    SYSCMD(const std::string& filename);

    // get the command to be executed at time t
    void getCommand(double t);
    void printCommands();
    void printCommand();
    int isCommandEmpty();
};

#endif //SYSCMD_H
