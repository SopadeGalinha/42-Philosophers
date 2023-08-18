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

static void	set_params(t_params *input, int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		input->n_philo = ft_atoi(argv[1]);
		input->n_time_to_die = ft_atoi(argv[2]);
		input->n_time_to_eat = ft_atoi(argv[3]);
		input->n_time_to_sleep = ft_atoi(argv[4]);
		if (argc == 6)
			input->n_meals = ft_atoi(argv[5]);
		else
			input->n_meals = -1;
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

bool	initialization(t_params *input, int argc, char **argv)
{
	set_params(input, argc, argv);
	if (check_params(input, argc))
		return (true);
	return (false);
}
