/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:01:58 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/15 14:01:58 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*dst;

	i = 0;
	len = ft_strlen (s);
	dst = ft_calloc(len + 1, sizeof(char));
	if (dst == NULL)
		return (NULL);
	while (i < len)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
/*
int	main(void)
{
	char	*src;
	char	*dst;

	src = "Hello World!";
	dst = ft_strdup(src);
	printf("%s\n", dst);
	free (dst);
	return (0);
}
*/