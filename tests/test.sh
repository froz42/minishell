# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmatis <tmatis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/15 13:57:53 by tmatis            #+#    #+#              #
#    Updated: 2021/05/22 12:56:21 by tmatis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# This program is going to test leaks, memory error, fd leaks, and output

printf "\n###MINISHELL UNIT TEST###\n\n"

scripts_list=`ls -t parts/` # liste des scripts

mkdir -p ./outs/ # on cree le repertoire des outputs
mkdir -p ./logs/ # on cree le repertoire des logs
mkdir -p ./diffs/ # on cree le repertoire des diffs

errors=0;

for elem in $scripts_list
do
    printf "\033[0;34mtesting: \033[0;36m$elem\n\033[m"
    mkdir ./sandbox
    bash < parts/$elem > outs/$elem\_bash.out 2> /dev/null
    rm -rf ./sandbox/*
    valgrind --track-fds=yes --leak-check=full --show-reachable=yes --error-exitcode=1 --track-origins=yes \
    ../minishell < parts/$elem > outs/$elem\_minishell.out 2> ./logs/$elem.log
    error_code=$?
    rm -rf ./sandbox
    printf "  \033[0;34mmemory health:		"
    if [ $error_code -eq 0 ]
    then
        printf "\033[0;32m[OK]\033[m\n"
    else
        printf "\033[0;31m[KO]\033[m  (check tests/logs/$elem.log)\n"
        error=1
    fi
    grep < ./logs/$elem.log "still reachable" > /dev/null
    error_code=$?
    printf "  \033[0;34mstill reachable:		"
    if [ $error_code -eq 1 ]
    then
        printf "\033[0;32m[OK]\033[m\n"
    else
        printf "\033[0;31m[KO]\033[m  (check tests/logs/$elem.log)\n"
        error=1
    fi
    grep < ./logs/$elem.log ": file" > /dev/null
    error_code=$?
    grep < ./logs/$elem.log "Open file descriptor .:" > /dev/null
    error_code2=$?
    printf "  \033[0;34mfd leaks:			"
    if [ $error_code -eq 1 ] && [ $error_code2 -eq 1 ]
    then
        printf "\033[0;32m[OK]\033[m\n"
    else
        printf "\033[0;31m[KO]\033[m  (check tests/logs/$elem.log)\n"
        error=1
    fi
    diff -c outs/$elem\_bash.out outs/$elem\_minishell.out > ./diffs/$elem.diff
    error_code=$?
    printf "  \033[0;34moutput:			"
    if [ $error_code -eq 0 ]
    then
        printf "\033[0;32m[OK]\033[m\n"
    else
        printf "\033[0;31m[KO]\033[m  (check tests/parts/$elem)\n"
		cat ./diffs/$elem.diff
        error=1
    fi
    printf "\n"
done

printf "\033[0;34mtesting: \033[0;36mcrash_test.sh\n\033[m"
mkdir ./sandbox
valgrind --track-fds=yes --leak-check=full --show-reachable=yes --error-exitcode=1 \
../minishell < crash_test.sh > outs/crash_test.sh_minishell.out 2> ./logs/crash_test.sh.log
error_code=$?
rm -rf ./sandbox
printf "  \033[0;34mmemory health:		"
if [ $error_code -eq 0 ]
then
    printf "\033[0;32m[OK]\033[m\n"
else
    printf "\033[0;31m[KO]\033[m  (check tests/logs/crash_test.sh.log)\n"
    error=1
fi
grep < ./logs/crash_test.sh.log "still reachable" > /dev/null
error_code=$?
printf "  \033[0;34mstill reachable:		"
if [ $error_code -eq 1 ]
then
    printf "\033[0;32m[OK]\033[m\n"
else
    printf "\033[0;31m[KO]\033[m  (check tests/logs/crash_test.sh.log)\n"
    error=1
fi
grep < ./logs/crash_test.sh.log ": file" > /dev/null
error_code=$?
grep < ./logs/crash_test.sh.log "Open file descriptor .:" > /dev/null
error_code2=$?
printf "  \033[0;34mfd leaks:			"
if [ $error_code -eq 1 ] && [ $error_code2 -eq 1 ]
then
    printf "\033[0;32m[OK]\033[m\n"
else
    printf "\033[0;31m[KO]\033[m  (check tests/logs/crash_test.sh.log)\n"
    error=1
fi
exit $error

#rm -r ./outs/
