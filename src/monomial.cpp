#include "../include/monomial.hpp"

Monomial::Monomial(int coefficient, int exponent):
coefficient_(coefficient), exponent_(exponent) 
{}

Monomial::~Monomial() 
{}

int Monomial::evaluate(int value) const
{
  return coefficient_ * pow(value, exponent_);
}

int Monomial::getCoefficient() const
{
  return coefficient_;
}

int Monomial::getExponent() const
{
  return exponent_;
}

void Monomial::setCoefficient(int coefficient) 
{
  coefficient_ = coefficient;
}

void Monomial::setExponent(int exponent) 
{
  exponent_ = exponent;
}

Monomial Monomial::operator+(const Monomial &operand)
{
  if (exponent_ != operand.getExponent())
  {
    std::cout << "ERROR: Monomial::operator+(Monomial)" << std::endl;
    std::cout << "Can not add monomials with different degrees." << std::endl;
    std::cout << "Tried: " << *this << "+" << operand << std::endl;
    throw 110;
  }
  return Monomial(coefficient_ + operand.getCoefficient(), operand.getExponent());
}

Monomial Monomial::operator*(const Monomial &operand) 
{
  return Monomial(coefficient_ * operand.getCoefficient(), exponent_ + operand.getExponent());
}

std::istream& operator>>(std::istream &sin, Monomial &monomial) 
{
  std::string inputMonomial;
  sin >> inputMonomial;
  try 
  {
    int xPosition = inputMonomial.find("x");
    // From begining to char before 'x' found.
    int coefficient = stoi(std::string(inputMonomial, 0, xPosition));
    // From next char of 'x' to end.
    int exponent = stoi(std::string(inputMonomial, xPosition + 1, inputMonomial.size() - xPosition + 1));
    monomial.setCoefficient(coefficient);
    monomial.setExponent(exponent);
    return sin;
  }
  catch (...)
  {
    std::cout << "ERROR: operator>>(istream, Monomial)" << std::endl;
    std::cout << "Bad syntax for monomial at [" + inputMonomial + "]" << std::endl;
    throw 120;
  }
}

std::ostream& operator<<(std::ostream &sout, const Monomial &monomial) 
{
  std::string coefficient = std::to_string(monomial.getCoefficient());
  std::string exponent = std::to_string(monomial.getExponent());
  std::string sign = monomial.getCoefficient() >= 0 ? "+" : "";
  sout << sign + coefficient + "x" + exponent;
  return sout;
}


