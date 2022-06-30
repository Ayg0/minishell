#include <unistd.h>
#include <stdlib.h>


int	*exit_code(void)
{
	static int	code;

	return (&code);
}

int	get_exit_code(void)
{
	int	i;

	i = *(exit_code());
	return (i);
}

void	set_exit_code(int status)
{
	int	*p;

	p = exit_code();
	*p = status;
}

int	main(int ac, char **av, char **envp)
{
	set_exit_code(0);
	printf("%d\n", get_exit_code());
	set_exit_code(50)
}