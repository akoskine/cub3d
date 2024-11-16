/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dmh.c            		                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoskine <akoskine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 22:24:43 by akoskine          #+#    #+#             */
/*   Updated: 2024/02/28 21:41:23 by akoskine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dmh	*dmh_new(size_t size, void *ptr)
{
	t_dmh	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(t_dmh) * 1);
	if (!res)
		return (NULL);
	res->next = NULL;
	if (ptr != NULL)
		res->void_hold = ptr;
	else
		res->void_hold = malloc(sizeof(char) * size);
	if (!res->void_hold)
		return (NULL);
	return (res);
}

void	*dmh(t_game *game, size_t size, void *ptr)
{
	t_dmh	*tmp;

	if (size == 0 && ptr == NULL)
		return (NULL);
	if (game->dmh_list == NULL)
	{
		if (ptr != NULL)
			game->dmh_list = dmh_new(0, ptr);
		else
			game->dmh_list = dmh_new(size, NULL);
		return (game->dmh_list->void_hold);
	}
	tmp = game->dmh_list;
	while (tmp->next)
		tmp = tmp->next;
	if (ptr != NULL)
		tmp->next = dmh_new(0, ptr);
	else
		tmp->next = dmh_new(size, NULL);
	return (tmp->next->void_hold);
}

void	free_dmh(t_game *game)
{
	t_dmh	*tmp;

	while (game->dmh_list)
	{
		if (game->dmh_list->void_hold != NULL)
			free(game->dmh_list->void_hold);
		tmp = game->dmh_list->next;
		if (game->dmh_list != NULL)
			free(game->dmh_list);
		game->dmh_list = tmp;
	}
}

void	clean_exit(t_game *game, char *msg, int exit_code)
{
	if (msg != NULL)
	{
		if (exit_code == 1)
			write(exit_code + 1, "Error\n", 6);
		write(exit_code + 1, msg, ft_strlen(msg));
		write(exit_code + 1, "\n", 1);
	}
	free_dmh(game);
	free(game);
	exit(exit_code);
}
