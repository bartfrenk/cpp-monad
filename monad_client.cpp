#include <list>
#include <iostream>
#include "monad.hpp"

typedef Monad<std::list> ListMonad;

using std::cout;

std::list<int> smaller(int x) {
    std::list<int> xs;
    if (x > 0)
        for (int i = 0; i < x; ++i)
            xs.push_back(i);
    return xs;
}

int main() {
    auto as = ListMonad::unit(6);
    write(std::cout, as);
    std::cout << "\n";

    auto bs = ListMonad::bind<int, int>(as, &smaller);
    write(std::cout, bs);
    std::cout << "\n";

    auto cs = ListMonad::map<int, int>(bs, [](int x) { return x + 1; });
    write(std::cout, cs);
    std::cout << "\n";

    auto ds = ListMonad::bind<int, int>(cs, &smaller);
    write(std::cout, ds);
    std::cout << "\n";

    return 0;
}
