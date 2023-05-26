// biseccion (es la misma logica que busqueda binaria)

#define ld long double

ld raizAux(ld inf, ld sup, int n) {
    ld m = (inf + sup)/2;
    ld err = 0.0001;
    if ((m-err)*(m-err) < n && (m+err)*(m+err) > n) return m;
    if (m*m < n) return raizAux(m, sup, n);
    return raizAux(inf, m, n);
}

ld raiz(int n) {
    return raizAux(1,n,n);
}