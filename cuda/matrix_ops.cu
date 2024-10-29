#include <cassert>
#include <iostream>
#include <cmath>

#include "matrix.hpp"

/**
 * @brief kernel that performs matrix multiplication, C = matMul(A, B), in parallel
 * 
 * @param A array pointer of 2D matrix A
 * @param B array pointer of 2D matrix B
 * @param C array pointer of 2D matrix C
 * @param w_a width of matrix A
 * @param w_c width of matix C
 * @param h_c height of matrix C
 */
__global__ void matMulKernel(float* A, float* B, float* C, int w_a, int w_c, int h_c)
{
    int col = blockDim.x * blockIdx.x + threadIdx.x;
    int row = blockDim.y * blockIdx.y + threadIdx.y;
    if (col < w_c && row < h_c)
    {
        for (int i = 0; i < w_a; ++i)
        {
            C[row*w_c+col] += ( A[row*w_a+i] * B[i*h_c + col] );
        }
    }
}

/**
 * @brief Kernel performing elementwise sigmoid
 * 
 * @param A matrix A
 * @param w width of matrix 
 * @param h height of matrix
 */
__global__ void sigmoidKernel(float* A, int w, int h)
{
    int col = blockDim.x * blockIdx.x + threadIdx.x;
    int row = blockDim.y * blockIdx.y + threadIdx.y;
    if (col < w && row < h)
    {
        int index = row*w + col;
        A[index] = 1.0f / (1.0f + expf(-A[index]));
    }
}


/**
 * @brief performs matrix multiplication and elementwise sigmoid
 * 
 * @param A  matrix A
 * @param B  matrix B
 * @param C  matrix C
 */
void matrixOperations(const Matrix& A, const Matrix& B, Matrix& C)
{
    // Allocate memory for matrix A, b and C on device
    float* A_d;
    float* B_d;
    float* C_d;
    cudaMalloc(&A_d, A.width*A.height*sizeof(float));
    cudaMalloc(&B_d, B.width*B.height*sizeof(float));
    cudaMalloc(&C_d, C.width*C.height*sizeof(float));
    cudaMemset(C_d, 0.0f, C.width*C.height*sizeof(float));

    // Copy data from host memory to device memory
    cudaMemcpy(A_d, A.data.get(), A.width*A.height*sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(B_d, B.data.get(), B.width*B.height*sizeof(float), cudaMemcpyHostToDevice);

    // Invoke kernels
    dim3 threadsPerblock(32, 16);
    dim3 blocksPerGrid( (C.width + threadsPerblock.x - 1) / threadsPerblock.x, 
    (C.height + threadsPerblock.y - 1) / threadsPerblock.y );

    // Launch matMulKernel 
    matMulKernel<<<blocksPerGrid, threadsPerblock>>>(A_d, B_d, C_d, A.width, C.width, C.height);

    // Launch sigmoidKernel
    sigmoidKernel<<<blocksPerGrid, threadsPerblock>>>(C_d, C.width, C.height);

    // Copy memory from device memory to host memory
    cudaMemcpy(C.data.get(), C_d, C.width*C.height*sizeof(float), cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(A_d);
    cudaFree(B_d);
    cudaFree(C_d);
}

/**
 * @brief performs matrix multiplication C = matMul(A, B) and elementwise sigmoid
 * 
 * @param A matrix A
 * @param B matrix B
 * @return Matrix C
 */
Matrix matrixOperations(const Matrix& A, const Matrix& B)
{
    if (A.width != B.height )
    {
        return Matrix();
    }
    // Initialize matrix C
    Matrix C(B.width, A.height);
    matrixOperations(A, B, C);
    return C;
}

/**
 * @brief Helper function to check equality within two decimal precision
 * 
 * @param a first float value
 * @param b second float value
 * @param precision precision 
 * @return true if precision met
 */
bool isApproxEqual(float a, float b, float precision = 0.01f) {
    return std::fabs(a - b) < precision;
}

int main()
{
    // Initialize matrix A 
    Matrix A(3, 4);
    A.data.get()[0] = 0.1f;
    A.data.get()[1] = 0.2f;
    A.data.get()[2] = 0.3f;
    A.data.get()[3] = 0.4f;
    A.data.get()[4] = 0.5f;
    A.data.get()[5] = 0.6f;
    A.data.get()[6] = 0.7f;
    A.data.get()[7] = 0.8f;
    A.data.get()[8] = 0.9f;
    A.data.get()[9] = 0.10f;
    A.data.get()[10] = 0.11f;
    A.data.get()[11] = 0.12f;

    // Initialize matrix B
    Matrix B(2, 3);
    B.data.get()[0] = 0.1f;
    B.data.get()[1] = 0.2f;
    B.data.get()[2] = 0.3f;
    B.data.get()[3] = 0.4f;
    B.data.get()[4] = 0.5f;
    B.data.get()[5] = 0.6f;

    // Matrix multiplication
    auto C = matrixOperations(A, B);

    // Check the results
    assert( isApproxEqual(C.data.get()[0], 0.55f) );
    assert( isApproxEqual(C.data.get()[1], 0.56f) );
    assert( isApproxEqual(C.data.get()[2], 0.62f) );
    assert( isApproxEqual(C.data.get()[3], 0.65f) );
    assert( isApproxEqual(C.data.get()[4], 0.68f) );
    assert( isApproxEqual(C.data.get()[5], 0.73f) );
    assert( isApproxEqual(C.data.get()[6], 0.52f) );
    assert( isApproxEqual(C.data.get()[7], 0.53f) );

    std::cout << "All tests passed!" << std::endl;

    return 0;
}