#include <assert.h>
#include "cyclone/particle.h"

void Particle::integrate(cyclone::real duration)
{
    // We don't integrate things with infinite mass.
    if (inverseMass <= 0.0f) return;

    assert(duration > 0.0);

    // Update position
    position.addScaledVec(velocity, duration);

    // Work out the acceleration from the force.
    // Wel'll add to this vector when we come to generate forces.
    cyclone::Vec3 resultingAcc;
    resultingAcc = acceleration;

    // Update linear Velocity from acceleration
    velocity.addScaledVec(resultingAcc, duration);
    
    // Impose drag
    velocity *= real_pow(damping, duration);

    // Clear the forces
    //clearAccumulator();
}


