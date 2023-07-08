#include "minishell.h"

static void check_dir(const char *path)
{
    DIR *dir;

    dir = opendir(path);
    if (dir != NULL)
    {
		printf("minishell: %s: is a directory\n", path);
		closedir(dir);
		exit(126);
    }
}

static char *get_path(char *envp, char *cmd)
{
	char *tmp;
	char *path;

	tmp = ft_strjoin(envp, "/");
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	path = ft_strjoin(tmp, cmd);
	if (path == NULL)
	{
		free(tmp);
		exit(EXIT_FAILURE);
	}
	free(tmp);
	return (path);		
}

static int check_access_cmd(t_cmd *cmd, t_pipe *pipe)
{
	size_t    i;
    char    *path;

	i = 0;
    path = pipe->cmd_path;
    check_dir(path);
	if (path == NULL || access(path, F_OK) == SUCCESS)
		return (SUCCESS);
	if (path[0] == '\0')
		return (FAILURE);
	while (cmd->envp[i])
	{
		path = get_path(cmd->envp[i], pipe->cmd_path);
		check_dir(path);
		if (access(path, F_OK) == SUCCESS)
		{
			pipe->cmd_path = path;
			return (SUCCESS);
		}
		free(path);
		i++;
	}
	return (FAILURE);
}

void exe_child(t_info *info, t_parse *parse, t_cmd *cmd, t_pipe *pipe)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (check_builtin(pipe) == FAILURE && \
		check_access_cmd(cmd, pipe) == FAILURE)
	{
		printf("minishell: %s: command not found\n", pipe->cmd[0]);
		free_mini(parse, cmd);
		exit(127);
	}
	else
	{
		// file descriptor 설정
		if (check_builtin(pipe) == TRUE)
			exe_builtin(parse, cmd, info, pipe);
		else
			// 실행 
			exit(0);
		exit(0);		
	}
}
