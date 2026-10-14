# 🍝 Philosophers (philo) - 42 School

**Philosophers** est un projet d'initiation à la programmation multithread, à la synchronisation de processus et au partage de ressources en C, basé sur le célèbre problème du *Dîner des Philosophes* posé par Edsger Dijkstra.

---

## 🚀 Fonctionnalités
- **Gestion des Threads (`pthread`)** : Chaque philosophe est représenté par un thread indépendant s'exécutant en parallèle.
- **Protection des Ressources (`mutex`)** : Utilisation de verrous mutuels (`pthread_mutex_t`) pour éviter les accès concurrents (*data races*) sur les fourchettes et l'affichage.
- **Surveillance de la Famine** : Un mécanisme de monitoring vérifie en continu le temps écoulé depuis le dernier repas de chaque philosophe pour déclencher l'arrêt immédiat en cas de mort.
- **Affichage Synchronisé** : Les logs d'état (prise de fourchette, repas, sommeil, pensée, mort) sont sérialisés pour garantir une sortie claire sur le terminal sans chevauchement.

---

## 🛠️ Compilation & Utilisation

### 1. Compiler le projet
Le projet se compile via le `Makefile` avec les flags de norme stricts (`-Wall -Wextra -Werror`) :
bash
make

###  2. Exécuter la simulation
Le programme prend 4 arguments obligatoires et 1 optionnel :
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Exemples :
Test de mort rapide (1 seul philosophe) :
./philo 1 800 200 200
(Le philosophe meurt après 800 ms car il n'a qu'une seule fourchette).
Simulation infinie sans mort :
./philo 5 800 200 200
Simulation avec nombre de repas limité :
./philo 5 800 200 200 7
La simulation s'arrête automatiquement une fois que chaque philosophe a mangé au moins 7 fois).

💻 Règles & Paramètres
number_of_philosophers : Le nombre de philosophes (et de fourchettes).
time_to_die (en ms) : Temps maximum qu'un philosophe peut passer sans manger avant de mourir.
time_to_eat (en ms) : Temps nécessaire à un philosophe pour manger (nécessite 2 fourchettes).
time_to_sleep (en ms) : Temps passé à dormir après avoir mangé.

📐 Stack Technique
Langage : C
Multithreading : pthread_create, pthread_join, pthread_detach
Synchronisation : pthread_mutex_init, pthread_mutex_lock, pthread_mutex_unlock, pthread_mutex_destroy
Gestion du temps : gettimeofday, usleep
[number_of_times_each_philosopher_must_eat] (optionnel) : Nombre de repas requis par philosophe pour terminer la simulation.
