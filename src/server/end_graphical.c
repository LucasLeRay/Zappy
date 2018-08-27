/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** end_graphical by Lucas Le Ray
*/

#include "server.h"

void end_graphical(server_t *server)
{
	char	buff[strlen(server->end) + 9];
	char	*tmp = buff;

	tmp += sprintf(tmp, "VICTORY:%s)", server->end);
	if (write(server->network->fd_graphical, buff, strlen(buff)) == -1) {
		server->network->fd_graphical = -1;
	}
}