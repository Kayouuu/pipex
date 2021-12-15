/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psaulnie <psaulnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:46:14 by psaulnie          #+#    #+#             */
/*   Updated: 2021/11/15 16:25:52 by psaulnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Return the difference between the first two differents characters */

#include "libft.h"

int	ft_strncmp(const char *first, const char *second, size_t length)
{
	size_t	n;

	n = 0;
	if (length < 0)
		return (-1);
	while (n < length && (first[n] || second[n]))
	{
		if (first[n] != second[n])
			return ((unsigned char)first[n] - second[n]);
		n++;
	}
	return (0);
}
