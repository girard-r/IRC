/*
** list.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Fri Apr 10 13:41:40 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:25:34 2015 Aurélien GIRARDEAU
*/

#include <stdio.h>
#include <string.h>
#include "parsing.h"
#include "channel.h"
#include "user.h"
#include "msg.h"

void		check_response(int fd, char *arg, e_bool *error,
			       t_channel *channel)
{
  char		*s1;
  char		*s3;
  char		s2[12];

  if (arg == NULL
      || strstr(channel->channel_name, arg))
    {
      *error = FALSE;
      sprintf(s2, "%d", channel->size);
      s1 = str_concat(channel->channel_name, " ", s2);
      s3 = str_concat(s1, " :", "topic");
      send_response(fd, "322", s3);
      free(s1);
      free(s3);
    }
}

int		list(int fd, t_user *users, t_channel *channels, char **arg)
{
  t_channel	*tmp;
  char		*s1;
  char		*s3;
  e_bool	error;

  error = TRUE;
  send_response(fd, "321", "Channel :Users Name");
  tmp = channels->next;
  while (tmp != channels)
    {
      check_response(fd, arg[1], &error, tmp);
      tmp = tmp->next;
    }
  if (arg[1] && error)
    {
      s1 = str_concat(get_nickname(fd, users), " ", arg[1]);
      s3 = str_concat(s1, " ", ":No such nick/channel");
      send_response(fd, "401", s3);
      free(s1);
      free(s3);
    }
  send_response(fd, "323", ":End of /LIST");
  return (0);
}
