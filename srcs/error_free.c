#include "minishell.h"

int	ft_error(char *m, int error)
{
	printf("Error\n%s\n", m);
	return (error);
}

void	ft_free_cmd(t_cmd *cmd, size_t pipe_i)
{
	size_t		i;

	i = 0;
	while (i < pipe_i)
	{
		free(cmd->pipe[i].cmd);
		free(cmd->pipe[i].redirect);
		i++;
	}
	free(cmd->pipe);
	i = 0;
	while (cmd->envp[i])
		free(cmd->envp[i++]);
	free(cmd->envp);
}

void	ft_free_tokens(t_parse *parse, size_t token_size)
{
	size_t	i;

	i = 0;
	while (i < token_size)
	{
		free(parse->tokens[i].s);
		i++;
	}
	free(parse->tokens);
}

void    free_mini(t_parse *parse, t_cmd *cmd)
{
    free(parse->line);
    free_cmd(cmd);
}