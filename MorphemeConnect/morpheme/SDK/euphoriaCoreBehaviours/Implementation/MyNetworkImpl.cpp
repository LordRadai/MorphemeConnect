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

//----------------------------------------------------------------------------------------------------------------------
#include "MyNetwork.h"
#include "euphoria/erBody.h"
#include "euphoria/erLimb.h"
#include "euphoria/erDebugDraw.h"
#include "euphoria/erEuphoriaLogger.h"
#include "euphoria/erGravityCompensation.h"
#include "euphoria/erEuphoriaUserData.h"

#include "mrPhysicsScenePhysX3.h"

#define SCALING_SOURCE data->dimensionalScaling
#include "euphoria/erDimensionalScalingHelpers.h"

#include "NMPlatform/NMProfiler.h"

// module children dependencies
#include "myNetworkPackaging.h"
#include "BodySection.h"
#include "ReachForBodyBehaviourInterface.h"
#include "BalanceBehaviourInterface.h"
#include "EuphoriaRagdollBehaviourInterface.h"
#include "AnimateBehaviourInterface.h"
#include "ReachForBody.h"
#include "BodyFrame.h"
#include "Arm.h"
#include "Spine.h"
#include "Head.h"
#include "Leg.h"
#include "ArmBrace.h"
#include "LegBrace.h"
#include "CharacteristicsBehaviourInterface.h"
#include "AutoGenerated/NetworkDescriptor.h"

#define PROBE_GROUP 31 // 31 is our group reserved for our individual shape probes

#ifdef EUPHORIA_PROFILING
namespace NM_BEHAVIOUR_LIB_NAMESPACE
{
  #define TIMETYPE float
extern TIMETYPE timer_update_rootModule[3];
extern TIMETYPE timer_feedback_rootModule[3];
}
extern TIMETYPE g_profilingTimerFraction;
#endif

