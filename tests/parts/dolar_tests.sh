export multiple_tokens="token1    token2     token3"
export space_token=" token1 token2"
echo $multiple_tokens
echo "$multiple_tokens"
echo "$multiple_tokens$multiple_tokens$multiple_tokens"
echo "$multiple_tokens$space_token$multiple_tokens"
echo $var_unset
echo "$var_unset"