#include "gtest.h"
#include "polinom.h"

TEST(MonomTest, DefaultConstructor)
{
    Monom m;
    EXPECT_EQ(m.get_degree(), 0);
    EXPECT_EQ(m.getK(), 0);
}

TEST(MonomTest, ConstructorWithParameters)
{
    Monom m(123, 5.0);
    EXPECT_EQ(m.get_degree(), 123);
    EXPECT_EQ(m.getK(), 5.0);
}

TEST(MonomTest, ConstructorThrowsExceptionForInvalidDegree)
{
    EXPECT_THROW(Monom(1000, 5.0), std::domain_error);
}

TEST(MonomTest, GetXDegree)
{
    Monom m(123, 5.0);
    EXPECT_EQ(m.get_x_degree(), 1);
}

TEST(MonomTest, GetYDegree)
{
    Monom m(123, 5.0);
    EXPECT_EQ(m.get_y_degree(), 2);
}

TEST(MonomTest, GetZDegree)
{
    Monom m(123, 5.0);
    EXPECT_EQ(m.get_z_degree(), 3);
}

TEST(MonomTest, AdditionOfMonomialsWithSameDegree)
{
    Monom m1(123, 2.0);
    Monom m2(123, 3.0);

    Monom result = m1 + m2;

    EXPECT_EQ(result.get_degree(), 123);
    EXPECT_EQ(result.getK(), 5.0);
}

TEST(MonomTest, AdditionOfMonomialsWithDifferentDegreesThrowsException)
{
    Monom m1(123, 2.0);
    Monom m2(124, 3.0);

    EXPECT_THROW(m1 + m2, std::domain_error);
}

TEST(MonomTest, SubtractionOfMonomialsWithSameDegree)
{
    Monom m1(123, 5.0);
    Monom m2(123, 2.0);

    Monom result = m1 - m2;

    EXPECT_EQ(result.get_degree(), 123);
    EXPECT_EQ(result.getK(), 3.0);
}

TEST(MonomTest, SubtractionOfMonomialsWithDifferentDegreesThrowsException)
{
    Monom m1(123, 5.0);
    Monom m2(124, 2.0);

    EXPECT_THROW(m1 - m2, std::domain_error);
}

TEST(MonomTest, MultiplicationByScalar)
{
    Monom m(123, 3.0);
    Monom result = m * 2.0;

    EXPECT_EQ(result.get_degree(), 123);
    EXPECT_EQ(result.getK(), 6.0);
}

TEST(MonomTest, MultiplicationByZeroScalarResultsInZeroMonom)
{
    Monom m(123, 3.0);
    Monom result = m * 0.0;

    EXPECT_EQ(result.get_degree(), 0);
    EXPECT_EQ(result.getK(), 0.0);
}

TEST(MonomTest, MultiplicationOfMonomials)
{
    Monom m1(123, 3.0);
    Monom m2(124, 4.0);

    Monom result = m1 * m2;

    EXPECT_EQ(result.get_degree(), 247);
    EXPECT_EQ(result.getK(), 12.0);
}

TEST(MonomTest, MultiplicationOfMonomialsWithDegreeOverflowThrowsException)
{
    Monom m1(900, 2.0);
    Monom m2(200, 3.0);

    EXPECT_THROW(m1 * m2, std::domain_error);
}

TEST(PolinomTest, DefaultConstructorCreatesEmptyPolynomial)
{
    Polinom p;
    EXPECT_EQ(p.get_size(), 0);
}

TEST(PolinomTest, AddingSingleMonomToPolynomial)
{
    Polinom p;
    Monom m(123, 2.0);

    p.addMonom(m);

    EXPECT_EQ(p.get_size(), 1);
    EXPECT_EQ(p.get_first()->value.get_degree(), 123);
    EXPECT_EQ(p.get_first()->value.getK(), 2.0);
}

TEST(PolinomTest, AddingMultipleMonomsToPolynomial)
{
    Polinom p;
    Monom m1(123, 2.0);
    Monom m2(124, 3.0);

    p.addMonom(m1);
    p.addMonom(m2);

    EXPECT_EQ(p.get_size(), 2);
    EXPECT_EQ(p.get_first()->value.get_degree(), 124);
    EXPECT_EQ(p.get_first()->value.getK(), 3.0);
    EXPECT_EQ(p.get_first()->next->value.get_degree(), 123);
    EXPECT_EQ(p.get_first()->next->value.getK(), 2.0);
}

