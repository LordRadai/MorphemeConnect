#include <filesystem>
#include "ME.h"

XMLElement* ME::NetworkDefExportXML::NetworkDefExportXML(XMLElement* pRoot, std::string guid, std::string name)
{
	XMLElement* pNetworkDef = pRoot->InsertNewChildElement("NetworkDefinition");
	pNetworkDef->SetAttribute("guid", guid.c_str());
	pNetworkDef->SetAttribute("name", name.c_str());

	return pNetworkDef;
}

void ME::NetworkDefExportXML::SetWorldOrientation(XMLElement* pRoot, Vector3 forward, Vector3 right, Vector3 up)
{
	char forward_text[255];
	char right_text[255];
	char up_text[255];

	sprintf_s(forward_text, "%f, %f, %f", forward.x, forward.y, forward.z);
	sprintf_s(right_text, "%f, %f, %f", right.x, right.y, right.z);
	sprintf_s(up_text, "%f, %f, %f", up.x, up.y, up.z);

	XMLElement* pForward = pRoot->InsertNewChildElement("networkWorldForwardVector");
	pForward->SetText(forward_text);

	XMLElement* pRight = pRoot->InsertNewChildElement("networkWorldRightVector");
	pRight->SetText(right_text);

	XMLElement* pUp = pRoot->InsertNewChildElement("networkWorldUpVector");
	pUp->SetText(up_text);
}

XMLElement* ME::NetworkDefExportXML::SetRootNodeNetworkID(XMLElement* pRoot, UINT nodeId)
{
	XMLElement* pNetworkRootId = pRoot->InsertNewChildElement("rootNodeNetworkID");
	pNetworkRootId->SetText(nodeId);

	return pNetworkRootId;
}

XMLElement* ME::NetworkDefExportXML::AddMessage(XMLElement* pRoot, std::string name, UINT messageTypeId, UINT messageId)
{
	XMLElement* pMessage = pRoot->InsertNewChildElement("Message");
	pMessage->SetAttribute("name", name.c_str());
	pMessage->SetAttribute("messageTypeID", messageTypeId);
	pMessage->SetAttribute("messageID", messageId);

	return pMessage;
}

XMLElement* ME::NetworkDefExportXML::SetAnimLibraryRef(XMLElement* pRoot, std::string guid, std::string filename)
{
	XMLElement* pAnimLibraryRef = pRoot->InsertNewChildElement("AnimLibraryRef");
	pAnimLibraryRef->SetAttribute("refGUID", guid.c_str());
	pAnimLibraryRef->SetAttribute("filename", filename.c_str());

	return pAnimLibraryRef;
}

XMLElement* ME::NetworkDefExportXML::SetMessagePresetLibraryRef(XMLElement* pRoot, std::string guid, std::string filename)
{
	XMLElement* pMessagePresetLibraryRef = pRoot->InsertNewChildElement("AnimLibraryRef");
	pMessagePresetLibraryRef->SetAttribute("refGUID", guid.c_str());
	pMessagePresetLibraryRef->SetAttribute("filename", filename.c_str());

	return pMessagePresetLibraryRef;
}

XMLElement* ME::RigExportXML::RigExportXML(XMLElement* pRoot, std::string guid, std::string name, float rigScale)
{
	XMLElement* pRig = pRoot->InsertNewChildElement("Rig");
	pRig->SetAttribute("guid", guid.c_str());
	pRig->SetAttribute("name", name.c_str());
	pRig->SetAttribute("RigScale", rigScale);

	return pRig;
}

XMLElement* ME::RigExportXML::SetHipIndex(XMLElement* pRoot, UINT index)
{
	XMLElement* pHipIndex = pRoot->InsertNewChildElement("hipIndex");
	pHipIndex->SetText(index);

	return pHipIndex;
}

XMLElement* ME::RigExportXML::SetTrajectoryIndex(XMLElement* pRoot, UINT index)
{
	XMLElement* pTrajIndex = pRoot->InsertNewChildElement("trajectoryIndex");
	pTrajIndex->SetText(index);

	return pTrajIndex;
}

