#ifndef DISPLAYABLEOBJECT_H
#define DISPLAYABLEOBJECT_H

#include "BaseEngine.h"

class DisplayableObject
{
public:
	// Constructor
	DisplayableObject(BaseEngine* pEngine);

	// Destructor
	virtual ~DisplayableObject(void);

	// Draw the object - override to implement the actual drawing of the correct object
	virtual void Draw();

	// Redraw the background behind the current position of the object, prior to movement
	virtual void RedrawBackground();

	// Handle the update action, moving the object and/or handling any game logic
	virtual void DoUpdate( int iCurrentTime );

	// Handle a notification by a caller. The SignalNumber will have an application-specific meaning, i.e. you can use whatever you wish. See the NotifyAllObjects... functions in BaseEngine.
	virtual long Notify( int iSignalNumber ) { return 0; }

	// Store the last position of the object, prior to moving it, and store the update rectangle.
	// The update rectangle is the area of the screen which needs to be redrawn and includes both the new and old positions of the object.
	void StoreLastScreenPositionForUndraw();

	// Get pointer to game object
	inline BaseEngine* GetEngine() const { return m_pEngine; }

	/** Redraw the moving objects on the screen */
	void RedrawObjects() { m_pEngine->Redraw(false); }

	/** Redraw the whole screen - background and objects */
	void RedrawWholeScreen() { m_pEngine->Redraw(true); }

	/** Get the X centre position of the object */
	int GetXCentre() const { return m_iCurrentScreenX + m_iStartDrawPosX + m_iDrawWidth/2; }

	/** Get the Y centre position of the object */
	int GetYCentre() const { return m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight / 2; }

	// Call this to make the item visible or invisible
	void SetVisible( bool bVisible ) { m_bVisible = bVisible; }

	// Returns true if the object should be visible
	bool IsVisible() const { return m_bVisible; }

	// Fix coords if they are off the screen
	void FixPosition()
	{
		if ( ( m_iCurrentScreenX+m_iStartDrawPosX) < 0 )
			m_iCurrentScreenX = -m_iStartDrawPosX;
		else if ( ( m_iCurrentScreenX+m_iStartDrawPosX+m_iDrawWidth) >= m_pEngine->GetScreenWidth() )
			m_iCurrentScreenX = m_pEngine->GetScreenWidth() - m_iStartDrawPosX - m_iDrawWidth;

		if ( ( m_iCurrentScreenY + m_iStartDrawPosY) < 0 )
			m_iCurrentScreenY = -m_iStartDrawPosY;
		else if ( ( m_iCurrentScreenY + m_iStartDrawPosY + m_iDrawHeight) >= m_pEngine->GetScreenHeight() )
			m_iCurrentScreenY = m_pEngine->GetScreenHeight() - m_iStartDrawPosY - m_iDrawHeight;
	}

	virtual void ObjectHit(int thisObjectId, int hitObjectId);

private:

	// The rectangle on screen which must be updated.
//	int m_iXUpdateRect;
//	int m_iYUpdateRect;
//	int m_iWUpdateRect;
//	int m_iHUpdateRect;

	// These are really provided for the use of sub-classes so we will expose them
	// Note that this breaks encapsulation
protected:
	// Pointer to the game object
	BaseEngine* m_pEngine;

	// We expect the sub-class to specify where to draw the object, and where it came from
	// Current position of object on the screen
	int m_iCurrentScreenX;
	int m_iCurrentScreenY;
	// Previous position of object on the screen
	int m_iPreviousScreenX;
	int m_iPreviousScreenY;

	// We expect the sub-class to specify the size of the drawable area, and where, within the drawable area, to draw the object
	// Details of where to actually draw this thing
	// Using these offsets allows moving of the drawn object within the drawing region, without altering the calling code.
	int m_iStartDrawPosX;
	int m_iStartDrawPosY;
	// Size of the object to draw
	int m_iDrawWidth;
	int m_iDrawHeight;

	// True if item is visible
	bool m_bVisible;

	
};

#endif
