#include <iostream>
#include "Vector.h"
#include "Matrix.h"
#include "Exceptions.h"
using std::cout;
using std::cin;
using std::endl;
using std::cerr;

void Vector_Testing() {
    cout << "-------- Vector testing --------" << endl << endl;

    cout << "1) Constructors and operators <<, >>" << endl;
    cout << "Enter vector v1:" << endl;
    Vector v1;
    cin >> v1;
    Vector v2(v1);
    cout << "We built vector v2 as a copy of vector v1: v2 = " << v2 << endl << endl;

    cout << "2) Operators" << endl << endl;

    cout << "1. Operator =" << endl;
    Vector v3(v1.getSize());
    cout << "Vector v1 = " << v1 << ", vector v3 = " << v3 << endl;
    v3 = v1;
    cout << "After operation v3 = v1" << endl;
    cout << "Vector v1 = " << v1 << ", vector v3 = " << v3 << endl << endl;
        
    try {
        cout << "2. Operator +=" << endl;
        cout << "Enter vector v2 (please, input size = size of v1):" << endl;
        cin >> v2;
        cout << "Vector v1 = " << v1 << ", vector v2 = " << v2 << endl;
        v2 += v1;
        cout << "After operation v2 += v1" << endl;
        cout << "Vector v1 = " << v1 << ", vector v2 = " << v2 << endl << endl;

        cout << "3. Operator -=" << endl;
        cout << "Vector v1 = " << v1 << ", vector v2 = " << v2 << endl;
        v2 -= v1;
        cout << "After operation v2 -= v1" << endl;
        cout << "Vector v1 = " << v1 << ", vector v2 = " << v2 << endl << endl;

        cout << "4. Operator + (binary)" << endl;
        v3 -= v3;
        cout << "Vector v1 = " << v1 << ", vector v2 = " << v2 << ", vector v3 = " << v3 << endl;
        v3 = v1 + v2;
        cout << "After operation v3 = v1 + v2" << endl;
        cout << "Vector v1 = " << v1 << ", vector v2 = " << v2 << ", vector v3 = " << v3 << endl << endl;

        cout << "5. Operator + (unary)" << endl;
        v3 -= v3;
        cout << "Vector v1 = " << v1 << ", vector v3 = " << v3 << endl;
        v3 = +v1;
        cout << "After operation v3 = +v1" << endl;
        cout << "Vector v1 = " << v1 << ", vector v3 = " << v3 << endl << endl;

        cout << "6. Operator - (binary)" << endl;
        v3 -= v3;
        cout << "Vector v1 = " << v1 << ", vector v2 = " << v2 << ", vector v3 = " << v3 << endl;
        v3 = v1 - v2;
        cout << "After operation v3 = v1 - v2" << endl;
        cout << "Vector v1 = " << v1 << ", vector v2 = " << v2 << ", vector v3 = " << v3 << endl << endl;

        cout << "7. Operator - (unary)" << endl;
        v3 -= v3;
        cout << "Vector v1 = " << v1 << ", vector v3 = " << v3 << endl;
        v3 = -v1;
        cout << "After operation v3 = -v1" << endl;
        cout << "Vector v1 = " << v1 << ", vector v3 = " << v3 << endl << endl;

        cout << "8. Operator * by a number" << endl;
        v3 -= v3;
        cout << "Vector v1 = " << v1 << ", vector v3 = " << v3 << endl;
        v3 = v1 * 5.;
        cout << "After operation v3 = v1 * 5" << endl;
        cout << "Vector v1 = " << v1 << ", vector v3 = " << v3 << endl;
        v3 -= v3;
        cout << "Erasing vector v3: v3 = " << v3 << endl;
        v3 = 5. * v1;
        cout << "After operation v3 = 5 * v1" << endl;
        cout << "Vector v1 = " << v1 << ", vector v3 = " << v3 << endl << endl;

        cout << "9. Operator * between vectors" << endl;
        double result = 0.;
        cout << "Vector v1 = " << v1 << ", vector v2 = " << v2 << endl;
        result = v1 * v2;
        cout << "After operation result = v1 * v2;" << endl;
        cout << "Vector v1 = " << v1 << ", vector v2 = " << v2 << ", result = " << result << endl << endl;
    }
    catch (InCompatibleDimException& exception) {
        cerr << exception.what() << endl << endl;
    }    

    cout << "10. Operator []" << endl;
    cout << "Vector v1 = " << v1 << endl;
    cout << "Input index: ";
    int index;
    cin >> index;
    try {
        cout << "v1[" << index << "] = " << v1[index] << endl << endl;
    }
    catch (OutOfRangeException &exception) {
        cerr << exception.what() << endl << endl;
    }

    cout << "3) getSize and getLength" << endl << endl;
    cout << "Vector v1 = " << v1 << endl;
    cout << "Size of v1 = " << v1.getSize() << endl;
    cout << "Length of v1 = " << v1.getLength() << endl << endl;
}

