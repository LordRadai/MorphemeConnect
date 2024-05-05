#include "ME.h"

XMLElement* ME::NodeExportXML(XMLElement* pRoot, std::string name, UINT network_id, UINT parent_id, UINT type_id, bool persistent, bool downstream_multiply_connected)
{
	XMLElement* pNode = pRoot->InsertNewChildElement("Node");
	pRoot->SetAttribute("name", name.c_str());
	pRoot->SetAttribute("networkID", network_id);
	pRoot->SetAttribute("downstreamParentID", parent_id);
	pRoot->SetAttribute("typeID", type_id);

	if (persistent)
		pRoot->SetAttribute("persistent", "true");

	if (downstream_multiply_connected)
		pRoot->SetAttribute("downstreamMultiplyConnected", "true");

	return pNode;
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

XMLElement* ME::DiscreteEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track)
{
	XMLElement* pEventTrack = pRoot->InsertNewChildElement("DiscreteEventTrack");
	pEventTrack->SetAttribute("name", event_track->m_data->m_trackName);
	pEventTrack->SetAttribute("guid", event_track->GetGUID().c_str());
	pEventTrack->SetAttribute("channelID", event_track->m_data->m_channelId);

	XMLElement* pAttributes = pEventTrack->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(event_track->m_data->m_eventId);

	return pEventTrack;
}

XMLElement* ME::DiscreteEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time)
{
	XMLElement* pEvent = pRoot->InsertNewChildElement("DiscreteEvent");
	pEvent->SetAttribute("index", event_idx);

	XMLElement* pAttributes = pEvent->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(user_data);

	XMLElement* pStartTime = pAttributes->InsertNewChildElement("startTime");
	pStartTime->SetAttribute("type", "double");
	pStartTime->SetText(start_time);

	return pEvent;
}

XMLElement* ME::CurveEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track)
{
	XMLElement* pEventTrack = pRoot->InsertNewChildElement("CurveEventTrack");
	pEventTrack->SetAttribute("name", event_track->m_data->m_trackName);
	pEventTrack->SetAttribute("guid", event_track->GetGUID().c_str());
	pEventTrack->SetAttribute("channelID", event_track->m_data->m_channelId);

	XMLElement* pAttributes = pEventTrack->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(event_track->m_data->m_eventId);

	return pEventTrack;
}

XMLElement* ME::CurveEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time, float end_time)
{
	XMLElement* pEvent = pRoot->InsertNewChildElement("CurveEvent");
	pEvent->SetAttribute("index", event_idx);

	XMLElement* pAttributes = pEvent->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(user_data);

	XMLElement* pStartTime = pAttributes->InsertNewChildElement("startTime");
	pStartTime->SetAttribute("type", "double");
	pStartTime->SetText(start_time);

	XMLElement* pEndTime = pAttributes->InsertNewChildElement("duration");
	pEndTime->SetAttribute("type", "double");
	pEndTime->SetText(end_time);

	return pEvent;
}

XMLElement* ME::DurationEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track)
{
	XMLElement* pEventTrack = pRoot->InsertNewChildElement("DurationEventTrack");
	pEventTrack->SetAttribute("name", event_track->m_data->m_trackName);
	pEventTrack->SetAttribute("guid", event_track->GetGUID().c_str());
	pEventTrack->SetAttribute("channelID", event_track->m_data->m_channelId);

	XMLElement* pAttributes = pEventTrack->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(event_track->m_data->m_eventId);

	return pEventTrack;
}

XMLElement* ME::DurationEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time, float end_time)
{
	XMLElement* pEvent = pRoot->InsertNewChildElement("DurationEvent");
	pEvent->SetAttribute("index", event_idx);

	XMLElement* pAttributes = pEvent->InsertNewChildElement("Attributes");

	XMLElement* pUserData = pAttributes->InsertNewChildElement("userData");
	pUserData->SetAttribute("type", "uint");
	pUserData->SetText(user_data);

	XMLElement* pStartTime = pAttributes->InsertNewChildElement("startTime");
	pStartTime->SetAttribute("type", "double");
	pStartTime->SetText(start_time);

	XMLElement* pEndTime = pAttributes->InsertNewChildElement("duration");
	pEndTime->SetAttribute("type", "double");
	pEndTime->SetText(end_time);

	return pEvent;
}