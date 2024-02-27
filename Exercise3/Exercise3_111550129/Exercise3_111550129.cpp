#include<iostream>
#include<stdio.h>

using namespace std;

int profit[1000][1000];
int sum[1000][1000];
int score[10000];
int dp(int days, int a, int b){
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


int main() {
    int sets, a, b, queries;
    cin >> sets;  // Number of profit tables

    while (sets--) {
        cin >> a >> b;  // Dimensions of the profit table

        // Read profit table
        for (int i = 1; i <= a; ++i) {
            for (int j = 1; j <= b; ++j) {
                cin >> profit[i][j];
            }
        }

        cin >> queries;  // Number of days of study queries
        int days;
        for (int i = 0; i < queries; ++i) {
            cin >> days;
            int ans = dp(days, a, b);
            cout << ans << endl;
        }
    }

    return 0;
}
