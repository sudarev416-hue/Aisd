export module view;
import std;
import Class;
// Шаблонная функция для демонстрации всех операций над одним типом T
export template<typename T>
void demo(const std::string& typeName, const T& fill,
          const T& min, const T& max,
          const T& scalar, const T& scalar2,
          int size = 5)
{
    std::cout << "========== " << typeName << " ==========\n\n";

    // 1. Конструктор с заполнением
    std::cout << "--- Конструктор с заполнением (size=" << size
              << ", value=" << fill << ") ---\n";
    Vector<T> a(size, fill);
    std::cout << "a = ";
    a.print();

    // 2. Конструктор со случайными значениями
    std::cout << "\n--- Конструктор со случайными значениями (size=" << size
              << ", min=" << min << ", max=" << max << ") ---\n";
    Vector<T> b(size, min, max);
    std::cout << "b = ";
    b.print();

    Vector<T> c(size, min, max);
    std::cout << "c = ";
    c.print();

    // 3. operator[] — чтение и запись
    std::cout << "\n--- operator[] (чтение/запись) ---\n";
    std::cout << "b[0] (до)  = " << b[0] << '\n';
    b[0] = fill;
    std::cout << "b[0] (после) = " << b[0] << '\n';
    std::cout << "b = ";
    b.print();

    // 4. Операторы сложения и вычитания
    std::cout << "\n--- Операторы + и - ---\n";
    Vector<T> sum = b + c;
    std::cout << "b + c = ";
    sum.print();

    Vector<T> diff = b - c;
    std::cout << "b - c = ";
    diff.print();

    std::cout << "\n--- Операторы += и -= ---\n";
    Vector<T> d = b;
    d += c;
    std::cout << "d = b; d += c -> ";
    d.print();

    d = b;
    d -= c;
    std::cout << "d = b; d -= c -> ";
    d.print();

    // 5. Скалярное произведение
    std::cout << "\n--- Скалярное произведение (b * c) ---\n";
    std::cout << "b * c = " << (b * c) << '\n';

    // 6. Умножение на скаляр (с коммутативностью)
    std::cout << "\n--- Умножение на скаляр ---\n";
    Vector<T> e = b * scalar;
    std::cout << "b * " << scalar << " = ";
    e.print();

    Vector<T> f = scalar * b;  // коммутативность
    std::cout << scalar << " * b = ";
    f.print();

    std::cout << "\n--- *= ---\n";
    Vector<T> g = b;
    g *= scalar2;
    std::cout << "g = b; g *= " << scalar2 << " -> ";
    g.print();

    // 7. Деление на скаляр
    std::cout << "\n--- Деление на скаляр ---\n";
    Vector<T> h = b / scalar;
    std::cout << "b / " << scalar << " = ";
    h.print();

    std::cout << "\n--- /= ---\n";
    Vector<T> k = b;
    k /= scalar2;
    std::cout << "k = b; k /= " << scalar2 << " -> ";
    k.print();

    std::cout << "\n\n";
}
