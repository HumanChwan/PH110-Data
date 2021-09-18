#include <iomanip>
#include <iostream>

constexpr int MONKE = 0;
constexpr int N = 9;

struct Reading {
    float d, t1, t2, t3;
    float tmean;

    float T;
    float d_2;
    float T_2d;

   private:
    void calc_mean() { tmean = (t1 + t2 + t3) / 3.0f; }

    void set_T() { T = tmean / 20.0f; }

    void set_d_2() { d_2 = d * d; }

    void set_T_2d() { T_2d = T * T * d; }

   public:
    void calc() {
        calc_mean();
        set_T();
        set_d_2();
        set_T_2d();
    }
};

struct pair {
    float a, b;
};

pair linear_regression(Reading set[]) {
    float sigmaX = 0.0f;
    float sigmaX2 = 0.0f;
    float sigmaY = 0.0f;
    float sigmaXY = 0.0f;

    for (int i = 0; i < N; ++i) {
        sigmaX += set[i].d_2;
        sigmaY += set[i].T_2d;

        sigmaX2 += (set[i].d_2) * (set[i].d_2);
        sigmaXY += (set[i].d_2) * (set[i].T_2d);
    }

    float a =
        ((N * sigmaXY) - (sigmaX * sigmaY)) / ((N * sigmaX2) - sigmaX * sigmaX);
    float b = ((sigmaY * sigmaX2) - (sigmaX * sigmaXY)) /
              ((N * sigmaX2) - sigmaX * sigmaX);

    pair result = {a, b};
    return result;
}

constexpr float L = 100.0f;
constexpr float B = 3.9f;
constexpr float PI = 3.14f;

int main() {
    freopen("data.txt", "r", stdin);
    freopen("log.txt", "w", stdout);

    Reading set[N];
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "t1\t\tt2\t\tt3\t\ttmean\t\tT\t\td\t\td^2\t\t\tT^2*d\n";
    for (int i = 0; i < N; ++i) {
        std::cin >> set[i].d >> set[i].t1 >> set[i].t2 >> set[i].t3;
        set[i].calc();

        std::cout << set[i].t1 << "\t" << set[i].t2 << "\t" << set[i].t3 << "\t"
                  << set[i].tmean << "\t\t" << set[i].T << "\t" << set[i].d
                  << "\t" << set[i].d_2 << "\t\t" << set[i].T_2d << "\n";
    }

    pair linear_reg = linear_regression(set);
    std::cout << "\nEquation: \n";
    std::cout << "y = " << linear_reg.a << "x + " << linear_reg.b << "\n";

    std::cout << "\nK^2: " << (L * L + B * B) / 12.0f << " m^2";
    std::cout << "\ng: " << (4.0f * PI * PI) / (linear_reg.a * 100.0f)
              << " m/s^2";

    return MONKE;
}