#ifndef SAMPEN_ZERO
#define SAMPEN_ZERO
#include <assert.h> 
#include <vector>
#include <opencv2/opencv.hpp>
#include <iostream>

class Entropy
{
public:
    double sampleEntropy(int dim, int newSampFreq,float r,int oldsampeFreq,bool DS);
    double approxEntropy(int dim, float r);
    double multiscaleEntropy(std::vector<int> scales, float r);
    void downSample(int numerator, int denominator);
    int getDim() const;
    int getLag() const;
    void setDim(const int dim);
    void setOld(const int oldSamp);
    void setNew(const int newSamp);
    void setArray(std::vector<double> inputDataArr);
    void setMaxSize(const int inputSize);
    double calculateSD();
    void printArray();
    /*double minVal(double* inputData,int size);
    double maxVal(double* inputData,int size);*/
private:
    int dim;
    int newSampFreq;
    int oldsampFreq;
    std::vector<double> data;
    std::vector<double> copScale;
    int maxSize;
    int newMaxSize;
};
#endif //SAMPEN_ZERO
