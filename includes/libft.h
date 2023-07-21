/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejunki <heejunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:52:32 by heejunki          #+#    #+#             */
/*   Updated: 2023/07/21 01:24:46 by heejunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		ft_atoi(const char *str);
int		check_max_or_min(long num, const char c, int minus);
void	*ft_memset(void *p, int val, size_t len);
void	ft_bzero(void *p, size_t len);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
char	*ft_strchr(const char *str, int c);
char	*ft_strdup(const char *src);
size_t	ft_strlen(const char *str);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, char *src, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *str, int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_strcmp(const char *str1, const char *str2);

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const	*s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
int		get_count(char const *s, char c);
char	*ft_strndup(char *str, size_t str_len);
char	**null_free(char **res);
int		count_strlen(char *str, char c, int str_in);
char	*ft_itoa(int n);
int		integer_len(int n);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	*ft_malloc(size_t size);
void	*ft_realloc(void *ptr, size_t size);
void	ft_not(int *value);
int		ft_count_char(char *str, char c);

#endif