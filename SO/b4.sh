#Krzysztof Wydrzynski
#!/bin/bash

i=0
suma=0
liczby=()
regex='^[0-9]+$'
while read linia; do
  if [[ $linia =~ $regex ]]; then
    liczby[$i]=$linia
    suma=$((suma+linia))
    ((i++))
  fi
done
if [ $i -le 0 ]; then
  i=1
fi

srednia=$((suma/i))

j=0
max=${#liczby[@]}
sum=0
while [ $j -lt $max ]; do
  first=$((liczby[j]-srednia))
  liczba=$[first**2]
  sum=$((sum+liczba))
  ((j++))
done

wariancja=$((sum/i))

echo $srednia
echo $wariancja