XMLElement* ME::RigExportXML::SetBlendFrameOrientationQuat(XMLElement* pRoot, Quaternion orientation)
{
	char orientation_text[255];

	sprintf_s(orientation_text, "%f, %f, %f, %f", orientation.x, orientation.y, orientation.z, orientation.w);

	XMLElement* pOrientation = pRoot->InsertNewChildElement("orientationQuat");
	pOrientation->SetText(orientation_text);

	return pOrientation;
}

XMLElement* ME::RigExportXML::SetBlendFramePositionVecVec(XMLElement* pRoot, Vector3 position)
{
	char translation_text[255];

	sprintf_s(translation_text, "%f, %f, %f", position.x, position.y, position.z);

	XMLElement* pTranslation = pRoot->InsertNewChildElement("positionVec");
	pTranslation->SetText(translation_text);

	return pTranslation;
}

XMLElement* ME::RigExportXML::SetRigSourceFilename(XMLElement* pRoot, std::string filename)
{
	char rig_filename_ext[255];

	sprintf_s(rig_filename_ext, "![CDATA[%s]]", filename.c_str());

	XMLElement* pRigFilename = pRoot->InsertNewChildElement("rigSourceFileName");
	pRigFilename->SetText(rig_filename_ext);

	return pRigFilename;
}

XMLElement* ME::RigExportXML::SetRigRetargetScale(XMLElement* pRoot, float rigRetargetScale)
{
	XMLElement* pRigRetargetScale = pRoot->InsertNewChildElement("rigRetargetScale");
	pRigRetargetScale->SetText(rigRetargetScale);

	return pRigRetargetScale;
}

XMLElement* ME::RigExportXML::SetMirrorPlane(XMLElement* pRoot, UINT plane)
{
	XMLElement* pMirrorPlane = pRoot->InsertNewChildElement("mirrorPlane");
	pMirrorPlane->SetText(plane);

	return pMirrorPlane;
}

XMLElement* ME::RigExportXML::AddJointMirrorMapping(XMLElement* pRoot, UINT index, UINT first, UINT second)
{
	XMLElement* pJointMirror = pRoot->InsertNewChildElement("JointMirrorMapping");
	pJointMirror->SetAttribute("index", index);
	pJointMirror->SetAttribute("first", first);
	pJointMirror->SetAttribute("second", second);

	return pJointMirror;
}

XMLElement* ME::JointExportXML::JointExportXML(XMLElement* pRoot, UINT index, std::string name, UINT parentIdx)
{
	XMLElement* pJoint = pRoot->InsertNewChildElement("Joint");
	pJoint->SetAttribute("index", index);
	pJoint->SetAttribute("name", name.c_str());
	pJoint->SetAttribute("parent", parentIdx);

	return pJoint;
}

void ME::JointExportXML::AddBodyPlanTag(XMLElement* pRoot, std::string bodyPlanTag)
{
	pRoot->SetAttribute("BodyPlanTag", bodyPlanTag.c_str());
}

void ME::JointExportXML::AddRetargetTag(XMLElement* pRoot, std::string retargetTag)
{
	pRoot->SetAttribute("RetargetTag", retargetTag.c_str());
}

XMLElement* ME::JointExportXML::SetOrientation(XMLElement* pRoot, Quaternion rotation)
{
	char rotation_text[255];

	sprintf_s(rotation_text, "%f, %f, %f, %f", rotation.x, rotation.y, rotation.z, rotation.w);

	XMLElement* pRotation = pRoot->InsertNewChildElement("Rotation");
	pRotation->SetText(rotation_text);

	return pRotation;
}

XMLElement* ME::JointExportXML::SetTranslation(XMLElement* pRoot, Vector3 translation)
{
	char translation_text[255];

	sprintf_s(translation_text, "%f, %f, %f", translation.x, translation.y, translation.z);

	XMLElement* pTranslation = pRoot->InsertNewChildElement("Translation");
	pTranslation->SetText(translation_text);

	return pTranslation;
}

