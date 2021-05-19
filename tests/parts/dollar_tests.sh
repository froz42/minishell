export multiple_tokens="token1    token2     token3"
export space_token1=" token1 token2 "
export space_token2=" token1 token2"
export space_token3="token1 token2 "
export space_token4="token1 token2"

echo $multiple_tokens
echo $multiple_tokens$multiple_tokens$multiple_tokens
echo "$multiple_tokens"
echo "$multiple_tokens$multiple_tokens$multiple_tokens"
echo $space_token1$space_token1$space_token1
echo $space_token1$space_token2$space_token3
echo $space_token3$space_token2$space_token1
echo $space_token3$space_token1$space_token2
echo $space_token2$space_token1$space_token3
echo $space_token2$space_token2$space_token2
echo $space_token3$space_token3$space_token3
echo $space_token1$space_token1$space_token1
echo $space_token2$space_token4$space_token3
echo $space_token4$space_token4$space_token4
echo $space_token4$space_token3$space_token4
echo fail
echo $space_token1$space_token4$space_token1
echo $space_token1$var$space_token4$var$space_token1
echo $USER$var\$USER$USER\$USERtest$USER

echo $var_unset
echo "$var_unset"

echo $USER$
echo $
echo $+
export hello="   "
echo $hello j
