/*
 * shortestpaths.cpp
 *
 *  Created on: Dec 3, 2018
 *      Author: dshap
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <regex>
#include <string>
#include <climits>


using namespace std;

long INF = LONG_MAX;
string vert1;
string vert2;
string diststr;
int dist;

int len(long val){
	int length = 0;
	while(val>9){
		val = val/10;
		length++;
	}
	return length;
}
int num_vertices;

void floyd_alg(long** dist_matrix, long** path_matrix, long** inter_matrix){
	for(int k = 0;k<dist; k++){
		for(int i = 0; i<dist; i++){
			for(int j = 0; j<dist; j++){
				if(j == i || k == i){

				}else{
					if((path_matrix[i][k] + path_matrix[k][j]) < (path_matrix[i][j])){
						inter_matrix[i][j] = char('A' + k);
					}
					path_matrix[i][j] = min(path_matrix[i][j], path_matrix[i][k] + path_matrix[k][j]);
				}
			}
		}
	}
}
/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label,
					const bool use_letters = false) {
	 cout << label << endl;
 	 long max_val = 0;
 	 for (int i = 0; i < num_vertices; i++) {
	 	 for (int j = 0; j < num_vertices; j++) {
		 	 long cell = matrix[i][j];
		 	 if (cell < INF && cell > max_val) {
		 		 max_val = matrix[i][j];
		 	 }
	 	 }
 	 }
 	 int max_cell_width = len(max(static_cast<long>(num_vertices), max_val));
 	 cout << ' ';
 	 for (int j = 0; j < num_vertices; j++) {
 		 cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
 	 }
 	 cout << endl;
 	 for (int i = 0; i < num_vertices; i++) {
 		 cout << static_cast<char>(i + 'A');
 		 for (int j = 0; j < num_vertices; j++) {
 			 cout << " " << setw(max_cell_width);
 			 if (matrix[i][j] == INF) {
 				 cout << "-";
 			 } else if (use_letters) {
 				 cout << static_cast<char>(matrix[i][j] + 'A');
 			 } else {
 				 cout << matrix[i][j];
 			 }
 		 }
 		 cout << endl;
 }
 cout << endl;
}

bool errorcheck(string str, int line_number ,int range) {
    istringstream ss(str);
    regex checknum("[A-Z]+\\s[A-Z]+\\s[0-9]+");

    if (!regex_match(str, checknum)) {
    	cout<<"Error: Invalid edge data '" << str <<"' on line " << line_number << "." << endl;
    }
    getline(ss, vert1, ' ');
    getline(ss, vert2, ' ');
    getline(ss, diststr, ' ');
    if((vert1.length() > 1) || int(vert1) < 65 + range || int(vert1) > 65 + range)){
    	cout<<"Error: Starting vertex '"<<vert1<<"' on line "<<line_number<<" is not among valid values A-"<<char(65+range)<<"."<<endl;
    	return 1;
    }
    if((vert2.length() > 1) || (int(vert2)> 65 + range) || (int(vert2)> 65 + range)){
		cout<<"Error: Ending vertex '"<<vert2<<"' on line "<<line_number<<" is not among valid values A-"<<char(65+range)<<"."<<endl;
		return 1;
    }
    dist = static_cast<int>(diststr);
    if(dist < 0){
    	cout<<"Error: Invalid edge weight '"<<diststr<<"' on line "<<line_number<<"."<<endl;
    	return 1;
    }

    return false;
}

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try {
        istringstream iss;
    	int x;
    	string var1, var2;
    	long** distance_matrix;
    	long** path_lengths_matrix;
    	long** inter_matrix;
        unsigned int line_number = 1;
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        while (getline(input_file, line)) {
        	if(line_number == 1) {
        		iss.str(line);
        		x<<iss;
        	}
            if((line_number == 1) && ((x<1)|| (x>26))){
                cout<<"Error: Invalid number of vertices: '"<<x<<"' on line 1."<<endl;
                return 1;
            }
            if(line_number == 1) {
                num_vertices = x;
                distance_matrix = new long[num_vertices][num_vertices];
                path_lengths_matrix = new long[num_vertices][num_vertices];
                inter_matrix = new long[num_vertices][num_vertices];
            	for(int i = 0; i<num_vertices;i++){
            		for(int j = 0; j<num_vertices;j++){
            			distance_matrix[i][j] = LONG_MAX;
            			path_lengths_matrix[i][j] = LONG_MAX;
            			inter_matrix[i][j] = LONG_MAX;
            		}
            	}
            	for(int i = 0; i<num_vertices;i++){
    				for(int j = 0; j<num_vertices;j++){
    					if(i == j){
    						distance_matrix[i][j] = 0;
    						path_lengths_matrix[i][j] = 0;
    					}
    				}
    			}
            }
        	if(line_number > 1) {
        		errorcheck(line, line_number, x);
        	}
        	distance_matrix[int(vert1) - 65][int(vert2) - 65] = dist;

            ++line_number;
        }
        // Don't forget to close the file.
        input_file.close();
        long** distma = distance_matrix;
        long** pathma = path_lengths_matrix;
        long** interma = inter_matrix;
        floyd_alg(distma, pathma, interma);
        display_table(distma, "Distance matrix");
        display_table(pathma, "Path lengths");
        display_table(interma, "Intermediate vertices", true);
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}




