template <class T>
class MyLess {
public:
    const bool operator() (const T &x, const T &y) const;
};

template <class T>
const bool MyLess<T>::operator() (const T &x, const T &y) const {
    return x % 10 < y % 10;
}
