/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** check_cmd_param by Lucas Le Ray
*/

#include "server.h"

bool check_cmd_param(player_t *player, char *cmd, int nb)
{
	char	**tab = str_to_tab(cmd, " ");
	int	i = 0;

	while (tab[i])
		i++;
	free(tab);
	if (i != nb) {
		add_msg_send(player, MSG_KO);
		return (false);
	}
	return (true);
}