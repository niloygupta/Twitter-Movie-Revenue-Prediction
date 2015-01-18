#!/bin/sh

count=1

while [ $count -le 15 ]
do
curl "http://search.twitter.com/search.json?q=%23$1&rpp=100&page=$count" >> $1.txt
count=`expr $count + 1`
done

tr ',' '\n' < $1.txt | grep "text" > $1Tweets
