/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolivei <heolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:33:33 by heolivei          #+#    #+#             */
/*   Updated: 2023/09/08 21:50:14 by heolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*init_philo(int i, t_params *params)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->params = params;
	philo->id = i;
	philo->id_fork_right = i;
	philo->time_lst_meal = (int)get_time(params->start_program);
	philo->meals_count = 0;
	pthread_mutex_init(&philo->meal_count_lock, NULL);
	pthread_mutex_init(&philo->lst_meal_lock, NULL);
	if (i > 0)
		philo->id_fork_left = i - 1;
	else
		philo->id_fork_left = params->n_philo - 1;
	if (pthread_create(&philo->thread, NULL, &routine, philo) != 0)
	{
		printf("erro na cricao da thread");
		return (NULL);
	}
	return (philo);
}

void	init_forks(t_params *params)
{
	int	i;

	i = 0;
	params->forks = malloc(sizeof(pthread_mutex_t) * params->n_philo);
	while (i < params->n_philo)
	{
		if (pthread_mutex_init(&params->forks[i], NULL) != 0)
		{
			printf("Erro ao inicializar o mutex\n");
			return ;
		}
		i++;
	}
}

int	check_n_meals(t_params *params)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < params->n_philo)
	{
		pthread_mutex_lock(&params->philos[i]->meal_count_lock);
		if (params->philos[i]->meals_count >= params->n_meals)
			count++;
		pthread_mutex_unlock(&params->philos[i]->meal_count_lock);
		i++;
	}
	if (count == params->n_philo)
	{
		printf("\nAll the %d philosophers ate %d times\n", 
			params->n_philo, params->n_meals);
		pthread_mutex_lock(&params->finish_lock);
		params->finish = 1;
		pthread_mutex_unlock(&params->finish_lock);
		return (1);
	}
	return (0);
}

void	*monitoring(void *arg)
{
	t_params	*params;
	int			finish;

	params = (t_params *)arg;
	pthread_mutex_lock(&params->finish_lock);
	finish = params->finish;
	pthread_mutex_unlock(&params->finish_lock);
	if (finish)
		return (NULL);
	while (finish == 0)
	{
		usleep(1000);
		if (params->n_meals != -1)
		{
			if (check_n_meals(params))
				return (NULL);
		}
		if (check_any_dead(params))
			return (NULL);
	}
	return (NULL);
}

t_philo	**init_philos_array(t_params *params)
{
	t_philo	**philos;
	int		i;

	philos = malloc(sizeof(t_philo *) * params->n_philo);
	i = -1;
	if (!philos)
		return (NULL);
	init_forks(params);
	while (++i < params->n_philo)
		philos[i] = init_philo(i, params);
	i = -1;
	params->philos = philos;
	if (pthread_create(&params->thread_monitoring, NULL,
			&monitoring, params) != 0)
		return (NULL);
	while (++i < params->n_philo)
		pthread_join(philos[i]->thread, NULL);
	pthread_join(params->thread_monitoring, NULL);
	pthread_mutex_destroy(&params->finish_lock);
	pthread_mutex_destroy(&params->print);
	pthread_mutex_destroy(&params->sleep_lock);
	return (params->philos);
}