void Matrix_Testing() {
    cout << "-------- CSRMatrix testing --------" << endl << endl;

    cout << "1) Constructors and operators <<, >>" << endl << endl;
    cout << "Enter size n of matrix m_default: ";
    int n;
    cin >> n;
    CSRMatrix m_default(n, 0);
    cout << "Default matrix m_default:" << endl;
    cout << m_default << endl;
    cout << "Enter matrix m1: " << endl;
    CSRMatrix m1;
    cin >> m1;
    cout << m1 << endl;
    CSRMatrix m2(m1);
    cout << "We built matrix m2 as a copy of matrix m1:" << endl;
    cout << m2 << endl;

    cout << "2) Operators" << endl << endl;

    cout << "1. Operator =" << endl << endl;
    CSRMatrix m3(m1.getSize(), m1.getNonZeros());
    cout << "Matrix m1:" << endl;
    cout << m1 << endl;
    m3 = m1;
    cout << "After operation m3 = m1" << endl;
    cout << "Matrix m3:" << endl;
    cout << m3 << endl;

    cout << "2. Operator * by a number" << endl << endl;
    cout << "Matrix m1:" << endl;
    cout << m1 << endl;
    m2 = m1 * 5.;
    m3 = 5. * m1;
    cout << "After operations m2 = m1 * 5; m3 = 5 * m1" << endl;
    cout << "Matrix m2:" << endl;
    cout << m2 << endl;
    cout << "Matrix m3:" << endl;
    cout << m3 << endl;

    cout << "3) getSize and getNonZeros" << endl << endl;
       
    cout << "Matrix m1:" << endl;
    cout << m1 << endl;
    cout << "Size m1 = " << m1.getSize() << endl;
    cout << "Number of non zero elements = " << m1.getNonZeros() << endl << endl;
}

void Multiple_Testing() {
    {
        cout << "-------- Vector x Matrix --------" << endl << endl;

        cout << "Operator vector * matrix" << endl << endl;
        cout << "Enter vector v1:" << endl;
        Vector v1;
        cin >> v1;
        cout << "Enter matrix m1: " << endl;
        CSRMatrix m1;
        cin >> m1;
        cout << m1 << endl;
        Vector result(v1);
        try {
            result = v1 * m1;
        }
        catch (InCompatibleDimException& exception) {
            cerr << exception.what() << endl << endl;
        }
        catch (std::exception& exception) {
            cerr << "Error: other std::exception occurred " << exception.what() << endl << endl;
        }
        cout << "v1 * m1 = " << result << endl << endl;

        cout << "Operator matrix * vector" << endl << endl;
        try {
            result = m1 * v1;
        }
        catch (InCompatibleDimException& exception) {
            cerr << exception.what() << endl << endl;
        }
        catch (std::exception& exception) {
            cerr << "Error: other std::exception occurred " << exception.what() << endl << endl;
        }
        cout << "m1 * v1 = " << result << endl << endl;
    }

    cout << "-------- Now let's try to solve: res = - c1 * m1 * (v1 - c2 * v2) + v3 * c3 --------" << endl << endl;
    double c1, c2, c3;
    Vector v1, v2, v3;
    CSRMatrix m1;
    cout << "c1 = ";
    cin >> c1;
    cout << "c2 = ";
    cin >> c2;
    cout << "c3 = ";
    cin >> c3;
    cout << "Vector v1:" << endl;
    cin >> v1;
    cout << "Vector v2:" << endl;
    cin >> v2;
    cout << "Vector v3:" << endl;
    cin >> v3;
    cout << "Matrix m1:" << endl;
    cin >> m1;
    Vector res(v1.getSize());

    try {
        res = -c1 * m1 * (v1 - c2 * v2) + v3 * c3;
    }
    catch (InCompatibleDimException& exception){
        cerr << exception.what() << endl;
    }
    catch (OutOfRangeException& exception) {
        cerr << exception.what() << endl;
    }
    catch (std::exception& exception) {
        cerr << "Error: other std::exception occurred " << exception.what() << endl;
    }
}

int main()
{
    Vector_Testing();
    Matrix_Testing();
    Multiple_Testing();
    return 0;
}