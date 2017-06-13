/*knuthmorrispratt helper*/
lo arr[1000006];

lo knuthmorrispratt(string str)
{
    lo no;
    arr[0]=no=-1;
    REP(1,str.length()){
        while(no>-1 && str[no+1]!=str[i]) no=arr[no];
        if(str[i]==str[no+1]) no++;
        arr[i]=no;
    }
    return 0;
}
/*      */
