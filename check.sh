#!/bin/bash

printf "\n\n\n\n\n"

make

#1==================without infile and outfile

./philo 5 3100 1000 1000 9
#valgrind --leak-check=full --show-leak-kinds=all ./philo infile "grgh" "hjkfhk" outfile 
