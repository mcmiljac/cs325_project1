// CS 325 - Project 1
// Group 30

#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <sstream>
#include <fstream>
using std::ifstream;
using std::ofstream;

#include<string>
using std::string;

#include<vector>
using std::vector;

vector<int> Enumeration (vector<int> v){
    int lower = 0;
    int upper = 0;
    int maxSum = v[0];
    int tempSum;
    int length = v.size();
    for (int i = 0; i < length; i++){
        for(int j = i; j < length; j++){
            tempSum = 0;
            for(int k = i; k <= j; k++){
                tempSum += v[k];
            }
            if (tempSum > maxSum){
                maxSum = tempSum;
                lower = i;
                upper = j;
            }
        }
    }
    vector<int>::const_iterator first = v.begin() + lower;
    vector<int>::const_iterator last = v.begin() + upper + 1;
    vector<int> subVect(first, last);
    return subVect;
}

int main(){
    string fileName, outputFile, inputStr;
    int value;
    int maxSum = 0;
    vector<int> vect;

    cout << "Please input name of input file:" << endl;
    cin >> fileName;
    ifstream inFile;
    inFile.open(fileName.c_str());

     while(!inFile.is_open())
    {
        if (!inFile.is_open())
        {
            cout << "Error: Could not open file." << endl << endl;
        }
        cout << "Please input name of first file:" << endl;
        cin >> fileName;
        inFile.open(fileName.c_str());
    }

/*
    cout << endl << "Please input name of output file:" << endl;
    cin >> outputFile;

    ofstream outFile;
    outFile.open(outputFile.c_str());

    //Validates that output file can be opened.
    while(!outFile.is_open())
    {
        cout << "Error: Could not open file." << endl <<endl;
        cout << "Please input name of output file:" << endl;
        cin >> outputFile;
        outFile.open(outputFile.c_str());
    }
*/

while (std::getline(inFile, inputStr))
{
    std::istringstream iss(inputStr);
    iss.ignore();
    while (iss >> value){
        vect.push_back(value);
        if (iss.peek() == ',')
            iss.ignore();
        else if (iss.peek() == ']')
            break;
    }

    cout << "[";
    for(int i = 0; i< vect.size(); i++){
        if(i == vect.size()-1)
            cout << vect[i];
        else
            cout << vect[i] << ", ";
    }
    cout << "]" << endl;

    vector<int> subVect = Enumeration(vect);
    cout << "Subvector: [";
    for(int i = 0; i< subVect.size(); i++){
        maxSum += subVect[i];
        if(i == subVect.size()-1)
            cout << subVect[i];
        else
            cout << subVect[i] << ", ";
    }
    cout << "]" << endl << "Maximum Sum: " << maxSum << endl << endl;

    vect.clear();
    maxSum = 0;
}

    inFile.close();
    //outFile.close();
    return 0;
}
