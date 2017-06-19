lo LCE(vl lcp, vl invsuf, lo n,lo L, lo R)
{
    if (L == R)return (n-L);
    lo low = min(invsuf[L], invsuf[R]);
    lo high = max(invsuf[L], invsuf[R]);
    lo length = lcp[low];
    REP(low+1, high)if (lcp[i] < length)length = lcp[i];
    return (length);
}
