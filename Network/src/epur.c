/*
** epur.c for  in /home/nekfeu/Share/PSU_2015_zappy/Network/src
**
** Made by Kevin Empociello
** Login   <nekfeu@epitech.net>
**
** Started on  Thu Jun  9 01:10:25 2016 Kevin Empociello
** Last update Fri Jun 17 18:01:04 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"

static char	*delete_end(char *str)
{
  int		i;
  int		j;
  char		*new;

  i = 0;
  j = 0;
  if ((new = malloc(4096 * sizeof(char))) == NULL)
    return (fprintf(stderr, ERR_PRINTF), NULL);
  while (str && str[i])
    {
      if (str[i] != '\r' && str[i] != '\n')
	new[j++] = str[i];
      i++;
    }
  new[j] = '\0';
  return (new);
}

char		*epur_bf(char *str)
{
  char		*new;
  int		i;
  int		j;

  i = 0;
  j = 0;
  if ((new = malloc((strlen(str) + 2) * sizeof(char))) == NULL)
    return (fprintf(stderr, ERR_PRINTF), NULL);
  while (str && str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
    i++;
  str = &str[i];
  i = 0;
  while (str && str[i] != '\0')
    {
      new[j++] = str[i];
      if (str[i] == ' ' || str[i] == '\t')
	while (str[i] != '\0' && (str[i] == ' ' || str[i] == '\t'))
	  i++;
      else
	i++;
	}
      j > 0 && (new[j - 1] == ' ' || new[j - 1] == '\t') ? (new[j - 1] = '\0') :
	  (new[j] = '\0');
  return (delete_end(new));
}
