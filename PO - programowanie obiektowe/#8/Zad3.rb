class Jawne
    def initialize (napis)
        @napis = napis
    end
    
    def zaszyfruj (klucz)
        res = ""
        for c in 0 .. @napis.length-1 do
            res+= klucz[ @napis[c] ]
        end
        return Zaszyfrowane.new(res)
        end
        
        def to_s
            return @napis
        end
    end
    
    class Zaszyfrowane
        def initialize (napis)
            @napis=napis
        end
        
        def odszyfruj(klucz)
            res = ""
            for c in 0 .. @napis.length-1 do
                res+= klucz[ @napis[c] ]
            end
            return Jawne.new(res)
            end
            
            def to_s
                return @napis
            end
        end
        
        print("zad.3\n")
        klucz = {
        'a' => 'b',
        'b' => 'r',
        'c' => 'd',
        'd' => 'e',
        'r' => 'y',
        'y' => 'u',
        'u' => 'a'
        }
        j = Jawne.new("ruby")
        puts(j)
        puts(j.zaszyfruj(klucz))
        puts("\n")
        z = Zaszyfrowane.new("yaru")
        w = j.zaszyfruj(klucz)
        puts(z)
        puts(w)
        puts(z.odszyfruj(klucz))
        puts(w.odszyfruj(klucz))
