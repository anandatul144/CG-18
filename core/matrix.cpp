#include <core/matrix.h>
#include<core/assert.h>
#include<math.h>
#include<core/scalar.h>

namespace rt {
    Matrix::Matrix(const Float4 & r1, const Float4 & r2, const Float4 & r3, const Float4 & r4)
    {
        this->r1 = r1;
        this->r2 = r2;
        this->r3 = r3;
        this->r4 = r4;

    }

    Float4 & Matrix::operator[](int idx)
    {
        switch (idx)
        {
        case 0:
            return this->r1;
        case 1:
            return this->r2;
        case 2:
            return this->r3;
        case 3:
            return this->r4;
        default:
            return this->r1;
        }
    }

    Float4 Matrix::operator[](int idx) const
    {
        switch (idx)
        {
        case 0:
            return this->r1;
        case 1:
            return this->r2;
        case 2:
            return this->r3;
        case 3:
            return this->r4;
        default:
            return this->r1;
        }
    }

    Matrix Matrix::operator+(const Matrix & b) const
    {
        return Matrix(this->r1 + b.r1, this->r2 + b.r2, this->r3 + b.r3, this->r4 + b.r4);
    }

    Matrix Matrix::operator-(const Matrix & b) const
    {
        return Matrix(this->r1 - b.r1, this->r2 - b.r2, this->r3 - b.r3, this->r4 - b.r4);
    }

