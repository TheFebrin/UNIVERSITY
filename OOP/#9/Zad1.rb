class Proc

	def value(x) # wylicza wartosc x
		self.call(x)
	end

	def miejsce_zerowe(a, b, eps) #aproksymacja miejsca zerowego

				middle = (a+b)/2.0  #srednia arytm
        x = value(middle) #wartosc funkcji w miejscu x

        if x.abs <= eps
            return middle
        else
            left = value(a)
            rigth = value(b)

            if left < 0 and x > 0
                return miejsce_zerowe(a,middle,eps)

            elsif left > 0 and x < 0
                return miejsce_zerowe(a,middle,eps)

            elsif rigth > 0 and x < 0
                return miejsce_zerowe(middle,b,eps)

            elsif rigth < 0 and x > 0
                return miejsce_zerowe(middle,b,eps)

            end
        end
    end



	def pochodna(x) #pochodna
		h = 0.00000000001
		return (0.0 + value(x + h) - value(x)) / h
	end



	def calka(a, b) #calka oznaczona

		sn = 0.0
		n = 1000
		h = (b-a)/n

		for i in 1..n
			yi = value(a + (i-1)*h)
			yi /= 2 if i == 1 or i == n
			sn += h*yi
		end

		return sn
	end



   def wykres(a, b, nazwa) #wykres

        file = File.open(nazwa, "w")
        file.puts "%!PS"

        x = 200
        y = 200

        dx = (b - a) / x.to_f
        h = y / 2 # wysokosc

        file.puts "0 " + (value(a) + h).to_s + " moveto"

	    for i in 1..x
            file.puts i.to_s + " " + (value(a + i * dx) + h).to_s + " lineto"
        end

        file.puts "stroke"
        file.puts "showpage"

        file.close
    end

end

puts "Dla f(x) = x^2 - 4 \n\n"


f = proc {|x| x * x - 4}


puts "f(100) = ", f.value(100)
print "\n"

puts "Miejsce zerowe na [-100,100] : ", f.miejsce_zerowe(-100.0, 100.0, 0.0000001)
print "\n"

puts "Pochodna w punkcie 5", f.pochodna(5)
print "\n"

puts "calka oznaczona na  [-3, 8] : ", f.calka(-3.0, 8.0)
print "\n"

f.wykres(-10.0, 10.0, "plik.PS")
