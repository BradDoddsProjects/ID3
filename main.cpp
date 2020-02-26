#include "header.h"

using namespace std;

int main() {

    const string FILE = "data.txt";
    ID3 ID3;


    //Read data file and recognize attributes and values
    ID3.readFile(FILE);
    ID3.recognizeFeatures();
    ID3.output_recognizedFeatures();

    //Convert original data set to binary for manipulation
    ID3.convertBinaryVector();
    ID3.output_initialDataVector();
    ID3.output_binaryVector();

    //Calculations
    ID3.entropy();
    ID3.information_gain();


    return 0;
}