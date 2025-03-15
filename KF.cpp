//
// Created by andre on 28/05/2024.
//

#include <iostream>
#include "KF.h"
#include "utils.h"
#include "PPC.h"
#include <chrono>
using namespace std;

KF::KF(Eigen::Matrix<double, 16, 1>  initial_x, double anVar, double wnVar, double awVar, double wwVar, double pVar, double qVar, double dt)
{
    x = initial_x;
    g << 0, 0, -9.81;
    // State to state variables
    clock = 0;
    samplingTime = dt;
    error = Eigen::Matrix<double,15,1>::Ones(15,1);// Can not be zero
    u = Eigen::Matrix<double,6,1>::Zero(6,1);

    // Contructing Fx (it depends on states)
    Fx = Eigen::Matrix<double,15,15>::Zero(15,15);

    // Construct Fi (it is constant)
    Fi = Eigen::Matrix<double, 15, 12>::Zero();
    Fi.block<3,3>(3,0) = Eigen::Matrix3d::Identity();
    Fi.block<3,3>(6,3) = Eigen::Matrix3d::Identity();
    Fi.block<3,3>(9,6) = Eigen::Matrix3d::Identity();
    Fi.block<3,3>(12,9) = Eigen::Matrix3d::Identity();

    // Construct Qi (it is constant)
    Eigen::Matrix3d AnIntegratedVar = anVar*dt*dt*Eigen::Matrix3d::Identity();
    Eigen::Matrix3d WnIntegratedVar = wnVar*dt*dt*Eigen::Matrix3d::Identity();
    Eigen::Matrix3d AwIntegratedVar = awVar*dt*Eigen::Matrix3d::Identity();
    Eigen::Matrix3d WwIntegratedVar = wwVar*dt*Eigen::Matrix3d::Identity();
    Qi = Eigen::Matrix<double,12,12>::Zero(12,12);
    Qi.block<3,3>(0,0) = AnIntegratedVar;
    Qi.block<3,3>(3,3) = WnIntegratedVar;
    Qi.block<3,3>(6,6) = AwIntegratedVar;
    Qi.block<3,3>(9,9) = WwIntegratedVar;

    V = Eigen::Matrix<double,7,7>::Zero(7,7);
    V.block<3,3>(0,0) = pVar*Eigen::Matrix3d::Identity();
    V.block<4,4>(3,3) = qVar*Eigen::Matrix4d::Identity()/4;

    // Contruct P
    P = Eigen::Matrix<double,15,15>::Ones();

    P(9,9) = 100;
    P(10,10) = 100;
    P(11,11) = 100;
    P(12,12) = 100;
    P(13,13) = 100;
    P(14,14) = 100;

    G = Eigen::Matrix<double,15,15>::Identity(15,15);
}

Eigen::Matrix<double,15,15> KF::updatedFx(const Eigen::Vector3d am, const Eigen::Vector3d wm, double dt) {
    Eigen::Vector4d q = x.block<4,1>(6,0);
    Eigen::Vector3d ab = x.block<3,1>(10,0);
    Eigen::Vector3d wb = x.block<3,1>(13,0);
    // Aux
    Eigen::Matrix3d R = q2R(q);
    Eigen::Matrix3d integrationR = q2R(zerothOrderIntegration((wm-wb),dt));

    // Contructing Fx
    // TODO: Otimizacao da atualizacao
    Fx = Eigen::Matrix<double,15,15>::Zero(15,15);
    Fx.block<3,3>(0,0) = Eigen::Matrix3d::Identity();
    Fx.block<3,3>(0,3) = Eigen::Matrix3d::Identity()*dt;
    Fx.block<3,3>(3,3) = Eigen::Matrix3d::Identity();
    Fx.block<3,3>(3,6) = -R*crossMatrix(am-ab)*dt;
    Fx.block<3,3>(3,9) = -R*dt;
    Fx.block<3,3>(6,6) = integrationR.transpose();
    Fx.block<3,3>(6,12) = - Eigen::Matrix3d::Identity()*dt;
    Fx.block<3,3>(9,9) = Eigen::Matrix3d::Identity();
    Fx.block<3,3>(12,12) = Eigen::Matrix3d::Identity();
    return Fx;
}

