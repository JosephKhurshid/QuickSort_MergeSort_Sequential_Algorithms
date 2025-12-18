#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <fstream>
using namespace std;

//Went with the lomuto's partitioning method rather than Hoares. Selecting the last element as a pivot 
int lomutoPartition(vector<int>& array_of_file_values, int higher_index, int lower_index) {
    int pivot = array_of_file_values[higher_index];//pivot is lat element
    int index = lower_index - 1; 

    for (int i = lower_index; i <= higher_index -1; i++) {//looping from lower to hiher -1
        if (array_of_file_values[i] < pivot) {//if the current array value is less than the pivot 
            index++;
            swap(array_of_file_values[index], array_of_file_values[i]); //swap the element smaller than the pivot to the left side  

        }
    }
    swap(array_of_file_values[index + 1], array_of_file_values[higher_index]);//placing the pivot in the correct position, 
    return index + 1;
}

//Initiation of Quick Sort alg. This and the lomutoPartition fn are responsible for sorting the array_of_file_values.
int quickSort(vector<int>& array_of_file_values, int higher_index, int lower_index) {
    int pivot;
    if (lower_index < higher_index) {//base case is lower_index>= higher_index
        pivot = lomutoPartition(array_of_file_values, higher_index, lower_index);//get pivot to base recursive calls on
        quickSort(array_of_file_values, pivot - 1, lower_index );//sorting left side, smaller than pivot
        quickSort(array_of_file_values,  higher_index, pivot + 1); //sorting the right side, greater than pivot
    }
    return 0;
}

int merge(vector<int> &array_of_file_values, int lower_index, int middle_index, int higher_index) {
    vector<int> left_split; //creating a new array with all the begining to mid elements
    vector<int> right_split; // creating a new array with all the mid to end elements
    int left_array_index = 0;
    int right_array_index = 0;
    int array_of_file_values_index = lower_index;

    for (int i = lower_index; i <= middle_index; i++) {//storing in the new array
        left_split.push_back(array_of_file_values[i]);
    }
    for (int i = (middle_index +1); i <= higher_index; i++) {//storing in the new array
        right_split.push_back(array_of_file_values[i]);
    }

    //Main sorting between left and right
    while ( (left_array_index < left_split.size()) && (right_array_index < right_split.size()) ) { //this condition fails when ONE of the arrays has been fully searched.
        if (left_split[left_array_index] < right_split[right_array_index]) {//left array element is smaller than right array element.
            array_of_file_values[array_of_file_values_index] = left_split[left_array_index];//store left array element
            left_array_index++;
            array_of_file_values_index++;
        }else { //right array element is smaller than left array element.
            array_of_file_values[array_of_file_values_index] = right_split[right_array_index];//store right array element
            array_of_file_values_index++;
            right_array_index++;
        }
    }

    // Only one of the below loops will run, not both. Since the for loop will check the condition before it ever runs, it doesn't seem efficient to do a if statement checking which array has been searched before writing the for loops below. 
    for (int i = left_array_index; i < left_split.size(); i++) {//if necessary, Storing the last elements in left_split into array_of_file_values.
        array_of_file_values[array_of_file_values_index] = left_split[i];
        array_of_file_values_index++;
    }
    for (int i = right_array_index; i < right_split.size(); i++) {//if necessary, Storing the last elements in left_split into array_of_file_values. 
        array_of_file_values[array_of_file_values_index] = right_split[i];
        array_of_file_values_index++;
    }
    return 0;
}

//Initiation of Merge Sort alg. This and the merge fn are responsible for sorting the array_of_file_values.
int mergeSort(vector<int>& array_of_file_values, int lower_index, int higher_index) {
    if (lower_index >= higher_index) return 0;//base case
    int middle_index = (lower_index + higher_index) / 2; 
    mergeSort(array_of_file_values, lower_index, middle_index); //recursive call for left side of the array
    mergeSort(array_of_file_values, middle_index + 1, higher_index);//recursive call for right side of the array
    merge(array_of_file_values, lower_index, middle_index, higher_index); //sorting all the sub arrays and then finally the full array
    return 0;
}

//Opening/Reading input file and storing the values into an array.
int populateArray(vector<int>& array_of_file_values, string file_name) {
    ifstream intput_file(file_name);
    string line;
    int value;

    if (!intput_file.is_open()){//Error Checking file opening (if errored, else executes)
        printf("There is something wrong with opening your file. Please make sure the file you inputted exists.\n");
        return 1;
    }
    while (getline(intput_file, line)){//Get Each Line
        try {//Try is for the stoi. In case the user's file has an invalid value and it can't convert to a int.
            value = stoi(line);
            array_of_file_values.push_back(value);//stornig file values in the array.
        } catch (const invalid_argument&) {
            printf("The file you inputted has an invalid value. Please modify the file.\n");
            return 1;
        } 
    }
    intput_file.close();
    return 0;
}

