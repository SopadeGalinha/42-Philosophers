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
	if (i > 0)
		philo->id_fork_left = i - 1;
	else
		philo->id_fork_left = params->n_philo - 1;
	if(pthread_create(&philo->thread, NULL, &routine, philo) != 0)
	{
		printf("erro na cricao da thread");
		return (0);
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

t_philo	**init_philos_array(t_params *params)
{
	t_philo		**philos;
	int			i;

	i = -1;
	philos = (t_philo **)malloc(sizeof(t_philo *) * params->n_philo);
	if (!philos)
	{
		printf("Erro ao inicializar os philos\n");
		return (NULL);
	}
	init_forks(params);
	while (++i < params->n_philo)
		philos[i] = init_philo(i, params);
	i = -1;
	while (++i < params->n_philo)
		pthread_join(philos[i]->thread, NULL);
	pthread_mutex_destroy(&params->mutex);
	return (philos);
}
