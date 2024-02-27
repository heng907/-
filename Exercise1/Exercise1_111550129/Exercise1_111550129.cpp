#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<climits>


using namespace std;

fstream file,file2;
int tableau[20000][20000];

void insert(int m, int n, int temp)
{
    int row=m-1;
    int col=n-1;
    tableau[row][col]=temp;
    while(tableau[row][col]<tableau[row][col-1]||tableau[row][col]<tableau[row-1][col])
    {
        
        if(row==0||col==0)
        {
            break;
        }
        //x-u>x and x-u>=x-l
        if(tableau[row-1][col]<tableau[row][col-1])
        {
            swap(tableau[row][col],tableau[row][col-1]);
            col--;
        }
        //x-l>x and x-l>x-u
        else
        {
            swap(tableau[row][col],tableau[row-1][col]);
            row--;
        }
    }
    //when row=0
    if(row==0&&col!=0)
    {
        while(tableau[row][col-1]>tableau[row][col])
        {
            swap(tableau[row][col-1],tableau[row][col]);
            col--;
            if(col==0)
            {
                //reach to the [0][0]
                break;
            }
        }
    }
    //when col=0
    if(row!=0&&col==0)
    {
        while(tableau[row-1][col]>tableau[row][col])
        {
            swap(tableau[row-1][col],tableau[row][col]);
            row--;
            if(row==0)
            {
                break;
            }
        }
    }
}

int extractMin(int m, int n)
{
    int min=tableau[m][n];
    if(tableau[m+1][n]==INT_MAX&&tableau[m][n+1]==INT_MAX)
    {
        tableau[m][n]=INT_MAX;
        return min;
    }
    if(tableau[m+1][n]>tableau[m][n+1])
    {
        tableau[m][n]=tableau[m][n+1];
        tableau[m][n+1]=min;
        return extractMin(m,n+1);
    }
    else
    {
        tableau[m][n]=tableau[m+1][n];
        tableau[m+1][n]=min;
        return extractMin(m+1,n);
    }
}

void Clear(){
    for(int i=0;i<20000;++i){
        for(int j=0;j<20000;++j){
            tableau[i][j]=INT_MAX;
        }
    }
}

void print(int m, int n)
{
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(tableau[i][j]==INT_MAX)
            {
                file2<<"x ";
            }
            else
            {
                file2<<tableau[i][j]<<" ";
            }
        }
        file2<<endl;
    }
}

int main()
{
    file.open("input.txt",ios::in);
    file2.open("output.txt",ios::out);
    int num_tab;
    file>>num_tab;
    while(num_tab--)
    {
        Clear();
        int means;
        file>>means;
        stringstream ss;
        string s;
        if(means==1)
        {
            getline(file,s);  /*clean buffer*/
            getline(file,s);
            ss<<s;//take from ss
            int val;
            vector<int> temp;
            while(ss>>val)
            {
                temp.push_back(val);
            }
            file2<<"Insert ";
            for(int i=0;i<temp.size();++i)
            {
                file2<<temp[i]<<" ";
            }
            file2<<endl;
            ss.clear();
            s.clear();
            int m=0,n=0;
            char ch,pre_ch;
            while(1)
            {
                file.get(ch);
                if(ch>=48&&ch<=57)
                {
                    s+=ch;
                }
                if(ch=='x')
                {
                    n++;
                }
                if((ch==' '||ch=='\n')&&(pre_ch>=48&&pre_ch<=57))
                {
                    ss<<s;//write
                    ss>>val;//read 
                    temp.push_back(val);
                    s.clear();
                    ss.clear();
                    n++;
                }
                if(ch=='\n')
                {
                    m++;
                }
                if(ch=='\n'&&pre_ch=='\n')
                {
                    m--;
                    break;
                }
                pre_ch=ch;
            }
            n/=m;
            for(int i=0;i<temp.size();++i)
            {
                insert(m,n,temp[i]);
            }
            print(m,n);
            file2<<endl;
        }
        else
        {
            getline(file,s);
            vector<int> temp;
            int m=0,n=0;
            int val;
            char ch,pre_ch;
            while(1){
                file.get(ch);
                if(ch>=48&&ch<=57)
                {
                    s+=ch;
                }
                if(ch=='x')
                {
                    n++;
                }
                if((ch==' '||ch=='\n')&&(pre_ch>=48&&pre_ch<=57))
                {
                    ss<<s;
                    ss>>val;
                    temp.push_back(val);
                    s.clear();
                    ss.clear();
                    n++;
                }
                if(ch=='\n')
                {
                    m++;
                }
                if(ch=='\n'&&pre_ch=='\n')
                {
                    m--;
                    break;
                }
                pre_ch=ch;
            }
            n/=m;
            for(int i=0;i<temp.size();++i)
            {
                insert(m,n,temp[i]);
            }
            int e=extractMin(0,0);
            file2<<"Extract-min "<<e<<endl;
            print(m,n);
            file2<<endl;
        }
    }
    file.close();
    return 0;
}