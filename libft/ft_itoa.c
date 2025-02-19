/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:42:24 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/16 15:42:24 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_num_len(long int n)
{
	int	len;

	len = 1;
	if (n < 0)
		len++;
	while (n >= 10 || n <= -10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_putchar(char *ptr, long int n, int len, int sign)
{
	ptr[len] = '\0';
	len--;
	if (sign == -1)
		ptr[0] = '-';
	while (len >= 0 && ptr[len] != '-')
	{
		ptr[len] = n % 10 + '0';
		n = n / 10;
		len--;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	int			len;
	int			sign;
	long int	nb;
	char		*ptr;

	nb = n;
	sign = 1;
	len = ft_num_len(n);
	if (n < 0)
	{
		sign = -1;
		nb = nb * -1;
	}
	ptr = ft_calloc(len + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	ptr = ft_putchar(ptr, nb, len, sign);
	return (ptr);
}
/*
int	main(void)
{
	int	n;
	char	*ptr;

	n = 0;
//	n = 2147483647;
//	n = -2147483648;
	ptr = NULL;
	ptr = ft_itoa(n);
	printf("%s\n", ptr);
	free(ptr);
	return(0);
}
*/