//Writing to the output file
int writeToFile(vector<int>& array_of_file_values, string file_name) {
    ofstream output_file(file_name);

    if(output_file.is_open()) {//Error checking for creating the file (if errored, else executes)
        for (int i = 0; i < array_of_file_values.size(); i++) {//for loop to write the values to the output file
            output_file << array_of_file_values[i] << "\n";
        }
        output_file.close();
    } else {
        printf("Can't open the output file.\n");
        return 1;
    }

    return 0;
}

//checks if --name exists and prints my name. Different from other verify fns in that I don't return 1 if there is no --name since the readme doesn't specify that.
int printName(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {//search through arguments
        if (strcmp(argv[i], "--name") == 0){//if --name exists, print the name
            printf("Bazz Khurshid\n");
            break;
        }
    }
    return 0;
}

//Every verify_ fn below is about verifying there specific arugmnet. So verify_alg is about verifying the --alg argument. The rest follow after their fn name
int verifyAlg(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {//search through arguments
        if (strcmp(argv[i], "--alg=merge") == 0){ //if the alg --alg=merge and --alg=quick
            return 0;
        }else if (strcmp(argv[i], "--alg=quick") == 0){
            return 0;
        }
    }
    printf("You are missing the argument for the algorithm. You can either put --alg=quick or --alg=merge\n");
    return 1;
}

int verifyInputFileArg(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {//search through arguments
        if (strcmp(argv[i], "-i") == 0){
            if (i != (argc -1)) {                
                return 0;
            }
        }
    }
    printf("You are missing the argument for the input file, -i [filename].\n");
    return 1;
}

int verifyOutputFileArg(int argc, char* argv[]) {
    for (int i = 0; i < argc; ++i) {//search through arguments
        if (strcmp(argv[i], "-o") == 0){
            if (i != (argc -1)) {                
                return 0;
            }
        }
    }
    printf("You are missing the argument for the output file, -o [filename].\n");
    return 1;
}

//Verify all the arguments except --name. If they don't exist, then return 1 to signify an error. 
//printName is called but there is no verification, since the readMe states it is an optional argument.
int verifyArguments(int argc, char* argv[]) {
    if (verifyInputFileArg(argc, argv) == 1) return 1;
    if (verifyOutputFileArg(argc, argv) == 1) return 1;
    if (verifyAlg(argc, argv) == 1) return 1;
    printName(argc, argv);
    return 0;
}

int main(int argc, char* argv[]) {
    //For when the user just calls the program with --name and nothing else.
    if (argc == 2) {
        if (strcmp(argv[1], "--name") == 0){
            printf("Bazz Khurshid\n");
            return 0;
        }
    }
    //If the user does not have -i, -o or --alg, then I return 1. Crucially, if the call has those but doesn't put a input or output file name, 
    //then I error out on not being able to open the file. For example ./quickmergealg -i -o outputFile.txt --alg=merge will pass verify_arguments but
    //when it goes to populateArray, the filename being opened, to read, will be -o b/c it is the one after -i. This will then error b/c there should be no
    //file named -o in the user directory. Since this would clearly be a mistake on the user part. 
    if (verifyArguments(argc, argv) == 1) return 1;
    vector<int> array_of_file_values;

    //Through the rest of the main fn, I search through the args each time to find the exact argument.

    //populateArray fn is when I read the input file and store all of its values in the array_of_file_values.
    for (int i = 0; i < argc; ++i) {//Search through the args
        if (strcmp(argv[i], "-i") == 0){
            if (populateArray(array_of_file_values, argv[i+1]) != 0) return 1;
            break;
        }
    }

    for (int i = 0; i < argc; ++i) {//Search through the args
        if (strcmp(argv[i], "--alg=merge") == 0){//if merge, call mergeSort
            mergeSort(array_of_file_values, 0, array_of_file_values.size() - 1);
            break;
        }else if (strcmp(argv[i], "--alg=quick") == 0){//if quick, call quickSort
            quickSort(array_of_file_values, array_of_file_values.size() - 1, 0);
            break;
        }
    }

    for (int i = 0; i < argc; ++i) {//Search through the args
        if (strcmp(argv[i], "-o") == 0){
            writeToFile(array_of_file_values, argv[i + 1]);//Write the array values into the File, argument after -o (argv[i+1]).  
            break;
        }
    }

    return 0;
}
