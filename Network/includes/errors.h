/*
** errors.h for errors in /Users/noboud_n/Documents/Share/PSU_2015_zappy/server/includes/
**
** Made by Nyrandone Noboud-Inpeng
** Login   <noboud_n@epitech.eu>
**
** Started on  Tue Jun  7 11:42:10 2016 Nyrandone Noboud-Inpeng
** Last update Sat Jun 11 16:05:37 2016 Nyrandone Noboud-Inpeng
*/

#ifndef ERRORS_H_
# define ERRORS_H_

# define USAGE "Usage: ./server -p port -x world_x -y world_y -c" USAGE_REST
# define USAGE_REST " max_clients -t speed -n team_name_1 team_name_2...\n"
# define ERR_MALLOC "Error: malloc failed.\n"
# define ERR_NBTEAMS "Error: Teams have not been specified.\n"
# define ERR_PUSHBACK "Error: Push back of a node failed.\n"
# define ERR_POS_MAP "Error: could not find position in the map. Aborted.\n"
# define ERR_GET_RESOURCES "Error: could not get any resources. Aborted.\n"

#endif /* ERRORS_H_ */
