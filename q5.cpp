//
// Created by kobi on 12/31/22.
//

#include <cstdint>
#include <bitset>
#include <iostream>

int main() {

    uint32_t val = 0b1111'0101;
    std::clog << "before " << std::bitset<32>(val) << '\n';
    for(int i=0, j=31; i<j; ++i, --j){
        const auto mi = ((1U<<i) & val);
        const auto mj = ((1U<<j) & val);
        if ( (mi && !mj) || (!mi && mj)) {
            // swap
            if (mi) {
                val &= ~(1U << i);
                val |=  (1U << j);
            } else {
                val |=  (1U << i);
                val &= ~(1U << j);
            }
        }
    }
    std::clog << "after  " << std::bitset<32>(val) << '\n';
}
