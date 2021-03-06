//=========================================================================
// Copyright (C) 2012 The Elastos Open Source Project
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=========================================================================

#include "elastos/droid/app/backup/CRestoreSet.h"

namespace Elastos {
namespace Droid {
namespace App {
namespace Backup {

CAR_INTERFACE_IMPL(CRestoreSet, Object, IRestoreSet)

CAR_OBJECT_IMPL(CRestoreSet)

CRestoreSet::CRestoreSet()
    : mName(NULL)
    , mDevice(NULL)
    , mToken(-1)
{
}

CRestoreSet::~CRestoreSet()
{
}

ECode CRestoreSet::constructor()
{
    return NOERROR;
}

ECode CRestoreSet::constructor(
    /* [in] */ const String &name,
    /* [in] */ const String &dev,
    /* [in] */ Int64 token)
{
    mName = name;
    mDevice = dev;
    mToken = token;
    return NOERROR;
}

/**
 * Name of this restore set.  May be user generated, may simply be the name
 * of the handset model, e.g. "T-Mobile G1".
 */
ECode CRestoreSet::GetName(
    /* [out] */ String *name)
{
    VALIDATE_NOT_NULL(name);
    *name = mName;
    return NOERROR;
}

ECode CRestoreSet::SetName(
    /* [in] */ const String& name)
{
    mName = name;
    return NOERROR;
}

/**
 * Identifier of the device whose data this is.  This will be as unique as
 * is practically possible; for example, it might be an IMEI.
 */
ECode CRestoreSet::GetDevice(
    /* [out] */ String *device)
{
    VALIDATE_NOT_NULL(device);
    *device = mDevice;
    return NOERROR;
}

ECode CRestoreSet::SetDevice(
    /* [in] */ const String& device)
{
    mDevice = device;
    return NOERROR;
}

/**
 * Token that identifies this backup set unambiguously to the backup/restore
 * transport.  This is guaranteed to be valid for the duration of a restore
 * session, but is meaningless once the session has ended.
 */
ECode CRestoreSet::GetToken(
    /* [out] */ Int64 *token)
{
    VALIDATE_NOT_NULL(token);
    *token = mToken;
    return NOERROR;
}

ECode CRestoreSet::SetToken(
    /* [in] */ Int64 token)
{
    mToken = token;
    return NOERROR;
}

} // namespace Backup
} // namespace App
} // namespace Droid
} // namespace Elastos
