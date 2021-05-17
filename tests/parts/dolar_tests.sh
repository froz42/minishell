export multiple_tokens="token1    token2     token3"
<<<<<<< HEAD
export space_token1=" token1 token2 "
export space_token2=" token1 token2"
export space_token3="token1 token2 "
=======
export space_token=" token1 token2 "
export space_token2="token1 token2 "
export space_token3=" token1 token2"
>>>>>>> origin/master

echo $multiple_tokens
echo $multiple_tokens$multiple_tokens$multiple_tokens
echo "$multiple_tokens"
echo "$multiple_tokens$multiple_tokens$multiple_tokens"
<<<<<<< HEAD
echo $space_token1$space_token1$space_token1
echo $space_token1$space_token2$space_token3
echo $space_token3$space_token2$space_token1
echo $space_token3$space_token1$space_token2
echo $space_token2$space_token1$space_token3
echo $space_token2$space_token2$space_token2
echo $space_token3$space_token3$space_token3
echo $space_token1$space_token1$space_token1

=======
echo "$multiple_tokens$space_token$multiple_tokens"
echo $space_token$space_token$space_token
echo $space_token2$space_token2$space_token2
echo $space_token3$space_token3$space_token3
echo $space_token$space_token2$space_token3
echo $space_token3$space_token2$space_token1
echo $space_token3$space_token1$space_token2
echo $space_token2$space_token1$space_token3
echo $USER$var\$USER$USER\$USERtest$USER
>>>>>>> origin/master
echo $var_unset
echo "$var_unset"