TEST(PolinomTest, AddingMonomsWithSameDegreeCombinesThem)
{
    Polinom p;
    Monom m1(123, 2.0);
    Monom m2(123, 3.0);

    p.addMonom(m1);
    p.addMonom(m2);

    EXPECT_EQ(p.get_size(), 1);
    EXPECT_EQ(p.get_first()->value.get_degree(), 123);
    EXPECT_EQ(p.get_first()->value.getK(), 5.0);
}

TEST(PolinomTest, AddingMonomWithZeroCoefficientDoesNotChangePolynomial)
{
    Polinom p;
    Monom m1(123, 2.0);
    Monom m2(124, 0.0);

    p.addMonom(m1);
    p.addMonom(m2);

    EXPECT_EQ(p.get_size(), 1);
    EXPECT_EQ(p.get_first()->value.get_degree(), 123);
    EXPECT_EQ(p.get_first()->value.getK(), 2.0);
}

TEST(PolinomTest, AddingTwoPolynomials)
{
    Polinom p1;
    Monom m1(123, 2.0);
    Monom m2(124, 3.0);
    p1.addMonom(m1);
    p1.addMonom(m2);

    Polinom p2;
    Monom m3(123, 1.0);
    Monom m4(125, 4.0);
    p2.addMonom(m3);
    p2.addMonom(m4);

    Polinom result = p1 + p2;

    EXPECT_EQ(result.get_size(), 3);
    EXPECT_EQ(result.get_first()->value.get_degree(), 125);
    EXPECT_EQ(result.get_first()->value.getK(), 4.0);
    EXPECT_EQ(result.get_first()->next->value.get_degree(), 124);
    EXPECT_EQ(result.get_first()->next->value.getK(), 3.0);
    EXPECT_EQ(result.get_first()->next->next->value.get_degree(), 123);
    EXPECT_EQ(result.get_first()->next->next->value.getK(), 3.0);
}

TEST(PolinomTest, MultiplyingPolynomialByScalar)
{
    Polinom p;
    Monom m1(123, 2.0);
    Monom m2(124, 3.0);

    p.addMonom(m1);
    p.addMonom(m2);

    Polinom result = p * 2.0;

    EXPECT_EQ(result.get_size(), 2);
    EXPECT_EQ(result.get_first()->value.get_degree(), 124);
    EXPECT_EQ(result.get_first()->value.getK(), 6.0);
    EXPECT_EQ(result.get_first()->next->value.get_degree(), 123);
    EXPECT_EQ(result.get_first()->next->value.getK(), 4.0);
}

TEST(PolinomTest, MultiplyingPolynomialByZeroResultsInEmptyPolynomial)
{
    Polinom p;
    Monom m1(123, 2.0);
    Monom m2(124, 3.0);

    p.addMonom(m1);
    p.addMonom(m2);

    Polinom result = p * 0.0;

    EXPECT_EQ(result.get_size(), 0);
}

TEST(PolinomTest, MultiplyingPolynomialByMonom)
{
    Polinom p;
    Monom m1(123, 2.0);
    Monom m2(124, 3.0);

    p.addMonom(m1);
    p.addMonom(m2);

    Monom m3(100, 2.0);
    Polinom result = p * m3;

    EXPECT_EQ(result.get_size(), 2);
    EXPECT_EQ(result.get_first()->value.get_degree(), 224);
    EXPECT_EQ(result.get_first()->value.getK(), 6.0);
    EXPECT_EQ(result.get_first()->next->value.get_degree(), 223);
    EXPECT_EQ(result.get_first()->next->value.getK(), 4.0);
}

TEST(PolinomTest, MultiplyingTwoPolynomials)
{
    Polinom p1;
    Monom m1(123, 2.0);
    Monom m2(124, 3.0);

    p1.addMonom(m1);
    p1.addMonom(m2);

    Polinom p2;
    Monom m3(100, 2.0);
    Monom m4(101, 1.0);

    p2.addMonom(m3);
    p2.addMonom(m4);

    Polinom result = p1 * p2;

    EXPECT_EQ(result.get_size(), 4);
    EXPECT_EQ(result.get_first()->value.get_degree(), 225);
    EXPECT_EQ(result.get_first()->value.getK(), 3.0);
    EXPECT_EQ(result.get_first()->next->value.get_degree(), 224);
    EXPECT_EQ(result.get_first()->next->value.getK(), 6.0);
    EXPECT_EQ(result.get_first()->next->next->value.get_degree(), 223);
    EXPECT_EQ(result.get_first()->next->next->value.getK(), 2.0);
    EXPECT_EQ(result.get_first()->next->next->next->value.get_degree(), 224);
    EXPECT_EQ(result.get_first()->next->next->next->value.getK(), 4.0);
}