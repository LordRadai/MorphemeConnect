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