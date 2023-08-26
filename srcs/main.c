/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:18:34 by heolivei          #+#    #+#             */
/*   Updated: 2023/08/26 09:29:08 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	clear_table(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args.nb_philo)
	{
		pthread_mutex_destroy(&table->philos[i]->is_done_lock);
		pthread_mutex_destroy(&table->philos[i]->last_meal_lock);
		free(table->philos[i]);
		i++;
	}
	pthread_mutex_destroy(&table->is_over_lock);
	pthread_mutex_destroy(&table->printzone);
	free(table->philos);
	free(table->forks);
	free(table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = init_table(ac, av);
	if (table)
		start_dinner(table);
	clear_table(table);
}
