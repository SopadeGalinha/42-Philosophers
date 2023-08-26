/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/26 09:04:58 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/26 09:04:58 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"


void	*simulation(void	*philo)
{
	printf("Hi from philo %d\n", ((t_philo *)philo)->id);
}

int	start_dinner(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->args.nb_philo)
	{
		if (pthread_create(&table->philos[i]->thread_id, NULL,\
			simulation, table->philos[i]) != 0)
			return (printf("Error creating thread for philo %d\n", i + 1));
		i++;
	}
	i = 0;
	while (i < table->args.nb_philo)
	{
		if (pthread_join(table->philos[i]->thread_id, NULL) != 0)
			return (printf("Error joining thread for philo %d\n", i + 1));
		i++;
	}
	return (0);
}