#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

using namespace std;

void handler (int signum){
  cout << "HANDLER: (Signal Number " << signum << ")" << endl;
  switch (signum) {
    case SIGHUP:
            cout << "Hangup signal handled" << endl;
            break;
    case SIGILL:
            cout << "Illegal signal handled" << endl;
            break;
    case SIGUSR1:
            cout << "User signal handled" << endl;
            break;

    default: cout << "Did not handle signal: " << signum << endl;
  }


}


int main(){

  errno = 0;
  struct sigaction *actionHup = new (struct sigaction);
  actionHup->sa_handler = handler;
  actionHup->sa_flags = SA_RESTART;
  sigemptyset(&(actionHup->sa_mask));
  sigaction(SIGHUP, actionHup, 0);

  assert(sigaction(SIGHUP, actionHup, NULL) == 0);

  struct sigaction *actionIll = new (struct sigaction);
  actionIll->sa_handler = handler;
  actionIll->sa_flags = SA_RESTART;
  sigemptyset(&(actionIll->sa_mask));
  sigaction(SIGILL, actionIll, 0);
  assert(sigaction(SIGILL, actionIll, NULL) == 0);

  struct sigaction *actionUsr1 = new (struct sigaction);
  actionUsr1->sa_handler = handler;
  actionUsr1->sa_flags = SA_RESTART;
  sigemptyset(&(actionUsr1->sa_mask));
  sigaction(SIGUSR1, actionUsr1, 0);
  assert(sigaction(SIGUSR1, actionUsr1, NULL) == 0);


  pid_t childpid = fork();

  //Child process
  if(childpid == 0){
    pid_t ppid = getppid();
    cout << "Signal: Hangup " << endl;
    kill(ppid, SIGHUP);

    cout << "Signal: Illegal Instruction " << endl;
    kill(ppid, SIGILL);


    cout << "Signal: User1 " << endl;
    kill(ppid, SIGUSR1);

    cout << "Sending three SIGHUP Signals..." << endl;
    kill(ppid, SIGHUP);
    kill(ppid, SIGHUP);
    kill(ppid, SIGHUP);


  } else if(childpid < 0){
    perror("Fork failed");

  }
  //Child is dead
  else{
    while (true) {
    int status;
    pid_t done = waitpid(childpid, &status, '\0');
    if (done == -1) {
        if (errno == ECHILD) break; // no more child processes
    } else {
        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            cerr << "pid " << done << " failed" << endl;
            exit(1);
        }
    }
}

  }

  delete actionHup;
  delete actionIll;
  delete actionUsr1;

  return 0;

}
