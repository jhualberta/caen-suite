/////////////////////////////////////////////////////////////////////////////
// Name:        drawing_left_canvas.cpp
// Purpose:     
// Author:      NDA
// Modified by: 
// Created:     10/10/2006 15:55:30
// RCS-ID:      
// Copyright:   CAEN S.p.A All rights reserved.
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// Generated by DialogBlocks (unregistered), 10/10/2006 15:55:30

#if defined(__GNUG__) && !defined(NO_GCC_PRAGMA)
#pragma implementation "drawing_left_canvas.h"
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif
#include <wx/dcbuffer.h>

////@begin includes
////@end includes

#include "drawing_left_canvas.h"
#include "drawing_panel.h"

////@begin XPM images
////@end XPM images

/*!
 * DrawingLeftCanvas type definition
 */

IMPLEMENT_DYNAMIC_CLASS( DrawingLeftCanvas, wxPanel )

/*!
 * DrawingLeftCanvas event table definition
 */

BEGIN_EVENT_TABLE( DrawingLeftCanvas, wxPanel )

////@begin DrawingLeftCanvas event table entries
    EVT_SIZE( DrawingLeftCanvas::OnSize )
    EVT_PAINT( DrawingLeftCanvas::OnPaint )
    EVT_ERASE_BACKGROUND( DrawingLeftCanvas::OnEraseBackground )

////@end DrawingLeftCanvas event table entries

END_EVENT_TABLE()

/*!
 * DrawingLeftCanvas constructors
 */

DrawingLeftCanvas::DrawingLeftCanvas( ): m_parent( NULL), m_first_time(true), m_scope_index( 0)
{
	this->m_p_back_bitmap= new wxBitmap( 1, 1);
}

DrawingLeftCanvas::DrawingLeftCanvas( int scope_index, wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ): m_parent( (DrawingPanel*)parent), m_first_time(true)
{
	this->m_scope_index= scope_index;
	this->m_p_back_bitmap= new wxBitmap( 1, 1);
    Create(parent, id, pos, size, style);
}
DrawingLeftCanvas::~DrawingLeftCanvas()
{
	delete this->m_p_back_bitmap; 
}

/*!
 * DrawingLeftCanvas creator
 */

bool DrawingLeftCanvas::Create( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style )
{
////@begin DrawingLeftCanvas member initialisation
////@end DrawingLeftCanvas member initialisation

////@begin DrawingLeftCanvas creation
    wxPanel::Create( parent, id, pos, size, style );

    CreateControls();
    Centre();
////@end DrawingLeftCanvas creation
    return true;
}

/*!
 * Control creation for DrawingLeftCanvas
 */

void DrawingLeftCanvas::CreateControls()
{    
////@begin DrawingLeftCanvas content construction
    // Generated by DialogBlocks, 10/10/2006 16:06:16 (unregistered)

    DrawingLeftCanvas* itemPanel1 = this;

////@end DrawingLeftCanvas content construction
}

/*!
 * Should we show tooltips?
 */

bool DrawingLeftCanvas::ShowToolTips()
{
    return true;
}

/*!
 * Get bitmap resources
 */

wxBitmap DrawingLeftCanvas::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin DrawingLeftCanvas bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end DrawingLeftCanvas bitmap retrieval
}

/*!
 * Get icon resources
 */

wxIcon DrawingLeftCanvas::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin DrawingLeftCanvas icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end DrawingLeftCanvas icon retrieval
}
/*!
 * wxEVT_SIZE event handler for ID_DRAWINGLEFTCANVAS
 */

void DrawingLeftCanvas::OnSize( wxSizeEvent& event )
{
	this->RefreshBackBitmap();
    event.Skip();
}

/*!
 * wxEVT_PAINT event handler for ID_DRAWINGLEFTCANVAS
 */

void DrawingLeftCanvas::OnPaint( wxPaintEvent& event )
{
	if( this->m_parent->IsFreezed())
	{
		event.Skip();
		return;
	}
	if( this->m_first_time )
	{
		this->RefreshBackBitmap();
		this->m_first_time= false;
	}

	// wxMutexLocker lock( this->m_mutex);
	if( this->m_parent->m_app_settings== NULL)
		return;

    wxBufferedPaintDC dc( this /*, wxBUFFER_VIRTUAL_AREA*/);
	dc.DrawBitmap( *this->m_p_back_bitmap, 0, 0, false);
}

/*!
 * wxEVT_ERASE_BACKGROUND event handler for ID_DRAWINGLEFTCANVAS
 */

void DrawingLeftCanvas::OnEraseBackground( wxEraseEvent& /* event*/ )
{
}

void DrawingLeftCanvas::DrawPosition( wxDC &dc)
{
	//
	// Loop boards
	for( size_t i= 0; i< this->m_parent->m_app_settings->m_board_array.GetCount(); i++)
	{
		GenericBoard *board= ( GenericBoard *)this->m_parent->m_app_settings->m_board_array[ i];
		board->DrawPosition( this->m_scope_index, dc);
	}
}
void DrawingLeftCanvas:: RefreshBackBitmap( )
{
	if( this->m_parent->m_app_settings== NULL)
		return;
	if( this->m_parent->IsFreezed())
	{
		return;
	}
	this->m_pix_X= this->GetRect().width;
	this->m_pix_Y= this->GetRect().height;

	// Loop boards
	for( size_t i= 0; i< this->m_parent->m_app_settings->m_board_array.GetCount(); i++)
	{
		GenericBoard *board= ( GenericBoard *)this->m_parent->m_app_settings->m_board_array[ i];
		board->SetLeftDiv2Pix( this->m_scope_index, (double)this->m_pix_Y/ DrawingCanvas::NUM_DIV_PER_SCREEN);
		board->SetLeftPix( this->m_scope_index, this->m_pix_X, this->m_pix_Y);
	}


	if(( this->m_p_back_bitmap->GetWidth()!= this->m_pix_X)||
		( this->m_p_back_bitmap->GetHeight()!= this->m_pix_Y))
	{
		delete this->m_p_back_bitmap;
		this->m_p_back_bitmap= new wxBitmap( this->m_pix_X, this->m_pix_Y);
	}

	wxMemoryDC dc;
	dc.SelectObject( *this->m_p_back_bitmap);

	this->DrawBackground( dc);
	this->DrawPosition( dc);
	dc.SelectObject( wxNullBitmap);

}
void DrawingLeftCanvas::DrawBackground( wxDC &dc)
{
	wxMutexLocker lock( this->m_parent->m_app_settings->m_mutex);

	if( this->m_parent->m_app_settings->m_back_brush[ this->m_scope_index]== NULL)
		return;
	dc.SetBackground( *this->m_parent->m_app_settings->m_back_brush[ this->m_scope_index]);
	dc.Clear();
	// Restore original brush
	dc.SetBackground( *this->m_parent->m_app_settings->m_back_brush[ this->m_scope_index]);
}

