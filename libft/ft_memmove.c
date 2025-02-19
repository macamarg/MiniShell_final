/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:04:14 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/12 16:59:25 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*csrc;
	unsigned char	*cdest;

	csrc = (unsigned char *)src;
	cdest = (unsigned char *)dest;
	if (!src && !dest)
		return (NULL);
	if (dest <= src)
	{
		while (n--)
		{
			*cdest++ = *csrc++;
		}
	}
	else
	{
		cdest += n - 1;
		csrc += n - 1;
		while (n--)
		{
			*cdest-- = *csrc--;
		}
	}
	return (dest);
}
/*
int	main(void)
{
	int	dest[100];
	int	src[] = {1, 2, 3, 4};
	size_t	n;

	n = 3;

	while (n--)
	{	
		printf("%i\n", src[n]);
	}
	ft_memmove (dest, src, sizeof(int)*3);
	n = 3;
	while (n--)
	{
		printf("%i", dest[n]);
	}
	return(0);
}
*/
