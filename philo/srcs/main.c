/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:32:40 by heolivei          #+#    #+#             */
/*   Updated: 2023/08/30 12:32:51 by heolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print_params(t_params *params, int argc)
{
	printf("\nNúmero de filósofos: %d\n", params->n_philo);
	printf("Tempo para morrer: %d\n", params->n_time_to_die);
	printf("Tempo para comer: %d\n", params->n_time_to_eat);
	printf("Tempo para dormir: %d\n", params->n_time_to_sleep);
	if (argc == 6)
		printf("Quantide de refeicoes: %d\n\n", params->n_meals);
	else
		printf("Sem quantidade de refeicoes definida\n\n");
}

int	get_time(t_params *params)
{
	struct timeval	time;
	(void)params;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	// - (params->starttime.tv_sec)
	return (printf("%ld\n", (time.tv_usec) / 1000));
}
void *rotine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	/*printf("filosofo->table->time_to_die: %dms\n", (filosofo->table->n_time_to_die));
	printf("filosofo->table->time_to_eat: %dms\n", (filosofo->table->n_time_to_eat));
	printf("filosofo->table->time_to_sleep: %dms\n\n", (filosofo->table->n_time_to_sleep));*/

	//printf("filosofo %d comecou a comer.\n", philo->id);
	//pthread_mutex_lock(&filosofo->fork_left);
	//pthread_mutex_lock(&filosofo->fork_right);
	//usleep(philo->params->n_time_to_eat * 1000);
	//pthread_mutex_unlock(&filosofo->fork_left);
	//pthread_mutex_unlock(&filosofo->fork_right);
	//printf("filosofo %d acabou de comer.\n\n ", philo->id);
	(void)philo;

	return (0);
}

void	print_philos(t_philo *philo, int i)
{
	printf("filosofo->id: %d\n", (philo->id));
	printf("filosofo->time_lst_meal: %d\n", (philo->time_lst_meal));
	printf("filosofo->fork: %p\n", (void *)(&philo->params->forks[i]));
	printf("filosofo->id_fork_left: %d\n", (philo->id_fork_left));
	printf("filosofo->id_fork_right: %d\n", (philo->id_fork_right));
	printf("filosofo->thread: %ld\n", (philo->thread));
	printf("\n");
	printf("filosofo->table->time_to_die: %dms\n", (philo->params->n_time_to_die));
	printf("filosofo->table->time_to_eat: %dms\n", (philo->params->n_time_to_eat));
	printf("filosofo->table->time_to_sleep: %dms\n", (philo->params->n_time_to_sleep));
	printf("--------------------------------------------------\n");
}
t_philo	*init_philo(int i, t_params *params)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	
	philo->params = params;
	philo->id = i;
	philo->time_lst_meal = get_time(params);
	philo->id_fork_right = i;
	if (i > 0)
		philo->id_fork_left = i - 1;
	else
		philo->id_fork_left = params->n_philo - 1;
	pthread_create(&philo->thread, NULL, rotine, philo);
	print_philos(philo, i);
	return (0);
}

void	init_forks(t_params *params)
{
	int i;

	i = 0;
	params->forks = malloc(sizeof(pthread_mutex_t) * params->n_philo);
	while (i < params->n_philo)
	{
		if (pthread_mutex_init(&params->forks[i], NULL) != 0)
		{
			printf("Erro ao inicializar o mutex\n");
			return;
		}
		i++;
	}
}

t_philo	**init_philos_array(t_params *params)
{
	t_philo	**philos;
	int	i = -1;
	philos = (t_philo **)malloc(sizeof(t_philo *) * params->n_philo);
	if(!philos)
	{
		printf("Erro ao inicializar os philos\n");
		return (NULL);
	}
	init_forks(params);
	while (++i < params->n_philo)
		philos[i] = init_philo(i, params);

	return (philos);
}
int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		**philos;

	params = (t_params){0};
	pthread_mutex_init(&params.mutex, NULL);
	pthread_mutex_init(&params.mutex, NULL);
	
	if (initialization(&params, argc, argv))
		return (printf("feito"));
	if (argc == 5 || argc == 6)
		ft_print_params(&params, argc);

	philos = init_philos_array(&params);
	return (0);
}
