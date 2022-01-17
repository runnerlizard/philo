#!/bin/bash

printf "\n\n\n\n\n"

make

#1==================without infile and outfile

./philo 2 10000 1000 1000 5
#valgrind --leak-check=full --show-leak-kinds=all ./philo infile "grgh" "hjkfhk" outfile 
