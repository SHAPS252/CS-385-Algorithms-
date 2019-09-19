/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Daniel Shapiro
 * Date        : 9/17/18
 * Description : Sieve of Eratosthenes
 * Pledge      : "I pledge my honor that I have abided by the Stevens Honor System." - Daniel Shapiro
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit) : is_prime_{new bool[limit + 1]}, limit_{limit} {
    	// Contructor that initializes is_prime_ as an array for booleans and makes all entries true,
    	// and the input limit as limit_, then calls the sieve function.
    	for(int i = 0; i<= limit_; i++){
    		is_prime_[i] = true;
    	}
        sieve();
    }

    ~PrimesSieve() {
    	// Frees any memory allocated from running the program.
        delete  is_prime_ [];
    }

    inline int num_primes() const {
    	// Returns num_primes_ at any point needed because it is inline.
        return num_primes_;
    }

    inline int countnumprimes(){
    	//Public method to return private method of count_num_primes().
    	return count_num_primes();
    }
    void display_primes() const {
        // TODO: write code to display the primes in the format specified in the
        // requirements document.
    	// First creates a new array of all the primes found.
    	// Then check the size of the new array to see if they can all fit on one line.
    	// If they can fit on one line, then print accordingly, else print based upon the set width of the largest prime.
    	vector<int> primes;
    	int j;
    	for(int i =  2; i<=limit_;i++){
    		if(is_prime_[i] == 1){
    			primes.push_back(i);
    			j++;
    		}
    	}

    	const int max_prime_width = num_digits(max_prime_);
    	const int primes_per_row  = 80 / (max_prime_width + 1);
    	const int x = primes.size();
    	if(x <= primes_per_row){
    		for(unsigned int i = 0; i < primes.size();i++){
    			if(i == primes.size() - 1){
    				cout<<primes[i]<<endl;
    			}else{
    				cout<<primes[i]<<" ";
    			}
    		}
    	}else{
    		int j = 1;
    		for(unsigned int i = 0; i < primes.size(); i++){
    			if(i == primes.size() - 1){
    				cout<<setw(max_prime_width)<<primes[i]<<endl;
    			}else{
    				if(j == primes_per_row){
    					cout<<setw(max_prime_width)<<primes[i]<<endl;
    					j = 1;
    				}else{
    					cout<<setw(max_prime_width)<<primes[i]<<" ";
    					j++;
    				}

    				}
    			}
    		}

    }

private:
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;


    int count_num_primes() const {
        // TODO: write code to count the number of primes found
    	// Iterates through is_prime_ counting the number of trues.
    	int count = 0;
    	for(int i = 2; i <= limit_; i++){
    		if(is_prime_[i] == 1){
    			count++;
    		}
    	}
    	return count;
    }

    int max_prime_finder(){
    	// Iterates through is_prime_ finding the last index of a prime number.
    	for(int i = 2; i <= limit_; i++){
    		if(is_prime_[i] == 1){
    			max_prime_ = i;
    		}
    	}
    	return max_prime_;
    }
    int num_digits(int num) const {
        // TODO: write code to determine how many digits are in an integer
        // Hint: No strings are needed. Keep dividing by 10.
    	// Divides by ten until one digit remains, then add 1.
    	int curr = num;
    	int count = 0;
    	while(curr > 9){
    		count+=1;
    		curr = curr / 10;

    	}
    	count += 1;
    	return count;
    }

    void sieve() {
        // TODO: write sieve algorithm
    	// Iterates through is_prime_ up to the square root of the input limit
    	// and if a number is true, it scales up to its index squared making it false, and then increments
    	// by its index also making those values false.
		for(int i = 2; i <= sqrt(limit_); i++){
			if(is_prime_[i] == 1){
				int j = i*i;
				while(j <=  limit_){
					is_prime_[j] = 0;
					j += i;
				}
			}
		}
		num_primes_ = count_num_primes();
		 max_prime_ = max_prime_finder();
    }
};

int main() {
	// Prompts user for limit of finding primes, tells the number of primes found, and then displays them
	// accordingly.
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve test = PrimesSieve(limit);
    cout<< endl << "Number of primes found: "<< test.countnumprimes() << endl;
    cout<< "Primes up to " << limit <<":" <<endl;
    test.display_primes();
    return 0;
}
