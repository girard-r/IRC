/*
** fds_list.c for server_irc in /home/girard_r/rendu/PSU_2014_myirc
** 
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
** 
** Started on  Sun Apr 12 20:02:33 2015 Aurélien GIRARDEAU
** Last update Sun Apr 12 20:02:34 2015 Aurélien GIRARDEAU
*/

#include "channel.h"
#include "msg.h"

t_fds			*init_fds()
{
  t_fds			*root;

  if ((root = malloc(sizeof(t_fds))) == NULL)
    return (NULL);
  root->fd = -1;
  root->next = root;
  root->prev = root;
  return (root);
}

int			pop_fd_list(t_fds **root, int fd)
{
  t_fds			*tmp;

  tmp = (*root)->next;
  while (tmp != (*root))
    {
      if (tmp->fd == fd)
	{
	  tmp->prev->next = tmp->next;
	  tmp->next->prev = tmp->prev;
	  free(tmp);
	  return (0);
	}
      tmp = tmp->next;
    }
  return (-1);
}

int			add_fd_list(t_fds **root, int fd)
{
  t_fds			*elem;

  if (is_in_fds(fd, *root) == TRUE
      || (elem = malloc(sizeof(t_fds))) == NULL)
    return (-1);
  elem->fd = fd;
  elem->next = (*root);
  elem->prev = (*root)->prev;
  elem->next->prev = elem;
  elem->prev->next = elem;
  return (0);
}

void			send_to_fds(t_fds *root, char *msg, int fd_except)
{
  t_fds			*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (tmp->fd != fd_except)
	send_response(tmp->fd, "", msg);
      tmp = tmp->next;
    }
}

e_bool			is_in_fds(int fd, t_fds *root)
{
  t_fds			*tmp;

  tmp = root->next;
  while (tmp != root)
    {
      if (tmp->fd == fd)
	return (TRUE);
      tmp = tmp->next;
    }
  return (FALSE);
}
