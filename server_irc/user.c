/*
** user.c for my_irc in /home/girard_r/rendu/PSU_2014_myirc/includes
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Wed Apr  8 16:51:57 2015 Aurélien GIRARDEAU
** Last update Thu Apr 16 11:55:06 2015 Aurélien GIRARDEAU
*/

#include <stdio.h>
#include "user.h"

t_user		*init_user()
{
  t_user	*user;

  if ((user = malloc(sizeof(t_user))) == NULL)
    return (NULL);
  user->fd = -1;
  user->nickname = NULL;
  user->accepted = NULL;
  user->next = user;
  user->prev = user;
  return (user);
}

int		user_len(t_user *root)
{
  t_user	*tmp;
  int		cmp;

  tmp = root->next;
  cmp = 0;
  while (tmp != root)
    {
      cmp += 1;
      tmp = tmp->next;
    }
  return (cmp);
}

char		*str_concat(char *s1, char *s2, char *s3)
{
  char		*s4;

  if ((s4 = malloc(strlen(s1) + strlen(s2) + strlen(s3) + 1)) == NULL)
    return (NULL);
  strcpy(s4, s1);
  s4[strlen(s1)] = 0;
  strcat(s4, s2);
  strcat(s4, s3);
  return (s4);
}

int		add_user(t_user **root, char *nickname, int fd)
{
  t_user	*user;
  static char	id[10] = "undefined";
  char		nb[10];
  static int	cmp = 0;

  if ((user = malloc(sizeof(t_user))) == NULL
      || sprintf(nb, "%d", cmp) == -1)
    return (-1);
  user->fd = fd;
  cmp += 1;
  if (*nickname == 0)
    user->nickname = str_concat(id, "_", nb);
  else
    user->nickname = strdup(nickname);
  user->accepted = init_fds();
  user->next = (*root);
  user->prev = (*root)->prev;
  user->prev->next = user;
  user->next->prev = user;
  return (0);
}

int		pop_fd(int fd, t_user **root)
{
  t_user	*tmp;

  tmp = (*root)->next;
  while (tmp != (*root))
    {
      if (tmp->fd == fd)
	{
	  tmp->prev->next = tmp->next;
	  tmp->next->prev = tmp->prev;
	  if (tmp->nickname)
	    free(tmp->nickname);
	  free(tmp);
	  return (1);
	}
      tmp = tmp->next;
    }
  return (0);
}
