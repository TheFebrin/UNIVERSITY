primes = [100001]
for(var i = 0; i <= 100000; i ++)
{
    primes[i] = true;
}

for(var i = 2; i * i <= 100000; i ++)
{
    if(primes[i])
    {
        for(var j = i * i; j <= 100000; j += i)
        {
            primes[j] = false;
        }
    }
}

P = []
for(var i = 2; i <= 100000; i ++)
{
    if(primes[i])
    {
        P.push(i)
    }
}

console.log(P)