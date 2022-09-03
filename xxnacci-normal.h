#ifndef _XXNACCI_NORMAL_
#define _XXNACCI_NORMAL_

#include <iostream>
#include <arm_neon.h>

#include "xxnacci-neon.h"

void print_mat(uint32_t* mat, size_t n) {
    std::cerr << "=======================" << std::endl;
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            std::cerr << mat[j * n + i] << " ";
        }
        std::cerr << std::endl;
    }
}

void set_zero_mat(uint32_t* mat, size_t n) {
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            mat[j * n + i] = 0;
        }
    }
}

void add_mat(uint32_t* dst, uint32_t* src, size_t n) {
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            dst[j * n + i] += src[j * n + i];
        }
    }
}

void normal_mat_mul(uint32_t* C, uint32_t* A, uint32_t* B, size_t n) {
    for (std::size_t i = 0; i < n; i++) {
        for (std::size_t j = 0; j < n; j++) {
            for (std::size_t k = 0; k < n; k++) {
                C[j * n + i] += A[k * n + i] * B[j * n + k];
            }
        }
    }
}

// void block4x4_mat_mul(uint32_t* C, uint32_t* A, uint32_t* B) {
//     for (std::size_t i = 0; i + 4 < n; i += 4) {
//         for (std::size_t j = 0; j + 4 < n; j += 4) {
//             for (std::size_t k = 0; k + 4 < n; k += 4) {
//                 // vmlaq_laneq_u32(C0, A0, B0, 0);
//                 C[j * n + i] += A[k * n + i] * B[j * n + k];
//                 C[j * n + i + 1] += A[k * n + i + 1] * B[j * n + k];
//                 C[j * n + i + 2] += A[k * n + i + 2] * B[j * n + k];
//                 C[j * n + i + 3] += A[k * n + i + 3] * B[j * n + k];

//                 // vmlaq_laneq_u32(C0, A1, B0, 1);
//                 C[j * n + i] += A[(k + 1) * n + i] * B[j * n + k + 1];
//                 C[j * n + i + 1] += A[(k + 1) * n + i + 1] * B[j * n + k + 1];
//                 C[j * n + i + 2] += A[(k + 1) * n + i + 2] * B[j * n + k + 1];
//                 C[j * n + i + 3] += A[(k + 1) * n + i + 3] * B[j * n + k + 1];

//                 // vmlaq_laneq_u32(C0, A2, B0, 2);
//                 C[j * n + i] += A[(k + 2) * n + i] * B[j * n + k + 2];
//                 C[j * n + i + 1] += A[(k + 2) * n + i + 1] * B[j * n + k + 2];
//                 C[j * n + i + 2] += A[(k + 2) * n + i + 2] * B[j * n + k + 2];
//                 C[j * n + i + 3] += A[(k + 2) * n + i + 3] * B[j * n + k + 2];

//                 // vmlaq_laneq_u32(C0, A3, B0, 3);
//                 C[j * n + i] += A[(k + 3) * n + i] * B[j * n + k + 3];
//                 C[j * n + i + 1] += A[(k + 3) * n + i + 1] * B[j * n + k + 3];
//                 C[j * n + i + 2] += A[(k + 3) * n + i + 2] * B[j * n + k + 3];
//                 C[j * n + i + 3] += A[(k + 3) * n + i + 3] * B[j * n + k + 3];

//                 // vmlaq_laneq_u32(C1, A0, B1, 0);
//                 C[(j + 1) * n + i] += A[k * n + i] * B[(j + 1) * n + k];
//                 C[(j + 1) * n + i + 1] += A[k * n + i + 1] * B[(j + 1) * n + k];
//                 C[(j + 1) * n + i + 2] += A[k * n + i + 2] * B[(j + 1) * n + k];
//                 C[(j + 1) * n + i + 3] += A[k * n + i + 3] * B[(j + 1) * n + k];

//                 // vmlaq_laneq_u32(C1, A1, B1, 1);
//                 C[(j + 1) * n + i] += A[(k + 1) * n + i] * B[(j + 1) * n + k + 1];
//                 C[(j + 1) * n + i + 1] += A[(k + 1) * n + i + 1] * B[(j + 1) * n + k + 1];
//                 C[(j + 1) * n + i + 2] += A[(k + 1) * n + i + 2] * B[(j + 1) * n + k + 1];
//                 C[(j + 1) * n + i + 3] += A[(k + 1) * n + i + 3] * B[(j + 1) * n + k + 1];

