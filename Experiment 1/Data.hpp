class Data {
   private:
    static float sumTime;
    static float sumSquareTime;
    static float denom;
    float a, b;
    float sigma_lnI, sigma_lnI_T;

   public:
    static int N;
    Data() {
        sigma_lnI = 0.0f;
        sigma_lnI_T = 0.0f;
    }

    void increment_sigma_ln_I(float x) { sigma_lnI += x; }
    void increment_sigma_ln_I_T(float x) { sigma_lnI_T += x; }

    void calculate() {
        float x = sigma_lnI_T * N;
        float y = sigma_lnI * sumTime;

        a = (x - y) / denom;

        x = sigma_lnI * sumSquareTime;
        y = sigma_lnI_T * sumTime;

        b = (x - y) / denom;
    }

    void print() { std::cout << "{a: " << a << "\tb: " << b << "}\n"; }
};