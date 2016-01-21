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

/***************************************************************************************
 ** Function: subArraySum
 ** Description: Returns the sum of elements in an integer array within specified range
 ** Parameters:
 ***************************************************************************************/
int subArraySum (vector<int> v,int low , int high){
    int sum = 0;
    for (int i = low; i <= high;i ++){
        sum += v[i];
    }
    return sum;
}

/***************************************************************************************
 ** Function: enumeration
 ** Description:
 ** Parameters:
 ***************************************************************************************/
vector<int> enumeration (vector<int> v){
    int lower = 0;
    int upper = 0;
    int maxSum = v[0];
    int tempSum;
    int length = v.size();

    //Calculate sum of every subarray starting from scratch each time.
    for (int i = 0; i < length; i++){
        for(int j = i; j < length; j++){
            tempSum = 0;
            for(int k = i; k <= j; k++){
                tempSum += v[k];
            }
            //Track the sum and endpoints of max subarray.
            if (tempSum > maxSum){
                maxSum = tempSum;
                lower = i;
                upper = j;
            }
        }
    }

    //Create a new vector for the maximum subarray and return.
    vector<int>::const_iterator first = v.begin() + lower;
    vector<int>::const_iterator last = v.begin() + upper + 1;
    vector<int> subVect(first, last);
    return subVect;
}

/***************************************************************************************
 ** Function: betterEnumeration
 ** Description:
 ** Parameters:
 ***************************************************************************************/
vector<int> betterEnumeration (vector<int> v){
    int lower = 0;
    int upper = 0;
    int maxSum = v[0];
    int tempSum;
    int length = v.size();

    //Calculate sum of every subarray by adding onto the sums of smaller subarrays.
    for (int i = 0; i < length; i++){
        tempSum = 0;
        for(int j = i; j < length; j++){
            tempSum += v[j];
            //Track the sum and endpoints of max subarray.
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

/***************************************************************************************
 ** Function: divideAndConquer
 ** Description:
 ** Parameters:
 ***************************************************************************************/
vector<int> divideAndConquer (vector<int> v,int low, int high){
    int lower = 0;
    int upper = 0;
    int maxSumL, maxSumR, maxSumLR;
    vector<int> subVectL;
    vector<int> subVectR;
    vector<int> subVect;

    if(low < high){
        int mid = (low + high)/2;
        subVectL = divideAndConquer(v,low,mid);
        subVectR = divideAndConquer(v,mid+1,high);
        maxSumL = subArraySum(subVectL,0,subVectL.size());
        maxSumR = subArraySum(subVectR,0,subVectR.size());
        maxSumLR = maxSumL + maxSumR; // + 'intermediateSum' - Need to find way to compute sum of terms in between the max left and right subarrays
        if (maxSumL > maxSumR && maxSumL > maxSumLR)
            subVect = subVectL;
        else if (maxSumR > maxSumL && maxSumR > maxSumLR)
            subVect = subVectR;
        else
            subVect  = subVect; //Again, need to find terms in original vector between the max left and right subarrays
    }
    else {
        vector<int>::const_iterator first = v.begin();
        vector<int> subVect(first, first);
    }
    return subVect;
}

/***************************************************************************************
 ** Function: linearTime
 ** Description:
 ** Parameters:
 ***************************************************************************************/
vector<int> linearTime (vector<int> v){
    int lower = 0;
    int upper = 0;

    vector<int>::const_iterator first = v.begin() + lower;
    vector<int>::const_iterator last = v.begin() + upper + 1;
    vector<int> subVect(first, last);
    return subVect;
}

/***************************************************************************************
 ** Function: main
 ** Description:
 ** Parameters:
 ***************************************************************************************/
int main(){
    string fileName, outputFile, inputStr;
    int value;
    int maxSum = 0;
    vector<int> vect;

    //User specifies name of file to read input from.
    cout << "Please input name of input file:" << endl;
    cin >> fileName;
    ifstream inFile;
    inFile.open(fileName.c_str());

    //Validates that input file can be opened.
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

// Read file line-by-line.
while (std::getline(inFile, inputStr))
{
    // Place integers into vector, ignoring commas, until closing brace is reached.
    std::istringstream iss(inputStr);
    iss.ignore();
    while (iss >> value){
        vect.push_back(value);
        if (iss.peek() == ',')
            iss.ignore();
        else if (iss.peek() == ']')
            break;
    }

    // Output the starting array.
    cout << "[";
    for(int i = 0; i< vect.size(); i++){
        if(i == vect.size()-1)
            cout << vect[i];
        else
            cout << vect[i] << ", ";
    }
    cout << "]" << endl;

    // Output the maximum sum subarray and display its sum.
    vector<int> subVect = betterEnumeration(vect);
    cout << "Subvector: [";
    for(int i = 0; i< subVect.size(); i++){
        maxSum += subVect[i];
        if(i == subVect.size()-1)
            cout << subVect[i];
        else
            cout << subVect[i] << ", ";
    }
    cout << "]" << endl << "Maximum Sum: " << maxSum << endl << endl;

    //Clear vector and sum for computations on next array in input file.
    vect.clear();
    maxSum = 0;
}

    inFile.close();
    //outFile.close();
    return 0;
}