Eigen::Matrix<double,7,15> KF::updatedH(Eigen::Vector4d q)
{
    double qw = q(0);
    double qx = q(1);
    double qy = q(2);
    double qz = q(3);
    H = Eigen::Matrix<double,7,15>::Zero(7,15);
    Eigen::Matrix<double,4,3> QdeltaTheta;
    QdeltaTheta << -qx,-qy,-qz,
                    qw,-qz, qy,
                    qz, qw, -qx,
                    -qy, qx, qw;
    QdeltaTheta = 0.5*QdeltaTheta;

    H.block<3,3>(0,0) = Eigen::Matrix3d::Identity();
    H.block<4,3>(3,6) = QdeltaTheta;
    //std::cout << H << std::endl;
    return H;
}

Eigen::Matrix<double, 7, 1> KF::computeh() {
    Eigen::Matrix<double, 7, 16> h = Eigen::Matrix<double, 7, 16>::Zero();
    h.block<3,3>(0,0) = Eigen::Matrix3d::Identity();
    h.block<4,4>(3,6) = Eigen::Matrix4d::Identity();
    return h*x;
}

void KF::predictError()
{
    // dx = Fx*dx;
    // P = Fx*P*Fx^t + Fi*Qi*Fi^t
    // Eigen::Matrix<double,18,1> errorPred = Fx*error;


    Eigen::Matrix<double,15,15> PPred = Fx*P*Fx.transpose() + Fi*Qi*Fi.transpose();
    //error = errorPred;
    P = PPred;
}

void KF::predictState(const Eigen::Vector3d am, const Eigen::Vector3d wm, double dt)
{
    Eigen::Vector3d p = getPosition();
    Eigen::Vector3d v = getVelocity();
    Eigen::Vector4d q = getOrientation();
    Eigen::Vector3d ab = getAccelerationBias();
    Eigen::Vector3d wb = getAngularRateBias();

    Eigen::Matrix3d R = q2R(q);
    p = p + v*dt + 0.5*(R*(am-ab)+g)*dt*dt;
    v = v + (R*(am-ab)+g)*dt;
    q = qProduct(q,zerothOrderIntegration((wm-wb),dt));
    x.block<3,1>(0,0) = p;
    x.block<3,1>(3,0) = v;
    x.block<4,1>(6,0) = q;
}

void KF::predictStep(const Eigen::Vector3d am, const Eigen::Vector3d wm, double time, double dt, std::ofstream* timePPC) {
    auto tic = std::chrono::high_resolution_clock::now();
    auto toc = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedPredictState;
    std::chrono::duration<double> elapsedUpdateFx;
    std::chrono::duration<double> elapsedPredictError;

    StateInfo stateInfo;
    stateInfo.u.block<3,1>(0,0) = am;
    stateInfo.u.block<3,1>(3,0) = wm;
    stateInfo.timestamp = time;
    stateInfo.dt = dt;

    tic = std::chrono::high_resolution_clock::now();
    this->predictState(am,wm,dt);
    toc = std::chrono::high_resolution_clock::now();
    elapsedPredictState = toc - tic;

    stateInfo.x = this->getX();
    tic = std::chrono::high_resolution_clock::now();
    this->updatedFx(am,wm,dt);
    toc = std::chrono::high_resolution_clock::now();
    elapsedUpdateFx = toc - tic;

    tic = std::chrono::high_resolution_clock::now();
    this->predictError();
    toc = std::chrono::high_resolution_clock::now();
    elapsedPredictError = toc - tic;

    saveMeasCompTimePred(timePPC,time,elapsedUpdateFx.count(),elapsedPredictState.count(),elapsedPredictError.count());

    stateInfo.P = this->getP();
    stateBuffer.push_back(stateInfo);
}