//                 // vmlaq_laneq_u32(C1, A2, B1, 2);
//                 C[(j + 1) * n + i] += A[(k + 2) * n + i] * B[(j + 1) * n + k + 2];
//                 C[(j + 1) * n + i + 1] += A[(k + 2) * n + i + 1] * B[(j + 1) * n + k + 2];
//                 C[(j + 1) * n + i + 2] += A[(k + 2) * n + i + 2] * B[(j + 1) * n + k + 2];
//                 C[(j + 1) * n + i + 3] += A[(k + 2) * n + i + 3] * B[(j + 1) * n + k + 2];

//                 // vmlaq_laneq_u32(C1, A3, B1, 3);
//                 C[(j + 1) * n + i] += A[(k + 3) * n + i] * B[(j + 1) * n + k + 3];
//                 C[(j + 1) * n + i + 1] += A[(k + 3) * n + i + 1] * B[(j + 1) * n + k + 3];
//                 C[(j + 1) * n + i + 2] += A[(k + 3) * n + i + 2] * B[(j + 1) * n + k + 3];
//                 C[(j + 1) * n + i + 3] += A[(k + 3) * n + i + 3] * B[(j + 1) * n + k + 3];

//                 // vmlaq_laneq_u32(C2, A0, B2, 0);
//                 C[(j + 2) * n + i] += A[k * n + i] * B[(j + 2) * n + k];
//                 C[(j + 2) * n + i + 1] += A[k * n + i + 1] * B[(j + 2) * n + k];
//                 C[(j + 2) * n + i + 2] += A[k * n + i + 2] * B[(j + 2) * n + k];
//                 C[(j + 2) * n + i + 3] += A[k * n + i + 3] * B[(j + 2) * n + k];

//                 // vmlaq_laneq_u32(C2, A1, B2, 1);
//                 C[(j + 2) * n + i] += A[(k + 1) * n + i] * B[(j + 2) * n + k + 1];
//                 C[(j + 2) * n + i + 1] += A[(k + 1) * n + i + 1] * B[(j + 2) * n + k + 1];
//                 C[(j + 2) * n + i + 2] += A[(k + 1) * n + i + 2] * B[(j + 2) * n + k + 1];
//                 C[(j + 2) * n + i + 3] += A[(k + 1) * n + i + 3] * B[(j + 2) * n + k + 1];

//                 // vmlaq_laneq_u32(C2, A2, B2, 2);
//                 C[(j + 2) * n + i] += A[(k + 2) * n + i] * B[(j + 2) * n + k + 2];
//                 C[(j + 2) * n + i + 1] += A[(k + 2) * n + i + 1] * B[(j + 2) * n + k + 2];
//                 C[(j + 2) * n + i + 2] += A[(k + 2) * n + i + 2] * B[(j + 2) * n + k + 2];
//                 C[(j + 2) * n + i + 3] += A[(k + 2) * n + i + 3] * B[(j + 2) * n + k + 2];

//                 // vmlaq_laneq_u32(C2, A3, B2, 3);
//                 C[(j + 2) * n + i] += A[(k + 3) * n + i] * B[(j + 2) * n + k + 3];
//                 C[(j + 2) * n + i + 1] += A[(k + 3) * n + i + 1] * B[(j + 2) * n + k + 3];
//                 C[(j + 2) * n + i + 2] += A[(k + 3) * n + i + 2] * B[(j + 2) * n + k + 3];
//                 C[(j + 2) * n + i + 3] += A[(k + 3) * n + i + 3] * B[(j + 2) * n + k + 3];

//                 // vmlaq_laneq_u32(C3, A0, B3, 0);
//                 C[(j + 3) * n + i] += A[k * n + i] * B[(j + 3) * n + k];
//                 C[(j + 3) * n + i + 1] += A[k * n + i + 1] * B[(j + 3) * n + k];
//                 C[(j + 3) * n + i + 2] += A[k * n + i + 2] * B[(j + 3) * n + k];
//                 C[(j + 3) * n + i + 3] += A[k * n + i + 3] * B[(j + 3) * n + k];

//                 // vmlaq_laneq_u32(C3, A1, B3, 1);
//                 C[(j + 3) * n + i] += A[(k + 1) * n + i] * B[(j + 3) * n + k + 1];
//                 C[(j + 3) * n + i + 1] += A[(k + 1) * n + i + 1] * B[(j + 3) * n + k + 1];
//                 C[(j + 3) * n + i + 2] += A[(k + 1) * n + i + 2] * B[(j + 3) * n + k + 1];
//                 C[(j + 3) * n + i + 3] += A[(k + 1) * n + i + 3] * B[(j + 3) * n + k + 1];

