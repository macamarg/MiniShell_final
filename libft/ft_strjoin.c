/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 14:57:13 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/15 14:57:13 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len_1;
	size_t	len_2;
	size_t	i;

	i = 0;
	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	dst = (char *)malloc((len_1 + len_2) * sizeof(char) + 1);
	if (dst == NULL)
		return (NULL);
	while (*s1)
		dst[i++] = *s1++;
	while (*s2)
		dst[i++] = *s2++;
	dst[i] = '\0';
	return (dst);
}
/*
	int	main(void)
	{
		char	*s1;
		char	*s2;
		char	*dst;

		s1 = "Hello ";
		s2 = "world!";
		dst = ft_strjoin(s1, s2);
		printf("%s", dst);
		free(dst);
		return(0);
	}
	*/