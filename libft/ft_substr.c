/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:16:40 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/15 14:16:40 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dst;

	i = 0;
	if (!s)
		return (NULL);
	else if ((size_t)start > ft_strlen(s))
		return (ft_strdup(""));
	else if ((ft_strlen(s) - (size_t)start) < len)
		len = ft_strlen(s) - (size_t)start;
	dst = (char *)malloc(sizeof(char) * len + 1);
	if (!dst)
		return (NULL);
	while (s[start] != '\0' && len > 0)
	{
		dst[i] = s[start];
		i++;
		start++;
		len--;
	}
	dst[i] = '\0';
	return (dst);
}

/*
int	main(void)
{
	char *src;
	unsigned int	start;
	size_t	size;
	char *sub;

	src = "Hello World!!";
	start = 20;
	size = 15;
	sub = ft_substr(src, start, size);
	printf("%s\n", sub);
	free (sub);
	return (0);
}
*/