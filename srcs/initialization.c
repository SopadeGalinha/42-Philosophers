/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:33:06 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/18 11:33:06 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

/* Set the start time at the first call
return the time in ms that passed since the first call */
int	get_time(t_config *config)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000)\
		+ (time.tv_usec / 1000) - (config->starttime.tv_sec));
}

static void	set_params(t_config *config, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{	
		config->n_philo = ft_atoi(argv[1]);
		config->t_to_die = ft_atoi(argv[2]);
		config->t_to_eat = ft_atoi(argv[3]);
		config->t_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			config->n_meals = ft_atoi(argv[5]);
		else
			config->n_meals = -1;
	}
}

int	check_params(t_config *config, int argc)
{
	printf("time in ms: %i\n\n\n", get_time(config));
	if (argc < 5 || argc > 6)
		return (printf("Try: ./config <number_of_philos>"\
			" <time_to_die> <time_to_eat> <time_to_sleep> "\
			"\n[number_of_times_each_philosopher_must_eat] (optional)\n"));
	if (config->n_philo < 1)
		return (printf("Erro: Quantidade de filosofos invalida\n"));
	if (config->t_to_die < 1)
		return (printf("Erro: Tempo de vida invalido\n"));
	if (config->t_to_eat < 1)
		return (printf("Erro: Tempo para comer invalido\n"));
	if (config->t_to_sleep < 1)
		return (printf("Erro: Tempo para dormir invalido\n"));
	if (argc == 6 && (config->n_meals < 1))
		return (printf("Erro: Numero de refeicoes invalido\n"));
	return (0);
}

bool	initialization(t_config *config, int argc, char **argv)
{
	set_params(config, argc, argv);
	if (check_params(config, argc))
		return (true);

	config->starttime.tv_sec =  get_time(config);
	sleep(1);
	printf("time passed since the set of start time: %ims\n", get_time(config));
	return (false);
}
