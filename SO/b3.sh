#Krzysztof Wydrzynski
#!/bin/bash
read linia
pierwsza=0
druga=1
i=0
max=$linia
while [ $i -lt $max ]; do
  ((i++))
  echo "$pierwsza "
  wartosc=$((pierwsza+druga))
  pierwsza=$druga
  druga=$wartosc
done
