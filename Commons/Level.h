#ifndef LEVEL_H
#define LEVEL_H

#include <string>

enum Level {
    ExtremlyEasy,
    Easy,
    Medium,
    Hard,
    Evil
};

struct Info {
    std::string name;
    unsigned int minTotalGiven;
    unsigned int maxTotalGiven;
    unsigned int minGivenRC;

    Info(std::string n, unsigned int miTG, unsigned int maTG, unsigned mGR) :
            name(n), minTotalGiven(miTG), maxTotalGiven(maTG), minGivenRC(mGR) {
    }
};

inline Info getInfo(Level l) {
    switch (l) {
        case ExtremlyEasy:
            return Info("Extremly Easy", 50, 75, 5);
        case Easy:
            return Info("Easy", 36, 39, 4);
        case Medium:
            return Info("Medium", 32, 35, 3);
        case Hard:
            return Info("Hard", 28, 31, 2);
        case Evil:
            return Info("Evil", 22, 27, 0);
    }
}

#endif // LEVEL_H
