

function good(num)
{
    function get_digits(num)
    {
        var l = []
        while(num > 0)
        {
            l.push(num % 10);
            num = Math.floor(num/10)
        }
        return l
    }

    if(num <= 0)
    {
        return false;
    }

    digits = get_digits(num)
    sum_of_digits = digits.reduce((acc, ele) => acc += ele)

    for(var i = 0; i < digits.length; i ++)
    {
        if(digits[i] == 0 || num % digits[i] != 0)
        {
            return false;
        }
    }
   
    return (num % sum_of_digits == 0)
}

S = new Set()
for(var i = 0; i <= 100000; i ++)
{
    if(good(i))
    {
        S.add(i)
    }
}

console.log('Numbers:' ,S.size)