//                 // vmlaq_laneq_u32(C3, A2, B3, 2);
//                 C[(j + 3) * n + i] += A[(k + 2) * n + i] * B[(j + 3) * n + k + 2];
//                 C[(j + 3) * n + i + 1] += A[(k + 2) * n + i + 1] * B[(j + 3) * n + k + 2];
//                 C[(j + 3) * n + i + 2] += A[(k + 2) * n + i + 2] * B[(j + 3) * n + k + 2];
//                 C[(j + 3) * n + i + 3] += A[(k + 2) * n + i + 3] * B[(j + 3) * n + k + 2];

//                 // vmlaq_laneq_u32(C3, A3, B3, 3);
//                 C[(j + 3) * n + i] += A[(k + 3) * n + i] * B[(j + 3) * n + k + 3];
//                 C[(j + 3) * n + i + 1] += A[(k + 3) * n + i + 1] * B[(j + 3) * n + k + 3];
//                 C[(j + 3) * n + i + 2] += A[(k + 3) * n + i + 2] * B[(j + 3) * n + k + 3];
//                 C[(j + 3) * n + i + 3] += A[(k + 3) * n + i + 3] * B[(j + 3) * n + k + 3];
//             }
//             for (std::size_t k = n / 4 * 4; k < n; k++) {
//                 C[j * n + i] += A[k * n + i] * B[j * n + k];
//                 C[j * n + i + 1] += A[k * n + i + 1] * B[j * n + k];
//                 C[j * n + i + 2] += A[k * n + i + 2] * B[j * n + k];
//                 C[j * n + i + 3] += A[k * n + i + 3] * B[j * n + k];

//                 C[(j + 1) * n + i] += A[k * n + i] * B[(j + 1) * n + k];
//                 C[(j + 1) * n + i + 1] += A[k * n + i + 1] * B[(j + 1) * n + k];
//                 C[(j + 1) * n + i + 2] += A[k * n + i + 2] * B[(j + 1) * n + k];
//                 C[(j + 1) * n + i + 3] += A[k * n + i + 3] * B[(j + 1) * n + k];

//                 C[(j + 2) * n + i] += A[k * n + i] * B[(j + 2) * n + k];
//                 C[(j + 2) * n + i + 1] += A[k * n + i + 1] * B[(j + 2) * n + k];
//                 C[(j + 2) * n + i + 2] += A[k * n + i + 2] * B[(j + 2) * n + k];
//                 C[(j + 2) * n + i + 3] += A[k * n + i + 3] * B[(j + 2) * n + k];

//                 C[(j + 3) * n + i] += A[k * n + i] * B[(j + 3) * n + k];
//                 C[(j + 3) * n + i + 1] += A[k * n + i + 1] * B[(j + 3) * n + k];
//                 C[(j + 3) * n + i + 2] += A[k * n + i + 2] * B[(j + 3) * n + k];
//                 C[(j + 3) * n + i + 3] += A[k * n + i + 3] * B[(j + 3) * n + k];
//             }
//         }
//         for (std::size_t j = n / 4 * 4; j < n; j++) {
//             for (std::size_t k = 0; k + 4 < n; k += 4) {
//                 // vmlaq_laneq_u32(C0, A0, B0, 0);
//                 C[j * n + i] += A[k * n + i] * B[j * n + k];
//                 C[j * n + i + 1] += A[k * n + i + 1] * B[j * n + k];
//                 C[j * n + i + 2] += A[k * n + i + 2] * B[j * n + k];
//                 C[j * n + i + 3] += A[k * n + i + 3] * B[j * n + k];

//                 // vmlaq_laneq_u32(C0, A1, B0, 1);
//                 C[j * n + i] += A[(k + 1) * n + i] * B[j * n + k + 1];
//                 C[j * n + i + 1] += A[(k + 1) * n + i + 1] * B[j * n + k + 1];
//                 C[j * n + i + 2] += A[(k + 1) * n + i + 2] * B[j * n + k + 1];
//                 C[j * n + i + 3] += A[(k + 1) * n + i + 3] * B[j * n + k + 1];

