/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 16:53:51 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/20 16:53:51 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static bool	ft_is_all_num(char **av);

int	check_args(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf("%s%s%s%s\n", ER1, ER2, ER3, ER4));
	if (!ft_is_all_num(av))
		return (printf("%s\n", ERROR_ARG_TYPE));
	if (ft_atoi(av[1]) < 1)
		return (printf("%s\n", ERROR_INV_NPHILO));
	if (ft_atoi(av[2]) < 1)
		return (printf("%s\n", ERROR_INV_TTDIE));
	if (ft_atoi(av[3]) < 1)
		return (printf("%s\n", ERROR_INV_TTEAT));
	if (ft_atoi(av[4]) < 1)
		return (printf("%s\n", ERROR_INV_TTSLEEP));
	if (ac == 6 && ft_atoi(av[5]) < 1)
		return (printf("%s\n", ERROR_INV_NPHILO));
	return (0);
}

static bool	ft_isdigit(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-' || str[0] == '+')
		i = 0;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (false);
	return (true);
}

static bool	ft_is_all_num(char **av)
{
	int	i;

	i = 0;
	while (av[++i])
		if (!ft_isdigit(av[i]))
			return (false);
	return (true);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	s = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res * s);
}
