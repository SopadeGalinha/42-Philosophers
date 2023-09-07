/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolivei <heolivei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 13:33:33 by heolivei          #+#    #+#             */
/*   Updated: 2023/09/03 11:42:43 by heolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_philos(t_philo *philo, int i)
{
	printf("filosofo->id: %d\n", (philo->id));
	printf("filosofo->time_lst_meal: %d\n", (philo->time_lst_meal));
	printf("filosofo->fork: %p\n", (void *)(&philo->params->forks[i]));
	printf("filosofo->id_fork_left: %d\n", (philo->id_fork_left));
	printf("filosofo->id_fork_right: %d\n", (philo->id_fork_right));
	printf("filosofo->thread: %ld\n", (philo->thread));
	printf("\n");
	printf("filosofo->params->time_to_die: %dms\n",
		(philo->params->n_time_to_die));
	printf("filosofo->params->time_to_eat: %dms\n",
		(philo->params->n_time_to_eat));
	printf("filosofo->params->time_to_sleep: %dms\n",
		(philo->params->n_time_to_sleep));
	printf("filosofo->params->start_progam: %lld\n", philo->params->start_program);
	printf("--------------------------------------------------\n");
}

t_philo	*init_philo(int i, t_params *params)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	philo->params = params;
	philo->id = i;
	philo->id_fork_right = i;
	philo->time_lst_meal = (int)get_time(params->start_program);
	philo->meals_count = 0;
	pthread_mutex_init(&philo->last_meal_lock, NULL);
	if (i > 0)
		philo->id_fork_left = i - 1;
	else
		philo->id_fork_left = params->n_philo - 1;
	if(pthread_create(&philo->thread, NULL, &routine, philo) != 0)
	{
		printf("erro na cricao da thread");
		return (NULL);
	}
	//print_philos(philo, i);
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
	while (params->finish == 0)
	{
		usleep(100);
		if (check_any_dead(params))
			return (NULL);
	}
	return (NULL);
}

t_philo	**init_philos_array(t_params *params)
{
	t_philo	**philos;
	int			i;

	philos = malloc(sizeof(t_philo *) * params->n_philo);
	i = -1;
	if (!philos)
		return (NULL);
	init_forks(params);
	while (++i < params->n_philo)
		philos[i] = init_philo(i, params);
	i = -1;
	params->philos = philos;
	if(pthread_create(&params->thread_monitoring, NULL, &monitoring, params) != 0)
		return (NULL);
	while (++i < params->n_philo)
		pthread_join(philos[i]->thread, NULL);
	pthread_join(params->thread_monitoring, NULL);
	pthread_mutex_destroy(&params->finish_lock);
	pthread_mutex_destroy(&params->print);
	return (params->philos);
}
