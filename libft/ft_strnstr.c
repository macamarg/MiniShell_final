/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:53:17 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/15 11:53:17 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	char	*ptr;

	ptr = (char *)big;
	if (!little || little[0] == '\0')
		return (ptr);
	if (!big)
		return (NULL);
	while (*ptr && len)
	{
		i = 0;
		while ((ptr[i] == little[i]) && len > i)
			i++;
		if (little[i] == '\0')
			return (ptr);
		ptr++;
		len --;
	}
	return (NULL);
}
/*
int	main(void)
{
	char	*big;
	char	*litle;
	char	*found;
	size_t	n;

	big = "Hello AABC World!";
	litle = "ABC";
	n = 15;
	found = ft_strnstr (big, litle, n);
	printf("%s\n", found);
	return (0);
	}
*/