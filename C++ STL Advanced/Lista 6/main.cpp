#include <bits/stdc++.h>
using namespace std;


template <class T>
void parmutate(T data[], int N)
{
    default_random_engine dre;
    dre.seed(time(NULL));

    for (int i = 0; i < N; i++){
        uniform_int_distribution <int> uniform(i, N - 1);
        swap(data[i], data[uniform(dre)]);
    }
}
 
void generate_uniform(int n)
{
    default_random_engine dre;
    uniform_real_distribution<float> uniform;
    fstream file;
    file.open("uni.csv", ios::out);
    for (int i = 0; i < n; i++)
        file << uniform(dre) << "\n";
    file.close();
}
 
void generate_binomial(int n)
{
    default_random_engine dre;
    binomial_distribution<int> bd(1000, 0.5);
    fstream file;
    file.open("bin.csv", ios::out);
    for (int i = 0; i < n; i++)
        file << bd(dre) << "\n";
    file.close();
}
 
void generate_normal(int n)
{
    default_random_engine dre;
    normal_distribution<double> normal;
    ofstream file;
    file.open("norm.csv");
    for (int i = 0; i < n; i++)
        file << normal(dre) << "\n";
}

int main()
{
    srand(time(NULL));
    int n = 20;
    int arr[n];
    for (int i = 0; i < n; i++)
       arr[i] = i + 1;
    
    parmutate(arr, n);

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout<<endl;


    generate_uniform(1000);
    generate_binomial(1000);
    generate_normal(1000);

    return 0;
}