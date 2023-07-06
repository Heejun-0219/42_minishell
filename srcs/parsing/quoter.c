// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   quoter.c                                           :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: mi <mi@student.42seoul.kr>                 +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/07/06 03:25:28 by mi                #+#    #+#             */
// /*   Updated: 2023/07/06 04:00:23 by mi               ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */


// #include "minishell.h"

// // void check_toggle_quote_type(char **tokens_str, int i, int *doub, int *single)
// // void check_toggle_quote_type(char **tokens_str, int i, int *quoter_type)
// // {
// // 	if (tokens_str[i][0] == '\"' && !(*single))
// // 	if (tokens_str[i][0] == '\"' && !(quoter_type[1]))
// // 		*doub = !(*doub);
// // 	if (tokens_str[i][0] == '\'' && !(*doub))
// // 		*single = !(*single);
// // }
// void check_toggle_quote_type(char **tokens_str, int i, int *quoter_type)
// {
// 	if (tokens_str[i][0] == '\"' && !(quoter_type[1]))
// 		quoter_type[0] = !(quoter_type[0]);
// 	if (tokens_str[i][0] == '\'' && !(quoter_type[0]))
// 		quoter_type[1] = !(quoter_type[1]);
// }

// // void merge_tokens(char **tokens_str, int *i, int *j, int *doub, int *single)
// // {
// // 	size_t array_size;

// // 	if (*doub || *single)
// // 	{
// // 		(*j) = (*i) + 1;
// // 		while (tokens_str[*j] != NULL && !is_end_of_quote_scope(tokens_str[*j], *doub, *single))
// // 			merge_and_free_tokens(&tokens_str[*i], tokens_str[(*j)++]);
// // 		if (is_end_of_quote_scope(tokens_str[*j], *doub, *single))
// // 		{
// // 			merge_and_free_tokens(&tokens_str[*i], tokens_str[*j]);
// // 			*doub = ft_not(*doub); 
// // 			*single = ft_not(*single);
// // 		}
// // 		array_size = sizeof(char *) * (get_array_size(tokens_str) - *j);
// // 		memmove(&tokens_str[*i + 1], &tokens_str[*j + 1], array_size);
// // 	}
// // }

// void merge_tokens(char **tokens_str, int *i, int *j, int *quoter_type)
// {
// 	size_t array_size;

// 	if (quoter_type[0] || quoter_type[1])
// 	{
// 		(*j) = (*i) + 1;
// 		while (tokens_str[*j] != NULL && !is_end_of_quote_scope(tokens_str[*j], quoter_type)){
// 			merge_and_free_tokens(&tokens_str[*i], tokens_str[*j]);
// 			(*j)++;
// 		}
// 		if (is_end_of_quote_scope(tokens_str[*j], quoter_type))
// 		{
// 			merge_and_free_tokens(&tokens_str[*i], tokens_str[*j]);
// 			ft_not(&(quoter_type[0]));
// 			ft_not(&(quoter_type[1]));
// 		}
// 		array_size = sizeof(char *) * (get_array_size(tokens_str) - *j);
// 		memmove(&tokens_str[*i + 1], &tokens_str[*j + 1], array_size);
// 	}
// }

// void merge_quoted_tokens(char **tokens_str)
// {
// 	int i;
// 	int j;
// 	int doub;
// 	int single;
// 	int *quoter_type;

// 	i = 0;
// 	quoter_type = (int *) ft_malloc(sizeof(int) * 2);
// 	quoter_type[0] = 0;
// 	quoter_type[1] = 0;
// 	while (tokens_str[i] != NULL)
// 	{
// 		check_toggle_quote_type(tokens_str, i, quoter_type);
// 		merge_tokens(tokens_str, &i, &j, quoter_type);
// 		i++;
// 	}
// 	free(quoter_type);
// }