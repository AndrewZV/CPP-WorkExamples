#include "header.h"
#include "templates.h"

#include "CollidableObject.h"

CollidableObject::CollidableObject(BaseEngine* pEngine)
	:DisplayableObject(pEngine)
{
}


CollidableObject::~CollidableObject()
{
}


void CollidableObject::CheckCollision(int iCurrentTime)
{
	
	// Iterate through the objects
	// We are looking for one which is too close to us
	
	int thisObjectId = m_pEngine->getObjectId(this);
	DisplayableObject* pObject;

	for (int iObjectId = 0;
		(pObject = m_pEngine->GetDisplayableObject(iObjectId)) != NULL;
		iObjectId++)
	{
		if (thisObjectId == iObjectId) // This is us, skip it
			continue;
		// If you need to cast to the sub-class type, you must use dynamic_cast, see lecture 19
		// We are just using base class parts
		int iXDiff = pObject->GetXCentre() - m_iCurrentScreenX;
		int iYDiff = pObject->GetYCentre() - m_iCurrentScreenY;

		// Estimate the size - by re-calculating it
		int iTick = iCurrentTime / 20; // 1 per 20ms
		int iFrame = iTick % 30;
		int iSize = 10 + iFrame;
		if (iFrame > 15)
			iSize = 10 + (30 - iFrame);
		int iSizeOther = iSize; // Assume both the same size

		// Pythagorus' theorum:
		if (((iXDiff*iXDiff) + (iYDiff*iYDiff))
			< ((iSizeOther + iSize)*(iSizeOther + iSize)))
		{
			pObject->ObjectHit(thisObjectId, iObjectId);
			return;	//collision dealt with
		}
	}
}

