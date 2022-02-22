#include <bits/stdc++.h>
#include <string>
using namespace std;
#define ll long long
#define ull unsigned long long
#define si(X) scanf("%d", &(X))
#define sll(X) scanf("%lld",&(X))
#define INFL 0x3f3f3f3f3f3f3f3fLL
const int mod = 1e9+7;
ll gcd(ll a,ll b){
    if(b==0)
    return a;return gcd(b,a%b);
}
ll expo(ll base,ll pow){
    ll ans = 1;
    while(pow!=0){
        if(pow&1==1){
            ans = ans*base;
            ans = ans%mod;
        }
        base *= base;base%=mod;
        pow/=2;
    }return ans;
}
ll inv(ll x){
    return expo(x,mod-2);
}
 
const int M = 2e5 + 5;
int pw[30];
struct Node{
    int numOfVectors;
    vector<int> basisVector;
};
Node merge(Node a, Node b){
    vector<int> v1 = a.basisVector;
    vector<int> v2 = b.basisVector;
 
    vector<int> totalNums;
    for(int i = 0 ; i < v1.size() ; i++){
        if(v1[i] != 0) totalNums.push_back(v1[i]);
    }
 
    for(int i = 0 ; i < v2.size() ; i++){
        if(v2[i] != 0) totalNums.push_back(v2[i]);
    }
 
    vector<int> mergedVector(26 , 0);
    int numOfVectors = 0;
 
    for(int i = 0 ; i < totalNums.size() ; i++){
        int num = totalNums[i];
        for(int j = 0 ; j < 26 ; j++){
            if(pw[j]&num){
                if(mergedVector[j] == 0){
                    mergedVector[j] = num;
                    numOfVectors++;
                    break;
                }
                else{
                    num = num^mergedVector[j];
                }
            }
        }
    }
    Node mergedNode;
    mergedNode.numOfVectors = numOfVectors;
    mergedNode.basisVector = mergedVector;
    return mergedNode;
}
 
Node segTree[4*M];
Node emptyNode;
Node arr[M];
 
int n;
vector<int> ansMasks;
 
int convToNum(string str){
    int num = 0;
    int strSz = str.size();
    for(int i = 0 ; i < strSz ; i++){
        int ch = (str[i] - 'a');
        num ^= (pw[ch]);
    }
    return num;
}
vector<int> createVector(int num){
    vector<int> vec(26 , 0);
    for(int i = 0 ; i < 26 ; i++){
        if(pw[i]&num){
            vec[i] = num;
            break;
        }
    }
    return vec;
}
void build(int node , int l , int r){
    if(l > r) return;
    if(l == r){
        segTree[node] = arr[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2*node , l , mid);
    build(2*node + 1 , mid + 1 , r);
    segTree[node] = merge(segTree[2*node], segTree[2*node + 1]);
}
 
Node query(int node , int l , int r , int ql , int qr){
    if(l > r || l > qr || r < ql) return emptyNode;
    if(l >= ql && r <= qr){
        return segTree[node];
    }
    int mid = (l + r) / 2;
    Node lef = query(2*node , l , mid , ql , qr);
    Node rig = query(2*node + 1 , mid + 1 , r , ql , qr);
 
    return merge(lef , rig);
}
 
void update(int node , int l , int r , int point , int val){
    if(l > r || l > point || r < point) return;
    if(l == r){
        segTree[node].numOfVectors = 1;
        segTree[node].basisVector = createVector(val);
        return;
    }
    int mid = (l + r) / 2;
    update(2*node , l , mid , point , val);
    update(2*node + 1 , mid + 1 , r , point , val);
 
    segTree[node] = merge(segTree[2*node], segTree[2*node + 1]);
}
 
ll calculateAns(Node node, int span){
    int numOfVectors = node.numOfVectors;
    vector<int> basis = node.basisVector;
    ll ans = 0;
 
    for(int i = 0 ; i < 27 ; i++){
        int num = ansMasks[i];
 
        // check representable or not
        bool representable = true;
 
        for(int j = 0 ; j < 26 ; j++){
            if(pw[j]&num){
                if(basis[j] == 0){
                    representable = false;
                    break;
                }
                num ^= basis[j];
            }
        }
        if(representable){
            ans = ans + expo(2 , span - numOfVectors);
            ans %= mod;
        }
 
    }
    return ans;
}
 
int main(){
 
    pw[0] = 1;
    for(int i = 1 ; i < 30 ; i++){
        pw[i] = pw[i - 1] * 2;
    }
 
    ansMasks.push_back(0);
    for(int i = 0 ; i < 26 ; i++){
        ansMasks.push_back(pw[i]);
    }
    int q;
    si(n);  si(q);
    emptyNode.numOfVectors = 0;
    emptyNode.basisVector = createVector(0);
 
    for(int i = 1 ; i <= n ; i++){
        string str;
        cin >> str;
        int num = convToNum(str);
 
        arr[i].numOfVectors = 1;
        arr[i].basisVector = createVector(num);
    }
 
    build(1 , 1 , n);
 
    while(q--){
        int typ;
        si(typ);
 
        if(typ == 1){
            int pos;
            string str;
            si(pos);
            cin >> str;
            update(1 , 1 , n , pos , convToNum(str));
        }
        else{
            int L, R;
            si(L);  si(R);
 
            Node result = query(1 , 1 , n , L , R);
 
            vector<int> here = result.basisVector;
            ll ans = calculateAns(result, R - L + 1);
            ans--;
            printf("%lld\n" , ans);
        }
 
    }
 
}