#!/bin/sh

# z=y^(1-x) y>0.5
#z=y^(1+x) y<0.5

rm tempFuzzy
touch tempFuzzy

cp $1 tempTaggedFile

grep -o "[a-zA-Z]*_JJ [a-zA-Z]*_JJ [a-zA-Z]*_NN[S]*" tempTaggedFile >patternoutput
sed 's/[a-zA-Z]*_JJ [a-zA-Z]*_JJ [a-zA-Z]*_NN[S]*//g' tempTaggedFile >temp1
cp temp1 tempTaggedFile

grep -o "[a-zA-Z]*_JJ [a-zA-Z]*_NN[S]*" tempTaggedFile >>patternoutput
sed 's/[a-zA-Z]*_JJ [a-zA-Z]*_NN[S]*//g' tempTaggedFile >temp1
cp temp1 tempTaggedFile


grep -o "[a-zA-Z]*_RB[R]*[S]* [a-zA-Z]*_RB[S]*[R]* [a-zA-Z]*_NN[S]*" tempTaggedFile >>patternoutput 
sed 's/[a-zA-Z]*_RB[R]*[S]* [a-zA-Z]*_RB[S]*[R]* [a-zA-Z]*_NN[S]*//g' tempTaggedFile >temp1
cp temp1 tempTaggedFile


grep -o "[a-zA-Z]*_RB[R]*[S]* [a-zA-Z]*_JJ [a-zA-Z]*_NN[S]*" tempTaggedFile >>patternoutput
sed 's/[a-zA-Z]*_RB[R]*[S]* [a-zA-Z]*_JJ [a-zA-Z]*_NN[S]*//g' tempTaggedFile >temp1
cp temp1 tempTaggedFile


grep -o "[a-zA-Z]*_RB[R]*[S]* [a-zA-Z]*_VB[ND]" tempTaggedFile >>patternoutput
sed 's/ [a-zA-Z]*_JJ [a-zA-Z]*_JJ [a-zA-Z]*_NN[S]*//g' tempTaggedFile >temp1
cp temp1 tempTaggedFile


grep -o "[a-zA-Z]*_VB[ND] [a-zA-Z]*_NN[S]*" tempTaggedFile >>patternoutput
sed 's/[a-zA-Z]*_VB[ND] [a-zA-Z]*_NN[S]*//g' tempTaggedFile >temp1
cp temp1 tempTaggedFile



sed 's/_[A-Z][A-Z][A-Z]*//g' <patternoutput > finalextracted

#./computeFinalFuzzyIntensity.sh tempFuzzy
#rm tempFuzzy
#sed 's/\n//g' tempFuzzy
#tr -d '\n' < tempFuzzy
g++ FuzzySentimentCalculation.cpp -o FuzzySentimentCalculation
./FuzzySentimentCalculation
rm temp1
printf "\n"






