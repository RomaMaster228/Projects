#!/usr/bin/env bash

DIR="."
CNT=0
USAGE="USAGE: $0 [--help] [-d DIR]"
LIST="$(mktemp)"
trap 'rm "$LIST"' EXIT

#error message
function die(){
      echo "$1" > /dev/stderr
      exit 1
}

function counter(){
      local IFS=$' '
      local TEMP="$(ls -l "$DIR" | grep -e '^...x' | grep -v '^d' | wc -l)"
      CNT=$((CNT+TEMP))
      DIRCNT="$(ls -l "$DIR" | grep -e '^d' | wc -l)"
      if [[ "$DIRCNT" != 0 ]];then
           ls -l "$DIR" | grep '^d' | cut -f2,2 -d ":" | sed 's/[0-9] /:/g' | cut -f2,2 -d ":" > "$LIST"
           cd "$DIR"
           IFS=$'\n'
           for word in $(< "$LIST")
           do
                 if [[ -r "$word" ]];then
                       DIR="$word"
                       counter "DIR"
                 fi
           done
           cd ..
      fi
}

while (( $# > 0 ));do
      CUR="$1"
      if [[ "$CUR" == "-d" ]];then
           shift
           DIR="$1"
      elif [[ "$CUR" == "--help" ]];then
           die "$USAGE"
      else
           die "$USAGE"
      fi
      shift
done

CHECK="$(file "$DIR" | cut -f3,3 -d " " | grep -w "open" | wc -w)"
if [[ "$CHECK" != 0 ]];then
      die "Directory $DIR does not exist"
else
      if [[ -r "$DIR" ]];then
           counter "DIR"
      fi
      echo "$CNT"
fi