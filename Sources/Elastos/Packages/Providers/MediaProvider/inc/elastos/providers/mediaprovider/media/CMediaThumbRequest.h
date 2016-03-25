#ifndef _ELASTOS_PROVIDERS_MEDIAPROVIDER_MEDIA_CMEDIATHUMBREQUEST_H__
#define _ELASTOS_PROVIDERS_MEDIAPROVIDER_MEDIA_CMEDIATHUMBREQUEST_H__

#include "_Elastos_Providers_MediaProvider_Media_CMediaThumbRequest.h"
#include "elastos/providers/mediaprovider/media/MediaThumbRequest.h"

namespace Elastos {
namespace Providers {
namespace MediaProvider {
namespace Media {

CarClass(CMediaThumbRequest), public MediaThumbRequest
{
public:
    CAR_OBJECT_DECL()
};

} // namespace Media
} // namespace MediaProvider
} // namespace Providers
} // namespace Elastos

#endif // _ELASTOS_PROVIDERS_MEDIAPROVIDER_MEDIA_CMEDIATHUMBREQUEST_H__