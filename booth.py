/* booths algorithm for lexographically minimum string rotation */
def boothsmin(str):
    str += str     
    f = [-1] * len(str)
    k = 0
    for j in xrange(1,len(str)):
        sj = str[j]
        i = f[j-k-1]
        while i != -1 and sj != str[k+i+1]:
            if sj < str[k+i+1]:
                k = j-i-1
            i = f[i]
        if sj != str[k+i+1]: # if sj != str[k+i+1], then i == -1 
            if sj < str[k]: # k+i+1 = k
                k = j
            f[j-k] = -1
        else:
            f[j-k] = i+1
    return k
/* wikipedia link : https://en.wikipedia.org/wiki/Lexicographically_minimal_string_rotation */
/*   */
