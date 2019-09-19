/*
 * waterjugpuzzle.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Daniel Shapiro(dshapir1) and Gary Ung(gung)
 *      "We pledge our honor that we have abided by the Stevens Honor System." - Daniel Shapiro, Gary Ung
 */
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;



// Struct to represent state of water in the jugs.
struct State {
	//Creates a "State" that holds three integers.
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

queue<State> Q;

bool errorCheck(char * const array[]) {
	//Checks the user input to make sure the given values are mathematically possible for the program to work. If it is,
	// then it calls the next methods, if not, it prints out the corresponding error message to the user.

	int capA,capB,capC,goalA,goalB,goalC;
	istringstream iss;

	iss.str(array[1]);
	if (!(iss>>capA) || (capA <= 0)) {
		cout << "Error: Invalid capacity '" << array[1] << "' for jug A." << endl;
		return false;
	}
	iss>>capA;
	iss.clear();
	iss.str(array[2]);
	if (!(iss>>capB) || (capB <= 0)) {
		cout << "Error: Invalid capacity '" << array[2] << "' for jug B." << endl;
		return false;
	}
	iss>>capB;
	iss.clear();
	iss.str(array[3]);
	if (!(iss>>capC) || (capC <= 0)) {
		cout << "Error: Invalid capacity '" << array[3] << "' for jug C." << endl;
		return false;
	}
	iss>>capC;
	iss.clear();
	iss.str(array[4]);
	if (!(iss>>goalA) || (goalA < 0)) {
		cout << "Error: Invalid goal '" << array[4] << "' for jug A." << endl;
		return false;
	}
	iss>>goalA;
	iss.clear();
	iss.str(array[5]);
	if (!(iss>>goalB) || (goalB < 0)) {
		cout << "Error: Invalid goal '" << array[5] << "' for jug B." << endl;
		return false;
	}
	iss>>goalB;
	iss.clear();
	iss.str(array[6]);
	if (!(iss>>goalC) || (goalC < 0)) {
		cout << "Error: Invalid goal '" << array[6] << "' for jug C." << endl;
		return false;
	}
	iss>>goalC;
	iss.clear();

	if(goalA > capA){
		cout<< "Error: Goal cannot exceed capacity of jug A."<<endl;
		return false;
	}
	if(goalB > capB){
		cout<< "Error: Goal cannot exceed capacity of jug B."<<endl;
		return false;
	}
	if(goalC > capC){
		cout<< "Error: Goal cannot exceed capacity of jug C."<<endl;
		return false;
	}

	if((goalA + goalB + goalC) != (capC)){
		cout<< "Error: Total gallons in goal state must be equal to the capacity of jug C."<<endl;
		return false;
	}
	return true;

}

void printout(int starta, int startb, int capC, vector<vector<State>> matrix, vector<string> acc){
	// Creates a vector of string vectors called print, to push all the respective directions from each state into. Then print the initial state,
	// and then display out the vector of vectors "print" in reverse order to ensure it's in correct chronological order.
	vector<vector<string>> print;
	print.push_back(acc);
	while(((starta == 0) && (startb != 0)) || ((starta != 0) && (startb == 0)) || ((starta != 0) && (startb != 0))){
		vector<string> part = matrix[starta][startb].directions;
		print.push_back(matrix[starta][startb].directions);
		int placehold;
		placehold = starta;
		starta = matrix[placehold][startb].a;
		startb = matrix[placehold][startb].b;
	}
	cout<<"Initial state. " << State(0,0, capC).to_string();
	for(unsigned int i = print.size() - 1; i>=0; i--){
		for(unsigned int j = 0; j<print[i].size(); j++){
			cout<<print[i][j];
		}
		cout << endl;
	}


}

void setup(int cA, int cB, int cC, int gA, int gB, int gC, vector<vector<State>> matrix){
	// Takes the topmost State in the queue Q, then calls all possible transitions from that State according to the order of pouring,
	// if a pour can be made, it is created into a new State and given directions on what was done in the pour, the new State is pushed onto the queue
	// and in the matrix corresponding to that new State's a, and b values is the State that came before it (the top most state that was popped
	// from the queue). Only stops once it reaches an accept state, or if the values that it gets was already visited meaning the queue would be empty.
	// If the values were all already visited then it returns "No Solution".
	// This will allow for a backwards traversal of preceding States that led to the accept state, so we can get the progression of pours made.
	while(!Q.empty()){
		State s = Q.front();

		if((s.a != cA) && (s.c != 0)){
			//Pour from C  to A
			State s2 = State(0,0,0);
			int diff;
			if (s.c + s.a > cA) {
				s2 = State(cA, s.b, s.c - (cA - s.a));
				diff = (cA - s.a);
			} else {
				s2 = State(s.a + s.c, s.b, 0);
				diff = s.c;
			}
            s2.directions.push_back("Pour "+ to_string(diff));
            if (diff == 1) {
                s2.directions.push_back(" gallon ");
            } else {
                s2.directions.push_back(" gallons ");
            }
            s2.directions.push_back("from C to A. " + s2.to_string());
			if(matrix[s2.a][s2.b].to_string() == State(-1,-1,-1).to_string()){
				matrix[s2.a][s2.b] = s;
				Q.push(s2);
			}
			if(((s2.a == gA) && (s2.b == gB) && (s2.c == gC))){
				printout(s2.a, s2.b, cC, matrix, s2.directions);
				return;
			}

		}
        if((s.a != cA) && (s.b != 0)){
        	// Pour from B to A
            State s3 = State(0,0,0);
            int diff;
            if (s.b + s.a > cA) {
              s3 = State(cA, s.b - (cA - s.a), s.c);
              diff = (cA - s.a);
            } else {
              s3 = State(s.a + s.b, 0, s.c);
              diff = s.b;
            }
            s3.directions.push_back("Pour "+ to_string(diff));
            if (diff == 1) {
              s3.directions.push_back( " gallon ");
            } else {
              s3.directions.push_back( " gallons ");
            }
            s3.directions.push_back( "from B to A. " + s3.to_string());
			if(matrix[s3.a][s3.b].to_string() == State(-1,-1,-1).to_string()){
				matrix[s3.a][s3.b] = s;
				Q.push(s3);
			}
            if(s3.a == gA && s3.b == gB && s3.c == gC){
            	printout(s3.a, s3.b, cC, matrix, s3.directions);
            	return;
            }
          }
        if((s.b != cB) && (s.c != 0)){
        	// Pour from C to B
            State s4 = State(0,0,0);
            int diff;
            if (s.b + s.c > cB) {
              s4 = State(s.a, cB, s.c - (cB - s.b));
              diff = (cB - s.b);
            } else {
              s4 = State(s.a, s.b + s.c, 0);
              diff = s.c;
            }
            s4.directions.push_back("Pour "+ to_string(diff));
            if (diff == 1) {
              s4.directions.push_back( " gallon ");
            } else {
              s4.directions.push_back( " gallons ");
            }
            s4.directions.push_back( "from C to B. " + s4.to_string());
			if(matrix[s4.a][s4.b].to_string() == State(-1,-1,-1).to_string()){
				matrix[s4.a][s4.b] = s;
				Q.push(s4);
			}
            if(s4.a == gA && s4.b == gB && s4.c == gC){
            	printout(s4.a, s4.b, cC, matrix, s4.directions);
            	return;
            }
          }
        if((s.b != cB) && (s.a != 0)){
        	// Pour from A to B
            State s5 = State(0,0,0);
            int diff;
            if (s.b + s.a > cB) {
              s5 = State(s.a - (cB - s.b), cB, s.c);
              diff = (cB - s.b);
            } else {
              s5 = State(0, s.a + s.b, s.c);
              diff = s.a;
            }
            s5.directions.push_back("Pour "+ to_string(diff));
            if (diff == 1) {
              s5.directions.push_back( " gallon ");
            } else {
              s5.directions.push_back( " gallons ");
            }
            s5.directions.push_back( "from A to B. " + s5.to_string());
			if(matrix[s5.a][s5.b].to_string() == State(-1,-1,-1).to_string()){
				matrix[s5.a][s5.b] = s;
				Q.push(s5);
			}
            if(s5.a == gA && s5.b == gB && s5.c == gC){
            	printout(s5.a, s5.b, cC, matrix, s5.directions);
                return;
            }
          }
        if((s.c != cC) && (s.b != 0)){
        	// Pour from B to C
            State s6 = State(0,0,0);
            int diff;
            if (s.b + s.c > cC) {
              s6 = State(s.a, s.b - (cC - s.c), cC);
              diff = (cC - s.c);
            } else {
              s6 = State(s.a, 0, s.c + s.b);
              diff = s.b;
            }
            s6.directions.push_back( "Pour "+ to_string(diff));
            if (diff == 1) {
              s6.directions.push_back( " gallon ");
            } else {
              s6.directions.push_back( " gallons ");
            }
            s6.directions.push_back( "from B to C. " + s6.to_string());
			if(matrix[s6.a][s6.b].to_string() == State(-1,-1,-1).to_string()){
				matrix[s6.a][s6.b] = s;
				Q.push(s6);
			}
            if(s6.a == gA && s6.b == gB && s6.c == gC){
            	printout(s6.a, s6.b, cC, matrix, s6.directions);
                return;
            }
          }
        if((s.c != cC) && (s.a != 0)){
        	// Pour from A to C
            State s7 = State(0,0,0);
            int diff;

            if (s.c + s.a > cC) {
              s7 = State(s.a - (cC - s.c), s.b, cC);
              diff = (cC - s.c);
            } else {
              s7 = State(0, s.b, s.c + s.a);
              diff = s.a;
            }
            s7.directions.push_back( "Pour "+ to_string(diff));
            if (diff == 1) {
              s7.directions.push_back( " gallon ");
            } else {
              s7.directions.push_back( " gallons ");
            }
            s7.directions.push_back( "from A to C. " + s7.to_string());
			if(matrix[s7.a][s7.b].to_string() == State(-1,-1,-1).to_string()){
				matrix[s7.a][s7.b] = s;
				Q.push(s7);
			}
            if(s7.a == gA && s7.b == gB && s7.c == gC){
            	printout(s7.a, s7.b, cC, matrix, s7.directions);
                return;
            }
          }
        Q.pop();

	}
	cout<<"No solution."<<endl;
}

int main(int argc, char * const argv[]) {
	// Checks initially that the number of arguments is correct. If it is then it moves to the error check phase, if not, it prints
	// an error message to the user.
	// If the error checking method returns true, meaning there were no errors, it then assigns values, otherwise it just displays errors.
	// It then assigns proper values to each variable using istringstream, and initializes a matrix to be filled with States of (-1,-1,-1)
	// because after error checking, such a State won't be possible to be reached in the algorithm, so it works as a "null" placeholder.
	// It then pushes the starting State onto the queue Q and checks if its the accept state. If it is the accept state, it just returns
	// that State, if not, it calls the setup() with the new assigned variables.
	if(argc != 7){
		cout<< "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" <<endl;
		return 1;
	}
	if(errorCheck(argv)){
	    int capA, capB, capC, goalA, goalB, goalC;
	    istringstream iss;
	    iss.str(argv[1]);
	    iss >> capA;
	    iss.clear();

	    iss.str(argv[2]);
	    iss >> capB;
	    iss.clear();

	    iss.str(argv[3]);
	    iss >> capC;
	    iss.clear();

	    iss.str(argv[4]);
	    iss >> goalA;
	    iss.clear();

	    iss.str(argv[5]);
	    iss >> goalB;
	    iss.clear();

	    iss.str(argv[6]);
	    iss >> goalC;
	    iss.clear();
		vector<vector<State>> matrix;
		for(int i = 0; i< capA+1; i++){
			vector<State> fill;
			matrix.push_back(fill);
			for (int j = 0; j< capB+1; j++){
				State bad = State(-1, -1, -1);
				matrix[i].push_back(bad);
			}
		}
		State s1 = State(0, 0, capC);
		Q.push(s1);
		if((0 == goalA) && (0 == goalB) && (capC == goalC)){
			cout<<"Initial state. "<< s1.to_string() << endl;
		}else{
			setup(capA, capB, capC, goalA, goalB, goalC, matrix);
		}
	}

	return 0;
}
