#pragma once

#ifndef REFSTRUCT_H
#define REFSTRUCT_H

#include "RefObjCommon.h"

namespace HydraFramework
{
    struct RefObjStruct : RefObjCommon {
        friend class CRefDataManager;

    public:
        int m_DummyData;

    };
}

#endif
