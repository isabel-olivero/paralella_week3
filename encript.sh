#!/bin/bash

# Uso: ./caesar.sh [-d] <rotacion> <texto...>

decrypt=false
if [[ "$1" == "-d" ]]; then
    decrypt=true
    shift
fi

if [[ $# -lt 2 ]]; then
    echo "Uso: $0 [-d] <rotacion> <texto...>"
    exit 1
fi

shiftval=$1
shift
text="$*"

# normalizar shift entre 0-25
shiftval=$(( (shiftval % 26 + 26) % 26 ))
if $decrypt; then
    shiftval=$(( (26 - shiftval) % 26 ))
fi

result=""

for (( i=0; i<${#text}; i++ )); do
    c="${text:$i:1}"
    ascii=$(printf "%d" "'$c")

    if [[ $ascii -ge 65 && $ascii -le 90 ]]; then
        # Mayúscula A-Z
        base=65
        new=$(( (ascii - base + shiftval) % 26 + base ))
        result+=$(printf "\\$(printf '%03o' "$new")")
    elif [[ $ascii -ge 97 && $ascii -le 122 ]]; then
        # Minúscula a-z
        base=97
        new=$(( (ascii - base + shiftval) % 26 + base ))
        result+=$(printf "\\$(printf '%03o' "$new")")
    else
        # Otros caracteres sin cambio
        result+="$c"
    fi
done

echo "$result"
