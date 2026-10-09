import std;
import Class;
import view;
import task;
int main() {
    // int
    demo<int>("int", 2, -10, 10, 3, 2);

    // float
    demo<float>("float", 2.5f, -10.0f, 10.0f, 3.0f, 2.0f);

    // double
    demo<double>("double", 2.5, -10.0, 10.0, 3.0, 2.0);

    // std::complex<float>
    demo<std::complex<float>>(
        "std::complex<float>",
        {2.0f, 1.0f},                       // fill
        {-10.0f, -10.0f}, {10.0f, 10.0f},   // min, max
        {3.0f, 0.0f}, {2.0f, 0.0f}          // scalar, scalar2
    );

    // std::complex<double>
    demo<std::complex<double>>(
        "std::complex<double>",
        {2.0, 1.0},
        {-10.0, -10.0}, {10.0, 10.0},
        {3.0, 0.0}, {2.0, 0.0}
    );
    Vector<double> a1(4, 1.0, 5.0);
    demoPerp("double", a1);

    Vector<float> a2(5, -3.0f, 7.0f);
    demoPerp("float", a2);

    Vector<std::complex<double>> a3(
        4,
        {-2.0, 1.0},
        { 3.0, 4.0}
    );
    demoPerp("std::complex<double>", a3);

    Vector<std::complex<float>> a4(
        3,
        {-1.0f, 2.0f},
        { 2.0f, 3.0f}
    );
    demoPerp("std::complex<float>", a4);

    return 0;
}