void KF::updateCamWithDelayCorrection(MeasurementData CAMdata, double currentTime ,std::ofstream* errorPPC,std::ofstream* statePPC,std::ofstream* covPPC,std::ofstream* camPPC, std::ofstream* timePPC) {
    auto tic = std::chrono::high_resolution_clock::now();
    auto toc = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedrecov(0);
    std::chrono::duration<double> elapsedH(0);
    std::chrono::duration<double> elapsedUp(0);
    std::chrono::duration<double> elapsedprop(0);
    std::chrono::duration<double> elapsedInj(0);
    std::chrono::duration<double> elapsedReset(0);
    std::chrono::duration<double> elapsedErase(0);

    saveMeasCAM(camPPC,CAMdata.timestamp,CAMdata.meas);
    tic = std::chrono::high_resolution_clock::now();
    int lastStateIndex = 0;
    double aquisitionTime = CAMdata.timestamp;

    //std::cout << "\tUpdate CAM with Delay Correction" << std::endl;
    //std::cout << "\tAquisition time: "<< aquisitionTime << std::endl;
    //std::cout << "\tBuffer Size: "<< stateBuffer.size() << std::endl;
    lastStateIndex = findLastIndexBeforeTime(aquisitionTime);
    /*
    for(int i=0;i<stateBuffer.size();i++) {
        if(stateBuffer[i].timestamp<=aquisitionTime) {
            //std::cout << "\t\tTimestamp of step: "<< stateBuffer[i].timestamp << std::endl;
            lastStateIndex = i;
        }
    }
    */
    x = stateBuffer[lastStateIndex].x;
    P = stateBuffer[lastStateIndex].P;
    u = stateBuffer[lastStateIndex].u;
    double time = stateBuffer[lastStateIndex].timestamp;
    toc = std::chrono::high_resolution_clock::now();
    elapsedrecov = toc - tic;

    saveCovariance(covPPC,time,P);
    saveStates(statePPC,time,x);

    tic = std::chrono::high_resolution_clock::now();
    updatedH(CAMdata.qMeas);
    toc = std::chrono::high_resolution_clock::now();
    elapsedH = toc - tic;

    tic = std::chrono::high_resolution_clock::now();
    updateCAM(CAMdata.meas);
    toc = std::chrono::high_resolution_clock::now();
    elapsedUp =toc - tic;

    saveErrorStates(errorPPC,time,error);
    saveCovariance(covPPC,time,P);

    tic = std::chrono::high_resolution_clock::now();
    errorInjection();
    toc = std::chrono::high_resolution_clock::now();
    elapsedInj = toc -tic;
    saveStates(statePPC,time,x);

    tic = std::chrono::high_resolution_clock::now();
    reset();
    toc = std::chrono::high_resolution_clock::now();
    elapsedReset = toc - tic;

    // Erase Buffer until the aquisition time
    //std::cout << "\tPropagate until current time: " << currentTime << std::endl;
    double dt = 0;
    Eigen::Vector3d am;
    Eigen::Vector3d wm;
    elapsedprop.zero();
    for(int i=lastStateIndex+1;i<stateBuffer.size();i++) {
        //std::cout << "\t\tTime of propagation: "<< stateBuffer[i].timestamp << std::endl;
        tic = std::chrono::high_resolution_clock::now();
        am = stateBuffer[i].u.block<3,1>(0,0);
        wm = stateBuffer[i].u.block<3,1>(3,0);
        dt = stateBuffer[i].dt;
        predictState(am,wm,dt);
        updatedFx(am,wm,dt);
        predictError();
        toc = std::chrono::high_resolution_clock::now();
        saveStates(statePPC,stateBuffer[i].timestamp,x);
        saveCovariance(covPPC,stateBuffer[i].timestamp,P);
        elapsedprop += toc - tic;
    }
    //std::cout << "\tErasing Buffer from: " << 0 << " until: " << lastStateIndex << std::endl;
    tic = std::chrono::high_resolution_clock::now();
    stateBuffer.erase(stateBuffer.begin(),stateBuffer.begin()+lastStateIndex);
    toc = std::chrono::high_resolution_clock::now();
    elapsedErase = toc - tic;
    //std::cout << "\tBuffer Size after erasing: "<< stateBuffer.size() << std::endl;
    saveMeasCompTimeUp(timePPC,CAMdata.timestamp,elapsedH.count(),elapsedUp.count(),elapsedInj.count(),elapsedReset.count(),elapsedrecov.count(),elapsedprop.count(),elapsedErase.count());
}

