#ifndef  __ELASTOS_DROID_LAUNCHER2_CBUBBLETEXTVIEW_H__
#define  __ELASTOS_DROID_LAUNCHER2_CBUBBLETEXTVIEW_H__

#include "_Elastos_Droid_Launcher2_CBubbleTextView.h"
#include "elastos/droid/ext/frameworkext.h"
#include "elastos/droid/launcher2/BubbleTextView.h"

namespace Elastos {
namespace Droid {
namespace Launcher2 {

/**
 * We use a custom tab view to process our own focus traversals.
 */
 CarClass(CBubbleTextView)
    , public BubbleTextView
{
public:
    CAR_OBJECT_DECL();
};

} // namespace Launcher2
} // namespace Droid
} // namespace Elastos

#endif // __ELASTOS_DROID_LAUNCHER2_CBUBBLETEXTVIEW_H__