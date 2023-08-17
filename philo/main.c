/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heolivei <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:18:34 by heolivei          #+#    #+#             */
/*   Updated: 2023/08/17 20:18:41 by heolivei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	c;
	int	s;
	int	res;

	c = 0;
	s = 1;
	res = 0;
	while (str[c] == ' ' || str[c] == '\n' || str[c] == '\t'
		|| str[c] == '\v' || str[c] == '\f' || str[c] == '\r')
		c++;
	if (str[c] == '-' || str[c] == '+')
	{
		if (str[c] == '-')
			s = -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		res = (res * 10) + (str[c] - 48);
		c++;
	}
	return (res * s);
}

void	set_params(t_params *input, int argc, char **argv)
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
	{
		printf("./philo <number_of_philos> <time_to_die ");
		return (printf("<time_to_eat> <time_to_sleep> [eat_number_times]\n"));
	}
	if (input->n_philo < 1)
		return (printf("Quantidade de filosofos invalida\n"));
	if (input->n_time_to_die < 1)
		return (printf("Tempo de vida invalido\n"));
	if (input->n_time_to_eat < 1)
		return (printf("Tempo para comer invalido\n"));
	if (input->n_time_to_sleep < 1)
		return (printf("Tempo para dormir invalido\n"));
	if (input->n_meals < -1 || input->n_meals == 0)
		return (printf("Numero de refeicoes invalido\n"));
	return (0);
}

void	ft_print_params(t_params *input, int argc)
{
	printf("Número de filósofos: %d\n", input->n_philo);
	printf("Tempo para morrer: %d\n", input->n_time_to_die);
	printf("Tempo para comer: %d\n", input->n_time_to_eat);
	printf("Tempo para dormir: %d\n", input->n_time_to_sleep);
	if (argc == 6)
		printf("Quantide de refeicoes: %d\n", input->n_meals);
	else
		printf("Sem quantidade de refeicoes definida: %d\n", input->n_meals);
}

int	main(int argc, char **argv)
{
	t_params	input;

	input = (t_params){0};
	set_params(&input, argc, argv);
	check_params(&input, argc);
	if (argc == 5 || argc == 6)
		ft_print_params(&input, argc);
	return (0);
}
//cc main.c -o philo
