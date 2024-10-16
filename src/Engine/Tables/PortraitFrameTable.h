#pragma once

#include <vector>

#include "Engine/Data/FrameEnums.h"
#include "Engine/Objects/CharacterEnums.h"
#include "Engine/Time/Duration.h"

struct PortraitFrame {
    CharacterPortrait portrait;
    uint16_t uTextureID; // TODO(captainurist): actually portraitIndex.
    Duration uAnimTime;
    Duration uAnimLength;
    FrameFlags uFlags;
};

struct PortraitFrameTable {
    unsigned int GetFrameIdByPortrait(CharacterPortrait portrait);
    Duration GetDurationByPortrait(CharacterPortrait portrait);
    PortraitFrame *GetFrameBy_x(int uFramesetID, Duration gameTime);
    PortraitFrame *GetFrameBy_y(int *a2, Duration *a3, Duration a4);

    std::vector<PortraitFrame> pFrames;
};

extern PortraitFrameTable *pPortraitFrameTable;  // idb
