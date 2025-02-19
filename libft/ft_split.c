/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrocha-f <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:37:06 by jrocha-f          #+#    #+#             */
/*   Updated: 2024/04/16 10:37:06 by jrocha-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_words(char *str, char c)
{
	int	count;
	int	new_word;

	new_word = 1;
	count = 0;
	while (*str)
	{
		if (new_word == 1 && *str != c)
		{
			count++;
			new_word = 0;
		}
		else if (new_word == 0 && *str == c)
			new_word = 1;
		str++;
	}
	return (count);
}

char	**ft_2d_array(int dim_1, int *dim_2)
{
	char	**array;
	int		i;

	i = 0;
	array = (char **)malloc(sizeof(char *) * (dim_1 + 1));
	if (!array)
		return (NULL);
	while (i < dim_1)
	{
		array[i] = (char *)malloc(sizeof(char) * (dim_2[i] + 1));
		if (!array[i])
		{
			while (--i >= 0)
				free (array[i]);
			free (array);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}

int	*ft_lens_array(int *lens, char *s, char c)
{
	int	j;
	int	i;
	int	len;

	i = 0;
	j = 0;
	while (s[j] != '\0')
	{
		len = 0;
		while (s[j] == c)
			j++;
		while (s[j] != c && s[j] != '\0')
		{
			len++;
			j++;
		}
		if (len > 0)
		{
			lens[i] = len;
			i++;
		}
	}
	return (lens);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	int		i;
	int		*lens;
	char	**array;

	if (!s)
		return (NULL);
	words = ft_count_words((char *)s, c);
	lens = (int *)malloc(sizeof(int) * words);
	if (!lens)
		return (NULL);
	lens = ft_lens_array(lens, (char *)s, c);
	array = ft_2d_array(words, lens);
	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		if (*s != '\0' && *s != c)
			ft_strlcpy(array[i], s, lens[i] + 1);
		s += lens[i];
		i++;
	}
	free (lens);
	return (array);
}

/*
int	main(void)
{
	char	*str;
	char	**array;
	char	c;
	int	i;

	i = 0;
	str = "Hello,world,i,am,here";
	c = ',';
	array = ft_split(str, c);
	while (i < ft_count_words(str, c))
		{
			printf("%s\n", array[i]);
			i++;
		}
	printf("%i\n", ft_count_words(str, c));
	while (--i >= 0)
		free(array[i]);
	free(array);
	return(0);
}
*/