    Matrix Matrix::transpose() const
    {
        Matrix result;

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                result[i][j] = (*this)[j][i];
            }
        }
        return result;
    }

    Matrix Matrix::invert() const {
        Matrix result;
        float m[4][4];
        m[0][0]=this->r1.x;m[0][1]=this->r1.y;m[0][2]=this->r1.z;m[0][3]=this->r1.w;
        m[1][0]=this->r2.x;m[1][1]=this->r2.y;m[1][2]=this->r2.z;m[1][3]=this->r2.w;
        m[2][0]=this->r3.x;m[2][1]=this->r3.y;m[2][2]=this->r3.z;m[2][3]=this->r3.w;
        m[3][0]=this->r4.x;m[3][1]=this->r4.y;m[3][2]=this->r4.z;m[3][3]=this->r4.w;

        //Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
        result[0][0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2] - m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2] + m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
        result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2] + m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2] - m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
        result[2][0] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1] - m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1] + m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
        result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1] + m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1] - m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

        float det = m[0][0] * result[0][0] + m[0][1] * result[1][0] + m[0][2] * result[2][0] + m[0][3] * result[3][0];
        if (det == 0)
            return Matrix::zero();

        result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2] + m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2] - m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
        result[1][1] = m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2] - m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2] + m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
        result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1] + m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1] - m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
        result[3][1] = m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1] - m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1] + m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
        result[0][2] = m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2] - m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2] + m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
        result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2] + m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2] - m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
        result[2][2] = m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1] - m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1] + m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
        result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1] + m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1] - m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
        result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2] + m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2] - m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
        result[1][3] = m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2] - m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2] + m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
        result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1] + m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1] - m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
        result[3][3] = m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1] - m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1] + m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

        result = result*(1.0f / det);
        return result;
    }

    bool Matrix::operator==(const Matrix & b) const
    {

    float m[4][4];
        m[0][0]=this->r1.x;m[0][1]=this->r1.y;m[0][2]=this->r1.z;m[0][3]=this->r1.w;
        m[1][0]=this->r2.x;m[1][1]=this->r2.y;m[1][2]=this->r2.z;m[1][3]=this->r2.w;
        m[2][0]=this->r3.x;m[2][1]=this->r3.y;m[2][2]=this->r3.z;m[2][3]=this->r3.w;
        m[3][0]=this->r4.x;m[3][1]=this->r4.y;m[3][2]=this->r4.z;m[3][3]=this->r4.w;

    for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
        {
            if(m[i][j]!=b[i][j])
                return false;
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix & b) const
    {
        float m[4][4];
        m[0][0]=this->r1.x;m[0][1]=this->r1.y;m[0][2]=this->r1.z;m[0][3]=this->r1.w;
        m[1][0]=this->r2.x;m[1][1]=this->r2.y;m[1][2]=this->r2.z;m[1][3]=this->r2.w;
        m[2][0]=this->r3.x;m[2][1]=this->r3.y;m[2][2]=this->r3.z;m[2][3]=this->r3.w;
        m[3][0]=this->r4.x;m[3][1]=this->r4.y;m[3][2]=this->r4.z;m[3][3]=this->r4.w;

        for (int i=0;i<4;i++)
        for (int j=0;j<4;j++)
        {
            if(m[i][j]!=b[i][j])
                return true;
        }
    return false;
    }

    Float4 Matrix::operator*(const Float4 & b) const
    {
        return Float4(dot(this->r1, b),
            dot(this->r2, b),
            dot(this->r3, b),
            dot(this->r4, b));

    }

    Vector Matrix::operator*(const Vector & b) const
    {
        float m[4][4];
        m[0][0]=this->r1.x;m[0][1]=this->r1.y;m[0][2]=this->r1.z;m[0][3]=this->r1.w;
        m[1][0]=this->r2.x;m[1][1]=this->r2.y;m[1][2]=this->r2.z;m[1][3]=this->r2.w;
        m[2][0]=this->r3.x;m[2][1]=this->r3.y;m[2][2]=this->r3.z;m[2][3]=this->r3.w;
        m[3][0]=this->r4.x;m[3][1]=this->r4.y;m[3][2]=this->r4.z;m[3][3]=this->r4.w;
        
        //const Matrix& m = *this;
        float a[4]={0};
        for (int i=0;i<4;i++)
            a[i]= m[i][0]*b.x+m[i][1]*b.y+m[i][2]*b.z+m[i][3]*0;

        return Vector(a[0],a[1],a[2]);
    }

    Point Matrix::operator*(const Point & b) const
    {
        float m[4][4];
        m[0][0]=this->r1.x;m[0][1]=this->r1.y;m[0][2]=this->r1.z;m[0][3]=this->r1.w;
        m[1][0]=this->r2.x;m[1][1]=this->r2.y;m[1][2]=this->r2.z;m[1][3]=this->r2.w;
        m[2][0]=this->r3.x;m[2][1]=this->r3.y;m[2][2]=this->r3.z;m[2][3]=this->r3.w;
        m[3][0]=this->r4.x;m[3][1]=this->r4.y;m[3][2]=this->r4.z;m[3][3]=this->r4.w;

        //const Matrix& m = *this;
        float a[4]={0};
        for (int i=0;i<4;i++)
            a[i]= m[i][0]*b.x+m[i][1]*b.y+m[i][2]*b.z+m[i][3]*1;
    
        return Point(a[0]/a[3],a[1]/a[3],a[2]/a[3]);

    }

    float Matrix::det() const
    {
        Matrix Result;
        float m[4][4];
        m[0][0]=this->r1.x;m[0][1]=this->r1.y;m[0][2]=this->r1.z;m[0][3]=this->r1.w;
        m[1][0]=this->r2.x;m[1][1]=this->r2.y;m[1][2]=this->r2.z;m[1][3]=this->r2.w;
        m[2][0]=this->r3.x;m[2][1]=this->r3.y;m[2][2]=this->r3.z;m[2][3]=this->r3.w;
        m[3][0]=this->r4.x;m[3][1]=this->r4.y;m[3][2]=this->r4.z;m[3][3]=this->r4.w;

        float tmp[12]; //* temp array for pairs 
        float src[16]; //* array of transpose source matrix *
        float det; //* determinant *
        //* transpose matrix *
        for (int i = 0; i < 4; i++)
        {
            src[i + 0 ] = m[i][0];
            src[i + 4 ] = m[i][1];
            src[i + 8 ] = m[i][2];
            src[i + 12] = m[i][3];
        }
    //* calculate pairs for first 8 elements (cofactors) *
        tmp[0] = src[10] * src[15];
        tmp[1] = src[11] * src[14];
        tmp[2] = src[9] * src[15];
        tmp[3] = src[11] * src[13];
        tmp[4] = src[9] * src[14];
        tmp[5] = src[10] * src[13];
        tmp[6] = src[8] * src[15];
        tmp[7] = src[11] * src[12];
        tmp[8] = src[8] * src[14];
        tmp[9] = src[10] * src[12];
        tmp[10] = src[8] * src[13];
        tmp[11] = src[9] * src[12];
        //* calculate first 8 elements (cofactors) *
        Result[0][0] = tmp[0]*src[5] + tmp[3]*src[6] + tmp[4]*src[7];
        Result[0][0] -= tmp[1]*src[5] + tmp[2]*src[6] + tmp[5]*src[7];
        Result[0][1] = tmp[1]*src[4] + tmp[6]*src[6] + tmp[9]*src[7];
        Result[0][1] -= tmp[0]*src[4] + tmp[7]*src[6] + tmp[8]*src[7];
        Result[0][2] = tmp[2]*src[4] + tmp[7]*src[5] + tmp[10]*src[7];
        Result[0][2] -= tmp[3]*src[4] + tmp[6]*src[5] + tmp[11]*src[7];
        Result[0][3] = tmp[5]*src[4] + tmp[8]*src[5] + tmp[11]*src[6];
        Result[0][3] -= tmp[4]*src[4] + tmp[9]*src[5] + tmp[10]*src[6];
        Result[1][0] = tmp[1]*src[1] + tmp[2]*src[2] + tmp[5]*src[3];
        Result[1][0] -= tmp[0]*src[1] + tmp[3]*src[2] + tmp[4]*src[3];
        Result[1][1] = tmp[0]*src[0] + tmp[7]*src[2] + tmp[8]*src[3];
        Result[1][1] -= tmp[1]*src[0] + tmp[6]*src[2] + tmp[9]*src[3];
        Result[1][2] = tmp[3]*src[0] + tmp[6]*src[1] + tmp[11]*src[3];
        Result[1][2] -= tmp[2]*src[0] + tmp[7]*src[1] + tmp[10]*src[3];
        Result[1][3] = tmp[4]*src[0] + tmp[9]*src[1] + tmp[10]*src[2];
        Result[1][3] -= tmp[5]*src[0] + tmp[8]*src[1] + tmp[11]*src[2];
        //* calculate pairs for second 8 elements (cofactors) *
        tmp[0] = src[2]*src[7];
        tmp[1] = src[3]*src[6];
        tmp[2] = src[1]*src[7];
        tmp[3] = src[3]*src[5];
        tmp[4] = src[1]*src[6];
        tmp[5] = src[2]*src[5];

        tmp[6] = src[0]*src[7];
        tmp[7] = src[3]*src[4];
        tmp[8] = src[0]*src[6];
        tmp[9] = src[2]*src[4];
        tmp[10] = src[0]*src[5];
        tmp[11] = src[1]*src[4];
        //* calculate second 8 elements (cofactors) *
        Result[2][0] = tmp[0]*src[13] + tmp[3]*src[14] + tmp[4]*src[15];
        Result[2][0] -= tmp[1]*src[13] + tmp[2]*src[14] + tmp[5]*src[15];
        Result[2][1] = tmp[1]*src[12] + tmp[6]*src[14] + tmp[9]*src[15];
        Result[2][1] -= tmp[0]*src[12] + tmp[7]*src[14] + tmp[8]*src[15];
        Result[2][2] = tmp[2]*src[12] + tmp[7]*src[13] + tmp[10]*src[15];
        Result[2][2] -= tmp[3]*src[12] + tmp[6]*src[13] + tmp[11]*src[15];
        Result[2][3] = tmp[5]*src[12] + tmp[8]*src[13] + tmp[11]*src[14];
        Result[2][3] -= tmp[4]*src[12] + tmp[9]*src[13] + tmp[10]*src[14];
        Result[3][0] = tmp[2]*src[10] + tmp[5]*src[11] + tmp[1]*src[9];
        Result[3][0] -= tmp[4]*src[11] + tmp[0]*src[9] + tmp[3]*src[10];
        Result[3][1] = tmp[8]*src[11] + tmp[0]*src[8] + tmp[7]*src[10];
        Result[3][1] -= tmp[6]*src[10] + tmp[9]*src[11] + tmp[1]*src[8];
        Result[3][2] = tmp[6]*src[9] + tmp[11]*src[11] + tmp[3]*src[8];
        Result[3][2] -= tmp[10]*src[11] + tmp[2]*src[8] + tmp[7]*src[9];
        Result[3][3] = tmp[10]*src[10] + tmp[4]*src[8] + tmp[9]*src[9];
        Result[3][3] -= tmp[8]*src[9] + tmp[11]*src[10] + tmp[5]*src[8];
        //* calculate determinant *
        det=src[0]*Result[0][0]+src[1]*Result[0][1]+src[2]*Result[0][2]+src[3]*Result[0][3];
        return det;

    }

    Matrix Matrix::zero()
    {
        return Matrix(Float4(0.0f, 0.0f, 0.0f, 0.0f),
            Float4(0.0f, 0.0f, 0.0f, 0.0f),
            Float4(0.0f, 0.0f, 0.0f, 0.0f),
            Float4(0.0f, 0.0f, 0.0f, 0.0f));
    }

    Matrix Matrix::identity()
    {
        return Matrix(Float4(1.0f, 0.0f, 0.0f, 0.0f),
            Float4(0.0f, 1.0f, 0.0f, 0.0f),
            Float4(0.0f, 0.0f, 1.0f, 0.0f),
            Float4(0.0f, 0.0f, 0.0f, 1.0f));
    }

    Matrix Matrix::system(const Vector & e1, const Vector & e2, const Vector & e3)
    {
        Float4 row1(e1.x, e2.x, e3.x, 0);
        Float4 row2(e1.y, e2.y, e3.y, 0);
        Float4 row3(e1.z, e2.z, e3.z, 0);
        Float4 row4(0, 0, 0, 1);
        return Matrix(row1, row2, row3, row4);
    }

    Matrix product(const Matrix & a, const Matrix & b)
    {
        Matrix output;
        for (int output_i = 0; output_i < 4; output_i++)
        {
            for (int output_j = 0; output_j < 4; output_j++)
            {
                output[output_i][output_j] = dot(a[output_i], b[output_j]);
            }
        }
        return output;
    }

    Matrix operator*(const Matrix & a, float scalar)
    {
        return Matrix(a.r1 * scalar, a.r2 * scalar, a.r3 * scalar, a.r4 * scalar);
    }

    Matrix operator*(float scalar, const Matrix & a)
    {
        return a * scalar;
    }

}

