/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:18:34 by heolivei          #+#    #+#             */
/*   Updated: 2023/08/18 12:49:41 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_print_params(t_params *input, int argc)
{
	printf("\nNúmero de filósofos: %d\n", input->n_philo);
	printf("Tempo para morrer: %d\n", input->n_time_to_die);
	printf("Tempo para comer: %d\n", input->n_time_to_eat);
	printf("Tempo para dormir: %d\n", input->n_time_to_sleep);
	if (argc == 6)
		printf("Quantide de refeicoes: %d\n", input->n_meals);
	else
		printf("Sem quantidade de refeicoes definida\n");
}

int	main(int argc, char **argv)
{
	t_params	input;
	bool		error;

	input = (t_params){0};
	error = initialization(&input, argc, argv);
	if (error)
		return (1);
	if (argc == 5 || argc == 6)
		ft_print_params(&input, argc);
	return (0);
}
