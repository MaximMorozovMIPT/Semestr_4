#include <iostream>
#include "Vector2.h"
using namespace std;

void TestFunc(Vector2 first, Vector2 second);

int main()
{
    Vector2 first(1, 1);
    Vector2 second(2, -2);
    TestFunc(first, second);
}

void TestFunc(Vector2 first, Vector2 second)
{
    cout << "First v = " << first << endl;
    cout << "Second v = " << second << endl;

    cout << "Sum v = " << second + first << endl;
    cout << "Substr v = " << second - first << endl;

    cout << "First mult v1 by 2 = " << first * 2 << endl;
    cout << "Second mult v2 by 2 = " << 2 * second << endl;

    cout << "Division second by 2 = " << second / 2 << endl;

    cout << "Scal prod v1*v2 = " << first * second << endl;
    cout << "Scal prod v2*v1 = " << second * first << endl;

    cout << "Vect prod v1*v2 = " << (first ^ second) << endl;
    cout << "Vect prod v2*v1 = " << (second ^ first) << endl;

    cout << "Square length v1 = " << first.SquareLen() << endl;
    cout << "Square length v2 = " << second.SquareLen() << endl;

    cout << "Length v1 = " << first.Len() << endl;
    cout << "Length v2 = " << second.Len() << endl;

    cout << "Norm v1 = " << first.Norm() << endl;
    cout << "Norm v2 = " << second.Norm() << endl;

    cout << "Perp v1 = " << first.Perpendicular() << endl;
    cout << "Perp v2 = " << second.Perpendicular() << endl;

    cout << "Minus v1 = " << -first << endl;
    cout << "Minus v2 = " << -second << endl;

    cout << "Rotate v1 45* = " << first.GetRotated(90) << endl;

    Vector2 variable;
    cin >> variable;

    cout << "Variable v = " << variable << endl;
    cout << "Variable v+(1,1) = " << (variable+={1,1}) << endl;
    cout << "Variable v-(1,1) = " << (variable-={1,1}) << " must be equal to start variable" << endl;

    variable.Rotate(90);
    cout << "Variable rotated 90* v = " << variable << endl;
    variable.Rotate(90);
    cout << "Variable rotated 90* v = " << variable << endl;
    variable.Rotate(90);
    cout << "Variable rotated 90* v = " << variable << endl;
    variable.Rotate(90);
    cout << "Variable rotated 90* v = " << variable << endl;
}
