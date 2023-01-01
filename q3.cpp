//
// Created by kobi on 12/31/22.
//

#include <array>
#include <algorithm>
#include <limits>
#include <iostream>

namespace {
    void option1() {
        auto arr = std::to_array({7, 1, 5, 3, 6, 4});
        auto diff = std::numeric_limits<int>::min();
        for (auto iter = arr.cbegin(); std::next(iter) != arr.cend(); ++iter) {
            const auto m = std::max_element(std::next(iter), arr.cend());
            const auto curr_diff = *m - *iter;
            if (curr_diff > diff) {
                diff = curr_diff;
            }
        }
        std::clog << diff << '\n';
    }

    void option2() {
        auto arr = std::to_array({7, 1, 5, 3, 6, 4});
        auto min_so_far = std::numeric_limits<int>::max();
        auto profit = 0;
        for (const auto v : arr) {
            if (v < min_so_far) {
                min_so_far = v;
            }
            const auto curr_profit = v - min_so_far;
            if (curr_profit > profit) {
                profit = curr_profit;
            }
        }
        std::clog << profit << '\n';
    }
}

int main() {
    option1();
    option2();
}
