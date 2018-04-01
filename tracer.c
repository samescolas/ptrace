#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <sys/ptrace.h>
#include <sys/user.h>

//
// NOTE: THIS CODE IS INCOMPLETE AND DESIGNED TO BE A STARTER
// SKELETON
//

int main (int argc, char* argv[])
{

	if (argc < 2) {
		printf("Usage: %s pid\n", argv[0]);
		exit(1);
	}

    struct user_regs_struct regs;

    int waitStat = 0;

    //
    // Use appropriate ptrace() call here
    // Remember, this program takes a single argument
    //
	pid_t pid = atoi(argv[1]);

	if ((ptrace(PTRACE_ATTACH, pid, NULL, NULL)) < 0) {
		perror("ptrace(ATTACH)");
		exit(1);
	}

	int waitRes = waitpid(pid, &waitStat, WUNTRACED);
	if (waitRes != pid || !WIFSTOPPED(waitStat))
	{
		perror("HEH:");
		printf("Something went wrong...\n");
		exit(1);
	}


	//
	// Execute this in a loop
	//
	while (1)
	{

		int signum = 0;
	//
	// Add appropriate ptrace() calls here
	//
		printf ("Getting Registers\n");
		if ((ptrace (PTRACE_GETREGS, pid, NULL, &regs)) < 0)
		{
			perror ("ptrace(GETREGS):");
			exit (1);
		}
		if ((ptrace(PTRACE_SINGLESTEP, pid, NULL, NULL)) < 0)
		{
			perror ("ptrace(CONT):");
			exit(1);
		}

		
		waitRes = wait(&waitStat);
		signum = WSTOPSIG(waitStat);
		if (signum == SIGTRAP)
		{
			signum = 0;
		//
		// Add appropriate ptrace() call here
		// Hint: print out the following register values
		//
		// RAX (please print both orig_rax and rax)
		// RCX
		// RDX
		// RSP
		// RBP
		// R8
		// R9
		// RIP
	
			printf("RAX:\t%llx\n", regs.rax);
			printf("RCX:\t%llx\n", regs.rcx);
			printf("RDX:\t%llx\n", regs.rdx);
			printf("RSP:\t%llx\n", regs.rsp);
			printf("RBP:\t%llx\n", regs.rbp);
			printf("R8:\t%llx\n", regs.r8);
			printf("R9:\t%llx\n", regs.r9);
			printf("RIP:\t%llx\n", regs.rip);


		}
		else
		{
			printf("Unexpected signal %d\n", signum);
			ptrace(PTRACE_CONT, pid, 0, signum);
			break;
		}

	}

    return 0;
}

