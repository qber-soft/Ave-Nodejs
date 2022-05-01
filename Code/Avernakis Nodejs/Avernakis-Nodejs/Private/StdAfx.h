#pragma once

#define NODE_ADDON_API_DISABLE_DEPRECATED
#define NAPI_EXPERIMENTAL
#include "../../../External/node-addon-api/napi.h"

#include "../../../External/Avernakis/Code/Avernakis/Avernakis.h"
#include "../../../External/Avernakis/Code/Avernakis-Gui/Avernakis-Gui.h"
#include "../../../External/Avernakis/Code/Avernakis-Gui-Image/Avernakis-Gui-Image.h"
#include "../../../External/Avernakis/Code/Avernakis-Text/Avernakis-Text.h"
#include "../../../External/Avernakis/Code/Avernakis-System/Avernakis-System.h"
#include "../../../External/Avernakis/Code/Avernakis-Io/Avernakis-Io.h"
#include "../../../External/Avernakis/Code/Avernakis-Image/Avernakis-Image.h"
#include "../../../External/Avernakis/Code/Avernakis-Byo-2/Avernakis-Byo-2.h"
#include "../../../External/Avernakis/Code/Avernakis-Byo-3/Avernakis-Byo-3.h"
#include "../../../External/Avernakis/Code/Avernakis-Dee/Avernakis-Dee.h"

#if !defined(AveCheckSdkCompileVersion) || !defined(AveCheckSdkCompileVersionPrivate)
#	error Ave SDK version is too old.
#endif

#if !AveCheckSdkCompileVersion( 0, 8, 2, 0 ) && !AveCheckSdkCompileVersionPrivate( 2022, 502 ) && ( 0 != __AveVersion_Major || 0 != __AveVersion_Minor || 0 != __AveVersion_Build || 0 != __AveVersion_Private )
#	error This node addon needs Ave SDK 0.8.2 or private version 2022.416 at least, or an experimental build.
#endif

namespace Nav
{
	using namespace Ave;
}
