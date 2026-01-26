/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clementngoie <clementngoie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 14:04:28 by clementngoi       #+#    #+#             */
/*   Updated: 2026/01/26 12:55:09 by clementngoi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void    think(t_philo *philo)
{
    if (is_dead(philo->data))
        return;
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%d is thinking\n", philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
}
void take_forks(t_philo *philo)
{
    if (philo->data->nb_philo == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        printf("%ld %d has taken a fork\n",
            timestamp() - philo->data->start_time, philo->id);
        usleep(philo->data->time_to_die * 1000);
        pthread_mutex_unlock(philo->left_fork);
        return;
    }

    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        printf("%ld %d has taken right fork\n",
            timestamp() - philo->data->start_time, philo->id);
        pthread_mutex_lock(philo->left_fork);
        printf("%ld %d has taken left fork\n",
            timestamp() - philo->data->start_time, philo->id);
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        printf("%ld %d has taken left fork\n",
            timestamp() - philo->data->start_time, philo->id);
        pthread_mutex_lock(philo->right_fork);
        printf("%ld %d has taken right fork\n",
            timestamp() - philo->data->start_time, philo->id);
    }
}

void    eat(t_philo *philo)
{
    if (is_dead(philo->data))
        return;
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%d is eating\n", philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = timestamp() - philo->data->start_time;
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);
    usleep(philo->data->time_to_eat * 1000);
}
void    put_forks(t_philo *philo)
{
    if (is_dead(philo->data))
        return;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}
void    sleep_philo(t_philo *philo)
{
    if (is_dead(philo->data))
        return;
    pthread_mutex_lock(&philo->data->print_mutex);
    printf("%d is sleeping\n", philo->id);
    pthread_mutex_unlock(&philo->data->print_mutex);
    usleep(philo->data->time_to_sleep * 1000);
}

void    *routine(void *ac)
{
    t_philo *philo;
    philo = (t_philo *)ac;
    printf("%ld %d started routine\n", timestamp() - philo->data->start_time, philo->id);

    if (philo->data->nb_philo == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(&philo->data->print_mutex);
        printf("%ld %d has taken a fork\n",
        timestamp() - philo->data->start_time,
        philo->id);
        pthread_mutex_unlock(&philo->data->print_mutex);

        usleep(philo->data->time_to_die * 1000);
        pthread_mutex_unlock(philo->left_fork);
        return(NULL);
    }
    while (!is_dead(philo->data))
    {
        think(philo);
        take_forks(philo);
        eat(philo);
        put_forks(philo);
        sleep_philo(philo);
    }
    return (NULL);
    
}