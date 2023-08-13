/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:47:24 by jhogonca          #+#    #+#             */
/*   Updated: 2023/07/21 22:47:24 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_table
{
    pthread_mutex_t *forks;
    pthread_mutex_t *print;
	pthread_mutex_t *dead;
}  t_table;

# endif