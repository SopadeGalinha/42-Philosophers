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
		return (printf("%s\n", ERROR_ARG_NUM));
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
