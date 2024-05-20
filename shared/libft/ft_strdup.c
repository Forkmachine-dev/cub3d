/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 05:36:05 by mel-akhd          #+#    #+#             */
/*   Updated: 2023/01/09 13:20:00 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	int		i;
	char	*s_dup;

	i = 0;
	s_len = ft_strlen(s);
	s_dup = (char *)malloc(s_len + 1);
	if (!s_dup)
		return (NULL);
	while (s[i])
	{
		s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = 0;
	return (s_dup);
}
