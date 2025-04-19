#include "WhittedIntegrator.h"

// implimentation incomplete!
Spectrum WhittedIntegrator::Li(const Scene* scene, const RayDifferential& ray, const Sample* sample, float* alpha) const
{
    Intersection intersection;
    Spectrum L(0.0f);
    bool hitSomething = scene->intersects(ray, &intersection);
    
   if(!hitSomething)
   {
        if(alpha)
            *alpha = 0.0f;
       
        for(int i = 0; i < scene->lights.size(); i++)
            L += scene->lights[i]->Le(ray);
            
        if(alpha && !L.isBlack())
            *alpha = 1.0f;
        
        return L;
   }
   else
   {
        if (alpha)
            *alpha = 1.0f;
        
        //evaluate BSDF at hit point
        BSDF* bsdf = intersection.getBSDF(ray);

        // initialize common variables for whitted integrators 
        const Point& p = bsdf->dgShading.p;
        const Normal& n = bsdf->dgShading.nn;
        Vector wo = -ray.d;
        
        // compute emmitted light if ray hit area light source
        L += intersection.Le(wo);


        // add contribution of each light source (pg 35)
        Vector wi;
        for(int i = 0; i < scene->lights.size(); i++)
        {
            VisibilityTester visibility;
            Spectrum Li = scene->lights[i]->sample_L(p, &wi, &visibility);
            if(Li.isBlack()) continue;
            /*
            Spectrum f = bsdf->f(wo, wi); // pbrt says to call as f(wo, wi), but does not define function with those parameters .........
            if(Li.isBlack() && visibility.unoccluded(scene))
            {
                L += Li * f * dotAbs(wi, Vector(n)) * visibility.transmittance(scene);
            }
            */
        }
        
        if(rayDepth++ < maxDepth)
        {
            // trace rays for specular reflection
        }
        
        rayDepth--;
   }

   return L;
}