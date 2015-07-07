/*
** nick.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Sun Apr 12 20:04:18 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:14:39 2015 Aurélien GIRARDEAU
*/

#include "parsing.h"
#include "channel.h"
#include "user.h"
#include "msg.h"

void		set_nickname(t_user *racine, int fd, char *newnick)
{
  t_user	*tmp;

  tmp = racine->next;
  while (tmp != racine)
    {
      if (tmp->fd == fd)
	{
	  if (tmp->nickname)
	    free(tmp->nickname);
	  tmp->nickname = strdup(newnick);
	  return ;
	}
      tmp = tmp->next;
    }
}

int		nick(int fd, t_user *users, t_channel *channels, char **arg)
{
  (void)channels;
  if (tab_len(arg) < 2)
    return (send_response(fd, "431", ":No nickname given"));
  else if (isset_nickname(arg[1], users) == TRUE)
    return (send_response
	    (fd, "433", str_concat(arg[1], " ", ":Nickname already in use")));
  set_nickname(users, fd, arg[1]);
  return (0);

}
