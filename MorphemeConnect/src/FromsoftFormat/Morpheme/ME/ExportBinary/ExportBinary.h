#include <Windows.h>
#include <fstream>
#include "../../MR/MR.h"

using namespace std;
using namespace MR;

namespace ME
{
	void ExportEvent(ofstream* out, int alignment, EventTrack::Event* event);
	void ExportEventTrack(ofstream* out, int alignment, EventTrack* eventTrack);
	void ExportAttribute(ofstream* out, int alignment, Attribute* attribute);
	void ExportNodeDef(ofstream* out, int alignment, NodeDef* nodeDef);
	void ExportNetworkDef(ofstream* out, int alignment, NetworkDef* networkDef);
	void ExportStringTable(ofstream* out, int alignment, StringTable* table);
	void ExportRig(ofstream* out, int alignment, Rig* rig);
	void ExportRigBindPose(ofstream* out, int alignment, BindPose* bindPose);
	void ExportCharacterController(ofstream* out, int alignment, CharacterController* characterController);
	void ExportRigToAnimMap(ofstream* out, int alignment, RigToAnimMap* rigToAnimMap);
}