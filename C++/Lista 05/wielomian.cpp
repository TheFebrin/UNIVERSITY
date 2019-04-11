#include "wielomian.hpp"

wielomian::wielomian()
{
    this->n = 0;
    this->a = new double[1];
    this->a[0] = 1.0;
}

wielomian::wielomian(int n, double a[])
{
    this->n = n;
    this->a = a;
}

wielomian::wielomian(initializer_list <double> l)
{
    this->n = l.size() - 1;
    this->a = new double[ n + 1 ];
    int i = 0;
    for(auto el : l)
    {
        this->a[ i ] = el;
        i++;
    }
}

wielomian::wielomian(const wielomian &W)
{
    n = W.n;
    a = new double[ n + 1 ];
    for(int i = 0; i <= n; i ++)
    {
        this->a[ i ] = W.a[ i ];
    }
}

wielomian::wielomian(wielomian &&W): wielomian(W.n, W.a)
{
    W.a = nullptr;
}

wielomian &wielomian::operator= (const wielomian &W)
{
    if(this != &W)
    {
        n = W.n;
        delete [] a;
        a = new double[ n + 1 ];
        for(int i = 0; i <= n; i++)
            a[ i ] = W.a[ i ];
    }
    return *this;
}

wielomian &wielomian::operator=(wielomian &&W)
{
    if(this != & W)
    {
        delete[] a;
        a = W.a;
        n = W.n;
        W.a = nullptr;
    }
    return *this;
}

wielomian::~wielomian()
{
    delete[] a;
}

istream &operator >> (istream &in, wielomian &W)
{
    int n;
    in >> n;
    double *new_a = new double[ n + 1 ];

    for (int i = 0; i <= n; i ++)
    {
        in >> new_a[ i ];
    }

    delete[] W.a;
    W.a = new_a;
    W.n = n;
    return in;
}

ostream &operator << (ostream &out, wielomian &W)
{
    out << "Stopien: " << W.n << "  " << W.a[ 0 ];
    for(int i = 1; i <= W.n; i ++)
    {
        out << " + " << W.a[ i ] << " * x^" << i;
    }
    return out;
}

wielomian operator + (const wielomian &u1, const wielomian &v1)
{
    wielomian u = u1;
    wielomian v = v1;
    int n = max(u.n, v.n);
    double *a = new double[ n + 1 ];

    for(int i = 0; i <= n ; i++)
    {
        a[i] = u.a[i] + v.a[i];
    }

    while( n > 0 and a[ n ] == 0 )
    {
        n --;
    }

    return wielomian(n, a);
}

wielomian operator - (const wielomian &u1, const wielomian &v1)
{
    wielomian u = u1;
    wielomian v = v1;
    int n = max(u.n, v.n);
    double *a = new double[ n + 1 ];

    for(int i = 0; i <= n ; i++)
    {
        a[i] = u.a[i] - v.a[i];
    }

    while( n > 0 and a[ n ] == 0 )
    {
        n --;
    }

    return wielomian(n, a);
}

wielomian operator * (const wielomian &u, const wielomian &v)
{
    if( (u.n == 0 and u.a[ 0 ] == 0 ) or (v.n == 0 and v.a[ 0 ] == 0)) // wielomian 0
        return wielomian({0});

    int n = u.n + v.n;
    double *a = new double[ n + 1 ];
    for(int i = 0; i <= n; i++)
    {
        a[ i ] = 0;
    }

    for (int i = 0; i <= u.n; i++)
    {
        for(int j = 0; j <= v.n; j++)
        {
            a[i + j] += u.a[ i ] * v.a[ j ];
        }
    }
    return wielomian(n, a);
}

wielomian operator * (const wielomian &u, const double c)
{
    if(c == 0.0)
    {
        return wielomian({0});
    }
    else
    {
        int n = u.n;
        double *a = new double[n + 1];
        for (int i = 0; i <= n; i ++)
        {
            a[ i ]  = u.a[ i ] * c;
        }
        return wielomian(n, a);
    }

}

wielomian &wielomian::operator += (const wielomian &v)
{
    int new_n = max(n, v.n);
    double *new_a = new double[new_n + 1];

    for(int i = 0; i <= new_n; i ++ )
    {
        new_a[ i ] = this->a[ i ] + v.a[ i ];
    }

    while( new_n > 0 and new_a[ new_n ] == 0 )
    {
        new_n --;
    }

    delete[] a;
    this->n = new_n;
    this->a = new_a;
    return *this;
}

wielomian &wielomian::operator -= (const wielomian &v)
{
    int new_n = max(n, v.n);
    double *new_a = new double[new_n + 1];

    for(int i = 0; i <= new_n; i ++ )
    {
        new_a[ i ] = this->a[ i ] - v.a[ i ];
    }

    while( new_n > 0 and new_a[ new_n ] == 0 )
    {
        new_n --;
    }

    delete[] a;
    this->n = new_n;
    this->a = new_a;
    return *this;
}

wielomian &wielomian::operator *= (const wielomian &v)
{
    if( (this->n == 0 and this->a[ 0 ] == 0) or (v.n == 0 and v.a[ 0 ] == 0) )  // wielomian zerowy
    {
        this->n = 0;
        delete this->a;
        this->a = new double[ 1 ];
        this->a[ 0 ] = 0.0;
    }
    else
    {
        double *new_a = new double[ this->n + v.n + 1 ];
        for(int i = 0; i <= this->n + v.n; i ++)
        {
            new_a[ i ] = 0;
        }

        for (int i = 0; i <= v.n; i ++)
        {
            for(int j = 0; j <= this->n; j ++)
            {
                new_a[ i + j ] += v.a[ i ] * this->a[ j ];
            }
        }

        this->n += v.n;
        delete[] a;
        this->a = new_a;
    }
    return *this;
}

wielomian &wielomian::operator *= (const double c)
{
    if( c == 0 )
    {
        this->n = 0;
        double new_a[] = {0.0};
        delete[] this->a;
        this->a = new_a;
    }
    else
    {
        for(int i = 0; i <= this->n; i ++)
            a[ i ] *= c;
    }
    return *this;
}

double &wielomian::operator [] (int i) const
{
    return a[ i ];
}

double wielomian::operator () (double x) const
{
    double ans = 0.0;
    for (int i = n; i >= 0; i --) // Horner
        ans = ans * x + a[ i ];
    return ans;
}

int wielomian::wez_stopien()
{
    return n;
}