//                 // vmlaq_laneq_u32(C0, A2, B0, 2);
//                 C[j * n + i] += A[(k + 2) * n + i] * B[j * n + k + 2];
//                 C[j * n + i + 1] += A[(k + 2) * n + i + 1] * B[j * n + k + 2];
//                 C[j * n + i + 2] += A[(k + 2) * n + i + 2] * B[j * n + k + 2];
//                 C[j * n + i + 3] += A[(k + 2) * n + i + 3] * B[j * n + k + 2];

//                 // vmlaq_laneq_u32(C0, A3, B0, 3);
//                 C[j * n + i] += A[(k + 3) * n + i] * B[j * n + k + 3];
//                 C[j * n + i + 1] += A[(k + 3) * n + i + 1] * B[j * n + k + 3];
//                 C[j * n + i + 2] += A[(k + 3) * n + i + 2] * B[j * n + k + 3];
//                 C[j * n + i + 3] += A[(k + 3) * n + i + 3] * B[j * n + k + 3];
//             }
//             for (std::size_t k = n / 4 * 4; k < n; k++) {
//                 C[j * n + i] += A[k * n + i] * B[j * n + k];
//                 C[j * n + i + 1] += A[k * n + i + 1] * B[j * n + k];
//                 C[j * n + i + 2] += A[k * n + i + 2] * B[j * n + k];
//                 C[j * n + i + 3] += A[k * n + i + 3] * B[j * n + k];
//             }
//         }
//     }
//     for (std::size_t i = n / 4 * 4; i < n; i++) {
//         for (std::size_t j = 0; j + 4 < n; j += 4) {
//             for (std::size_t k = 0; k + 4 < n; k += 4) {
//                 C[j * n + i] += A[k * n + i] * B[j * n + k];
//                 C[j * n + i] += A[(k + 1) * n + i] * B[j * n + k + 1];
//                 C[j * n + i] += A[(k + 2) * n + i] * B[j * n + k + 2];
//                 C[j * n + i] += A[(k + 3) * n + i] * B[j * n + k + 3];

//                 C[(j + 1) * n + i] += A[k * n + i] * B[(j + 1) * n + k];
//                 C[(j + 1) * n + i] += A[(k + 1) * n + i] * B[(j + 1) * n + k + 1];
//                 C[(j + 1) * n + i] += A[(k + 2) * n + i] * B[(j + 1) * n + k + 2];
//                 C[(j + 1) * n + i] += A[(k + 3) * n + i] * B[(j + 1) * n + k + 3];

//                 C[(j + 2) * n + i] += A[k * n + i] * B[(j + 2) * n + k];
//                 C[(j + 2) * n + i] += A[(k + 1) * n + i] * B[(j + 2) * n + k + 1];
//                 C[(j + 2) * n + i] += A[(k + 2) * n + i] * B[(j + 2) * n + k + 2];
//                 C[(j + 2) * n + i] += A[(k + 3) * n + i] * B[(j + 2) * n + k + 3];

//                 C[(j + 3) * n + i] += A[k * n + i] * B[(j + 3) * n + k];
//                 C[(j + 3) * n + i] += A[(k + 1) * n + i] * B[(j + 3) * n + k + 1];
//                 C[(j + 3) * n + i] += A[(k + 2) * n + i] * B[(j + 3) * n + k + 2];
//                 C[(j + 3) * n + i] += A[(k + 3) * n + i] * B[(j + 3) * n + k + 3];
//             }
//             for (std::size_t k = n / 4 * 4; k < n; k++) {
//                 C[j * n + i] += A[k * n + i] * B[j * n + k];
//                 C[(j + 1) * n + i] += A[k * n + i] * B[(j + 1) * n + k];
//                 C[(j + 2) * n + i] += A[k * n + i] * B[(j + 2) * n + k];
//                 C[(j + 3) * n + i] += A[k * n + i] * B[(j + 3) * n + k];
//             }
//         }
//         for (std::size_t j = n / 4 * 4; j < n; j++) {
//             for (std::size_t k = 0; k + 4 < n; k += 4) {
//                 C[j * n + i] += A[k * n + i] * B[j * n + k];
//                 C[j * n + i] += A[(k + 1) * n + i] * B[j * n + k + 1];
//                 C[j * n + i] += A[(k + 2) * n + i] * B[j * n + k + 2];
//                 C[j * n + i] += A[(k + 3) * n + i] * B[j * n + k + 3];
//             }
//             for (std::size_t k = n / 4 * 4; k < n; k++) {
//                 C[j * n + i] += A[k * n + i] * B[j * n + k];
//             }
//         }
//     }
// }
#endif
