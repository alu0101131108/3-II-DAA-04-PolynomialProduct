#include "../include/divide-conquer-product.hpp"

Polynomial DivideAndConquerProduct::run(const Polynomial &operandA, const Polynomial &operandB) 
{
  Polynomial normalizedOpA = operandA;
  Polynomial normalizedOpB = operandB;

  // Minimum cases.
  if (normalizedOpA.getMonomials().size() == 1)
  {
    return normalizedOpB * normalizedOpA.getMonomials()[0];
  }
  if (normalizedOpB.getMonomials().size() == 1)
  {
    return normalizedOpA * normalizedOpB.getMonomials()[0];
  }

  // Normalize both polynoms by adding null monomials untill bigger degree.
  int maxDegree = operandA.getDegree() > operandB.getDegree() ? operandA.getDegree() : operandB.getDegree();

  normalizedOpA.addNullMonomials(maxDegree);
  normalizedOpB.addNullMonomials(maxDegree);

  std::vector<Monomial> monomialsA = normalizedOpA.getMonomials();
  std::vector<Monomial> monomialsB = normalizedOpB.getMonomials();

  // Divide each polynom in two different ones.
  size_t halfSize = monomialsA.size() / 2;
  std::vector<Monomial> leftHalfA(monomialsA.begin(), monomialsA.begin() + halfSize);
  std::vector<Monomial> rightHalfA(monomialsA.begin() + halfSize, monomialsA.end());
  std::vector<Monomial> leftHalfB(monomialsB.begin(), monomialsB.begin() + halfSize);
  std::vector<Monomial> rightHalfB(monomialsB.begin() + halfSize, monomialsB.end());

  // Lower degree of right halves.
  for (int i = 0; i < rightHalfA.size(); i++)
  {
    rightHalfA[i].setExponent(i);
  }
  for (int i = 0; i < rightHalfB.size(); i++)
  {
    rightHalfB[i].setExponent(i);
  }

  // Create n/2 value, to undo the degree lowering.
  int nHalf = leftHalfA.size();
  Monomial undoNHalf(1, nHalf);
  Monomial undoN(1, nHalf * 2);

  // Create polynoms.
  Polynomial leftA(leftHalfA);
  Polynomial rightA(rightHalfA);
  Polynomial leftB(leftHalfB);
  Polynomial rightB(rightHalfB);
  
  // Normalize them and make the able to be multiplied.
  leftA.addNullMonomials(leftHalfA.size() - 1);
  rightA.addNullMonomials(rightHalfA.size() - 1);
  leftB.addNullMonomials(leftHalfB.size() - 1);
  rightB.addNullMonomials(rightHalfB.size() - 1);
  leftA.setProductStrategy(new DivideAndConquerProduct);
  rightA.setProductStrategy(new DivideAndConquerProduct);

  // Recursive calls for calculating final ecuation terms.
  Polynomial lefts = leftA * leftB;
  Polynomial rights = rightA * rightB;

  Polynomial rmSumA = leftA + rightA;
  Polynomial rmSumB = leftB + rightB;
  rmSumA.addNullMonomials(rightA.getDegree());
  rmSumB.addNullMonomials(rightB.getDegree());
  rmSumA.setProductStrategy(new DivideAndConquerProduct);
  Polynomial rm = rmSumA * rmSumB;

  return lefts + ((rm - lefts - rights) * undoNHalf) + (rights * undoN);
}
