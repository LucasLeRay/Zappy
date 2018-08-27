/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** add_msg by Lucas Le Ray
*/

#include "server.h"

void add_msg_get(player_t *player)
{
	char	buff[READ_SIZE + 1];
	ssize_t	size;

	memset(buff, 0, READ_SIZE + 1);
	if ((size = read(player->fd, buff, READ_SIZE)) < 0)
		player->disconnected = true;
	else if (size > 0 && strlen(buff) > 0)
		rb_push(&(player->msg_get), strdup(buff));
}

void add_msg_send(player_t *player, char *msg)
{
	rb_push(&(player->msg_send), msg);
}