/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:43:55 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/15 09:43:55 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && n > 0)
	{
		if (*s1 != *s2)
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
/*
int	main(void)
{
	char	*s1;
	char	*s2;
	size_t	 n;

	s1 = "AAAA";
	s2 = "ABCD";
	n = 3;
	printf("%i\n", ft_strncmp(s1, s2, n));
	return (0);
}
*/