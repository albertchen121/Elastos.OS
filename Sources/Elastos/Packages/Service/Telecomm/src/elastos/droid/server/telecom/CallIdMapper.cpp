
#include "elastos/droid/server/telecom/CallIdMapper.h"
#include "elastos/droid/server/telecom/ThreadUtil.h"
#include <Elastos.CoreLibrary.Utility.h>
#include <Elastos.Droid.Utility.h>
#include <elastos/core/StringUtils.h>

using Elastos::Droid::Utility::IPair;
using Elastos::Core::ICharSequence;
using Elastos::Core::StringUtils;
using Elastos::Utility::CHashMap;
using Elastos::Utility::ICollection;
using Elastos::Utility::IIterator;

namespace Elastos {
namespace Droid {
namespace Server {
namespace Telecom {

CAR_INTERFACE_IMPL(CallIdMapper, Object, ICallIdMapper)

Int32 CallIdMapper::sIdCount;

ECode CallIdMapper::constructor(
    /* [in] */ const String& callIdPrefix)
{
    CHashMap::New((IHashMap**)&mCalls);
    ThreadUtil::CheckOnMainThread();
    mCallIdPrefix = callIdPrefix + "@";
    return NOERROR;
}

ECode CallIdMapper::ReplaceCall(
    /* [in] */ ICall* newCall,
    /* [in] */ ICall* callToReplace)
{
    ThreadUtil::CheckOnMainThread();
    // Use the old call's ID for the new call.
    String callId;
    GetCallId(callToReplace, &callId);
    mCalls->Put(StringUtils::ParseCharSequence(callId), newCall);
    return NOERROR;
}

ECode CallIdMapper::AddCall(
    /* [in] */ ICall* call,
    /* [in] */ const String& id)
{
        if (call == NULL) {
            return NOERROR;
        }
        ThreadUtil::CheckOnMainThread();
        mCalls->Put(StringUtils::ParseCharSequence(id), call);
        return NOERROR;
}

ECode CallIdMapper::AddCall(
    /* [in] */ ICall* call)
{
    ThreadUtil::CheckOnMainThread();
    String newId;
    GetNewId(&newId);
    AddCall(call, newId);
    return NOERROR;
}

ECode CallIdMapper::RemoveCall(
    /* [in] */ ICall* call)
{
    if (call == NULL) {
        return NOERROR;
    }
    ThreadUtil::CheckOnMainThread();
    // mCalls.inverse().remove(call);
    String callId;
    GetCallId(call, &callId);
    RemoveCall(callId);
    return NOERROR;
}

ECode CallIdMapper::RemoveCall(
    /* [in] */ const String& callId)
{
    ThreadUtil::CheckOnMainThread();
    mCalls->Remove(StringUtils::ParseCharSequence(callId));
    return NOERROR;
}

ECode CallIdMapper::GetCallId(
    /* [in] */ ICall* call,
    /* [out] */ String* result)
{
    VALIDATE_NOT_NULL(result)
    *result = String(NULL);

    if (call == NULL) {
        return NOERROR;
    }
    ThreadUtil::CheckOnMainThread();
    // return mCalls->Inverse()->Get(call);
    AutoPtr<IIterator> it;
    ICollection::Probe(mCalls)->GetIterator((IIterator**)&it);
    Boolean hasNext;
    while(it->HasNext(&hasNext), hasNext) {
        AutoPtr<IInterface> obj;
        it->GetNext((IInterface**)&obj);
        AutoPtr<IPair> pair = IPair::Probe(obj);
        obj = NULL;
        pair->GetSecond((IInterface**)&obj);
        if (ICall::Probe(obj) == call) {
            obj = NULL;
            pair ->GetFirst((IInterface**)&obj);
            IObject::Probe(obj)->ToString(result);
            break;
        }
    }
    return NOERROR;
}

ECode CallIdMapper::GetCall(
    /* [in] */ IInterface* objId,
    /* [out] */ ICall** result)
{
    VALIDATE_NOT_NULL(result)

    ThreadUtil::CheckOnMainThread();
    String callId(NULL);
    if (ICharSequence::Probe(objId) != NULL) {
        ICharSequence::Probe(objId)->ToString(&callId);
    }
    Boolean isValidConferenceId;
    IsValidConferenceId(callId, &isValidConferenceId);
    Boolean isValidCallId;
    IsValidCallId(callId, &isValidCallId);
    if (!isValidCallId && !isValidConferenceId) {
        *result = NULL;
        return NOERROR;
    }
    AutoPtr<IInterface> obj;
    mCalls->Get(StringUtils::ParseCharSequence(callId), (IInterface**)&obj);
    *result = ICall::Probe(obj);
    REFCOUNT_ADD(*result)
    return NOERROR;
}

ECode CallIdMapper::Clear()
{
    return mCalls->Clear();
}

ECode CallIdMapper::IsValidCallId(
    /* [in] */ const String& callId,
    /* [out] */ Boolean* result)
{
    VALIDATE_NOT_NULL(result)

    // Note, no need for thread check, this method is thread safe.
    *result = callId != NULL && callId.StartWith(mCallIdPrefix);
    return NOERROR;
}

ECode CallIdMapper::IsValidConferenceId(
    /* [in] */ const String& callId,
    /* [out] */ Boolean* result)
{
    VALIDATE_NOT_NULL(result)

    *result = callId != NULL;
    return NOERROR;
}

ECode CallIdMapper::GetNewId(
    /* [out] */ String* result)
{
    VALIDATE_NOT_NULL(result)

    sIdCount++;
    *result = mCallIdPrefix + StringUtils::ToString(sIdCount);
    return NOERROR;
}

} // namespace Telecom
} // namespace Server
} // namespace Droid
} // namespace Elastos