XMLElement* ME::JointExportXML::SetOrientationOffset(XMLElement* pRoot, Quaternion orientationOffset)
{
	char rotation_text[255];

	sprintf_s(rotation_text, "%f, %f, %f, %f", orientationOffset.x, orientationOffset.y, orientationOffset.z, orientationOffset.w);

	XMLElement* pOrientationOffset = pRoot->InsertNewChildElement("OrientationOffset");
	pOrientationOffset->SetText(rotation_text);

	return pOrientationOffset;
}

XMLElement* ME::JointExportXML::SetTranslationOffset(XMLElement* pRoot, Vector3 translationOffset)
{
	char translation_text[255];

	sprintf_s(translation_text, "%f, %f, %f", translationOffset.x, translationOffset.y, translationOffset.z);

	XMLElement* pTranslationOffset = pRoot->InsertNewChildElement("TranslationOffset");
	pTranslationOffset->SetText(translation_text);

	return pTranslationOffset;
}

XMLElement* ME::JointExportXML::SetPostOrientationOffset(XMLElement* pRoot, Quaternion postOrientationOffset)
{
	char rotation_text[255];

	sprintf_s(rotation_text, "%f, %f, %f, %f", postOrientationOffset.x, postOrientationOffset.y, postOrientationOffset.z, postOrientationOffset.w);

	XMLElement* pPostOrientationOffset = pRoot->InsertNewChildElement("PostOrientationOffset");
	pPostOrientationOffset->SetText(rotation_text);

	return pPostOrientationOffset;
}

XMLElement* ME::AttributeBlockExportXML(XMLElement* pRoot)
{
	return pRoot->InsertNewChildElement("Attributes");
}

XMLElement* ME::AttributeExportXML::AttributeExportXML(XMLElement* pRoot, std::string name)
{
	return pRoot->InsertNewChildElement(name.c_str());
}

void ME::AttributeExportXML::SetAsBool(XMLElement* pRoot, bool value)
{
	pRoot->SetAttribute("type", "bool");
	
	if (value)
		pRoot->SetText("true");
	else
		pRoot->SetText("false");
}

void ME::AttributeExportXML::SetAsBoolArray(XMLElement* pRoot, bool* values, UINT size)
{
	pRoot->SetAttribute("type", "boolArray");
	pRoot->SetAttribute("size", size);
	
	for (size_t i = 0; i < size; i++)
	{
		XMLElement* pElement = pRoot->InsertNewChildElement("elem");
		ME::AttributeExportXML::SetAsBool(pElement, values[i]);
	}
}

void ME::AttributeExportXML::SetAsDouble(XMLElement* pRoot, double value)
{
	pRoot->SetAttribute("type", "double");
	pRoot->SetText(value);
}

void ME::AttributeExportXML::SetAsDoubleArray(XMLElement* pRoot, double* values, UINT size)
{
	pRoot->SetAttribute("type", "doubleArray");
	pRoot->SetAttribute("size", size);

	for (size_t i = 0; i < size; i++)
	{
		XMLElement* pElement = pRoot->InsertNewChildElement("elem");
		ME::AttributeExportXML::SetAsDouble(pElement, values[i]);
	}
}

void ME::AttributeExportXML::SetAsInt(XMLElement* pRoot, int value)
{
	pRoot->SetAttribute("type", "int");
	pRoot->SetText(value);
}

void ME::AttributeExportXML::SetAsIntArray(XMLElement* pRoot, int* values, UINT size)
{
	pRoot->SetAttribute("type", "intArray");
	pRoot->SetAttribute("size", size);

	for (size_t i = 0; i < size; i++)
	{
		XMLElement* pElement = pRoot->InsertNewChildElement("elem");
		ME::AttributeExportXML::SetAsInt(pElement, values[i]);
	}
}

