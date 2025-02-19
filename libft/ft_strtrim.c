/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 09:37:36 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/16 09:37:36 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	char	*dst;

	if (!s1)
		return (ft_strdup(""));
	if (!set)
		return (ft_strdup(s1));
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	while (len > 0 && ft_strrchr(set, s1[len - 1]))
		len--;
	dst = ft_calloc(len + 1, sizeof(char));
	if (dst == NULL)
		return (0);
	ft_strlcpy(dst, s1, len + 1);
	return (dst);
}
/*
	int	main(void)
	{
		char	*dst;
		char	*s1;
		char	*set;

		s1 = "abcdba";
		set = "acb";

		dst = ft_strtrim(s1, set);
		printf ("%s\n", dst);
		free(dst);
		return(0);
	}
*/