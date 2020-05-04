#Krzysztof Wydrzynski
#!/bin/bash

declare -A assoc

kolejnosc=()
i=0
while read linia; do
  ((assoc[$linia]++))
  kolejnosc[$i]=$linia
  ((i++))
done

min=100000
max=$i
i=0
while [ $i -le $max ]; do
  if [ ${assoc[${kolejnosc[$i]}]} -lt $min ]; then
    min=${assoc[${kolejnosc[$i]}]}
    minNazwa=${kolejnosc[$i]}
  fi
  ((i++))
done

if [ $min -eq 100000 ]; then
  echo ""
else
  echo "$minNazwa ${assoc[$minNazwa]}"
fi
