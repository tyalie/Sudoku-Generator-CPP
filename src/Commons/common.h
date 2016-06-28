#ifndef COMMON_H
#define COMMON_H


#include <cstring>
#include <math.h>
#include <iomanip>
#include <iostream>
#include <chrono>


#include "Level.h"

#define DIM_F 9
#define DIM_B (int)sqrt(DIM_F)
#define TOTAL (DIM_F*DIM_F)

#define NAF 0

#define printBool(b) (b?"TRUE":"FALSE")

inline void showMessage(std::string message) {
    using namespace std::chrono;
    milliseconds ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
    auto hh = ms;
    auto ss = (hh/=1000)%60;
    auto mm = (hh/=60)%60;
    hh= (hh/60)%24;

    std::cout << hh.count()<<":"<<mm.count()<<"-"<<ss.count()<<"."<<(ms.count()%1000)<<" :"<<message<<std::endl;
}

#endif // COMMON_H
