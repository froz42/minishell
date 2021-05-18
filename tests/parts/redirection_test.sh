echo "create dir"
echo "cd dir"
cd ./sandbox
/bin/pwd
echo "hello world" > file
ls
cat < file
echo "hello france" >> file
ls
cat < file
rm -rf file
echo "hi" > file1 > file2 > file3
ls
cat file1 file2 file3
> file2 > file3
exit 0