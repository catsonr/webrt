#ifndef BXDF_H
#define BXDF_H

#include "Spectrum.h"

enum BxDFType
{
    BSDF_REFLECTION   = 1 << 0,
    BSDF_TRANSMISSION = 1 << 1,
    BSDF_DIFFUSE      = 1 << 2,
    BSDF_GLOSSY       = 1 << 3,
    BSDF_SPECULAR     = 1 << 4,
    
    BSDF_ALL_TYPES = BSDF_DIFFUSE | BSDF_GLOSSY | BSDF_SPECULAR,
    BSDF_ALL_REFLECTION = BSDF_REFLECTION | BSDF_ALL_TYPES,
    BSDF_ALL_TRANSMISION = BSDF_TRANSMISSION | BSDF_ALL_TYPES,
    
    BSDF_ALL = BSDF_ALL_REFLECTION | BSDF_ALL_TRANSMISION,
};

class BxDF
{
public:
    /* PUBLIC MEMBERS */
    const BxDFType type;
    
    /* CONSTRUCTORS */
    BxDF(BxDFType t) :
        type(t)
    {}
    
    /* PUBLIC VIRTUAL FUNCTIONS */
    virtual Spectrum f(const Vector& wo, const Vector& wi) const = 0;
    virtual Spectrum sample_f(const Vector& wo, Vector* wi, float u1, float u2, float* pdf) const;
    virtual Spectrum rho(const Vector& wo, int nSamples = 16, float* samples = NULL) const;
    
    /* PUBLIC FUNCTIONS */
    constexpr bool matchesFlags(BxDFType flags) const
    {
        return (type & flags) == type;
    }
};

#endif