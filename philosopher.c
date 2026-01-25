/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementngoie <clementngoie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:04:28 by clementngoi       #+#    #+#             */
/*   Updated: 2026/01/24 15:20:40 by clementngoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    think(t_philo *philo)
{
    printf("%d is thinking\n", philo->id);
}
void    take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    printf("%d has taken a fork\n", philo->id);
    pthread_mutex_lock(philo->right_fork);
    printf("%d has taken a fork\n", philo->id);
}
void    eat(t_philo *philo)
{
    printf("%d is eating\n", philo->id);
    philo->last_meal = timestamp();
    philo->meals_eaten++;
    usleep(philo->data->time_to_eat * 1000);
}
void    put_forks(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
void    sleep_philo(t_philo *philo)
{
    printf("%d is sleeping\n", philo->id);
    usleep(philo->data->time_to_sleep * 1000);
}

void    *routine(void *ac)
{
    t_philo *philo;
    philo = (t_philo *)ac;
    while (1)
    {
        think(philo);
        take_forks(philo);
        eat(philo);
        put_forks(philo);
        sleep_philo(philo);
    }
    return (NULL);
    
}