namespace NM_BEHAVIOUR_LIB_NAMESPACE
{
#if defined(MR_OUTPUT_DEBUGGING)
static bool debug_colourLimbs = true;
#endif // defined(MR_OUTPUT_DEBUGGING)

//----------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------
/// Returns the limb control object from the appropriate limb module
//----------------------------------------------------------------------------------------------------------------------
const LimbControl* MyNetwork::getLimbControl(uint32_t iLimb) const
{
  if (iLimb - data->firstArmRigIndex < data->numArms)
    return &arms[iLimb - data->firstArmRigIndex]->out->getControl();

  if (iLimb - data->firstHeadRigIndex < data->numHeads)
    return &heads[iLimb - data->firstHeadRigIndex]->out->getControl();

  if (iLimb - data->firstLegRigIndex < data->numLegs)
    return &legs[iLimb - data->firstLegRigIndex]->out->getControl();

  NMP_ASSERT(iLimb - data->firstSpineRigIndex < data->numSpines);
  return &spines[iLimb - data->firstSpineRigIndex]->out->getControl();
}

//----------------------------------------------------------------------------------------------------------------------
/// Extract limb indices from bodyDef
//----------------------------------------------------------------------------------------------------------------------
void MyNetwork::initLimbIndices()
{
  ER::BodyDef* bodyDef = m_character->getBody().m_definition;
  data->numArms = bodyDef->m_numArmLimbs;
  data->numHeads = bodyDef->m_numHeadLimbs;
  data->numLegs = bodyDef->m_numLegLimbs;
  data->numSpines = bodyDef->m_numSpineLimbs;

  data->firstArmRigIndex = bodyDef->getLimbIndexFromName("Arm_0");
  data->firstHeadRigIndex = bodyDef->getLimbIndexFromName("Head_0");
  data->firstLegRigIndex = bodyDef->getLimbIndexFromName("Leg_0");
  data->firstSpineRigIndex = bodyDef->getLimbIndexFromName("Spine_0");

  NMP_ASSERT(data->numArms == 0 || data->firstArmRigIndex  != 0xFFFFFFFF);
  NMP_ASSERT(data->numHeads == 0 || data->firstHeadRigIndex  != 0xFFFFFFFF);
  NMP_ASSERT(data->numLegs == 0 || data->firstLegRigIndex  != 0xFFFFFFFF);
  NMP_ASSERT(data->numSpines > 0 && data->firstSpineRigIndex  != 0xFFFFFFFF);

  // Also feed the limb indices into gravity compensation (it relies on the order to a small extent), and store the
  // default/zero pose.
  int order = 0;
  ER::GravityCompensation* gravComp = m_character->getBody().m_gravComp;
  for (uint32_t i = 0; i < data->numHeads; ++i)
  {
    data->headRigIndices[i] = data->firstHeadRigIndex + i;
    ER::Limb& limb = m_character->getBody().getLimb(data->headRigIndices[i]);
    gravComp->setOrderedLimbIndices(order++, data->headRigIndices[i]);
    int netId = MyNetworkData::firstHeadNetworkIndex + i;
    data->defaultPoseEndsRelativeToRoot[netId] = limb.getDefaultPoseEndRelativeToRoot();
    data->zeroPoseEndsRelativeToRoot[netId] = limb.getZeroPoseEndRelativeToRoot();
    data->defaultPoseLimbLengths[netId] = limb.getDefaultPoseLimbLength();
    data->baseToEndLength[netId] = limb.calculateBaseToEndLength();
  }
  for (uint32_t i = 0; i < data->numArms; ++i)
  {
    data->armRigIndices[i] = data->firstArmRigIndex + i;
    ER::Limb& limb = m_character->getBody().getLimb(data->armRigIndices[i]);
    gravComp->setOrderedLimbIndices(order++, data->armRigIndices[i]);
    int netId = MyNetworkData::firstArmNetworkIndex + i;
    data->defaultPoseEndsRelativeToRoot[netId] = limb.getDefaultPoseEndRelativeToRoot();
    data->zeroPoseEndsRelativeToRoot[netId] = limb.getZeroPoseEndRelativeToRoot();
    data->defaultPoseLimbLengths[netId] = limb.getDefaultPoseLimbLength();
    data->baseToEndLength[netId] = limb.calculateBaseToEndLength();
  }
  for (uint32_t i = 0; i < data->numSpines; ++i)
  {
    data->spineRigIndices[i] = data->firstSpineRigIndex + i;
    ER::Limb& limb = m_character->getBody().getLimb(data->spineRigIndices[i]);
    gravComp->setOrderedLimbIndices(order++, data->spineRigIndices[i]);
    int netId = MyNetworkData::firstSpineNetworkIndex + i;
    data->defaultPoseEndsRelativeToRoot[netId] = limb.getDefaultPoseEndRelativeToRoot();
    data->zeroPoseEndsRelativeToRoot[netId] = limb.getZeroPoseEndRelativeToRoot();
    data->defaultPoseLimbLengths[netId] = limb.getDefaultPoseLimbLength();
    data->baseToEndLength[netId] = limb.calculateBaseToEndLength();
  }
  for (uint32_t i = 0; i < data->numLegs; ++i)
  {
    data->legRigIndices[i] = data->firstLegRigIndex + i;
    ER::Limb& limb = m_character->getBody().getLimb(data->legRigIndices[i]);
    gravComp->setOrderedLimbIndices(order++, data->legRigIndices[i]);
    int netId = MyNetworkData::firstLegNetworkIndex + i;
    data->defaultPoseEndsRelativeToRoot[netId] = limb.getDefaultPoseEndRelativeToRoot();
    data->zeroPoseEndsRelativeToRoot[netId] = limb.getZeroPoseEndRelativeToRoot();
    data->defaultPoseLimbLengths[netId] = limb.getDefaultPoseLimbLength();
    data->baseToEndLength[netId] = limb.calculateBaseToEndLength();
  }
}

//----------------------------------------------------------------------------------------------------------------------
// called each time the character is initialised from animation into behaviour
//----------------------------------------------------------------------------------------------------------------------
void MyNetwork::entry()
{
  data->totalMass = m_character->getBody().getMass();

  // authored self avoidance data
  data->selfAvoidanceRadius = m_character->getBody().getSelfAvoidanceRadius();

  // runtime self avoidance data
  const NMP::Matrix34& pelvis =  m_character->getBody().getLimb(data->firstSpineRigIndex).getRootTransform();
  const NMP::Matrix34& chest =  m_character->getBody().getLimb(data->firstSpineRigIndex).getEndTransform();

  // Gravity & up/down
  data->gravity = m_character->getBody().getTotalGravity();
  data->gravityMagnitude = data->gravity.magnitude();
  if (data->gravityMagnitude > 0.0f)
  {
    data->down = data->gravity.getNormalised();
  }
  else
  {
    data->down = (pelvis.translation() - chest.translation()).getNormalised();
  }
  data->up = -data->down;

  // Setup per-limb data: extracts rig indices, sets up ordering for gravity compensation, and stores default pose data.
  if (m_character)
  {
    initLimbIndices();
  }

  data->dimensionalScaling = m_character->getBody().getDimensionalScaling();

  // Disable limbs that exist in the network but not in the rig
  for (uint32_t i = data->numArms ; i < NetworkConstants::networkMaxNumArms ; ++i)
  {
    setEnabledByOwner(arms[i]->getManifestIndex(), false);
  }
  for (uint32_t i = data->numHeads ; i < NetworkConstants::networkMaxNumHeads ; ++i)
  {
    setEnabledByOwner(heads[i]->getManifestIndex(), false);
  }
  for (uint32_t i = data->numLegs ; i < NetworkConstants::networkMaxNumLegs ; ++i)
  {
    setEnabledByOwner(legs[i]->getManifestIndex(), false);
  }
  for (uint32_t i = data->numSpines ; i < NetworkConstants::networkMaxNumSpines ; ++i)
  {
    setEnabledByOwner(spines[i]->getManifestIndex(), false);
  }

  // Initialise shared limb state data structures.
  for (uint32_t i = 0; i < data->numArms; ++i)
  {
    uint32_t j = data->firstArmRigIndex + i;
    ER::Limb& limb = m_character->getBody().getLimb(j);
    data->armLimbSharedStates[i].initialise(limb);
  }
  for (uint32_t i = 0; i < data->numHeads; ++i)
  {
    uint32_t j = data->firstHeadRigIndex + i;
    ER::Limb& limb = m_character->getBody().getLimb(j);
    data->headLimbSharedStates[i].initialise(limb);
  }
  for (uint32_t i = 0; i < data->numLegs; ++i)
  {
    uint32_t j = data->firstLegRigIndex + i;
    ER::Limb& limb = m_character->getBody().getLimb(j);
    data->legLimbSharedStates[i].initialise(limb);
  }
  for (uint32_t i = 0; i < data->numSpines; ++i)
  {
    uint32_t j = data->firstSpineRigIndex + i;
    ER::Limb& limb = m_character->getBody().getLimb(j);
    data->spineLimbSharedStates[i].initialise(limb);
  }

  // Store the average arm default pose
  data->averageArmDefaultPoseEndRelativeToRoot.zero();
  for (uint32_t i = 0; i < data->numArms ; ++i)
  {
    data->averageArmDefaultPoseEndRelativeToRoot +=
      data->defaultPoseEndsRelativeToRoot[MyNetworkData::firstArmNetworkIndex + i];
  }
  data->averageArmDefaultPoseEndRelativeToRoot.orthonormalise();
  if (data->numArms > 0)
  {
    data->averageArmDefaultPoseEndRelativeToRoot.translation() *= 1.0f / data->numArms;
  }

  // Store the average leg default pose
  data->averageLegDefaultPoseEndRelativeToRoot.zero();
  for (uint32_t i = 0; i < data->numLegs ; ++i)
  {
    data->averageLegDefaultPoseEndRelativeToRoot +=
      data->defaultPoseEndsRelativeToRoot[MyNetworkData::firstLegNetworkIndex + i];
    uint32_t index = data->firstLegRigIndex + i;
    m_character->getBody().m_gravComp->setLimbIsLeg(index);
  }
  data->averageLegDefaultPoseEndRelativeToRoot.orthonormalise();
  if (data->numLegs > 0)
  {
    data->averageLegDefaultPoseEndRelativeToRoot.translation() *= 1.0f / data->numLegs;
  }

  setStrengths();
  setProperties();
}

//----------------------------------------------------------------------------------------------------------------------
/// Sets up "normal" strength which individual behaviours can use for coherent strength scaling
//----------------------------------------------------------------------------------------------------------------------
void MyNetwork::setStrengths()
{
  m_character->getBody().setHamstringStiffness(SCALE_STIFFNESS(32.0f));
  m_character->getBody().setSoftLimitStiffness(SCALE_STIFFNESS(10.0f));
  data->normalStiffness = SCALE_STIFFNESS(16.0f);
  // 1 = critical damping, use slightly larger value to prevent excessive snappiness, without sapping basic strength.
  data->normalDampingRatio = 1.0f; // optimal for intercepting an object is 0.816 (root 2/3)
  data->normalDriveCompensation = 9.0f; // 0 to infinity, unitless
  data->minDamping = SCALE_DAMPING(10.0f); // This is also the damping when relaxed
  data->relaxDriveCompensation = 0.0f;
  // this relaxStiffness is stiffness when relaxed.
  data->relaxStiffness = 0.0f;
  // maxStiffness and minStiffnessForActing should be authored explicitly - see MORPH-11232
  data->maxStiffness = 2.0f * data->normalStiffness;
  data->minStiffnessForActing = 0.25f * data->normalStiffness;
  data->minInterestingRelativeMass = 0.0001f; // unitless, e.g. hazard mass <0.001 of character mass is not interesting
}

//----------------------------------------------------------------------------------------------------------------------
/// Sets up "normal" properties
//----------------------------------------------------------------------------------------------------------------------
void MyNetwork::setProperties()
{
  data->collidingSupportTime = SCALE_TIME(0.5f);
  data->cosMaxSlopeForGround = 0.5f;
  data->awarenessPredictionTime = SCALE_TIME(1.0f);
}

//----------------------------------------------------------------------------------------------------------------------
/// Adjust limb soft limits strength based on the strength of that limb and desired stiffnessScale.
//----------------------------------------------------------------------------------------------------------------------
void MyNetwork::adjustLimbSoftLimits(
  uint32_t           limbIndex,
  const LimbControl* limbControl,
  float              stiffnessScale)
{
  NMP_ASSERT(limbControl);

  float softLimitAdjustment = limbControl->getStrength() / NMP::sqr(data->normalStiffness);
  softLimitAdjustment = NMP::clampValue(softLimitAdjustment, 0.0f, 1.0f);

  ER::Limb& limb = m_character->getBody().getLimb(limbIndex);
  limb.setSoftLimitAdjustment(softLimitAdjustment, NMP::clampValue(stiffnessScale, 0.0f, 1.0f));
}

//----------------------------------------------------------------------------------------------------------------------
// This calls child module updates first then forwards network data to the limbs before the limb updates
// and then the physics. This module is unusual in that it is a 'user module' or a 'non-spu' module,
// meaning we can access all sorts of different data from it. We also use the slightly lower level
// member functions for update and release here. The role of this update is to read the control data
// from each limb and pass it into the euphoria limb objects.
//----------------------------------------------------------------------------------------------------------------------
void MyNetwork::update(float timeStep)
{
  MR_DEBUG_MODULE_ENTER(m_debugInterface, getClassName());

#if defined(MR_OUTPUT_DEBUGGING)
  // call setStrengths when debugging because it then makes it possible to use edit+continue to experiment
  setStrengths();
#endif

  setProperties();

  NM_BEGIN_PROFILING("updateChildren");
  executeNetworkUpdate(timeStep);
  NM_END_PROFILING();

#ifdef EUPHORIA_PROFILING
  // Start profiling rootNetwork here, so we don't measure the time of all child modules as well.
  NMP::Timer profileTimer(true);
#endif // EUPHORIA_PROFILING

  NM_BEGIN_PROFILING("Collecting prephys results into body");
  // Start off by setting the sleeping flag
  bool sleepingDisabled = false;
  if (euphoriaRagdollBehaviourInterface->out->getSleepingDisabledImportance() > 0.0f &&
      euphoriaRagdollBehaviourInterface->out->getSleepingDisabled())
  {
    sleepingDisabled = true;
  }

  if (animateBehaviourInterface->out->getSleepingDisabledImportance() > 0.0f &&
      animateBehaviourInterface->out->getSleepingDisabled())
  {
    sleepingDisabled = true;
  }

  // Check if any other behaviours are enabled
  ER::Character::Behaviours::const_value_walker itr = m_character->getBehaviours().constWalker();
  while (itr.next())
  {
    const ER::Behaviour* behaviour = itr();
    // Animate and euphoria ragdoll allowed
    if (behaviour->getBehaviourID() == NetworkManifest::BehaviourID_Animate ||
        behaviour->getBehaviourID() == NetworkManifest::BehaviourID_EuphoriaRagdoll)
      continue;

    if (behaviour->getEnabled())
    {
      // This stops sleeping if there are any modules apart from ragdoll or animate enabled.
      // It might seem a bit slow but only iterates over all modules when nothing is happening,
      // so doesn't affect worst-case performance
      sleepingDisabled = true;
      break;
    }
  }
  if (sleepingDisabled)
    m_character->getBody().getPhysicsRig()->disableSleeping();

  // This is code specific to the main euphoria network, it will write to the limb structures
  static const int maxLimbControls =
    NetworkConstants::networkMaxNumArms + NetworkConstants::networkMaxNumHeads +
    NetworkConstants::networkMaxNumLegs + NetworkConstants::networkMaxNumSpines;
  const LimbControl* limbControls[maxLimbControls];
  float limbControlImportances[maxLimbControls];

  // dummy for if the limbs are not enabled
  // notice that we override the damping ratio with a raw damping since relaxStiffness may be 0
  LimbControl emptyControl(
    data->relaxStiffness, data->normalDampingRatio, data->relaxDriveCompensation);
  emptyControl.setImplicitStiffness(0.0f);
  emptyControl.setDamping(data->minDamping);

  // Characteristics behaviour controls the soft limit stiffness scale.
  const float wholeBodySoftLimitStiffnessScale =
    1.0f - NMP::clampValue(characteristicsBehaviourInterface->out->getWholeBodySoftLimitStiffnessReduction(), 0.0f, 1.0f);

  for (uint32_t i = 0; i < m_character->getBody().m_definition->m_numArmLimbs; ++i)
  {
    uint32_t index = data->firstArmRigIndex + i;
    limbControls[index] = arms[i]->out->getControlImportance() ? &arms[i]->out->getControl() : &emptyControl;
    limbControlImportances[index] = arms[i]->out->getControlImportance();

    // Soft limits are adjusted based on the strength of each limb.
    const float limbSoftLimitStiffnessScale =
      1.0f - NMP::clampValue(characteristicsBehaviourInterface->out->getArmSoftLimitStiffnessReduction(i), 0.0f, 1.0f);
    adjustLimbSoftLimits(index, limbControls[index], limbSoftLimitStiffnessScale * wholeBodySoftLimitStiffnessScale);
  }

  for (uint32_t i = 0; i < m_character->getBody().m_definition->m_numHeadLimbs; ++i)
  {
    uint32_t index = data->firstHeadRigIndex + i;
    limbControls[index] = heads[i]->out->getControlImportance() ? &heads[i]->out->getControl() : &emptyControl;
    limbControlImportances[index] = heads[i]->out->getControlImportance();

    // Soft limits are adjusted based on the strength of each limb.
    const float limbSoftLimitStiffnessScale =
      1.0f - NMP::clampValue(characteristicsBehaviourInterface->out->getHeadSoftLimitStiffnessReduction(i), 0.0f, 1.0f);
    adjustLimbSoftLimits(index, limbControls[index], limbSoftLimitStiffnessScale * wholeBodySoftLimitStiffnessScale);
  }

  for (uint32_t i = 0; i < m_character->getBody().m_definition->m_numLegLimbs; ++i)
  {
    uint32_t index = data->firstLegRigIndex + i;
    limbControls[index] = legs[i]->out->getControlImportance() ? &legs[i]->out->getControl() : &emptyControl;
    limbControlImportances[index] = legs[i]->out->getControlImportance();

    // Soft limits are adjusted based on the strength of each limb.
    const float limbSoftLimitStiffnessScale =
      1.0f - NMP::clampValue(characteristicsBehaviourInterface->out->getLegSoftLimitStiffnessReduction(i), 0.0f, 1.0f);
    adjustLimbSoftLimits(index, limbControls[index], limbSoftLimitStiffnessScale * wholeBodySoftLimitStiffnessScale);
  }

  for (uint32_t i = 0; i < m_character->getBody().m_definition->m_numSpineLimbs; ++i)
  {
    uint32_t index = data->firstSpineRigIndex + i;
    limbControls[index] = spines[i]->out->getControlImportance() ? &spines[i]->out->getControl() : &emptyControl;
    limbControlImportances[index] = spines[i]->out->getControlImportance();

    // Soft limits are adjusted based on the strength of each limb.
    const float limbSoftLimitStiffnessScale =
      1.0f - NMP::clampValue(characteristicsBehaviourInterface->out->getSpineSoftLimitStiffnessReduction(i), 0.0f, 1.0f);
    adjustLimbSoftLimits(index, limbControls[index], limbSoftLimitStiffnessScale * wholeBodySoftLimitStiffnessScale);
  }

  // Update limb's end-effector constraints
  // First, find out if and which end-constraint allows it to be broken when hands are crossed:
  // Choose the one with maximum HoldBreakageOpportunity.
  float maxBreakageOpportunity = 0.000001f;
  uint32_t armBreakageIndex = data->numArms; // impossible index
  for (uint32_t i = 0; i < data->numArms; i++)
  {
    float breakageOpportunity = arms[i]->out->getHoldBreakageOpportunity();
    if (breakageOpportunity > maxBreakageOpportunity)
    {
      armBreakageIndex = i;
      maxBreakageOpportunity = breakageOpportunity;
    }
  }

  for (uint32_t i = 0; i < data->numArms; i++)
  {
    ER::Limb& limb = m_character->getBody().getLimb(data->firstArmRigIndex + i);
    ER::EndConstraint& endConstraint = limb.getEndConstraint();
    const EndConstraintControl& holdParams = arms[i]->out->getEndConstraint();
    // only update these parameters if not constrained yet. If already grabbing, cached values are used.
    if ((i != armBreakageIndex) /*&& !endConstraint.isConstrained()*/ && arms[i]->out->getEndConstraintImportance() > 0.0f)
    {
      endConstraint.doConstrain(true);
      endConstraint.setDesiredTransformWs(holdParams.desiredTM, holdParams.targetShapeID);
      endConstraint.setLockedDofs(holdParams.lockedLinearDofs, holdParams.lockedAngularDofs);
      endConstraint.disableCollisions(holdParams.disableCollisions);
      endConstraint.constrainOnContact(holdParams.constrainOnContact);
      endConstraint.setSeparationThresholds(holdParams.createDistance, holdParams.destroyDistance,
        holdParams.startOrientationAngle, holdParams.stopOrientationAngle);
      endConstraint.useCheatForces(holdParams.useCheatForces);
    }
    // this needs to be set irrespective, to disable when already constrained
    else if (arms[i]->out->getEndConstraintImportance() == 0.0f || i == armBreakageIndex)
    {
      endConstraint.doConstrain(false);
      endConstraint.constrainOnContact(false);
    }
  }

  // Note that we should allow for strength increasing here
  float wholeBodyStrengthScale = NMP::clampValue(
    1.0f - characteristicsBehaviourInterface->out->getWholeBodyStrengthReduction(), 0.0f, 1.0f);
  float wholeBodyStrengthScaleSquared  = NMP::sqr(wholeBodyStrengthScale);
  float wholeBodyControlCompensationScale =
    1.0f - NMP::clampValue(characteristicsBehaviourInterface->out->getWholeBodyControlCompensationReduction(), 0.0f, 1.0f);
  float wholeBodyExternalComplianceScale =
    1.0f - NMP::clampValue(characteristicsBehaviourInterface->out->getWholeBodyExternalComplianceReduction(), 0.0f, 1.0f);

  for (uint32_t i = 0; i < m_character->getBody().m_definition->m_numLimbs; ++i)
  {
    ER::Limb& limb = m_character->getBody().getLimb(i);

    // fill in the limb effector params from the control
    const LimbControl* lc = limbControls[i];
    const float maxDriveVelocityOffset = SCALE_DIST(1.2f);
#if defined(MR_OUTPUT_DEBUGGING)
    if (debug_colourLimbs)
    {
      float stiffness = sqrtf(lc->getStrength());
      float stiffnessFraction = stiffness/data->normalStiffness;
      limb.setDebugControlAmounts(*lc->getControlAmounts(), stiffnessFraction);
    }
#endif // defined(MR_OUTPUT_DEBUGGING)

    float strength = lc->getStrength();
    strength = NMP::clampValue(strength, 0.0f, NMP::sqr(data->maxStiffness));
    float damping = lc->getDamping();
    float driveCompensation = lc->getDriveCompensation();
    float implicitStiffness = lc->getImplicitStiffness();
    // fast blend with the empty control, ignoring bits that don't matter
    float blend = 1.0f - limbControlImportances[i];
    strength += (emptyControl.getStrength() - strength) * blend;
    damping += (emptyControl.getDamping() - damping) * blend;
    driveCompensation += (emptyControl.getDriveCompensation() - driveCompensation) * blend;
    implicitStiffness += (emptyControl.getImplicitStiffness() - implicitStiffness) * blend;

    ER::Limb::EffectorControlParams ecp =
    {
      // target and root data (geometry + weights)
      lc->getTargetPos(),
      lc->getTargetNormal(),
      lc->getLocalNormalVector(),
      lc->getTargetOrientation(),
      lc->getTargetsVelocity(),
      lc->getTargetsAngularVelocity(),

      lc->getExpectedRootPosForTarget(),
      lc->getExpectedRootOrientationForTarget(),
      lc->getRootsVelocity(),
      lc->getRootsAngularVelocity(),

      lc->getPositionWeight(),
      lc->getNormalWeight(),
      lc->getOrientationWeight(),
      lc->getRootPositionWeight(),
      lc->getRootOrientationWeight(),

      strength* wholeBodyStrengthScaleSquared,
      NMP::maximum(damping, data->minDamping) * wholeBodyStrengthScale,
      driveCompensation * wholeBodyControlCompensationScale,
      wholeBodyExternalComplianceScale,
      implicitStiffness,
      maxDriveVelocityOffset,
      lc->getTargetDeltaStep(),
      lc->getSwivelAmount(),
      lc->getStrengthReductionTowardsEnd(),
      lc->getUseIncrementalIK()
    };

    limb.setEffectorControlParams(ecp);

    limb.applySkinWidthIncrease(lc->getSkinWidthIncrease());
    limb.setEndFrictionScale(lc->getEndFrictionScale());

    // Configure per-limb gravity compensation parameters:
    // The end is supported if it is either set to supported or if externally supported
    bool limbEndSupported = limbControls[i]->getEndSupportAmount() > 0.0f || limb.getEndIsExternallySupported();
    m_character->getBody().m_gravComp->setLimbEndSupported(i, limbEndSupported);

    // This code prevents the ankles moving in non-support behaviours
    limb.setLeafLimitScale(1.0f);
    if (limb.getType() == ER::LimbTypeEnum::L_leg)
    {
      bool useAnkleRange = legs[i-data->firstLegRigIndex]->out->getUseFullAnkleRange();
      if (!useAnkleRange)
      {
        limb.setLeafLimitScale(0.01f);
      }
    }
    else if (limb.getType() == ER::LimbTypeEnum::L_arm)
    {
      limb.setLeafLimitScale(1.0f - arms[i-data->firstArmRigIndex]->out->getWristLimitReduction());
    }
    const bool limbRootSupported =
      limb.getRootIsExternallySupported() || limbControls[i]->getRootSupportedAmount() > 0.0f;
    m_character->getBody().m_gravComp->setLimbRootSupported(i, limbRootSupported);
    m_character->getBody().m_gravComp->setSupportForceMultiplier(i, limbControls[i]->getSupportForceMultiplier());
    // here we convert the gravity compensation from the limb into a simple multiplier for GC
    float GCmultiplier = NMP::minimum(
      limbControls[i]->getGravityCompensation() * sqrtf(ecp.strength) / data->normalStiffness, 1.0f);
    m_character->getBody().m_gravComp->setLimbGravityCompensationMultiplier(i, GCmultiplier);

    // We only want to use the collision set info if it came from a single source - i.e. if
    // importance is basically 1.
    limb.activateCollisionGroupIndex(-1); // default
    if (limbControlImportances[i] > 0.9999f)
    {
      float indexF = lc->getCollisionGroupIndex();
      int index = indexF > 0.0f ? (int) (indexF + 0.5f) : (int) (indexF - 0.5f);
      if (index >= 0)
        limb.activateCollisionGroupIndex(index);
    }
  }

  // Configure the gravity compensation
  // the ZMPOffset is a lean vector based on clamping the centre of mass to the support polygon in bodyFrame
  NMP::Vector3 ZMPOffset = -bodyFrame->feedOut->getLeanVector();
  ZMPOffset -= data->up * data->up.dot(ZMPOffset); // flatten it
  m_character->getBody().m_gravComp->setZMPOffset(ZMPOffset);
  m_character->getBody().m_gravComp->setBridgeSupportLimb(data->firstSpineRigIndex);

  NM_END_PROFILING();

#ifdef EUPHORIA_PROFILING
  float myNetworkUpdateTime = profileTimer.stop() * 1000.0f; // convert to micro seconds;
  timer_update_rootModule[1] = (TIMETYPE) (g_profilingTimerFraction * myNetworkUpdateTime +
    (1.0 - g_profilingTimerFraction) * timer_update_rootModule[1]);
#endif // EUPHORIA_PROFILING
}

//----------------------------------------------------------------------------------------------------------------------
// For collecting the closest objects
//----------------------------------------------------------------------------------------------------------------------
struct Shape
{
  physx::PxShape* physXShape;
  float distance;
};

//----------------------------------------------------------------------------------------------------------------------
static NM_INLINE bool isPartInContactWithPatch(const MR::PhysicsRig::Part* const part, const int64_t patchShapeID)
{
  bool inContact = false;

  const uint16_t numContacts = 
    ER::EuphoriaRigPartUserData::getFromPart(part)->getNumContacts();
  for (uint16_t contactIndex = 0; (contactIndex < numContacts) && !inContact; ++contactIndex)
  {
    const int64_t collisionShapeId = 
      ER::EuphoriaRigPartUserData::getFromPart(part)->getContactedShapeID(contactIndex);
    // if the part contact id matches the patch id then the part is in contact with the patch
    inContact = (collisionShapeId == patchShapeID);
  }

  return inContact;
}

//----------------------------------------------------------------------------------------------------------------------
// Update data specific to arms and legs (but not heads or spines).
//----------------------------------------------------------------------------------------------------------------------
template <class LimbModule>
static void updateArmOrLeg(
  const ER::Limb& limb,
  ER::Module* limbBase)
{
  LimbModule* limbModule = (LimbModule*) limbBase;

  // Brace-specific: pass up whether the arm is colliding with the specified contact test ID
  const int64_t patchShapeID = limbModule->brace->data->patchShapeID;
  if (patchShapeID != 0)
  {
    // Test for contact between limb root and test patch.
    const MR::PhysicsRig::Part* const rootPart = static_cast<const MR::PhysicsRig::Part*>(limb.getPart(0));
    limbModule->brace->feedIn->setRootInContactWithPatchShapeID(isPartInContactWithPatch(rootPart, patchShapeID));

    // Test for contact between any part of limb (including root) and test patch.
    for (uint32_t i = 0; i < limb.getTotalNumParts(); ++i)
    {
      const MR::PhysicsRig::Part* const part = static_cast<const MR::PhysicsRig::Part*>(limb.getPart(i));
      if (isPartInContactWithPatch(part, patchShapeID))
      {
        limbModule->brace->feedIn->setLimbInContactWithPatchShapeID(true);
        break;
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------
// Called after physics and after limb's post step. Reads the data from the limb and passes back up to its child limb
// modules. Also calls ApplySweeps which probes the physics scene.
//----------------------------------------------------------------------------------------------------------------------
void MyNetwork::feedback(float timeStep)
{
  MR_DEBUG_MODULE_ENTER(m_debugInterface, getClassName());

  NM_BEGIN_PROFILING("feedbackNetwork_start");
#ifdef EUPHORIA_PROFILING
  NMP::Timer profileTimer(true);
#endif // EUPHORIA_PROFILING

  NMP_ASSERT(m_character);
  NMP_ASSERT(timeStep > 0.0f); // Guaranteed by Character::feedbackNetwork

  // update self avoidance data
  const NMP::Matrix34& pelvis =  m_character->getBody().getLimb(data->firstSpineRigIndex).getRootTransform();
  const NMP::Matrix34& chest =  m_character->getBody().getLimb(data->firstSpineRigIndex).getEndTransform();

  // Gravity & up/down
  data->gravity = m_character->getBody().getTotalGravity();
  data->gravityMagnitude = data->gravity.magnitude();
  if (data->gravityMagnitude > 0.0f)
  {
    data->down = data->gravity.getNormalised();
  }
  else
  {
    data->down = (pelvis.translation() - chest.translation()).getNormalised();
  }
  data->up = -data->down;

  // acquire data for/from each limb and update corresponding state of limb modules in behaviour network

  // arms update
  for (uint32_t i = 0; i < data->numArms; ++i)
  {
    ER::Limb& limb = m_character->getBody().getLimb(data->firstArmRigIndex + i);
    updateArmOrLeg<Arm>(limb, arms[i]); // the parts[] array will be filled now
  }
  // legs update
  for (uint32_t i = 0; i < data->numLegs; ++i)
  {
    ER::Limb& limb = m_character->getBody().getLimb(data->firstLegRigIndex + i);
    updateArmOrLeg<Leg>(limb, legs[i]); // the parts[] array will be filled now
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Update the new shared limb data structures: arms, legs, spines, heads
  //

  for (uint32_t i = 0; i < data->numArms; ++i)
  {
    ER::Limb& limb = m_character->getBody().getLimb(data->firstArmRigIndex + i);
    data->armLimbSharedStates[i].update(*this, limb, timeStep, m_debugInterface);
  }
  for (uint32_t i = 0; i < data->numLegs; ++i)
  {
    ER::Limb& limb = m_character->getBody().getLimb(data->firstLegRigIndex + i);
    data->legLimbSharedStates[i].update(*this, limb, timeStep, m_debugInterface);
  }
  for (uint32_t i = 0; i < data->numHeads; ++i)
  {
    data->headLimbSharedStates[i].update(
      *this, m_character->getBody().getLimb(data->firstHeadRigIndex + i), timeStep, m_debugInterface);
  }
  for (uint32_t i = 0; i < data->numSpines; ++i)
  {
    ER::Limb& limb = m_character->getBody().getLimb(data->firstSpineRigIndex + i);
    data->spineLimbSharedStates[i].update(*this, limb, timeStep, m_debugInterface);
  }
  // note: this relies on data from spine 0 and legs updates so must come after
  data->spineLimbSharedStates[0].updateMainSpineExternalSupportAmount(*this);
  // summary body state.
  data->bodyLimbSharedState.update( *this,
    data->armLimbSharedStates, data->legLimbSharedStates, data->headLimbSharedStates, data->spineLimbSharedStates);

  // Debug viz for the average quantities calculated by the limb and body states updates.
  //
  MR_DEBUG_DRAW_MATRIX(m_debugInterface,
    data->bodyLimbSharedState.m_averageOfFeetTM, SCALE_DIST(0.2f));
  MR_DEBUG_DRAW_MATRIX(m_debugInterface,
    data->bodyLimbSharedState.m_averageOfDefaultPoseFeetTMWorld, SCALE_DIST(0.5f));
  MR_DEBUG_DRAW_MATRIX(m_debugInterface,
    data->bodyLimbSharedState.m_averageOfDefaultPoseShouldersTMWorld, SCALE_DIST(1.5f));

  // Backdoor set body frame feedin to ensure it's valid.
  bodyFrame->feedIn->setExternalSpineSupportAmount(data->spineLimbSharedStates[0].m_externalSupportAmount, 1.0f);

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  // Read part local hit info from the hit reaction interface, transform to world coordinates,
  // and write into the reachForBody module
  // For now we only take the one but there are actually as many as we have arms
  int32_t maxNumInputs = NetworkConstants::networkMaxNumArms;
  for (int32_t i = 0; i < maxNumInputs; ++i)
  {
    if (reachForBodyBehaviourInterface->out->getBodyHitInfoImportance(i) != 0)
    {
      const int32_t limbRigIndex = reachForBodyBehaviourInterface->out->getBodyHitInfo(i).limbRigIndex;
      if (limbRigIndex >= 0 && limbRigIndex < m_character->getBody().getNumLimbs())
      {
        ER::Limb& limb = m_character->getBody().getLimb(limbRigIndex);
        const int32_t partIndex = reachForBodyBehaviourInterface->out->getBodyHitInfo(i).partIndex;
        if (partIndex >= 0 && partIndex < (int32_t) limb.getNumPartsInChain())
        {
          BodyHitInfo bhi(reachForBodyBehaviourInterface->out->getBodyHitInfo(i));
          // transform pos and normal from part local coords to world coords
          MR::PhysicsRig::Part* part = m_character->getBody().getPhysicsRig()->getPart(limb.getPhysicsRigPartIndex(partIndex));
          const NMP::Matrix34 &partTM = part->getTransform();
          partTM.transformVector(bhi.point);
          partTM.rotateVector(bhi.normal);
          bodyFrame->reachForBody->feedIn->setHitInfoAt(
            i, bhi, reachForBodyBehaviourInterface->out->getBodyHitInfoImportance(0));
        }
      }
    }
  }

  // Special case code for getting most relevant ground contacts. Used in get-up, but may also be
  // useful in other behaviours. Basically it finds the contact closest to the requested normal in
  // the upper body and lower body by requesting the closest on each limb in turn
  bool upperContactRequest = upperBody->out->getContactDirectionRequestImportance() > 0.0f;
  bool lowerContactRequest = lowerBody->out->getContactDirectionRequestImportance() > 0.0f;
  if (upperContactRequest || lowerContactRequest)
  {
    float closestDistUpper = 1e10f;
    float closestDistLower = 1e10f;
    ER::EuphoriaRigPartUserData* dataLower = NULL;
    ER::EuphoriaRigPartUserData* dataUpper = NULL;
    for (uint32_t i = 0 ; i < m_character->getBody().m_definition->m_numLimbs; i++)
    {
      ER::Limb& limb = m_character->getBody().getLimb(i);
      float dist;
      ER::EuphoriaRigPartUserData* userData = NULL;
      if (limb.getDefinition()->m_type == ER::LimbTypeEnum::L_leg)
      {
        userData = limb.getClosestContactInDirection(lowerBody->out->getContactDirectionRequest(), dist);
        if (lowerContactRequest && userData && dist < closestDistUpper)
        {
          closestDistUpper = dist;
          dataLower = userData;
        }
      }
      else
      {
        userData = limb.getClosestContactInDirection(upperBody->out->getContactDirectionRequest(), dist);
        if (upperContactRequest && userData && dist < closestDistLower)
        {
          closestDistLower = dist;
          dataUpper = userData;
        }
      }
    }

    if (dataUpper)
    {
      ContactInfo& contact = upperBody->feedIn->startClosestContactModification();
      contact.lastVelocity = dataUpper->getLastAverageVelocity();
      contact.lastPosition = dataUpper->getLastAveragePosition();
      contact.lastNormal = dataUpper->getLastAverageNormal();
      // Behaviours are normally interested mostly in forces - e.g. the foot/ground contact forces,
      // rather than impulses. If behaviours need to analyse impacts they should convert to impulse
      // using the timestep.
      contact.lastForce = dataUpper->getLastTotalImpulse() / timeStep;
      upperBody->feedIn->stopClosestContactModification(1.0f);
    }

    if (dataLower)
    {
      ContactInfo& contact = lowerBody->feedIn->startClosestContactModification();
      contact.lastVelocity = dataLower->getLastAverageVelocity();
      contact.lastPosition = dataLower->getLastAveragePosition();
      contact.lastNormal = dataLower->getLastAverageNormal();
      contact.lastForce = dataLower->getLastTotalImpulse() / timeStep;
      lowerBody->feedIn->stopClosestContactModification(1.0f);
    }
  }

#ifdef EUPHORIA_PROFILING
  // stop the timing before applySweeps as that's not really part of the euphoria update
  float myNetworkFeedbackTime = profileTimer.stop() * 1000.0f; // convert to microseconds
  timer_feedback_rootModule[1] = (TIMETYPE) (g_profilingTimerFraction * myNetworkFeedbackTime +
    (1.0 - g_profilingTimerFraction) * timer_feedback_rootModule[1]);
#endif // EUPHORIA_PROFILING

  NM_END_PROFILING(); // End of feedbackNetwork_start

  // recursive feedback call to child modules
  NM_BEGIN_PROFILING("feedbackNetwork_end");
  executeNetworkFeedback(timeStep);
  NM_END_PROFILING(); // End of feedbackNetwork_end
}

} //namespace NM_BEHAVIOUR_LIB_NAMESPACE
