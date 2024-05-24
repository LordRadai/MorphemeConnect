#pragma once

/*
* Copyright (c) 2011 NaturalMotion Ltd. All rights reserved.
*
* Not to be copied, adapted, modified, used, distributed, sold,
* licensed or commercially exploited in any manner without the
* written consent of NaturalMotion.
*
* All non public elements of this software are the confidential
* information of NaturalMotion and may not be disclosed to any
* person nor used for any purpose not expressly approved by
* NaturalMotion in writing.
*
*/

#ifndef NM_HELPERS_H
#define NM_HELPERS_H

//----------------------------------------------------------------------------------------------------------------------
#include "AutoGenerated/NetworkForceInclude.h"
#include "NMGeomUtils/NMGeomUtils.h"

//----------------------------------------------------------------------------------------------------------------------

#ifndef NM_BEHAVIOUR_LIB_NAMESPACE
  #error behaviour library namespace undefined
#endif

namespace MR
{
  class InstanceDebugInterface;
}

namespace NM_BEHAVIOUR_LIB_NAMESPACE
{

/// Used to return the result of the closest point of approach functions
struct ClosestPointOfApproachData
{
  NMP::Vector3 positionA; ///< The position of A at the closest point of approach
  NMP::Vector3 positionB; ///< The position of B at the closest point of approach
  float time; ///< The time at which the closest point of approach happens - always positive
  float dist; ///< The separation between A and B at the time of closest approach
};

//----------------------------------------------------------------------------------------------------------------------
/// Returns the closest point of approach data for two objects starting at positionA and positionB,
/// moving with constant velocities velocityA and velocityB. If the objects are not moving relative
/// to one another then the time will be zero.
ClosestPointOfApproachData calculateClosestPointOfApproach(
const NMP::Vector3& positionA, const NMP::Vector3& positionB, 
const NMP::Vector3& velocityA, const NMP::Vector3& velocityB);

//----------------------------------------------------------------------------------------------------------------------
/// Returns the closest point of approach data for two objects starting at positionA and positionB,
/// moving with initial velocity velocityA and constant acceleration accelerationA, and velocityB
/// respectively. If the objects are not moving relative to one another then the time will be zero.
ClosestPointOfApproachData calculateClosestPointOfApproach(
  const NMP::Vector3& positionA,
  const NMP::Vector3& positionB,
  const NMP::Vector3& velocityA,
  const NMP::Vector3& velocityB,
  const NMP::Vector3& accelerationA,
  MR::InstanceDebugInterface* pDebugDrawInst);

//----------------------------------------------------------------------------------------------------------------------
/// Projects a point onto a line (-segment) which is defined by a point on the line (origin) and a direction vector.
/// If minDist or maxDist are specified then the projected point will be clamped to the given distance relative to
/// the line's "origin"
NMP::Vector3 projectPointOntoLineSegment(
  const NMP::Vector3& origin, 
  const NMP::Vector3& lineDir, 
  const NMP::Vector3& point, 
  float minDist = 1.0f, 
  float maxDist = -1.0f);

//----------------------------------------------------------------------------------------------------------------------
/// Maps a scalar input value from [0, 1] to [r, g, b] values (also in [0, 1]) such that the resulting colour
/// corresponds to a point on the rainbow colour map.
NMP::Vector3 getRainbowColourMapped(float f);

//----------------------------------------------------------------------------------------------------------------------
/// Mapping from [0, 1]->[0, 1], in which the output value changes according to the ascending leg of the sin function
/// in the interval [min, max]. The output is 0 or 1 for lower and higher input values respectively
float sinusoidalUnitBlend(float val, float min, float max);

//----------------------------------------------------------------------------------------------------------------------
/// Mapping from [0, 1]->[0, 1], in which the output value changes from startAmpl to endAmpl according to a linear ramp
/// in the interval [start, end], while being startAmpl or endAmpl for lower and higher input values respectively
float linearRampBlend(float val, float start, float end, float startAmpl, float endAmpl);

//----------------------------------------------------------------------------------------------------------------------
/// Returns coordinate frame with y up and x forwards, of a support transform relative to the feet using the supplied
/// leg transforms. 
/// 
/// This function assumes that all the legs contribute equally. This provides more predictable behaviour than
/// trying to use the limb balance weights.
NMP::Matrix34 getSupportTransformRelRoot(const NMP::Matrix34* legEndRelRoot, const uint32_t numLegs);

//----------------------------------------------------------------------------------------------------------------------
/// Returns coordinate frame with y up and x forwards, of a support transform relative to the feet using the supplied
/// leg transforms. 
///
/// The up (y) direction of the calculated transform is determined by the upDir argument, rather than the supplied leg 
/// transforms. This function assumes that all the legs contribute equally. This provides more predictable behaviour than
/// trying to use the limb balance weights.
NMP::Matrix34 getSupportTransformRelRoot(
  const NMP::Matrix34* legEndRelRoot,
  const uint32_t numLegs,
  const NMP::Vector3& upDir);

}

#endif
