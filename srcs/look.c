/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_link.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 12:04:50 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/08 17:44:22 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		add_link(t_param *param)
{
	t_element	*new;
	t_element	*begin;

	if ((new = (t_element *)malloc(sizeof(t_element))) == NULL)
		return ;
	new->name = ft_strdup(param->dir->d_name);
	new->next = NULL;
	if (param->elem == NULL)
		param->elem = new;
	else
	{
		begin = param->elem;
		while (begin->next && 
			   (param->bool[3] == 0 ? ft_strcmp(begin->next->name, new->name) < 0 :
				ft_strcmp(begin->next->name, new->name) > 0))
			begin = begin->next;
		new->next = begin->next;
		begin->next = new;
	}
}

void		add_list(t_param *param)
{
	t_element	*new;
	t_element	*begin;

	if ((new = (t_element *)malloc(sizeof(t_element))) == NULL)
		return ;
	new->name = ft_strdup(param->rec->name);
	new->name = ft_strjoin(new->name, "/");
	new->name = ft_strjoin(new->name, param->dir->d_name);
	new->next = NULL;
	if (param->listime == NULL)
		param->listime = new;
	else
	{
		begin = param->listime;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new;
	}
}

void		add_rec_link(t_param *param)
{
	t_element	*new;
	t_element	*begin;

	if ((new = (t_element *)malloc(sizeof(t_element))) == NULL)
		return ;
	new->name = ft_strdup(param->rec->name);
	new->name = ft_strjoin(new->name, "/");
	new->name = ft_strjoin(new->name, param->dir->d_name);
	new->next = NULL;
	if (param->rec == NULL)
		param->rec = new;
	else
	{
		begin = param->rec;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new;
	}
}

void		add_av(t_param *param)
{
	t_element	*new;
	t_element	*begin;

	if ((new = (t_element *)malloc(sizeof(t_element))) == NULL)
		return ;
	new->name = ft_strdup(param->av[param->i]);
	new->next = NULL;
	if (param->rec == NULL)
		param->rec = new;
	else
	{
		begin = param->rec;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = new;
	}
}

