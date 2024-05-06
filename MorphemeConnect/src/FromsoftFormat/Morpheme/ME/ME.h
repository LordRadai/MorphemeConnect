#pragma once
#include <SimpleMath.h>
#include "TinyXML/tinyxml2.h"

using namespace DirectX::SimpleMath;
using namespace tinyxml2;

namespace ME
{
	XMLElement* AnimationLibraryXML(XMLElement* pRoot, std::string guid);

	namespace AnimationSetExportXML
	{
		XMLElement* AnimationSetExportXML(XMLElement* pRoot, int index, std::string name);
		XMLElement* SetCharacterController(XMLElement* pRoot, std::string guid, std::string filename);
		XMLElement* SetRig(XMLElement* pRoot, std::string guid, std::string filename);
		XMLElement* SetPhysicsRig(XMLElement* pRoot, std::string guid, std::string filename);
	}

	namespace AnimationEntryExportXML
	{
		XMLElement* AnimationEntryExportXML(XMLElement* pRoot, UINT index, std::string format, std::string options);
		XMLElement* SetAnimFile(XMLElement* pRoot, std::string animFile);
		XMLElement* SetTakeFile(XMLElement* pRoot, std::string takeFile);
		XMLElement* SetTake(XMLElement* pRoot, std::string take);
		XMLElement* SetSyncTrack(XMLElement* pRoot, std::string syncTrack);
	}

	namespace NetworkDefExportXML
	{
		XMLElement* NetworkDefExportXML(XMLElement* pRoot, std::string guid, std::string name);
		void SetWorldOrientation(XMLElement* pRoot, Vector3 forward, Vector3 right, Vector3 up);
		XMLElement* SetRootNodeNetworkID(XMLElement* pRoot, UINT nodeId);
		XMLElement* SetAnimLibraryRef(XMLElement* pRoot, std::string guid, std::string filename);
		XMLElement* SetMessagePresetLibraryRef(XMLElement* pRoot, std::string guid, std::string filename);
	}

	namespace DataBlockExportXML
	{
		XMLElement* DataBlockExportXML(XMLElement* pRoot);
		XMLElement* AddElement(XMLElement* pRoot, void* pData, UINT lenght, std::string type, std::string description);
		XMLElement* WriteBool(XMLElement* pRoot, bool value, std::string description);
		XMLElement* WriteBoolArray(XMLElement* pRoot, bool* values, UINT count, std::string description);
		XMLElement* WriteChar(XMLElement* pRoot, char value, std::string description);
		XMLElement* WriteCharArray(XMLElement* pRoot, char* values, UINT count, std::string description);
		XMLElement* WriteInt(XMLElement* pRoot, int value, std::string description);
		XMLElement* WriteIntArray(XMLElement* pRoot, int* values, UINT count, std::string description);
		XMLElement* WriteUInt(XMLElement* pRoot, UINT value, std::string description);
		XMLElement* WriteUIntArray(XMLElement* pRoot, UINT* values, UINT count, std::string description);
		XMLElement* WriteFloat(XMLElement* pRoot, float value, std::string description);
		XMLElement* WriteFloatArray(XMLElement* pRoot, float* values, UINT count, std::string description);
		XMLElement* WriteDouble(XMLElement* pRoot, double value, std::string description);
		XMLElement* WriteDoubleArray(XMLElement* pRoot, double* values, UINT count, std::string description);
		XMLElement* WriteString(XMLElement* pRoot, std::string value, std::string description);
		XMLElement* WriteUnicodeString(XMLElement* pRoot, std::wstring value, std::string description);
		XMLElement* WriteAnimationId(XMLElement* pRoot, UINT value, std::string description);
		XMLElement* WriteNetworkNodeId(XMLElement* pRoot, UINT value, std::string description);
		XMLElement* WriteNetworkNodeId(XMLElement* pRoot, UINT value, UINT pinIndex, std::string description);
	}

	namespace ConditionSetExportXML
	{
		XMLElement* ConditionSetExportXML(XMLElement* pRoot, UINT index, int targetNodeId);
		XMLElement* SetConditionIndices(XMLElement* pRoot, std::vector<UINT> indices);
	}

	namespace RigExportXML
	{
		XMLElement* RigExportXML(XMLElement* pRoot, std::string guid, std::string name, float rigScale);
		XMLElement* SetHipIndex(XMLElement* pRoot, UINT index);
		XMLElement* SetTrajectoryIndex(XMLElement* pRoot, UINT index);
		XMLElement* SetBlendFrameOrientationQuat(XMLElement* pRoot, Quaternion orientation);
		XMLElement* SetBlendFramePositionVecVec(XMLElement* pRoot, Vector3 position);
		XMLElement* SetRigSourceFilename(XMLElement* pRoot, std::string filename);
		XMLElement* SetRigRetargetScale(XMLElement* pRoot, float rigRetargetScale);
		XMLElement* SetMirrorPlane(XMLElement* pRoot, UINT plane);
		XMLElement* AddJointMirrorMapping(XMLElement* pRoot, UINT index, UINT first, UINT second);
	}

