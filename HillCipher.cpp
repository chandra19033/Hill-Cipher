/*
Nama     : Chandra Wijaya (140810190033)
           Adam Din Naufan (140810190045)
Kelas    : A
Program  : Hill Cipher
*/
 
#include <algorithm>
#include<iostream>
#include<vector>
using namespace std;
 
int modInverse(int a, int m){ 
    a=a%m; 
    for(int x=-m;x<m;x++) 
       if((a*x)%m==1) 
          return x; 
} 
void getCofactor(vector<vector<int> > &a, vector<vector<int> > &temp, int p, int q, int n){ 
    int i=0,j=0; 
    for(int row=0;row<n;row++){ 
        for(int col=0;col<n;col++){ 
            if(row!=p&&col!=q){ 
                temp[i][j++] = a[row][col]; 
                if (j==n-1){ 
                    j=0; 
                    i++; 
                } 
            } 
        } 
    } 
}
int determinant(vector<vector<int> > &a, int n, int N){ 
    int D = 0;
    if(n==1) 
        return a[0][0]; 
    vector<vector<int> > temp(N, vector<int>(N));
    int sign = 1;
    for(int f=0;f<n;f++){ 
        getCofactor(a, temp, 0, f, n); 
        D += sign * a[0][f] * determinant(temp, n - 1, N); 
        sign = -sign; 
    }
    return D; 
} 
void adjoint(vector<vector<int> > &a,vector<vector<int> > &adj,int N){ 
    if(N == 1){ 
        adj[0][0] = 1; 
        return; 
    } 
    int sign = 1;
    vector<vector<int> > temp(N, vector<int>(N));
    for(int i=0;i<N;i++){ 
        for(int j=0;j<N;j++){ 
            getCofactor(a, temp, i, j, N); 
            sign = ((i+j)%2==0)? 1: -1; 
            adj[j][i] = (sign)*(determinant(temp, N-1 , N)); 
        } 
    } 
} 
bool inverse(vector<vector<int> > &a, vector<vector<int> > &inv, int N){ 
    int det = determinant(a, N, N); 
    if(det == 0){ 
        cout << "Tidak Memiliki Invers"; 
        return false; 
    } 
    int invDet = modInverse(det,26);
    cout<<det%26<<' '<<invDet<<'\n';
    vector<vector<int> > adj(N, vector<int>(N));
    adjoint(a, adj, N);  
    for(int i=0;i<N;i++) 
        for(int j=0;j<N;j++) 
            inv[i][j] = (adj[i][j]*invDet)%26; 
    return true; 
} 
 
bool findKey(string plaintext, string ciphertext, vector<vector<int>> &K,
             int N) {

  int i, j;

  if (plaintext.size() != ciphertext.size()) {
    cout << "Jumlah huruf plaintext dan ciphertext tidak sama\n";
    return false;
  }

  if (plaintext.size() % N != 0 || N < 2) {
    cout << "Ukuran matriks kunci tidak sesuai\n";
    return false;
  }

  vector<vector<int>> P, C, inversP;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      P[i][j] = plaintext[i * N + j] - 97;
      C[i][j] = ciphertext[i * N + j] - 97;
    }
  }
  if (!inverse(P, inversP, N)) {
    cout << "Matriks key tidak dapat ditemukan\n";
    return false;
  }
  return false;
}
 
 
int main() {
start:
	string s, d;
  char loop = 'n';
  string ans = "";
  int x, y, i, j, k, n, pilih;
  vector<vector<int>> a(10, vector<int>(10));
  vector<vector<int>> adj(10, vector<int>(10));
  vector<vector<int>> inv(10, vector<int>(10));
  vector<vector<int>> key;

    cout<<"===========================\n";
    cout<<"----Program Hill Cipher----\n";
    cout<<"===========================\n";
    cout<<"1.Mengenkripsi\n";
    cout<<"2.Mendeskripsi\n";
    cout<<"3.Mencari Kunci\n";
    cout<<"===========================\n";
    cout<<"Pilihan : ";
    cin>>pilih; 
    if(pilih == 1){
        
    cout<<"Masukan Ukuran Kunci Matrix : ";
    cin>>n;
    cout<<"Masukan Kunci Matrix : \n";
    int a[n][n];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    cout<<"Masukan Huruf/Kalimat : ";
    string s;
    cin>>s;
    int temp = (n-s.size()%n)%n;
    for(i=0;i<temp;i++){
        s+='x';
    }
    k=0;
    string ans="";
    while(k<s.size()){
        for(i=0;i<n;i++){
            int sum = 0;
            int temp = k;
            for(j=0;j<n;j++){
                sum += (a[i][j]%26*(s[temp++]-'a')%26)%26;
                sum = sum%26;
            }
            ans+=(sum+'a');
        }
        k+=n;
    }
    cout<<"===========================\n";
    cout<<"Hasil Enkripsi : "<<ans<<'\n';
    } 
    
    if(pilih==2){
    
    cout<<"Masukan Ukuran Kunci Matrix : ";
    cin>>n;
    cout<<"Masukan Kunci Matrix : \n";
    vector<vector<int> > a(n, vector<int>(n));
    vector<vector<int> > adj(n, vector<int>(n));
    vector<vector<int> > inv(n, vector<int>(n));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            cin>>a[i][j];
        }
    }
    if(inverse(a,inv,n)){
        cout<<"Terdapat Invers\n";
    }
    cout<<"Masukan Huruf/Kalimat : \n";
    string s;
    cin>>s;
    k=0;
    string ans;
    while(k<s.size()){
        for(i=0;i<n;i++){
            int sum = 0;
            int temp = k;
            for(j=0;j<n;j++){
                sum += ((inv[i][j] + 26)%26*(s[temp++]-'a')%26)%26;
                sum = sum%26;
            }
            ans+=(sum+'a');
        }
        k+=n;
    }

    int f=ans.size()-1;
    while(ans[f]=='x'){
        f--;
    }
    for(i=0;i<=f;i++){
        cout<<"Hasil Deskripsi : "<<ans[i];
    }
    cout<<'\n';     
    }
    
	if(pilih==3){
	    cout << "Plainteks : ";
    cin >> s;

    cout << "Cipherteks : ";
    cin >> d;

    cout << "Ukuran matriks kunci : ";
    cin >> n;

    cout << "Matriks kuncinya : \n" << findKey(s, d, key, n);
	  	}
    string ulang;
  cout << "\nApakah ingin diulang ? (Y/N) ";
  cin >> ulang;
  if (ulang == "Y" || ulang == "y") {
    goto start;
  } else {
    return 0;
  }
}


