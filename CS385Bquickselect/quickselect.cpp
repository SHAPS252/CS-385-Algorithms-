/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Daniel Shapiro
 * Pledge        : "I pledge my honor that I have abided by the Stevens Honor System." - Daniel Shapiro
 * Date          : 10/28/18
 * Description   : Implements the quickselect algorithm found on page 160 in
 *                 Algorithms, 3e by Anany Levitin.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

size_t lomuto_partition(int array[], size_t left, size_t right) {
	// It modifies the input array so that the pivot is array[left] and is in its correct location, and elements to the left are lower than it,
	// while elements to the right are larger than it.
    int p = array[left];
    int s = left;
    for (unsigned int i = (left+1); i<= right; i++){
    	if (array[i] < p){
    		s+=1;
    		int temp = array[s];
    		array[s] = array[i];
    		array[i] = temp;
    	}
    }
	int temp = array[left];
	array[left] = array[s];
	array[s] = temp;
    return s;
}

int quick_select(int array[], size_t left, size_t right, size_t k) {
	// Finds the k-smallest element by recursively partitioning the array, and calling the algorithm on subarrays based on indices and not slicing,
	// until the partitioned element becomes the k-smallest element and is in its correct location in the array.
	size_t s = lomuto_partition(array, left, right);
	if(s == k-1){
		return array[s];
	}else if(left == right){
		return array[s];
	}else if(s > (k -1)){
		return quick_select(array, left, s-1, k);
	}else{
		return quick_select(array, s+1, right, k);
	}

}

int quick_select(int array[], const size_t length, size_t k) {
	// Calls the quick_select with specified left, and right variables.
    return quick_select(array, 0, length - 1, k);
}

int main(int argc, char *argv[]) {
	// Checks input to make sure that integers are being entered, and that k is a possible value for the given created vector of input integers.
	// If not, output the respective errors. If it passes, call the quick_select method using the created vector.data() as the array being
	// input, and num_values as the length, and the input k.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <k>" << endl;
        return 1;
    }

    int k;
    istringstream iss;
    iss.str(argv[1]);
    if ( !(iss >> k) || k <= 0 ) {
        cerr << "Error: Invalid value '" << argv[1] << "' for k." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    iss.clear();
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    int num_values = values.size();
    if (num_values == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }
    if(k > num_values){
    	cerr << "Error: Cannot find smallest element " << k << " with only ";
    			if(num_values == 1){
    				cout<< "1 value."<<endl;
    			}else{
    				cout<< num_values << " values."<<endl;
    			}
    }else{
    	cout<< "Smallest element "<< k << ": ";
    	cout<<quick_select(values.data(), num_values, k);
    	cout<<endl;
    }



    return 0;
}
