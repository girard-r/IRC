/*
** parsing.c for myftp_server in /home/girard_r/rendu/PSU_2014_myftp
**
** Made by Aurélien GIRARDEAU
** Login   <girard_r@epitech.net>
**
** Started on  Fri Mar 13 22:59:06 2015 Aurélien GIRARDEAU
** Last update Sun Mar 22 21:12:06 2015 Aurélien GIRARDEAU
*/

# include <stdlib.h>
# include <string.h>
# include <stdio.h>

void		delete_tab(char **str)
{
  int		i;

  i = 0;
  while ((*str)[i])
    {
      if ((*str)[i] == '\t')
	(*str)[i] = ' ';
      i += 1;
    }
}

char		**parse_cmdline(char *cmdline)
{
  char		**tab;
  char		*tmp;
  char		*cpy;
  unsigned int	cmp;

  cpy = strdup(cmdline);
  tmp = NULL;
  cmp = 2;
  delete_tab(&cpy);
  if ((tab = malloc(sizeof(char *) * 2)) == NULL
      || (tab[0] = strtok(cpy, " ")) == NULL)
    return (NULL);
  tab[1] = NULL;
  while ((tmp = strtok(NULL, " ")))
    {
      if ((tab = realloc(tab, sizeof(char *) * (cmp + 1))) == NULL)
  	return (NULL);
      tab[cmp - 1] = tmp;
      tab[cmp] = NULL;
      cmp += 1;
    }
  return (tab);
}
