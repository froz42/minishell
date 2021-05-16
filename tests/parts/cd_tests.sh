cd does_not_exist
echo $?
cd tests
echo $?
/bin/pwd
cd ../../../../../../
echo $?
/bin/pwd
cd
echo $?
/bin/pwd
exit 0