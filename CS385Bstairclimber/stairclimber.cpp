/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Daniel Shapiro
 * Date        : 10/3/18
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System." - Daniel Shapiro
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	// Uses tree recursion to find all the paths available to climb num_stairs.
	// Keeps track of them by storing them as vectors and then adding those vectors into the final ways
	// vector of vectors.
	vector <vector <int>> ways;
	if(num_stairs <= 0){
		vector <int> result;
		ways.push_back(result);
	}else{
		for(int i = 1; i<=3; i++){
			if(num_stairs >= i){
				vector<vector<int>> result = get_ways(num_stairs - i);
				for (vector<int> r : result){
					r.push_back(i);
					ways.push_back(r);
				}
			}
		}
	}
	return ways;
}

int get_width(int x){
	// Takes a number and keeps dividing it by 10 to calculate the number of digits in the number.
	int q = 1;
	while(x>9){
		x = x/10;
		q+=1;
	}
	return q;
}
void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	// Iterates through the vector of vectors, printing out their contents in reverse order to the screen,
	// which actually correctly orients them.
	unsigned int s = ways.size();

	for(unsigned int i=0; i<s; i++){
		cout<<setw(get_width(s))<< i + 1<<". [";
		unsigned int t = ways[i].size();
		for(unsigned int j = t-1; j>0; j--){
			cout<<ways[i][j]<<", ";
		}
		cout<<ways[i][0]<<"]"<<endl;
	}


}

int main(int argc, char * const argv[]) {
	// Checks for various errors of user input and prints out the correct error message. If the user enters
	// a 1, then it says "1 way to climb 1 stair", otherwise it uses the resulting vector of get_ways to
	// figure out the number of ways, and uses display_ways to correctly display them to the user.
	// Uses istringstream for conversions of user input to a usable integer.

	if(argc!= 2){
		cerr<<"Usage: ./stairclimber <number of stairs>"<<endl;
	}else{
		istringstream iss;
		int m;
		iss.str(argv[1]);
		if(!(iss >> m)){
			cerr<<"Error: Number of stairs must be a positive integer."<<endl;
		}else if(m<=0){
			cerr<<"Error: Number of stairs must be a positive integer."<<endl;
		}else if(m==1){
			cout<<"1 way to climb 1 stair."<<endl;
			display_ways(get_ways(m));
		}else{
			iss>>m;
			cout<< get_ways(m).size() << " ways to climb "<< m << " stairs."<<endl;
			display_ways(get_ways(m));
		}
	}
	return 0;
}
