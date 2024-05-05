#include "ME.h"

void ME::NodeExportXML(XMLElement* pRoot, std::string name, UINT network_id, UINT parent_id, UINT type_id, bool persistent, bool downstream_multiply_connected)
{
	XMLElement* pRoot = pRoot->InsertNewChildElement("Node");
	pRoot->SetAttribute("name", name.c_str());
	pRoot->SetAttribute("networkID", network_id);
	pRoot->SetAttribute("downstreamParentID", parent_id);
	pRoot->SetAttribute("typeID", type_id);

	if (persistent)
		pRoot->SetAttribute("persistent", "true");

	if (downstream_multiply_connected)
		pRoot->SetAttribute("downstreamMultiplyConnected", "true");
}

void ME::TakeListXML(tinyxml2::XMLDocument* pDoc, std::string name, int version)
{
	tinyxml2::XMLElement* pRoot = pDoc->NewElement("TakeList");
	pRoot->SetAttribute("sourceAnimFile", name.c_str());
	pRoot->SetAttribute("version", version);
}

void ME::TakeExportXML(XMLElement* pRoot, std::string name, bool is_loop, float duration, float fps, float clipStart, float clipEnd)
{
	XMLElement* take = pRoot->InsertNewChildElement("Take");
	take->SetAttribute("name", name.c_str());
	
	XMLElement* attributes = take->InsertNewChildElement("Attributes");

	XMLElement* pDuration = attributes->InsertNewChildElement("secondsDuration");
	pDuration->SetAttribute("type", "double");
	pDuration->SetText(duration);

	XMLElement* pFps = attributes->InsertNewChildElement("fps");
	pFps->SetAttribute("type", "double");
	pFps->SetText(30);

	XMLElement* pClipStart = attributes->InsertNewChildElement("clipStart");
	pClipStart->SetAttribute("type", "double");
	pClipStart->SetText(clipStart);

	XMLElement* pClipEnd = attributes->InsertNewChildElement("clipEnd");
	pClipEnd->SetAttribute("type", "double");
	pClipEnd->SetText(clipEnd);

	XMLElement* loop = attributes->InsertNewChildElement("loop");
	loop->SetAttribute("type", "bool");

	if (is_loop)
		loop->SetText("true");
	else
		loop->SetText("false");
}

void ME::DiscreteEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track)
{
	XMLElement* discreteEventTrack = pRoot->InsertNewChildElement("DiscreteEventTrack");
	discreteEventTrack->SetAttribute("name", event_track->m_data->m_trackName);
	discreteEventTrack->SetAttribute("guid", event_track->GetGUID().c_str());
	discreteEventTrack->SetAttribute("channelID", event_track->m_data->m_channelId);

	XMLElement* attributeET = pRoot->InsertNewChildElement("Attributes");

	XMLElement* userData = pRoot->InsertNewChildElement("userData");
	userData->SetAttribute("type", "uint");
	userData->SetText(event_track->m_data->m_eventId);

	for (size_t i = 0; i < event_track->m_data->m_numEvents; i++)
		ME::DiscreteEventExportXML(discreteEventTrack, i, event_track->m_data->m_events[i].m_value, event_track->m_data->m_events[i].m_start);
}

void ME::DiscreteEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time)
{
	XMLElement* discreteEvent = pRoot->InsertNewChildElement("DiscreteEvent");
	discreteEvent->SetAttribute("index", event_idx);

	XMLElement* attributesEvent = pRoot->InsertNewChildElement("Attributes");

	XMLElement* userData = attributesEvent->InsertNewChildElement("userData");
	userData->SetAttribute("type", "uint");
	userData->SetText(user_data);

	XMLElement* startTime = userData->InsertNewChildElement("startTime");
	startTime->SetAttribute("type", "double");
	startTime->SetText(start_time);
}

void ME::CurveEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track)
{
	XMLElement* discreteEventTrack = pRoot->InsertNewChildElement("CurveEventTrack");
	discreteEventTrack->SetAttribute("name", event_track->m_data->m_trackName);
	discreteEventTrack->SetAttribute("guid", event_track->GetGUID().c_str());
	discreteEventTrack->SetAttribute("channelID", event_track->m_data->m_channelId);

	XMLElement* attributeET = pRoot->InsertNewChildElement("Attributes");

	XMLElement* userData = pRoot->InsertNewChildElement("userData");
	userData->SetAttribute("type", "uint");
	userData->SetText(event_track->m_data->m_eventId);

	for (size_t i = 0; i < event_track->m_data->m_numEvents; i++)
		ME::CurveEventExportXML(discreteEventTrack, i, event_track->m_data->m_events[i].m_value, event_track->m_data->m_events[i].m_start, event_track->m_data->m_events[i].m_duration);
}

void ME::CurveEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time, float end_time)
{
	XMLElement* discreteEvent = pRoot->InsertNewChildElement("CurveEvent");
	discreteEvent->SetAttribute("index", event_idx);

	XMLElement* attributesEvent = pRoot->InsertNewChildElement("Attributes");

	XMLElement* userData = attributesEvent->InsertNewChildElement("userData");
	userData->SetAttribute("type", "uint");
	userData->SetText(user_data);

	XMLElement* startTime = userData->InsertNewChildElement("startTime");
	startTime->SetAttribute("type", "double");
	startTime->SetText(start_time);

	XMLElement* endTime = userData->InsertNewChildElement("duration");
	startTime->SetAttribute("type", "double");
	startTime->SetText(end_time);
}

void ME::DurationEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track)
{
	XMLElement* discreteEventTrack = pRoot->InsertNewChildElement("DurationEventTrack");
	discreteEventTrack->SetAttribute("name", event_track->m_data->m_trackName);
	discreteEventTrack->SetAttribute("guid", event_track->GetGUID().c_str());
	discreteEventTrack->SetAttribute("channelID", event_track->m_data->m_channelId);

	XMLElement* attributeET = pRoot->InsertNewChildElement("Attributes");

	XMLElement* userData = pRoot->InsertNewChildElement("userData");
	userData->SetAttribute("type", "uint");
	userData->SetText(event_track->m_data->m_eventId);
}

void ME::DurationEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time, float end_time)
{
	XMLElement* discreteEvent = pRoot->InsertNewChildElement("DurationEvent");
	discreteEvent->SetAttribute("index", event_idx);

	XMLElement* attributesEvent = pRoot->InsertNewChildElement("Attributes");

	XMLElement* userData = attributesEvent->InsertNewChildElement("userData");
	userData->SetAttribute("type", "uint");
	userData->SetText(user_data);

	XMLElement* startTime = userData->InsertNewChildElement("startTime");
	startTime->SetAttribute("type", "double");
	startTime->SetText(start_time);

	XMLElement* endTime = userData->InsertNewChildElement("duration");
	startTime->SetAttribute("type", "double");
	startTime->SetText(end_time);
}