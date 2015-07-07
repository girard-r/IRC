/*
** channel_msg.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Apr 12 20:03:54 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:03:55 2015 Aurélien GIRARDEAU
*/

#include "parsing.h"
#include "channel.h"
#include "user.h"
#include "msg.h"

int		broadcast_msg_from_name(int fd, t_channel *channels,
					char *msg, char *name)
{
  t_channel	*tmp;

  tmp = channels->next;
  while (tmp != channels)
    {
      if (!strcmp(tmp->channel_name, name)
	 && is_in_fds(fd, tmp->root) == TRUE)
	{
	  send_to_fds(tmp->root, msg, fd);
	  return (0);
	}
      tmp = tmp->next;
    }
  return (1);
}
