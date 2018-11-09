/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mchain.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 15:57:27 by sgardner          #+#    #+#             */
/*   Updated: 2018/07/10 02:03:02 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_memmgr.h"

t_mchain	**ft_mcgetall(void)
{
	static t_mchain	*head;

	return (&head);
}

t_mchain	*ft_mcget(const char *label)
{
	t_mchain	**mchain;

	mchain = ft_mcgetall();
	while (*mchain && ft_strcmp(label, (*mchain)->label))
		mchain = &(*mchain)->next;
	if (!*mchain)
	{
		if (!(*mchain = (t_mchain *)ft_memalloc(sizeof(t_mchain))))
			return (NULL);
		ft_stpncpy((*mchain)->label, label, MCHAIN_LABEL_MAXLEN);
	}
	return (*mchain);
}

int			ft_mcdel(t_mchain *mchain)
{
	t_mchain	**mchead;
	t_mchain	*next_chain;
	t_mlink		*next_link;
	int			count;

	if (!mchain)
		return (-1);
	count = 0;
	while (mchain->start)
	{
		next_link = mchain->start->next;
		if (CANFREE(mchain->start))
			free(mchain->start->ptr);
		free(mchain->start);
		mchain->start = next_link;
		++count;
	}
	mchead = ft_mcgetall();
	while (*mchead && *mchead != mchain)
		mchead = &(*mchead)->next;
	next_chain = mchain->next;
	free(mchain);
	*mchead = next_chain;
	return (count);
}

int			ft_mcdelall(void)
{
	t_mchain	**mchain;
	t_mchain	*next_chain;
	t_mlink		*next_link;
	int			count;

	mchain = ft_mcgetall();
	count = 0;
	while (*mchain)
	{
		while ((*mchain)->start)
		{
			next_link = (*mchain)->start->next;
			if (CANFREE((*mchain)->start))
				free((*mchain)->start->ptr);
			free((*mchain)->start);
			(*mchain)->start = next_link;
			++count;
		}
		next_chain = (*mchain)->next;
		free(*mchain);
		*mchain = next_chain;
	}
	return (count);
}

t_bool		ft_mcexists(const char *label)
{
	t_mchain	**mchain;

	mchain = ft_mcgetall();
	while (*mchain && ft_strcmp(label, (*mchain)->label))
		mchain = &(*mchain)->next;
	return (*mchain != NULL);
}
