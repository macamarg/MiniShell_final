/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 11:33:30 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/13 11:33:30 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	len_src;

	len_src = ft_strlen(src);
	if (!size)
		return (len_src);
	while ((*src) && --size)
		*dst++ = *src ++;
	*dst = '\0';
	return (len_src);
}

/*
int	main (void)
{
	char	dst[50];
	const char	*src;

	src = "oi!";
	printf("%i\n", ft_strlcpy (dst, src, 15));
	printf("%s\n", dst);
	printf("%s\n", src);
	return (0);
}
*/