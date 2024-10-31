#include "tensor.hpp"

/**
 * @brief kernel that squares each element of array representing 4D image (bxwxhxc)
 * 
 * @param arr array pointer
 * @param arrSize array size
 */
__global__ void square2DMatrix(float* matrix, int width, int height, int channels, int batchSize)
{
    int col = blockDim.x * blockIdx.x + threadIdx.x;
    int row = blockDim.y * blockIdx.y + threadIdx.y;
    // Number of threads in z dim is equal to batchSize*channels
    int ch = (blockDim.z * blockIdx.z + threadIdx.z) / batchSize;
    int batch = (blockDim.z * blockIdx.z + threadIdx.z) % batchSize;  

    if (col < width && row < height && ch < channels && batch < batchSize)
    {
        int index = batch*channels*height*wight + ch*row*width + row*width + col;
        matrix[index] *= matrix[index];
    }
}

// Image initialization 
const int width = 1024;
const int height = 1024;
const int channels = 3;
const int batches = 4;
using Image4D = Tenosr<float, width, height, channels, batches>;
Image4D hostImage;

int main()
{
    // Fill image 
    for (int b=0; b < batches; ++b)
    {
        for (int ch=0; ch < channels; ++ch)
        {
            for (int r =0; r < height; ++r)
            {
                for (int c =0; c < width; ++c)
                {
                    hostImage.data[b*channels*width*height + ch*width*height + r*width + c] = 1/1024.f;
                }
            }
        }
    }

    // Allocate memory for image on device
    Image4D::value_type* deviceImage;
    cudaMalloc(&deviceImage, width*height*channels*batches*sizeof(Image4D::value_type));

    // Copy memory from host memory to device memory
    cudaMemcpy(deviceImage, hostImage.data, width*height*channels*batches*sizeof(Image4D::value_type), cudaMemcpyHostToDevice);

    1024x1024x3
    widthxheightxchannel
    batchxheightxwidthxchannel

    // Invoke kernel
    dim3 threadsPerblock(16, 16, 1);
    dim3 blocksPerGrid( (width + threadsPerblock.x - 1) / threadsPerblock.x, 
    (height + threadsPerblock.y - 1) / threadsPerblock.y, (channels * batches + threadsPerblock.z - 1) / threadsPerblock.z);
    square2DMatrix<<<blocksPerGrid, threadsPerblock>>>(deviceImage, width, height, channels, batches);

    // Copy memory from device memory to host memory 
    cudaMemcpy(hostImage.data, deviceImage, width*height*channels*batches*sizeof(Image4D::value_type), cudaMemcpyDeviceToHost);

    // Free device memory
    cudaFree(deviceImage);

    return 0;
}