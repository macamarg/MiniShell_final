/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:15:33 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/17 16:32:27 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = c;
		i++;
	}
	return (s);
}
/*
int     main(void)
{
	char s[10];
	int     c;
	size_t i;

	c = 'A';
	i = 0;

	ft_memset(s, c, 10);
	while(i < 10)
	{
		write(1, &s[i], 1);
		write (1, "\n", 1);
		i++;
	}
	return(0);
}
*/
