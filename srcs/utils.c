/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_messages.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 11:01:17 by jhogonca          #+#    #+#             */
/*   Updated: 2023/08/24 11:01:17 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	clean_table(t_table *table)
{
	int	i;

	if (!table)
		return ;
	i = -1;
	pthread_mutex_destroy(&table->printzone);
	pthread_mutex_destroy(&table->is_over_lock);
	if (table->forks)
		while (++i < table->args.nb_philo)
			pthread_mutex_destroy(&table->forks[i]);
	i = -1;
	while (++i < table->args.nb_philo)
	{
		pthread_mutex_destroy(table->philos[i]->print_zone);
		pthread_mutex_destroy(table->philos[i]->is_over_lock);
		pthread_mutex_destroy(&table->philos[i]->last_meal_lock);
		pthread_mutex_destroy(&table->philos[i]->is_done_lock);
		free(table->philos[i]);
	}
	if (table->philos)
		free(table->philos);
	if (table->forks)
		free(table->forks);
	free(table);
}

void	log_message(t_philo *philo, t_table *table, char *log_msg, char *color)
{
	long	since_start;

	pthread_mutex_lock(philo->print_zone);
	since_start = get_time(table);
	printf("%s%ld %d %s%s\n", color, \
		since_start, philo->id, log_msg, ESC_BOLD_WHITE);
	pthread_mutex_unlock(philo->print_zone);
}

int	get_time(t_table *table)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) \
		+ (time.tv_usec / 1000) - (table->start_time.tv_sec));
}

bool	is_meal_over(t_philo *philo)
{
	bool	is_over;
	bool	is_done;

	pthread_mutex_lock(philo->is_over_lock);
	is_over = *philo->is_over;
	pthread_mutex_unlock(philo->is_over_lock);
	if (is_over)
		return (true);
	pthread_mutex_lock(&philo->is_done_lock);
	is_done = philo->is_done;
	pthread_mutex_unlock(&philo->is_done_lock);
	if (is_done)
		return (true);
	return (false);
}
