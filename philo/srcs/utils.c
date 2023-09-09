/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilibft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 19:02:26 by heolivei          #+#    #+#             */
/*   Updated: 2023/09/09 19:02:30 by heolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	int	c;
	int	s;
	int	res;

	c = 0;
	s = 1;
	res = 0;
	while (str[c] == ' ' || str[c] == '\n' || str[c] == '\t'
		|| str[c] == '\v' || str[c] == '\f' || str[c] == '\r')
		c++;
	if (str[c] == '-' || str[c] == '+')
	{
		if (str[c] == '-')
			s = -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		res = (res * 10) + (str[c] - 48);
		c++;
	}
	while (str[c])
		if (str[c] < '0' || str[c++] > '9')
			return (-1);
	return (res * s);
}

int	check_any_dead(t_params *params)
{
	int	i;
	int	since_last_meal;

	i = 0;
	while (i < params->n_philo)
	{
		pthread_mutex_lock(&params->philos[i]->lst_meal_lock);
		since_last_meal = get_time(params->start_program)
			- params->philos[i]->time_lst_meal;
		pthread_mutex_unlock(&params->philos[i]->lst_meal_lock);
		if (since_last_meal >= params->n_time_to_die)
		{
			if (params->n_philo == 1)
				return (1);
			printf("%d %d died\n",
				(int)get_time((__uint64_t)params->start_program), params->philos[i]->id + 1);
			pthread_mutex_lock(&params->finish_lock);
			params->finish = 1;
			pthread_mutex_unlock(&params->finish_lock);
			return (1);
		}
		i++;
	}
	return (0);
}