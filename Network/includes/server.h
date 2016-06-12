/*
** server.h for server in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/includes/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 11:49:04 2016 Nyrandone Noboud-Inpeng
** Last update Sun Jun 12 21:40:47 2016 Nyrandone Noboud-Inpeng
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
  int			id;
  int			x;
  int			y;
  int			orientation;
  int			level;
  int			inventory[8];
  double		timer;
}			t_player;

typedef struct		s_team
{
  int			max_players;
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
  float			percentages[8];
  int			*required_players;
  char			*strings_resources[8];
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
  char			*params;
  char			*cmd;
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
t_player	*new_player(t_server *, t_client *);
t_client	*new_client(t_server *);
int		handle_new_client(t_server *);
int		handle_new_graphic(t_server *, t_client *);

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
** count.c
*/
int		count_elements(t_list *);

/*
** drop_ia.c
*/
int		drop_ia(t_server *, t_player *);

/*
** expulse_ia.c
*/
int		expulse_ia(t_server *, t_player *);

/*
** epur.c
*/
char		*epur_bf(char *str);

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
t_list		get_players_at_pos(t_data *, int, int);

/*
** get_team.c
*/
t_team		*get_team_by_name(t_server *, const char *);
t_team		*get_team_by_player(t_server *, t_player *);

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
** init_perimeter.c
*/
void	init_perimeter_top(t_data, t_player *, int *);
void	init_perimeter_right(t_data, t_player *, int *);
void	init_perimeter_bottom(t_data, t_player *, int *);
void	init_perimeter_left(t_data, t_player *, int *);
void	call_init_parameter(t_data, t_player *, int *);

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
** parse.c
*/
char		*parse_cmd(t_server *, char *);

/*
** plv.c
*/
int		plv(t_server *, t_client *);

/*
** pin.c
*/
int		pin_ia(t_server *, t_player *);
int		pin(t_server *, t_client *);

/*
** ppo.c
*/
int		ppo_ia(t_server *, t_player *);
int		ppo(t_server *, t_client *);

/*
** process.c
*/
int		manage_commands_graphic(t_server *, t_client *, const char *);
int		manage_commands_ia(t_server *, t_player *, const char *);
int		manage_auth(t_server *, t_client *, const char *);

/*
** remove.c
*/
int		remove_client_from_queue(t_server *, t_client *);

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
** send.c
*/
int		send_all_players(t_server *, t_player *, const char *);
int		send_all_graphics(t_server *, const char *);

/*
** sgt.c
*/
int		sgt(t_server *, t_client *);

/*
** sst.c
*/
int		sst(t_server *, t_client *);

#endif /* !SERVER_H_ */
