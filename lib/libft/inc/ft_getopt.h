/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getopt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/04 18:43:33 by sgardner          #+#    #+#             */
/*   Updated: 2018/04/11 16:58:58 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GETOPT_H
# define FT_GETOPT_H

int	ft_getopt(int ac, char *const av[], const char *optstring);

extern char	*g_optarg;
extern int	g_optind;
extern int	g_opterr;
extern int	g_optopt;
#endif
