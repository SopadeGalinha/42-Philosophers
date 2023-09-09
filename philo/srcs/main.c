/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolivei <heolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:32:40 by heolivei          #+#    #+#             */
/*   Updated: 2023/09/03 10:33:56 by heolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

__uint64_t	get_time(__uint64_t start_time)
{
	struct timeval	time;
	__uint64_t	current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000) - start_time;
	return (current_time);
}

int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		**philos;
	int			i;

	i = 0;
	params = (t_params){0};
	pthread_mutex_init(&params.finish_lock, NULL);
	pthread_mutex_init(&params.sleep_lock, NULL);
	pthread_mutex_init(&params.print, NULL);
	if (initialization(&params, argc, argv))
		return (printf("error"));
	philos = init_philos_array(&params);
	while (i < params.n_philo)
	{
		pthread_mutex_destroy(&params.forks[i]);
		free(philos[i]);
		i++;
	}
	free(params.forks);
	free(philos);
	return (0);
}
