/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/10 13:26:29 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/10 18:25:33 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
#define FT_LS_H

# include <unistd.h>
# include <stdio.h>
# include <dirent.h>
# include <string.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <sys/types.h>
# include <time.h>
# include <errno.h>
# include <pwd.h>
# include <grp.h>
# include "libft.h"

# define BUFF_SIZE 256


typedef struct s_element t_element;

typedef struct	s_param
{
	t_element		*elem;
	t_element		*rec;
	t_element		*list;
	t_element		*listime;
	char			**av;
	char			**reg;
	char			**none;
	char			*path;
	unsigned int	tcount[6];
	unsigned int	total;
	int				bool[6];
	int				count_opt;
	int				ac;
	int				i;
	int				j;
	DIR				*dirp;
	struct dirent	*dir;
	struct stat		info;
	struct passwd	*dui;
	struct group	*group;

}t_param;

struct	s_element
{
	char				*name;
	char				*path;
	t_element			*next;
};

int				ft_bool(char **av, t_param *param);
int				ft_bool_error(char **av, int i, int j);
int				ft_hide(t_param *param);

char			*ft_pwd(t_param *param);
char			*ft_dwp(t_param *param);

void			ft_swap(char **a, char **b);
void			ft_add_av(t_param *param);
void			add_av(t_param *param);
void			add_link(t_param *param);
void			add_rec_link(t_param *param);
void			add_if_none(t_param *param);
void			add_list(t_param *param);


void			sort_listime(t_param *param);

void			sort_list(t_param *param);
void			sort_rec(t_param *param);
void			sort_list_rev(t_param *param);
void			sort_list_time(t_param *param);
void			sort_list_time_rev(t_param *param);
void			sort_list2(t_param *param);
void			sort_list_rev2(t_param *param);

void			ft_option_rec(t_param *param);
void			sort_list_time_rec(t_param *param);
void			sort_list_time_rev_rec(t_param *param);
void			sort_list_rev_rec(t_param *param);


void			sort_arg_time(char **tmp, t_param *param);

void			sort_arg(char ** tmp, t_param *param);
void			opt_arg(char **tmp, t_param *param);



void			ft_list_clear(t_element *list);
void			ft_multad(t_param *param);
int				ft_bool2(char **av, t_param *param, unsigned int j);
void			ft_adress(t_param *param);
void			ft_print(t_param *param);
void			ft_printer(t_param *param);
void			ft_error(t_param *param);
void			ft_aff_error(t_param *param);
void			ft_right(t_param *param);
void			ft_time(t_param *param);
void			ft_ls_l(t_param *param);
void			ft_ls_rec(t_param *param, int i);
void			ft_pre_aff(t_param *param);
void			ft_aff(t_param *param);
void			print_total(t_param *param);
void			ft_symlink(t_param *param);
void			sort_equ(t_param *param);
void			sort_list2(t_param *param);
void			sort_list2bis(t_param *param);
void			sort_list2bibis(t_param *param);

#endif
