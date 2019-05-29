#include <iostream>
#include <algorithm>
#include <vector>
#include "manipulators.h"

int main() {

    std::cout << index(144, 6) << std::endl << index(5, 6) << std::endl << index(5555, 6);


    std::vector<line> Vec;

    Vec.push_back(line());
    Vec.push_back(line());
    Vec.push_back(line());
    Vec.push_back(line());
    Vec.push_back(line());


    std::sort(Vec.begin(), Vec.end(), [](const line& A, const line& B) { return A.get_m_line() < B.get_m_line(); });


    for (auto &i : Vec)
    {
        std::cout << i;
    }


    return 0;
}