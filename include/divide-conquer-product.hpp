#ifndef __DIVIDECONQUERPRODUCT_H__
#define __DIVIDECONQUERPRODUCT_H__
#include "polynomial-product.hpp"

class DivideAndConquerProduct : public PolynomialProduct
{
  Polynomial run(const Polynomial &operandA, const Polynomial &operandB);
};

#endif // __DIVIDECONQUERPRODUCT_H__