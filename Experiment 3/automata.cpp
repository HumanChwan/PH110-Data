#include <iomanip>
#include <iostream>
#include <string>

struct Data {
  float i, v1, v2, v3, v4;
  float vh;
};

int main(int argc, char** argv) {
  freopen("data.txt", "r", stdin);
  freopen("log.txt", "w", stdout);

  int N;
  if (argc < 1) {
    std::cout << "error";
    return 0;
  } else {
    std::string N_as_string = argv[1];
    N = std::stoi(N_as_string);
  }

  std::cout << std::fixed << std::setprecision(2);

  Data data[N];
  for (int i = 0; i < N; ++i) {
    std::cin >> data[i].i >> data[i].v1 >> data[i].v2 >> data[i].v3 >>
        data[i].v4;
    data[i].v1 = std::abs(data[i].v1);
    data[i].v2 = std::abs(data[i].v2);
    data[i].v3 = std::abs(data[i].v3);
    data[i].v4 = std::abs(data[i].v4);

    data[i].vh = (data[i].v1 + data[i].v2 + data[i].v3 + data[i].v4) / 4.0f;
  }

  float sigmaX = 0.0f;
  float sigmaX2 = 0.0f;
  float sigmaY = 0.0f;
  float sigmaXY = 0.0f;

  for (int i = 0; i < N; ++i) {
    sigmaX += data[i].i;
    sigmaY += data[i].vh;

    sigmaX2 += (data[i].i) * (data[i].i);
    sigmaXY += (data[i].i) * (data[i].vh);
  }

  float a =
      ((N * sigmaXY) - (sigmaX * sigmaY)) / ((N * sigmaX2) - sigmaX * sigmaX);
  float b = ((sigmaY * sigmaX2) - (sigmaX * sigmaXY)) /
            ((N * sigmaX2) - sigmaX * sigmaX);

  std::cout << "I (mA)\tVh (mV)\n";
  for (int i = 0; i < N; ++i) {
    std::cout << data[i].i << "\t\t" << (data[i].vh) << "\n";
  }
  std::cout << "\na: " << a << "\nb: " << b;
}