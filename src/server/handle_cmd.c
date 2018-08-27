/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** handle_cmd by Lucas Le Ray
*/

#include "server.h"

static const command_t COMMANDS[] = {
	{ "Forward", move_forward, 7, (clock_t)0 },
	{ "Left", turn_left, 7, (clock_t)0 },
	{ "Right", turn_right, 7, (clock_t)0 },
	{ "Look", look_around, 7, (clock_t)0 },
	{ "Inventory", inventory, 1, (clock_t)0 },
	{ "Connect_nbr", connect_nbr, 0, (clock_t)0 },
	{ "Eject", eject_player, 7, (clock_t)0 },
	{ "Take", take_object, 7, (clock_t)0 },
	{ "Set", set_object, 7, (clock_t)0 },
	{ "Fork", fork_player, 42, (clock_t)0 },
	{ "Broadcast", broadcast_message, 7, (clock_t)0 }
};

void choose_cmd(player_t *player, char *cmd_player)
{
	char	**tab = str_to_tab(cmd_player, " ");

	if (!tab || !*tab)
		return;
	for (int i = 0; i < 11; i++) {
		if (!strcmp(tab[0], COMMANDS[i].cmd)) {
			player->command = malloc(sizeof(command_t));
			player->command->cmd = cmd_player;
			player->command->exec = COMMANDS[i].exec;
			player->command->cycle = COMMANDS[i].cycle;
			player->command->start = clock();
			free_tab(tab);
			return;
		} else if (!strcmp(tab[0], "Incantation")) {
			launch_incantation(player);
			free_tab(tab);
			return;
		}
	}
	add_msg_send(player, MSG_KO);
	free_tab(tab);
}

void handle_cmd_player(server_t *server, player_t *player)
{
	char	*cmd;

	cmd = extract_cmd_from_buff(&(player->msg_get), "\n");
	if (!player->team) {
		join_team(server, player, cmd);
	} else {
		choose_cmd(player, cmd);
	}
}

void execute_action(server_t *server, player_t *player)
{
	double	waiting = (double)(clock() - player->command->start)
				/ CLOCKS_PER_SEC;

	if (waiting >=
	((double)player->command->cycle / (double)server->freq)) {
		player->command->exec(server, player, player->command->cmd);
		free(player->command->cmd);
		free(player->command);
		player->command = NULL;
	}
}

void handle_cmd(server_t *server)
{
	player_list_t	*tmp = server->players->next;

	while (tmp) {
		if (rb_size(&(tmp->data->msg_get)) > 0
			&& !tmp->data->command) {
			handle_cmd_player(server, tmp->data);
		} else if (tmp->data->command) {
			execute_action(server, tmp->data);
		}
		tmp = tmp->next;
	}
	tmp = server->players->next;
	while (tmp) {
		if (tmp->data->disconnected)
			delete_player(server, &tmp);
		tmp = tmp->next;
	}
}