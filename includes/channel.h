/*
** channel.h for server in /home/girard_r/rendu/PSU_2014_myirc/server
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Wed Apr  8 17:50:33 2015 Aurélien GIRARDEAU
** Last update Fri Apr 10 16:54:18 2015 Aurélien GIRARDEAU
*/

#ifndef CHANNEL_H_
# define CHANNEL_H_

# include <stdlib.h>
# include <string.h>
# include "e_bool.h"

typedef struct		s_fds
{
  int			fd;
  struct s_fds		*next;
  struct s_fds		*prev;
}			t_fds;

typedef struct		s_channel
{
  t_fds			*root;
  int			size;
  char			*channel_name;
  struct s_channel	*next;
  struct s_channel	*prev;
}			t_channel;

/*
** fd List
*/
t_fds			*init_fds();
int			add_fd_list(t_fds **root, int fd);
int			pop_fd_list(t_fds **root, int fd);
e_bool			is_in_fds(int fd, t_fds *root);
void			send_to_fds(t_fds *root, char *msg, int fd_except);

/*
** channel list
*/
t_channel		*init_channels();
int			delete_channel(t_channel *tmp);
int			add_in_channel(char *name, int fd, t_channel **root);
int			pop_in_channel(char *name, int fd, t_channel **root);
t_channel		*get_channel(t_channel *root, char *search);
e_bool			channel_exists(char *name, t_channel *root);

/* optionnal */
e_bool			is_in_channel(char *name, int fd, t_channel *root);

/* utils */
int			add_in_channel_aux(t_channel *elem, int fd);
int			create_channel(t_channel **root, char *name, int fd);

/* msg */
int			broadcast_msg_from_name(int fd, t_channel *channels,
						char *msg, char *name);

#endif /* CHANNEL_H_ */
