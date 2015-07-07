/*
** part.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Apr 12 20:04:26 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:04:27 2015 Aurélien GIRARDEAU
*/

#include "parsing.h"
#include "channel.h"
#include "user.h"
#include "msg.h"

int		part(int fd, t_user *users, t_channel *channels, char **arg)
{
  unsigned int	i;
  int		ret;

  i = 1;
  (void)users;
  if (tab_len(arg) < 2)
    return (send_response(fd, "461", "part :Not enough parameters"));
  while (arg[i] != NULL)
    {
      ret = pop_in_channel(arg[i], fd, &channels);
      if (ret == -1)
	send_response(fd, "403", str_concat(arg[i], " ", ":No such channel"));
      else if (ret == -2)
	send_response
	  (fd, "442", str_concat(arg[i], " ", ":You're not on that channel"));
      else
	send_response(fd, "", str_concat("PART", " ", arg[i]));
	++i;
    }
  return (0);
}
