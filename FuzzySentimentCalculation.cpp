#include<iostream>
#include<stdio.h>
#include<algorithm>
#include <string>
#include<string.h>
#include<ctime>
#include<math.h>
#include <fstream>
#include <sstream>
using namespace std;

int main(int argc, char **argv)
{
	string phrase,word,lexiconLine,temp;
	stringstream ss,lexiconss;
	ifstream phraseFile("finalextracted");
	ofstream QualityFactor("FuzzyQualityScore.txt",ios::app);
	int foundWord,phraseWordCount=0,SentimentCount=0;
	float fuzzyPhraseValues [5];
	float fuzzyVal,fuzzySum=0.0,x,y,z,PhraseFuzzyVal;
	while(phraseFile.good())
	{
		getline(phraseFile,phrase);
		//cout<<phrase<<"\t";
		SentimentCount++;	
		ss<<phrase;
		phraseWordCount=0;
		while(getline(ss,word,' '))
		{
			std::transform(word.begin(), word.end(), word.begin(), ::tolower);			
			//cout<<word<<endl;
			ifstream lexicon("LexiconFuzzy.txt");
			while(lexicon.good())
			{
				getline(lexicon,lexiconLine);
				foundWord=lexiconLine.find(word);
				//cout<<foundWord;
				if(foundWord==0 && word.compare("")!=0)
				{
				
					
					lexiconss<<lexiconLine;				
					getline(lexiconss,temp,'\t');
					getline(lexiconss,temp,'\t');					
					//cout<<endl<<word<<" ";
					fuzzyVal=::atof(temp.c_str());				
					//cout<<"\n"<<word<<"  "<<fuzzyVal;
					fuzzyPhraseValues[phraseWordCount++]=fuzzyVal;
					lexiconss.clear();
					break;
				}
						
			}
			lexicon.close();
				
		}
// z=y^(1-x) y>0.5
//z=y^(1+x) y<0.5
		PhraseFuzzyVal=0;
		ss.clear();
		if(phraseWordCount==1)
		{
			fuzzySum+=PhraseFuzzyVal=fuzzyPhraseValues[0];
		}
		else if(phraseWordCount==2)
		{
			y=fuzzyPhraseValues[1];
			x=fuzzyPhraseValues[0];
			if(x>2)
			{
				fuzzySum+=PhraseFuzzyVal=1-y;
			}
			else if (x<1 && y>0.5)
			{
				fuzzySum+=PhraseFuzzyVal=pow(y,(1-x));
			}
			else 
			{
				
				fuzzySum+=PhraseFuzzyVal=pow(y,(1+x));
			}
		}
		else if (phraseWordCount==3)
		{
			z=fuzzyPhraseValues[2];	
			y=fuzzyPhraseValues[1];
			x=fuzzyPhraseValues[0];
			if(x>1)
			{
				if(z>0.5)
				{
					fuzzySum+=PhraseFuzzyVal=1-pow(z,(1-y));
				}
				else
				{
					fuzzySum+=PhraseFuzzyVal=1-pow(z,(1+y));
				}
			}
			else
			{
				if(y>0.5)
				{
					x=pow(y,(1-x));
				}
				else if(x<1 && y <=0.5)
				{
					
					x=pow(y,(1+x));
				}
				y=fuzzyPhraseValues[2];
				if(y>0.5)
				{
					fuzzySum+=PhraseFuzzyVal=pow(y,(1-x));
				}
				else
				{
					
					fuzzySum+=PhraseFuzzyVal=pow(y,(1+x));
				}
			}		
			
		}
		if(PhraseFuzzyVal==0)
		{
			SentimentCount--;
		}
		/*else
		{
			cout<<PhraseFuzzyVal<<endl;
		}*/
	}
	phraseFile.close();
	float finalVal;
	finalVal=fuzzySum/SentimentCount;
	cout<<finalVal;
	QualityFactor<<finalVal<<"\n";
	QualityFactor.close();
	return 0;
}
