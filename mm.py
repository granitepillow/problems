def generate_code():
    #TODO
    return 1234

def make_guess(guess, code):
    b = 0
    w = 0
    code2 = []
    for e in code:
        code2.append(e)
    for i,e in enumerate(guess):
        if e == code[i]:
            b += 1
            code2.remove(e)
        elif e in code[i:]:
            w += 1
            code2.remove(e)
    return (b, w)


class mmcode():
    def __init__(self, size=4, vals=6):
        self._size = size
        self._range = vals
        self._code = []
        for i in range(size):
            self._code.append(1)
    
    def inc(self):
        for i in self._code:
            


def populate_poss():
    p = []
    b = 1111
    for i in range(6**4):
        p.append(b)
        b+=1
    

def main():
    code = generate_code()
    guesses = 0
    possibilities = []

    guess = [1,1,2,2]
    while(True):

