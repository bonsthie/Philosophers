/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babonnet <babonnet@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 22:34:33 by babonnet          #+#    #+#             */
/*   Updated: 2024/04/08 22:42:17 by babonnet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_isspace(int c)
{
	return (c == ' ' || (unsigned int)c - '\t' < 5);
}

int	ft_isdigit(int c)
{
	return ((unsigned int)c - '0' < 10);
}

int	ft_toupper(int c)
{
	return (c - (c >= 'a' && c <= 'z') * 32);
}

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	i;

	i = 0;
	if (length == 0)
		return (0);
	while (first[i] == second[i] && first[i] && i < length - 1)
		i++;
	return ((unsigned char) first[i] - (unsigned char) second[i]);
}
