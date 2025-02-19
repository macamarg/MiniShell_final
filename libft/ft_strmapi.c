/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:38:32 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/17 17:49:13 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Map a given function f over each character of the string s, potentially
transforming each character based on its position in the string and the
character itself, and to return a newly created string that contains all
the transformed characters.*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len;
	char	*dst;

	i = 0;
	len = ft_strlen(s) + 1;
	dst = (char *)malloc(sizeof(char) * (len));
	if (!dst)
		return (NULL);
	while (s[i] != '\0')
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
/*
char	f(unsigned int n, char c)
{
	if (n == 0)
		c = ft_toupper(c);
	return (c);
}

int	main(void)
{
	char	*str;
	char	*dst;
	void	(*f_ptr);

	str = "hello world!";
	f_ptr = &f;
	dst = ft_strmapi(str, f_ptr);
	printf("%s", dst);
	free (dst);
	return(0);
}
*/
