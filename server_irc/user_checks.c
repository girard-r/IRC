/*
** user_checks.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Apr 12 20:16:49 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:16:50 2015 Aurélien GIRARDEAU
*/

#include "user.h"

e_bool		isset_nickname(char *nickname, t_user *root)
{
  t_user	*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (!strcmp(tmp->nickname, nickname))
	return (TRUE);
      tmp = tmp->next;
    }
  return (FALSE);
}

e_bool		isset_fd(int fd, t_user *root)
{
  t_user	*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (tmp->fd == fd)
	return (TRUE);
      tmp = tmp->next;
    }
  return (FALSE);
}
