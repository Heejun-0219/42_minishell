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
		if (ft_strncmp(env_val, key, ft_strlen(key)) == 0)
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
    int *string_index, t_token *target)
{
    int     len;
    char    *env_val;

    target->token_index = (size_t) *string_index;
    while (ft_isalnum(token->s[*string_index + 1]) \
        || token->s[*string_index + 1] == '_' \
        || token->s[*string_index + 1] == '-')
        (*string_index)++;
    len = *string_index - (int) target->token_index;
    env_val = (char *) malloc(sizeof(char) * (len + 1));
    if (env_val == NULL)
        return (ft_error("malloc error\n", FAILURE));
    ft_strlcpy(env_val, &token->s[target->token_index + 1], len + 1);
    target->s = ft_strjoin(env_val, "=");
    if (target->s == NULL)
    {
        free(env_val);
        return (ft_error("malloc error\n", FAILURE));
    }
    free(env_val);
    if (get_env_val(target->s, info) != NULL)        
        return (TRUE);
    free(target->s);
    return (FALSE);
}

static int  add_env(t_token *token, t_info *info, int *string_index, t_token *target)
{
    char    *env_val;
    char    *tmp;

    token->s[target->token_index] = '\0';
    env_val = ft_strjoin(token->s, ft_split(get_env_val(target->s, info), '=')[1]);
    if (env_val == NULL)
        return (ft_error("change env error\n", FAILURE));
    tmp = ft_strjoin(env_val, &token->s[*string_index + 1]);
    if (tmp == NULL)
    {
        free(env_val);
        return (ft_error("change env error\n", FAILURE));
    }
    free(token->s);
    free(env_val);
    free(target->s);
    token->s = tmp;
    return (SUCCESS);
}

static int  is_env(t_info *info, t_token *token, int *string_index)
{
    t_token *tmp;
    int     env_len;
    int     i;

    env_len = 0;
    i = 0;
    tmp = (t_token *) malloc(sizeof(t_token));
    if (token->s[*string_index] == '$' && \
        ft_isalpha(token->s[*string_index + 1]))
    {
        if (change_env(info, token, string_index, tmp) == TRUE)
        {
            env_len = (int)ft_strlen(tmp->s);
            i = ft_strlen(ft_split(get_env_val(tmp->s, info), '=')[1]);
            if (add_env(token, info, string_index, tmp) == FAILURE)
            {
                free(tmp);
                free(tmp->s);
                return (FAILURE);
            }
            *string_index = (int)tmp->token_index + i - 1;
        }
        else 
        {
            ft_strlcpy(&token->s[tmp->token_index], \
                &token->s[*string_index + 1], \
                ft_strlen(token->s) + 1);
            *string_index -= env_len + 1;
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
    free(tmp);
    return (SUCCESS);
}

int if_env_change(t_info *info, t_parse *parse)
{
    int	    string_index;
    t_token	*token;

    token = (t_token *) malloc(sizeof(t_token));
    token->token_index = 0;
    while (token->token_index < parse->token_count)
    {
        token = &parse->tokens[token->token_index];
        string_index = 0;
        while (token->s[string_index])
        {
            if (check_here(token->s[string_index], \
                token->s[string_index + 1]) == TRUE)
            {
                token->token_index++;
                break ;
            }
            if (is_env(info, token, &string_index) == FAILURE)
                return (FAILURE);
            string_index++;
        }
        token->token_index++;
    }
    token = NULL;
    return (SUCCESS);
}