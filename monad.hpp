#include <list>
#include <iostream>
#include <functional>

template <typename T>
void write(std::ostream &os, std::list<T> &ts) {
    os << "[";
    auto it = ts.begin();
    if (it != ts.end()) {
        os << *(it++);
        for (; it != ts.end(); ++it) {
            os << ", " << *it;
        }
    }
    os << "]";
}

template <template <typename... T> class M>
class Monad {
public:
    template <typename X, typename Y>
    static M<Y> bind(M<X> xs, const std::function<M<Y>(X)> &fn);

    template <typename X>
    static M<X> unit(X x);

    template <typename X, typename Y>
    static M<Y> map(M<X> xs, const std::function<Y(X)> &fn);
};

template <template <typename... T> class M>
template <typename X, typename Y>
M<Y> Monad<M>::map(M<X> xs, const std::function<Y(X)> &fn) {
    auto kleisli = [fn](X x) { return unit(fn(x)); };
    return bind<X, Y>(xs, kleisli);
}

template <>
template <typename X, typename Y>
std::list<Y> Monad<std::list>::bind(std::list<X> xs, const std::function<std::list<Y>(X)> &fn) {
    std::list<Y> ys;
    std::list<Y> zs;
    for (auto x : xs) {
        zs = fn(x);
        ys.insert(ys.end(), zs.begin(), zs.end());
    }
    return ys;
}

template <>
template <typename X>
std::list<X> Monad<std::list>::unit(X x) {
    return std::list<X>(1, x);
}
