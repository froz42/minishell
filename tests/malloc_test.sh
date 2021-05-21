# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    malloc_test.sh                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/21 13:22:03 by tmatis            #+#    #+#              #
#    Updated: 2021/05/21 15:49:50 by tmatis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

fail_list="39 44 30 4 41 19 46 0 2 15 6 49 9 28 31 34 33 29 50 42 21 5 27 24 45 22 26 38 12 8 20 25 1 36 23 17 14 13 48 47 7 43 40 11 16 35 3 32 18 37 10 154 332 272 282 437 271 241 21 188 197 467 382 484 408 85 452 363 34 328 106 371 420 37 258 377 473 445 48 378 221 489 374 334 397 102 439 218 30 113 162 349 290 229 111 205 219 121 468 110 315 252 5822 706 3641 96 959 5226 4582 3490 5178 1479 3472 2182 4558 1317 2723 2260 2708 3811 3486 3631 5723 2877 3740 3561 4089 3576 4429 2765 1957 3244 2402 5468 4119 5397 2653 3365 5744 3312 5663 4389 5667 4888 4326 1182 356 3523 4802 2108 2728 5788 157"

error=0

rm -rf ./logs
mkdir -p ./logs
i=0
for fail_number in $fail_list
do
    cd ./malloc_fail/
    clang -Wall -Werror -Wextra -g -c my_malloc.c -D FAIL=$fail_number && ar -rcs libfail.a my_malloc.o
    rm my_malloc.o
    cd ..
	make -sC ../ malloc_test &> /dev/null
	mkdir ./sandbox
	../malloc_test < parts/large_test.sh > /dev/null 2>> ./logs/malloc_fail.log
	return_value=$?
	if [ $return_value -gt 130 ]
	then
	    printf "\033[0;31m$fail_number\033[m ratio: \033[0;31m[KO]\033[m  (check tests/logs/malloc_fail.log)\n"
		error=1
		rm -rf ./sandbox
		rm -rf ../malloc_test
		break
	fi
	((i = i + 1))
	rm -rf ./sandbox
	rm -rf ../malloc_test
done
printf "\033[0;32m$i\033[m test passed\n"
if [ $error -eq 0 ]
then
	printf "Protection \033[0;32m[OK]\033[m\n"
fi
rm 'malloc_fail/libfail.a'
exit $error