void ME::AttributeExportXML::SetAsUInt(XMLElement* pRoot, UINT value)
{
	pRoot->SetAttribute("type", "uint");
	pRoot->SetText(value);
}

void ME::AttributeExportXML::SetAsUIntArray(XMLElement* pRoot, UINT* values, UINT size)
{
	pRoot->SetAttribute("type", "boolArray");
	pRoot->SetAttribute("size", size);

	for (size_t i = 0; i < size; i++)
	{
		XMLElement* pElement = pRoot->InsertNewChildElement("elem");
		ME::AttributeExportXML::SetAsUInt(pElement, values[i]);
	}
}

void ME::AttributeExportXML::SetAsMatrix34(XMLElement* pRoot, Matrix value)
{
	pRoot->SetAttribute("type", "matrix34");

	for (size_t i = 0; i < 4; i++)
	{
		char row_name[10];

		sprintf_s(row_name, "r%d", i);
		XMLElement* pRow = pRoot->InsertNewChildElement(row_name);

		ME::AttributeExportXML::SetAsVector3(pRow, Vector3(value.m[0]));
	}
}

void ME::AttributeExportXML::SetAsQuat(XMLElement* pRoot, Quaternion value)
{
	char value_text[255];

	sprintf_s(value_text, "%f, %f, %f, %f", value.x, value.y, value.z, value.w);

	pRoot->SetAttribute("type", "quat");
	pRoot->SetText(value_text);
}

void ME::AttributeExportXML::SetAsVector3(XMLElement* pRoot, Vector3 value)
{
	char value_text[255];

	sprintf_s(value_text, "%f, %f, %f", value.x, value.y, value.z);

	pRoot->SetAttribute("type", "vector3");
	pRoot->SetText(value_text);
}

void ME::AttributeExportXML::SetAsVector4(XMLElement* pRoot, Vector4 value)
{
	char value_text[255];

	sprintf_s(value_text, "%f, %f, %f, %f", value.x, value.y, value.z, value.w);

	pRoot->SetAttribute("type", "vector4");
	pRoot->SetText(value_text);
}

void ME::AttributeExportXML::SetAsString(XMLElement* pRoot, std::string value)
{
	pRoot->SetAttribute("type", "string");
	pRoot->SetText(value.c_str());
}

XMLElement* ME::NodeExportXML(XMLElement* pRoot, std::string name, UINT networkId, UINT parentId, UINT typeId, bool persistent, bool downstreamMultiplyConnected)
{
	XMLElement* pNode = pRoot->InsertNewChildElement("Node");
	pNode->SetAttribute("name", name.c_str());
	pNode->SetAttribute("networkID", networkId);
	pNode->SetAttribute("downstreamParentID", parentId);
	pNode->SetAttribute("typeID", typeId);

	if (persistent)
		pNode->SetAttribute("persistent", "true");

	if (downstreamMultiplyConnected)
		pNode->SetAttribute("downstreamMultiplyConnected", "true");

	return pNode;
}

XMLElement* ME::DataBlockExportXML::DataBlockExportXML(XMLElement* pRoot, UINT lenght, int elements)
{
	XMLElement* pDataBlock = pRoot->InsertNewChildElement("DataBlock");
	pDataBlock->SetAttribute("lenght", lenght);
	pDataBlock->SetAttribute("elements", elements);

	return pDataBlock;
}

XMLElement* ME::DataBlockExportXML::AddElement(XMLElement* pRoot, std::string type, int index, UINT lenght, std::wstring description, BYTE* pData)
{
	XMLElement* pElement = pRoot->InsertNewChildElement("DataElement");
	pElement->SetAttribute("type", type.c_str());
	pElement->SetAttribute("index", index);
	pElement->SetAttribute("bytes", lenght);
	pElement->SetAttribute("description", description.c_str());

	char data_stream[255];

	for (size_t i = 0; i < lenght; i++)
		sprintf_s(data_stream, "%02x,", pData[i]);

	pElement->SetText(data_stream);

	return pElement;
}

