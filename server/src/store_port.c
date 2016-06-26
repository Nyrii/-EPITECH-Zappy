/*
** store_port.c for store_port in /Users/noboud_n/Documents/Share/PSU_2015_zappy/Network/src/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun 21 16:05:35 2016 Nyrandone Noboud-Inpeng
** Last update Tue Jun 21 16:55:43 2016 Nyrandone Noboud-Inpeng
*/

#include <string.h>
#include "server.h"
#include "errors.h"

static int	is_port_already_existing(int *ports, int port_to_check)
{
  int		i;

  i = 0;
  if (ports == NULL)
    return (0);
  while (ports[i] != -1)
    {
      if (ports[i] == port_to_check)
	return (1);
      ++i;
    }
  return (0);
}

static int	len(int *ports)
{
  int		len;
  int		i;

  len = 0;
  i = 0;
  if (ports == NULL)
    return (len);
  while (ports[i] != -1)
    {
      ++i;
      ++len;
    }
  return (len);
}

static int	store_port(t_data *data, int new_port)
{
  int		is_null;
  int		i;

  i = -1;
  is_null = data->ports == NULL ? 1 : 0;
  if ((data->ports == NULL && (data->ports = malloc(3 * sizeof(int))) == NULL)
      || (is_null == 0
	  && (data->ports = realloc(data->ports, (len(data->ports) + 2)
				    * sizeof(int))) == NULL))
    return (fprintf(stderr, ERR_MALLOC), -1);
  if (is_null)
    {
      data->ports[0] = new_port;
      data->ports[1] = -1;
      return (0);
    }
  while (data->ports[++i] != -1);
  data->ports[i++] = new_port;
  data->ports[i] = -1;
  return (0);
}

void		ports_manager(t_server *s, char **argv, int *optind)
{
  int		i;

  i = 0;
  --(*optind);
  while (argv[*optind] != NULL
	 && strcmp(argv[*optind], "-n") != 0
	 && strcmp(argv[*optind], "-x") != 0
	 && strcmp(argv[*optind], "-y") != 0
	 && strcmp(argv[*optind], "-c") != 0
	 && strcmp(argv[*optind], "-t") != 0)
    {
      if (atoi(argv[*optind]) < 0)
	exit(fprintf(stderr, ERR_INVALID_PORT));
      if (strcmp(argv[*optind], "-p") != 0
	  && is_port_already_existing(s->data.ports, atoi(argv[*optind])) == 1)
	exit(fprintf(stderr, ERR_SAME_PORT));
      if (strcmp(argv[*optind], "-p") != 0 &&
	  store_port(&s->data, atoi(argv[*optind])) == -1)
	exit(fprintf(stderr, ERR_PUSHBACK));
      if (strcmp(argv[*optind], "-p") != 0)
	++i;
      ++(*optind);
    }
  if (i == 0)
    exit(fprintf(stderr, ERR_PORTS));
}
