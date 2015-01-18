#include<iostream>
#include<stdio.h>
#include<algorithm>
#include <string>
#include<string.h>
#include<ctime>
#include<math.h>
using namespace std;
int main(int argc, char *argv[])
{
	int TweetMatrix[1000][1000];//NxM Blog X Word
	int T=0,D=0;//Term and Document
	float P1[1000][5],P2[5][1000];
	
	string str,strtweet;	
	string::iterator p;	
	FILE *word,*tweet,*fop;
	char s[80],t[300];
	int i=0,j=0;
	word=fopen(argv[1],"r");
	tweet=fopen(argv[2],"r");
	if(word==NULL || tweet==NULL)
	{
		cout<<"Cannot open file";
		return 0;
	}	
	int count=0,z;	
	while( fgets (s,79,word)!=NULL)
	{
		str=s;
		str.erase(str.length()-1,1);
		//cout<<str;
		tweet=fopen(argv[2],"r");j=0;
		while(fgets(t,299,tweet)!=NULL)
		{
			strtweet=t;
			std::transform(strtweet.begin(), strtweet.end(), strtweet.begin(), ::tolower);	
			z=strtweet.find(str);count=0;
			while (z!=-1) 
			{
				z=strtweet.find(str,z+str.size());
				count++;
			}	
			if(count>0)
			{
				//cout<<count<<"  "<<str<<endl;		
			}
			TweetMatrix[i][j++]=count;
		}
		D=j;
		fclose(tweet);
		i++;
	}
	T=i;
	//Actual PLSA
	int K=3;//number of topics or hidden sentiments
	int term=0,doc=0;//term and document

	srand(time(NULL));//Initialization
	float normsum=0.0;
	for (i=0;i<T;i++)
	{
		normsum=0.0;
		for(j=0;j<K;j++)
		{
			P1[i][j]=(rand()%11)/10.0;
			normsum+=P1[i][j];
		}
		for(j=0;j<K;j++)
		{
			P1[i][j]=P1[i][j]/normsum;
		}
	}

	for (i=0;i<K;i++)
	{
		normsum=0.0;
		for(j=0;j<D;j++)
		{
			P2[i][j]=(rand()%11)/10.0;normsum+=P2[i][j];
		}
		for(j=0;j<D;j++)
		{
			P2[i][j]=P2[i][j]/normsum;
			//cout<<P2[i][j]<<" ";
		}
		//cout<<endl;
	}	

	
	
	//and now it begins
	float sum1=0.0,sum2=0.0,sum3=0.0;
	int flag=0;
	/*cout<<"D "<<D<<endl;
	cout<<"T "<<T<<endl;
	cout<<"K "<<K<<endl;*/
	for(doc=0;doc<D;doc++)
	{	
		for(term=0;term<T;term++)
		{
			for(int k=0;k<K;k++)
			{
				sum1=0.0;
				if(!isnan(P1[term][k]) && !isnan(P2[k][doc]))
				{
					/*cout<<"Term: "<<term;
					cout<<" k: "<<k;
					cout<<" Doc: "<<doc;cout<<endl;*/
				}
				for(int i=0;i<K;i++)
				{
					sum1+=(P1[term][i])*(P2[i][doc]);//cout<<P1[term][i]<<" "<<P2[i][doc];sleep(0.95);
				}
				//cout<<sum1;
				sum2=0.0;
				for(int i=0;i<D;i++)
				{
					sum2+=TweetMatrix[term][i]*P2[k][i];	
				}
				sum2=sum2/sum1;
				if(!isnan(P1[term][k]*sum2)&&!isinf(P1[term][k]*sum2))
				{
					
					P1[term][k]=P1[term][k]*sum2;

					sum3=0.0;
					for(int i=0;i<T;i++)
					{
						sum3+=P1[i][k];
					}
					if(!isnan(P1[term][k]/sum3)&&!isinf(P1[term][k]/sum3))
					{P1[term][k]=P1[term][k]/sum3;}
				}
				/*else
				{
					flag++;
				}*/
				sum2=0.0;
				for(int i=0;i<T;i++)
				{
					sum2+=TweetMatrix[i][doc]*P1[i][k];	
				}
				sum2=sum2/sum1;
				if(!isnan(P2[k][doc]*sum2)&&!isinf(P2[k][doc]*sum2))
				{
					P2[k][doc]=P2[k][doc]*sum2;
					sum3=0.0;
					for(int i=0;i<K;i++)
					{
						sum3+=P2[i][doc];
					}
					if(!isnan(P2[k][doc]/sum3)&& !isinf(P2[k][doc]/sum3))
					{P2[k][doc]=P2[k][doc]/sum3;}
				}
				/*else
				{
					flag++;
				}
				if(flag>=2)
				{
					//break;
				}*/	
			}
			/*if(flag>=2)
			{
				//break;
			}*/
		}
/*		if(flag>=2){//break;
}*/
	}
	float sum=0.0;
	fop=fopen(argv[3],"a+");
	if(fop==NULL)
	{
		cout<<"Cannot Open File";
	}
	
	for (i=0;i<K;i++)
	{
		sum=0.0;
		for(j=0;j<D;j++)
		{
			if(!isnan(P2[i][j])&&!isinf(P2[i][j]))
			{			
		//		cout<<P2[i][j]<<" ";
				sum+=P2[i][j];				
				//fprintf(fop,"%f \t", P2[i][j]);
			}
		}
		fprintf(fop,"%f \t", sum/D);
		//cout<<endl;
	}
	fprintf(fop,"\n");	
	fclose(fop);
	/*for (i=0;i<T;i++)
	{
		for(j=0;j<K;j++)
		{
			if(isnan(P1[i][j])||isinf(P1[i][j]))
			{			
				cout<<P1[i][j]<<" ";
			}
		}
		//cout<<endl;
	}*/
	
	/*for(int i=0;i<K;i++)
	{
		sum+=P2[i][54]*P1[54][i];cout<<P2[i][54]<<"  "<<P1[54][i]<<"  ";
		sum1+=P2[i][2]*P1[2][i];cout<<P2[i][2]<<"  "<<P1[2][i]<<"  ";
	}
	cout<<endl<<sum/K<<endl<<sum1/K<<endl<<(sum1-sum)/K<<endl;*/
	return 0;
}