XMLElement* ME::ConditionExportXML(XMLElement* pRoot, UINT index, int typeId)
{
	XMLElement* pCondition = pRoot->InsertNewChildElement("Condition");
	pCondition->SetAttribute("index", index);
	pCondition->SetAttribute("typeID", typeId);

	return pCondition;
}

XMLElement* ME::ConditionSetExportXML::ConditionSetExportXML(XMLElement* pRoot, UINT index, int targetNodeId)
{
	XMLElement* pConditionSet = pRoot->InsertNewChildElement("ConditionSet");
	pConditionSet->SetAttribute("index", index);
	pConditionSet->SetAttribute("targetNodeID", targetNodeId);

	return pConditionSet;
}

XMLElement* ME::ConditionSetExportXML::SetConditionIndices(XMLElement* pRoot, std::vector<UINT> indices)
{
	char str[255];

	for (size_t i = 0; i < indices.size(); i++)
		sprintf_s(str, "%d,", indices[i]);

	XMLElement* pConditionIndices = pRoot->InsertNewChildElement("conditionIndices");
	pConditionIndices->SetText(str);

	return pConditionIndices;
}

XMLElement* ME::TakeListXML(XMLElement* pDoc, std::string name, int version)
{
	XMLElement* pTakeList = pDoc->InsertNewChildElement("TakeList");
	pTakeList->SetAttribute("sourceAnimFile", name.c_str());
	pTakeList->SetAttribute("version", version);

	return pTakeList;
}

XMLElement* ME::TakeExportXML(XMLElement* pRoot, std::string name, bool is_loop, float duration, float fps, float clipStart, float clipEnd)
{
	XMLElement* pTake = pRoot->InsertNewChildElement("Take");
	pTake->SetAttribute("name", name.c_str());
	
	XMLElement* pAttributes = ME::AttributeBlockExportXML(pTake);

	XMLElement* pDuration = ME::AttributeExportXML::AttributeExportXML(pAttributes, "secondsDuration");
	ME::AttributeExportXML::SetAsDouble(pDuration, duration);

	XMLElement* pFps = ME::AttributeExportXML::AttributeExportXML(pAttributes, "fps");
	ME::AttributeExportXML::SetAsDouble(pFps, fps);

	XMLElement* pClipStart = ME::AttributeExportXML::AttributeExportXML(pAttributes, "clipStart");
	ME::AttributeExportXML::SetAsDouble(pClipStart, clipStart);

	XMLElement* pClipEnd = ME::AttributeExportXML::AttributeExportXML(pAttributes, "clipEnd");
	ME::AttributeExportXML::SetAsDouble(pClipEnd, clipEnd);

	XMLElement* pLoop = ME::AttributeExportXML::AttributeExportXML(pAttributes, "loop");
	ME::AttributeExportXML::SetAsBool(pLoop, is_loop);

	return pTake;
}

XMLElement* ME::DiscreteEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData)
{
	XMLElement* pEventTrack = pRoot->InsertNewChildElement("DiscreteEventTrack");
	pEventTrack->SetAttribute("name", name.c_str());
	pEventTrack->SetAttribute("guid", guid.c_str());
	pEventTrack->SetAttribute("channelID", channelId);

	XMLElement* pAttributes = ME::AttributeBlockExportXML(pEventTrack);

	XMLElement* pUserData = ME::AttributeExportXML::AttributeExportXML(pAttributes, "userData");
	ME::AttributeExportXML::SetAsUInt(pUserData, userData);

	return pEventTrack;
}

