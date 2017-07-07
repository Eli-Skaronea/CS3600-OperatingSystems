#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>


using namespace std;

int main(int argc, char const *argv[]) {
  //Call a fork system call and assign the pid
  pid_t childpid = fork();
  //The status code returned later by the child process
  int statusCode;

  //A sucessfull fork will return 0
  if(childpid == 0){
    execl("./counter", "./counter", "5", NULL);
    perror("Execl");
  }
  //Run the parent process
  else if(childpid > 0){
    cout << "Child PID: " << childpid << endl;
    cout << "Parent PID: "<< getpid() << endl;

    pid_t wait = waitpid(childpid, &statusCode, '\0');

    if(WIFEXITED(statusCode)){
       statusCode = WEXITSTATUS(statusCode);
      cout << "Process " << childpid << " " << "exited with status: " << statusCode << endl;
    }
    else{
      cout << "Process " << childpid << " " << "failed." << endl;
    }
  }
  //Fork has failed
  else{
    perror("Fork returned: ");
  }

  return(0);
}
