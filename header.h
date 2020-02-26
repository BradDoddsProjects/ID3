#ifndef PROJECT1_HEADER_H
#define PROJECT1_HEADER_H


#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>

using namespace std;




class ID3 {


public:


    void information_gain() {

        double binary_one_count = 0.0;
        double binary_zero_count = 0.0;
        double possible_values_0 = 0.0;
        double possible_values_1 = 0.0;
        double entropy1 = 0.0;
        double entropy0 = 0.0;
        double match1 = 0.0;
        double match0 = 0.0;
        double temp1 = 0.0;
        double temp0 = 0.0;
        double ig = 0.0;


        cout << "\nINFORMATION GAIN" << endl;

        for (int j = 0; j < binaryVectorData[0].size(); j++) {

            for (int i = 0; i < binaryVectorData.size(); i++) {


                //cout << binaryVectorData[i][j] << " ";

                if(binaryVectorData[i][j] == 1){
                    binary_one_count++;
                }else {
                    binary_zero_count++;
                }


             }

            possible_values_0 = binary_zero_count / totalDataSets;
            possible_values_1 = binary_one_count / totalDataSets;

            match0 = check_events(j, 0);
            match1 = check_events(j, 1);

            temp1 = binary_one_count - match1;
            temp0 = binary_zero_count - match0;

            if(temp1 == 0){
                entropy1 = log2(match1/binary_one_count) * match1/binary_one_count;
            }else {
                entropy1 = -((log2(match1/binary_one_count) * match1/binary_one_count) + (log2(temp1/binary_one_count) * temp1/binary_one_count));
            }

            if(temp0 == 0){
                entropy0 = (log2(match0/binary_zero_count) * match0/binary_zero_count);
            }else {
                entropy0 = -((log2(match0/binary_zero_count) * match0/binary_zero_count) + (log2(temp0/binary_zero_count) * temp0/binary_zero_count));
            }

            ig = entropyValue - possible_values_1 * entropy1 - possible_values_0 * entropy0;



            cout << initialData[0][j] << endl;

            cout << "P(S " << recognizedFeatures[j][0] << ") = " << possible_values_1 << endl;
            cout << "P(S " << recognizedFeatures[j][1] << ") = " << possible_values_0 << endl;

            cout << "E(S " << recognizedFeatures[j][0] << ") = " << entropy1 << endl;
            cout << "E(S " << recognizedFeatures[j][1] << ") = " << entropy0 << endl;

            cout << "IG(S," << initialData[0][j] << ") = " << ig << endl << endl;



            possible_values_0 = 0;
            possible_values_1 = 0;
            binary_zero_count = 0;
            binary_one_count = 0;



        }



    }

    double check_events(int index, int checkValue) {

        double matchCount = 0.0;
        double lastIndex = binaryVectorData[0].size() - 1;

        for (int j = 0; j < binaryVectorData.size(); j++) {
           // cout << binaryVectorData[j][index] << " " << binaryVectorData[j][lastIndex] << endl;
            if(binaryVectorData[j][index] == binaryVectorData[j][lastIndex] && binaryVectorData[j][index] == checkValue) {

                matchCount++;
            }


        }

        return matchCount;

    }





    void entropy() {

        double positives = 0.0;
        double negatives = 0.0;

        for(int i = 0; i < totalDataSets; i++) {

            if(binaryVectorData[i][totalAttributes - 1] == 1) {
                positives++;
            }else  {
                negatives++;
            }

        }


        entropyValue = -((log2(positives/totalDataSets) * positives/totalDataSets) + (log2(negatives/totalDataSets) * negatives/totalDataSets));

        cout << "\nENTROPY" << endl;
        cout << "instances: " << totalDataSets << endl;
        cout << "positives: " << positives << endl;
        cout << "negatives: " << negatives << endl;
        cout << "E(S) = " << entropyValue << endl;
    }

    void output_binaryVector() {

        cout << "\n\nNEW BINARY VECTOR" << endl;

        for (int i = 0; i < binaryVectorData.size(); i++) {
            for (int j = 0; j < binaryVectorData[i].size(); j++) {

                cout << binaryVectorData[i][j] << " ";
            }

            cout << endl;
        }

    }

    void convertBinaryVector() {

        int valueRepresentation = 0;
        vector<int> temp;

        for (int i = 1; i < initialData.size(); i++) {

            for (int j = 0; j < initialData[i].size(); j++) {

                //cout << initialData[i][j] << " ";

                if( recognizedFeatures[j].size() == 2){

                        if(initialData[i][j] == recognizedFeatures[j][0]) {
                            temp.push_back(1);
                        }else{
                            temp.push_back(0);
                        }

                }

            }

            binaryVectorData.push_back(temp);
            temp.clear();

        }





    }

    void output_recognizedFeatures() {



            for (int j = 0; j < recognizedFeatures.size(); j++) {

                cout << endl << initialData[0][j] << endl;
                cout << "Total different values: " <<  recognizedFeatures[j].size() << endl;
                cout << "Recognized values: ";
                for(int i = 0; i < recognizedFeatures[0].size(); i++) {


                    cout << recognizedFeatures[j][i] << " ";


            }

            cout << endl;

        }

    }

    void recognizeFeatures() {

        vector<string> temp;
        string tempFeature = "";
        bool featureFound = false;


        for(int i = 0; i < initialData[0].size(); i++) {

            for (int j = 1; j < initialData.size(); j++) {

                    tempFeature = initialData[j][i];


                    if(temp.size() > 0){

                        for(int k = 0; k < temp.size(); k++) {


                            if(tempFeature.compare(temp[k]) == 0) {
                                featureFound = true;
                            }
                        }

                        if(featureFound == false){
                            temp.push_back(tempFeature);

                        }



                    }else {
                        temp.push_back(tempFeature);

                    }

                featureFound = false;
            }

            recognizedFeatures.push_back(temp);
            temp.clear();



        }


    }

    void readFile(string fileName){

        string data;
        string tempData;
        string fileLines;
        int attributes = 0;
        int features = 0;
        int row, col;
        vector<string> temp;

        fileInput.open(fileName);


        getline(fileInput, data);

        for(int i = 0; data[i] != '\0'; i++)
        {
            if (isspace(data[i])) //Checking for spaces
            {
                attributes++;
            }
        }

        while (getline(fileInput, fileLines)) {
            features++;
        }

        cout << data << endl;
        cout << "Total attributes: " << attributes << endl;
        cout << "Each attribute has " << features << " features" << endl;

        row = attributes;
        col = features;

        totalDataSets = features;
        totalAttributes = attributes;

        fileInput.clear();
        fileInput.seekg(0, std::ios::beg);



        //initialize 2D initialData vector with input file data
        for(int i = 0; i < col + 1; i++) {

            for(int j = 0; j < row; j++ ) {

                fileInput >> tempData;
                temp.push_back(tempData);

            }

            initialData.push_back(temp);
            temp.clear();
        }



        fileInput.close();

    }

void output_initialDataVector() {

    cout << "\n\nINITIAL DATA VECTOR" << endl;

    for (int i = 0; i < initialData.size(); i++) {
        for (int j = 0; j < initialData[i].size(); j++) {

            cout << initialData[i][j] << " ";
        }

        cout << endl;
    }

    }



private:
    ifstream fileInput;
    vector < vector < string > > initialData;
    vector < vector < string > > recognizedFeatures;
    vector < vector < int > > binaryVectorData;

    double totalDataSets;
    double totalAttributes;
    double entropyValue;



};




#endif //PROJECT1_HEADER_H
