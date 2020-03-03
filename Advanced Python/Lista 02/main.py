from itertools import permutations

class Formula(object):
    def __init__(self, left, right):
        self.left = left
        self.right = right

    def __str__(self):
        raise NotImplementedError

    def oblicz(self, zmienne):
        raise NotImplementedError


    def is_tautology(self, vars):
        def set_up_vars(i, vars):
            ans = {}
            for x in vars:
                if i % 2 == 0:
                    ans[x] = False
                else:
                    ans[x] = True
                i >>= 1
            return ans

        variables_no = len(vars)
        for i in range((1 << variables_no)):
            tmp_vars = set_up_vars(i, vars)
            if not self.oblicz(tmp_vars):
                return False
        
        return True



class Impl(Formula):
    def __init__(self, left, right):
        super().__init__(left, right)

    def __str__(self):
        return f'({self.left} ⇒ {self.right})'

    def oblicz(self, vars):
        return not(self.left.oblicz(vars)) or self.right.oblicz(vars)

class And(Formula):
    def __init__(self, left, right):
        super().__init__(left, right)

    def __str__(self):
        return f'({self.left} ∧ {self.right})'

    def oblicz(self, vars):
        return self.left.oblicz(vars) and self.right.oblicz(vars)

class Or(Formula):
    def __init__(self, left, right):
        super().__init__(left, right)

    def __str__(self):
        return f'({self.left} ∨ {self.right})'

    def oblicz(self, vars):
        return self.left.oblicz(vars) or self.right.oblicz(vars)

class Neg(Formula):
    def __init__(self, expr):
        self.expr = expr

    def __str__(self):
        return f'(¬({self.expr}))'

    def oblicz(self, vars):
        return not(self.expr.oblicz(vars))

class _True_(Formula): 
    def __str__(self):
        return 'true'

    def oblicz(self, vars):
        return True

class _False_(Formula):
    def __str__(self):
        return 'false'

    def oblicz(self, vars):
        return False

class Zmienna(Formula): 
    def __init__(self, var):
        self.var = var
        super().__init__

    def __str__(self):
        return self.var

    def oblicz(self, vars):
        if self.var not in vars:
            print(f'Variable {self.var} is not assigned!')
        else:
            return vars[self.var]



if __name__ == "__main__":
    print('Start')

    x, y, z = Zmienna('x'), Zmienna('y'), Zmienna('z')
    p = Or(x,y)
    q = And(z, p)

    env = {
        'x' : True,
        'y' : False,
        'z' : True
    }
    print(And(Zmienna('x'), Or(Neg(Zmienna('x')), Zmienna('x'))))

    print(f'{q.__str__()} <=> {q.oblicz(env)}')

    p = Or(Zmienna('x'), Neg(Zmienna('x')))
    print(p.__str__(), ' tautologia: ', p.is_tautology(env))

    p = And(Or(Zmienna('x'), Neg(Zmienna('x'))), Or(Zmienna('y'), Neg(Zmienna('y'))))
    print(p.__str__(), ' tautologia: ', p.is_tautology(env))
    