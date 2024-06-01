/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-akhd <mel-akhd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 18:44:26 by mel-akhd          #+#    #+#             */
/*   Updated: 2024/06/01 23:54:55 by mel-akhd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	one_or_space(char c)
{
	return (c == '1' || is_space(c));
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	is_valid_char(char c)
{
	return (c == '1' || c == '0' || c == '2' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == ' ' || c == 'V' || c == 'H');
}

char	*get_path(char *line, int i)
{
	int		to_copy;
	char	*new_path;
	char	*final_path;

	to_copy = 0;
	while (line[i + to_copy] && line[i + to_copy] != '\n')
		to_copy++;
	new_path = ft_substr(line, i, to_copy);
	final_path = ft_strtrim(new_path, " ");
	free(new_path);
	return (final_path);
}

int	get_image_path(t_cub3d *cub, char **dist, char *line)
{
	int	i;
	int	to_copy;
	int	len;

	i = 0;
	to_copy = 0;
	if (!line || !line[i])
		return (0);
	i = skip_spaces(&line);
	if (line[i] == '\0')
		return (0);
	*dist = get_path(line, i);
	if (!*dist)
		return (0);
	len = ft_strlen(*dist);
	if (len < 4 || ft_strncmp(*dist + len - 4, ".png", 4) != 0)
	{
		free(*dist);
		cub->parsing_checklist.wrong_texture_ext = true;
		return (0);
	}
	return (1);
}
