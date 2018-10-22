/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmgr.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:56:20 by sgardner          #+#    #+#             */
/*   Updated: 2018/10/10 00:36:03 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MEMMGR_H
# define FT_MEMMGR_H
# include "libft.h"
# include <stdint.h>

# define MCHAIN_LABEL_MAXLEN	26
# define NOFREE					(~(SIZE_MAX >> 1))
# define CANFREE(mlink)			(!(mlink->size & NOFREE))
# define REALSIZE(x)			(x & (SIZE_MAX >> 1))
# define MLSIZE(mlink)			REALSIZE(mlink->size)

typedef struct	s_mchain
{
	char			label[MCHAIN_LABEL_MAXLEN];
	int				link_count;
	struct s_mlink	*start;
	struct s_mlink	*end;
	struct s_mchain	*next;
}				t_mchain;

typedef struct	s_mlink
{
	struct s_mchain	*mchain;
	void			*ptr;
	size_t			size;
	struct s_mlink	*next;
}				t_mlink;

/*
** Memchain functions
*/

t_mchain		**ft_mcgetall(void);
t_mchain		*ft_mcget(const char *label);
int				ft_mcdel(t_mchain *mchain);
int				ft_mcdelall(void);
t_bool			ft_mcexists(const char *label);

/*
** Memlink functions
*/

t_mlink			*ft_mladd(t_mchain *mchain, void *ptr, size_t size);
t_mlink			*ft_mlappend(t_mchain *mchain, void *ptr, size_t size);
void			**ft_mlarray(t_mchain *mchain);
void			*ft_mlalloc(t_mchain *mchain, size_t size);
t_mlink			*ft_mldel(t_mlink *mlink);
t_mlink			*ft_mlfind(t_mchain *mchain, void *ptr);
t_mlink			*ft_mlpop(t_mchain *mchain);
t_mlink			*ft_mlremove(t_mlink *mlink);
t_mlink			*ft_mlrev(t_mchain *mchain);
size_t			ft_mlsize(t_mlink *mlink);
t_mlink			*ft_mlxfer(t_mlink *mlink, t_mchain *mchain);
#endif
