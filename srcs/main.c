/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:18:34 by heolivei          #+#    #+#             */
/*   Updated: 2023/08/26 12:54:25 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

static void	clean_table(t_table *table)
{
	int	i;

	printf(ESC_RESET);
	if (!table)
		return ;
	i = -1;
	pthread_mutex_destroy(&table->is_over_lock);
	pthread_mutex_destroy(&table->printzone);
	if (table->forks)
		while (++i < table->args.nb_philo)
			pthread_mutex_destroy(&table->forks[i]);
	i = -1;
	while (++i < table->args.nb_philo)
	{
		pthread_mutex_destroy(&table->philos[i]->is_done_lock);
		pthread_mutex_destroy(&table->philos[i]->last_meal_lock);
		free(table->philos[i]);
	}
	free(table->philos);
	free(table->forks);
	free(table);
}

int	main(int ac, char **av)
{
	t_table	*table;

	table = init_table(ac, av);
	printf("\n");
	if (table)
		start_dinner(table);
	clean_table(table);
	return (0);
}
