#include <iomanip>
#include <iostream>

float Y_Vs[] = {0.35f, 0.58f, 0.72f, 0.92f, 1.08f};
float X_v[] = {4.72e14, 5.26e14, 5.55e14, 5.99e14, 6.52e14};
constexpr int N = 5;

int main() {
    float sigmaX = 0.0f;
    float sigmaX2 = 0.0f;
    float sigmaY = 0.0f;
    float sigmaXY = 0.0f;

    for (int i = 0; i < N; ++i) {
        sigmaX += X_v[i];
        sigmaY += Y_Vs[i];

        sigmaX2 += (X_v[i]) * (X_v[i]);
        sigmaXY += (X_v[i]) * (Y_Vs[i]);
    }

    float a =
        ((N * sigmaXY) - (sigmaX * sigmaY)) / ((N * sigmaX2) - sigmaX * sigmaX);
    float b = ((sigmaY * sigmaX2) - (sigmaX * sigmaXY)) /
              ((N * sigmaX2) - sigmaX * sigmaX);

    std::cout << "SigmaX: " << sigmaX << "\n";
    std::cout << "SigmaY: " << sigmaY << "\n";
    std::cout << "SigmaX2: " << sigmaX2 << "\n";
    std::cout << "SigmaXY: " << sigmaXY << "\n\n";
    std::cout << "a: " << a << "\t";
    std::cout << "b: " << b << "\n";
}