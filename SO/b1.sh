#Krzysztof Wydrzynski
#!/bin/bash

read litera
isEqual="true"

if [[ ${litera:1:1} == "=" ]]; then
   isEqual="false"
fi

litera=${litera:0:1}
litera2=$(echo "$litera" | tr /a-z/ /A-Z/)

while read linia; do
  dlugosc=${#linia}
  i=0
  wynik=0
  while [ $i -lt $dlugosc ]; do
    znak=${linia:$i:1}
    ((i++))
    if [ "$isEqual" = true ] && [[ "$znak" = "$litera2" ]]; then
      ((wynik++))
    elif [[ "$znak" = "$litera" ]]; then
      ((wynik++))
    fi
  done
  echo $wynik
done
