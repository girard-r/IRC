/*
** quit.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Apr 12 20:04:35 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:04:36 2015 Aurélien GIRARDEAU
*/

#include <unistd.h>
#include "parsing.h"
#include "channel.h"
#include "user.h"
#include "msg.h"

int		quit(int fd, t_user *users, t_channel *channels, char **arg)
{
  t_channel	*tmp;
  char		*msg;

  msg = (arg[1] == NULL ? strdup("Quit") : arg[1]);
  tmp = channels->next;
  while (tmp != channels)
    {
      if (is_in_fds(fd, tmp->root) == TRUE)
	{
	  send_to_fds(tmp->root,
		      str_concat("QUIT",
				 str_concat(" :", msg, ": "),
				 get_nickname(fd, users)),
		      fd);
	  pop_in_channel(tmp->channel_name, fd, &channels);
	}
      tmp = tmp->next;
    }
  pop_fd(fd, &users);
  close(fd);
  return (0);
}
