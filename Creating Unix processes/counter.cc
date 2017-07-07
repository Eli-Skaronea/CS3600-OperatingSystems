#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char const *argv[]) {
  string input;
  if(argc >= 2){          //Make sure there is a second argument for how many times to loop
    input = argv[1];
  }
  else{
    cout << "Not enough arguments given" << endl;
    exit(EXIT_FAILURE);
  }


  int i = 1;
  int numOfTimes = atoi(input.c_str());   //Converts input into int

  //Output the process id and number within the loop it is
  while(i <= numOfTimes){
    cout << "Process: " << getpid() << " " << i << endl;
    i++;
  }
  //Exit and return the argument given 
  exit(numOfTimes);
}
