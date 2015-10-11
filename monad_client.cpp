#include <list>
#include <iostream>

#include "list.hpp"
#include "option.hpp"

using std::cout;

std::list<int> smaller(int x) {
    std::list<int> xs;
    if (x > 0)
        for (int i = 0; i < x; ++i)
            xs.push_back(i);
    return xs;
}

int main() {
    std::cout << "ListMonad\n";

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

    std::cout << "\nOptionMonad\n";
    std::string s = "hello";

    auto es = OptionMonad::unit(s);
    es.write(std::cout);
    std::cout << "\n";

    auto fs = OptionMonad::map<std::string, size_t>(es, [](std::string s) { return s.size(); });
    fs.write(std::cout);
    std::cout << "\n";

    auto gs = OptionMonad::bind<size_t, std::string>(fs, [](size_t i) {
            return (i != 5 ? Option<std::string>("not 5") : Option<std::string>());
        });
    gs.write(std::cout);
    std::cout << "\n";

    return 0;
}
