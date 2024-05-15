#include <Windows.h>
#include <fstream>
#include "../../MR/MR.h"

using namespace std;
using namespace MR;

namespace ME
{
	void ExportEvent(ofstream* out, int alignment, EventTrack::Event* event);
	void ExportEventTrack(ofstream* out, int alignment, EventTrack* eventTrack);
	void ExportStringTable(ofstream* out, int alignment, StringTable* table);
}