#ifndef _XXNACCI_NEON_
#define _XXNACCI_NEON_

#include <arm_neon.h>

void neon_mat_mul(uint32_t* C, uint32_t* A, uint32_t* B, size_t n) {
    uint32x4_t A0;
    uint32x4_t A1;
    uint32x4_t A2;
    uint32x4_t A3;

    uint32x4_t B0;
    uint32x4_t B1;
    uint32x4_t B2;
    uint32x4_t B3;

    uint32x4_t C0;
    uint32x4_t C1;
    uint32x4_t C2;
    uint32x4_t C3;

    for (size_t i = 0; i + 3 < n; i += 4) {
        for (size_t j = 0; j + 3 < n; j += 4) {
            for (size_t k = 0; k + 3 < n; k += 4) {
                A0 = vld1q_u32(A + k * n + i);
                A1 = vld1q_u32(A + (k + 1) * n + i);
                A2 = vld1q_u32(A + (k + 2) * n + i);
                A3 = vld1q_u32(A + (k + 3) * n + i);

                B0 = vld1q_u32(B + j * n + k);
                C0 = vld1q_u32(C + j * n + i);

                C0 = vmlaq_laneq_u32(C0, A0, B0, 0);
                C0 = vmlaq_laneq_u32(C0, A1, B0, 1);
                C0 = vmlaq_laneq_u32(C0, A2, B0, 2);
                C0 = vmlaq_laneq_u32(C0, A3, B0, 3);
                vst1q_u32(C + j * n + i, C0);

                B1 = vld1q_u32(B + (j + 1) * n + k);
                C1 = vld1q_u32(C + (j + 1) * n + i);

                C1 = vmlaq_laneq_u32(C1, A0, B1, 0);
                C1 = vmlaq_laneq_u32(C1, A1, B1, 1);
                C1 = vmlaq_laneq_u32(C1, A2, B1, 2);
                C1 = vmlaq_laneq_u32(C1, A3, B1, 3);
                vst1q_u32(C + (j + 1) * n + i, C1);

                B2 = vld1q_u32(B + (j + 2) * n + k);
                C2 = vld1q_u32(C + (j + 2) * n + i);

                C2 = vmlaq_laneq_u32(C2, A0, B2, 0);
                C2 = vmlaq_laneq_u32(C2, A1, B2, 1);
                C2 = vmlaq_laneq_u32(C2, A2, B2, 2);
                C2 = vmlaq_laneq_u32(C2, A3, B2, 3);
                vst1q_u32(C + (j + 2) * n + i, C2);

                B3 = vld1q_u32(B + (j + 3) * n + k);
                C3 = vld1q_u32(C + (j + 3) * n + i);

                C3 = vmlaq_laneq_u32(C3, A0, B3, 0);
                C3 = vmlaq_laneq_u32(C3, A1, B3, 1);
                C3 = vmlaq_laneq_u32(C3, A2, B3, 2);
                C3 = vmlaq_laneq_u32(C3, A3, B3, 3);
                vst1q_u32(C + (j + 3) * n + i, C3);
            }
            for (size_t k = n / 4 * 4; k < n; k++) {
                A0 = vld1q_u32(A + k * n + i);

                B0 = vld1q_u32(B + j * n + k);
                C0 = vld1q_u32(C + j * n + i);
                C0 = vmlaq_laneq_u32(C0, A0, B0, 0);
                vst1q_u32(C + j * n + i, C0);

                B1 = vld1q_u32(B + (j + 1) * n + k);
                C1 = vld1q_u32(C + (j + 1) * n + i);
                C1 = vmlaq_laneq_u32(C1, A0, B1, 0);
                vst1q_u32(C + (j + 1) * n + i, C1);

                B2 = vld1q_u32(B + (j + 2) * n + k);
                C2 = vld1q_u32(C + (j + 2) * n + i);
                C2 = vmlaq_laneq_u32(C2, A0, B2, 0);
                vst1q_u32(C + (j + 2) * n + i, C2);

                B3 = vld1q_u32(B + (j + 3) * n + k);
                C3 = vld1q_u32(C + (j + 3) * n + i);
                C3 = vmlaq_laneq_u32(C3, A0, B3, 0);
                vst1q_u32(C + (j + 3) * n + i, C3);
            }
        }
        for (size_t j = n / 4 * 4; j < n; j++) {
            for (size_t k = 0; k + 3 < n; k += 4) {
                A0 = vld1q_u32(A + k * n + i);
                B0 = vld1q_u32(B + j * n + k);
                C0 = vld1q_u32(C + j * n + i);
                C0 = vmlaq_laneq_u32(C0, A0, B0, 0);

                A1 = vld1q_u32(A + (k + 1) * n + i);
                C0 = vmlaq_laneq_u32(C0, A1, B0, 1);

                A2 = vld1q_u32(A + (k + 2) * n + i);
                C0 = vmlaq_laneq_u32(C0, A2, B0, 2);

                A3 = vld1q_u32(A + (k + 3) * n + i);
                C0 = vmlaq_laneq_u32(C0, A3, B0, 3);
                vst1q_u32(C + j * n + i, C0);
            }
            for (size_t k = n / 4 * 4; k < n; k++) {
                C[j * n + i] += A[k * n + i] * B[j * n + k];
                C[j * n + i + 1] += A[k * n + i + 1] * B[j * n + k];
                C[j * n + i + 2] += A[k * n + i + 2] * B[j * n + k];
                C[j * n + i + 3] += A[k * n + i + 3] * B[j * n + k];
            }
        }
    }
    for (size_t i = n / 4 * 4; i < n; i++) {
        for (size_t j = 0; j + 3 < n; j += 4) {
            for (size_t k = 0; k + 3 < n; k += 4) {
                C[j * n + i] += A[k * n + i] * B[j * n + k];
                C[j * n + i] += A[(k + 1) * n + i] * B[j * n + k + 1];
                C[j * n + i] += A[(k + 2) * n + i] * B[j * n + k + 2];
                C[j * n + i] += A[(k + 3) * n + i] * B[j * n + k + 3];

                C[(j + 1) * n + i] += A[k * n + i] * B[(j + 1) * n + k];
                C[(j + 1) * n + i] += A[(k + 1) * n + i] * B[(j + 1) * n + k + 1];
                C[(j + 1) * n + i] += A[(k + 2) * n + i] * B[(j + 1) * n + k + 2];
                C[(j + 1) * n + i] += A[(k + 3) * n + i] * B[(j + 1) * n + k + 3];

                C[(j + 2) * n + i] += A[k * n + i] * B[(j + 2) * n + k];
                C[(j + 2) * n + i] += A[(k + 1) * n + i] * B[(j + 2) * n + k + 1];
                C[(j + 2) * n + i] += A[(k + 2) * n + i] * B[(j + 2) * n + k + 2];
                C[(j + 2) * n + i] += A[(k + 3) * n + i] * B[(j + 2) * n + k + 3];

                C[(j + 3) * n + i] += A[k * n + i] * B[(j + 3) * n + k];
                C[(j + 3) * n + i] += A[(k + 1) * n + i] * B[(j + 3) * n + k + 1];
                C[(j + 3) * n + i] += A[(k + 2) * n + i] * B[(j + 3) * n + k + 2];
                C[(j + 3) * n + i] += A[(k + 3) * n + i] * B[(j + 3) * n + k + 3];
            }
            for (size_t k = n / 4 * 4; k < n; k++) {
                C[j * n + i] += A[k * n + i] * B[j * n + k];
                C[(j + 1) * n + i] += A[k * n + i] * B[(j + 1) * n + k];
                C[(j + 2) * n + i] += A[k * n + i] * B[(j + 2) * n + k];
                C[(j + 3) * n + i] += A[k * n + i] * B[(j + 3) * n + k];
            }
        }
        for (size_t j = n / 4 * 4; j < n; j++) {
            for (size_t k = 0; k + 3 < n; k += 4) {
                C[j * n + i] += A[k * n + i] * B[j * n + k];
                C[j * n + i] += A[(k + 1) * n + i] * B[j * n + k + 1];
                C[j * n + i] += A[(k + 2) * n + i] * B[j * n + k + 2];
                C[j * n + i] += A[(k + 3) * n + i] * B[j * n + k + 3];
            }
            for (size_t k = n / 4 * 4; k < n; k++) {
                C[j * n + i] += A[k * n + i] * B[j * n + k];
            }
        }
    }
}
#endif
