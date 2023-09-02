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

long long int	get_time(long long int start_time)
{
	struct timeval	time;
	long long int	current_time;

	gettimeofday(&time, NULL);
	current_time = (time.tv_sec * 1000) + (time.tv_usec / 1000) - start_time;
	return (current_time);
}

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


int	main(int argc, char **argv)
{
	t_params	params;
	t_philo		**philos;

	params = (t_params){0};
	pthread_mutex_init(&params.mutex, NULL);
	pthread_mutex_init(&params.mutex, NULL);
	if (initialization(&params, argc, argv))
		return (printf("error"));
	if (argc == 5 || argc == 6)
		ft_print_params(&params, argc);
	philos = init_philos_array(&params);
	
	return (0);
}
