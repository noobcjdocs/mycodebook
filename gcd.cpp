lo gcd(lo a, lo b){
    while(b){
        lo y = a%b;
        a = b; b = y;
    }
    return a;
}
