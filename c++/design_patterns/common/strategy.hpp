//Strategy Pattern
//Purpose: Allows selecting an algorithm’s behavior at runtime.
//
//Use case: Sorting algorithms, different payment methods in e-commerce, or AI decision trees.
//
//Benefit: Makes algorithms interchangeable and avoids hardcoding logic.
#include <iostream>
#include <string>
#include <memory>

class CompressionStrategy{
public:
    virtual void compress() = 0;
};

class Compressor{
private:
    std::unique_ptr<CompressionStrategy> m_compressor;
public:
    Compressor(std::unique_ptr<CompressionStrategy>&& compressor): m_compressor(std::move(compressor)){}
    void compress()
    {
        m_compressor.get()->compress();
    }
};

class ZipCopression: public CompressionStrategy{
public:
    virtual void compress() override
    {
        std::cout<<"compressed using zip\n";
    }
};

class RARCompression: public CompressionStrategy{
public:
    virtual void compress() override
    {
       std::cout<<"compressed using rar\n"; 
    }
};

int main()
{
    auto compreesor1 = Compressor(std::unique_ptr<CompressionStrategy>(new ZipCopression()));
    auto compreesor2 = Compressor(std::unique_ptr<CompressionStrategy>(new RARCompression()));
    compreesor1.compress();
    compreesor2.compress();
    return 0;
}