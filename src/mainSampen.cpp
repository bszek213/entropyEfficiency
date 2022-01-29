#include <iostream>
#include <filesystem>
#include <sstream>
#include <helper/sampenZero.h>
#include <vector>
#include <fstream>
namespace fs = std::filesystem;
int main()
{
    std::string inputString1 = "/home/bszekely/Desktop/ProjectsResearch/Entropy/temp_copx.csv";
    std::ifstream fin;
    float values;
    std::vector<double> input;
    std::string line;
    int num = 0;
    fin.open(inputString1);
    Entropy sampEn;
    while (!fin.eof())
    {
        getline(fin, line); // discard only include this if there are text headers
        //std::cout << line << std::endl;
        values = strtod(line.c_str(), nullptr);
        //std::cout << values << std::endl;
        input.push_back(values);
        num++; //will this always overestimate the number of elements by 1?
    }
    double *arrInput = &input[0];
    sampEn.setMaxSize(num);
    sampEn.setArray(input);
    double entropyValue = sampEn.sampleEntropy(2,10,0.2,1000,false);
    double apenValue = sampEn.approxEntropy(2,0.2);
    std::cout << "sample entropy value:  " << entropyValue << std::endl;
    std::cout << "approximate entropy value: " << apenValue << std::endl;
    //write entropy value to file
    std::ofstream fout;
    fout.open("entropyOutfile.txt");
    for (int i = 0; i < 1; i++){
        fout << entropyValue;
    }
    fout.close();

    return 0;
}


    /*std::ifstream fin;
    std::string line;
    float values;
    int num = 0;
    std::string::size_type sz;
    std::vector<double> input;
    for (const auto &entry : fs::directory_iterator(inputString1))
    {
        Entropy sampEn;
        auto file = entry.path();
        std::cout << entry.path() << std::endl;
        fin.open(file);
        while (!fin.eof())
        {
            getline(fin, line); // discard only include this if there are text headers
            values = strtod(line.c_str(), NULL);
            //std::cout << values << std::endl;
            input.push_back(values);
            num++; //will this always overestimate the number of elements by 1?
        }
        std::cout << num << std::endl;
        double *arrInput = &input[0];
        sampEn.setMaxSize(num);
        sampEn.setArray(arrInput);
        double entropyValue = sampEn.sampenZero(2,10,1000,true);
    }*/
