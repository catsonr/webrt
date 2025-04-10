#include "Mat4.h"

Mat4::Mat4()
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            if(i == j) m[i][j] = 1.0f;
            else m[i][j] = 0.0f;
        }
    }
}
Mat4::Mat4(float _m[ELEMS])
{
    for (int i = 0; i < ELEMS; i++)
        m[(int)(i / COLS)][i % COLS] = _m[i];
}
Mat4::Mat4(float _m[ROWS][COLS])
{
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            m[i][j] = _m[i][j];
        }
    }
}
Mat4::Mat4(float t00, float t01, float t02, float t03,
           float t10, float t11, float t12, float t13,
           float t20, float t21, float t22, float t23,
           float t30, float t31, float t32, float t33)
{
    m[0][0] = t00;
    m[0][1] = t01;
    m[0][2] = t02;
    m[0][3] = t03;
    m[1][0] = t10;
    m[1][1] = t11;
    m[1][2] = t12;
    m[1][3] = t13;
    m[2][0] = t20;
    m[2][1] = t21;
    m[2][2] = t22;
    m[2][3] = t23;
    m[3][0] = t30;
    m[3][1] = t31;
    m[3][2] = t32;
    m[3][3] = t33;
}

std::shared_ptr<Mat4> Mat4::transpose() const
{
    return std::make_shared<Mat4>(m[0][0], m[1][0], m[2][0], m[3][0],
                                  m[0][1], m[1][1], m[2][1], m[3][1],
                                  m[0][2], m[1][2], m[2][2], m[3][2],
                                  m[0][3], m[1][3], m[2][3], m[3][3]);
}
std::shared_ptr<Mat4> Mat4::multiply(const std::shared_ptr<Mat4> m1, const std::shared_ptr<Mat4> m2) const
{
    float r[4][4];

    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
        {
            r[i][j] = m1->m[i][0] * m2->m[0][j] +
                      m1->m[i][1] * m2->m[1][j] +
                      m1->m[i][2] * m2->m[2][j] +
                      m1->m[i][3] * m2->m[3][j];
        }
    }
    
    return std::make_shared<Mat4>(r);
}

// chatgpt code
// returns new matrix (identity matrix) if matrix is un-invertable 
std::shared_ptr<Mat4> Mat4::inverse() const
{
    // Make a copy of this matrix.
    Mat4 t(*this);
    // s is initialized as the identity matrix by default.
    Mat4 s;

    // Gauss-Jordan elimination.
    for (int i = 0; i < 4; i++) {
        // Step 1: Select pivot row with the largest absolute value in column i.
        int pivot = i;
        float pivotSize = fabs(t.m[i][i]);
        for (int j = i + 1; j < 4; j++) {
            float temp = fabs(t.m[j][i]);
            if (temp > pivotSize) {
                pivot = j;
                pivotSize = temp;
            }
        }
        // Matrix is singular if the pivot element is zero.
        if (pivotSize == 0.0f) {
            return std::make_shared<Mat4>();
        }
        // Step 2: Swap rows if necessary.
        if (pivot != i) {
            for (int k = 0; k < 4; k++) {
                std::swap(t.m[i][k], t.m[pivot][k]);
                std::swap(s.m[i][k], s.m[pivot][k]);
            }
        }
        // Step 3: Scale pivot row to have pivot = 1.
        float pivotVal = t.m[i][i];
        for (int k = 0; k < 4; k++) {
            t.m[i][k] /= pivotVal;
            s.m[i][k] /= pivotVal;
        }
        // Step 4: Eliminate the other entries in column i.
        for (int j = 0; j < 4; j++) {
            if (j != i) {
                float factor = t.m[j][i];
                for (int k = 0; k < 4; k++) {
                    t.m[j][k] -= factor * t.m[i][k];
                    s.m[j][k] -= factor * s.m[i][k];
                }
            }
        }
    }
    // Return the inverted matrix wrapped in a shared pointer.
    return std::make_shared<Mat4>(s.m);
}