#!/bin/bash

#free in error cases
#add mutexes check list

printf "\n\n\n\n\n"

make


./philo 4 310 200 dsf klk

./philo 0 800 200 200

./philo 4 310 -200 100

./philo 1 800 200 200

#./philo 5 800 200 200 7

#./philo 4 410 200 200

#./philo 4 310 200 100



./philo_bonus 4 310 200 dsf klk

./philo_bonus 0 800 200 200

./philo_bonus 4 310 -200 100

./philo_bonus 5 800 200 200

./philo_bonus 5 800 200 200 7

./philo_bonus 4 500 200 200






















#valgrind --leak-check=full --show-leak-kinds=all ./philo 1 800 200 200

