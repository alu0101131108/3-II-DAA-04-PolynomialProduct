#ifndef __POLYNOMIALPRODUCT_H__
#define __POLYNOMIALPRODUCT_H__
#include "polynomial.hpp"

class Polynomial;
class PolynomialProduct
{
public:
  virtual Polynomial run(const Polynomial &operandA, const Polynomial &operandB) = 0;
};

#endif // __POLYNOMIALPRODUCT_H__