#Krzysztof Wydrzynski
#!/bin/bash

read a

while read linia; do
  i=0
  dlugosc=${#linia}
  operation=0
  isFolder="F"
  isAFile="F"
  permisions=""
  number=0
  r="r"
  filename=""
  staryZnak=" "
  while [ $i -le $dlugosc ]; do
    znak=${linia:$i:1}
    if [ $operation -eq 0 ]; then
      if [ $i -eq 4 ] || [ $i -eq 7 ] || [ $i -eq 10 ]; then
          permisions="$permisions$number"
          number=0
      fi

      if [ $i -eq 0 ]; then
        if [[ "$znak" = "d" ]]; then
          isFolder="T"
        fi
      elif [ $i -eq 1 ] || [ $i -eq 4 ] || [ $i -eq 7 ]; then
        if [[ "$znak" = "r" ]]; then
          ((number+=4))
        fi
      elif [ $i -eq 2 ] || [ $i -eq 5 ] || [ $i -eq 8 ]; then
        if [[ "$znak" = "w" ]]; then
          ((number+=2))
        fi
      elif [ $i -eq 3 ] || [ $i -eq 6 ] || [ $i -eq 9 ]; then
        if [[ "$znak" = "x" ]]; then
          ((number+=1))
          if [ $i -eq 3 ]; then
            isAFile="T"
          fi
        fi
      fi

    elif [ $operation -eq 8 ]; then
      filename=$filename$znak
    fi
    
    if [[ "$znak" = " " ]] && [[ "$staryZnak" != " " ]]; then
      ((operation++))
    fi
  staryZnak=$znak
  ((i++))
  done
  znak=" "
  if [[ "$isAFile" = "T" ]]; then
    znak="* "
  fi
  if [[ "$isFolder" = "T" ]]; then
    znak="/ "
  fi
  echo "$filename$znak$permisions"
done