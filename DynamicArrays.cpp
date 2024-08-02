#ifndef DYNAMICARRAYS_CPP
#define DYNAMICARRAYS_CPP

#include "DynamicArrays.h"
//V4
//Isn't compiling, working on comments till I get an idea
// Function to check if the rowNumber is valid
bool isValidRowNumber(int rowNumber, int numRows) {
    return rowNumber >= 0 && rowNumber < numRows;
}

void createArray(int**& array, int*& numColumns, int& numRows, std::string input) {
    if (array != NULL || numColumns != NULL || numRows != 0) {
        // Properly deallocate existing memory before reinitializing
        if (array != NULL) {
            for (int i = 0; i < numRows; i++) {
                delete[] array[i];
            }
            delete[] array;
        }
        delete[] numColumns;
        array = NULL;
        numColumns = NULL;
        numRows = 0;
    }
    if(input.empty()){
        numRows = 1;
        numColumns = new int[1];
        numColumns[0] = 0;
        array = new int*[1];
        array[0] = NULL;
        return;
    }

    // Size Calculation
    int strI = 0;
    numRows = 1;
    while (input[strI] != '\0') {
        if (input[strI] == '|') {
            numRows++;
        }
        strI++;
    }

    numColumns = new int[numRows];
    for (int i = 0; i < numRows; i++) {
        numColumns[i] = 0;
    }

    strI = 0;
    int rI = 0;
    while (input[strI] != '\0') {
        if (input[strI] == '|') {
            rI++;
        } else if (input[strI] == ',') {
            numColumns[rI]++;
        }
        strI++;
    }
    for (int i = 0; i < numRows; i++) {
        numColumns[i]++;
    }

    // Allocating memory for 2-d dynamic array structure.
    array = new int*[numRows];
    for (int i = 0; i < numRows; i++) {
        array[i] = new int[numColumns[i]];
    }

    // Populate the array
    strI = 0;
    rI = 0;
    int cI = 0;
    while (input[strI] != '\0') {
        if (input[strI] != '|' && input[strI] != ',') {
            array[rI][cI] = input[strI] - '0';
            cI++;
        } else if (input[strI] == '|') {
            rI++;
            cI = 0;
        }
        strI++;
    }
}

void destroyArray(int**& array, int*& numColumns, int& numRows) {
    if (array != NULL) {
        for (int i = 0; i < numRows; i++) {
            if (array[i] != NULL) {
                delete[] array[i];
                array[i] = NULL;
            }
        }
        delete[] array;
        array = NULL;
    }
    if (numColumns != NULL) {
        delete[] numColumns;
        numColumns = NULL;
    }
    numRows = 0;
}

std::string printArrayStructure(int**& array, int*& numColumns, int& numRows){
    //got this from the discord
    // Converting an int to a string
    std::string outputString;
    std::stringstream intToStr;
    intToStr << numRows;
    intToStr >> outputString;

    std::string output = "numRows : " + outputString + "\n";
    for(int i = 0; i < numRows; i++){
        std::string outputI;
        std::stringstream IToStr;
        IToStr << i;
        IToStr >> outputI;
        std::string outputC;
        std::stringstream CToStr;
        CToStr << numColumns[i];
        CToStr >> outputC;
        if(numRows - 1 == i) {
            output += "row[" + outputI + "] : " + outputC;
        }else {
            output += "row[" + outputI + "] : " + outputC + "\n";
        }
    }
    return output;
}

//print array
std::string printArray(int**& array, int*& numColumns, int& numRows) {
    std::string output = "";
    for (int i = 0; i < numRows; i++) {
        if (numColumns[i] == 0) {
            continue; // Skip empty rows, bad I know but I'm tired
        } else {

            for (int j = 0; j < numColumns[i]; j++) {
                std::string outputA;
                std::stringstream AToStr;
                AToStr << array[i][j];
                AToStr >> outputA;
                output += outputA;
                if (j < numColumns[i] - 1) {
                    output += ",";
                }
            }
        }
        if (i < numRows - 1) {
            output += "\n";
        }
    }
    return output;
}

void addRow(int**& array, int*& numColumns, int& numRows) {
    // Allocate new memory for the array with an additional row
    int** newArray = new int*[numRows + 1];
    for (int i = 0; i < numRows; ++i) {
        newArray[i] = array[i];
    }
    newArray[numRows] = NULL; // New row with 0 columns

    // Allocate new memory for numColumns with an additional element
    int* newNumColumns = new int[numRows + 1];
    for (int i = 0; i < numRows; ++i) {
        newNumColumns[i] = numColumns[i];
    }
    newNumColumns[numRows] = 0; // New row with 0 columns

    // Deallocate old memory
    delete[] array;
    delete[] numColumns;

    // Update pointers and numRows
    array = newArray;
    numColumns = newNumColumns;
    numRows++;
}

