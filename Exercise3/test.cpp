#include<iostream>
#include<stdio.h>
#include<string>
#include<cstring>
#include<fstream>
using namespace std;

int profit[1000][1000];
int sum[1000][1000];
int score[10000];
 
int calculate(int days, int a, int b){
	for(int i=0;i<10000;i++){
		score[i]=0;
	}
	
	//has b rows(ways) 
	for(int i=1;i<=a;i++){
		score[i]=profit[i][1];
	}
	
	//calculate course 2 to a
	for(int i=2;i<=b;i++){
		
		//calculate sum between before courses and current course 
		for(int j=1;j<=days;j++){ 
			for(int k=1;k<=a;k++){
				if(score[j]!=0){
					if(j+k<=days){
						sum[j][k]=score[j]+profit[k][i];
					}
				}
			}
		}
		
		for(int j=1;j<=days;j++){
			for(int k=1;k<=days;k++){
				if(sum[j][k]!=0){
					if(score[j+k]<sum[j][k]){
						score[j+k]=sum[j][k];
					}
				}
			}
		}
		score[i-1]=0;

		for(int j=0;j<1000;j++){
	        for(int k=0;k<1000;k++){
	            sum[j][k]=0;
	        }
	    }
	    
	}
	
	return score[days];
	
}

int main(void){
	
	// fstream infile;
	bool end = false;
	char c;
	int num=0;
	int temp1=0;
	int temp2=0;
	int temp2_1=0;
	int k=0;
	int days[1000]={0};
	int ans;
	//write
	/*fstream file;
	file.open("output.txt", ios::out);
	if(file.fail()){
		cout<<"The file can not open!"<<endl;
	}*/

	//read
	infile.open("input.txt", ios::in);
	if(!infile){
		cout<<"The file can not open!"<<endl;
	}else{
		while(!infile.eof()){
			
			
				int m=1;                                     //course
				int n=1;                                     //ways
				int a,b;
				k=0;
				
				memset(days,0,sizeof(days));
				for(int i=0;i<1000;i++){
			        for(int j=0;j<1000;j++){
			            profit[i][j]=0;
			        }
			    }
				//read profit_table	
				if(temp1!=0){
				profit[1][1]=temp1;
				n++;
				temp1=0;
				}
				if(temp2!=0){
					profit[1][1]=temp2_1;
					m++;
					temp2_1=0;
					num=temp2;
					temp2=0;
				}			
				while(infile.get(c)){
					if(infile.fail()){
						break;
					}
					
					if(c=='\n'||c=='\r'){
						if(c=='\r'){
	                        infile.get(c);
	                    }
	                    profit[m][n]=num;
	                    num=0;
	                    m++;
						b=n;
						n=1;   
						                    
						infile.get(c);
						if(infile.fail()){
							break;
						}	
						//two '\n' indicate profit_table ends				
						if(c=='\n'||c=='\r'){
							if(c=='\r'){
								infile.get(c);                        
							}
	                        break;
	                    }else{
	                    	num=num*10+(c-'0');
						}
						
					}
					else if(c==' '){					
						profit[m][n]=num;
						n++;										
						num=0;					
					}
					else{
						num=num*10+(c-'0');
					}
				}
				a=m-1;
				
				//cout<<"a"<<a<<"b"<<b<<endl;
				/*for(int i=1;i<=a;i++){
					for(int j=1;j<=b;j++){
						cout<<profit[i][j]<<" ";
					}
					cout<<endl;
				}*/
				
				//read days
				while(infile.get(c)){
					if(infile.fail()){
						days[k]=num;
	                    num=0;
	                    k++;
	                    end=true;
						break;
					}
					
					if(c=='\n'||c=='\r'){
						if(c=='\r'){
	                        infile.get(c);
	                    }	
	                    temp2_1=num;
	                    infile.get(c);
						if(infile.fail()){
							days[k]=num;
	                        num=0;
	                        k++;
	                        end=true;
							break;
						}	
						//two '\n' indicate days				
						if(c=='\n'||c=='\r'){
							if(c=='\r'){
								infile.get(c);                        
							}
	                        days[k]=num;
	                        num=0;
	                        k++;
	                    }else{
	                    	temp2=c-'0';
	                    	break;
						}
					}
					else if(c==' '){
						temp1=num;
						num=0;
						break;
					}
					else{
						num=num*10+(c-'0');
					}
				}
				
				/*for(int i=0;i<k;i++){
					cout<<days[i]<<" ";
				}
				cout<<endl;*/
				
				if(end){
					for(int i=0;i<k-1;i++){
						ans=calculate(days[i],a,b);
						cout<<ans<<endl;
					}
					ans=calculate(days[k-1],a,b);
					cout<<ans;
				}else{
					for(int i=0;i<k;i++){
						ans=calculate(days[i],a,b);
						cout<<ans<<endl;
					}
				}
				
					
			
						
		}
		infile.close();
		//file.close();
	}
}