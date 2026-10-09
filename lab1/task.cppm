export module task;
import std;
import Class;
template<typename T>
Vector<T> perpendicularUnit(Vector<T>& a) {
    const int n = a.size();
    if (n < 2)
        throw std::invalid_argument("Вектор должен иметь размер >= 2");

    // Проверка на нулевой вектор
    bool isZero = true;
    for (int i = 0; i < n; ++i) {
        if (a[i] != T{}) { isZero = false; break; }
    }
    if (isZero)
        throw std::invalid_argument("Нулевой вектор не имеет перпендикуляра");

    // 1. Ищем индекс k с максимальным |a[k]|
    int k = 0;
    double bestAbs = 0.0;
    for (int i = 0; i < n; ++i) {
        double curAbs = std::abs(a[i]);   // работает и для complex, и для чисел
        if (curAbs > bestAbs) { bestAbs = curAbs; k = i; }
    }

    // 2. Ищем индекс j != k с ненулевым a[j]
    //    (или просто ближайший другой индекс)
    int j = (k == 0) ? 1 : 0;
    for (int i = 0; i < n; ++i) {
        if (i != k && a[i] != T{}) { j = i; break; }
    }

    // 3. Строим b' = (-a[j] на месте k, a[k] на месте j, остальное 0)
    Vector<T> b(n, T{});
    b[k] = -a[j];
    b[j] =  a[k];

    // 4. Нормируем b = b' / ||b'||
    double norm = 0.0;
    for (int i = 0; i < n; ++i)
        norm += std::norm(b[i]);   // std::norm — квадрат модуля, работает и для complex
    norm = std::sqrt(norm);

    b /= static_cast<T>(norm);     // деление на скаляр
    return b;
}

// Демонстрация для разных типов
export template<typename T>
void demoPerp(const std::string& typeName, Vector<T>& a) {
    std::cout << "========== " << typeName << " ==========\n";
    std::cout << "a          = ";
    a.print();

    Vector<T> b = perpendicularUnit(a);

    std::cout << "b (перпенд.) = ";
    b.print();

    // Проверка: a * b должно быть 0, ||b|| = 1
    T dot = a * b;
    double normB = 0.0;
    for (int i = 0; i < b.size(); ++i)
        normB += std::norm(b[i]);
    normB = std::sqrt(normB);

    std::cout << "a * b = " << dot << "  (должно быть 0)\n";
    std::cout << "||b|| = " << normB << "  (должно быть 1)\n\n";
}