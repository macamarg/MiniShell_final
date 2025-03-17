/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:58:26 by jrocha-f          #+#    #+#             */
/*   Updated: 2025/03/17 10:46:03 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (*s != '\0')
	{
		s ++;
		len ++;
	}
	return (len);
}
/*
int	main (void)
{
	const char	*src;

	src = "Hello World!";
	printf("%i\n", ft_strlen (src));
	return (0);
}
*/