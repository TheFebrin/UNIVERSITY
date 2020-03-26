# DobreZiomki.io;
## Rise & Grind!🔥💯🤟🏽

# 0. Wprowadzenie do tego gówna. 🤢 🤮

https://www.cs.cmu.edu/~213/recitations/x86-cheat-sheet.pdf

https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf?fbclid=IwAR2YfBj2m0ggDu4EMwhDr548W7LE73-q1EaOLLLRoIpy-FbzuKzLGsu9ckg

https://web.cecs.pdx.edu/~kimchris/cs201/slides/10%20-%20x86%20Basics,%20Part%202.pdf

## 0.1 movq Operand Combinations
#### 1.1 Immediate -> Register
```cpp=
temp = 0x4; // C
movq $0x4, %rax // Assembler
```

#### 1.2 Immediate -> Memory
```cpp=
*ptr = -420;
movq $-420, (%rax)
```


#### 2.1 Register -> Register
```cpp=
temp1 = temp2;
movq %rax, %rdx
```

#### 2.2 Register -> Memory
```cpp=
*ptr = temp;
movq %rax, (%rdx)
```

#### 3.1 Memory -> Register
```cpp=
temp = *ptr;
movq (%rax), %rdx
```

#### 3.2 Memory -> Memory
```cpp=
ni chuja w 1 instrukcji
```

## 0.2 Address Computation Examples

|%rdx  |  %rcx |
|-     | -     |
|0xf000| 0x0100|


| Expression      | Address Computation   | Address |
|   -             |   -                   |   -     |
| 0x8(%rdx)       | 0xf000 + 0x8          | 0xf008  |
| (%rdx, %rcx)    | 0xf000 + 0x100        | 0xf100  |
| (%rdx, %rcx, 4) | 0xf000 + 4 * 0x100    | 0xf400  |
| 0x80(, %rdx, 2) | 2 * 0xf000 + 0x80     | 0x1e080 |

## 0.3. Leaq vs movq
* LEA means Load Effective Address
* MOV means Load Value


In short, LEA loads a pointer to the item you're addressing whereas MOV loads the actual value at that address.

The purpose of LEA is to allow one to perform a non-trivial address calculation and store the result.

```cpp=
leaq %rax, %rcx // załaduje adres do %rcx
movq %rax, %rcx // załaduje wartość z adresu %rax do %rcx
```

## 0.4 Some Arithmetic Operations
* `addq Src,Dest`   ==>   `Dest = Dest + Src`
* `subq Src,Dest`   ==>   `Dest = Dest − Src`
* `imulq Src,Dest`  ==>   `Dest = Dest * Src`
* `salq Src,Dest`   ==>   `Dest = Dest << Src` Also called shlq
* `sarq Src,Dest`   ==>   `Dest = Dest >> Src` Arithmetic
* `shrq Src,Dest`   ==>   `Dest = Dest >> Src` Logical
* `xorq Src,Dest`   ==>   `Dest = Dest ^ Src`
* `andq Src,Dest`   ==>   `Dest = Dest & Src`
* `orq Src,Dest`    ==>   `Dest = Dest | Src`
* `incq Dest`    ==>   `Dest = Dest + 1`
* `decq Dest`    ==>   `Dest = Dest − 1`
* `negq Dest`   ==>   `Dest = − Dest`
* `notq Dest`    ==>   `Dest = ~Dest`

## 0.5 Registers
|8-byte register | Bytes 0-3 | Bytes 0-1 | Byte 0|
|-            |          -|          -| -     |
|%rax |%eax |%ax |%al|
|%rcx |%ecx |%cx |%cl|
|%rdx |%edx |%dx |%dl|
|%rbx |%ebx |%bx |%bl|
|%rsi |%esi |%si |%sil|
|%rdi |%edi |%di |%dil|
|%rsp |%esp |%sp |%spl|
|%rbp |%ebp |%bp |%bpl|
|%r8 |%r8d |%r8w |%r8b|
|%r9 |%r9d |%r9w |%r9b|
|%r10 |%r10d |%r10w |%r10b|
|%r11 |%r11d |%r11w |%r11b|
|%r12 |%r12d |%r12w |%r12b|
|%r13 |%r13d |%r13w |%r13b|
|%r14 |%r14d |%r14w |%r14b|
|%r15 |%r15d |%r15w |%r15b|


## 0.6 Przykladowe funkcje

#### 1. 12 * x
```cpp=
long m12(long x)
{
    return x*12;
}
```
```cpp=
leaq (%rdi,%rdi,2), %rax   // t = x+2*x
salq $2, %rax              // return t<<2
```

