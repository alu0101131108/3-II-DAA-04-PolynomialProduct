#include "../include/polynomial.hpp"
Polynomial::Polynomial() : productStrategy_(NULL), monomials_({})
{}

Polynomial::Polynomial(const std::vector<int> &coefficients):
productStrategy_(NULL) 
{
  for (int i = 0; i < coefficients.size(); i++)
  {
    if (coefficients[i] != 0)
    {
      monomials_.push_back(Monomial(coefficients[i], i));
    }
  }
}

Polynomial::Polynomial(const std::vector<Monomial> &inputMonomials):
productStrategy_(NULL), monomials_(inputMonomials)  
{
  simplify();
}

Polynomial::~Polynomial() 
{
  // if (productStrategy_ != NULL)
  // {
  //   delete productStrategy_;
  // }
}

void Polynomial::setProductStrategy(PolynomialProduct *productStrategy)
{
  if (productStrategy_ != NULL)
  {
    delete productStrategy_;
  }
  productStrategy_ = productStrategy;
}

const std::vector<Monomial>& Polynomial::getMonomials() const 
{
  return monomials_;
}

void Polynomial::simplify()
{
  if (monomials_.size() > 0)
  {
    std::vector<Monomial> unsimplifiedMonomials = monomials_;
    monomials_.clear();
    monomials_.push_back(unsimplifiedMonomials[0]);
    for (int i = 1; i < unsimplifiedMonomials.size(); i++)
    {
      Monomial currentToInsert = unsimplifiedMonomials[i];
      // Monomials with coef = 0 will be ignored.
      if (currentToInsert.getCoefficient() != 0)  
      {
        for (int j = 0; j < monomials_.size(); j++)
        {
          // Placed inmediately previous to the first greater exp monomial. 
          if (currentToInsert.getExponent() < monomials_[j].getExponent())
          {
            monomials_.insert(monomials_.begin() + j, currentToInsert);
            break;
          }
          // Added to an existing monomial with same exp.
          else if (currentToInsert.getExponent() == monomials_[j].getExponent())
          {
            monomials_[j] = monomials_[j] + currentToInsert;
            break;
          }
          // There is no bigger monomial in monomials_.
          else if (j == monomials_.size() - 1)
          {
            monomials_.push_back(currentToInsert);
            break;
          }
        }
      }
    }
    if (monomials_[0].getCoefficient() == 0)
    {
      monomials_.erase(monomials_.begin());
    }
  }
}

void Polynomial::generateRandom(const int degree, const int range) 
{
  for (int i = 0; i <= degree; i++)
  {
    int randomCoef = rand() % (range * 2) - range;
    monomials_.push_back(Monomial(randomCoef, i));
  }
}

void Polynomial::addNullMonomials(int degree) 
{
  if (degree < 0)
  {
    degree = getDegree();
  }
  std::vector<Monomial> newMonomials;
  int j = 0;
  for (int i = 0; i <= degree; i++)
  {
    // Si no pongo j < monomials_.size(), hay un comportamiento inesperado.
    if (j < monomials_.size() && monomials_[j].getExponent() == i)
    {
      newMonomials.push_back(monomials_[j]);
      j++;
    }
    else
    {
      newMonomials.push_back(Monomial(0, i));
    }
  }
  monomials_ = newMonomials;
}

int Polynomial::getDegree() const
{
  return monomials_.size() > 0 ? monomials_[monomials_.size() - 1].getExponent() : 0;
}

Polynomial Polynomial::operator*(const Monomial &operand) 
{
  std::vector<Monomial> incrementedMonomials;
  for (int i = 0; i < monomials_.size(); i++)
  {
    incrementedMonomials.push_back(monomials_[i] * operand);
  }
  return Polynomial(incrementedMonomials);
}

Polynomial Polynomial::operator*(const Polynomial &operand)
{
  if (productStrategy_ == NULL)
  {
    std::cout << "ERROR: Polynomial::operator*(Polynomial)" << std::endl;
    std::cout << "No product strategy set" << std::endl;
    throw 510;
  }
  return productStrategy_->run(*this, operand); // '*this' is a reference to the object 'this' pointer is pointing.
}

Polynomial Polynomial::operator+(const Polynomial &operand) 
{
  std::vector<Monomial> monomials = monomials_;
  std::vector<Monomial> addedMonomials = operand.getMonomials();
  monomials.insert(monomials.end(), addedMonomials.begin(), addedMonomials.end());
  Polynomial result(monomials);
  return result;
}

Polynomial Polynomial::operator-(const Polynomial &operand) 
{
  std::vector<Monomial> monomials = monomials_;
  std::vector<Monomial> addedMonomials = operand.getMonomials();
  for (int i = 0; i < addedMonomials.size(); i++)
  {
    addedMonomials[i].setCoefficient(addedMonomials[i].getCoefficient() * -1);
  } 
  monomials.insert(monomials.end(), addedMonomials.begin(), addedMonomials.end());
  Polynomial result(monomials);
  return result;
}

std::ostream& operator<<(std::ostream &sout, const Polynomial &polynomial) 
{
  std::vector<Monomial> monomials = polynomial.getMonomials();
  for (int i = 0; i < monomials.size(); i++)
  {
    sout << monomials[i] << " ";
  }
  return sout;
}

