/*
   a Spectrum object's only purpose is to hold a representation of an SPD
   a SPD, or Spectral Power Distribution describes how much energy is released at a given wavelength

   rt::SPECTRUM_COLORSAMPLES in globals.h is the number of samples all spectrums use
*/

#ifndef SPECTRUM_H
#define SPECTRUM_H

#include "globals.h"

class Spectrum
{
public:
    // public data
    static const int CIEstart = 360;
    static const int CIEend = 830;
    static const int nCIE = CIEend - CIEstart + 1;
    static const float CIE_X[nCIE];
    static const float CIE_Y[nCIE];
    static const float CIE_Z[nCIE];

    // constructors 
    Spectrum(float v = 0.0f);
    Spectrum(float colorSamples[rt::SPECTRUM_COLORSAMPLES]);

    // public functions
    void addWeighted(float w, const Spectrum& s);
    void XYZ(float XYZ[3]) const;
    
    float y() const;

    bool isBlack() const;
    bool isNaN() const;

    Spectrum sqrt() const;
    Spectrum pow(const Spectrum& e) const;
    Spectrum clamp(float min = 0.0f, float max = INFINITY) const;
    Spectrum fromXYZ(float x, float y, float z);
    
    // inline operator overloads
    inline Spectrum operator+(const Spectrum& s2)
    {
        Spectrum ret = *this;
        
        for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
            ret.c[i] += s2.c[i];
        
        return ret;
    }
    inline Spectrum& operator+=(const Spectrum& s2)
    {
        for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
            c[i] += s2.c[i];
        
        return *this;
    }
    inline Spectrum operator-(const Spectrum& s2)
    {
        Spectrum ret = *this;
        
        for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
            ret.c[i] -= s2.c[i];
        
        return ret;
    }
    inline Spectrum& operator-=(const Spectrum& s2)
    {
        for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
            c[i] -= s2.c[i];
        
        return *this;
    }
    inline bool operator==(const Spectrum& s2) const
    {
        for(int i = 0; i < rt::SPECTRUM_COLORSAMPLES; i++)
            if(c[i] != s2.c[i])
                return false;

        return true;
    }
    inline bool operator<(const Spectrum& s2) const
    {
        return y() < s2.y();
    }
    inline bool operator<=(const Spectrum& s2) const
    {
        return y() <= s2.y();
    }
    inline bool operator>(const Spectrum& s2) const
    {
        return y() > s2.y();
    }
    inline bool operator>=(const Spectrum& s2) const
    {
        return y() >= s2.y();
    }

private:
    float c[rt::SPECTRUM_COLORSAMPLES];
    
    float XWeight[rt::SPECTRUM_COLORSAMPLES] = {
        0.412453f, 0.357580f, 0.180423f
    };
    float YWeight[rt::SPECTRUM_COLORSAMPLES] = {
        0.212671f, 0.715160f, 0.072169f
    };
    float ZWeight[rt::SPECTRUM_COLORSAMPLES] = {
        0.019334f, 0.119193f, 0.950227f
    };
};

#endif