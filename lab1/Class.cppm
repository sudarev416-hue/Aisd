export module Class;
import std;
export template<typename T>
class Vector{
    private:
    T* _vec=nullptr;
    int _size=0;
    public:
    Vector(int size,const T& el):_vec(new T[size]),_size(size){
        if(_size<0){
            throw std::invalid_argument("size must be non-negative");
        }
        for (int i=0;i<_size;++i){
            _vec[i]=el;
        }
    }
    Vector(int size,const T& min, const T& max)requires std::integral<T>:_vec(new T[size]),_size(size)
    {
        if(_size<0){
            throw std::invalid_argument("size must be non-negative");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<T> dist(min, max);
        for(int i=0; i<_size;++i){
            _vec[i]=dist(gen);
        }
    }
    Vector(int size,const T& min, const T& max)requires std::floating_point<T>:_vec(new T[size]),_size(size)
    {
        if(_size<0){
            throw std::invalid_argument("size must be non-negative");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> dist(min, max);
        for(int i=0; i<_size;++i){
            _vec[i]=dist(gen);
        }
    }
    Vector(int size,const T& min, const T& max)requires std::same_as<T, std::complex<double>>:_vec(new T[size]),_size(size)
    {
        if(_size<0){
            throw std::invalid_argument("size must be non-negative");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<double> distRe(min.real(), max.real());
        std::uniform_real_distribution<double> distIm(min.imag(), max.imag());
        for (int i = 0; i < _size; ++i)
            _vec[i] = {distRe(gen), distIm(gen)};
    }
    Vector(int size,const T& min, const T& max)requires std::same_as<T, std::complex<float>>:_vec(new T[size]),_size(size)
    {
        if(_size<0){
            throw std::invalid_argument("size must be non-negative");
        }
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distRe(min.real(), max.real());
        std::uniform_real_distribution<float> distIm(min.imag(), max.imag());
        for (int i = 0; i < _size; ++i)
            _vec[i] = {distRe(gen), distIm(gen)};
    }
    const int size(){
        return _size;
    }
     T& operator[](const int& index) {
        return _vec[index];
    }
    const T& operator[](const int& index) const{
        return _vec[index];
    }
    Vector& operator+=(const Vector& other ){
        if (_size != other._size){
            throw std::invalid_argument("Размеры векторов не совпадают");
        }
        for (int i = 0; i < _size; ++i) _vec[i]+=other._vec[i];
        return *this;
    }
    Vector& operator-=(const Vector& other ){
        if (_size != other._size){
            throw std::invalid_argument("Размеры векторов не совпадают");
        }
        for (int i = 0; i < _size; ++i) _vec[i]-=other._vec[i];
        return *this;
    }
    Vector operator+(const Vector& other) const {
        Vector result = *this;
        result += other;
        return result;
    }

    Vector operator-(const Vector& other) const {
        Vector result = *this;
        result -= other;
        return result;
    }
    T operator*(const Vector& other) const
        requires (std::integral<T> || std::floating_point<T>)
    {
        if (_size != other._size){
            throw std::invalid_argument("Размеры векторов не совпадают");
        }
        T result{};
        for (int i = 0; i < _size; ++i){
            result += _vec[i] * other._vec[i];
        }
        return result;
    }
    T operator*(const Vector& other) const
        requires (std::same_as<T, std::complex<double>> || std::same_as<T, std::complex<float>>)
    {
        if (_size != other._size){
            throw std::invalid_argument("Размеры векторов не совпадают");
        }
        T result{};
        for (int i = 0; i < _size; ++i){
            result += std::conj(_vec[i]) * other._vec[i];
        }
        return result;
    }
    Vector& operator*=(const T& chi){
        for(int i=0; i < _size; ++i){
            _vec[i]*=chi;
        }
        return *this;
    } 
    Vector operator*(const T& chi){
        Vector result=*this;
        result*=chi;
        return result;
    }
    friend Vector operator*(const T& chi, Vector v) {
        return v *= chi;
    }
    Vector& operator/=(const T& chi){
        if (chi == T{}) throw std::invalid_argument("Деление на ноль");
        for(int i=0; i < _size; ++i){
            _vec[i]/=chi;
        }
        return *this;
    } 
    Vector operator/(const T& chi) const{
        Vector result=*this;
        result/=chi;
        return result;
    }
    void print(){
        for(int i = 0; i < _size; ++i){
            std::cout << _vec[i] << " ";
        }
        std::cout << std::endl;
    }
};