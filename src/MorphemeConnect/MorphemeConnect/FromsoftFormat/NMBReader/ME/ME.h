#pragma once
#include "../MorphemeBundle/MorphemeBundle_NetworkDef.h"
#include "../MorphemeBundle/MorphemeBundle_EventTrack.h"
#include "TinyXML/tinyxml2.h"

using namespace tinyxml2;

namespace ME
{
	void NodeExportXML(XMLElement* pRoot, std::string name, UINT network_id, UINT parent_id, UINT type_id, bool persistent, bool downstream_multiply_connected);
	
	void TakeListXML(tinyxml2::XMLDocument* pDoc, std::string name);
	void TakeExportXML(XMLElement* pRoot, std::string name, NodeAttribBool* is_loop, NodeAttribSourceAnim* source_anim, NodeAttribSourceEventTrack* event_track);
	void DiscreteEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track);
	void DiscreteEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time);
	void CurveEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track);
	void CurveEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time, float end_time);
	void DurationEventTrackExportXML(XMLElement* pRoot, MorphemeBundle_EventTrack* event_track);
	void DurationEventExportXML(XMLElement* pRoot, int event_idx, int user_data, float start_time, float end_time);
}