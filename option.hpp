#ifndef OPTION_HPP
#define OPTION_HPP

#include <iostream>

#include "monad.hpp"

// TODO: think about ownership and overhead!
// TODO: implement safe bool idiom
template <typename T>
class Option {
public:
    Option(T t) : t(t), none(false) {}
    Option() : none(true) {}
    T get() { return t; };
    bool empty() { return none; };
    void write(std::ostream &os);
private:
    T t;
    bool none;
};


template <typename T>
void Option<T>::write(std::ostream &os) {
    if (none)
        os << "None";
    else
        os << "Some " << t;
}

typedef Monad<Option> OptionMonad;

template <>
template <typename X, typename Y>
Option<Y> OptionMonad::bind(Option<X> xs, const std::function<Option<Y>(X)> &fn) {
    if (xs.empty()) return Option<Y>();
    else return fn(xs.get());
}

template <>
template <typename X>
Option<X> OptionMonad::unit(X x) {
    return Option<X>(x);
}


#endif
