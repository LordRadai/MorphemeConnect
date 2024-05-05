#pragma once
#include "../MorphemeBundle/MorphemeBundle_NetworkDef.h"
#include "../MorphemeBundle/MorphemeBundle_EventTrack.h"
#include "TinyXML/tinyxml2.h"

using namespace tinyxml2;

namespace ME
{
	XMLElement* NodeExportXML(XMLElement* pRoot, std::string name, UINT network_id, UINT parent_id, UINT type_id, bool persistent, bool downstream_multiply_connected);
	XMLElement* TakeListXML(XMLElement* pDoc, std::string name, int version);
	XMLElement* TakeExportXML(XMLElement* pRoot, std::string name, bool is_loop, float duration, float fps, float clipStart, float clipEnd);
	XMLElement* DiscreteEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track);
	XMLElement* DiscreteEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time);
	XMLElement* CurveEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track);
	XMLElement* CurveEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time, float end_time);
	XMLElement* DurationEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track);
	XMLElement* DurationEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time, float end_time);
}