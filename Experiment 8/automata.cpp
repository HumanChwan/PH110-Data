#include <iomanip>
#include <iostream>

constexpr int MONKE = 0;
constexpr int RINGS = 20;

struct data {
    int ring_no;

    int L_msr;
    int L_csr;
    float L_Tr;

    int R_msr;
    int R_csr;
    float R_Tr;

    float D, Pm, Pm2;

    void set(int a, int L_m, int L_c, int R_m, int R_c) {
        ring_no = a;
        L_msr = L_m;
        L_csr = L_c;
        L_Tr = (float)L_msr + 0.01f * (float)(L_csr);

        R_msr = R_m;
        R_csr = R_c;
        R_Tr = (float)R_msr + 0.01f * (float)(R_csr);

        D = std::abs(R_Tr - L_Tr);
        Pm = D / 2.0f;
        Pm2 = Pm * Pm;
    }
};

int main() {
    std::cout << "Hello World";
    std::cout << std::fixed << std::setprecision(2);
    data RingData[RINGS];
    for (int i = 0; i < RINGS; ++i) {
        int a, L_m, L_c, R_m, R_c;
        std::cin >> a >> L_m >> L_c >> R_m >> R_c;
        RingData[i].set(a, L_m, L_c, R_m, R_c);
    }

    std::cout << "m\t\tD\t\tPm=D/2\t\tPm^2\n";
    for (int i = 0; i < 55; ++i) std::cout << "-";
    std::cout << "\n";
    for (int i = 0; i < RINGS; ++i) {
        std::cout << RingData[i].ring_no << "\t\t" << RingData[i].D << "\t\t"
                  << RingData[i].Pm << "\t\t" << RingData[i].Pm2 << "\n";
    }

    std::cout << "\n";

    float sigmaX = 0.0f;
    float sigmaX2 = 0.0f;
    float sigmaY = 0.0f;
    float sigmaXY = 0.0f;

    for (int i = 0; i < RINGS; ++i) {
        sigmaX += RingData[i].ring_no;
        sigmaY += RingData[i].Pm2;

        sigmaX2 += (RingData[i].ring_no) * (RingData[i].ring_no);
        sigmaXY += (RingData[i].ring_no) * (RingData[i].Pm2);
    }

    float a = ((RINGS * sigmaXY) - (sigmaX * sigmaY)) /
              ((RINGS * sigmaX2) - sigmaX * sigmaX);
    float b = ((sigmaY * sigmaX2) - (sigmaX * sigmaXY)) /
              ((RINGS * sigmaX2) - sigmaX * sigmaX);

    std::cout << "\tSigmaX: " << sigmaX << "\n";
    std::cout << "\tSigmaY: " << sigmaY << "\n";
    std::cout << "\tSigmaX2: " << sigmaX2 << "\n";
    std::cout << "\tSigmaXY: " << sigmaXY << "\n\n";

    std::cout << "\ta: " << a << "\t";
    std::cout << "\tb: " << b << "\n";

    constexpr float WAVELENGTH = 5.893e-4;

    std::cout << "\tRadius of curvature: " << a / (WAVELENGTH * 1e3f);
    std::cout << std::endl;
    return MONKE;
}
