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
	t_philo *filosofo = (t_philo *)arg;

	/*printf("filosofo->table->time_to_die: %dms\n", (filosofo->table->n_time_to_die));
	printf("filosofo->table->time_to_eat: %dms\n", (filosofo->table->n_time_to_eat));
	printf("filosofo->table->time_to_sleep: %dms\n\n", (filosofo->table->n_time_to_sleep));*/

	printf("filosofo %d comecou a comer.\n", filosofo->id);
	//pthread_mutex_lock(&filosofo->fork_left);
	//pthread_mutex_lock(&filosofo->fork_right);
	usleep(filosofo->table->n_time_to_eat * 1000);
	//pthread_mutex_unlock(&filosofo->fork_left);
	//pthread_mutex_unlock(&filosofo->fork_right);
	printf("filosofo %d acabou de comer.\n\n ", filosofo->id);
	/*printf("filosofo->id: %d\n", (filosofo->id));
	printf("filosofo->time_lst_meal: %d\n", (filosofo->time_lst_meal));
	printf("filosofo->fork: %p\n", (void *)(&filosofo->fork));
	printf("filosofo->thread: %ld\n", (filosofo->thread));
	printf("filosofo->table->time_to_die: %dms\n", (filosofo->table->n_time_to_die));
	printf("filosofo->table->time_to_eat: %dms\n", (filosofo->table->n_time_to_eat));
	printf("filosofo->table->time_to_sleep: %dms\n\n", (filosofo->table->n_time_to_sleep));*/

	return (0);
}
t_philo	**init_philo(t_params *params)
{
	t_philo	**philos;
	int	i = 0;
	philos = (t_philo **)malloc(sizeof(t_philo *) * params->n_philo);
	if(!philos)
	{
		printf("Erro ao inicializar os philos\n");
		return (NULL);
	}
	while (i < params->n_philo)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		philos[i]->id  = i;
		pthread_create(&philos[i]->thread, NULL, rotine, philos[i]);
		if (pthread_mutex_init(&philos[i]->fork_right, NULL) != 0)
		{
			printf("Erro ao inicializar o mutex\n");
			return(NULL);
		}
		if (i < (params->n_philo - 1))
			philos[i + 1]->fork_left = philos[i]->fork_right;
		else if (i == (params->n_philo - 1))
			philos[0]->fork_left = philos[i]->fork_right;
		philos[i]->table = params;
		philos[i]->time_lst_meal = get_time(philos[i]->table);
		i++;
	}
	i = 0;
	while (i < params->n_philo)
		pthread_join(philos[i++]->thread, NULL);
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

	philos = init_philo(&params);
	return (0);
}