	namespace JointExportXML
	{
		XMLElement* JointExportXML(XMLElement* pRoot, UINT index, std::string name, UINT parentIdx);
		void AddBodyPlanTag(XMLElement* pRoot, std::string bodyPlanTag);
		void AddRetargetTag(XMLElement* pRoot, std::string retargetTag);
		XMLElement* SetOrientation(XMLElement* pRoot, Quaternion rotation);
		XMLElement* SetTranslation(XMLElement* pRoot, Vector3 translation);
		XMLElement* SetOrientationOffset(XMLElement* pRoot, Quaternion orientationOffset);
		XMLElement* SetTranslationOffset(XMLElement* pRoot, Vector3 translationOffset);
		XMLElement* SetPostOrientationOffset(XMLElement* pRoot, Quaternion postOrientationOffset);
	}

	namespace CharacterControllerExportXML
	{
		XMLElement* CharacterControllerExportXML(XMLElement* pRoot, std::string guid, std::string name);
		XMLElement* SetShape(XMLElement* pRoot, std::string shape);
		XMLElement* SetHeight(XMLElement* pRoot, float height);
		XMLElement* SetRadius(XMLElement* pRoot, float radius);
		XMLElement* SetColour(XMLElement* pRoot, Vector3 color);
		XMLElement* SetIsVisible(XMLElement* pRoot, bool isVisible);
		XMLElement* SetSkinWidth(XMLElement* pRoot, float skinWidth);
		XMLElement* SetMaxPushForce(XMLElement* pRoot, float maxPushForce);
		XMLElement* SetMaxSlopeAngle(XMLElement* pRoot, float maxSlopeAngle);
		XMLElement* SetStepHeight(XMLElement* pRoot, float stepHeight);
	}

	XMLElement* AttributeBlockExportXML(XMLElement* pRoot);

	namespace AttributeExportXML
	{
		XMLElement* AttributeExportXML(XMLElement* pRoot, std::string name);
		void SetAsBool(XMLElement* pRoot, bool value);
		void SetAsBoolArray(XMLElement* pRoot, bool* values, UINT size);
		void SetAsDouble(XMLElement* pRoot, double value);
		void SetAsFloatArray(XMLElement* pRoot, double* values, UINT size);
		void SetAsInt(XMLElement* pRoot, int value);
		void SetAsIntArray(XMLElement* pRoot, int* values, UINT size);
		void SetAsUInt(XMLElement* pRoot, UINT value);
		void SetAsUIntArray(XMLElement* pRoot, UINT* values, UINT size);
		void SetAsMatrix34(XMLElement* pRoot, Matrix value);
		void SetAsQuat(XMLElement* pRoot, Quaternion value);
		void SetAsVector3(XMLElement* pRoot, Vector3 value);
		void SetAsVector4(XMLElement* pRoot, Vector4 value);
		void SetAsString(XMLElement* pRoot, std::string value);
		void SetAsStringArray(XMLElement* pRoot, std::string* values, UINT size);
	}

	XMLElement* MessagePresetLibraryExportXML(XMLElement* pRoot, std::string guid);
	XMLElement* MessagePresetListExportXML(XMLElement* pRoot, int messageType, std::string name);
	XMLElement* MessagePresetExportXML(XMLElement* pRoot, std::string name);

	XMLElement* MessageExportXML(XMLElement* pRoot, std::string name, UINT messageTypeId, UINT messageId);
	XMLElement* NodeExportXML(XMLElement* pRoot, std::string name, UINT networkId, UINT parentId, UINT typeId, bool persistent, bool downstreamMultiplyConnected);
	XMLElement* ConditionExportXML(XMLElement* pRoot, UINT index, int typeId);
	XMLElement* TakeListXML(XMLElement* pDoc, std::string name, int version);
	XMLElement* TakeExportXML(XMLElement* pRoot, std::string name, bool is_loop, float duration, float fps, float clipStart, float clipEnd);
	XMLElement* DiscreteEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData);
	XMLElement* DiscreteEventExportXML(XMLElement* pRoot, UINT eventIdx, UINT userData, float startTime);
	XMLElement* CurveEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData);
	XMLElement* CurveEventExportXML(XMLElement* pRoot, UINT eventIdx, UINT userData, float startTime, float floatVal);
	XMLElement* DurationEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData);
	XMLElement* DurationEventExportXML(XMLElement* pRoot, UINT eventIdx, UINT userData, float startTime, float duration);

	void SaveFile(tinyxml2::XMLDocument* pDoc, std::string path, std::string filename, bool compact = false);
}