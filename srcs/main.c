/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:18:34 by heolivei          #+#    #+#             */
/*   Updated: 2023/08/29 02:19:14 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = init_table(ac, av);
	printf("\n");
	if (!table)
		return (1);
	if (!start_dinner(table))
		return (1);
	clean_table(&table);
	return (0);
}
