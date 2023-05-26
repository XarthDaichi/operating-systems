int raiz_int(int n) {
    int inf = 1;
    int sup = n;
    int m = (inf + sup) /2;
    while(inf + 1 < sup) {
        if (m + m > n) sup = m;
        else inf = m;
        m = (inf + sup)/2;
    } 
    return inf;
}