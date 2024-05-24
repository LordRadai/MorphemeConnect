// Copyright (c) 2010 NaturalMotion.  All Rights Reserved.
// Not to be copied, adapted, modified, used, distributed, sold,
// licensed or commercially exploited in any manner without the
// written consent of NaturalMotion.
//
// All non public elements of this software are the confidential
// information of NaturalMotion and may not be disclosed to any
// person nor used for any purpose not expressly approved by
// NaturalMotion in writing.

//----------------------------------------------------------------------------------------------------------------------
#include "TransitConditionDefBuilderCrossedDurationFraction.h"
#include "morpheme/TransitConditions/mrTransitConditionCrossedDurationFraction.h"
//----------------------------------------------------------------------------------------------------------------------

namespace AP
{

//----------------------------------------------------------------------------------------------------------------------
NMP::Memory::Format TransitConditionDefBuilderCrossedDurationFraction::getMemoryRequirements(
  const ME::ConditionExport*   NMP_UNUSED(condExport),
  const ME::NetworkDefExport*  NMP_UNUSED(netDefExport),
  AssetProcessor*              NMP_UNUSED(processor))
{
  return NMP::Memory::Format(NMP::Memory::align(sizeof(MR::TransitConditionDefCrossedDurationFraction), NMP_NATURAL_TYPE_ALIGNMENT), NMP_NATURAL_TYPE_ALIGNMENT);
}

//----------------------------------------------------------------------------------------------------------------------
/// \brief Initialise the TransitCondition from connects xml data.
MR::TransitConditionDef* TransitConditionDefBuilderCrossedDurationFraction::init(
  NMP::Memory::Resource&       memRes,
  const ME::ConditionExport*   condExport,
  const ME::NetworkDefExport*  netDefExport,
  AssetProcessor*              processor,
  MR::NodeID                   sourceNodeID)
{
  const ME::DataBlockExport* condDataBlock = condExport->getDataBlock();

  NMP::Memory::Format memReqs = getMemoryRequirements(condExport, netDefExport, processor);
  memRes.align(memReqs);
  MR::TransitConditionDefCrossedDurationFraction* result = (MR::TransitConditionDefCrossedDurationFraction*) memRes.ptr;
  memRes.increment(memReqs);
  result->setType(TRANSCOND_CROSSED_DURATION_FRACTION_ID);

  // Initialise fractional playback pos attrib address to look for.
  MR::AttribAddress sourceNodeFractionalPosAttribAddress(MR::ATTRIB_SEMANTIC_FRACTION_POS, sourceNodeID, MR::INVALID_NODE_ID, MR::VALID_FRAME_ANY_FRAME, MR::ANIMATION_SET_ANY);
  result->setSourceNodeFractionalPosAttribAddress(sourceNodeFractionalPosAttribAddress);

  float triggerFraction;
  condDataBlock->readFloat(triggerFraction, "TestFraction");
  result->setTriggerFraction(triggerFraction);
  result->setInvertFlag(false); // TODO: build UI.

  return result;
}

} // namespace AP

//----------------------------------------------------------------------------------------------------------------------