#### 2. Swap
```cpp=
void swap(long *xp, long *yp)
{
    long t0 = *xp;
    long t1 = *yp;
    *xp = t1;
    *yp = t0;
}
```
```cpp=
swap:
movq (%rdi), %rax
movq (%rsi), %rdx
movq %rdx, (%rdi)
movq %rax, (%rsi)
ret
```


# Zadanie 1. ✔️
Poniżej podano wartości typu int64_t leżące pod wskazanymi adresami i w rejestrach:

| Adres | Wartość | Rejestr | Wartość |
|   -   |   -  |   -  |  -  |
| 0x100 | 0xFF | %rax | 0x100 |
| 0x108 | 0xAB | %rcx | 1 |
| 0x110 | 0x13 | %rdx | 3 |
| 0x118 | 0x11 | -    | - |

   
Oblicz wartość poniższych operandów. Wskaż, które z nich mogą dotyczyć adresu w pamięci.
1. `%rax` -> 0x100
2. `$0x110` -> 0x110
3. `0x108` -> 0xAB
4. `(%rax)` -> (to na co wskazuje adres pod %rax) -> 0xFF
5. `8(%rax)` -> (to na co wskazuje adres pod %rax + 8 czyli 0x108) -> 0xAB
6. `23(%rax,%rcx)` -> (23 + %rax + %rcx) -> (0x17 + %rax + %rcx) -> (0x118) -> 0x11
7. `0x104(,%rdx,4)` -> (0x104 + %rdx * 4) -> (gdzie wskazuje adres 0x110) -> 0x13
8. `(%rax,%rdx,8)` -> (%rax + 8*%rdx) -> (%rax + 8*3) -> (%rax + 0x18) -> (gdzie wskazuje 0x118) -> 0x11
9. `265(%rcx,%rdx,2)` -> (0x109 + %rcx + 2*%rdx) -> (gdzie wskazuje 0x110) -> 0x13

<3 jechane 

# Zadanie 2. ✔️
Każdą z poniższych instrukcji wykonujemy w stanie maszyny opisanym tabelką z zadania 1.
Wskaż miejsce, w którym zostanie umieszczony wynik działania instrukcji, oraz obliczoną wartość.

**chujowainstrukcjaq source, desc**


`addq Src,Dest` Dest = Dest + Src
`subq Src,Dest` Dest = Dest − Src
`imulq Src,Dest` Dest = Dest * Src
`salq Src,Dest` Dest = Dest << Src     (Also called shlq)
`sarq Src,Dest` Dest = Dest >> Src     (Arithmetic, czyli wstawia bit który był skrajnie po lewej)
`shrq Src,Dest` Dest = Dest >> Src     (Logical, czyli wstawia zera od lewej)
`xorq Src,Dest` Dest = Dest ^ Src
`andq Src,Dest` Dest = Dest & Src
`orq Src,Dest` Dest = Dest | Src

`incq Dest` Dest = Dest + 1
`decq Dest` Dest = Dest − 1
`negq Dest` Dest = − Dest
`notq Dest` Dest = ~Dest

1. `addq %rcx,(%rax)` -> 0x100 w 0x100
2. `subq 16(%rax),%rdx` -> 3 - (to co w 0x100 + 16, czyli to co w 0x110) -> 3 - 0x13 w %rdx
3. `shrq $4,%rax` -> (0x100 >> 4) -> (0x10) w %rax
4. `incq 16(%rax)` -> (0x100 + 0x10 zwiększ o 1) -> (co w 0x110 zwiększ o 1) -> 0x14 w %rax
5. `decq %rcx` -> 0 w %rcx
6. `imulq 8(%rax)` -> %rax * 8(%rax) -> 0x100 * (to co w 0x108) -> 0xAB00 w %rdx:%rax
jeśli 1 argument w imulq to pomnóż to co wychodzi razy to co w %rax i zapisz wynik w rejestrach %rdx i %rax bo wynik może być duży
7. `leaq 7(%rcx,%rcx,8),%rdx` -> (7+1+8*1) -> 0x10 i zapisz w %rdx
8. `leaq OxA(,%rdx,4),%rdx` -> 0xA+4*3 -> 0x16 w %rdx


# Zadanie 3. ✔️
Dla każdej z poniższych instrukcji wyznacz odpowiedni sufiks (tj. b, w, l lub q) na podstawie
rozmiarów operandów:

    * b -> bajt
    * w -> word - 2 bajty
    * l -> long - 4 bajty
    * q -> quad - 8 bajtów
    
Nie wiemy czy rozmiar operandu dobierać na podstawie source, dest czy najmniejszego!!!

1. mov %eax,(%rsp) 
    > %eax to połowa %rax więc 4 bajty - movl
2. mov (%rax),%dx 
    > %dx połowa %edx, 2 bajty - movw
