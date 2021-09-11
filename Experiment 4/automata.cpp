#include <iomanip>
#include <iostream>
#include <string>

constexpr int MONKE = 0;
int N;
struct Data {
    int freq;
    float l1, l2;
    float diff;
    float wavelen;

    Data() {
        freq = 0;
        l1 = 0.0f;
        l2 = 0.0f;
    }

    void set(int f, float len1, float len2) {
        freq = f;
        l1 = len1;
        l2 = len2;

        diff = len2 - len1;
        wavelen = diff * 2.0f;
    }
};

struct PlotData {
    int freq;
    float mean_wavelen;

    float x;
    float y;

    void set(int f, float w) {
        freq = f;
        mean_wavelen = w;

        x = 1.0f / freq;
        y = w;
    }
};

int main(int argc, char* argv[]) {
    freopen("data.txt", "r", stdin);
    freopen("log.txt", "w", stdout);

    if (argc != 2) {
        std::cerr << "ERROR: missing command line arguments";
        return -1;
    }

    std::string N_as_string = argv[1];
    N = std::stoi(N_as_string);
    Data tuple[N];
    PlotData set[N / 3];

    int freq;
    float len1, len2;
    for (int i = 0; i < N / 3; ++i) {
        float mean = 0.0f;
        for (int j = 0; j < 3; ++j) {
            std::cin >> freq >> len1 >> len2;
            tuple[i * 3 + j].set(freq, len1, len2);
            mean += (len2 - len1) * 2.0f;
        }
        mean /= 3.0f;

        set[i].set(tuple[i * 3].freq, mean);
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "S.No\tfreq(v)\t\t(1/freq)(1/v)\t\tl1\t\t\tl2\t\t\t(l2-l1 = "
                 "wav/2)\t\twav\t\t\tmean_wav\n\n";
    for (int i = 0; i < N / 3; ++i) {
        std::cout << i + 1;
        for (int j = 0; j < 3; ++j) {
            std::cout << "\t\t\t";
            std::cout << set[i].freq << "\t\t\t";
            std::cout << std::setprecision(2) << std::scientific << set[i].x
                      << "\t\t\t\t";
            std::cout << std::fixed << std::setprecision(2);
            std::cout << tuple[i * 3 + j].l1 << "\t\t" << tuple[i * 3 + j].l2
                      << "\t\t\t\t" << tuple[i * 3 + j].diff << "\t\t\t\t\t"
                      << tuple[i * 3 + j].wavelen;

            if (j == 1) {
                std::cout << "\t\t\t" << set[i].mean_wavelen;
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    float sigmaX = 0.0f;
    float sigmaX2 = 0.0f;
    float sigmaY = 0.0f;
    float sigmaXY = 0.0f;

    N = N / 3;

    for (int i = 0; i < N; ++i) {
        sigmaX += set[i].x * 1000;
        sigmaY += set[i].y;

        sigmaX2 += (set[i].x * 1000) * (set[i].x * 1000);
        sigmaXY += (set[i].x * 1000) * (set[i].y);
    }

    float a =
        ((N * sigmaXY) - (sigmaX * sigmaY)) / ((N * sigmaX2) - sigmaX * sigmaX);
    float b = ((sigmaY * sigmaX2) - (sigmaX * sigmaXY)) /
              ((N * sigmaX2) - sigmaX * sigmaX);

    std::cout << "Equation: \n";
    std::cout << "y = " << a << "x + " << b << "\n";

    std::cout << "unit of y: (cm) & unit of x: (kHz ^ -1)\n";

    std::cout << "\nSpeed of sound: " << a << " cm / ms\n";
    std::cout << "=> " << a * 10 << " m / s\n";

    return MONKE;
}