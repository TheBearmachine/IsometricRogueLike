#pragma once
#include "Typedefs.h"

namespace ActionHelper
{
    namespace Conditions
    {
        const Condition DontFetchItem("FetchItem", 0);
        const Condition DoFetchItem("FetchItem", 1);
        const Condition DontGotoTile("GotoTile", 0);
        const Condition DoGotoTile("GotoTile", 1);
    }
}