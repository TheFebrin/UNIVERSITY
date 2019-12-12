#include <bits/stdc++.h>

using namespace std;

complex<long double> Euler_gamma(complex<long double> z, int n)
{
    complex <long double> ans(1.0, 0);
    for(long double i = 1; i <= n; i ++)
    {
        complex <long double> num = pow(1 + 1.0 / i, z);
        complex <long double> den = (long double)1 + z / i;
        complex <long double> frac = num / den;
        ans *= frac;
    }
    return ans / z;
}
complex<long double> Euler_gamma_inv(complex<long double> z, int n)
{
    complex <long double> ans(1.0, 0); 
    for(long double i = 1; i <= n; i ++)
    {   
        complex <long double > prod = ((long double)1 + z / i) / exp(z / i);
        ans *= prod;
    }
    long double lambda = 0.5772156649;
    ans *= z * exp(lambda * z);
    return ans;
}


complex<long double> Riemann_zeta(complex <long double> z, int n)
{
   complex <long double> ans(0, 0);  
   for(long double i = 1; i <= n; i ++)
   {
       complex<long double> jeden(1, 0);
       ans += jeden / pow(i, z);
   }
   return ans;
}

complex <long double> Riemann_alaytic(complex<long double> z, int n)
{
    complex<long double> ans(0, 0);
    for (long double i = 1; i <= n; i ++)
    {
        ans += pow(-1.0, i + 1.0) / pow(i, z);
    }
    return ans / ((long double)1 - (long double)2 / pow(2.0, z));
}



int main()
{
    complex <long double> z1(3, 2);
    cout << z1 << endl;
    auto eg = Euler_gamma(z1, 10000);
    cout << eg << endl;
    auto egi = Euler_gamma_inv(z1, 1000);
    cout << egi << endl;
    cout << egi * eg << endl;

    complex <long double> z2(2, 0);
    cout << Riemann_zeta(z2, 10000) << endl;
    cout << Riemann_alaytic(z2, 10000) << endl;


    fstream f;
    f.open("data.txt", ios::out);
    for(int i = 0; i < 10000; i ++)
    {
        complex<long double > c(0.5, i);
        auto val = Riemann_alaytic(c, 1000);
        f << val << "\n";
    }
    f.close();
    
    return 0;
}