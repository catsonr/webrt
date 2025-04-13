#include "Transform.h"

Transform::Transform()
{
    const std::shared_ptr<Mat4> _m = std::make_shared<Mat4>();

    m = _m;
    mInv = _m; // inverse of identity is identity
}
Transform::Transform(const std::shared_ptr<Mat4> _m) :
    m(_m),
    mInv(_m->inverse())
{}
Transform::Transform(const std::shared_ptr<Mat4> _m, const std::shared_ptr<Mat4> _mInv) :
    m(_m),
    mInv(_mInv)
{}
Transform::Transform(float _m[4][4])
{
    m = std::make_shared<Mat4>(
        _m[0][0], _m[0][1], _m[0][2], _m[0][3],
        _m[1][0], _m[1][1], _m[1][2], _m[1][3],
        _m[2][0], _m[2][1], _m[2][2], _m[2][3],
        _m[3][0], _m[3][1], _m[3][2], _m[3][3]);
    mInv = m->inverse();
}

Transform Transform::translate(const Vector &delta)
{
    std::shared_ptr<Mat4> mNew = std::make_shared<Mat4>(
        1, 0, 0, delta.x,
        0, 1, 0, delta.y,
        0, 0, 1, delta.z,
        0, 0, 0, 1
    );
    std::shared_ptr<Mat4> mInvNew = std::make_shared<Mat4>(
        1, 0, 0, -delta.x,
        0, 1, 0, -delta.y,
        0, 0, 1, -delta.z,
        0, 0, 0, 1
    );
    
    return Transform(mNew, mInvNew);
}
Transform Transform::scale(float x, float y, float z)
{
    std::shared_ptr<Mat4> mNew = std::make_shared<Mat4>(
        x, 0, 0, 0,
        0, y, 0, 0,
        0, 0, z, 0,
        0, 0, 0, 1
    );
    std::shared_ptr<Mat4> mInvNew = std::make_shared<Mat4>(
        1.0f / x, 0, 0, 0,
        0, 1.0f / y, 0, 0,
        0, 0, 1.0f / z, 0,
        0, 0, 0, 1
    );
    
    return Transform(mNew, mInvNew);
}
//Transform Transform::rotateX(float angle) {}
//Transform Transform::rotateY(float angle) {}
//Transform Transform::rotateZ(float angle) {}
//Transform Transform::rotate(const Vector &axis, float angle) {}

Transform Transform::lookAt(const Point &pos, const Point &lookingAt, const Vector &up)
{
    float _m[4][4];

    // initialize fourth column
    _m[0][3] = pos.x;
    _m[1][3] = pos.y;
    _m[2][3] = pos.z;
    _m[3][3] = 1;
    
    // initialize first three columns
    Vector dir = -normalize(lookingAt - pos); // negative defines "forward" as down -z
    Vector right = cross(dir, normalize(up));
    Vector newUp = cross(right, dir);
    _m[0][0] = right.x;
    _m[1][0] = right.y;
    _m[2][0] = right.z;
    _m[3][0] = 0.0f;
    _m[0][1] = newUp.x;
    _m[1][1] = newUp.y;
    _m[2][1] = newUp.z;
    _m[3][1] = 0.0f;
    _m[0][2] = dir.x;
    _m[1][2] = dir.y;
    _m[2][2] = dir.z;
    _m[3][2] = 0.0f;

    std::shared_ptr<Mat4> camToWorld = std::make_shared<Mat4>(_m);
    
    return Transform(camToWorld->inverse(), camToWorld);
}

void Transform::print() const
{
}