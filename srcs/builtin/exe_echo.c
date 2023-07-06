#include "minishell.h"

static void echo_str(char **str, int flag)
{
    int i;

    i = 0;
    while (str[i])
    {
        printf("%s", str[i]);
        if (str[i + 1] != NULL)
            printf(" ");
        i++;
    }
    if (flag == FALSE)
        printf("\n");
}

int exe_echo(t_parse *parse, t_cmd *cmd, t_info *info, t_pipe *pipe)
{
    if (pipe->cmd[1] == NULL)
	{
		printf("\n");
	}
	else if (ft_strncmp(pipe->cmd[1], "-n", 3) == 0)
	{
		echo_str(pipe->cmd + 2, TRUE);
	}
	else
	{
		echo_str(pipe->cmd + 1, FALSE);
	}
    exit(EXIT_SUCCESS);
}
