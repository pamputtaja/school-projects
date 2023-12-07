// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}

double power(double base, double exp) {
    double total = base;
    if ( exp == 0 ) {
        return 1;
    }
    if ( exp == 1 ) {
        return base;
    } else {
        for ( int i = 2; i <= exp; i++ ) {
            total = total * base;
        }
        return total;
    }

}
