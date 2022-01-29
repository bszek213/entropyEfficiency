#include <iostream>
#include <filesystem>
#include <sstream>
#include <algorithm>   
#include <vector> 
#include <math.h>
#include <helper/sampenZero.h>
//#include "sampenZero.h""
using namespace cv;
/*double Entropy::minVal(double *inputData,int size)
{   
    double min = inputData[0];
    int min_index = 0;
    for (int i = 0; i < size; i++)
    {
        if (inputData[i] < min)
        {
            min = inputData[i];
            min_index = i;
        }
    }
    std::cout<<" The index of the smallest area is: "<<min_index<<endl;
    return min;
}*/

void Entropy::setMaxSize(const int inputSize){
    maxSize = inputSize; 
}
void Entropy::setArray(std::vector<double> inputDataArr){
    data = inputDataArr;
}

void Entropy::downSample(int p, int q)
{ // p is the original sampling frequency, q is the new sampling frequency
    int freqRatio = p / q;
    int dataNewLength=0;
    for (int i = 0; i < maxSize / freqRatio; i++)
    {
        if (i <= maxSize)
        {
            data[i] = data[i + freqRatio];
            ++dataNewLength;
        }
    }
    newMaxSize = dataNewLength;
}

double Entropy::sampleEntropy(int m, int newSampFreq, float r, int oldsampFreq, bool DS)
{
    /* checks for correct inputs */
    /*assert(data != NULL);
    assert(m > 1);
    assert(newSampFreq > 0);
    assert(oldsampFreq > 0);*/
    /* apply lag */
    if (DS)
    {
        downSample(oldsampFreq, newSampFreq);
    }
    else
    {
        newMaxSize = maxSize;
    }
    /*Getting subarrays*/
    //int N = sizeof(data);
    int N = newMaxSize;
    int *result = new int[2];
    /* This section comes from Chesnokov Yuriy */
    int Cm = 0, Cm1 = 0;
    float err = 0.0, sum = 0.0;
    Scalar mean, stddev;
    meanStdDev ( data, mean, stddev );
    err = stddev[0] * r;
    int location;
    for (unsigned int i = 0; i < N - (m + 1) + 1; i++)
    {
        for (unsigned int j = i + 1; j < N - (m + 1) + 1; j++)
        {
            std::vector<double> temp_m;
            std::vector<double> temp_m1;
            std::vector<double>::iterator distResult;
            //m - length series
            for (unsigned int k = 0; k < m; k++)
            {
                temp_m.push_back(abs(data[i + k] - data[j + k])); 
               
                            
            }
            distResult = std::max_element(temp_m.begin(), temp_m.end());
            location = std::distance(temp_m.begin(), distResult);
            if(temp_m[location] < err){
                Cm++;
            }
            //m+1 - length series
            for (unsigned int z = 0; z < m+1; z++)
            {
                temp_m1.push_back(abs(data[i + z] - data[j + z])); 
                 //std::cout << "Temp Value" << z << " " << temp_m1[z] << std::endl;          
            }
            distResult = std::max_element(temp_m1.begin(), temp_m1.end());
            location = std::distance(temp_m1.begin(), distResult);
            //std::cout << "Temp max Location: " << temp_m1[location] << " The std: " <<  err <<std::endl;
            //std::cout << "Temp Value Location Iterator" << " " << location << std::endl;  
            if(temp_m1[location] < err){
                Cm1++;
            }           
        }
    }
    //std::cout << Cm << ": CM, " << Cm1 << ": CM1" << std::endl;
    if (Cm > 0 && Cm1 > 0)
        return abs(log((double)Cm/(double)Cm1));
    else
        return 0.0;
}
//To do: edit the sample entroy equation and add in the multiscale entropy
double Entropy::approxEntropy(int m,  float r){
        int Cm = 0, Cm1 = 0;
        double err = 0.0, sum = 0.0;
        newMaxSize = newMaxSize;
        int N = newMaxSize;
        Scalar mean, stddev;
        meanStdDev ( data, mean, stddev );
        err = stddev[0] * r;

        for (unsigned int i = 0; i < N - (m + 1) + 1; i++) {
                Cm = Cm1 = 0;
                for (unsigned int j = 0; j < N - (m + 1) + 1; j++) {
                        bool eq = true;
                        //m - length series
                        for (unsigned int k = 0; k < m; k++) {
                                if (abs(data[i+k] - data[j+k]) > err) {
                                        eq = false;
                                        break;
                                }
                        }
                        if (eq) Cm++;

                        //m+1 - length series
                        int k = m;
                        if (eq && abs(data[i+k] - data[j+k]) <= err)
                                Cm1++;
                }

                if (Cm > 0 && Cm1 > 0)
                        sum += log((double)Cm / (double)Cm1);                
        }

        return sum / (double)(N - m);
}

double Entropy::multiscaleEntropy(std::vector<int> scales, float r){
std::vector<float> sampenArr;
    std::vector<double> copScale;
    for (int i = 0; i < scales.size(); i++){
        float j = trunc(maxSize/scales[i]);
            for (int m = 1; m < j; m++){
                std::vector<double> copScale = mean(data[m-1*i+1:m*i]);
            }
        double sampenTemp = sampleEntropy(2,10,0.2,1000,false); 
        sampenArr.push_back(sampenTemp);
    }
}

void Entropy::printArray(){
    for(int i = 0; i < newMaxSize; i++){
        std::cout << data[i] << std::endl;
    }
}

   /* creating the maximum absolute distance for m */
 /*    double *temp = new double[(N - (m)) * (N - (m)) * m];
    double *temp2 = new double[(N - (m + 1)) * (N - (m + 1)) * m];
    /*unsigned long long int append = 0;
    unsigned long long int append2 = 0;
    for (unsigned int i = 0; i < N - (m + 1) + 1; i++)
    {
        for (unsigned int j = i + 1; j < N - (m + 1) + 1; j++)
        {
            //m - length series
            for (unsigned int k = 0; k < m; k++)
            {
                temp[append] = std::abs(data[i + k] - data[j + k]);
                append++;
            }
            // m+1 -length series
            int k = m;
            temp2[append2] = std::abs(data[i + k] - data[j + k]);
            append2++;
        }
    }*/
    /* Calculate HistCounts Now
    double min, max;
    cv::Mat srcMat = cv::Mat(1, append, CV_32FC1, temp2);
    cv::minMaxLoc(srcMat, &min, &max);
    int histSize = 2048;
    float range[] = {min, max};
    const float *histRange = {range};
    bool uniform = true;
    bool accumulate = false;
    cv::Mat histOut;
    cv::calcHist(&srcMat, 1, 0, Mat(), histOut, 1, &histSize, &histRange, uniform, accumulate);
    std::cout << histOut << std::endl;
    */
