export var1=hi
echo $var1
export var1+=" tmatis"
echo $var1
export var1
echo $var1
export | grep var1
export var_unset
export | grep var_unset
echo $var_unset
export var_unset="set now"
echo $var_unset
env | grep var_unset
export var_unset=
echo $var_unset
export var2=yo var2+=yo
echo $var2
export var5=yo; echo $var5
export var6=yo var7=log
echo $var6 echo $var7
env | grep var6
export noassign
export | grep noassign
env | grep noassign
exit 0;