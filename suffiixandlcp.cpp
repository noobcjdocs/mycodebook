/* SUFFIX ARRAY AND LCP */
vl sa;
struct suffix
{
    lo index, rank[2];
};
lo cmp(struct suffix a, struct suffix b)
{   if(a.rank[0]==b.rank[0])if(a.rank[1]==b.rank[1])return a.index < b.index;else return a.rank[1] < b.rank[1];
    else return a.rank[0]<b.rank[0];
}
vector<lo> buildSuffixArray(string txt, lo n)
{
    struct suffix suffixes[n];
    REP(0,n)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
    }
    sort(suffixes, suffixes+n, cmp);
    lo ind[n];
    for (lo k = 4; k < 2*n; k = k*2)
    {
        lo rank = 0;
        lo prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;
        REP(1,n)
        {
            if (suffixes[i].rank[0] == prev_rank &&
                    suffixes[i].rank[1] == suffixes[i-1].rank[1])
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            }
            else
            {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }
        REP(0,n)
        {
            lo nextindex = suffixes[i].index + k/2;
            suffixes[i].rank[1] = (nextindex < n)?
                                  suffixes[ind[nextindex]].rank[0]: -1;
        }
        sort(suffixes, suffixes+n, cmp);
    }
    vector<lo>suffixArr;
    REP(0,n)suffixArr.push_back(suffixes[i].index);
    return  suffixArr;
}
vl kasai(string tx, lo n){
    vl lcp(n,0);vl invsuf(n,0);
    REP(0,n)invsuf[sa[i]]=i;
    lo k=0;
    REP(0,n){
        if(invsuf[i]==n-1){k=0;continue;}
        lo j = sa[invsuf[i]+1];
        while(i+k<n && j+k<n && tx[i+k]==tx[j+k])k++;
        lcp[invsuf[i]]=k;
        if(k>0)k--;
    }
    return lcp;
}
/*       */
