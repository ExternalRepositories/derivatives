#include "AlgoDiff.hpp"

#include <cstdlib>
#include <iostream>
#include <iomanip>
using namespace std;

namespace
{
bool isDoubleEqual(double x1, double x2)
{
    return abs(x1 - x2) < 1e-9;
}

void test1() // +, -
{
    algo_diff::Variable a(3.);
    a.setAsParameter(algo_diff::Parameter("a"));
    a += 2;
    a *= 4;
    algo_diff::Variable b(1.5);
    b.setAsParameter(algo_diff::Parameter("b"));
    algo_diff::Variable c = a - 3 * b;

    algo_diff::Derivatives results;
    c.computeDerivatives(results);
    bool ok = c.getValue() == 15.5;
    ok &= results.getDerivative(algo_diff::Parameter("a")) == 4.;
    ok &= results.getDerivative(algo_diff::Parameter("b")) == -3.;
    cout << "TEST1 : " << (ok ? "OK" : "FAILED") << endl;
}

void test2() // *
{
    using namespace algo_diff;
    Variable t(2.);
    t.setAsParameter("time");
    Variable r = (1 - t) * (2 + t * t);

    Derivatives results;
    r.computeDerivatives(results);
    bool ok = r.getValue() == -6.;
    ok &= results.getDerivative("time") == -10.;
    cout << "TEST2 : " << (ok ? "OK" : "FAILED") << endl;
}

void test3() // /
{
    using namespace algo_diff;
    Variable x(3.);
    x.setAsParameter("x");
    Variable z = (2 / x + 3) / ((1 + x) * (1 - x));

    Derivatives results;
    z.computeDerivatives(results);
    bool ok = isDoubleEqual(z.getValue(), -0.4583333333) ;
    ok &= isDoubleEqual(results.getDerivative("x"), 0.3715277778) ;
    cout << "TEST3 : " << (ok ? "OK" : "FAILED") << endl;
}

void test4() // user defined functions
{
    using namespace algo_diff;
    Variable x(3.141592657 / 4);
    x.setAsParameter("x");
    Variable s = 2 * sin(x);

    Derivatives results;
    s.computeDerivatives(results);
    bool ok = isDoubleEqual(s.getValue(), 1.414213564);
    ok &= isDoubleEqual(results.getDerivative("x"), 1.414213561);
    cout << "TEST4 : " << (ok ? "OK" : "FAILED") << endl;
}

void test5() // doc example
{
    using namespace algo_diff;
    Variable x(3.);
    x.setAsParameter("x");
    x += 4;
    Variable y(-2.);
    y.setAsParameter("y");
    x += 4;
    Variable z = (2 / sin(y) + 3) / ((1 + x) * (1 - x));
    z *= 2 * x;

    Derivatives results;
    z.computeDerivatives(results);
    bool ok = isDoubleEqual(z.getValue(), -0.1467582709);
    ok &= isDoubleEqual(results.getDerivative("x"), 0.01356402201);
    ok &= isDoubleEqual(results.getDerivative("y"), -0.1845466236);
    cout << "TEST5 : " << (ok ? "OK" : "FAILED") << endl;
}
}

void launchFunctionalTests()
{
    cout << "FUNCTIONAL TESTS:" << endl;
    test1();
    test2();
    test3();
    test4();
    test5();
}

