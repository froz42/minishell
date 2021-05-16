cat test.sh | cat -e
echo hello | wc -l
export | grep USER | wc -l
cat /dev/urandom | head -n 10 | wc -l
cd ./sandbox
cat ../test.sh > file | cat -e > file2 | wc -l
cat file file2
echo hello | cat < file | wc
exit 0