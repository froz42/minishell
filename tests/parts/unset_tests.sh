export hello=yo
export | grep hello
env | grep hello
unset hello
export | grep hello
env | grep hello
export var1
unset var1
export var2=yolo var3=yolo
unset var2 var3
export | grep var2
export | grep var3
exit 0