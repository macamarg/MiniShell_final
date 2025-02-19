/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safemalloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macamarg <macamarg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:51:22 by macamarg          #+#    #+#             */
/*   Updated: 2024/12/02 12:56:00 by macamarg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	exit_err(char *msg, int err)
{
	printf("[%i] %s\n", err, msg);
	exit (err);
}

/*
	SUSv2 requires malloc(), calloc(), and realloc() to set errno to ENOMEM
       upon  failure.
*/

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = ft_calloc(1, bytes);
	if (!ret)
		exit_err("Error in memory allocation", ENOMEM);
	return (ret);
}
