#!/bin/bash
#if [ -f tempphraseword ]
#then
#	rm tempphraseword
#	touch tempphraseword	
#fi

sed 's/_[A-Z][A-Z][A-Z]*//g' <$1 > tempExtract
while read line; 
do
	#check=`echo $line | grep -o -E '\w+' `
	echo $line > tempFILE
	grep -o -E '\w+' tempFILE >tempphraseword
	noOfWords=`wc -l tempphraseword |cut -f1 -d" "` 
	printf "$noOfWords" >> tempFuzzy	
	while read line1; 
	do
		check=`grep "$line1" LexiconFuzzy.txt`
		
		if [ $? -eq 0 ]
		then 
			#echo ""
			fuzzyIntensity=`grep -i "$line1" LexiconFuzzy.txt | cut -f2 -d  "	"|tr -d '\n'`
			if [ -n "$fuzzyIntensity" ]; then 
				printf "\t$fuzzyIntensity" >>tempFuzzy
			fi			
			#echo $fuzzyintensity >> tempFuzzy
			#grep "$line1" LexiconFuzzy.txt | cut -f2 -d "	"
		fi
	done < tempphraseword
	printf "\n" >> tempFuzzy
done < tempExtract
rm tempExtract
cat tempphraseword
#rm tempphraseword



