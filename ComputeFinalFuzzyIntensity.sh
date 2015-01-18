#!/bin/sh
# z=y^(1-x) y>0.5
#z=y^(1+x) y<0.5
while read line;
do 
	echo $line > tempLine	
	noOfValues=`cut -f1 -d " " tempLine`

	if [ $noOfValues = 1 ]
	then
		Value1=`cut -f2 -d " " tempLine`
		echo "Hello"		
		echo "$Value1 $Value1 $Value1"
		#printf "$Value1\t" >> FinalFuzzyValues
	fi
	if [ $noOfValues = 2 ]
	then
		Value1=`cut -f2 -d " " tempLine`
		Value2=`cut -f3 -d " " tempLine`
		if [ $Value2 -gt 0.5 ]
		then
			tempx=`echo "1 - $Value1" | bc `			
			Result=`echo "e(($tempx*l($Value2))" | bc -l`   #x^y
		else
			tempx=`echo "1 + $Value1"|bc`			
			Result=`echo "e(($tempx*l($Value2))" | bc -l`
		fi
		printf "$Result\n" >> FinalFuzzyValues
		
	fi
	if [ $noOfValues = 3 ]
	then
		Value1= `cut -f2 -d " " tempLine`
		Value2= `cut -f3 -d " " tempLine`
		Value3= `cut -f4 -d " " tempLine`
		
		if [ $Value2 -gt 0.5 ]
		then
			tempx=`echo "1 - $Value1"|bc`			
			Result=`echo "e(($tempx*l($Value2))" | bc -l`   #x^y
		else
			tempx=`echo "1 + $Value1"|bc`			
			Result=`echo "e(($tempx*l($Value2))" | bc -l`
		fi
		
		if [ $Value3 -gt 0.5 ]
		then
			tempx=`echo "1 - $Result"|bc`			
			Result=`echo "e(($tempx*l($Value3))" | bc -l`   #x^y
		else
			tempx=`echo "1 + $Result"|bc`			
			Result=`echo "e(($tempx*l($Value3))" | bc -l`
		fi
		printf "$Result\n" >> FinalFuzzyValues
	fi 
done < $1
#rm tempLine
