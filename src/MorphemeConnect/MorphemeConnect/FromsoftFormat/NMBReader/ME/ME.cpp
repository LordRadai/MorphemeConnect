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
	
	XMLElement* pAttributes = pTake->InsertNewChildElement("Attributes");

	XMLElement* pDuration = pAttributes->InsertNewChildElement("secondsDuration");
	pDuration->SetAttribute("type", "double");
	pDuration->SetText(duration);

	XMLElement* pFps = pAttributes->InsertNewChildElement("fps");
	pFps->SetAttribute("type", "double");
	pFps->SetText(30);

	XMLElement* pClipStart = pAttributes->InsertNewChildElement("clipStart");
	pClipStart->SetAttribute("type", "double");
	pClipStart->SetText(clipStart);

	XMLElement* pClipEnd = pAttributes->InsertNewChildElement("clipEnd");
	pClipEnd->SetAttribute("type", "double");
	pClipEnd->SetText(clipEnd);

	XMLElement* loop = pAttributes->InsertNewChildElement("loop");
	loop->SetAttribute("type", "bool");

	if (is_loop)
		loop->SetText("true");
	else
		loop->SetText("false");

	return pTake;
}

XMLElement* ME::DiscreteEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData)
{
	XMLElement* pEventTrack = pRoot->InsertNewChildElement("DiscreteEventTrack");
	pEventTrack->SetAttribute("name", name.c_str());
	pEventTrack->SetAttribute("guid", guid.c_str());
	pEventTrack->SetAttribute("channelID", channelId);

	XMLElement* pAttributes = pEventTrack->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(userData);

	return pEventTrack;
}

XMLElement* ME::DiscreteEventExportXML(XMLElement* pRoot, int eventIdx, int userData, float startTime)
{
	XMLElement* pEvent = pRoot->InsertNewChildElement("DiscreteEvent");
	pEvent->SetAttribute("index", eventIdx);

	XMLElement* pAttributes = pEvent->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(userData);

	XMLElement* pStartTime = pAttributes->InsertNewChildElement("startTime");
	pStartTime->SetAttribute("type", "double");
	pStartTime->SetText(startTime);

	return pEvent;
}

XMLElement* ME::CurveEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData)
{
	XMLElement* pEventTrack = pRoot->InsertNewChildElement("CurveEventTrack");
	pEventTrack->SetAttribute("name", name.c_str());
	pEventTrack->SetAttribute("guid", guid.c_str());
	pEventTrack->SetAttribute("channelID", channelId);

	XMLElement* pAttributes = pEventTrack->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(userData);

	return pEventTrack;
}

XMLElement* ME::CurveEventExportXML(XMLElement* pRoot, int eventIdx, int userData, float startTime, float endTime)
{
	XMLElement* pEvent = pRoot->InsertNewChildElement("CurveEvent");
	pEvent->SetAttribute("index", eventIdx);

	XMLElement* pAttributes = pEvent->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(userData);

	XMLElement* pStartTime = pAttributes->InsertNewChildElement("startTime");
	pStartTime->SetAttribute("type", "double");
	pStartTime->SetText(startTime);

	XMLElement* pEndTime = pAttributes->InsertNewChildElement("duration");
	pEndTime->SetAttribute("type", "double");
	pEndTime->SetText(endTime);

	return pEvent;
}

XMLElement* ME::DurationEventTrackExportXML(XMLElement* pRoot, std::string name, std::string guid, int channelId, int userData)
{
	XMLElement* pEventTrack = pRoot->InsertNewChildElement("DurationEventTrack");
	pEventTrack->SetAttribute("name", name.c_str());
	pEventTrack->SetAttribute("guid", guid.c_str());
	pEventTrack->SetAttribute("channelID", channelId);

	XMLElement* pAttributes = pEventTrack->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(userData);

	return pEventTrack;
}

XMLElement* ME::DurationEventExportXML(XMLElement* pRoot, int eventIdx, int userData, float startTime, float endTime)
{
	XMLElement* pEvent = pRoot->InsertNewChildElement("DurationEvent");
	pEvent->SetAttribute("index", eventIdx);

	XMLElement* pAttributes = pEvent->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(userData);

	XMLElement* pStartTime = pAttributes->InsertNewChildElement("startTime");
	pStartTime->SetAttribute("type", "double");
	pStartTime->SetText(startTime);

	XMLElement* pEndTime = pAttributes->InsertNewChildElement("duration");
	pEndTime->SetAttribute("type", "double");
	pEndTime->SetText(endTime);

	return pEvent;
}

void ME::SaveFile(tinyxml2::XMLDocument* pDoc, std::string path, std::string filename, bool compact)
{
	std::filesystem::create_directories(path);

	std::string full_path = path + filename + ".xml";

	pDoc->SaveFile(full_path.c_str(), compact);
}