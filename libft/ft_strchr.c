/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:17:18 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/15 09:17:18 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	temp;

	temp = (unsigned char)c;
	while (*s)
	{
		if (*s == temp)
			return ((char *)s);
		s++;
	}
	if (*s == (char)temp)
		return ((char *)s);
	return (0);
}

/*
int	main(void)
{
	char	*s;
	char	c;

	s = "Hello World!";
	c = '\0';
	printf("%s\n", ft_strchr(s, c));
	return(0);
}
*/