void KF::updateCAM(Eigen::Matrix<double, 7, 1> meas)
{
    /*
    // y = z - h(x)
    // S = H*P*H^t + R
    // K = P*H^t*S^-1
    // x = x+ K*y
    // P = (I - K*H)*P

    Eigen::MatrixXd H(19,18);
    Eigen::VectorXd z(1,1);
    Eigen::MatrixXd R(1,1);
    Eigen::VectorXd y(1,1);
    Eigen::MatrixXd S(1,1);

    z << meas;
    R << pos_var;
    y = z - H*x;
    S = H*P*H.transpose() + R;
    K = P*H.transpose()*S.inverse();

    Eigen::Vector3d new_x = x + K*y;
    Eigen::Matrix3d new_P = (Eigen::Matrix3d::Identity() - K*H)*P;

    x = new_x;
    P = new_P;
    */
    Eigen::Matrix<double, 7, 7> S = H*P*H.transpose()+V;
    //std::cout << "Matrix S:\n" << S << std::endl;
    //std::cout << "Matrix detS:\n" << S.determinant() << std::endl;
    Eigen::Matrix<double, 15, 7> K = P*H.transpose()*S.inverse();
    //std::cout << "Matrix HK:\n" << H*K << std::endl;
    error = K*(meas - computeh());
    //std::cout << "Matrix error:\n" << error << std::endl;
    P = (Eigen::MatrixXd::Identity(15,15)-K*H)*P;
    //std::cout << "Matrix P:\n" << P << std::endl;
}

void KF::errorInjection(){
    // Position error injection
    x.block<3,1>(0,0) += error.block<3,1>(0,0);
    // Velocity error injection
    x.block<3,1>(3,0) += error.block<3,1>(3,0);
    // Quaternion error injection
    x.block<4,1>(6,0) = qProduct(x.block<4,1>(6,0),theta2q(error.block<3,1>(6,0)));
    // Acceleration bias error injection
    x.block<3,1>(10,0) += error.block<3,1>(9,0);
    // Angular velocity bias error injection
    x.block<3,1>(13,0) += error.block<3,1>(12,0);
    //std::cout << x << std::endl;
}

void KF::reset(){
    // Reset error state
    //error = Eigen::Matrix<double,15,1>::Zero(15,1);
    G.block<3,3>(6,6) = Eigen::Matrix3d::Identity() + crossMatrix(0.5*error.block<3,1>(6,0));

    // P = G*P*G, G ~ I
    P = G*P*G.transpose();
}

Eigen::Matrix<double, 16, 1> KF::getX() {
    return x;
}

Eigen::Matrix<double, 15, 1> KF::getErrorState() {
    return error;
}

Eigen::Vector3d KF::getPosition()
{
    return x.block<3,1>(0,0);
}

Eigen::Vector3d KF::getVelocity()
{
    return x.block<3,1>(3,0);
}

Eigen::Vector4d KF::getOrientation()
{
    return x.block<4,1>(6,0);
}

Eigen::Vector3d KF::getAccelerationBias()
{
    return x.block<3,1>(10,0);
}

Eigen::Vector3d KF::getAngularRateBias()
{
    return x.block<3,1>(13,0);
}

Eigen::Matrix<double,15,15> KF::getP()
{
    return P;
}

void KF::getInfo()
{
    cout << "State:\n" << x << endl;
    cout << "Error State:\n" << error << endl;
    cout << "Measurements:\n" << u << endl;
    cout << "Fx:\n" << Fx << endl;
    cout << "Fi:\n" << Fi << endl;
    cout << "Qi:\n" << Qi << endl;
    cout << "P:\n"  << P << endl;
}

void KF::updateClock(double dt)
{
    clock = clock + dt;
}

bool KF::checkTimeout()
{
    if(clock>samplingTime)
    {
        clock = 0;
        return true;
    }
    return false;

}

int KF::findLastIndexBeforeTime(double aquisitionTime) {
    // Usa upper_bound para encontrar o primeiro índice com timestamp >= aquisitionTime
    auto it = std::upper_bound(stateBuffer.begin(), stateBuffer.end(), aquisitionTime,
        [](double value, const StateInfo& state) { return value < state.timestamp; });

    // Se o iterador está no início, nenhum elemento satisfaz a condição timestamp < aquisitionTime
    if (it == stateBuffer.begin()) {
        return -1; // Nenhum elemento satisfaz a condição
    }

    // Caso contrário, retornamos o índice do elemento anterior ao encontrado
    return std::distance(stateBuffer.begin(), it) - 1;
}