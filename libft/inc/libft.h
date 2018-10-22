/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 01:23:55 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/21 04:18:21 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>

# define UNUSED(x)		(void)(x)
# define LEN(x)			ft_strlen(x)
# define NLEN(x, y)		ft_strnlen(x, y)
# define MAX(x, y)		((x > y) ? x : y)
# define MIN(x, y)		((x < y) ? x : y)

# ifndef FALSE
#  define FALSE 		0
# endif
# ifndef TRUE
#  define TRUE			!FALSE
# endif

typedef int				t_bool;
typedef unsigned char	t_byte;
typedef unsigned int	t_uint;

/*
** Reproduction of <ctype.h>
*/

# define IS_ASCII(c)	(!(c >> 7))
# define IS_BLANK(c)	(c == ' ' || c == '\t')
# define IS_DIGIT(c)	((t_uint)(c - '0') < 10)
# define IS_GRAPH(c)	((t_uint)(c - '!') < 94)
# define IS_LOWER(c)	((t_uint)(c - 'a') < 26)
# define IS_PRINT(c)	((t_uint)(c - ' ') < 95)
# define IS_CNTRL(c)	(!IS_PRINT(c))
# define IS_UPPER(c)	((t_uint)(c - 'A') < 26)
# define IS_ALPHA(c)	(IS_LOWER(c) || IS_UPPER(c))
# define IS_ALNUM(c)	(IS_ALPHA(c) || IS_DIGIT(c))
# define IS_PUNCT(c)	(IS_PRINT(c) && !FT_ISALNUM(c) && c != ' ')
# define IS_SPACE(c)	(c == ' ' || (t_uint)(c - '\t') < 5)
# define IS_XDIGIT(c)	(ISDIGIT(c) || (t_uint)(c - 'A') < 6)
# define TO_ASCII(c)	(c & 0x7F)
# define TO_LOWER(c)	(IS_UPPER(c) ? c + ' ' : c)
# define TO_UPPER(c)	(IS_LOWER(c) ? c - ' ' : c)

/*
** Reproduction of <stdlib.h>
*/

# define ABS(x)			((x < 0) ? -x : x)

int		ft_atoi(const char *str);

/*
** Standard I/O: libft exclusive
*/

char	*ft_itoa(int n);
void	ft_putendl(const char *s);
void	ft_putendl_fd(const char *s, int fd);
void	ft_putchar(char c);
void	ft_putchar_fd(char c, int fd);
void	ft_putnbr(int n);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr(const char *s);
void	ft_putstr_fd(const char *s, int fd);

/*
** Reproduction of <string.h>
*/

void	*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *s1, const void *s2, size_t n);
void	*ft_memmove(void *s1, const void *s2, size_t n);
void	*ft_memset(void *s, int c, size_t n);
char	*ft_stpcpy(char *s1, const char *s2);
char	*ft_stpncpy(char *s1, const char *s2, size_t n);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *s1, const char *s2);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
char	*ft_strncat(char *s1, const char *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strncpy(char *s1, const char *s2, size_t n);
char	*ft_strndup(const char *s, size_t size);
size_t	ft_strnlen(const char *s, size_t maxlen);
char	*ft_strrchr(const char *s, int c);
char	*ft_strstr(const char *s1, const char *s2);

/*
** BSD <string.h>
*/

size_t	ft_strlcat(char *s1, const char *s2, size_t n);
size_t	ft_strlcpy(char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *s1, const char *s2, size_t n);

/*
** Strings and memory: libft exclusive
*/

void	*ft_memalloc(size_t size);
void	ft_memdel(void **ap);
void	*ft_revbytes(void *ptr, size_t n);
char	*ft_strcapitalize(char *str);
void	ft_strclr(char *s);
void	ft_strdel(char **as);
int		ft_strequ(const char *s1, const char *s2);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strlowcase(char *str);
int		ft_strnequ(const char *s1, const char *s2, size_t n);
char	*ft_strnew(size_t size);
char	*ft_strrev(char *str);
char	**ft_strsplit(const char *s, char delim);
char	*ft_strsub(const char *s, unsigned int start, size_t len);
char	*ft_strtrim(const char *s);
char	*ft_strupcase(char *str);
#endif
