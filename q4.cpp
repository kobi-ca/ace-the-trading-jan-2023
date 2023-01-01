//
// Created by kobi on 12/31/22.
//

#include <array>
#include <algorithm>
#include <limits>
#include <iostream>
#include <iterator>

namespace {
    const auto arr = std::to_array({3, 3, 5, 0, 0, 3, 1, 4});

    void compute_fwd(std::array<int, arr.size()> &profit_fwd) {
        auto fwd_profit_so_far = 0;
        auto min_so_far = std::numeric_limits<int>::max();
        auto profit_fwd_iter = profit_fwd.begin();
        for(auto iter = arr.cbegin(); std::next(iter) != arr.cend(); ++iter, ++profit_fwd_iter) {
            if (*iter < min_so_far) {
                min_so_far = *iter;
            }
            const auto p = *iter - min_so_far;
            if (p > fwd_profit_so_far) {
                fwd_profit_so_far = p;
                *profit_fwd_iter = p;
            }
        }
    }

    void compute_back(std::array<int, arr.size()> &profit_back) {
        auto back_profit_so_far = 0;
        auto max_so_far = std::numeric_limits<int>::min();
        auto profit_back_iter = profit_back.rbegin();
        for(auto iter = arr.crbegin(); std::next(iter) != arr.crend(); ++iter, ++profit_back_iter) {
            if (*iter > max_so_far) {
                max_so_far = *iter;
            }
            const auto p = max_so_far - *iter;
            if (p > back_profit_so_far) {
                back_profit_so_far = p;
                *profit_back_iter = p;
            }
        }
    }
}

int main() {
    std::array<int, arr.size()> profit_fwd{};
    compute_fwd(profit_fwd);
    std::copy(profit_fwd.cbegin(), profit_fwd.cend(), std::ostream_iterator<int>(std::clog, " "));
    std::clog << '\n';
    std::array<int, arr.size()> profit_back{};
    compute_back(profit_back);
    std::copy(profit_back.cbegin(), profit_back.cend(), std::ostream_iterator<int>(std::clog, " "));
    std::clog << '\n';

    const auto m1 = std::max_element(profit_back.cbegin(), profit_back.cend());
    const auto dist = std::distance(profit_back.cbegin(), m1);
    const auto m2 = std::max_element(profit_fwd.cbegin(), profit_fwd.cbegin() + dist);
    std::clog << *m1 + *m2 << '\n';
}
