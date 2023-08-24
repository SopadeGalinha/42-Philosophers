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

void	log_message(t_philo *philo, t_table *table, char *log_msg, char *color)
{
	int	ms_since_start;

	pthread_mutex_lock(&table->printzone);
	ms_since_start = get_time(table);
	printf("%s%d %d %s%s\n", color, ms_since_start, philo->id, log_msg, ESC_WHITE);
	pthread_mutex_unlock(&table->printzone);
}