3. mov $0xFF, %bl
    > %ebx = 4 bajty, %bx = 2 bajty, a %bl 1 bajt - movb
4. mov (%rsp,%rdx,4),%dl
    > %dl, %edx = 4 bajty, %dx = 2 bajty, %dl = 1 bajt - movb
5. mov (%rdx),%rax
    > normalnie 8 bajtów - movq
6. mov %dx,(%rax)
    > 2 bajty - movw



# Zadanie 4. ✔️
Które z poniższych linii generuje komunikat błędu asemblera i dlaczego?
1. movb $0xF,(%ebx) ✔️
    >chyba git
2. movl %rax,(%rsp) ❌
    >nie dziala bo l to 4 bajty tylko
3. movw (%rax),4(%rsp) ❌
    > nie dziala bo src i dest nie moga razem miec referencji
4. movb %al,%sl ❌
    > nie dziala bo %sl to podrabianiec
5. movq %rax,$0x123 ❌
    > nie mozna przenosic do wartosci zmiennej
6. movl %eax,%rdx  ❌
    > różne rozmiary rejestrów -- powinno być (%rdx) albo %edx
7. movb %si,8(%rbp) ❌
    > si to 2 bajty, a b przenosi bajta


# Zadanie 5. ✔️
Rejestry `%rax` i `%rcx` przechowują odpowiednio wartości x i y. Podaj wyrażenie, które będzie opisywać zawartość rejestru %rdx po wykonaniu każdej z poniższych instrukcji:

