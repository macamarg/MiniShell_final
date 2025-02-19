/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:37:46 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/15 09:37:46 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	temp;
	int				len;
	char			*ptr;

	temp = (unsigned char)c;
	len = ft_strlen(s);
	ptr = (char *)s;
	while (len >= 0)
	{
		if (ptr[len] == temp)
			return (&ptr[len]);
		len--;
	}
	return (0);
}

/*
int	main(void)
{
	char	*s;
	char	c;

	s = "Hello World!";
	c = 'o';
	printf("%s\n", ft_strrchr(s, c));
	return(0);
}
*/