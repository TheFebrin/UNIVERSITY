def ps(n)
    (0..n).each{|r|
            lst=[1]
            term=1
            k=1
            (0..r-1).step(1){|index|
                    term=term*(r-k+1)/k
                    lst.push term
                    k+=1
            }
            p lst
    }
end

def pascal(n)
    first = [1]
    second = [1, 1]

    if n == 1
        print first, "\n"
        return
    end
    print first, "\n"
    print second, "\n"

    if n == 2
        return
    end

    0.upto(n-3) do |i|

        if i % 2 == 0 #pierwsza tab
            first = [1]
            0.upto(second.size - 2) do |x|
                first << second[x] + second[x+1]
            end
            first << 1
            print first, "\n"

        else #druga tab
            second = [1]
            0.upto(first.size - 2) do |x|
                second << first[x] + first[x+1]
            end
            second << 1
            print second, "\n"
        end
    end
end


def pierwsza(n)
    if n == 1
        return false
    end

    if n == 2
        return true
    end

    if n % 2 == 0
        return false
    end

    i = 3
    while i * i <= n
        if n % i == 0
            return false
        end
        i += 2
    end
    return true
end

def podzielniki(n)
    arr = []
    for i in 1..n
        if n % i == 0 and pierwsza(i)
            arr.push(i)
        end
    end
    return(arr.uniq)
end
print "Podaj liczbe naturalna: "
n = gets.to_i
print "Dzielniki pierwsze ",n, " to: ",  podzielniki(n)
puts()
print "Podaj wysokosc piramidy Pascala: "
h = gets.to_i
pascal(h)
