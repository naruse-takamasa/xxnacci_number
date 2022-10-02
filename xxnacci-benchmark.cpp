#include "xxnacci-normal.h"
#include "xxnacci-neon.h"

#include <iostream>
#include <vector>
#include <cstddef>

namespace {

constexpr size_t MAX_N = 300000;
size_t n;
uint32_t m;
uint32_t A[MAX_N << 1], ANS[MAX_N << 1];


template<bool is_neon_mode>
std::pair<double, uint32_t> cal_xxnacci() {

    set_zero_mat(&A[0], n);
    set_zero_mat(&A[MAX_N], n);
    set_zero_mat(&ANS[0], n);
    set_zero_mat(&ANS[MAX_N], n);
    for (size_t i = 0; i < n; i++) {
        A[i * n] = 1;
    }
    for (size_t i = 1; i < n; i++) {
        A[i + (i - 1) * n] = 1;
    }

    auto ans_idx = 0, a_idx = 0;
    auto first = true;
    uint32_t mask = 1;
    auto start = std::chrono::system_clock::now();

    while (m >= mask) {
        if (m & mask) {
            if (first) {
                add_mat(&ANS[(ans_idx ^ 1) * MAX_N], &A[a_idx * MAX_N], n);
                first = false;
            } else {
                set_zero_mat(&ANS[(ans_idx ^ 1) * MAX_N], n);
                if constexpr (is_neon_mode)
                    neon_mat_mul(&ANS[(ans_idx ^ 1) * MAX_N], &A[a_idx * MAX_N], &ANS[ans_idx * MAX_N], n);
                else
                    normal_mat_mul(&ANS[(ans_idx ^ 1) * MAX_N], &A[a_idx * MAX_N], &ANS[ans_idx * MAX_N], n);
            }
            ans_idx ^= 1;
        }
        set_zero_mat(&A[(a_idx ^ 1) * MAX_N], n);
        if constexpr (is_neon_mode)
            neon_mat_mul(&A[(a_idx ^ 1) * MAX_N], &A[a_idx * MAX_N], &A[a_idx * MAX_N], n);
        else
            normal_mat_mul(&A[(a_idx ^ 1) * MAX_N], &A[a_idx * MAX_N], &A[a_idx * MAX_N], n);
#ifdef DEBUG_BUILD
        print_mat(&A[a_idx * MAX_N], n);
        print_mat(&A[(a_idx ^ 1) * MAX_N], n);
#endif
        a_idx ^= 1;
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
    std::cerr << ANS[ans_idx * MAX_N] << std::endl;
#endif
    return {elapse_time, ANS[ans_idx * MAX_N]};
}

std::vector<std::tuple<size_t, uint32_t, double, double> > elapse_time_list;

void test() {
    constexpr uint32_t num_of_test = 30;
    std::vector<double> times[2];
    for (uint32_t i = 0; i < num_of_test; i++) {
        auto [neon_time, neon_res] = cal_xxnacci<true>();
        auto [normal_time, normal_res] = cal_xxnacci<false>();
        assert(neon_res == normal_res);
        times[0].push_back(neon_time);
        times[1].push_back(normal_time);
    }
    sort(times[0].begin(), times[0].end());
    sort(times[1].begin(), times[1].end());
    elapse_time_list.emplace_back(n, m, times[0][times[0].size() / 2],  times[1][times[1].size() / 2]);
    // std::cout << "neon median : " << times[0][times[0].size() / 2] << " micro sec.  ";
    // std::cout << "normal median : " << times[1][times[1].size() / 2] << " micro sec." << std::endl;
}

void print_csv() {
    std::cout << "XX number, m, NEON median, normal median" << std::endl;
    std::for_each(elapse_time_list.begin(), elapse_time_list.end(),
        [](std::tuple<size_t, uint32_t, double, double> i) {
            std::cout << get<0>(i) << ", " << get<1>(i) << ", " << get<2>(i) << ", " << get<3>(i) << std::endl;
        });
}

}

int main() {
    for (m = 1; m < 30; m++) {
        std::cerr << m << std::endl;
        for (n = 2; n < 300; n++) {
            ::test();
        }
    }
    print_csv();
}
