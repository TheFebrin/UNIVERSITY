
class Fixnum
    
    
  def factors
    tab = [1]
    i = 2
    while i <= self do
      if self%i == 0
        tab << i
      end
      i+=1
    end
    tab
  end


  def perfect_number
    sum = 0
    tab = self.factors
    tab.each {|i| sum += i}
    if sum-self == self
      true
    else
      false
    end
  end

  def int_to_words
    String s = self.to_s
    t = ""
    while s.length > 0 do
      case s[0]
      when "0"
        t += 'zero '
      when "1"
        t += 'jeden '
      when "2"
        t += 'dwa '
      when "3"
        t += 'trzy '
      when "4"
        t += 'cztery '
      when "5"
        t += 'pięć '
      when "6"
        t += 'sześć '
      when "7"
        t += 'siedem '
      when "8"
        t += 'osiem '
      when "9"
        t += 'dziewięć '
      end
      s = s[1, s.length-1]
    end
    t
    end
    
    
    def ack(m)
        if self == 0
            m+1
            elsif m == 0
            (self-1).ack(1)
            else
            (self-1).ack(self.ack(m-1))
        end
        
    end
end

puts(24.factors.to_s)
puts(6.perfect_number)
puts(2.ack(1))
puts(200345678.int_to_words)
