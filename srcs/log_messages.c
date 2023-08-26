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

static void	printdead(t_philo *philo, t_table *table, char *log_msg, char *color)
{
	long	since_start;

	since_start = get_time(table);
	printf("%s%ld %d %s%s\n", color, since_start, philo->id, log_msg, ESC_BOLD_RED);
}

void	log_message(t_philo *philo, t_table *table, char *log_msg, char *color)
{
	long	since_start;

	pthread_mutex_lock(philo->print_zone);
	since_start = get_time(table);
	printf("%s%ld %d %s%s\n", color, since_start, philo->id, log_msg, ESC_BOLD_WHITE);
	pthread_mutex_unlock(philo->print_zone);
}
