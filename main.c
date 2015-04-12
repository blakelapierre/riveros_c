/*
# ************************************************************************* #
#          Copyright (c) 2015 Oscar Riveros. All rights reserved.           #
#                         oscar.riveros@gmail.com                           #
#                                                                           #
#      Without any restriction, Oscar Riveros reserve the rights,           #
# patents and marketing this knowledge and directly derived from this work. #
# ************************************************************************* #
*/

// C port from Python by Blake La Pierre <blakelapierre@gmail.com>

#include <gmp.h>
#include <stdio.h>

void meta_sum(mpz_t sum, mpz_t * u, mpz_t n) {
  size_t bits = mpz_sizeinbase(n, 2);

  printf("\nn: ");
  mpz_out_str(stdout, 2, n);
  printf("\nbits: %d", bits);

  for(size_t i = 0; i < bits; i++) {
    int bit = mpz_tstbit(n, i);
    printf("\ngot bit %d for index %d", bit, i);
    if (bit == 1) mpz_add(sum, sum, u[i]);
  }
}

int rf(mpz_t * u, mpz_t length, mpz_t zero, mpz_t one, mpz_t two) {
  mpz_t * no_solution;

  int iterations = 0;

  mpz_t k;
  mpz_init(k);
  for (k; mpz_cmp(k, length) < 0; mpz_add(k, k, one)) {
    mpz_t a; mpz_init(a);
    mpz_t b; mpz_init(b);

    printf("\n\nk: ");
    mpz_out_str(stdout, 10, k);
    printf("\nlength: ");
    mpz_out_str(stdout, 10, length);
    printf("\n");

    mpz_pow_ui(a, two, mpz_get_ui(k));      mpz_sub(a, a, one);
    mpz_pow_ui(b, two, mpz_get_ui(length)); mpz_sub(b, b, one);

    while (mpz_cmp(a, b) < 0) {
      printf("\n\na: ");
      mpz_out_str(stdout, 10, a);
      printf("\nb: ");
      mpz_out_str(stdout, 10, b);

      mpz_t ab;
      mpz_init(ab);
      mpz_add(ab, a, b);

      printf("\na+b: ");
      mpz_out_str(stdout, 10, ab);

      mpz_t q; mpz_init(q);
      mpz_t r; mpz_init(r);

      mpz_fdiv_qr(q, r, ab, two);

      printf("\nq: ");
      mpz_out_str(stdout, 10, q);

      printf("\nr: ");
      mpz_out_str(stdout, 10, r);

      // calculate meta_level here

      mpz_t s; mpz_init(s);
      meta_sum(s, u, q);

      printf("\ns: ");
      mpz_out_str(stdout, 10, s);

      iterations++;

      if (mpz_cmp(s, zero) < 0) mpz_add(a, q, one);
      else if (mpz_cmp(s, zero) > 0) mpz_set(b, q);
      else {
        printf("\niterations: %d\n", iterations);
        printf("\nsolution found: ");
        mpz_out_str(stdout, 2, q);
        printf("\n");
        return 1;
      }
    }
  }

  printf("\niterations: %d\n", iterations);
  printf("\nno solution!\n");

  return 0;
};

int main() {
  mpz_t zero;
  mpz_t one;
  mpz_t two;

  mpz_init(zero);
  mpz_init_set_ui(one, 1);
  mpz_init_set_ui(two, 2);

  // 10
  // 01
  // 11

  // 100
  // 110
  // 111
  // 101
  // 011
  // 001

  // mpz_t u[3];
  // mpz_init_set_si(u[0], -2);
  // mpz_init_set_si(u[1], -1);
  // mpz_init_set_si(u[2], 3);

  // mpz_t u[3];
  // mpz_init_set_si(u[0], -2);
  // mpz_init_set_si(u[1], 1);
  // mpz_init_set_si(u[2], 2);

  // mpz_t u[3];
  // mpz_init_set_si(u[0], -2);
  // mpz_init_set_si(u[1], -1);
  // mpz_init_set_si(u[2], 1);

  // mpz_t u[3];
  // mpz_init_set_si(u[0], -2);
  // mpz_init_set_si(u[1], -99998);
  // mpz_init_set_si(u[2], 100000);

  // mpz_t u[4];
  // mpz_init_set_si(u[0], -2);
  // mpz_init_set_si(u[1], -1);
  // mpz_init_set_si(u[2], 4);
  // mpz_init_set_si(u[3], 5);

  // mpz_t u[4];
  // mpz_init_set_si(u[0], -6);
  // mpz_init_set_si(u[1], 2);
  // mpz_init_set_si(u[2], 5);
  // mpz_init_set_si(u[3], 6);

  // mpz_t u[5];
  // mpz_init_set_si(u[0], -2);
  // mpz_init_set_si(u[1], -1);
  // mpz_init_set_si(u[2], 4);
  // mpz_init_set_si(u[3], 5);
  // mpz_init_set_si(u[4], 100);

  // mpz_t u[6];
  // mpz_init_set_si(u[0], -2);
  // mpz_init_set_si(u[1], -1);
  // mpz_init_set_si(u[2], 4);
  // mpz_init_set_si(u[3], 5);
  // mpz_init_set_si(u[4], -99999);
  // mpz_init_set_si(u[5], 100000);


  mpz_t u[9];
  mpz_init_set_si(u[0], -17);
  mpz_init_set_si(u[1], -15);
  mpz_init_set_si(u[2], -12);
  mpz_init_set_si(u[3], -5);
  mpz_init_set_si(u[4], -4);
  mpz_init_set_si(u[5], 6);
  mpz_init_set_si(u[6], 12);
  mpz_init_set_si(u[7], 16);
  mpz_init_set_si(u[8], 18);

  // 101111110
  // 001000100
  // 010010100

  // mpz_t n;

  // mpz_init_set_ui(n, 0x6);

  // mpz_t sum; mpz_init_set_ui(sum, 0);

  // printf("sum: ");
  // mpz_out_str(stdout, 10, sum);

  // meta_sum(sum, u, n);

  // printf("sum: ");
  // mpz_out_str(stdout, 10, sum);

  printf("\nzero: ");
  mpz_out_str(stdout, 10, zero);

  printf("\none: ");
  mpz_out_str(stdout, 10, one);

  printf("\ntwo: ");
  mpz_out_str(stdout, 10, two);


  mpz_t length; mpz_init_set_ui(length, sizeof(u) / sizeof(u[0]));
  rf(u, length, zero, one, two);

  return 0;
}