#ifndef __TYPES__
#define __TYPES__

#include <memory>
#include <algorithm>

/**
 * @brief Type definition of matrix
 * 
 */
struct Matrix
{
    // Matrix width
    int width;
    // Matrix height
    int height;
    // Matrix data
    std::unique_ptr<float> data;

    /**
     * @brief Construct a new Matrix object
     * 
     * @param w  width of matrix
     * @param h  height of matrix
     */
    Matrix(int w, int h): width(w), height(h)
    {
        data.reset(new float[width*height]);
        std::fill(data.get(), data.get() + width * height, 0.0f);
    }

    /**
     * @brief Default constructor
     * 
     */
    Matrix()
    {
        data.reset(nullptr);
        width = height = 0;
    }
};

#endif