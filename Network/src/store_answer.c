/*
** store_answer.c for store_answer in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Wed Jun 22 14:59:20 2016 Nyrandone Noboud-Inpeng
** Last update Wed Jun 22 17:02:20 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"

int		store_answer_p(t_player *player, const char *answer,
			       int ret_value)
{
  if (player == NULL)
    return (fprintf(stderr, ERR_PLAYER), -1);
  if (write_to_buffer(answer, &player->buffs.out, strlen(answer)) == -1)
    return (fprintf(stderr, ERR_BUFFER), ret_value);
  return (ret_value);
}

int		store_answer_c(t_client *client, const char *answer,
			       int ret_value)
{
  if (client == NULL)
    return (fprintf(stderr, ERR_PLAYER), -1);
  if (write_to_buffer(answer, &client->buffs.out, strlen(answer)) == -1)
    return (fprintf(stderr, ERR_BUFFER), ret_value);
  return (ret_value);
}
