#!/bin/bash
sort lexiconSeedWords | uniq -i  > tempWordOcc

while read line; 
do
WordCount=`grep  -c -i "$line" lexiconSeedWords`
echo -ne "$WordCount	" >>temptest 
echo  "$line" >> temptest
done < tempWordOcc

sort temptest > WordCountList
rm temptest
rm tempWordOcc
