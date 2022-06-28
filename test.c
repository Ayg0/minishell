#include <unistd.h>
#include <stdlib.h>

int	main(int ac, char **av, char **envp)
{
	char *wow[2];
	wow[0] = "./env";
	wow[1] = NULL;
	execve("./env", wow, envp);
}