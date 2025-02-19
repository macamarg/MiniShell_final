/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:00:08 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/17 16:34:35 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** LIBRARY: <strings.h>
** SYNOPSIS: write zeroes to a byte string
**
** DESCRIPTION:
** 		The bzero() function writes n zeroed bytes to the string s. If n is
**	zero, bzero() does nothing.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	if (!s)
		return ;
	ft_memset(s, 0, n);
}
/*
int	main(void)
{
	char	s[10];
	int		c;
	size_t	i;

	c = 'A';
	i = 0;

	ft_memset(s, c, 10);
	while(i < 10)
	{
		write(1, &s[i], 1);
		write (1, "\n", 1);
		i++;
	}
	i = 0;
	ft_bzero(s, 10);
		while(i < 10)
	{
		write(1, &s[i], 1);
		write (1, "\n", 1);
		i++;
	}
	return(0);
}
*/