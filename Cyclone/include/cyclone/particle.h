#pragma once

#include "core.h"
#include "precision.h"

class Particle
{
protected:
    cyclone::Vec3 position; // Holds the linear position of the particle in world space
    cyclone::Vec3 velocity; // Holds the linear velocity of the particle in world space
    
    /**
     * Acceleration is the only attribute that can be set directly, position and velocity
     * will be determined by an integrator function. This is because the 2nd law of motion 
     * (F = ma) => a = F/m
     * implies that only acceleration can be changed directly and so velocity and postion
     * will change as a result of the change in acceleration.
    **/
    cyclone::Vec3 acceleration;
    
    /**
     * Holds the amount of damping applied to linear
     * motion. Damping is required to remove energy added
     * through numerical instability in the integrator.
    **/
    cyclone::real damping;

    /**
     * Holds the inverse of the mass of the particle. It
     * is more useful to hold the inverse mass because
     * integration is simpler, and because in real-time
     * simulation it is more useful to have objects with
     * infinite mass (immovable) than zero mass
     * (completely unstable in numerical simulation)
    **/
    cyclone::real inverseMass;

    /**
     * Integrates the particle forward in time by the given amount.
     * This function uses a Newton-Euler integration method, which
     * is a linear approximation to the correct integral. For this
     * reason it may be inaccurate in some cases.
     **/
    void integrate(cyclone::real duration);
};
