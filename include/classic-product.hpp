#ifndef __CLASSICPRODUCT_H__
#define __CLASSICPRODUCT_H__
#include "polynomial-product.hpp"

class ClassicProduct : public PolynomialProduct
{
  Polynomial run(const Polynomial &operandA, const Polynomial &operandB);
};

#endif // __CLASSICPRODUCT_H__