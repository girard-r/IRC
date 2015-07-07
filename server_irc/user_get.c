/*
** user_get.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Apr 12 20:17:21 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:17:25 2015 Aurélien GIRARDEAU
*/

#include <stdio.h>
#include "user.h"

int		get_fd(char *nickname, t_user *root)
{
  t_user	*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (strcmp(nickname, tmp->nickname) == 0)
	return (tmp->fd);
      tmp = tmp->next;
    }
  return (-1);
}

char		*get_nickname(int fd, t_user *root)
{
  t_user	*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (fd == tmp->fd)
	return (tmp->nickname);
      tmp = tmp->next;
    }
  return (NULL);
}

t_user		*get_user(char *nickname, t_user *root)
{
  t_user	*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (!strcmp(nickname, tmp->nickname))
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}

t_user		*get_user_from_fd(int fd, t_user *root)
{
  t_user	*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (tmp->fd == fd)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}
