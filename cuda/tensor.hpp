#ifndef __TENSOR__
#define __TENSOR__

/**
 * @brief Type defining 2D Tensor
 * 
 * @tparam ElementType  type of each element/pixel
 * @tparam WIDTH        width of Tensor
 * @tparam HEIGHT       height of Tensor
 * @tparam CHANNELS     num of channels of Tensor
 * @tparam BATCHES      num of batches of Tensor
 */
template<typename ElementType, int WIDTH, int HEIGHT, int CHANNELS, int BATCHES>
struct Tensor
{
    // Element type
    using value_type = ElementType;
    // Tensor width
    const int width{WIDTH};
    // Tensor height
    const int height{HEIGHT};
    // Tensor width
    const int channels{CHANNELS};
    // Tensor height
    const int batches{BATCHES};
    // Tensor data
    ElementType data[WIDTH*HEIGHT*CHANNELS*BATCHES];
};

#endif