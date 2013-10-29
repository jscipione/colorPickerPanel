/*
 * Copyright 1999, Be Incorporated. All rights reserved.
 * Copyright 2012-2013 Haiku, Inc. All rights reserved. 
 * This file may be used under the terms of the Be Sample Code License.
 */
#ifndef __PROTOCOL__
#define __PROTOCOL__


const uint32 kInitiateConnection = 'init';
const uint32 kOpenConnection = 'open';
const uint32 kCloseConnection = 'clse';
const uint32 kServerQuitting = 'quit';
const uint32 kApplyValue = 'done';
const uint32 kActivateWindow = 'awin';

#define kInvokePoint "be:invokePoint"
#define kTargetName "be:targetName"
#define kInitialValue "be:initialValue"
#define kRequestedValues "be:requestedValues"
#define kProvidedValues "be:providedValues"
#define kServerAddress "be:serverAddress"
#define kClientAddress "be:clientAddress"


#endif	// __PROTOCOL__
