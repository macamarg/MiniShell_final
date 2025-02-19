/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:16:48 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/17 11:23:26 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}
/*
int	main(void)
{
	char	dest[10];
	char	*src;
	int	n;
	int	i;

	src = "Hello World!";
	n = 3;
	i = 0;

	ft_memcpy(dest, src, n);
	while (i < n)
	{
		write (1, &dest[i], 1);
		i++;
	}
	return (0);
}
*/
