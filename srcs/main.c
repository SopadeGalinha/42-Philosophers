/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhogonca <jhogonca@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:44:55 by jhogonca          #+#    #+#             */
/*   Updated: 2023/07/21 22:44:55 by jhogonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

/* STEPS:
1. set table
	- check args
	- init mutexes
	- set args
	- set forks
	- set philosophers
2. start dinner
3. end dinner
4. clear table

*/

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int shared_variable = 0;

void* thread_function(void* arg) {
    for (int i = 0; i < 10000; ++i) {
        pthread_mutex_lock(&mutex); 
        shared_variable++;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, thread_function, NULL);
    pthread_create(&thread2, NULL, thread_function, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("Shared variable value: %d\n", shared_variable);

    return 0;
}
