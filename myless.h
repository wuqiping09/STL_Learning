template <class T>
class MyLess {
public:
    bool operator() (const T &x, const T &y);
};

template <class T>
bool MyLess<T>::operator() (const T &x, const T &y) {
    return x % 10 < y % 10;
}
