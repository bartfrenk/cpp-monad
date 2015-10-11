#ifndef MONAD_HPP
#define MONAD_HPP

#include <functional>

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

#endif
