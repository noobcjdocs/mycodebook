vl machers(string text)
{
    vl ve;
    lo N = text.length();
    if(N == 0)
        return ve;
    N = 2*N + 1;
    vl L(N,0);
    L[0] = 0;
    L[1] = 1;
    lo C = 1;
    lo R = 2;
    lo i = 0;
    lo iMirror;
    lo expand = -1;
    lo diff = -1;
    lo maxLPSLength = 0;
    lo maxLPSCenterPosition = 0;
    lo start = -1;
    lo end = -1;
    REP(2,N)
    {
        iMirror  = 2*C-i;
        expand = 0;
        diff = R - i;
        if(diff > 0)
        {
            if(L[iMirror] < diff)
                L[i] = L[iMirror];
            else if(L[iMirror] == diff && i == N-1)
                L[i] = L[iMirror];
            else if(L[iMirror] == diff && i < N-1)
            {
                    L[i] = L[iMirror];
                    expand = 1;
            }
            else if(L[iMirror] > diff)
            {
                L[i] = diff;
                expand = 1;
            }
        }
        else
        {
            L[i] = 0;
            expand = 1;
        }
        if (expand == 1)
        {
            while (((i + L[i]) < N && (i - L[i]) > 0) &&
                ( ((i + L[i] + 1) % 2 == 0) ||
                (text[(i + L[i] + 1)/2] == text[(i-L[i]-1)/2] )))
            {
                L[i]++;
            }
        }
        if(L[i] > maxLPSLength)
        {
            maxLPSLength = L[i];
            maxLPSCenterPosition = i;
        }
        if (i + L[i] > R)
        {
            C = i;
            R = i + L[i];
        }
    }
    start = (maxLPSCenterPosition - maxLPSLength)/2;
    end = start + maxLPSLength - 1;
    //start and end of the longest palindrome //
    return L;
}

/* original source code : http://www.geeksforgeeks.org/manachers-algorithm-linear-time-longest-palindromic-substring-part-3-2/ */
