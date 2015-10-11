#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <list>

#include "monad.hpp"

typedef Monad<std::list> ListMonad;

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

template <>
template <typename X, typename Y>
std::list<Y> ListMonad::bind(std::list<X> xs, const std::function<std::list<Y>(X)> &fn) {
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
std::list<X> ListMonad::unit(X x) {
    return std::list<X>(1, x);
}

#endif
