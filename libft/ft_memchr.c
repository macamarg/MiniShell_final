/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:18:02 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/15 10:18:02 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Searches for the first occurrence of the character c in the memory block
pointed to by str, up to a specified length n. It iterates through the
memory block using a while loop and checks if each byte matches c. If a
match is found, it returns a pointer to that byte. If no match is found
within the specified length, it returns NULL.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = (void *)s;
	if (s == NULL)
		return (NULL);
	while (n--)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	return (0);
}

/*int	main (void)
{
	char	*str;
	char	*found;
	int	c;
	size_t	n;

	str = "Hello World!";
	c = 'e';
	n = 10;
	found = ft_memchr(str, c, n);
	if (found != NULL)
		printf("Found character '%c' at position: %s\n", c, found);
	else
		printf("Character '%c' not found within the
			first %zu characters.\n", c, n);
	return (0);
}
*/