/* Dejwo to ziomal ®© */

#include <bits/stdc++.h>
using namespace std;

void Zadanie1()
{
    cout << "Zadanie 1: \n";
    cout << numeric_limits<long long int>::max() << "\n";
    cout << numeric_limits<long long int>::min() << "\n";
    cout << numeric_limits<long long int>::digits10 << "\n";
    cout << numeric_limits<long long int>::digits << "\n\n";
}

void Zadanie2()
{
    cout << "Zadanie 2: \n";
    cout << "Min double: " << numeric_limits<double>::min() << "\n";
    cout << "Max negative double: " << -numeric_limits<double>::min() << "\n";

    cout << "Max double: " << numeric_limits<double>::max() << "\n";
    cout << "1 - Min double: " << (double)1 - numeric_limits<double>::min() << "\n";

    cout << "Min float: " << numeric_limits<float>::min() << "\n";
    cout << "Max positive float: " << numeric_limits<float>::lowest() << "\n";

    cout << "Max float: " <<numeric_limits<float>::max() << "\n";
    cout << "1 - Min double: " << (float)1 - numeric_limits<float>::min() << "\n\n";
}

void Zadanie3()
{
    cout << "Zadanie 3: \n";
    typedef ratio<1, 1> first; 
    typedef ratio_add<first, ratio<1, 2>> second; 
    typedef ratio_add<second, ratio<1, 3>> third;
    typedef ratio_add<third, ratio<1, 4>> fourth; 
    typedef ratio_add<third, ratio<1, 5>> fifth; 
    cout << first::num << " / " << first::den << "\n";
    cout << second::num << " / " << second::den << "\n";
    cout << third::num << " / " << third::den << "\n";
    cout << fourth::num << " / " << fourth::den << "\n";
    cout << fifth::num << " / " << fifth::den << "\n";
}

void square(vector <vector<double>> &M) 
{ 
    int N = (int)M.size();
    vector < vector < double >  > ans(N, vector< double >(N, 0));
    for (int i = 0; i < N; i++) 
    { 
        for (int j = 0; j < N; j++) 
        { 
            for (int k = 0; k < N; k++) 
                ans[ i ][ j ] += M[ i ][ k ] *  M[ k ][ j ]; 
        } 
    }
    M = ans;
}

void fill_random(vector <vector<double>> &M)
{
    srand(time(NULL));
    int N = (int)M.size();
    for(int i = 0; i < N; i ++)
    {
        for(int j = 0; j < N; j ++)
        {
            M[ i ][ j ] = rand() % 16 + 5;
            M[ i ][ j ] /= 10;
         //   cout << M[ i ][ j ] << " ";
        }
       // cout << endl;
    }
}
void Zadanie5()
{
    int n1 = 10, n2 = 100, n3 = 1000, n4 = 10000;
    vector < vector < double > > M1(n1, vector<double>(n1));
    vector < vector < double > > M2(n2, vector<double>(n2));
    vector < vector < double > > M3(n3, vector<double>(n3));
   // vector < vector < double > > M4(n4, vector<double>(n4));

    fill_random(M1);
    fill_random(M2);
    fill_random(M3);
    //fill_random(M4);

    using namespace std::chrono;

    cout << "Square 10x10 \n";
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    square(M1);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    cout << "Time " << time_span.count() << " seconds.\n\n";

    cout << "Square 100x100 \n";
    t1 = high_resolution_clock::now();
    square(M2);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    cout << "Time " << time_span.count() << " seconds.\n\n";

    cout << "Square 1000x1000 \n";
    t1 = high_resolution_clock::now();
    square(M3);
    t2 = high_resolution_clock::now();
    time_span = duration_cast<duration<double>>(t2 - t1);
    cout << "Time " << time_span.count() << " seconds.\n";

    // cout << "Square 10000x10000 \n";
    // M4 = square(M4);

    chrono::duration<double> sum_of_times(0);
    int no = 50;
    for(int i = 0; i < no; i++){
        auto start = chrono::high_resolution_clock::now();
        auto M5 = M1;
        square(M5);
        auto end = chrono::high_resolution_clock::now();
        sum_of_times += chrono::duration_cast<chrono::duration<double>>(end - start);
    }
    cout << "Time after: " << no << " " << sum_of_times.count() / no << endl;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Zadanie1();
    Zadanie2();
    Zadanie3();
    Zadanie5();
    return 0;
}
