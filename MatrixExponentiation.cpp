#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

#define MOD 1000000000


vector<ll>a;
vector<ll> b;
vector<ll> c;
ll k;

vector<vector<ll> > Multiply(vector<vector<ll> > M, vector<vector<ll> > N)
{
    // Creating an auxillary 2D vector to store the product of the 2 matrices
    vector<vector<ll>> C(k+1, vector<ll>(k+1));
    for(int i = 1; i<=k; i++)
    {
        for(int j = 1; j<=k; j++)
        {
            for(int x =1; x<=k; x++)
            {
                C[i][j] = (C[i][j] + (M[i][x]*N[x][i])%MOD)%MOD;
            }
        }
    }
    return C;
}

vector<vector<ll>> pow(vector<vector<ll>> A, ll p)
{
    // Using divide and conquer algorithm to compute the power
    if(p == 1)
        return A;
    //Checking if the power is odd
    if(p & 1)
        return Multiply(A, pow(A, p-1));
    else{
        vector<vector<ll> >X = pow(A, p/2);
        return Multiply(X, X);
    }
}
ll compute(ll n){
if(n == 0)
    return 0;
if(n<=k)
    return b[n-1];
//  Otherwise use matrix exponentiation
// Indexing from 1

//Step 1
vector<ll> F1(k+1);
for(ll i = 1; i< k+1; i++)
{
    F1[i] = b[i-1];
}

// Step 2 (Creating the transformation matrix)
vector<vector<ll>> T(k+1, vector<ll>(k+1));
for(int i = 1; i<=k; i++)
{
    for(int j = 1; j<=k; j++)
    {
        if(i <k)
        {
            if(j == i+1)
                T[i][j]=1;
            else{
                T[i][j] = 0;
            }
         continue;
        }
        T[i][j] = c[k-j];
    }
}
// Step3 Do the exponentiation of the matrix
T = pow(T, n-1);
ll result = 0;
for(int i =1; i<=k; i++)
{
    result = (result + (T[1][i]*F1[i])%MOD)%MOD;
}
return result % MOD;
}


int main(){
int t;
cin>>t;
while(t--){
    int n, no;
    //Contains the F1 vector
    for(int i = 0;  i< k; i++)
    {
        cin>>no;
        b.push_back(no);
    }
    //Init coefficient vector
    for(int i = 0; i<k; i++)
    {
        cin>>no;
        c.push_back(no);
    }
    cin>>n;
    cout<<compute(n)<<endl;
    b.clear();
    c.clear();
}
return 0;
}

