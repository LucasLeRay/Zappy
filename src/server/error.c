/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** error by Lucas Le Ray
*/

#include "server.h"

bool	error_msg(char *message)
{
	dprintf(2, "Error: %s", message);
	return (false);
}