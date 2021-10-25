#include "../include/classic-product.hpp"

Polynomial ClassicProduct::run(const Polynomial &operandA, const Polynomial &operandB) 
{
  std::vector<Monomial> monomialsA = operandA.getMonomials();
  std::vector<Monomial> monomialsB = operandB.getMonomials();
  std::vector<Monomial> resultantMonomials;
  for (int i = 0; i < monomialsA.size(); i++)
    for (int j = 0; j < monomialsB.size(); j++)
    {
      resultantMonomials.push_back(monomialsA[i] * monomialsB[j]);
    } 
    
  return Polynomial(resultantMonomials);
}
