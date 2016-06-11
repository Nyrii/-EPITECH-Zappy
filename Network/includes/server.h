/*
** server.h for server in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/includes/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 11:49:04 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 11 19:33:06 2016 Kevin Empociello
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "generic_list.h"

typedef struct		s_client
{
  int			sock;
  int			timer;
}			t_client;

typedef struct		s_player
{
  int     		sock;
  int			x;
  int			y;
  int			orientation;
  int			level;
  int			stones[7];
  double		timer;
}			t_player;

typedef struct		s_team
{
  int			nb_players;
  char			*name;
  t_list		players;
}			t_team;

typedef struct		s_data
{
  int			port;
  int			world_x;
  int			world_y;
  int			max_clients;
  int			delay;
  t_list	       	teams;
  int			***map;
  int			**resources;
  float			percentages[7];
  int			*required_players;
  char			*strings_resources[7];
}			t_data;

typedef struct		s_server
{
  /* DATA WORLD */
  t_data		data;

  /* Clients */
  t_list  		queue_clients;
  t_list		graphic_clients;
  t_list		all_players;

  /* CMDS */
  char			*cmd_tab_ia[13];
  int			(*cmd_ptr_ia[13])();
  char			*cmd_tab_graphic[8];
  int			(*cmd_ptr_graphic[8])();

  /* SOCKET */
  struct timeval	timeout;
  struct hostent	*hostinfo;
  int			max;
  int			sock;
  fd_set		rdfs;
}			t_server;


/* Socket */
int   		init_server(int, int);
int   		error(char *);
int   		loop_server(t_server *);
void  		set_all_clients(t_server *);
void  		check_sockets_loop(t_server *);
t_client	*new_client(t_server *);
void		handle_new_client(t_server *);

/*
** bct.c
*/
char		*bct(int ***map, int const, int const);
int		bct_on_tile(t_server *, t_client *);

/*
** broadcast_ia.c
*/
int		broadcast_ia(t_server *, t_player *);

/*
** connect_ia.c
*/
int		connect_nbr_ia(t_server *, t_player *);

/*
** drop_ia.c
*/
int		drop_ia(t_server *, t_player *);

/*
** expulse_ia.c
*/
int		expulse_ia(t_server *, t_player *);

/*
** fork_ia.c
*/
int		fork_ia(t_server *, t_player *);

/*
** forward_ia.c
*/
int		forward_ia(t_server *, t_player *);

/*
** free.c
*/
int		free_tab(char **, int);

/*
** left_ia.c
*/
int		left_ia(t_server *, t_player *);

/*
** generate_map.c
*/
int		generate_map(t_data *, int, int, int);

/*
** generate_resources.c
*/
int		init_resources(int ***);

/*
** get_opt.c
*/
int		get_opt(int, char **, t_data *);

/*
** get_player.c
*/
t_list		*get_players_at_pos(t_data *, int, int);

/*
** incantation_ia.c
*/
int		incantation_ia(t_server *, t_player *);

/*
** init.c
*/
void		init_code(char **, char **);
void		init_ptrfunc(int (**)(t_server *, t_player *),
			     int (**)(t_server *, t_client *));

/*
** init_nb_players.c
*/
int		init_nb_players(int **);

/*
** inventory_ia.c
*/
int		inventory_ia(t_server *, t_player *);

/* main */
int		run_zappy(t_server *);

/*
** mct.c
*/
int		mct(t_server *, t_client *);

/*
** msz.c
*/
int		msz(t_server *, t_client *);

/*
** take_ia.c
*/
int		take_ia(t_server *, t_player *);

/*
** tna.c
*/
int		tna(t_server *, t_client *);

/*
** plv.c
*/
int		plv(t_server *, t_client *);

/*
** pin.c
*/
int		pin(t_server *, t_client *);

/*
** ppo.c
*/
int		ppo(t_server *, t_client *);

/*
** process.c
*/
int		manage_commands_graphic(t_server *, t_client *, const char *);
int		manage_commands_ia(t_server *, t_player *, const char *);

/*
** right_ia.c
*/
int		right_ia(t_server *, t_player *);

/*
** see_ia.c
*/
int		see_ia(t_server *, t_player *);

/*
** see_ia_calculs.c
*/
void		determine_minus_x(t_server *, t_player *, int *, int);
void		determine_minus_y(t_server *, t_player *, int *, int);
void		determine_plus_x(t_server *, t_player *, int *, int);
void		determine_plus_y(t_server *, t_player *, int *, int);

/*
** see_ia_resources.c
*/
int		see_ia_resources(char **, t_server *,
				 int *, int *);

/*
** sgt.c
*/
int		sgt(t_server *, t_client *);

/*
** sst.c
*/
int		sst(t_server *, t_client *);

#endif /* !SERVER_H_ */