void addValueToRow(int**& array, int*& numColumns, int& numRows, int rowNumber, int value) {
    // Check if rowNumber is valid
    if (!isValidRowNumber(rowNumber, numRows)) {
        return;
    }

    // Allocate new memory for the row with an additional column
    int* newRow = new int[numColumns[rowNumber] + 1];
    for (int i = 0; i < numColumns[rowNumber]; ++i) {
        newRow[i] = array[rowNumber][i];
    }
    newRow[numColumns[rowNumber]] = value; // Add the new value

    // Deallocate old memory for the row
    delete[] array[rowNumber];

    // Update the pointer for the row
    array[rowNumber] = newRow;

    // Update the column count for the row
    numColumns[rowNumber]++;
}

void removeRow(int**& array, int*& numColumns, int& numRows, int rowNumber) {
    // Check if rowNumber is valid
    if (!isValidRowNumber(rowNumber, numRows)) {
        return;
    }

    // Deallocate memory for the specified row
    delete[] array[rowNumber];

    // Allocate new memory for the array with one less row
    int** newArray = new int*[numRows - 1];
    for (int i = 0, j = 0; i < numRows; ++i) {
        if (i != rowNumber) {
            newArray[j++] = array[i];
        }
    }

    // Allocate new memory for numColumns with one less element
    int* newNumColumns = new int[numRows - 1];
    for (int i = 0, j = 0; i < numRows; ++i) {
        if (i != rowNumber) {
            newNumColumns[j++] = numColumns[i];
        }
    }

    // Deallocate old memory
    delete[] array;
    delete[] numColumns;

    // Update pointers and numRows
    array = newArray;
    numColumns = newNumColumns;
    numRows--;
}

void removeValueFromRow(int**& array, int*& numColumns, int& numRows, int rowNumber, int value) {
    // Check if rowNumber is valid
    if (!isValidRowNumber(rowNumber, numRows)) {
        return;
    }

    // Count occurrences of the value in the specified row
    int count = 0;
    for (int i = 0; i < numColumns[rowNumber]; ++i) {
        if (array[rowNumber][i] == value) {
            count++;
        }
    }

    // If no occurrences, do nothing
    if (count == 0) {
        return;
    }

    // Allocate new memory for the row with reduced size
    int newSize = numColumns[rowNumber] - count;
    int* newRow = new int[newSize];
    int newIndex = 0;
    for (int i = 0; i < numColumns[rowNumber]; ++i) {
        if (array[rowNumber][i] != value) {
            newRow[newIndex++] = array[rowNumber][i];
        }
    }

    // Deallocate old memory for the row
    delete[] array[rowNumber];

    // Update the pointer for the row
    array[rowNumber] = newRow;

    // Update the column count for the row
    numColumns[rowNumber] = newSize;
}
int rowSum(int**& array, int*& numColumns, int& numRows, int rowNumber) {
    // Check if rowNumber is valid
    if (!isValidRowNumber(rowNumber, numRows)) {
        return -1;
    }

    // Calculate the sum of the specified row
    int sum = 0;
    for (int i = 0; i < numColumns[rowNumber]; ++i) {
        sum += array[rowNumber][i];
    }

    return sum;
}

// Function to calculate the average of a row
float rowAvg(int**& array, int*& numColumns, int& numRows, int rowNumber) {
    // Check if rowNumber is valid
    if (!isValidRowNumber(rowNumber, numRows)) {
        return -1;
    }

    // Calculate the sum of the specified row
    int sum = 0;
    for (int i = 0; i < numColumns[rowNumber]; ++i) {
        sum += array[rowNumber][i];
    }
    if(numColumns[rowNumber]<=0){
        return -1;
    }
    // Calculate and return the average
    return static_cast<float>(sum) / numColumns[rowNumber];
}

// Function to find the maximum value in a row
int rowMax(int**& array, int*& numColumns, int& numRows, int rowNumber) {
    // Check if rowNumber is valid
    if (!isValidRowNumber(rowNumber, numRows)) {
        return -1;
    }

    // Find the maximum value in the specified row
    if(array[rowNumber][0] != NULL) {
        int maxVal = array[rowNumber][0];
        for (int i = 1; i < numColumns[rowNumber]; ++i) {
            if (array[rowNumber][i] > maxVal) {
                maxVal = array[rowNumber][i];
            }
        }


        return maxVal;
    }else{
        return -1;
    }
}

// Function to find the minimum value in a row
int rowMin(int**& array, int*& numColumns, int& numRows, int rowNumber) {
    // Check if rowNumber is valid
    if (!isValidRowNumber(rowNumber, numRows)) {
        return -1;
    }

    // Find the minimum value in the specified row
    if(array[rowNumber][0] != NULL){
    int minVal = array[rowNumber][0];
    for (int i = 1; i < numColumns[rowNumber]; ++i) {
        if (array[rowNumber][i] < minVal) {
            minVal = array[rowNumber][i];
        }
    }

    return minVal;
    } else{
        return -1;
    }
}
#endif