class Formula(object):
    def __str__(self):
        raise NotImplementedError

    def oblicz(self, zmienne):
        raise NotImplementedError

class Impl(Formula): #subclass, inherits from SuperHero
    def __str__(self):
        print('Impl')

class And(Formula): #another subclass
    def __str__(self):
        print('And')

class Or(Formula): #another subclass
    def __str__(self):
        print('Or')

class Neg(Formula): #another subclass
    def __str__(self):
        print('Neg')

class True(Formula): #another subclass
    def __str__(self):
        print('True')

class False(Formula): #another subclass
    def __str__(self):
        print('False')

class Zmienna(Formula): #another subclass
    def __str__(self):
        print('Zmienna')

if __name__ == "__main__":