XMLElement* ME::DiscreteEventExportXML(XMLElement* pRoot, UINT eventIdx, UINT userData, float startTime)
{
	XMLElement* pEvent = pRoot->InsertNewChildElement("DiscreteEvent");
	pEvent->SetAttribute("index", eventIdx);

	XMLElement* pAttributes = ME::AttributeBlockExportXML(pEvent);

	XMLElement* pUserData = ME::AttributeExportXML::AttributeExportXML(pAttributes, "userData");
	ME::AttributeExportXML::SetAsUInt(pUserData, userData);

	XMLElement* pStartTime = ME::AttributeExportXML::AttributeExportXML(pAttributes, "startTime");
	ME::AttributeExportXML::SetAsDouble(pStartTime, startTime);

	return pEvent;
}

XMLElement* ME::CurveEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData)
{
	XMLElement* pEventTrack = pRoot->InsertNewChildElement("CurveEventTrack");
	pEventTrack->SetAttribute("name", name.c_str());
	pEventTrack->SetAttribute("guid", guid.c_str());
	pEventTrack->SetAttribute("channelID", channelId);

	XMLElement* pAttributes = ME::AttributeBlockExportXML(pEventTrack);

	XMLElement* pUserData = ME::AttributeExportXML::AttributeExportXML(pAttributes, "userData");
	ME::AttributeExportXML::SetAsUInt(pUserData, userData);

	return pEventTrack;
}

XMLElement* ME::CurveEventExportXML(XMLElement* pRoot, UINT eventIdx, UINT userData, float startTime, float floatVal)
{
	XMLElement* pEvent = pRoot->InsertNewChildElement("CurveEvent");
	pEvent->SetAttribute("index", eventIdx);

	XMLElement* pAttributes = ME::AttributeBlockExportXML(pEvent);

	XMLElement* pUserData = ME::AttributeExportXML::AttributeExportXML(pAttributes, "userData");
	ME::AttributeExportXML::SetAsUInt(pUserData, userData);

	XMLElement* pStartTime = ME::AttributeExportXML::AttributeExportXML(pAttributes, "startTime");
	ME::AttributeExportXML::SetAsDouble(pStartTime, startTime);

	XMLElement* pFloatVal = ME::AttributeExportXML::AttributeExportXML(pAttributes, "floatVal");
	ME::AttributeExportXML::SetAsDouble(pFloatVal, floatVal);

	return pEvent;
}

XMLElement* ME::DurationEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData)
{
	XMLElement* pEventTrack = pRoot->InsertNewChildElement("DurationEventTrack");
	pEventTrack->SetAttribute("name", name.c_str());
	pEventTrack->SetAttribute("guid", guid.c_str());
	pEventTrack->SetAttribute("channelID", channelId);

	XMLElement* pAttributes = ME::AttributeBlockExportXML(pEventTrack);

	XMLElement* pUserData = ME::AttributeExportXML::AttributeExportXML(pAttributes, "userData");
	ME::AttributeExportXML::SetAsUInt(pUserData, userData);

	return pEventTrack;
}

XMLElement* ME::DurationEventExportXML(XMLElement* pRoot, UINT eventIdx, UINT userData, float startTime, float duration)
{
	XMLElement* pEvent = pRoot->InsertNewChildElement("DurationEvent");
	pEvent->SetAttribute("index", eventIdx);

	XMLElement* pAttributes = ME::AttributeBlockExportXML(pEvent);

	XMLElement* pUserData = ME::AttributeExportXML::AttributeExportXML(pAttributes, "userData");
	ME::AttributeExportXML::SetAsUInt(pUserData, userData);

	XMLElement* pStartTime = ME::AttributeExportXML::AttributeExportXML(pAttributes, "startTime");
	ME::AttributeExportXML::SetAsDouble(pStartTime, startTime);

	XMLElement* pFloatVal = ME::AttributeExportXML::AttributeExportXML(pAttributes, "duration");
	ME::AttributeExportXML::SetAsDouble(pFloatVal, duration);

	return pEvent;
}

void ME::SaveFile(tinyxml2::XMLDocument* pDoc, std::string path, std::string filename, bool compact)
{
	std::filesystem::create_directories(path);

	std::string full_path = path + filename + ".xml";

	pDoc->SaveFile(full_path.c_str(), compact);
}