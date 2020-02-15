#!/bin/bash

#Year, Date, Time, km
while [[ $# -gt 1 ]]
 do
 key="$1"
 
 case $key in
   -Y)
   YEAR="$2" # YYYY
   shift
   ;;
   -T)
   TIME="$2" # HHMM
   shift
   ;;
   -D)
   DATE="$2" # MMDD
   shift
   ;;
   -K)
   KM="$2"
   shift
   ;;
   *)
   ;;
 esac
 shift
 done

 DATE=`date -j ${DATE}${TIME}${YEAR} +%s`

 echo "$DATE $KM" >> walks_log_${YEAR}.txt
