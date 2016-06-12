/*
** parse.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Sat Jun 11 21:12:23 2016 Kevin Empociello
*/

#include <string.h>
#include "server.h"

static char	*get_cmd(char *buffer)
{
  char	*new;
  int	i;

  i = 0;
  if (buffer == NULL)
    return (NULL);
  if ((new = malloc(96 * sizeof(char))) == NULL)
    return (NULL);
  while (buffer[i] && buffer[i] != ' ' && buffer[i] != '\0')
    {
      new[i] = buffer[i];
      i++;
    }
  new[i] = '\0';
  return (new);
}

static char	*get_parameter(char *buffer)
{
  char	*new;
  int	i;

  i = 0;
  new = NULL;
  if (buffer == NULL)
    return (NULL);
  while (buffer[i] && buffer[i] != ' ' && buffer[i] != '\0')
    i++;
  if (buffer[i] == '/')
    i++;
  if (buffer[i] != '\0' && buffer[i + 1] != '\0')
    new = &buffer[i + 1];
  else
    return (NULL);
  return (new);
}

char		*parse_cmd(t_server *srv, char *cmd)
{
  if (cmd == NULL)
    return (NULL);
  if ((srv->cmd = get_cmd(cmd)) == NULL)
    return (NULL);
  srv->params = get_parameter(cmd);
  return (srv->cmd);
}
