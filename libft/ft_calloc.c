/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 13:32:40 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/15 13:32:40 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	tot_size;

	if (nmemb == 0 || size == 0)
	{
		ptr = (void *)malloc(0);
		if (!ptr)
			return (NULL);
		return (ptr);
	}
	tot_size = size * nmemb;
	if (tot_size / size != nmemb)
		return (NULL);
	ptr = (void *)malloc(tot_size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, tot_size);
	return (ptr);
}
/*
int	main(void)
{
	size_t	nmemb;
	size_t	size;
	int	*ptr;
	size_t		i;

	nmemb = 12;
	size = sizeof(int);
	ptr = ft_calloc(nmemb, size);
	i = 0;
	while(i < nmemb)
	{
		printf("%i, ", ptr[i]);
		i++;
	}
	i = 0;
	while (i < nmemb)
	{
		ptr[i] = i;
		i++;
	}
	printf("\n");
		i = 0;
	while(i < nmemb)
	{
		printf("%i, ", ptr[i]);
		i++;
	}
	free(ptr);
	return (0);
}
*/
