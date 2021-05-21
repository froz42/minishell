# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    malloc_test.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 13:22:03 by tmatis            #+#    #+#              #
#    Updated: 2021/05/21 15:03:45 by tmatis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

fail_list="1 8 9 233 377 610 987 1597 2584 4181 6765 420"

error=0

mkdir ./logs

for fail_number in $fail_list
do
    printf "\033[0;34mCompiling malloc fail lib: "
    cd ./malloc_fail/
    clang -Wall -Werror -Wextra -g -c my_malloc.c -D FAIL=$fail_number && ar -rcs libfail.a my_malloc.o
    rm my_malloc.o
    cd ..
    printf "\033[0;32m[OK]\033[m\n"
	printf "\033[0;34mCompiling malloc test bin: "
	make -sC ../ malloc_test &> /dev/null
	printf "\033[0;32m[OK]\033[m\n"
	mkdir ./sandbox
	../malloc_test < parts/large_test.sh > /dev/null 2>> ./logs/malloc_fail.log
	echo the exit number is $?
	rm -rf ./sandbox
	rm -rf ../malloc_test
done
rm 'malloc_fail/libfail.a'
