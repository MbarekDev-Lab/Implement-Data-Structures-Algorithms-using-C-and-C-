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

void cleanup(struct Polynomial *p)
{
    free(p->terms);
    p->terms = NULL;
    p->n = 0;
}

int main()
{
    struct Polynomial p1;
    create(&p1);

    printf("\nPolynomial: ");
    display(p1);

    cleanup(&p1);
    return 0;
}

//*═══════════════════════════════════════════════════════
//DEMO COMPLETE
//═══════════════════════════════════════════════════════* /
    /**
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