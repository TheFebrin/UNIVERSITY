Barbara Piasecka

**Zad.1**
    $$\sigma_{A=A' \wedge \neg (B=B' \wedge C=C')}(R \times \rho_{R'(A', B', C')}(R))$$
    
**Zad.2**
    $$\{ s \in S \;| \; (\forall r \in R)(r.A \neq s.Z)\}$$
    
$$\{a,b,c \mid }

**Zad.3**
1. $\{a\mid\ (\exists b)(R(a,b)\wedge\neg((\exists a') a'>a\ \wedge (\exists b')(R(a',b'))))\}$

$$\pi_A(R \setminus (\pi_{A,B} (\sigma _{A<A'}(R \times \rho_{R'(A',B')}(R)))) ) $$
    
2. $\{a,b\mid (\forall c)(T(c,a)\vee T(c,b)\vee (\forall d)(\neg T(c,d)))\}$

formuła niebezpieczna. Jeśli $$(\forall c) (T(c,a) \vee (\forall d)(\neg T(c,d)))$$ to będzie nieskończenie wiele rozwiązań. 
    
3. $\{a,b\mid S(a,b)\wedge \neg(\exists c)(T(a,c)\vee T(b,c))\}$

 $\neg(\exists c)(T(a,c)\vee T(b,c)) \iff (\forall c)(\neg T(a,c) \wedge \neg T(b,c))$
 
 $$ S \setminus (\pi_{S.B_1, S.B_2}(\sigma _{T.B=S.B_1 \vee T.B= S.B_2}(S \times T))) $$
 
 
 
 
 
 
 
 
 
 **Zad.4**
 W zasadzie to wszystkie zapytania są niepoprawne, ponieważ każde zakłada, że osoba musi chodzić do jakiegoś baru. A osoba, która nie bywa w żadnym barze, bywa tylko w tych barach, w których podawany jest jej ulubiony sok, zatem spełnia założenia.
 
 $\{o\mid (\exists b)(B(o,b))\wedge \neg(\exists b)(B(o,b)\wedge (\forall s)(P(s,b)\Rightarrow \neg L(o,s)))\}$
 
 
$\{o\mid (\exists b)(B(o,b))\wedge \neg(\exists b)(B(o,b)\wedge (\forall s)(P(s,b)\Rightarrow L(o,s)))\}$


$\{o\mid (\exists b)(B(o,b))\wedge (\forall b)(B(o,b)\Rightarrow (\exists s)(P(s,b)\wedge L(o,s)))\}$


$\{o\mid (\exists b)(B(o,b))\wedge (\forall b)(B(o,b)\wedge (\exists s)(P(s,b)\wedge L(o,s)))\}$


**Zad.5**

$\{o\mid (\exists b)(B(o,b)\wedge \neg(\exists b')(B(o,b')))\}$
Niepoprawne, ponieważ b może być równe b', więc zapytanie zawsze będzie zwracać zbiór pusty.

$\{o\mid (\exists b)(B(o,b)\}$
Niepoprawne, sprawdzamy tylko, czy bywa w jakimś barze.

$\{o\mid (\exists b)(B(o,b)\wedge \neg(\exists b')(b\not= b' \wedge B(o,b')))\}$
Poprawne. (Poprawione pierwsze)

$\{o\mid (\exists b)(B(o,b)\wedge \neg(\exists b',o')(b\not= b' \wedge o=o' \wedge B(o',b')))\}$
Poprawne. 

**Zad.6**

$\{ a \in A \mid (\exists r \in R(a.pseudo=r.pseudo \wedge \neg(\exists r' \in R) ( r.pseudo = r'.pseudo \wedge (\exists f_1, f_2 \in F)(f_1.idf = r.idf \wedge f_2.idf = r'.idf \wedge f_1.rokProd \neq f_2.rokProd)))\}$

$\{
    f \in F \mid \neg(\exists f'\in F)(f.rezyser = f'.rezyser \wedge f.rokProd < f'.rokProd)
    \}$
    
$\{
    r^{[pseudo,idf,gaza]} \mid r \in R \wedge \neg (\exists r' \in R)(r.idf = r'.idf \wedge r.gaza < r'.gaza)
    \}$
    
$\{
    a \in A \mid (\forall m \in M)(m.pseudo = a.pseudo \Rightarrow \neg(\exists m' \in M)(m.pseudo = m'.pseudo \wedge m.rok > m'.rok \wedge m.minGaza < m'.minGaza))
    \}$
    

    