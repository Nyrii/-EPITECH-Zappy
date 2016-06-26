/*
** store_answer.c for store_answer in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed Jun 22 14:59:20 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 26 02:21:22 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"

int		store_answer_p(t_player *player, char *answer,
			       int ret_value)
{
  if (player == NULL)
    return (fprintf(stderr, ERR_PLAYER), -1);
  else if (!answer)
    return (fprintf(stderr, ERR_ANSWER_NOT_FOUND), -1);
  if (player->buff == NULL)
    {
      if ((player->buff = malloc(strlen(answer) + 2)) == NULL)
	return (fprintf(stderr, ERR_MALLOC), -1);
      player->buff[0] = '\0';
    }
  else if (!(player->buff = realloc(player->buff,
				    strlen(player->buff) + strlen(answer) + 2)))
    return (fprintf(stderr, ERR_MALLOC), -1);
  if ((player->buff = strcat(player->buff, answer)) == NULL)
    return (fprintf(stderr, ERR_STRCAT), -1);
  free(answer);
  return (ret_value);
}

int		store_answer_c(t_client *client, char *answer,
			       int ret_value)
{
  if (client == NULL)
    return (fprintf(stderr, ERR_PLAYER), -1);
  else if (!answer)
    return (fprintf(stderr, ERR_ANSWER_NOT_FOUND), -1);
  if (client->buff == NULL)
    {
      if ((client->buff = malloc(strlen(answer) + 2)) == NULL)
	return (fprintf(stderr, ERR_MALLOC), -1);
      client->buff[0] = '\0';
    }
  else if (!(client->buff = realloc(client->buff,
				    strlen(client->buff) + strlen(answer) + 2)))
    return (fprintf(stderr, ERR_MALLOC), -1);
  if ((client->buff = strcat(client->buff, answer)) == NULL)
    return (fprintf(stderr, ERR_STRCAT), -1);
  free(answer);
  return (ret_value);
}
