#pragma once
#include "../MorphemeBundle/MorphemeBundle_NetworkDef.h"
#include "../MorphemeBundle/MorphemeBundle_EventTrack.h"
#include "TinyXML/tinyxml2.h"
#include <SimpleMath.h>

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

	XMLElement* NodeExportXML(XMLElement* pRoot, std::string name, UINT networkId, UINT parentId, UINT typeId, bool persistent, bool downstreamMultiplyConnected);
	XMLElement* ConditionExportXML(XMLElement* pRoot, UINT index, int typeId);

	namespace ConditionSetExportXML
	{
		XMLElement* ConditionSetExportXML(XMLElement* pRoot, UINT index, int targetNodeId);
		XMLElement* SetConditionIndices(XMLElement* pRoot, std::vector<UINT> indices);
	}

	XMLElement* TakeListXML(XMLElement* pDoc, std::string name, int version);
	XMLElement* TakeExportXML(XMLElement* pRoot, std::string name, bool is_loop, float duration, float fps, float clipStart, float clipEnd);
	XMLElement* DiscreteEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData);
	XMLElement* DiscreteEventExportXML(XMLElement* pRoot, int eventIdx, int userData, float startTime);
	XMLElement* CurveEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData);
	XMLElement* CurveEventExportXML(XMLElement* pRoot, int eventIdx, int userData, float startTime, float endTime);
	XMLElement* DurationEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData);
	XMLElement* DurationEventExportXML(XMLElement* pRoot, int eventIdx, int userData, float startTime, float endTime);
}