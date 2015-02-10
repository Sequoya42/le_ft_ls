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
