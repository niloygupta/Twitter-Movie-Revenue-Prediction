#!/bin/sh


for arg
do
	echo $arg
	grep -o "[a-zA-Z]*_JJ" $arg>>tempSeeds
	grep -o "[a-zA-Z]*_RB[R]*[S]*" $arg >>tempSeeds
	grep -o "[a-zA-Z]*_VB[ND]" $arg >>tempSeeds
done

sed 's/_[A-Z][A-Z][A-Z]*//g' <tempSeeds > lexiconSeedWords

