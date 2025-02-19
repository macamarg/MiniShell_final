/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 15:22:26 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/13 15:22:26 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_d;
	size_t	len_s;
	size_t	i;

	len_d = ft_strlen(dst);
	len_s = ft_strlen(src);
	i = len_d;
	if (size > len_d)
	{
		while (*dst)
			dst++;
		while (*src && i < size - 1)
		{
			*dst++ = *src++;
			i++;
		}
		*dst = '\0';
		return (len_d + len_s);
	}
	else
		return (size + len_s);
}
/*
int	main(void)
{
	const char *src;
	char dst[50] = "Hello ";
	size_t	size;
	size = 50;

	src = "world\n";
	printf("%li\n", ft_strlcat(dst, src, size));
	printf("%s", dst);
	return (0);
}
*/