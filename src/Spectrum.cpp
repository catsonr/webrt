#include "Spectrum.h"

// constructors
Spectrum::Spectrum(float v)
{
    for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
        c[i] = v;
}
Spectrum::Spectrum(float colorSamples[rt::SPECTRUM_COLORSAMPLES])
{
    for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
        c[i] = colorSamples[i];
}

// public functions
void Spectrum::addWeighted(float w, const Spectrum& s)
{
    for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
        c[i] += w * s.c[i];
}

void Spectrum::XYZ(float XYZ[3]) const
{
    XYZ[0] = XYZ[1] = XYZ[2] = 0.0f;
    
    for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
    {
        XYZ[0] += c[i] * XWeight[i];
        XYZ[1] += c[i] * YWeight[i];
        XYZ[2] += c[i] * ZWeight[i];
    }
}

float Spectrum::y() const
{
    float v = 0.0f;
    for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
        v += YWeight[i] * c[i];
    
    return v;
}

bool Spectrum::isBlack() const
{
    for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
        if(c[i] != 0.0f) return false;

    return true;
}

bool Spectrum::isNaN() const
{
    for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
        if(isnan(c[i])) return true;

    return false;
}

Spectrum Spectrum::sqrt() const
{
    Spectrum ret;

    for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
        ret.c[i] = sqrtf(c[i]);
    
    return ret;
}

Spectrum Spectrum::pow(const Spectrum& e) const
{
    Spectrum ret;

    for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
        ret.c[i] = c[i] > 0 ? powf(c[i], e.c[i]) : 0.0f;
    
    return ret;
}

Spectrum Spectrum::clamp(float min, float max) const
{
    Spectrum ret;

    for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
        ret.c[i] = rt::clamp(c[i], min, max);
    
    return ret;
}

Spectrum Spectrum::fromXYZ(float x, float y, float z)
{
    float colorSamples[3];

    c[0] = 3.240479f*x + -1.537150f*y + -0.498535f*z;
    c[1] = -0.969256f*x + 1.875991f*y + 0.041556f*z;
    c[2] = 0.055648f*x + -0.204043f*y + 1.057311f*z;
    
    return Spectrum(colorSamples);
}