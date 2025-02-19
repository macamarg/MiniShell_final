/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:07:48 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/17 14:35:23 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	if (!s || !f)
		return ;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	f(unsigned int n, char *ptr)
{
	if (n == 0)
		*ptr = ft_toupper(*ptr);
}
*/
/*
int	main(void)
{
	char	str[50] = "hello World!";

	ft_striteri(str, f);
	printf("%s", str);
	return(0);
}
*/