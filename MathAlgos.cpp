//
// Created by kapildd on 9/21/17.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <cstdio>
using namespace std;

vector<bool> is_prime;

void sieve_of_eratosthenes(int n) {
    is_prime.resize(n+1, true);
    is_prime[0] = is_prime[1] = false;
    for(int i=0; i<=n; i++) {
        if(!is_prime[i]) continue;
        for(int j=i*i; j>=0 && j<=n; j+=i) {
            is_prime[j] = false;
        }
    }
}

long long modular_exponentiation(long long base, long long pow, long long mod) {
    long long result = 1;
    while(pow) {
        if(pow&1) result = (result * base) % mod;
        base = (base * base) % mod;
        pow>>=1;
    }
    return result;
}

int extended_gcd(int a, int m, int& x, int& y) {
    //ax + my = gcd(a, m)
    //mx' + (a-m*floor(a/m))y' = gcd(a, m)
    //==> ay' + m(x'-y'.floor(a/m)) = gcd(a, m)
    //==> x = y' and y = (x'-y'.floor(a/m))
    if(m == 0) {
        x = 1; y = 0;
        return a;
    }
    int result = extended_gcd(m, a%m, x, y);
    int x_dash = x, y_dash = y;
    x = y_dash;
    y = x_dash-y_dash*(a/m);
    return result;
}
int main() {
    int n = 100003, x, y, inverse; //n is prime
    sieve_of_eratosthenes(n);
    for(int i=1; i<1000; i++) {
        //x = i^-1 mod n
        extended_gcd(i, n, x, y);
        if(x<0) x+=n;
        //Also, inverse = i^(n-2) mod n
        inverse = modular_exponentiation(i, n-2, n);
        //Check that they match
        assert(inverse == x);
        //Check property of primes in modulo ring
        if(i>2 && is_prime[i])
            assert(modular_exponentiation(2, i-1, i)==1LL);
    }
    return 0;
}