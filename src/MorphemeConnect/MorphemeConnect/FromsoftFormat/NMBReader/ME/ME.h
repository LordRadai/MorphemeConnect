#pragma once
#include "../MorphemeBundle/MorphemeBundle_NetworkDef.h"
#include "../MorphemeBundle/MorphemeBundle_EventTrack.h"
#include "TinyXML/tinyxml2.h"

using namespace tinyxml2;

namespace ME
{
	void NodeExportXML(XMLElement* pRoot, std::string name, UINT network_id, UINT parent_id, UINT type_id, bool persistent, bool downstream_multiply_connected);
	void DiscreteEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track);
	void DiscreteEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time)
}