CXX      = g++
CXX_FILE = $(wildcard *.cpp)
TARGET   = $(patsubst %.cpp,%,$(CXX_FILE))
CXXFLAGS = -O3 -std=c++11 -Wall -Werror -pedantic-errors -fmessage-length=0

all:
	$(CXX) $(CXXFLAGS) $(CXX_FILE) -o $(TARGET)
clean:
	rm -f $(TARGET) $(TARGET).exe

	
#top is vaiables, bottom is instructions for building. 
#CXX = g++ which is name of new c++ compiler we are using.
#CXX_file , subshell for wildcard, looks into folder and looks for all files that end in cpp extension and assigns them. only works for one cpp file in a folder.
#target, name of the output executable we want to build. Same as source file without extension, pattern substitution on all characters up until .cpp etension
#CXX Flags, -g include debug info inside of exectuable(preserves variable names and function names to see problems)
	#for professionals is -O for compiler optimizations (only use once you know it works)
	#-Wall, warn on all things. warn on everything doing wrong
	#-Werror, turn all warnings into errors, stopping compilation before an error produced
	#-pedantic-errors, be even more ennoying about possible errors in code
	#-fmessage-length, setws error line length = 0 so that error messages will be a long line
	#-std assures whih standard is being used
	
#format    target : dependencies, then tab, then build instructions (line 6 and on)
#line 6: 
	#g++ -g -Wall -Werror -pedantic-errors -fmessage-length=0 gcd.cpp -o gcd
	
#make clean removes executable (make clean && make)
#man g++ searches the manual for g++ description

#pwd prints what directory you are in
#cd changes directory (cd - : goes back direectories)
