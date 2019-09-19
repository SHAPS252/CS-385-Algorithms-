#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    vector<string> directions;
    
    State(int _a, int _b, int _c) : a(_a), b(_b), c(_c) { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

bool error_check(int argc, char * const argv[]){
	istringstream iss;
	
}
int main(int argc, char * const argv[]) {

    }
}
