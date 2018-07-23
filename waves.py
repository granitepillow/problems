a = [0, 0, 0, 0, 0]
dir = -1
val = 100
full = val
at = 0.9

for i in range(1000):
    for j in range(len(a)-1):
        a[-1-j] = a[-2-j]*at
    if val >= full and dir == 1:
        dir = -1
        full *= at
    elif val <= -full and dir == -1:
        dir = 1
        full *= at
    val += dir*full/4
    a[0] = val
    print(a)
