/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** cmd_broadcast by Lucas Le Ray
*/

#include "server.h"

static const orientation_t ORIENTATIONS[] = {
	{ UP, 2, 1, 8, 4, 5, 6, 3, 7 },
	{ RIGHT, 4, 3, 2, 6, 7, 8, 5, 1 },
	{ DOWN, 6, 5, 4, 8, 1, 2, 7, 3 },
	{ LEFT, 8, 7, 6, 2, 3, 4, 1, 5 },
	{ NO_DIR, 0, 0, 0, 0, 0, 0, 0, 0 }
};

vector_t	get_distance(server_t *server, player_t *from, player_t *to)
{
	int		x1 = to->x - from->x;
	int		x2 = server->width - ABS(x1);
	int		y1 = to->y - from->y;
	int		y2 = server->height - ABS(y1);
	int		x = from->x < to->x ? 1 : from->x > to->x ? -1 : 0;
	int		y = from->y < to->y ? 1 : from->y > to->y ? -1 : 0;

	if (ABS(x2) < ABS(x1))
		x *= (-1);
	if (ABS(y2) < ABS(y1))
		y *= (-1);
	vector_t	distance;


	distance.x = x;
	distance.y = y;
	return (distance);
}

int	adapt_orientation(dir_e direction, int orientation, int i)
{
	while (ORIENTATIONS[++i].dir != direction);
	switch (orientation) {
		case (11):
			return (ORIENTATIONS[i].up_left);
		case (21):
			return (ORIENTATIONS[i].down_left);
		case (31):
			return (ORIENTATIONS[i].center_left);
		case (12):
			return (ORIENTATIONS[i].up_right);
		case (22):
			return (ORIENTATIONS[i].down_right);
		case (32):
			return (ORIENTATIONS[i].center_right);
		case (13):
			return (ORIENTATIONS[i].up_center);
		case (23):
			return (ORIENTATIONS[i].down_center);
		default:
			return (0);
	}
}

int 	get_orientation(server_t *server, player_t *from, player_t *to)
{
	vector_t	distance = get_distance(server, from, to);
	int		orientation = 0;

	if (to->case_on == from->case_on)
		return (0);
	orientation += distance.x == 1 ? 1 : distance.x == -1 ? 2 : 3;
	orientation += distance.y == 1 ? 10 : distance.y == -1 ? 20 : 30;
	return (adapt_orientation(to->direction, orientation, -1));
}

void broadcast_message(server_t *server, player_t *from, char *cmd)
{
	player_list_t	*to = server->players;
	int		orientation;
	char		buff[strlen(cmd) + 16];
	char		*tmp = buff;

	if (!check_cmd_param(from, cmd, 2))
		return;
	while ((to = to->next)) {
		if (to->data != from && to->data->team) {
			orientation = get_orientation(server, from, to->data);
			sprintf(tmp, "message %d, %s\n", orientation,
				&cmd[strlen("Broadcast")]);
			add_msg_send(to->data, strdup(buff));
		}
	}
	add_msg_send(from, MSG_OK);
}
