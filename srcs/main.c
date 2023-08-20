/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:18:34 by heolivei          #+#    #+#             */
/*   Updated: 2023/08/19 01:01:02 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_config	config;
	bool	error;

	config = (t_config){0};
	error = initialization(&config, argc, argv);
	if (error)
		return (1);
	if (argc == 5 || argc == 6)
		ft_print_params(&config, argc);
	return (0);
}
