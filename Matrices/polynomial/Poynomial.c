#include <stdio.h>
#include <stdlib.h>

struct Term
{
    int coeff;
    int exp;
};

struct Polynomial
{
    struct Term *terms;
    int n;
};

void create(struct Polynomial *p)
{
    printf("Number of terms: ");
    scanf("%d", &p->n);
    p->terms = (struct Term *)malloc(p->n * sizeof(struct Term));

    printf("Enter all terms (coeff exp) in decreasing order of exponents:\n");
    for (int i = 0; i < p->n; i++)
    {
        printf("Term %d: ", i + 1);
        scanf("%d%d", &p->terms[i].coeff, &p->terms[i].exp);
    }
}

void display(struct Polynomial p)
{
    for (int i = 0; i < p.n; i++)
    {
        printf("%dx^%d", p.terms[i].coeff, p.terms[i].exp);
        if (i != p.n - 1)
            printf(" + ");
    }
    printf("\n");
}

struct Polynomial *add(struct Polynomial *p1, struct Polynomial *p2)
{
    /* data */
    int i, j, k;
    struct Polynomial *sum;

    sum = malloc(sizeof(struct Polynomial));
    sum->terms = malloc((p1->n + p2->n) * sizeof(struct Term));
    sum->n = p1->n + p2->n;

    i = j = k = 0;

    // this loop in to compare exponents of both polynomials and add accordingly
    while (i < p1->n && j < p2->n)
    {
        if (p1->terms[i].exp > p2->terms[j].exp)
        {
            sum->terms[k++] = p1->terms[i++];
        }
        else if (p1->terms[i].exp < p2->terms[j].exp)
        {
            sum->terms[k++] = p2->terms[j++];
        }
        else
        {
            sum->terms[k].exp = p1->terms[i].exp;
            sum->terms[k++].coeff = p1->terms[i++].coeff + p2->terms[j++].coeff;
        }
    }

    for (; i < p1->n; i++)
    {
        sum->terms[k++] = p1->terms[i];
    }
    for (; j < p2->n; j++)
    {
        sum->terms[k++] = p2->terms[j];
    }
    return sum;
};

void cleanup(struct Polynomial *p)
{
    free(p->terms);
    p->terms = NULL;
    p->n = 0;
}

int main()
{
    struct Polynomial p1, p2, *p3;

    create(&p1);
    create(&p2);
    p3 = add(&p1, &p2);

    printf("\nPolynomial 1: ");
    display(p1);
    printf("Polynomial 2: ");
    display(p2);
    printf("Sum: ");
    display(*p3);

    cleanup(&p1);
    cleanup(&p2);
    cleanup(p3);
    create(&p1);

    printf("\nPolynomial: ");
    display(p1);

    cleanup(&p1);
    return 0;
}

//*═══════════════════════════════════════════════════════
// DEMO COMPLETE code polynomial version C
// ═══════════════════════════════════════════════════════* /
/**
 *
 *
 benraiss@MacBookAir Matrices % clang -std=c17 -Wall -Wextra -o poynomial_cpp ./polynomial/Poynomial.c
benraiss@MacBookAir Matrices % ./poynomial_cpp
// add two polynomials :

Number of terms: 3
Enter all terms (coeff exp) in decreasing order of exponents:
Term 1: 1 5
Term 2: 1 3
Term 3: 1 1
Number of terms: 3
Enter all terms (coeff exp) in decreasing order of exponents:
Term 1: 1 4
Term 2: 1 2
Term 3: 1 0

Polynomial 1: 1x^5 + 1x^3 + 1x^1
Polynomial 2: 1x^4 + 1x^2 + 1x^0
Sum: 1x^5 + 1x^4 + 1x

 *
 *
 *
 * Number of terms: 4
Enter all terms (coeff exp) in decreasing order of exponents:
Term 1: 2 3
Term 2: 5 2
Term 3: 3 1
Term 4: 4 0

Polynomial: 2x^3 + 5x^2 + 3x^1 + 4x^0
 */