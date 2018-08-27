/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** get_item by Lucas Le Ray
*/

#include "server.h"

char *get_item_name(item_e item)
{
	switch (item) {
		case (FOOD):
			return ("food");
		case (LINEMATE):
			return ("linemate");
		case (DERAUMERE):
			return ("deraumere");
		case (SIBUR):
			return ("sibur");
		case (MENDIANE):
			return ("mendiane");
		case (PHIRAS):
			return ("phiras");
		case (THYSTAME):
			return ("thystame");
		case (EGG):
			return ("egg");
		default:
			return ("none");
	}
}

char *item_list_to_string(item_list_t *list)
{
	char		buff[16 * item_list_size_all(list)];
	char		*tmp = buff;
	item_list_t	*tmp_list = list->next;

	if (!tmp_list)
		return (NULL);
	while (tmp_list) {
		tmp += sprintf(tmp, "%s", get_item_name(tmp_list->data));
		if (tmp_list->next)
			tmp += sprintf(tmp, " ");
		tmp_list = tmp_list->next;
	}
	return (strdup(buff));
}