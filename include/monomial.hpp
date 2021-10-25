#ifndef __MONOMIAL_H__
#define __MONOMIAL_H__
#include <iostream>
#include <cmath>
#include <string>

class Monomial
{
private:
  int coefficient_;
  int exponent_;

public:
  Monomial(int coefficient = 0, int exponent = 0);
  ~Monomial();
  int evaluate(int value) const;
  int getCoefficient() const;
  int getExponent() const;
  void setCoefficient(int coefficient);
  void setExponent(int exponent);

  Monomial operator+(const Monomial &operand);
  Monomial operator*(const Monomial &operand);
  friend std::ostream &operator<<(std::ostream &sout, const Monomial &monomial);
  friend std::istream &operator>>(std::istream &sin, Monomial &monomial);
};

#endif // __MONOMIAL_H__