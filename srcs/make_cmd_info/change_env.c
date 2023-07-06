#include "minishell.h"

static int  check_here(char s1, char s2)
{
    return (s1 == '<' && s2 == '<');
}

char	*get_env_val(char *key, t_info *info)
{
	char	*env_val;
	t_node	*node;

	node = info->env_list.front;
	while (node)
	{
		env_val = node->content;
		if (ft_strncmp(key, env_val, ft_strlen(key)) == 0)
			return (env_val);
		if (node->next == NULL)
			break ;
		node = node->next;
	}
	return (NULL);
}

int change_question(t_info *info, t_token *token, int *string_index)
{
    char   *tmp;

    tmp = NULL;
    if (info->ac < 2)
        return (FAILURE);
    tmp = ft_strjoin(info->av[1], &token->s[*string_index + 2]);
    if (tmp == NULL)
        return (FAILURE);
    free(token->s);
    token->s = tmp;
    return (SUCCESS);
}

int change_last_argument(t_token *token, t_info *info, int *string_index)
{
    char    *tmp;

    tmp = ft_strjoin(info->av[info->ac - 1], &token->s[*string_index + 2]);
    if (tmp == NULL)
        return (FAILURE);
    free(token->s);
    token->s = tmp;
    return (SUCCESS);
}

static int  change_abs(t_info *info, t_token *token, int string_index)
{
    char    *tmp;

    tmp = ft_strjoin(get_env_val("HOME", info), &token->s[string_index + 1]);
    if (tmp == NULL)
        return (FAILURE);
    tmp = ft_split(tmp, '=')[1];
    free(token->s);
    token->s = tmp;
    return (SUCCESS);
}

static int  change_child_exit_code(t_token *token, int *index)
{
    char    *exit_code;
    char    *tmp;
    char    *tmp2;

    exit_code = ft_itoa(g_exit_code);
    if (exit_code == NULL)
        return (FAILURE);
    token->s[*index] = '\0';
    tmp = ft_strjoin(token->s, exit_code);
    if (tmp == NULL)
    {
        free(exit_code);
        return (FAILURE);
    }
    tmp2 = ft_strjoin(tmp, &token->s[*index + 2]);
    if (tmp2 == NULL)
    {
        free(exit_code);
        free(tmp);
        return (FAILURE);
    }
    free(token->s);
    token->s = tmp2;
    *index += ft_strlen(exit_code) - 1;
    free(exit_code);
    free(tmp);
    return (SUCCESS);
}

static int change_env(t_info *info, t_token *token, \
    int *string_index, char *target)
{
    int     start_index;
    int     len;
    char    *env_val;

    start_index = *string_index;
    while (ft_isalnum(token->s[*string_index + 1]) \
        || token->s[*string_index + 1] == '_' \
        || token->s[*string_index + 1] == '-')
        (*string_index)++;
    len = *string_index - start_index;
    env_val = (char *) malloc(sizeof(char) * (len + 1));
    if (env_val == NULL)
        return (ft_error("malloc error\n", FAILURE));
    ft_strlcpy(env_val, &token->s[start_index + 1], len + 1);
    printf("env_val : %s\n", env_val);
    target = ft_strjoin(env_val, "=");
    if (target == NULL)
    {
        free(env_val);
        return (ft_error("malloc error\n", FAILURE));
    }
    printf("target : %s\n", target);
    free(env_val);
    printf("get_env_val : %s\n", get_env_val(target, info));
    if (get_env_val(target, info) != NULL)
        return (TRUE);
    free(target);
    return (FALSE);
}

static int  add_env(t_token *token, t_info *info, int *string_index, char *target)
{
    char    *env_val;
    char    *tmp;
    char    *tmp2;

    token->s[*string_index] = '\0';
    env_val = ft_strjoin(token->s, get_env_val(target, info));
    if (env_val == NULL)
        return (ft_error("change env error\n", FAILURE));
    tmp = ft_strjoin(env_val, &token->s[*string_index + 1]);
    if (tmp == NULL)
    {
        free(env_val);
        return (ft_error("change env error\n", FAILURE));
    }
    tmp2 = ft_strjoin(tmp, &token->s[*string_index + ft_strlen(target)]);
    if (tmp2 == NULL)
    {
        free(env_val);
        free(tmp);
        return (ft_error("change env error\n", FAILURE));
    }
    printf("tmp2 : %s\n", tmp2);
    free(tmp);
    free(token->s);
    free(env_val);
    free(target);
    token->s = tmp2;
    return (SUCCESS);
}

static int  is_env(t_info *info, t_token *token, int *string_index)
{
    size_t  index;
    char    *target;

    index = 0;
    target = NULL;
    if (token->s[*string_index] == '$' && \
        ft_isalpha(token->s[*string_index + 1]))
    {
        if (change_env(info, token, string_index, target) == TRUE)
        {
            if (add_env(token, info, string_index, target) == FAILURE)
                return (FAILURE);
            *string_index += ft_strlen(target) - 1;
        }
        else 
        {
            ft_strlcpy(&token->s[*string_index], \
                &token->s[*string_index + 1], \
                ft_strlen(token->s) + 1);
            *string_index -= index + 1;
        }
    }
    else if (token->s[*string_index] == '$' && \
        token->s[*string_index + 1] == '?')
        return (change_child_exit_code(token, string_index));
    else if (token->s[*string_index] == '$' && \
        token->s[*string_index + 1] == '_')
        return (change_last_argument(token, info, string_index));
    else if (token->s[*string_index] == '$' && \
        token->s[*string_index + 1] == '-')
    {
        if (change_question(info, token, string_index) == FAILURE)
            return (FAILURE);
    }
    else if (token->s[*string_index] == '~')
    {
        if (change_abs(info, token, *string_index) == FAILURE)
            return (FAILURE);
    }
    return (SUCCESS);
}

int if_env_change(t_info *info, t_parse *parse)
{
    size_t	token_index;
    int	    string_index;
    t_token	*token;

    token_index = 0;
    while (token_index < parse->token_count)
    {
        token = &parse->tokens[token_index];
        string_index = 0;
        while (token->s[string_index])
        {
            if (check_here(token->s[string_index], \
                token->s[string_index + 1]) == TRUE)
            {
                token_index++;
                break ;
            }
            if (is_env(info, token, &string_index) == FAILURE)
                return (FAILURE);
            string_index++;
        }
        token_index++;
    }
    return (SUCCESS);
}