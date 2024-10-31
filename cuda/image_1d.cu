#include "image.hpp"

/**
 * @brief kernel that squares each element of array
 * 
 * @param arr array pointer
 * @param arrSize array size
 */
__global__ void squareArray(float* arr, int arrSize)
{
    int i = blockDim.x * blockIdx.x + threadIdx.x;
    if (i < arrSize)
    {
        const float tmp = arr[i];
        arr[i] = tmp * tmp;
    }
}

// Image initialization 
const int width = 1024;
const int height = 1024;
using Image2D = Image<float, width, height>;
Image2D hostImage;

int main()
{
    // Fill image 
    for (int r =0; r < height; ++r)
    {
        for (int c =0; c < width; ++c)
        {
            hostImage.data[r*width+c] = (r*width+c)/1024.f;
        }
    }

    // Allocate memory for image on device
    Image2D::value_type* deviceImage;
    cudaMalloc(&deviceImage, width*height*sizeof(Image2D::value_type));

    // Copy memory from host memory to device memory
    cudaMemcpy(deviceImage, hostImage.data, width*height*sizeof(Image2D::value_type), cudaMemcpyHostToDevice);

    // Invoke kernel
    int threadsPerblock = 256;
    int blocksPerGrid = ( width*height + threadsPerblock  - 1) / threadsPerblock;
    squareArray<<<blocksPerGrid, threadsPerblock>>>(deviceImage, width*height);

    // Copy memory from device memory to host memory
    cudaMemcpy(hostImage.data, deviceImage, width*height*sizeof(Image2D::value_type), cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(deviceImage);

    return 0;
}