void		add_if_none(t_param *param)
{
	t_element	*new;

	if ((new = (t_element *)malloc(sizeof(t_element))) == NULL)
		return ;
	new->name = ft_strdup(".");
	new->next = NULL;
	param->rec = new;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_adress.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/30 16:58:36 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/08 16:25:08 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_printer(t_param *param)
{
	while (param->elem != NULL)
	{
		if ((param->elem->name[0] == '.' && param->bool[2] == 1) ||
			param->elem->name[0] != '.')
			ft_putendl(param->elem->name);
		param->elem = param->elem->next;
	}
	free(param->elem);
	param->elem = NULL;
}

void	ft_option(t_param *param)
{
	if (param->bool[4] == 1)
	{
		sort_listime(param);
		sort_list_time(param);
	}
	if (param->bool[0] == 1 && ft_hide(param) == 0)
		ft_ls_l(param);
}

void	ft_print(t_param *param)
{
	param->elem = NULL;
	param->list = NULL;
	while ((param->dir = readdir(param->dirp)) != NULL)
	{
		add_list(param);
		add_link(param);
		if (param->dir->d_type == DT_DIR && (param->bool[1] == 1)
			&& (ft_strcmp(param->dir->d_name, ".") != 0)
			&& (ft_strcmp(param->dir->d_name, "..") != 0))
			add_rec_link(param);
	}
	ft_option(param);
	if (ft_hide(param) == 0)
		ft_printer(param);
}

void	ft_multad(t_param *param)
{
	if (param->rec)
		ft_option_rec(param);
	if ((param->dirp = opendir(param->rec->name)) == NULL)
		return ;
	else
	{
		if (param->j >= 2 && ft_hide(param) == 0)
		{
			ft_putstr(param->rec->name);
			ft_putendl(":");
		}
		ft_print(param);
		closedir(param->dirp);
		if (param->rec->next && ft_hide(param) == 0)
		ft_putchar('\n');
	}
	free(param->rec);
}

void	ft_adress(t_param *param)
{
	param->i = ft_bool(param->av, param->ac, param);
	param->j = ((param->ac - param->i) - 1);
	param->i++;
	opt_arg(param->av, param);
	if (param->av[param->i])
	{
		add_av(param);
		param->i++;
	}
	if (param->j == 0)
		add_if_none(param);
	while (param->rec)
	{
		ft_multad(param);
		param->rec = param->rec->next;
		param->j++;
		ft_add_av(param);
	}
	free(param->rec);
	free(param);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 21:49:43 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/08 15:53:00 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_bool2(char **av, t_param *param, unsigned int j, int ac)
{
	int			i;

	i = 0;
	while (++i < ac && av[i][0] == '-' && av[i][1])
	{
		j = 1;
		while (j < ft_strlen(av[i]))
		{
			if (av[i][j] == 'l')
				param->bool[0] = 1;
			else if (av[i][j] == 'R')
				param->bool[1] = 1;
			else if (av[i][j] == 'a')
				param->bool[2] = 1;
			else if (av[i][j] == 'r')
				param->bool[3] = 1;
			else if (av[i][j] == 't')
				param->bool[4] = 1;
			else if (av[i][j] != '1')
				ft_bool_error(av, i, j);
			j++;
		}
	}
	param->count_opt = i - 1;
}

int			ft_bool(char **av, int ac, t_param *param)
{
	int			i;
	int			j;

	i = 0;
	j = 1;
	while (param->bool[i])
		param->bool[i++] = 0;
	ft_bool2(av, param, j, ac);
	return (param->count_opt);
}

int			ft_bool_error(char **av, int i, int j)
{
	ft_putstr("ft_ls: illegal option -- ");
	ft_putchar(av[i][j]);
	ft_putchar('\n');
	ft_putendl("usage: ft_ls [Ralrt] [file ...]");
	exit(0);
}

int			ft_hide(t_param *param)
{
	int size;
	int i;

	i = 0;
	size = ft_strlen(param->rec->name) - 1;
	while (size != 0 && param->rec->name[size] != '/')
	{
		if (param->rec->name[size] == '.' && param->rec->name[size - 1] != '.')
			i = 1;
		size--;
	}
	return (i);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/16 13:10:39 by rbaum             #+#    #+#             */
/*   Updated: 2015/01/19 19:35:13 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void ft_list_clear(t_element *list)
{
	t_element *tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		if (tmp != NULL)
			free(tmp);
	}
	tmp = NULL;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 13:27:41 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/07 15:23:30 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <string.h>
void		sort_error(char **tmp)
{
	int		i;

	i = 0;
	while (tmp[i + 1])
	{
		if (ft_strcmp(tmp[i], tmp[i + 1]) > 0)
		{
			ft_swap(&tmp[i], &tmp[i + 1]);
			i = -1;
		}
		i++;
	}
	i = 0;
}

void		ft_error(t_param *param)
{
	struct stat		*info;
	int				i;
	int				k;
	int				l;


	k = 0;
	l = 0;
	if ((info = malloc(sizeof(struct stat))) == NULL)
		return ;
	i = ft_bool(param->av, param->ac, param) + 1;
	int j = param->ac - i;
	if ((param->none = malloc(sizeof(char*) * j + 1)) == NULL)
		return;
	if ((param->reg = malloc(sizeof(char *) * j + 1)) == NULL)
		return;
	while (i < param->ac)
	{
		if (((stat(param->av[i], info)) != -1) && S_ISREG(info->st_mode))
			param->reg[k++] = param->av[i];
		else if (stat(param->av[i], info) == -1)
			 param->none[l++] = param->av[i];
		 i++;
 	} 
	opt_arg(param->reg, param);
	sort_error(param->none);
}

void	ft_aff_error(t_param *param)
{
	int i;

	i = 0;
	ft_error(param);
	while (param->none[i])
	{
		ft_putstr("ft_ls: ");
		perror(param->none[i++]);
	}
	i = 0;
	while (param->reg[i])
		ft_putendl(param->reg[i++]);
	free(param->reg);
	free(param->none);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/24 15:18:03 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/07 16:11:45 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		main(int ac, char **av)
{
	t_param				*param;
	struct stat			*info;
	struct s_element	*elem;
	struct s_element	*list;
	struct dirent		*dir;

	dir = (struct dirent *)malloc(sizeof(struct dirent));
	param = (t_param*)malloc(sizeof(t_param));
	info = (struct stat*)malloc(sizeof(struct stat));
	elem = (struct s_element*)malloc(sizeof(struct s_element));
	list = (struct s_element*)malloc(sizeof(struct s_element));
	param->av = av;
	param->ac = ac;
	param->dir = dir;
	param->info = *info;
	param->elem = elem;
	param->list = list;
	ft_aff_error(param);
	ft_adress(param);
	free(dir);
//	free(param);
	free(info);
	free(elem);
	free(list);
	return (0);
}

/*
Trier -R et -t en meme temps
Verifier tous les tris
Free les bons trucs pour qu'il fonctionne enfin correctmeent
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_aff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/03 18:56:46 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/08 13:35:59 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_pre_aff(t_param *param)
{
	unsigned int i;
	unsigned int j;

	i = ft_strlen(ft_itoa((unsigned)major(param->info.st_rdev)));
	j = ft_strlen(ft_itoa((unsigned)minor(param->info.st_rdev)));
	lstat(ft_pwd(param), &param->info);
	if ((param->group = getgrgid(param->info.st_gid)) != NULL)
	{
		if (param->tcount[0] < ft_strlen(ft_itoa(param->info.st_nlink)))
			param->tcount[0] = ft_strlen(ft_itoa(param->info.st_nlink));
	}
	if ((param->dui = getpwuid(param->info.st_uid)) != NULL)
	{
		if (param->tcount[1] < ft_strlen(param->dui->pw_name))
			param->tcount[1] = ft_strlen(param->dui->pw_name);
	}
		if (param->tcount[2] < ft_strlen(param->group->gr_name))
			param->tcount[2] = ft_strlen(param->group->gr_name);
		if (param->tcount[3] < ft_strlen(ft_itoa(param->info.st_size)))
			param->tcount[3] = ft_strlen(ft_itoa(param->info.st_size));
		if (param->tcount[4] < i)
			param->tcount[4] = i;
		if (param->tcount[5] < j)
			param->tcount[5] = j;
		param->total = param->total + param->info.st_blocks;
}

void		ft_sem_aff(t_param *param)
{
	unsigned int y;

	stat(ft_pwd(param), &param->info);
	ft_right(param);
	y = ft_strlen(ft_itoa(param->info.st_nlink));
	while (param->tcount[0] >= y++)
		ft_putchar(' ');
	ft_putnbr(param->info.st_nlink);
	y = ft_strlen(param->dui->pw_name);
	ft_putstr(" ");
		ft_putstr(param->dui->pw_name);
	while (param->tcount[1] >= y++ - 1)
		ft_putchar(' ');
	y = ft_strlen(param->group->gr_name);
	ft_putstr(param->group->gr_name);
	while (param->tcount[2] >= y++)
		ft_putchar(' ');
}

void		ft_isblk(t_param *param)
{
	unsigned int y;

	if ((S_ISBLK(param->info.st_mode)) || (S_ISCHR(param->info.st_mode)))
	{
		y = ft_strlen(ft_itoa(major(param->info.st_rdev)));
		while (param->tcount[4] >= y++)
			ft_putchar(' ');
		ft_putnbr(major(param->info.st_rdev));
		ft_putstr(",");
		y = ft_strlen(ft_itoa(minor(param->info.st_rdev)));
		while (param->tcount[5] >= y++)
			ft_putchar(' ');
		ft_putnbr(minor(param->info.st_rdev));
	}
}

void		ft_aff(t_param *param)
{
	unsigned int y;
	unsigned int i;

	i = param->tcount[4] + param->tcount[5] + 1;
	ft_sem_aff(param);
	if ((S_ISBLK(param->info.st_mode)) || (S_ISCHR(param->info.st_mode)))
		ft_isblk(param);
	else
	{
		if (i > 3)
		{
			while (i-- > 0)
				ft_putchar(' ');
		}
		y = ft_strlen(ft_itoa(param->info.st_size));
		while (param->tcount[3] >= y++)
			ft_putchar(' ');
		ft_putnbr(param->info.st_size);
	}
	ft_putchar(' ');
	ft_time(param);
	ft_putstr(param->elem->name);
}

void		print_total(t_param *param)
{
	while (param->elem)
	{
		if ((param->elem->name[0] == '.' && param->bool[2] == 1) ||
			param->elem->name[0] != '.')
		{
			ft_putstr("total ");
			ft_putnbrn(param->total);
			break ;
		}
		param->elem = param->elem->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/07 17:49:19 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/07 16:57:31 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_right(t_param *param)
{
	if (lstat(ft_pwd(param), &param->info) == -1)
		perror("lstat");
	if (S_ISDIR(param->info.st_mode))
		ft_putchar('d');
	else if (S_ISREG(param->info.st_mode))
		ft_putchar('-');
	else if (S_ISLNK(param->info.st_mode))
		ft_putchar('l');
	else if (S_ISBLK(param->info.st_mode))
		ft_putchar('b');
	else if (S_ISCHR(param->info.st_mode))
		ft_putchar('c');
	else if (S_ISSOCK(param->info.st_mode))
		ft_putchar('s');
	(S_IRUSR & param->info.st_mode) ? ft_putchar('r') : ft_putchar('-');
	(S_IWUSR & param->info.st_mode) ? ft_putchar('w') : ft_putchar('-');
	(S_IXUSR & param->info.st_mode) ? ft_putchar('x') : ft_putchar('-');
	(S_IRGRP & param->info.st_mode) ? ft_putchar('r') : ft_putchar('-');
	(S_IWGRP & param->info.st_mode) ? ft_putchar('w') : ft_putchar('-');
	(S_IXGRP & param->info.st_mode) ? ft_putchar('x') : ft_putchar('-');
	(S_IROTH & param->info.st_mode) ? ft_putchar('r') : ft_putchar('-');
	(S_IWOTH & param->info.st_mode) ? ft_putchar('w') : ft_putchar('-');
	(S_IXOTH & param->info.st_mode) ? ft_putchar('x') : ft_putchar('-');
	ft_putchar(' ');
}

void	ft_time(t_param *param)
{
	char			*mtime;
	int				j;
	unsigned int	now;

	j = 4;
	now = time(NULL);
	lstat(ft_pwd(param), &param->info);
	if (((now - param->info.st_mtime) <= -1)
		|| (now - (param->info.st_mtime) > 15811200))
	{
		mtime = ctime(&param->info.st_mtime);
		while (j < 10)
			ft_putchar(mtime[j++]);
		j = 19;
		ft_putchar(' ');
		while (j < 24)
			ft_putchar(mtime[j++]);
	}
	else
	{
		mtime = ctime(&param->info.st_mtime);
		while (j < 16)
			ft_putchar(mtime[j++]);
	}
	ft_putchar(' ');
}

void	ft_symlink(t_param *param)
{
	char	buf[BUFF_SIZE + 1];
	int		ret;

	if ((ret = readlink(ft_pwd(param), buf, BUFF_SIZE)) != -1)
	{
		buf[ret] = '\0';
		ft_putstr(" -> ");
		ft_putstr(buf);
	}
	ft_putchar('\n');
}

void	ft_ls_l(t_param *param)
{
	t_element *begin;

	param->total = 0;
	begin = param->elem;
	while (param->elem)
	{
		if ((param->elem->name[0] == '.' && param->bool[2] == 1) ||
			param->elem->name[0] != '.')
			ft_pre_aff(param);
		param->elem = param->elem->next;
	}
	param->elem = begin;
	begin = param->elem;
	print_total(param);
	param->elem = begin;
	while (param->elem)
	{
		if ((param->elem->name[0] == '.' && param->bool[2] == 1) ||
			param->elem->name[0] != '.')
		{
			ft_aff(param);
			ft_symlink(param);
		}
		param->elem = param->elem->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_t.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/05 16:17:59 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/08 17:43:25 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

void	sort_list_swap(t_param *param, t_element *begin, t_element *begin2)
{
	char *tmp;

	tmp = param->list->name;
	param->list->name = param->list->next->name;
	param->list->next->name = tmp;
	param->list = begin;
	tmp = param->listime->name;
	param->listime->name = param->listime->next->name;
	param->listime->next->name = tmp;
	param->listime = begin2;
}

void	sort_equ(t_param *param)
{
	sort_list(param);
	sort_listime(param);
}

void	ft_next(t_param *param)
{
	param->list = param->list->next;
	param->listime = param->listime->next;
}

void	sort_list_time(t_param *param)
{
	struct stat		*one;
	struct stat		*two;
	t_element		*begin;
	t_element		*begin2;

	one = (struct stat*)malloc(sizeof(struct stat));
	two = (struct stat*)malloc(sizeof(struct stat));
	param->list = param->elem;
	begin = param->elem;
	begin2 = param->listime;
	while (param->list->next != NULL)
	{
		if (lstat(param->listime->name, one) == -1)
			perror("stat");
		if (lstat(param->listime->next->name, two) == -1)
			perror("stat");
		if (param->bool[3] == 0 ? one->st_mtime < two->st_mtime :
			one->st_mtime < two->st_mtime)
			sort_list_swap(param, begin, begin2);
		else
			ft_next(param);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/01 18:30:27 by rbaum             #+#    #+#             */
/*   Updated: 2015/01/13 13:44:33 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*ft_pwd(t_param *param)
{
	char	*str;

	if (param->elem != NULL)
	{
		str = ft_strdup(param->rec->name);
		str = ft_strjoin(str, "/");
		str = ft_strjoin(str, param->elem->name);
	}
	return (str);
}

char	*ft_dwp(t_param *param)
{
	char *str;

	if (param->elem->next != NULL)
	{
		str = ft_strdup(param->rec->name);
		str = ft_strjoin(str, "/");
		str = ft_strjoin(str, param->elem->next->name);
	}
	return (str);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/08 15:25:00 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/07 15:45:22 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	opt_arg(char **tmp, t_param *param)
{
	sort_arg(tmp, param);
	if (param->bool[4] == 1)
		sort_arg_time(tmp, param);
}

void	ft_swap(char **a, char **b)
{

	char *tmp;
	if (*a && *b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

void	sort_arg(char **tmp, t_param *param)
{
	int i;

	i = param->i;
	while (tmp[i + 1])
	{
		if (param->bool[3] == 0 ? 
			(ft_strcmp(tmp[i], tmp[i + 1]) > 0) :
			(ft_strcmp(tmp[i], tmp[i + 1]) < 0))
		{
			ft_swap(&tmp[i], &tmp[i + 1]);
			i = param->i;
			if (i == 0)
				i--;
		}
		i++;
	}
}

void	sort_arg_time(char **tmp, t_param *param)
{
	int				i;
	struct stat		*one;
	struct stat		*two;

	i = param->i;
	one = (struct stat*)malloc(sizeof(struct stat));
	two = (struct stat*)malloc(sizeof(struct stat));
	if (tmp[i])
	{
		while (tmp[i + 1])
		{
			if (stat(tmp[i], one) == -1)
				perror("stat");
			if (stat(tmp[i + 1], two) == -1)
				perror("stat");
			if (param->bool[3] == 0 ? one->st_mtime < two->st_mtime : 
				one->st_mtime > two->st_mtime)
			{
				ft_swap(&tmp[i], &tmp[i + 1]);
				i = param->i - 1;
			}
			i++;
		}
	}
}

void	ft_add_av(t_param *param)
{
	struct stat		*info;
	if ((info = malloc(sizeof(struct stat))) == NULL)
		return;
	if (!param->rec && param->av[param->i])
	{
		if ((stat(param->av[param->i], info)) != -1 && S_ISDIR(info->st_mode))
			ft_putchar('\n');
		add_av(param);
		param->i++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 22:47:54 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/08 15:56:26 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void    sort_list2(t_param *param)
{
    char        *tmp;

	if (param->bool[3] == 1 ?
		ft_strcmp(param->list->name, param->list->next->name) < 0 :
		ft_strcmp(param->list->name, param->list->next->name) > 0)
    {
        tmp = param->list->name;
        param->list->name = param->list->next->name;
        param->list->next->name = tmp;
        param->list = param->elem;
    }
    else
        param->list = param->list->next;
}

void    sort_list(t_param *param)
{
    param->list = param->elem;
    while (param->list->next != NULL)
        sort_list2(param);
}

void	sort_listime(t_param *param)
{
	char		*tmp;
	t_element	*begin;

	begin = param->listime;
	while (param->listime->next != NULL)
	{
		if (param->bool[3] == 1 ?
			ft_strcmp(param->listime->name, param->listime->next->name) < 0 :
			ft_strcmp(param->listime->name, param->listime->next->name) > 0)
		{
			tmp = param->listime->name;
			param->listime->name = param->listime->next->name;
			param->listime->next->name = tmp;
			param->listime = begin;
		}
		else
			param->listime = param->listime->next;
	}
	param->listime = begin;
}

void	sort_rec(t_param *param)
{
	char		*tmp;
	t_element	*list;

	list = param->rec;
	while (list->next != NULL)
	{
		if (param->bool[3] == 0 ?
			ft_strcmp(list->name, list->next->name) > 0 :
			ft_strcmp(list->name, list->next->name) < 0)
		{
			tmp = list->name;
			list->name = list->next->name;
			list->next->name = tmp;
			list = param->rec;
		}
		else
			list = list->next;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list_rec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbaum <rbaum@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 11:31:44 by rbaum             #+#    #+#             */
/*   Updated: 2015/02/08 17:46:17 by rbaum            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_option_rec(t_param *param)
{
	sort_rec(param);
	if (param->bool[4] == 1)
		sort_list_time_rec(param);
}

void	 sort_list3(t_param *param)
{
	char	*tmp;

	if (param->bool[3] == 0 ?
		ft_strcmp(param->list->name, param->list->next->name) > 0 :
		ft_strcmp(param->list->name, param->list->next->name) < 0)
	{
		tmp = param->list->name;
		param->list->name = param->list->next->name;
		param->list->next->name = tmp;
		param->list = param->rec;
	}
	else
		param->list = param->list->next;
}

void	sort_swap_rec(t_param *param)
{
	char *tmp;

	tmp = param->list->name;
	param->list->name = param->list->next->name;
	param->list->next->name = tmp;
	param->list = param->rec;
}

void	 sort_list_time_rec(t_param *param)
{
	struct stat		*one;
	struct stat		*two;

	one = (struct stat*)malloc(sizeof(struct stat));
	two = (struct stat*)malloc(sizeof(struct stat));
	param->list = param->rec;
	while (param->list->next != NULL)
	{
		if (stat(param->list->name, one) == -1)
			perror("stat");
		if (stat(param->list->next->name, two) == -1)
			perror("stat");
		if (param->bool[3] == 0 ? one->st_mtime < two->st_mtime :
			one->st_mtime > two->st_mtime)
			sort_swap_rec(param);
		else if (one->st_mtime == two->st_mtime)
			sort_list3(param);
		else
			param->list = param->list->next;
	}
}
