#ifndef __IMAGE__
#define __IMAGE__

/**
 * @brief Type defining 2D image
 * 
 * @tparam ElementType  type of each element/pixel
 * @tparam WIDTH        width of image
 * @tparam HEIGHT       height of image
 */
template<typename ElementType, int WIDTH, int HEIGHT>
struct Image
{
    // Element type
    using value_type = ElementType;
    // Image width
    const int width{WIDTH};
    // Image height
    const int height{HEIGHT};
    // Image data
    ElementType data[WIDTH*HEIGHT];
};

#endif