def reverse_word(m, start, end):
    i = 0
    while i < (end-start)/2:
        tmp = m[start+i]
        m[start+i] = m[end-1-i]
        m[end-1-i] = tmp
        i+=1

def reverse_words(message):
    s = bytearray(message)
    start = 0
    i = 0
    while(i < len(s)):
        if s[i] is ord(" "):
            #check for space index
            reverse_word(s, start, i)
            start = i+1
        i+=1
    reverse_word(s, start, i)
    i = 0
    while(i < len(s)/2):
        tmp = s[i]
        s[i] = s[-1-i]
        s[-1-i] = tmp
        i+=1
    return str(s)

print reverse_words("use the force young skywalker must")
print reverse_words("successfully working is this")
