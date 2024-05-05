#pragma once
#include <SimpleMath.h>
#include "TinyXML/tinyxml2.h"

using namespace DirectX::SimpleMath;
using namespace tinyxml2;

namespace ME
{
	namespace NetworkDefExportXML
	{
		XMLElement* NetworkDefExportXML(XMLElement* pRoot, std::string guid, std::string name);
		void SetWorldOrientation(XMLElement* pRoot, Vector3 forward, Vector3 right, Vector3 up);
		XMLElement* SetRootNodeNetworkID(XMLElement* pRoot, UINT nodeId);
		XMLElement* AddMessage(XMLElement* pRoot, std::string name, UINT messageTypeId, UINT messageId);
		XMLElement* SetAnimLibraryRef(XMLElement* pRoot, std::string guid, std::string filename);
		XMLElement* SetMessagePresetLibraryRef(XMLElement* pRoot, std::string guid, std::string filename);
	}

	namespace DataBlockExportXML
	{
		XMLElement* DataBlockExportXML(XMLElement* pRoot, UINT lenght, int elements);
		XMLElement* AddElement(XMLElement* pRoot, std::string type, int index, UINT lenght, std::wstring description, BYTE* pData);
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
		XMLElement* SetShape(XMLElement* pRoot, std::string name);
	}

	XMLElement* AttributeBlockExportXML(XMLElement* pRoot);

	namespace AttributeExportXML
	{
		XMLElement* AttributeExportXML(XMLElement* pRoot, std::string name);
		void SetAsBool(XMLElement* pRoot, bool value);
		void SetAsBoolArray(XMLElement* pRoot, bool* values, UINT size);
		void SetAsDouble(XMLElement* pRoot, double value);
		void SetAsDoubleArray(XMLElement* pRoot, double* values, UINT size);
		void SetAsInt(XMLElement* pRoot, int value);
		void SetAsIntArray(XMLElement* pRoot, int* values, UINT size);
		void SetAsUInt(XMLElement* pRoot, UINT value);
		void SetAsUIntArray(XMLElement* pRoot, UINT* values, UINT size);
		void SetAsMatrix34(XMLElement* pRoot, Matrix value);
		void SetAsQuat(XMLElement* pRoot, Quaternion value);
		void SetAsVector3(XMLElement* pRoot, Vector3 value);
		void SetAsVector4(XMLElement* pRoot, Vector4 value);
		void SetAsString(XMLElement* pRoot, std::string value);
	}

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