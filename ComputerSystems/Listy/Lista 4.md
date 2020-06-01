# [SyK] Lista 4

UWAGA ZADANIA MOŻNA NORMALNIE NAPISAĆ W C, ŻEBY ROBIŁO TO SAMO
==============================================================

## Linki
 * https://www.cs.cmu.edu/~213/recitations/x86-cheat-sheet.pdf
 * https://docas.oracle.com/cd/E26502_01/html/E28388/ennbz.html
 * https://www.youtube.com/watch?v=v1APxmB54og&fbclid=IwAR2Bhwy101oT0d-BHaMn9Vtvitjd9YoIa8eAggzgM6XrSV9aYQ6buzG3nVI - jakoś w 24:00 typ kontynuuje prezentacje od momentu, w którym dziadek ze skosa kończy
 
 
![](https://i.imgur.com/DfnQNA8.png)
![](https://i.imgur.com/R23pC8Z.png)
![](https://i.imgur.com/XLxobuY.png)
![](https://i.imgur.com/pcPOzE3.png)
![](https://i.imgur.com/wlp2qiS.png)

    * b -> bajt
    * w -> word - 2 bajty
    * l -> long - 4 bajty
    * q -> quad - 8 bajtów

## Zad 1 ❌
**Rejestry %reg1% i %reg2 są tego samego rozmiaru. Wykaż, że niezależnie od zapisanych w nich wartości, interpretowanych jako liczby ze znakiem, instrukcja cmp %reg1, %reg2 ustawia flagi tak, że setl %reg3 zadziała zgodnie z oczekiwaniami. Podobnie, wykaż, że jeśli te wartości intepretujemy jako liczby bez znaku, to setb %reg3 zadziała zgodnie z oczekiwaniami. Wywnioskuj stąd, że pozostałe instrukcje rodziny set działają stosownie do swoich sufiksów.**


    ZF - Zero Flag
    SF - Sign Flag
    OF - Overflow Flag (Signed)
    CF - Carry Flag (Unsigned)

%reg1 i %reg2 są tego samego rozmiaru.
cmp %reg1, %reg2 (%reg2 - %reg1)

1. %reg1 i %reg2 interpretujemy jako liczby ze znakiem
setl: SF ^ OF 
setl %reg3 (SF = 1, gdy %reg2 - %reg1 <0)
2. %reg1 i %reg2 interpretujemy jako liczby bez znaku
setb: CF
setb %reg3 


## Zad 2 ✔️
**Poniżej znajduje się kod funkcji o sygnaturze «void who(short v[], size_t n)». Przetłumacz go na język C i odpowiedz, jaki jest efekt jego wykonania. Czy znajomość sygnatury jest istotna?**


```c=
who: subq $1, %rsi
     movl $0, %eax
.L2: cmpq %rsi, %rax
     jnb .L4
     leaq (%rdi,%rax,2), %rcx <-- //rax element (od dołu)
     movzwl (%rcx), %r8d //przenosimy to co pod rcx do r8d
     leaq (%rdi,%rsi,2), %rdx <-- //rsi element (od góry)
     movzwl (%rdx), %r9d
     movw %r9w, (%rcx)
     movw %r8w, (%rdx)
     addq $1, %rax
     subq $1, %rsi
     jmp .L2
.L4: ret
```
>result -> %rax
>stack top -> %rsp
>stack bottm -> %rbp
>tablica argumentów -> %rdi


#### Rozwiązanie:
```c=
short who(short v[], size_t n){
//reverse tablicy v
    n = n - 1;
    short result = 0;
    while(result < n){
        short *rcx = v + 2 * result; //wskaznik na v[result], 2*result bo to shorty - 2 bajty
        short r8d = *rcx; //v[result]
        
        short *rdx = v + 2*n; //wskaznik na v[n]
        short r9d = *rdx; //v[n]
        
        *rdx = r8d;
        *rcx = r9d;
        
        result++;
        n--;
    }    
    return result;
}
```

```cpp=
void who(__int16_t v[], size_t n)
{
    __int16_t a, b;
    size_t k = 0;
    n = n - 1;
    while(k < n)
    {
        a = v[k];
        b = v[n];
        v[k] = b;
        v[n] = a;
        k ++;
        n --;
    }
}
```

**Wynik funkcji: reverse tablicy**

## Zad 3 ✔️
**Poniżej znajduje się kod funkcji o sygnaturze «bool zonk(char\* a, char\* b)», jako argumenty przyjmującej C-owe łańcuchy znaków. Przetłumacz ją na język C (bez instrukcji goto). Jaką wartość powinna liczyć ta funkcja?**

    * movzb{wlq}, movzw{lq} --> move and zero extend
    * movsl, smovl --> move doubleword string
    
http://www.eecg.toronto.edu/~amza/www.mindsec.com/files/x86regs.html
#### `test`:
TEST sets the zero flag, ZF, when the result of the AND operation is zero. If two operands are equal, their bitwise AND is zero when both are zero. TEST also sets the sign flag, SF, when the most significant bit is set in the result, and the parity flag, PF, when the number of set bits is even.

```cpp=
; Conditional Jump
test cl, cl   ; set ZF to 1 if cl == 0
je 0x804f430  ; jump if ZF == 1

; Conditional Jump with NOT
test cl, cl   ; set ZF to 1 if cl == 0
jne 0x804f430  ; jump if ZF != 1

; or
test eax, eax  ; set SF to 1 if eax < 0 (negative)
js error ; jump if SF == 1
```

#### Kod z zadania:
```cpp=
zonk: movl $0, %ecx
.L2: movslq %ecx, %rax // sign-extened from long to quad
     movzbl (%rdi,%rax), %edx //zero-extended from byte to long
     testb %dl, %dl
     je .L6
     cmpb %dl, (%rsi,%rax)
     jne .L5
     addl $1, %ecx
     jmp .L2
.L6: orb (%rsi,%rax), %dl
     sete %al
     ret
.L5: movl $0, %eax
     ret
```


#### Rozwiązanie:
```cpp=
//al to ostatni bajt rax
//dl to ostatni bajt rdx

//a -> rdi, b -> rsi
bool zonk(char*a, char*b) {
    ecx = 0;
    
    while(true) {
        rax = ecx; //result = ecx
        edx = *(a+rax); //a[rax]
        dl = edx&0xFF; //a[rax] -> bo char ma 1 bajt
        
        
/*L6*/  if (dl == 0) // NULL
        {
            dl = (*(b+rax)) | dl; //  dl = b[rax] | dl
            //edx = edx | dl;
            
            /*sete - sets instruction (and its equivalent, setz) 
            sets its argument to 1 if the zero flag is set 
            or to 0 otherwise. 
            */
            
            //ZERO_FLAG bedzie ustawione na 1 tylko jesli or ja ustawil czyli skoro dl = 0 to b[rax] tez, tzn b[rax] = NULL czyli a i b skonczyly sie w tym samym momencie
            rax = rax | ZERO_FLAG;
            return rax;
            
        }
/*L5*/  if (! (dl == *(b+rax)))
//      if (dl != b[rax])
        {
            rax = rax & 0; //zerowanko raxa -> zwroc falsz
            return rax;

        }
        ecx++;
    }
    
}
```

#### Rozwiązanie v2 LEPSZE:
```cpp=
bool zonk(char* a, char* b)
{
    int iter;
    for (iter = 0; a[iter]; iter++)
    {
        if(b[iter] != a[iter])
        {
            return 0;
        }
    }
    return (b[iter] == NULL);
}
```

#### Co robi: sprawdza czy a jest równy b.

## Zad 4 ✔️
**Zastąp instrukcje pushq %reg1 oraz popq %reg2 równoważnymi ciągami instrukcji jawnie operującymi na stosie.**

```
pushq src:
    subq $8, %rsp
    movq src, (%rsp)
    
popq dest:
    movq (%rsp), dest
    addq $8, %rsp
```



## Zad 5 ✔️
**Poniżej znajduje się kod funkcji o sygnaturze «foo(int16_t v[], size_t n)». Przetłumacz ją na język C. Narysuj ramkę stosu tej funkcji i wytłumacz, jaka jest rola poszczególnych komórek ramki oraz jak jej zawartość zmienia się w trakcie działania. Jaki jest efekt ma ten kod?**
```c=
foo: pushq %rbp
     movq %rsp, %rbp
     movq %rdi, -24(%rbp) //wrzuca %rdi w miesjcu adres %rbp - 24 do %rbp-8, bo zajmuje 16 bitów (chyba do rbp - 20, no bo zajmuje 16 bitów = 4 bajty)
     movq %rsi, -32(%rbp) // wrzuca %rsi w miesjcu adres %rbp -32 do -24
     movq $0, -8(%rbp) // int64 czyli 8 bajtów
     jmp .L2
.L3: movq -8(%rbp), %rax
     leaq (%rax,%rax), %rdx
     movq -24(%rbp), %rax
     addq %rdx, %rax
     movzwl (%rax), %eax
     leal (%rax,%rax), %edx
     movq -8(%rbp), %rax
     leaq (%rax,%rax), %rcx
     movq -24(%rbp), %rax
     addq %rcx, %rax
     movw %dx, (%rax)
     addq $1, -8(%rbp)
.L2: movq -8(%rbp), %rax
     cmpq -32(%rbp), %rax
     jb .L3
     nop // nic nie zmienia, cos tam sie psuło w AMD bo typ na wykladzie tak gadał
popq %rbp
     ret
```
| schemat ramki       | 
|---------------------|
|old %rbp             |
|saved registers      |
|local varables       |
|addidtional args >= 7|

| schemat frame'a procedury           | 
|-------------------------|
|%rsp <--  %rsp ==%rbp         |  
|i  <--  %rsp-8          |
|?  <--  %rsp-16           |
|v  <--  %rsp-24   |
|n  <--  %rsp - 32 |


- -24(%rbp) -> n
- -32(%rbp) -> v[]
- -8(%rbp) -> 0, przerzucamy zawsze do raxa


```cpp=
//'i' to jest wartość -8(%rsp)
foo(int16_t v[], size_t n) {
    rax = 0;
    
    for (i = 0; i < n; i++) {
        rax = i;
        rdx = 2 * rax; // leaq (%rax,%rax), %rdx
        rax = v; //wskaźnik na v
        rax = rax+rdx; //&v[i]  (wskaźnik na v[i])  bo v to &v[0] + sizeof(short) * i
        rax = *rax; //v[i]
        edx = 2 * rax; //2*v[i]
        rax = i;
        rcx = 2 * rax; //2*i
        rax = v;
        rax = rax+rcx; //v + 2*i = v[i];
        rax = edx;// v[i] = 2*v[i];
    }
}
```

```cpp=
void foo(int16_t v[], size_t n) {
    for (int i = 0; i < n; i++) 
        v[i] = v[i] * 2;
    
}

```

#### Rozwiązanie: zastępuje pierwsze n wartości przez ich dwukrotności


## Zad 6 ✔️
**Poniżej znajduje się kod funkcji rekurencyjnej o nieznanej sygnaturze. Przetłumacz tę funkcję na język C, odkryj jej sygnaturę i odpowiedz, jaką wartość ona liczy.**
```c=
reccur:
    pushq %rbp
    movq %rsp, %rbp
    subq $16, %rsp //8 bajtów na pointer i 8 na wartość
    movl %edi, -4(%rbp)
    cmpl $0, -4(%rbp)
    jne .L2
    movl $1, %eax
    jmp .L3
.L2: 
    movl -4(%rbp), %eax
    subl $1, %eax
    movl %eax, %edi //teraz edi = n-1, -4(%rbp) = n 
    call reccur
    imull -4(%rbp), %eax // rax = (n-1)!, -4(%rbp) = n
.L3: 
    leave
    ret
```
**Wskazówka** Instrukcja leave podstawia %rbp pod %rsp wykonuje popq %rbp.
| schemat frame'a procedury           | 
|-------------------------|
|       %rbp <-- %rbp  |  
|      %edi <-- %rbp - 4    |
|  adres powrotu <-- %rbp - 8|
|  %rsp <-- %rbp - 16|
```cpp=
//-4(%rbp) - edi
reccur(int edi) {
    if (edi == 0) {
        eax = 1;
        //leave - pewnie cos trzeba tu dopisac
        return eax;
    }
/*L2*/
    eax = edi;
    eax = eax - 1;
    edi = eax;
    wynik = reccur(edi); // wynik --> -4(%rbp), czyli silnia(n - 1)
    eax = wynik * (edi + 1); //  imull -4(%rbp), %eax
    //leave
    return eax;
}
```
```c=
reccur(int n){
    if (n == 0){
        return 1;
    }
    return n * reccur(n-1);
}
```
#### rozwiązanie: silnia

## Zad 7 ✔️
**Dana jest funkcja o sygnaturze postaci «int32_t bar(int32_t a1,...,int32_t an)», gdzie n jest nieznane. Jaka jest minimalna wartość n, jeżeli wiadomo, że funkcja zwraca wartość jednego ze swoich argumentów, a jej kod wygląda tak:**
```c=
bar: pushq %rbp
movq %rsp, %rbp
.....
movl 16(%rbp), %eax
popq %rbp
ret
```

**Napisz szkic kodu asemblerowego wywołującego funkcję bar z liczbą parametrów równą takiemu minimalnemu n. Zadbaj o poprawne przekazanie argumentów do funkcji. Jak zmieni się napisany przez Ciebie kod, gdy n będzie większe?**

**Dana jest funkcja o sygnaturze postaci «int32_t bar(int32_t a1,...,int32_t an)», gdzie n jest nieznane. Jaka jest minimalna wartość n, jeżeli wiadomo, że funkcja zwraca wartość jednego ze swoich argumentów, a jej kod wygląda tak:**
```c=
bar: 
    pushq %rbp
    movq %rsp, %rbp
    .....
    movl 16(%rbp), %eax
    popq %rbp
    ret
```

**Napisz szkic kodu asemblerowego wywołującego funkcję bar z liczbą parametrów równą takiemu minimalnemu n. Zadbaj o poprawne przekazanie argumentów do funkcji. Jak zmieni się napisany przez Ciebie kod, gdy n będzie większe?**

#### Prezentacja uznana przez polesiuka
Liczba argumentów -> 7

godbolt.org

```c=
int foo(int num1, int num2, int num3, int num4, int num5, int num6, int num7) {
    return num7;
}
int main(){
    foo(1,2,3,4,5,6,7);
}
```

```c=
foo:
    push    rbp
    mov     rsp, rbp
    mov     -4(rbp), edi 
    mov     -8(rbp), esi
    mov     -12(rbp), edx 
    mov     -16(rbp), ecx 
    mov     -20(rbp), r9d 
    mov     16(rbp), eax 
    pop     rbp
    ret
main:
    push    rbp
    mov     rsp, rbp
    push    7
    mov     6, r9d
    mov     5, r8d
    mov     4, ecx
    mov     3, edx
    mov     2, esi
    mov     1, edi
    call    foo
    add     8, rsp
    mov     0, eax
    leave
    ret
```

|co|adres od rsp|
|-|-|
|num7|16|
|ret addr|8|
|rbp|0|


> instrukcja movl 16(%rbp), %eax w tym zadaniu jest poprawna i tak,
rzeczywiście adres 16(%rbp) odnosi się do ramki funkcji wywołującej
funkcję bar. Co będzie w tym miejscu, jeśli bar ma więcej niż 6
argumentów? W ogóle to zachęcam do eksperymentowania z serwisem
godbolt.org, można spróbować "odgadnąć" kod w C funkcji bar i zobaczyć
jego tłumaczenie na asembler. ~ P. Witkowski 


