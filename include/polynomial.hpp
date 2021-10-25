#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__
#include <vector>
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include "monomial.hpp"
#include "polynomial-product.hpp"

class PolynomialProduct;
class Polynomial
{
private:
  std::vector<Monomial> monomials_; 
  PolynomialProduct *productStrategy_;

public:
  Polynomial();
  Polynomial(const std::vector<int> &coefficients);
  Polynomial(const std::vector<Monomial> &monomials);
  ~Polynomial();
  void setProductStrategy(PolynomialProduct *productStrategy);
  const std::vector<Monomial>& getMonomials() const;
  void simplify();
  void generateRandom(const int degree, const int range);
  void addNullMonomials(int degree = -1);
  int getDegree() const;

  Polynomial operator*(const Monomial &operand);
  Polynomial operator*(const Polynomial &operand);
  Polynomial operator+(const Polynomial &operand);
  Polynomial operator-(const Polynomial &operand);
  friend std::ostream &operator<<(std::ostream &sout, const Polynomial &polynomial);
};

#endif // __POLYNOMIAL_H__