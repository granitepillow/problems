class QueensBoard(object):
    self.queens = []
    self.m = None
    self.n = None

    def __init__(self, m, n, queens=[]):
        pass
    def rankfile_to_diag_forward(r, f):
        rout = 'a'
        fout = f + r.lower() - rout #eg (c,3) -> 3 + 'c' - 'a' = 5
        if fout > 8:
            rout += chr(fout - 8 + 'a') #eg (d,7) -> 7 + 'd' - 'a' = 10 -> rout = c
            fout = 8
        return rout + str(fout) #(d,7) is in the "C8" diag_forward file
        #[A1, A2, ..., A8, B8, C8, ..., H8]

    def rankfile_to_diag_backward(r, f):
        rout = 'h'
        fout = f + rout - r.lower() #eg (f,2) - > 2 + h - f = 4
        if fout > 8:
            rout -= chr(fout - 8 + 'a') #eg (d,7) -> 7 + 'h' - 'd' = 11 -> rout = 'e'
            fout = 8
        return rout + str(fout) #eg (d,7) is in the "E8" diag_backward_file
        #[H1, H2, ..., H8, G8, F8, ..., A8]

    def has_collision():
        for q in self.queens:

    def is_full():
        pass

    def add_queen():
        pass

    def remove_queen(queen=None):
        pass