(https://web.cecs.pdx.edu/~kimchris/cs201/slides/10%20-%20x86%20Basics,%20Part%202.pdf)

(leaq przenosi adresy, nie wartości)

* `%rax` = x
* `%rcx` = y
* `%rdx` = w

1. `leaq 6(%rax),%rdx`
    > w := x + 6
2. `leaq (%rax,%rcx),%rdx`
    > w := x + y
3. `leaq (%rax,%rcx,4),%rdx`
    > w := x + 4 * y
4. `leaq 7(%rax,%rax,8),%rdx`
    > w := 8 * x + x + 7 = 9 * x + 7
5. `leaq OxA(,%rcx,4),%rdx`
    > w := 4 * y + 10
6. `leaq 9(%rax,%rcx,2),%rdx`
    > w := 2 * y + x + 9


# Zadanie 6. ✔️
Zastąp instrukcję `subq %rsi, %rdi` równoważnym ciągiem instrukcji bez jawnego użycia operacji odejmowania. Można używać dowolnych innych instrukcji i rejestrów.

Negacja bitowa `~x` to `-x - 1`. 

```cpp=
notq %rsi
leaq 1(%rdi,%rsi) %rdi
```

# Zadanie 7. ✔️
Kompilator przetłumaczył funkcję o sygnaturze `«uint64_t compute(int64_t x, int64_t y)»` na następujący kod asemblerowy.

    * %rdi = x
    * %rsi = y
    * %rax = z
    * %rdx = w

```cpp=
compute:
leaq (%rdi,%rsi), %rax  // z = x + y
movq %rax, %rdx         // w = z
sarq $31, %rdx          // w = w >> 31
xorq %rdx, %rax         // z = w ^ z
subq %rdx, %rax         // z = z - w
ret                     // return z
```
Argumenty «x» i «y» zostały przekazane funkcji «compute» odpowiednio przez rejestry `%rdi` i `%rsi`, a wynik został zwrócony przez instrukcję ret w rejestrze `%rax`. Jaką wartość oblicza ta funkcja?
Wskazówka To, że sarq jest instrukcją przesunięcia arytmetycznego a nie logicznego jest w tym zadaniu istotne.

To jest `|x+y|`.
So basically ... niech `z = x + y`, robimy `(z >> 31) ^ z - (z >> 31)`.
Dla + nie dziala jak gdzieś w lewej połowie jest 1.
Dla - nie dziala jak gdzieś w lewej połowie jest 0.


Przyklady:
```cpp=
z: -27
(z >> 31): -1
(z >> 31) ^ z): 26
wynik: 27
```

```cpp=
z: 9223372036854775791
(z >> 31): 4294967295
(z >> 31) ^ z): 9223372032559808528
wynik: 9223372028264841233
```

```cpp=
z: -4611686018427387904
(z >> 31): -2147483648
(z >> 31) ^ z): 4611686016279904256
wynik: 4611686018427387904
```

# Zadanie 8. ✔️
Rozwiąż poprzednie zadanie dla funkcji `«int16_t compute2(int8_t m, int8_t s)»`. 
Jak poprzednio, pierwszy argument został przekazany w rejestrze `%rdi`, drugi w `%rsi`,
a wartość zwracana jest w `%rax`. Funkcja operuje na 8-, 16-, 32 i 64-bitowych rejestrach, a zwraca wynik w rejestrze 64-bitowym.
Wyjaśnij, jak poszczególne wiersze kodu zmieniają starsze bajty rejestrów, których młodszymi bajtami są ich operandy.

    * %rdi = m
    * %rsi = s
    * %rax = x
    * %rdx = y

* Conversions:
    - `movsbw` =>  word / `short`
    - `movsbl` =>  long / `int`
    - `movsbq` =>  quad / `long long` 

```cpp
int16_t compute2(int8_t m, int8_t s);
```
**-> funkcja oblicza 60m + s**

konwencja: %rdi: m (pierwszy arg), %rsi: s (drugi arg)
zwracamy wynik w: %rax

***movsXY*** -> przenosi z rejestru X-bitowego do Y-bitowego
w naszym przykładzie movsbw -> z 8-bitowego do 16-bitowego

```cpp
asm(
    "compute2:;"
    "movsbw %dil, %di;"  // rzutuje na 16bit
    "movl   %edi, %edx;" // edx = edi (przy czym bity 63-32 rdi sa zerowane)
    "sall   $4,   %edx;" // edx <<= 4 -> edx*=16 (czyli edx = 16*edi)
    "subl   %edi, %edx;" // edx = edx - edi czyli edx = 16*edi-edi = 15*edi
    "leal   0(,%rdx,4), %eax;" // eax = 4*rdx czyli 4*15*edi
    "movsbw %sil, %si;"  // rzutuje na 16bit
    "addl   %esi ,%eax;" // eax (czyli 60*edi) += esi czyli drugi argument
    "ret" // czyli podsumowujac: return 60*edi + esi;
);
```



# Zadanie 9. ✔️
Zinterpretuj poniższe stałe szesnastkowe jako liczby pojedyńczej precyzji (32-bitowe) w formacie IEEE 754, następnie wykonaj dodawania i zapisz wynik w takim samym formacie.

IEEE 754 - 1bit na znak, 8 na wykładnik, 23 - mantysa

Liczba zmiennoprzecinkowa w formacie IEEE 754 zapisywana jest za pomocą 32 bitów. Z czego 1 bit przeznaczamy na znak, 8 bitów na wykładnik, a następnie 23 bity na mantysę. BIAS jest równy 127.

**1.  0xC0D20004 + 0x72407020**

C0D20004~16~ = 1100 0000 1101 0010 0000 0000 0000 0100~2~
Przesuwamy przecinek aby na początku stała 1.

1,100 0000 1101 0010 0000 0000 0000 0100 * 2^31^
exp = 31 - 127 = -96
Wpisujemy wartość -96 w miejsce wykładnika.
W miejsce mantysy wpisujemy 23 kolejne bity które są po przecinku danej liczby.

|  s  | wykładnik |         mantysa         |
|:---:|:---------:|:-----------------------:|
|  0  | 10100000  | 10000001101001000000000 |


72407020~16~ = 0111 0010 0100 0000 0111 0000 0010 0000~2~
= 1,110010010000000111000000100000 * 2^30^
Schemat zapisania do podanej notacji jest taki sam.

Sprowadzamy dane liczby do wspólnego wykładnika i dodajemy je pisemnie.
*wynik:* 1,00110011000100100111000000100100 * 2^32^

|  s  | wykładnik |         mantysa         |
|:---:|:---------:|:-----------------------:|
|  0  | 10100001  | 00110011000100100111000 |



**2. 0xC0D20004 + 0x40DC0004**

C0D20004~16~ = 1,1000000110100100000000000000100 * 2^31^
40DC0004~16~ = 1,000000110111000000000000000100 * 2^30^

*wynik:* 1,00000001101011100000000000001000 * 2^32^

|  s  | wykładnik |         mantysa         |
|:---:|:---------:|:-----------------------:|
|  0  | 10100001  | 00000001101011100000000 |



**3. (0x5FBE4000 + 0x3FF80000) + 0xDFDE4000**

5FBE4000~16~ = 1,011111101111100100000000000000 * 2^30^
3FF80000~16~ = 1,11111111110000000000000000000 * 2^29^

*wynik1:* 1,0011111101101100100000000000000 * 2^31^

|  s  | wykładnik |         mantysa         |
|:---:|:---------:|:-----------------------:|
|  0  | 10100000  | 00111111011011001000000 |



DFDE4000~16~ = 1,1011111110111100100000000000000 * 2^31^

*wynik2:* 1,01111111100101001000000000000000 * 2^32^

|  s  | wykładnik |         mantysa         |
|:---:|:---------:|:-----------------------:|
|  0  | 10100001  | 01111111100101001000000 |


# 🔚