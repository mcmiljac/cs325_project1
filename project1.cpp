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


struct subVector{
    int lower;
    int upper;
    int sum;
};

/***************************************************************************************
 ** Function: _maxSumCrossingArray
 ** Description:
 ** Parameters:
 ***************************************************************************************/
struct subVector _maxSumCrossingArray (vector<int> v,int low, int mid, int high){
    struct subVector subVect;
    int maxSumL, maxSumR, runningSum;

    subVect.lower = mid;
    subVect.upper = mid + 1;
    subVect.sum = v[mid] + v[mid + 1];

    maxSumL = v[mid];
    runningSum = v[mid];
    for(int i = mid - 1; i >= low ; i--){
        runningSum += v[i];
        if(runningSum > maxSumL){
            maxSumL = runningSum;
            subVect.lower = i;
        }
    }

    maxSumR = v[mid + 1];
    runningSum = v[mid + 1];
    for(int i = mid + 2; i <= high; i++){
        runningSum += v[i];
        if(runningSum > maxSumR){
            maxSumR = runningSum;
            subVect.upper = i;
        }
    }
    subVect.sum = maxSumL + maxSumR;
    return subVect;
}

/***************************************************************************************
 ** Function: displayArray
 ** Description:
 ** Parameters:
 ***************************************************************************************/
void displayArray(vector<int> vect, struct subVector subVect){
    cout << "Subvector: [";
    for(int i = subVect.lower; i<= subVect.upper; i++){
        if(i == subVect.upper)
            cout << vect[i];
        else
            cout << vect[i] << ", ";
    }
    cout << "]" << endl << "Maximum Sum: " << subVect.sum << endl << endl;
}


/***************************************************************************************
 ** Function: enumeration
 ** Description:
 ** Parameters:
 ***************************************************************************************/
struct subVector enumeration (vector<int> v, int low, int high){
    struct subVector subVect;
    subVect.lower = low;
    subVect.upper = high;
    subVect.sum = v[low];
    int tempSum;

    //Calculate sum of every subarray starting from scratch each time.
    for (int i = low; i <= high; i++){
        for(int j = i; j <= high; j++){
            tempSum = 0;
            for(int k = i; k <= j; k++){
                tempSum += v[k];
            }
            //Track the sum and endpoints of max subarray.
            if (tempSum > subVect.sum){
                subVect.sum = tempSum;
                subVect.lower = i;
                subVect.upper = j;
            }
        }
    }

    //Create a new vector for the maximum subarray and return.

    return subVect;
}

/***************************************************************************************
 ** Function: betterEnumeration
 ** Description:
 ** Parameters:
 ***************************************************************************************/
struct subVector betterEnumeration (vector<int> v, int low, int high){
    struct subVector subVect;
    subVect.lower = low;
    subVect.upper = high;
    subVect.sum = v[low];
    int tempSum;

    //Calculate sum of every subarray by adding onto the sums of smaller subarrays.
    for (int i = low; i <= high; i++){
        tempSum = 0;
        for(int j = i; j <= high; j++){
            tempSum += v[j];
            //Track the sum and endpoints of max subarray.
            if (tempSum > subVect.sum){
                subVect.sum = tempSum;
                subVect.lower = i;
                subVect.upper = j;
            }
        }
    }
    return subVect;
}

/***************************************************************************************
 ** Function: divideAndConquer
 ** Description:
 ** Parameters:
 ***************************************************************************************/
struct subVector divideAndConquer (vector<int> v,int low, int high){
    struct subVector subVectL;
    struct subVector subVectR;
    struct subVector subVectC;
    struct subVector subVect;

    subVect.lower = low;
    subVect.upper = high;
    subVect.sum = v[low];
    if(low == high){
        return subVect;
    }
    else {
        int mid = (low + high)/2;
        subVectL = divideAndConquer(v,low,mid);
        subVectR = divideAndConquer(v,mid+1,high);
        subVectC = _maxSumCrossingArray(v,low,mid,high);
        if(subVectL.sum >= subVectR.sum && subVectL.sum >= subVectC.sum)
            return subVectL;
        else if(subVectR.sum >= subVectL.sum && subVectR.sum >= subVectC.sum)
            return subVectR;
        else
            return subVectC;
    }
}

/***************************************************************************************
 ** Function: linearTime
 ** Description:
 ** Parameters:
 ***************************************************************************************/
struct subVector linearTime (vector<int> v,int low, int high){
    struct subVector subVect;
    subVect.lower = low;
    subVect.upper = high;
    subVect.sum = v[low];

    int maxSum = 0, currentSum = 0, endHigh = 0, endLow = 0, endLeft =0, endRight = 0;

    for (int j = low; j <= high; j++) {
	currentSum += v[j];
	if (currentSum > maxSum) {
		maxSum = currentSum;
		endRight = j;
		endLow = endLeft;
		endHigh = endRight;
	}
	if (currentSum < 0) {
		currentSum = 0;
		endLeft = j + 1;
		endRight = j + 1;
	}

    }
	subVect.lower = endLeft;
	subVect.upper = endRight;
	subVect.sum = maxSum;
				

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
    vector<int> vect;
    struct subVector maxArray;

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
	
	if(vect.size()==0)
        continue;
	
    // Output the starting array.
    cout << endl << "Starting Array:" << endl << "[";
    for(int i = 0; i < (int)vect.size(); i++){
        if(i == (int)vect.size()-1)
            cout << vect[i];
        else
            cout << vect[i] << ", ";
    }
    cout << "]" << endl << endl;

    // Output the maximum sum subarray and display its sum.


    maxArray = enumeration(vect,0,vect.size()-1);
    cout << "Algorithm 1:" << endl;
    displayArray(vect,maxArray);

    maxArray = betterEnumeration(vect,0,vect.size()-1);
    cout << "Algorithm 2:" << endl;
    displayArray(vect,maxArray);

    maxArray = divideAndConquer(vect,0,vect.size()-1);
    cout << "Algorithm 3:" << endl;
    displayArray(vect,maxArray);

    maxArray = linearTime(vect,0,vect.size()-1);
    cout << "Algorithm 4:" << endl;
    displayArray(vect,maxArray);

    //Clear vector and sum for computations on next array in input file.
    vect.clear();
}

    inFile.close();
    //outFile.close();
    return 0;
}
