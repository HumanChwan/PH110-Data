#include <cmath>
#include <iomanip>
#include <iostream>

#include "Data.hpp"

float Data::sumTime = 10.0f * (15.0f * 31.0f);
float Data::sumSquareTime = 100.0f * (5.0f * 31.0f * 61.0f);
float Data::denom = N * sumSquareTime - (sumTime * sumTime);
int Data::N = 31;

int main() {
    freopen("phdataexp1.txt", "r", stdin);
    freopen("logs.txt", "w", stdout);
    int t;
    float iD, iC, iLogD, iLogC;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "S.No\tTime\tCharging\tLog(charging)\tDischarging\tLog("
                 "discharging)\n";

    Data charging, discharging;

    for (int i = 0; i < Data::N; ++i) {
        std::cin >> t >> iD >> iC;
        iLogC = log(iC);
        iLogD = log(iD);

        charging.increment_sigma_ln_I(iLogC);
        discharging.increment_sigma_ln_I(iLogD);

        charging.increment_sigma_ln_I_T(iLogC * t);
        discharging.increment_sigma_ln_I_T(iLogD * t);

        std::cout << (i + 1) << "\t\t" << t << "\t\t" << iC << "\t\t" << iLogC
                  << "\t\t\t" << iD << "\t\t" << iLogD << "\n";
    }

    charging.calculate();
    discharging.calculate();

    std::cout << std::setprecision(3);

    std::cout << "\nCharging:\t\t";
    charging.print();

    std::cout << "Discharging:\t";
    discharging.print();
    return 0;
}