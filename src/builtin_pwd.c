/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <jrocha-f@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 14:02:52 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/12/18 12:21:37 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	pwd_builtin:
	Executes the builtin pwd command and displays the current working 
	directory path.
	Returns 0 if successful, 1 if an error occured.

	Uses size as the initial buffer size (unless it is indeterminate or very
	large), and calls getcwd() with progressively larger buffers until it does
	not give an [ERANGE] error.

	TODO: Check possible errors without environment
*/

int ft_pwd(t_command *cmd)
{
	size_t	size;
	char	*buff;
	char	*ptr;
	int		error;

	size = 100;
	buff = NULL;
	ptr = NULL;
	error = ERANGE;
	buff = safe_malloc(sizeof(char)*size);
	while(error == ERANGE)
	{
		ptr = getcwd(buff, sizeof(char)*size);
		if (ptr)
			break;
		if (errno != ERANGE)
		{
			perror("error getcwd");
			return (EXIT_FAILURE);
		}			
		size *= 2;
		free (buff);
		buff = NULL;
		buff = safe_malloc(sizeof(char)*size);
	}
	ft_putendl_fd(ptr, 1); // TODO alterar para fd out
	//fd - posso imprimir para varios sitios
	//ver se apagarem o sitio onde estou
	//printf ("%s\n", ptr);
	free (buff);
	return (0);
}
