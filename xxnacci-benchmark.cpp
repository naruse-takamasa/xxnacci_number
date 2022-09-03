#include <iostream>
#include <vector>
#include <cstddef>

#include "xxnacci-normal.h"
#include "xxnacci-neon.h"

namespace{

constexpr uint32_t num_of_test = 30;
constexpr size_t MAX_N = 300000;
constexpr size_t n = 502;
constexpr uint32_t m = 19;
uint32_t A[MAX_N << 1], ANS[MAX_N << 1];
std::vector<double> times[2];

}

template<bool is_neon_mode>
std::pair<double, uint32_t> cal_xxnacci() {

    set_zero_mat(&A[0], n);
    set_zero_mat(&A[MAX_N], n);
    set_zero_mat(&ANS[0], n);
    set_zero_mat(&ANS[MAX_N], n);
    for (std::remove_const<decltype(n)>::type i = 0; i < n; i++) {
        A[i * n] = 1;
    }
    for (std::remove_const<decltype(n)>::type i = 1; i < n; i++) {
        A[i + (i - 1) * n] = 1;
    }

    auto ans_bit = 0, a_bit = 0;
    auto first = true;
    uint32_t mask = 1;
    auto start = std::chrono::system_clock::now();

    while (m >= mask) {
        if (m & mask) {
            if (first) {
                add_mat(&ANS[(ans_bit ^ 1) * MAX_N], &A[a_bit * MAX_N], n);
                first = false;
            } else {
                set_zero_mat(&ANS[(ans_bit ^ 1) * MAX_N], n);
                if constexpr (is_neon_mode)
                    neon_mat_mul(&ANS[(ans_bit ^ 1) * MAX_N], &A[a_bit * MAX_N], &ANS[ans_bit * MAX_N], n);
                else
                    normal_mat_mul(&ANS[(ans_bit ^ 1) * MAX_N], &A[a_bit * MAX_N], &ANS[ans_bit * MAX_N], n);
            }
            ans_bit ^= 1;
        }
        set_zero_mat(&A[(a_bit ^ 1) * MAX_N], n);
        if constexpr (is_neon_mode)
            neon_mat_mul(&A[(a_bit ^ 1) * MAX_N], &A[a_bit * MAX_N], &A[a_bit * MAX_N], n);
        else
            normal_mat_mul(&A[(a_bit ^ 1) * MAX_N], &A[a_bit * MAX_N], &A[a_bit * MAX_N], n);
#ifdef DEBUG_BUILD
        print_mat(&A[a_bit * MAX_N], n);
        print_mat(&A[(a_bit ^ 1) * MAX_N], n);
#endif
        a_bit ^= 1;
        mask <<= 1;
    }

    auto end = std::chrono::system_clock::now();
    auto elapse_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
#ifdef DEBUG_BUILD
    if constexpr (is_neon_mode)
        std::cerr << "neon ";
    else
        std::cerr << "normal ";
    std::cerr << "elapse time : " << elapse_time << " micro sec." << std::endl;
    std::cerr << ANS[ans_bit * MAX_N] << std::endl;
#endif
    return {elapse_time, ANS[ans_bit * MAX_N]};
}

void test() {
    auto [neon_time, neon_res] = cal_xxnacci<true>();
    auto [normal_time, normal_res] = cal_xxnacci<false>();
    assert(neon_res == normal_res);
    times[0].push_back(neon_time);
    times[1].push_back(normal_time);
}

int main() {
    for (std::remove_const<decltype(num_of_test)>::type i = 0; i < num_of_test; i++) {
        test();
    }
    sort(times[0].begin(), times[0].end());
    sort(times[1].begin(), times[1].end());
    std::cout << "neon median : " << times[0][times[0].size() / 2] << " micro sec.  ";
    std::cout << "normal median : " << times[1][times[1].size() / 2] << " micro sec." << std::endl;
}
