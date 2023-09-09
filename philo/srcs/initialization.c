/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 19:01:50 by heolivei          #+#    #+#             */
/*   Updated: 2023/09/09 19:01:56 by heolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	set_params(t_params *params, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		params->start_program = get_time(0);
		params->n_philo = ft_atoi(argv[1]);
		params->n_time_to_die = ft_atoi(argv[2]);
		params->n_time_to_eat = ft_atoi(argv[3]);
		params->n_time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			params->n_meals = ft_atoi(argv[5]);
		else
			params->n_meals = -1;
	}
}

int	check_params(t_params *input, int argc)
{
	if (argc < 5 || argc > 6)
		return (printf("Try: ./philo <number_of_philos>"\
			" <time_to_die> <time_to_eat> <time_to_sleep> "\
			"\n[number_of_times_each_philosopher_must_eat] (optional)\n"));
	if (input->n_philo < 1)
		return (printf("Erro: Quantidade de filosofos invalida\n"));
	if (input->n_time_to_die < 1)
		return (printf("Erro: Tempo de vida invalido\n"));
	if (input->n_time_to_eat < 1)
		return (printf("Erro: Tempo para comer invalido\n"));
	if (input->n_time_to_sleep < 1)
		return (printf("Erro: Tempo para dormir invalido\n"));
	if (argc == 6 && (input->n_meals < 1))
		return (printf("Erro: Numero de refeicoes invalido\n"));
	return (0);
}

bool	initialization(t_params *params, int argc, char **argv)
{
	set_params(params, argc, argv);
	if (!check_params(params, argc))
		return (false);
	return (true);
}
