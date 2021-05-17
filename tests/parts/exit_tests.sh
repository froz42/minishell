echo hello | exit 12
echo $?
echo hello | exit 0
echo $?
echo hello | exit 255
echo $?
echo hello | exit 90000000
exit 0
echo should not be displayed