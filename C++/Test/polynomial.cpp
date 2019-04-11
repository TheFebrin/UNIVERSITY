#include "polynomial.hpp"

polynomial::polynomial()
{
    this->n = 0;
    this->a = new double[1];
    this->a[0] = 1.0;
}
polynomial::polynomial(int n, double a[]){
    this->n = n;
    this->a = a;

}
polynomial::polynomial(initializer_list<double> l){
    this->n = l.size()-1;
    this->a = new double[n+1];
    int i=0;
    for(auto el : l){
        this->a[i] = el;
        i++;
    }
}
polynomial::polynomial(const polynomial& p){
    n = p.n;
    a = new double[n+1];
    for(int i=0;i<=n;i++){
        this->a[i]=p.a[i];
    }
}
polynomial::polynomial(polynomial&& p):polynomial(p.n, p.a){
    p.a=nullptr;
}
polynomial& polynomial::operator= (const polynomial& p)
{
    if(this!=&p)
    {
        n=p.n;
        delete [] a;
        a=new double[n+1];
        for(int i=0; i<=n; i++)
            a[i]=p.a[i];
    }
    return *this;
}

polynomial& polynomial::operator=(polynomial &&p)
{
    if(this!=&p){
        delete[] a;
        a=p.a;
        n=p.n;
        p.a=nullptr;
    }
    return *this;
}

polynomial::~polynomial(){
    delete[] a;
}

istream& operator >> (istream &in, polynomial &p){
    int n;
    in >> n;
    double* new_a = new double[n+1];
    for (int i=0; i<=n;i++){
        in>>new_a[i];
    }
    delete[] p.a;
    p.a = new_a;
    p.n = n;
    return in;
}

ostream& operator << (ostream &out, polynomial &p){
    out <<"deg:"<< p.n << "  "<<p.a[0];
    for(int i=1; i<=p.n; i++){
        out <<" + "<< p.a[i] <<" *x^" << i;
    }
    return out;
}

polynomial operator + (const polynomial &u1,const polynomial &v1){
    polynomial u = u1;
    polynomial v = v1;
    int lower_deg = 0;
    int n = max(u.n, v.n);
    if(u.n==v.n)
        for(int i=u.n; u.a[i]==(-1)*v.a[i] && i > 0; i--){
            n -=1;
            lower_deg++;
            if(n==-1)
                n=0;
        }
    double* a = new double[n+1];
    if(u.n<v.n)
        swap(u,v);

    for(int i=0; i<=v.n-lower_deg; i++)
        {
            a[i] = u.a[i] + v.a[i];
            //cout << u.a[i] << " " << v.a[i] << endl;
        }

    for(int i=v.n+1; i<=u.n-lower_deg; i++)
        a[i] = u.a[i];

    return polynomial(n,a);
}

polynomial operator - (const polynomial &u1,const polynomial &v1){
    polynomial u = polynomial(u1);
    polynomial v = v1;
    int lower_deg = 0;
    int n = max(u.n, v.n);
    if(u.n==v.n)
        for(int i=u.n;u.a[i]==v.a[i]&&i>0;i--){
            n -=1;
            lower_deg++;
            if(n==-1)
                n=0;
        }

    double* a = new double[n+1];
    bool swaped = false;
    if(u.n<v.n){
        swap(u,v);
        swaped = true;
    }
    for(int i=0; i<=v.n-lower_deg; i++)
        a[i]=(u.a[i]-v.a[i]);
    for(int i=v.n+1;i<=u.n-lower_deg;i++)
        a[i]=u.a[i];
    if(swaped)
        for(int i=0; i<=n; i++)
            a[i]=a[i]*(-1.0);
    return polynomial(n,a);
}

polynomial operator * (const polynomial &u,const polynomial &v){
    if(u.n==0 && u.a[0]==0 || v.n==0 && v.a[0]==0)
        return polynomial({0});
    int n = u.n+v.n;
    double* a = new double[n+1];
    for(int i=0; i<=n; i++)
        a[i]=0;
    for (int i=0; i<=u.n; i++){
        for(int j=0; j<=v.n; j++){
            a[i+j]+=u.a[i]*v.a[j];
        }
    }
    return polynomial(n,a);
}

polynomial operator * (const polynomial&u, const double c){
    if(c==0.0){
        return polynomial({0});
    }
    else{
        int n = u.n;
        double* a = new double[n+1];
        for (int i=0; i<=n; i++){
            a[i] = u.a[i]*c;
        }
        return polynomial(n,a);
    }

}

polynomial& polynomial::operator += (const polynomial &v){
    int new_n = max(n, v.n);
    int lower_deg = 0;
    if(n == v.n)
        for(int i=n;a[i]==(-1)*v.a[i]&&i>0;i--){
        lower_deg ++;
        new_n -=1;
        if(new_n==-1)
            new_n = 0;
        }
    double* new_a = new double[new_n+1];
    if(this->n<v.n){
        for(int i=0; i<=this->n;i++){
            new_a[i] = this->a[i]+v.a[i];
        }
        for(int i=this->n+1; i<=v.n;i++)
            new_a[i]=v.a[i];
    }
    else{
        for(int i=0; i<=v.n-lower_deg; i++){
            new_a[i] = this->a[i]+v.a[i];
        }
        for(int i=v.n+1; i<=this->n-lower_deg;i++)
            new_a[i]=a[i];
    }
    delete[] a;
    this->n=new_n;
    this->a=new_a;
    return *this;
}

polynomial& polynomial::operator -= (const polynomial &v){
    int new_n = max(n, v.n);
    int lower_deg = 0;
    if(n == v.n)
        for(int i=n; a[i]==v.a[i]&&i>0;i--){
        lower_deg++;
        new_n -=1;
        if(new_n ==-1)
            new_n = 0;
    }
    double* new_a = new double[new_n+1];
    if(this->n<v.n){
        for(int i=0; i<=this->n;i++){
            new_a[i] = this->a[i]-v.a[i];
        }
        for(int i=this->n+1; i<=v.n;i++)
            new_a[i]=v.a[i]*(-1);
    }
    else{
        for(int i=0; i<=v.n-lower_deg; i++){
            new_a[i] = this->a[i]-v.a[i];
        }
        for(int i=v.n+1; i<=this->n-lower_deg;i++)
            new_a[i]=a[i];
    }
    delete[] a;
    this->n=new_n;
    this->a=new_a;
    return *this;
}

polynomial& polynomial::operator *= (const polynomial &v){
    if(this->n==0 && this->a[0]==0 || v.n==0 && v.a[0]==0){
        this->n = 0;
        delete this->a;
        this->a = new double[1];
        this->a[0] = 0.0;
    }
    else{
        double* new_a = new double[this->n+v.n+1];
        for(int i=0; i<=this->n+v.n; i++)
            new_a[i]=0;
        for (int i=0; i<=v.n; i++){
            for(int j=0; j<=this->n; j++){
                new_a[i+j]+=v.a[i]*this->a[j];
            }
        }
        this->n +=v.n;
        delete[] a;
        this->a = new_a;
    }
    return *this;
}

polynomial& polynomial::operator *= (const double c){
    if(c==0.0){
        this->n = 0;
        double new_a[] = {0.0};
        delete[] this->a;
        this->a = new_a;
    }
    else{
        for(int i=0; i<=this->n; i++)
            a[i]*=c;
    }
    return *this;
}

double& polynomial::operator [] (int i) const{
    return a[i];
}

double polynomial::operator () (double x) const{
    double res = 0.0;
    for (int i=n; i>=0; i--)
        res = res*x+a[i];
    return res;
}

int polynomial::getDegree(){
    return n;
}
