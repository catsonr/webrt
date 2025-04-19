#ifndef BSDF_H
#define BSDF_H

#include "DifferentialGeometry.h"
#include "Normal.h"
#include "BxDF.h"

#define MAX_BxDFS 8

class BSDF
{
public:
    /* PUBLIC MEMBERS */    
    const DifferentialGeometry dgShading;
    const float eta;

    /* CONSTRUCTORS */
    BSDF(const DifferentialGeometry& dg, const Normal& n_geometry, float e) :
        dgShading(dg),
        eta(e),
        ng(n_geometry),
        nn(dgShading.nn),
        sn(normalize(dgShading.dpdu)),
        tn(cross(Vector(nn), sn)),
        nBxDFs(0)
    {}
    
    /* PUBLIC METHODS */
    int numComponents() const;
    int numComponents(BxDFType flags) const; // currently unimplimented
    
    bool hasShadingGeometry() const;

    Vector worldToLocal(const Vector& v) const;
    Vector localToWorld(const Vector& v) const;

    Spectrum f(const Vector& woW, const Vector& wiW, BxDFType flags) const;
    Spectrum rho(BxDFType flags = BSDF_ALL) const;
    Spectrum rho(const Vector& wo, BxDFType flags = BSDF_ALL) const;
    
    /* INLINES */
    inline void add(BxDF* b)
    {
        assert(nBxDFs < MAX_BxDFS);

        bxdfs[nBxDFs++] = b;
    }

private:
    Normal nn, ng;
    Vector sn, tn;
    int nBxDFs;
    BxDF* bxdfs[MAX_BxDFS];
};

#endif 