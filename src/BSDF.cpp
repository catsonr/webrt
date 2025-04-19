#include "BSDF.h"

int BSDF::numComponents() const
{
    return nBxDFs;
}

bool BSDF::hasShadingGeometry() const
{
    return (nn.x != ng.x ||
            nn.y != ng.y ||
            nn.z != ng.z
    );
}

Vector BSDF::worldToLocal(const Vector& v) const
{
    return Vector(dot(v, sn), dot(v, tn), dot(v, Vector(nn)));
}

Vector BSDF::localToWorld(const Vector& v) const
{
    return Vector(
        sn.x * v.x + tn.x * v.y + nn.x * v.z,
        sn.y * v.x + tn.y * v.y + nn.y * v.z,
        sn.z * v.x + tn.z * v.y + nn.z * v.z
    );
}

Spectrum BSDF::f(const Vector& woW, const Vector& wiW, BxDFType flags) const
{
    Vector wi = worldToLocal(wiW);
    Vector wo = worldToLocal(woW);
    
    if(dot(wiW, Vector(ng)) * dot(woW, Vector(ng)) > 0) // ignore BTDFs
        flags = BxDFType(flags & ~BSDF_TRANSMISSION);
    else // ignore BRDFs
        flags = BxDFType(flags & ~BSDF_REFLECTION);
    
    Spectrum f = 0.0f;
    for(int i = 0; i < nBxDFs; i++)
        if(bxdfs[i]->matchesFlags(flags))
            f += bxdfs[i]->f(wo, wi);
    
    return f;
}
