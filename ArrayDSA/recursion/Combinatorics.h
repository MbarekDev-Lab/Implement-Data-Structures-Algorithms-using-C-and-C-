//
//  Combinatorics.h
//  Essential
//
//  Created by M'Barek Benraiss on 18.12.25.
//

#ifndef Combinatorics_h
#define Combinatorics_h

#include <vector>

inline long long gcd(long long a, long long b)
{
    while (b != 0)
    {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

inline long long nCr(int n, int r)
{
    if (n < 0 || r < 0 || r > n)
    {
        return 0;
    }

    if (r > n - r)
    {
        r = n - r;
    }

    long long result = 1;
    for (int i = 1; i <= r; ++i)
    {
        long long numerator = static_cast<long long>(n - r + i);
        long long denominator = i;
        long long g1 = gcd(numerator, denominator);
        numerator /= g1;
        denominator /= g1;
        long long g2 = gcd(result, denominator);
        result /= g2;
        denominator /= g2;
        result *= numerator;
    }
    return result;
}

inline long long nCrRecursive(int n, int r)
{
    if (n < 0 || r < 0 || r > n)
        return 0;
    if (r == 0 || r == n)
        return 1;

    if (r > n - r)
        r = n - r;

    static std::vector<std::vector<long long>> memo; // memo[n][r]

    if ((int)memo.size() <= n)
        memo.resize(n + 1);
    if ((int)memo[n].size() <= r)
        memo[n].resize(r + 1, -1);

    long long &cached = memo[n][r];
    if (cached != -1)
        return cached;

    cached = nCrRecursive(n - 1, r - 1) + nCrRecursive(n - 1, r);
    return cached;
}

#endif /* Combinatorics_h */
