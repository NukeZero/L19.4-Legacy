// WndArcane.cpp: implementation of the CWndNeuz class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "defineText.h"
#include "AppDefine.h"
#include "DialogMsg.h"
#include "WndField.h"
#include "WndManager.h"
#include "WndRegVend.h"
#include "DPClient.h"

#ifdef __NEW_TASKBAR_V19
#include "definesound.h"
#include <fstream>
#include "defineSkill.h"
#define M_PI 3.14159265358979323846f
bool CWndTaskBarInterface::m_bLock = false;
#endif // __NEW_TASKBAR_V19

extern	CDPClient	g_DPlay;

_ERROR_STATE g_Error_State;


#define WND_WIDTH 210
#define TASKBAR_HEIGHT 48


/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �۾� ���� 
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
CWndShortcut::CWndShortcut()
{
}
CWndShortcut::~CWndShortcut()
{
}
void CWndShortcut::OnDraw(C2DRender* p2DRender)
{
	CWndButton::OnDraw( p2DRender );
}
BOOL CWndShortcut::Process()
{
	return CWndButton::Process();
}
void CWndShortcut::PaintFrame( C2DRender* p2DRender ) 
{
	CWndButton::PaintFrame( p2DRender );
} 
void CWndShortcut::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWndButton::OnLButtonUp( nFlags, point );
}
void CWndShortcut::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWndButton::OnLButtonDown( nFlags, point );
}
void CWndShortcut::OnRButtonUp(UINT nFlags, CPoint point)
{
	CWndButton::OnRButtonUp( nFlags, point );
}
void CWndShortcut::OnRButtonDown(UINT nFlags, CPoint point)
{
	CWndButton::OnRButtonDown( nFlags, point );
}
void CWndShortcut::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CWndButton::OnLButtonDblClk( nFlags, point );
}
void CWndShortcut::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	CWndButton::OnRButtonDblClk( nFlags, point );
}
void CWndShortcut::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWndButton::OnKeyDown( nChar, nRepCnt, nFlags );
}
void CWndShortcut::OnMouseMove(UINT nFlags, CPoint point)
{
	CWndButton::OnMouseMove( nFlags, point );
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �� ����Ʈ 
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

CWndQuickList::CWndQuickList() 
{ 
} 
CWndQuickList::~CWndQuickList() 
{ 
} 
void CWndQuickList::OnDraw( C2DRender* p2DRender ) 
{
	CWndTaskBar* pWndTaskBar = (CWndTaskBar*)m_pParentWnd;
	// ������ ������ ��� 
	CPoint point = CPoint( 0, 0);//POINT_ITEM;
	for( int y = 0; y < 4; y++ )
	{
		for( int i = 0; i < MAX_SLOT_ITEM; i++ )
		{
			point = CPoint( i * 32 + 32 , y * 38 + 6 );
			LPSHORTCUT lpShortcut = &pWndTaskBar->m_aSlotItem[ y ][ i ] ;
			if( !lpShortcut->IsEmpty() )
			{
				if( lpShortcut->m_pTexture )
					p2DRender->RenderTexture( point, lpShortcut->m_pTexture );
				if( lpShortcut->m_dwShortcut == SHORTCUT_ITEM )
				{
					CItemBase* pItemBase = g_pPlayer->GetItemId( lpShortcut->m_dwId );
					CItemElem* pItemElem = (CItemElem*)pItemBase;

					if( pItemElem  )
					{
						if( pItemElem->GetProp()->dwPackMax > 1 )
						{
							TCHAR szTemp[ 32 ];
							_stprintf( szTemp, "%d", pItemElem->m_nItemNum );
							CSize size = m_p2DRender->m_pFont->GetTextExtent( szTemp );
#if __VER >= 19
							CD3DFont* pOldFont = p2DRender->GetFont();
							p2DRender->SetFont( CWndBase::m_Theme.m_pFontWndNewTitle2 );

							p2DRender->TextOut( point.x + 35 - size.cx, point.y + 35 - size.cy, szTemp, 0xFF000000 );
							p2DRender->TextOut( point.x + 34 - size.cx, point.y + 34 - size.cy, szTemp, 0xFF85FF8A );
						
							p2DRender->SetFont( pOldFont );
#else // __VER >= 19
							p2DRender->TextOut( point.x + 32 - size.cx, point.y + 32 - size.cy, szTemp, 0xff0000ff );
							p2DRender->TextOut( point.x + 31 - size.cx, point.y + 31 - size.cy, szTemp, 0xffb0b0f0 );
#endif // __VER >= 19
						}
					}
					else
						lpShortcut->m_dwShortcut = SHORTCUT_NONE; 				
				}
			}
		}
	}
} 
void CWndQuickList::OnInitialUpdate() 
{ 
	CWndNeuz::OnInitialUpdate(); 
	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rectWindow = GetWindowRect();
	CPoint point( rectRoot.right - rectWindow.Width(), 110 );
	Move( point );
	MoveParentCenter();
} 
// ó�� �� �Լ��� �θ��� ������ ������.
BOOL CWndQuickList::Initialize( CWndBase* pWndParent, DWORD /*dwWndId*/ ) 
{ 
	// Daisy���� ������ ���ҽ��� ������ ����.
	return CWndNeuz::InitDialog( g_Neuz.GetSafeHwnd(), APP_QUICKLIST, 0, CPoint( 0, 0 ), pWndParent );
	
} 
/*
  ���� ������ ���� ��� 
BOOL CWndQuickList::Initialize( CWndBase* pWndParent, DWORD dwWndId ) 
{ 
	CRect rectWindow = m_pWndRoot->GetWindowRect(); 
	CRect rect( 50 ,50, 300, 300 ); 
	SetTitle( _T( "title" ) ); 
	return CWndNeuz::Create( WBS_THICKFRAME | WBS_MOVE | WBS_SOUND | WBS_CAPTION, rect, pWndParent, dwWndId ); 
} 
*/
BOOL CWndQuickList::OnCommand( UINT nID, DWORD dwMessage, CWndBase* pWndBase ) 
{ 
	return CWndNeuz::OnCommand( nID, dwMessage, pWndBase ); 
} 
void CWndQuickList::OnSize( UINT nType, int cx, int cy ) \
{ 
	CWndNeuz::OnSize( nType, cx, cy ); 
} 
void CWndQuickList::OnLButtonUp( UINT nFlags, CPoint point ) 
{ 
} 
void CWndQuickList::OnLButtonDown( UINT nFlags, CPoint point ) 
{ 
} 
BOOL CWndQuickList::OnChildNotify( UINT message, UINT nID, LRESULT* pLResult ) 
{ 
	return CWndNeuz::OnChildNotify( message, nID, pLResult ); 
} 
//#ifdef __NEWINTERFACE

//#define TASKSHORTCUT 45
#define ICON_SIZE    32
#define SKILL_SIZE   28

/*
#define POINT_APPLET_X  87
#define POINT_APPLET_Y   9
#define POINT_ITEM_X   295
#define POINT_ITEM_Y     9
#define POINT_QUEUE_X  649
#define POINT_QUEUE_Y    9
*/
DWORD   POINT_APPLET_X ;
DWORD   POINT_APPLET_Y ;
DWORD   POINT_ITEM_X   ;
DWORD   POINT_ITEM_Y   ;
DWORD   POINT_QUEUE_X  ;
DWORD   POINT_QUEUE_Y  ;

#define HORIRC_APPLET( nIndex ) CRect( POINT_APPLET_X + nIndex * ICON_SIZE, 6, POINT_APPLET_X + nIndex * ICON_SIZE + ICON_SIZE , 6 + ICON_SIZE )
#define VERTRC_APPLET( nIndex ) CRect( 6, POINT_APPLET_X + nIndex * ICON_SIZE, 3 + ICON_SIZE, POINT_APPLET_X + nIndex * ICON_SIZE + ICON_SIZE )
#define HORIRC_ITEM( nIndex )   CRect( POINT_ITEM_X + nIndex * ICON_SIZE, 6, POINT_ITEM_X + nIndex * ICON_SIZE + ICON_SIZE , 6 + ICON_SIZE )
#define VERTRC_ITEM( nIndex )   CRect( 6, POINT_ITEM_X + nIndex * ICON_SIZE, 3 + ICON_SIZE, POINT_ITEM_X + nIndex * ICON_SIZE + ICON_SIZE )
#define HORIRC_QUEUE( nIndex )  CRect( POINT_QUEUE_X + nIndex * SKILL_SIZE, 6, POINT_QUEUE_X + nIndex * SKILL_SIZE + SKILL_SIZE, 7 + SKILL_SIZE )
#define VERTRC_QUEUE( nIndex )  CRect( 6, POINT_QUEUE_X + nIndex * SKILL_SIZE, 6 + SKILL_SIZE, POINT_QUEUE_X + nIndex * SKILL_SIZE + SKILL_SIZE )

#define RECT_APPLET CRect( POINT_APPLET_X, POINT_APPLET_Y, POINT_APPLET_X + m_nMaxSlotApplet * ICON_SIZE , POINT_APPLET_Y + ICON_SIZE  )
#define RECT_ITEM   CRect( POINT_ITEM_X  , POINT_ITEM_Y  , POINT_ITEM_X   + MAX_SLOT_ITEM   * ICON_SIZE , POINT_ITEM_Y   + ICON_SIZE  )
#define RECT_QUEUE  CRect( POINT_QUEUE_X , POINT_QUEUE_Y , POINT_QUEUE_X  + MAX_SLOT_QUEUE  * SKILL_SIZE, POINT_QUEUE_Y  + SKILL_SIZE )

#define POINT_APPLET CPoint( POINT_APPLET_X, POINT_APPLET_Y )
#define POINT_ITEM   CPoint( POINT_ITEM_X  , POINT_ITEM_Y   )
#define POINT_QUEUE  CPoint( POINT_QUEUE_X , POINT_QUEUE_Y  )

//#else
/*
#define TASKSHORTCUT 45
#define ICON_SIZE    32
#define SKILL_SIZE   28

#define POINT_APPLET_X  89
#define POINT_APPLET_Y   8
#define POINT_ITEM_X   306
#define POINT_ITEM_Y     8
#define POINT_QUEUE_X  648
#define POINT_QUEUE_Y    6

#define HORIRC_APPLET( nIndex ) CRect( 89 + nIndex * ICON_SIZE, 6, 89 + nIndex * ICON_SIZE + ICON_SIZE , 6 + ICON_SIZE )
#define VERTRC_APPLET( nIndex ) CRect( 6, 89 + nIndex * ICON_SIZE, 3 + ICON_SIZE, 292 + nIndex * ICON_SIZE + ICON_SIZE )
#define HORIRC_ITEM( nIndex )   CRect( 306 + nIndex * ICON_SIZE, 6, 306 + nIndex * ICON_SIZE + ICON_SIZE , 6 + ICON_SIZE )
#define VERTRC_ITEM( nIndex )   CRect( 6, 292 + nIndex * ICON_SIZE, 3 + ICON_SIZE, 292 + nIndex * ICON_SIZE + ICON_SIZE )
#define HORIRC_QUEUE( nIndex )  CRect( 648 + nIndex * SKILL_SIZE, 6, 648 + nIndex * SKILL_SIZE + SKILL_SIZE, 7 + SKILL_SIZE )
#define VERTRC_QUEUE( nIndex )  CRect( 6, 648 + nIndex * SKILL_SIZE, 6 + 32, 648 + nIndex * SKILL_SIZE + SKILL_SIZE )

#define RECT_APPLET CRect(  89, 6, 280, 38 )
#define RECT_ITEM   CRect( 306, 6, 612, 38 )
#define RECT_QUEUE  CRect( 648, 6, 790, 38 )

#define POINT_APPLET CPoint( POINT_APPLET_X, POINT_APPLET_Y )
#define POINT_ITEM   CPoint( POINT_ITEM_X  , POINT_ITEM_Y   )
#define POINT_QUEUE  CPoint( POINT_QUEUE_X , POINT_QUEUE_Y  )

#endif
  */
void CWndTaskBar::OnDestroyChildWnd( CWndBase* pWndChild )
{
	if( m_pWndQuickList == pWndChild )
		SAFE_DELETE( m_pWndQuickList );
#ifdef __NEW_TASKBAR_V19
	SAFE_DELETE(pWndTaskBar_HUD);
	SAFE_DELETE(pWndTaskBar_HUD_SLIDE);
	SAFE_DELETE(pWndTaskBar_HUD_EX1);
	SAFE_DELETE(pWndTaskBar_HUD_EX2);
	SAFE_DELETE(pWndTaskBar_HUD_EX3);
	SAFE_DELETE(pWndNewSkillSlot);
#endif // __NEW_TASKBAR_V19
}

void CWndTaskBar::Serialize( CAr & ar )
{
	if( ar.IsStoring() )
	{
		int nCount	= 0;
		u_long uOffset	= ar.GetOffset();
		ar << nCount;
		for( int i = 0; i < MAX_SLOT_APPLET; i++ )
		{
			if( m_aSlotApplet[i].m_dwShortcut == SHORTCUT_NONE )		// ���� ����ִ��� �˻�
			{
				ar << i;
				ar << m_aSlotApplet[i].m_dwShortcut <<	m_aSlotApplet[i].m_dwId << m_aSlotApplet[i].m_dwType;
				ar << m_aSlotApplet[i].m_dwIndex <<	m_aSlotApplet[i].m_dwUserId << m_aSlotApplet[i].m_dwData;
				if( m_aSlotApplet[i].m_dwShortcut == SHORTCUT_CHAT )
					ar.WriteString( m_aSlotApplet[i].m_szString );
				nCount++;
			}
		}
		int nBufSize;
		LPBYTE lpBuf	= ar.GetBuffer( &nBufSize );
		*(UNALIGNED int*)( lpBuf + uOffset )	= nCount;

		nCount	= 0;
		uOffset	= ar.GetOffset();
		ar << nCount;
		for( int i = 0; i < MAX_SLOT_ITEM_COUNT; i++ )
		{
			for( int j = 0; j < MAX_SLOT_ITEM; j++ )
			{
				if( m_aSlotItem[i][j].m_dwShortcut == SHORTCUT_NONE )		// ���� ����ִ��� �˻�
				{
					ar << i << j;
					ar << m_aSlotItem[i][j].m_dwShortcut <<	m_aSlotItem[i][j].m_dwId << m_aSlotItem[i][j].m_dwType;
					ar << m_aSlotItem[i][j].m_dwIndex << m_aSlotItem[i][j].m_dwUserId << m_aSlotItem[i][j].m_dwData;
					if( m_aSlotItem[i][j].m_dwShortcut == SHORTCUT_CHAT)
						ar.WriteString( m_aSlotItem[i][j].m_szString );
					nCount++;
					
				}
			}
		}
		lpBuf	= ar.GetBuffer( &nBufSize );
		*(UNALIGNED int*)( lpBuf + uOffset )	= nCount;

		nCount	= 0;
		uOffset	= ar.GetOffset();
		ar << nCount;
		for( int i = 0; i < MAX_SLOT_QUEUE; i++ )
		{
			if( m_aSlotQueue[i].m_dwShortcut == SHORTCUT_NONE )		// ���� ����ִ��� �˻�
			{
				ar << i;
				ar << m_aSlotQueue[i].m_dwShortcut << m_aSlotQueue[i].m_dwId << m_aSlotQueue[i].m_dwType;
				ar << m_aSlotQueue[i].m_dwIndex << m_aSlotQueue[i].m_dwUserId << m_aSlotQueue[i].m_dwData;
				nCount++;
			}
		}
 		ar << m_nActionPoint;

		lpBuf	= ar.GetBuffer( &nBufSize );
		*(UNALIGNED int*)( lpBuf + uOffset )	= nCount;
	}
	else
	{
		InitTaskBar();
		int nCount, nIndex;
		ar >> nCount;	// applet count
		for( int i = 0; i < nCount; i++ )
		{
			ar >> nIndex;
			ar >> m_aSlotApplet[nIndex].m_dwShortcut >>	m_aSlotApplet[nIndex].m_dwId >> m_aSlotApplet[nIndex].m_dwType;
			ar >> m_aSlotApplet[nIndex].m_dwIndex >> m_aSlotApplet[nIndex].m_dwUserId >> m_aSlotApplet[nIndex].m_dwData;
			if( m_aSlotApplet[nIndex].m_dwShortcut == SHORTCUT_CHAT)
				ar.ReadString( m_aSlotApplet[nIndex].m_szString, MAX_SHORTCUT_STRING );
			m_aSlotApplet[nIndex].m_dwIndex = nIndex;
			SetTaskBarTexture( &m_aSlotApplet[nIndex] );

			if( m_aSlotApplet[nIndex].m_dwShortcut == SHORTCUT_SKILL )	
			{
				ItemProp* pProp;
				if( m_aSlotApplet[nIndex].m_dwType == 2 )
					pProp =  prj.GetPartySkill( m_aSlotApplet[nIndex].m_dwId );
				else
				{
					LPSKILL pSkill = g_pPlayer->GetSkill( 0, m_aSlotApplet[nIndex].m_dwId );
					pProp = prj.GetSkillProp( pSkill->dwSkill );	
				}
				if( pProp == NULL || (pProp->dwComboStyle != CT_STEP && pProp->dwComboStyle != CT_GENERAL) )	
				{
					m_aSlotApplet[nIndex].Empty();
				}
			}
#ifdef __CLIENT
#if __VER >= 8	// __JEFF_VER_8
			else if( m_aSlotApplet[nIndex].m_dwShortcut == SHORTCUT_ITEM )
			{
				if( g_pPlayer )
				{
					CItemBase* pItemBase	= g_pPlayer->GetItemId( m_aSlotApplet[nIndex].m_dwId );
					if( pItemBase && pItemBase->GetProp()->dwPackMax > 1 )	// ���� ������ �������̸�?
						m_aSlotApplet[nIndex].m_dwItemId	= pItemBase->m_dwItemId;
				}
			}
#endif	// __JEFF_VER_8
#endif	// __CLIENT
		}
		ar >> nCount;	// slot item count
		int nIndex2;
		for( int i = 0; i < nCount; i++ )
		{
			ar >> nIndex >> nIndex2;	// index
			ar >> m_aSlotItem[nIndex][nIndex2].m_dwShortcut >>	m_aSlotItem[nIndex][nIndex2].m_dwId >> m_aSlotItem[nIndex][nIndex2].m_dwType;
			ar >> m_aSlotItem[nIndex][nIndex2].m_dwIndex >> m_aSlotItem[nIndex][nIndex2].m_dwUserId >> m_aSlotItem[nIndex][nIndex2].m_dwData;
			if( m_aSlotItem[nIndex][nIndex2].m_dwShortcut == SHORTCUT_CHAT )
				ar.ReadString( m_aSlotItem[nIndex][nIndex2].m_szString, MAX_SHORTCUT_STRING );
#ifdef __CLIENT
#if __VER >= 8	// __JEFF_VER_8
			else if( m_aSlotItem[nIndex][nIndex2].m_dwShortcut == SHORTCUT_ITEM )
			{
				if( g_pPlayer )
				{
					CItemBase* pItemBase	= g_pPlayer->GetItemId( m_aSlotItem[nIndex][nIndex2].m_dwId );
					if( pItemBase && pItemBase->GetProp()->dwPackMax > 1 )	// ���� ������ �������̸�?
						m_aSlotItem[nIndex][nIndex2].m_dwItemId	= pItemBase->m_dwItemId;
				}
			}
#endif	// __JEFF_VER_8
#endif	// __CLIENT
			m_aSlotItem[nIndex][nIndex2].m_dwIndex = nIndex2;
			SetTaskBarTexture( &m_aSlotItem[nIndex][nIndex2] );
		}

		ar >> nCount;
		for( int i = 0; i < nCount; i++ )
		{
			ar >> nIndex;
			ar >> m_aSlotQueue[nIndex].m_dwShortcut >> m_aSlotQueue[nIndex].m_dwId >> m_aSlotQueue[nIndex].m_dwType;
			ar >> m_aSlotQueue[nIndex].m_dwIndex >> m_aSlotQueue[nIndex].m_dwUserId >> m_aSlotQueue[nIndex].m_dwData;

			m_aSlotQueue[nIndex].m_dwIndex = nIndex;

			LPSKILL lpSkill = g_pPlayer->GetSkill( m_aSlotQueue[nIndex].m_dwType, m_aSlotQueue[nIndex].m_dwId );
			//pWndButton->SetTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, lpSkill->GetProp()->szIcon ) );
			m_aSlotQueue[nIndex].m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, lpSkill->GetProp()->szIcon/*pItemBase->GetProp()->szIcon*/), 0xffff00ff, FALSE );
		}
		ar >> m_nActionPoint;
		m_nCurQueueNum = nCount;
	}
#ifdef __NEW_TASKBAR_V19
	CWndTaskBar_HUD_SLIDE* pManageSlide;
	pManageSlide = new CWndTaskBar_HUD_SLIDE;
	for (int y = 0; y < 4; y++)
	{
		for (int i = 0; i < MAX_SLOT_ITEM; i++)
		{
			pManageSlide->m_pSlotItem[i] = &m_aSlotItem[4][i];
	}
	}
	CWndTaskBar_HUD_SLIDE* pWndTaskBar_HUD_SLIDE = (CWndTaskBar_HUD_SLIDE*)GetWndBase(APP_NEWTASKBAR02);
	if (pWndTaskBar_HUD_SLIDE)
	{
		if (!pWndTaskBar_HUD_SLIDE->IsOpenWnd())
			pManageSlide->Initialize(&g_WndMng);
	}
	else
	{
		pManageSlide->Initialize(&g_WndMng);
	}

	CWndNewSkillSlot* pManageskill;
	pManageskill = new CWndNewSkillSlot;
	for (int i = 0; i < MAX_SLOT_QUEUE; i++)
	{
		pManageskill->m_pSlotQueue[i] = &m_aSlotQueue[i];
	}
	CWndNewSkillSlot * pWndNewSkillSlot = (CWndNewSkillSlot*)GetWndBase(APP_SLOT);
	if (pWndNewSkillSlot)
	{
		if (!pWndNewSkillSlot->IsOpenWnd())
			pManageskill->Initialize(&g_WndMng);
	}
	else
	{
		pManageskill->Initialize(&g_WndMng);
	}

	CWndTaskBar_HUD* pManage;
	pManage = new CWndTaskBar_HUD;
	//for( int y = 0; y < 4; y++ )
	{
	for (int i = 0; i < MAX_SLOT_ITEM; i++)
		{
		pManage->m_pSlotItem[i] = &m_aSlotItem[0][i];
		}
	}
	CWndTaskBar_HUD * pWndTaskBar_HUD = (CWndTaskBar_HUD*)GetWndBase(APP_NEWTASKBAR);
	if (pWndTaskBar_HUD)
	{
		if (!pWndTaskBar_HUD->IsOpenWnd())
			pManage->Initialize(&g_WndMng);
	}
	else
	{
		pManage->Initialize(&g_WndMng);
	}
	pManage->Move(pManageskill->GetWndRect().left - 544, pManageskill->GetWndRect().bottom - 88);
#endif // __NEW_TASKBAR_V19
}

void CWndTaskBar::SetTaskBarTexture( LPSHORTCUT pShortcut )
{
	if( pShortcut->m_dwShortcut == SHORTCUT_APPLET )
	{
		AppletFunc* pAppletFunc = g_WndMng.GetAppletFunc( pShortcut->m_dwId );
		if( pAppletFunc )
		{
			pShortcut->m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice,  MakePath( DIR_ICON, pAppletFunc->m_pszIconName ), 0xffff00ff );
		} else
		{
		}
	}
	else if( pShortcut->m_dwShortcut == SHORTCUT_ITEM )
	{
		CItemBase* pItemBase;
		pItemBase	= g_pPlayer->GetItemId( pShortcut->m_dwId );
		if( pItemBase )
			pShortcut->m_pTexture	= pItemBase->GetTexture();
	}
	else if ( pShortcut->m_dwShortcut == SHORTCUT_SKILL)
	{
		if( pShortcut->m_dwType == 2 )
		{
			ItemProp* pProp =  prj.GetPartySkill( pShortcut->m_dwId );
			pShortcut->m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, pProp->szIcon/*pItemBase->GetProp()->szIcon*/), 0xffff00ff );
		}
		else
		{	
			LPSKILL lpSkill = g_pPlayer->GetSkill( pShortcut->m_dwType, pShortcut->m_dwId );
			ItemProp* pSkillProp = prj.m_aPropSkill.GetAt( lpSkill->dwSkill );
			if( pSkillProp )
				pShortcut->m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, pSkillProp->szIcon ), 0xffff00ff );
		}
	}
#if __VER >= 12 // __LORD
	else if ( pShortcut->m_dwShortcut == SHORTCUT_LORDSKILL)
	{
		CCLord* pLord									= CCLord::Instance();
		CLordSkillComponentExecutable* pComponent		= pLord->GetSkills()->GetSkill(pShortcut->m_dwId);	
		if(pComponent) pShortcut->m_pTexture							= pComponent->GetTexture();
	}
#endif
	else if ( pShortcut->m_dwShortcut == SHORTCUT_MOTION )
	{
		MotionProp* pMotionProp = prj.GetMotionProp( pShortcut->m_dwId );
		if(pMotionProp)			//061206 ma	8���� �� ��ǰ����� ���� ���� �߰�	propMotion.txt
		{
			pMotionProp->pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, pMotionProp->szIconName ), 0xffff00ff );
			pShortcut->m_pTexture = pMotionProp->pTexture;
		}
	}
	else if( pShortcut->m_dwShortcut == SHORTCUT_CHAT )
	{
		pShortcut->m_pTexture	= m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, "icon_MacroChat.dds" ), 0xffff00ff );
	}
	else if( pShortcut->m_dwShortcut == SHORTCUT_EMOTICON )
	{
		if( pShortcut->m_dwId >= 0 && pShortcut->m_dwId < MAX_EMOTICON_NUM  )
		{
			TCHAR buffer[MAX_SHORTCUT_STRING] = { 0 };
			_tcscat( buffer, "/" );
			_tcscat( buffer, g_DialogMsg.m_EmiticonCmd[pShortcut->m_dwId].m_szCommand );
			_tcscpy( pShortcut->m_szString, buffer );
			pShortcut->m_pTexture =	g_DialogMsg.m_texEmoticonUser.GetAt(pShortcut->m_dwId);
		}
	}
	else if( pShortcut->m_dwShortcut == SHORTCUT_SKILLFUN )
	{
		pShortcut->m_pTexture	= m_pTexture;
	}
}

/*
* �׼� ����Ʈ
. �׼� ����Ʈ ���� CWndTaskBar::m_nActionPoint
. ��ų�ٿ� ������ �簢�� �׸���
. �׼�����Ʈ �ø��������
. ���ϰ����� 2��° ������ ���ÿ��� �׼�����Ʈ ���� 1���� - 100�� �Ѱ�
. �׼� ����Ʈ�� ���� ���̵� �׸��� - ��������Ʈ������ �ٸ���.
. ��ų���� �ܰ躰�� �׼�����Ʈ �Ҹ� �ٸ���.

*/

CWndTaskBar::CWndTaskBar()
{
	m_nCurQueue = -1;
	m_nCurQueueNum = 0;
	m_nPosition = TASKBAR_BOTTOM;
	memset( m_aSlotApplet, 0, sizeof( m_aSlotApplet ) );
	memset( m_aSlotItem  , 0, sizeof( m_aSlotItem ) );
	memset( m_aSlotQueue , 0, sizeof( m_aSlotQueue ) );
	memset( &m_aSlotSkill, 0, sizeof( m_aSlotSkill ) );

	m_pWndQuickList = NULL;
	m_pSelectShortcut = NULL;
	m_bStartTimeBar = FALSE;
	m_nSkillBar = 0;
	m_nUsedSkillQueue = 0;
	m_nExecute = 0;
	m_nSlotIndex = 0;
	m_paSlotItem = m_aSlotItem[ m_nSlotIndex ];
	m_nActionPoint = 0;
	m_dwHighAlpha = 0;
}

CWndTaskBar::~CWndTaskBar()
{
	/*
	for( int i = 0; i < m_awndShortCut.GetSize(); i++ )
	{
		CWndButton* pButton = (CWndButton*)m_awndShortCut.GetAt( i );
		SAFE_DELETE( pButton );
	}
	*/
}

void CWndTaskBar::InitTaskBar()
{
	m_nCurQueue = -1;
	m_nCurQueueNum = 0;
	//m_nPosition = TASKBAR_RIGHT;//LEFT;//TASKBAR_TOP;
	m_nPosition = TASKBAR_BOTTOM;//LEFT;//TASKBAR_TOP;
	memset( m_aSlotApplet, 0, sizeof( m_aSlotApplet ) );
	memset( m_aSlotItem  , 0, sizeof( m_aSlotItem ) );
	memset( m_aSlotQueue , 0, sizeof( m_aSlotQueue ) );
	
	m_pWndQuickList = NULL;
	m_pSelectShortcut = NULL;
	m_bStartTimeBar = FALSE;
	m_nSkillBar = 0;
	m_nUsedSkillQueue = 0;
	m_nExecute = 0;
	m_nSlotIndex = 0;
	m_paSlotItem = m_aSlotItem[ m_nSlotIndex ];
	m_nActionPoint = 0;
	m_dwHighAlpha = 0;
	//m_nMaxSlotApplet = 5;
}

void CWndTaskBar::PutTooTip( LPSHORTCUT pShortcut, CPoint point, CRect* pRect )
{
	ClientToScreen( &point );
	ClientToScreen( pRect );
	if( pShortcut->m_dwShortcut == SHORTCUT_APPLET )
	{
		AppletFunc* pAppletFunc = g_WndMng.GetAppletFunc( pShortcut->m_dwId ); 
		if( pAppletFunc )
		{
			//do 
		//	{
			
			//CString string;
			CEditString strEdit;
			if( pAppletFunc->m_cHotkey == 0 )
				strEdit.AddString( pAppletFunc->m_pAppletDesc );
			else
			{
				strEdit.AddString( pAppletFunc->m_pAppletDesc );
				strEdit.AddString( "\n" );
				CString string;
				string.Format( "[%s %c]", prj.GetText( TID_GAME_TOOLTIP_HOTKEY ), pAppletFunc->m_cHotkey );
				strEdit.AddString( string, 0xff0000ff );
			}
			//CEditString strEdit;
			//strEdit.SetParsingString( string );
			//strEdit.SetAt( 0, (CHAR)(aaa >> 8) );
			//strEdit.SetAt( 1, (CHAR)(aaa & 0xff00) );
			//aaa++;
			//TRACE( "aaa %x\n", aaa );
			g_toolTip.PutToolTip( pShortcut->m_dwId, strEdit, *pRect, point, 0 );
			//} while( aaa < 0xffff );
		}
	}
	else	
	if( pShortcut->m_dwShortcut == SHORTCUT_CHAT )
	{
		g_toolTip.PutToolTip( 10000, pShortcut->m_szString, *pRect, point, 0 );
	}
	else
	if( pShortcut->m_dwShortcut == SHORTCUT_EMOTICON )
	{
		g_toolTip.PutToolTip( 10000, pShortcut->m_szString, *pRect, point, 0 );
	}
	else	
	if( pShortcut->m_dwShortcut == SHORTCUT_ITEM  )
	{
		if( pShortcut->m_dwId != 0 )
		g_WndMng.PutToolTip_Item( pShortcut->m_dwType, pShortcut->m_dwId, point, pRect );
	}
	else	
	if( pShortcut->m_dwShortcut == SHORTCUT_SKILL )
	{
		if( pShortcut->m_dwType == 2 )
		{
			g_WndMng.PutToolTip_Troupe( pShortcut->m_dwId, point, pRect );
		}
		else
//		if( pShortcut->m_dwType == 0 || pShortcut->m_dwType == 1 || pShortcut->m_dwType == 3 )
		{
			LPSKILL lpSkill = g_pPlayer->GetSkill( 0, pShortcut->m_dwId );
			g_WndMng.PutToolTip_Skill( lpSkill->dwSkill, lpSkill->dwLevel, point, pRect );
		}
	}
#if __VER >= 12 // __LORD
	else	
	if( pShortcut->m_dwShortcut == SHORTCUT_LORDSKILL )
	{
		CCLord*							pLord		= CCLord::Instance();
		CLordSkillComponentExecutable*	pComponent	= pLord->GetSkills()->GetSkill(pShortcut->m_dwId);
		CString							string, str;
		CEditString						strEdit;

		if(!pComponent) return;

		string.Format( "#b#cff2fbe6d%s#nb#nc\n%s", pComponent->GetName(), pComponent->GetDesc());
		if(pComponent->GetTick() != 0)
		{
			str.Format( prj.GetText(TID_TOOLTIP_COOLTIME), pComponent->GetTick(), 0);
			string += "\n";
			string += str;
		}
	
		strEdit.SetParsingString( string );
		g_toolTip.PutToolTip(10000, strEdit, *pRect, point, 0);
	}
#endif
	else	
	if( pShortcut->m_dwShortcut == SHORTCUT_MOTION )
	{
		MotionProp* pMotionProp = prj.GetMotionProp( pShortcut->m_dwId );
		if(!pMotionProp)		//061206 ma	8���� �� ��ǰ����� ���� ���� �߰�	propMotion.txt
			return;

		CString string;

		string.Format( "%s", pMotionProp->szDesc );
		
		if( pMotionProp->dwID == MOT_BASE_CHEER )
		{
			if( g_pPlayer )
			{
				CString str;
				str.Format( prj.GetText(TID_CHEER_MESSAGE1), g_pPlayer->m_nCheerPoint );

				string += "\n\n";
				string += str;

				if( g_pPlayer->m_nCheerPoint < MAX_CHEERPOINT )
				{
					CTimeSpan ct( ((g_pPlayer->m_dwTickCheer - GetTickCount()) / 1000) );		// �����ð��� �ʴ����� ��ȯ�ؼ� �Ѱ���

					if( ct.GetMinutes() <= 0 )
					{
						str.Format( prj.GetText(TID_PK_LIMIT_SECOND), ct.GetSeconds() );
					}
					else
					{
						str.Format( prj.GetText(TID_PK_LIMIT_MINUTE), ct.GetMinutes() );
					}
					
					string += "\n";
					string += (prj.GetText(TID_CHEER_MESSAGE2)+str);
				}
			}
		}

		CEditString strEdit;
		strEdit.SetParsingString( string );
		g_toolTip.PutToolTip( pShortcut->m_dwId , strEdit, *pRect, point, 0 );
	}
	else
	if( pShortcut->m_dwShortcut == SHORTCUT_SKILLFUN )
	{
		strcpy( pShortcut->m_szString, prj.GetText(TID_GAME_SKILLSHORTCUT) );
		g_toolTip.PutToolTip( 10000, pShortcut->m_szString, *pRect, point, 0 );
	}
		
}

void CWndTaskBar::OnMouseWndSurface( CPoint point )
{
#ifndef __NEW_TASKBAR_V19
	CRect rect = CRect(POINT_APPLET_X, POINT_APPLET_Y, POINT_APPLET_X + ICON_SIZE, POINT_APPLET_Y + ICON_SIZE);
	for (int i = 0; i < m_nMaxSlotApplet; i++)
	{
		LPSHORTCUT lpShortcut = &m_aSlotApplet[i];
		if (!lpShortcut->IsEmpty() && rect.PtInRect(point))
		{
			MotionProp* pMotionProp = prj.GetMotionProp(lpShortcut->m_dwId);

			if (!IsShortcut(lpShortcut, SHORTCUT_MOTION, MOT_BASE_CHEER))
				PutTooTip(lpShortcut, point, &rect);
		}
		rect += CPoint(ICON_SIZE, 0);
	}

	rect = CRect(POINT_ITEM_X, POINT_ITEM_Y, POINT_ITEM_X + ICON_SIZE, POINT_ITEM_Y + ICON_SIZE);
	for (int i = 0; i < MAX_SLOT_ITEM; i++)
	{
		LPSHORTCUT lpShortcut = &m_paSlotItem[i];
		if (!lpShortcut->IsEmpty() && rect.PtInRect(point))
		{
			if (!IsShortcut(lpShortcut, SHORTCUT_MOTION, MOT_BASE_CHEER))
				PutTooTip(lpShortcut, point, &rect);
		}
		rect += CPoint(ICON_SIZE, 0);
	}
	rect = CRect(POINT_QUEUE_X, POINT_QUEUE_Y, POINT_QUEUE_X + SKILL_SIZE, POINT_QUEUE_Y + SKILL_SIZE);
	for (int i = 0; i < MAX_SLOT_QUEUE; i++)
	{
		LPSHORTCUT lpShortcut = &m_aSlotQueue[i];
		if (!lpShortcut->IsEmpty() && rect.PtInRect(point))
		{
			if (!IsShortcut(lpShortcut, SHORTCUT_MOTION, MOT_BASE_CHEER))
				PutTooTip(lpShortcut, point, &rect);
		}
		rect += CPoint(SKILL_SIZE, 0);
	}

	rect = CRect(POINT_QUEUE_X - ICON_SIZE - 5, POINT_QUEUE_Y, (POINT_QUEUE_X - ICON_SIZE - 5) + 32, POINT_QUEUE_Y + 32);

	if (rect.PtInRect(point))
	{
		SHORTCUT Shortcut;
		Shortcut.m_dwShortcut = SHORTCUT_SKILLFUN;
		PutTooTip(&Shortcut, point, &rect);
	}
#endif // __NEW_TASKBAR_V19
}

#define DRAW_HOTKEY( p2DRender, point, cHotkey ) { CString string; string.Format( "%c", cHotkey ); \
					p2DRender->TextOut( point.x - 0 + 2, point.y - 0 - 4, string, 0xffffffff ); }
					
					
/*
#define DRAW_HOTKEY( p2DRender, point, cHotkey ) {  \
	if( cHotkey >= 'A' && cHotkey <= 'Z' ) m_texPack.GetAt( cHotkey - 'A' )->Render( p2DRender, point, m_nAlphaCount );  \
	if( cHotkey >= '0' && cHotkey <= '9' ) m_texPack.GetAt( cHotkey - '0' + 26 )->Render( p2DRender, point, m_nAlphaCount ); }
*/


void CWndTaskBar::OnDraw( C2DRender* p2DRender )
{
	if( NULL == g_pPlayer )
		return;

	DWORD dwCur = g_tmCurrent;
	CRect rect = GetWindowRect();
	CRect rectSkillQueue;

	CD3DFont* pOldFont = p2DRender->GetFont(); 
	p2DRender->SetFont( CWndBase::m_Theme.m_pFontWndTitle ); 
		
	if( m_nPosition == TASKBAR_TOP || m_nPosition == TASKBAR_BOTTOM )
	{
		 rectSkillQueue.SetRect( rect.Width() - 32 * 4 - 6, 0, rect.Width(), rect.Height() );
	}
	else
	if( m_nPosition == TASKBAR_LEFT || m_nPosition == TASKBAR_RIGHT )
	{
		rectSkillQueue.SetRect( 0, rect.Height() - 32 * 4 - 6, rect.Width(), rect.Height() );
	}

	// �巡�� ���̶���Ʈ ���� ǥ��
	if( m_GlobalShortcut.IsEmpty() == FALSE )
	{
		DWORD dwColor;
		if( m_dwHighAlpha < 128 )
			dwColor = D3DCOLOR_ARGB( m_dwHighAlpha, 0, 0, 255 );
		else
			dwColor = D3DCOLOR_ARGB( 128 - ( m_dwHighAlpha - 128 ), 0, 0, 255 );

		LPWNDCTRL pApplet = GetWndCtrl( WIDC_CUSTOM1 );
		LPWNDCTRL pItem   = GetWndCtrl( WIDC_CUSTOM2 );
		LPWNDCTRL pSkill  = GetWndCtrl( WIDC_CUSTOM3 );

		CRect rectApplet = pApplet->rect;
		CRect rectItem = pItem->rect;
		CRect rectSkill = pSkill->rect;

		rectApplet.top = 42;
		rectApplet.bottom = 47;
		rectApplet.left -= 6;
		rectApplet.right += 6;
		rectItem.top = 42;
		rectItem.bottom = 47;
		rectItem.left -= 6;
		rectItem.right += 6;
		rectSkill.top = 42;
		rectSkill.bottom = 47;
		rectSkill.left -= 3;
		rectSkill.right += 4;
		
		switch( m_GlobalShortcut.m_dwShortcut )
		{
			case SHORTCUT_APPLET:
			case SHORTCUT_ITEM:
			case SHORTCUT_MOTION:
				p2DRender->RenderFillRect( rectApplet, dwColor );
				p2DRender->RenderFillRect( rectItem, dwColor );
				break;
			case SHORTCUT_SKILL:
				if( m_GlobalShortcut.m_dwType == 0 )
				{
					DWORD dwSkill = g_pPlayer->GetSkill( 0, m_GlobalShortcut.m_dwId )->dwSkill;
					DWORD dwComboStyleSrc = prj.GetSkillProp( dwSkill )->dwComboStyle;
					if( dwComboStyleSrc == CT_STEP  || dwComboStyleSrc == CT_GENERAL  )		// �����̳� ���׷��̸� �հ�
						p2DRender->RenderFillRect( rectItem, dwColor );		
					p2DRender->RenderFillRect( rectSkill, dwColor );
				}
				else
					p2DRender->RenderFillRect( rectItem, dwColor );
				break;
		}		
	}

	// ���÷� ������ ���
	CPoint point = POINT_APPLET;
	for( int i = 0; i < m_nMaxSlotApplet; i++ )
	{
		LPSHORTCUT lpShortcut = &m_aSlotApplet[ i ] ;
		if( !lpShortcut->IsEmpty() )
		{
			if( lpShortcut->m_pTexture )
				p2DRender->RenderTexture( point, lpShortcut->m_pTexture );
			if( lpShortcut->m_dwShortcut == SHORTCUT_ITEM )
			{
				CItemBase* pItemBase = g_pPlayer->GetItemId( lpShortcut->m_dwId );
				CItemElem* pItemElem = (CItemElem*)pItemBase;
				if( pItemElem )
				{
					if( pItemElem->GetProp()->dwPackMax > 1 )
					{
						TCHAR szTemp[ 32 ];
#if __VER >= 8	// __JEFF_VER_8
						_stprintf( szTemp, "%d", g_pPlayer?g_pPlayer->m_Inventory.GetItemCount( pItemElem->m_dwItemId ): 0 );
#else	// __JEFF_VER_8
						_stprintf( szTemp, "%d", pItemElem->m_nItemNum );
#endif	// __JEFF_VER_8
						CSize size = m_p2DRender->m_pFont->GetTextExtent( szTemp );
#if __VER >= 19
						CD3DFont* pOldFont = p2DRender->GetFont();
						p2DRender->SetFont( CWndBase::m_Theme.m_pFontWndNewTitle2 );

						p2DRender->TextOut( point.x + 35 - size.cx, point.y + 35 - size.cy, szTemp, 0xFF000000 );
						p2DRender->TextOut( point.x + 34 - size.cx, point.y + 34 - size.cy, szTemp, 0xFF85FF8A );
						
						p2DRender->SetFont( pOldFont );
#else // __VER >= 19
						p2DRender->TextOut( point.x + 32 - size.cx, point.y + 32 - size.cy, szTemp, 0xff0000ff );
						p2DRender->TextOut( point.x + 31 - size.cx, point.y + 31 - size.cy, szTemp, 0xffb0b0f0 );
#endif // __VER >= 19
					}
					DWORD dwGroup = g_pPlayer->m_cooltimeMgr.GetGroup( pItemElem->GetProp() );
					if( dwGroup )
					{
						DWORD dwEnd = g_pPlayer->m_cooltimeMgr.GetTime( dwGroup );		// �̺�Ʈ ���� �ð� 
						if( dwEnd != 0 && dwEnd > dwCur )  
						{
							DWORD dwBase = g_pPlayer->m_cooltimeMgr.GetBase( dwGroup );	// �̺�Ʈ ���� �ð� 
							RenderRadar( p2DRender, point, dwCur - dwBase, dwEnd - dwBase );
						}
					}
				}
				else
				{
#if __VER >= 8	// __JEFF_VER_8
					ItemProp* pItemProp	= prj.GetItemProp( lpShortcut->m_dwItemId );
					if( pItemProp && pItemProp->dwPackMax > 1 )	// ���� ������ �������̸�?
					{
						DWORD dwId	= g_pPlayer->m_Inventory.Find( lpShortcut->m_dwItemId );
						if( dwId != NULL_ID )	// ���� ������ �������� �ִٸ�?
						{
							lpShortcut->m_dwId	= dwId;
							g_DPlay.SendAddAppletTaskBar( i, lpShortcut );
						}
						else
						{
							lpShortcut->Empty();
							g_DPlay.SendRemoveAppletTaskBar( i );
						}
					}
					else
					{
						lpShortcut->Empty();
						g_DPlay.SendRemoveAppletTaskBar( i );
					}
#else	// __JEFF_VER_8
					lpShortcut->Empty();
					g_DPlay.SendRemoveAppletTaskBar( i );
#endif	// __JEFF_VER_8
				}
			}
			else
			if( lpShortcut->m_dwShortcut == SHORTCUT_APPLET )
			{
				AppletFunc* pAppletFunc = g_WndMng.GetAppletFunc( lpShortcut->m_dwId ); 
				if( pAppletFunc && pAppletFunc->m_cHotkey )
				{
					CPoint ptHotkey( point.x + 8, point.y - 9 );
					DRAW_HOTKEY( p2DRender, ptHotkey, pAppletFunc->m_cHotkey );
				}
			}
			else if( lpShortcut->m_dwShortcut == SHORTCUT_SKILL && lpShortcut->m_dwType != 2 ) //�شܽ�ų�� ��Ÿ�� ���� Render�� ���� �ʴ´�.
			{
				RenderCollTime( point, lpShortcut->m_dwId, p2DRender );
			}
		#if __VER >= 12 // __LORD
			else if( lpShortcut->m_dwShortcut == SHORTCUT_LORDSKILL)
			{
					RenderLordCollTime( point, lpShortcut->m_dwId, p2DRender );
			}
		#endif
			else
			if( lpShortcut->m_dwShortcut == SHORTCUT_MOTION )
			{
				if( lpShortcut->m_dwId == MOT_BASE_ESCAPE )
				{
					ItemProp* pItem = prj.GetItemProp( g_AddSMMode.dwSMItemID[SM_ESCAPE] );
					
					if( pItem && g_pPlayer )
					{
						CTimeSpan ct( g_pPlayer->m_dwSMTime[SM_ESCAPE] );
						
						if( ct.GetTotalSeconds() )
						{
							point.y -= 1;
							point.x += 1;
							RenderRadar( m_p2DRender, point, (DWORD)( pItem->dwCircleTime - ct.GetTotalSeconds() ), pItem->dwCircleTime );
						}
					}
				}
			}	
		}
		point += CPoint( ICON_SIZE, 0 );
	}
	// ������ ������ ��� 
	point = POINT_ITEM;
	for( int i = 0; i < MAX_SLOT_ITEM; i++ )
	{
		LPSHORTCUT lpShortcut = &m_paSlotItem[ i ] ;
		if( !lpShortcut->IsEmpty() )
		{
			if( lpShortcut->m_pTexture )
				p2DRender->RenderTexture( point, lpShortcut->m_pTexture );
			if( lpShortcut->m_dwShortcut == SHORTCUT_ITEM )
			{
				CItemBase* pItemBase = g_pPlayer->GetItemId( lpShortcut->m_dwId );
				CItemElem* pItemElem = (CItemElem*)pItemBase;
				if( pItemElem  )
				{
					if( pItemElem->GetProp()->dwPackMax > 1 )
					{
						TCHAR szTemp[ 32 ];
#if __VER >= 8	// __JEFF_VER_8
						_stprintf( szTemp, "%d", g_pPlayer?g_pPlayer->m_Inventory.GetItemCount( pItemElem->m_dwItemId ): 0 );
#else	// __JEFF_VER_8
						_stprintf( szTemp, "%d", pItemElem->m_nItemNum );
#endif	// __JEFF_VER_8
						CSize size = m_p2DRender->m_pFont->GetTextExtent( szTemp );
#if __VER >= 19
						CD3DFont* pOldFont = p2DRender->GetFont();
						p2DRender->SetFont( CWndBase::m_Theme.m_pFontWndNewTitle2 );

						p2DRender->TextOut( point.x + 35 - size.cx, point.y + 35 - size.cy, szTemp, 0xFF000000 );
						p2DRender->TextOut( point.x + 34 - size.cx, point.y + 34 - size.cy, szTemp, 0xFF85FF8A );
						
						p2DRender->SetFont( pOldFont );
#else // __VER >= 19
						p2DRender->TextOut( point.x + 32 - size.cx, point.y + 32 - size.cy, szTemp, 0xff0000ff );
						p2DRender->TextOut( point.x + 31 - size.cx, point.y + 31 - size.cy, szTemp, 0xffb0b0f0 );
#endif // __VER >= 19
					}
				}

				DWORD dwGroup = g_pPlayer->m_cooltimeMgr.GetGroup( pItemElem->GetProp() );
				if( dwGroup )
				{
					DWORD dwEnd = g_pPlayer->m_cooltimeMgr.GetTime( dwGroup );		// �̺�Ʈ ���� �ð� 
					if( dwEnd != 0 && dwEnd > dwCur )
					{
						DWORD dwBase = g_pPlayer->m_cooltimeMgr.GetBase( dwGroup );	// �̺�Ʈ ���� �ð� 
						RenderRadar( p2DRender, point, dwCur - dwBase, dwEnd - dwBase );
					}
				}
			} 
			else if( lpShortcut->m_dwShortcut == SHORTCUT_SKILL && lpShortcut->m_dwType != 2 ) //�شܽ�ų�� ��Ÿ�� ���� Render�� ���� �ʴ´�.
			{
				RenderCollTime( point, lpShortcut->m_dwId, p2DRender );
			}
		#if __VER >= 12 // __LORD
			else if( lpShortcut->m_dwShortcut == SHORTCUT_LORDSKILL)
			{
					RenderLordCollTime( point, lpShortcut->m_dwId, p2DRender );
			}
		#endif
			else
			if( lpShortcut->m_dwShortcut == SHORTCUT_MOTION )
			{
				if( lpShortcut->m_dwId == MOT_BASE_ESCAPE )
				{
					ItemProp* pItem = prj.GetItemProp( g_AddSMMode.dwSMItemID[SM_ESCAPE] );

					if( pItem && g_pPlayer )
					{
						CTimeSpan ct( g_pPlayer->m_dwSMTime[SM_ESCAPE] );
						
						if( ct.GetTotalSeconds() )
						{
							point.y -= 1;
							point.x += 1;
							RenderRadar( m_p2DRender, point, (DWORD)( pItem->dwCircleTime - ct.GetTotalSeconds() ), pItem->dwCircleTime );
						}
					}
				}
			}		

				
		}
		// hotkey ��� 
		CHAR cHotkey = ( i == 9 ) ? '0' : '1' + i;
		CPoint ptHotkey( point.x + 8, point.y - 9 );
		//DRAW_HOTKEY( p2DRender, ptHotkey, cHotkey );
		point += CPoint( ICON_SIZE, 0 );
	}
	
	point = CPoint( POINT_QUEUE_X - ICON_SIZE - 5, POINT_QUEUE_Y );
	p2DRender->RenderTexture( point, m_pTexture );

	// ��ų ť 
	point = POINT_QUEUE;
	//p2DRender->TextOut( point.x - 5, point.y - 16, "ACTION SLOT" );
	for( int i = 0; i < m_nCurQueueNum; i++ )
	{
		LPSHORTCUT lpShortcut = &m_aSlotQueue[ i ] ;
		if( !lpShortcut->IsEmpty() )
		{
			if( lpShortcut->m_pTexture )
			{
				p2DRender->RenderTexture( point, lpShortcut->m_pTexture );
//				LPSKILL pSkill = g_pPlayer->GetSkill( lpShortcut->m_dwType, lpShortcut->m_dwId );
//				if( g_pPlayer->m_nReUseDelay[ lpShortcut->m_dwId ] > 0 )
//					p2DRender->TextOut( point.x, point.y, g_pPlayer->m_nReUseDelay[ lpShortcut->m_dwId ] );

			}
		}
		point += CPoint( SKILL_SIZE, 0 );
	}

#ifndef __NEW_TASKBAR_V19
	if (!(g_pPlayer->IsSMMode(SM_ACTPOINT)))
	{
#define LV2MAXAP	10		// 2�ܰ� ��ų�� �����µ� �ʿ��� action point
#define LV3MAXAP	25		
#define LV4MAXAP	50
#define LV5MAXAP	100

		point = POINT_QUEUE;
		point.x += SKILL_SIZE;	// ��ų 2��°ĭ���� ���̵�ȴ�.
		{
			int nAP2Size;	// �׼�����Ʈ�� ���̶���Ʈ������ ��ȯ�Ѱ�.
			if (m_nActionPoint >= LV4MAXAP)	// LV4MAXAP�� �Ѿ�� 5�ܰ� ����.
				nAP2Size = (SKILL_SIZE * 3) + (((m_nActionPoint - LV4MAXAP) * SKILL_SIZE) / (LV5MAXAP - LV4MAXAP));
			else if (m_nActionPoint >= LV3MAXAP)
				nAP2Size = (SKILL_SIZE * 2) + (((m_nActionPoint - LV3MAXAP) * SKILL_SIZE) / (LV4MAXAP - LV3MAXAP));
			else if (m_nActionPoint >= LV2MAXAP)
				nAP2Size = (SKILL_SIZE * 1) + (((m_nActionPoint - LV2MAXAP) * SKILL_SIZE) / (LV3MAXAP - LV2MAXAP));
			else
				nAP2Size = (m_nActionPoint * SKILL_SIZE) / LV2MAXAP;

			p2DRender->m_pd3dDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			p2DRender->m_pd3dDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			point.x += nAP2Size;
			nAP2Size = (SKILL_SIZE * 4) - nAP2Size;
			p2DRender->RenderFillRect(CRect(point.x, point.y, point.x + nAP2Size, point.y + SKILL_SIZE + 2),
				D3DCOLOR_ARGB(0x7f, 0, 0, 0));

			if (m_nCurQueueNum > 0)
			{
				int show = 1;

				if (m_nActionPoint >= LV2MAXAP)
					show = 2;
				if (m_nActionPoint >= LV3MAXAP)
					show = 3;
				if (m_nActionPoint >= LV4MAXAP)
					show = 4;
				if (m_nActionPoint >= LV5MAXAP)
					show = 5;

				if (m_nCurQueueNum <= show)
					show = m_nCurQueueNum;

				CPoint Point = CPoint(POINT_QUEUE_X, POINT_QUEUE_Y + 1);

				RenderOutLineLamp(POINT_QUEUE_X, POINT_QUEUE_Y + 1, show, SKILL_SIZE);
			}
		}
	}
#endif // __NEW_TASKBAR_V19

	CWndButton* pWndButton = (CWndButton*)GetDlgItem( WIDC_UP );
	rect = pWndButton->GetWindowRect( TRUE );
	rect.top = rect.bottom - 2;
	p2DRender->TextOut( rect.left, rect.top, m_nSlotIndex + 1, 0xffffffff );
	p2DRender->SetFont( pOldFont );
}

void CWndTaskBar::UpdateItem()
{
	if( g_pPlayer == NULL )
		return;
	
	for( int i = 0; i < MAX_SLOT_ITEM; i++ )
	{
		LPSHORTCUT lpShortcut = &m_paSlotItem[ i ] ;
		if( !lpShortcut->IsEmpty() )
		{
			if( lpShortcut->m_dwShortcut == SHORTCUT_ITEM )
			{
				CItemBase* pItemBase = g_pPlayer->GetItemId( lpShortcut->m_dwId );
				CItemElem* pItemElem = (CItemElem*)pItemBase;

				if( pItemElem )
				{
					if( lpShortcut->m_pTexture != pItemElem->GetTexture() )
						lpShortcut->m_pTexture = pItemElem->GetTexture();
				}
				else
				{
#if __VER >= 8	// __JEFF_VER_8
					ItemProp* pItemProp	= prj.GetItemProp( lpShortcut->m_dwItemId );
					if( pItemProp && pItemProp->dwPackMax > 1 )	// ���� ������ �������̸�?
					{
						DWORD dwId	= g_pPlayer->m_Inventory.Find( lpShortcut->m_dwItemId );
						if( dwId != NULL_ID )	// ���� ������ �������� �ִٸ�?
						{
							lpShortcut->m_dwId	= dwId;
							g_DPlay.SendAddItemTaskBar( m_nSlotIndex, i, lpShortcut );
						}
						else
						{
							lpShortcut->Empty(); 				
							g_DPlay.SendRemoveItemTaskBar( m_nSlotIndex, i );
						}
					}
					else
					{
						lpShortcut->Empty(); 				
						g_DPlay.SendRemoveItemTaskBar( m_nSlotIndex, i );
					}
#else	// __JEFF_VER_8
					lpShortcut->Empty(); 				
					g_DPlay.SendRemoveItemTaskBar( m_nSlotIndex, i );
#endif	// __JEFF_VER_8
				}
			}
		}
	}
}

void CWndTaskBar::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
}
void CWndTaskBar::OnInitialUpdate()
{
	CWndNeuz::OnInitialUpdate();

	LPWNDCTRL pApplet = GetWndCtrl( WIDC_CUSTOM1 );
	LPWNDCTRL pItem   = GetWndCtrl( WIDC_CUSTOM2 );
	LPWNDCTRL pSkill  = GetWndCtrl( WIDC_CUSTOM3 );

	POINT_APPLET_X = pApplet->rect.left;
	POINT_APPLET_Y = pApplet->rect.top;
	POINT_ITEM_X   = pItem->rect.left;
	POINT_ITEM_Y   = pItem->rect.top;
	POINT_QUEUE_X  = pSkill->rect.left;
	POINT_QUEUE_Y  = pSkill->rect.top;

	CRect rect( 5, 7, 754, 40 );

	g_WndMng.m_pWndTaskBar = this;
	{
		rect = g_Neuz.GetDeviceRect();
		m_pWndRoot->m_rectLayout = rect;
#ifdef __NEW_TASKBAR_V19 
		pWndTaskBar_HUD       = new CWndTaskBar_HUD;
		pWndTaskBar_HUD_SLIDE = new CWndTaskBar_HUD_SLIDE;
		pWndTaskBar_HUD_EX1   = new CWndTaskBar_HUD_EX1;
		pWndTaskBar_HUD_EX2   = new CWndTaskBar_HUD_EX2;
		pWndTaskBar_HUD_EX3   = new CWndTaskBar_HUD_EX3;
		pWndNewSkillSlot      = new CWndNewSkillSlot;
#else // __NEW_TASKBAR_V19
		switch( m_nPosition )
		{
		case TASKBAR_TOP:
			rect.bottom = TASKBAR_HEIGHT;
			m_pWndRoot->m_rectLayout.top = rect.bottom;
			break;
		case TASKBAR_BOTTOM:
			rect.top = rect.bottom - TASKBAR_HEIGHT;
			m_pWndRoot->m_rectLayout.bottom = rect.top;
			break;
		case TASKBAR_LEFT:
			rect.right = TASKBAR_HEIGHT;
			m_pWndRoot->m_rectLayout.left = rect.right;
			break;
		case TASKBAR_RIGHT:
			rect.left = rect.right - TASKBAR_HEIGHT;
			m_pWndRoot->m_rectLayout.right = rect.left;
			break;
		}
		SetWndRect( rect );
#endif // __NEW_TASKBAR_V19
	}
	m_texPack.LoadScript( m_pApp->m_pd3dDevice, MakePath( DIR_THEME, "hotkey.inc" ) );

	m_menuShortcut.CreateMenu( this );	
	m_menuShortcut.AppendMenu( 0, 0 ,_T( "����" ) );

	m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice,  MakePath( DIR_ICON, "icon_ActionSkill.dds" ), 0xffff00ff );
	m_aSlotSkill.m_dwShortcut = SHORTCUT_SKILLFUN;
	m_aSlotSkill.m_pTexture   = m_pTexture;
}

HRESULT CWndTaskBar::InvalidateDeviceObjects()
{
	CWndBase::InvalidateDeviceObjects();
	
#ifdef __YDEBUG
	m_texPack.InvalidateDeviceObjects();
#endif //__YDEBUG
	return S_OK;
}

HRESULT CWndTaskBar::DeleteDeviceObjects()
{
	CWndBase::DeleteDeviceObjects();
	
#ifdef __YDEBUG
	m_texPack.DeleteDeviceObjects();
#endif //__YDEBUG
	return S_OK;
}

HRESULT CWndTaskBar::RestoreDeviceObjects()
{
	CWndBase::RestoreDeviceObjects();
	
#ifdef __YDEBUG
	m_texPack.RestoreDeviceObjects(m_pApp->m_pd3dDevice);
#endif //__YDEBUG
	
	return 0;
}

BOOL CWndTaskBar::Initialize(CWndBase* pWndParent,DWORD dwWndId)
{
	CRect rect = g_Neuz.GetDeviceRect();
	//m_rectLayout = rect;
/*
	switch( m_nPosition )
	{
	case TASKBAR_TOP:
		rect.bottom = TASKBAR_HEIGHT;
		m_pWndRoot->m_rectLayout.top = rect.bottom;
		break;
	case TASKBAR_BOTTOM:
		rect.top = rect.bottom - TASKBAR_HEIGHT;
		m_pWndRoot->m_rectLayout.bottom = rect.top;
		break;
	case TASKBAR_LEFT:
		break;
	case TASKBAR_RIGHT:
		break;
	}
	*/
	//m_pWndRoot->SetWndRect( rectRoot );

//CMainFrame
	//rect.top = rect.bottom;
	//rect.bottom += TASKBAR_HEIGHT;
//	rect.bottom = CLIENT_HEIGHT;
	//m_strMessage = lpszMessage;
	//m_dwType = nType;
	//SetTitle("������ ����");
//	return CWndBase::Create( 0 | /*WBS_MODAL|*/ WBS_MANAGER | WBS_SOUND | WBS_NOFRAME, rect, &g_WndMng, APP_TASKBAR );
	BOOL bResult;
	if( g_Option.m_nResWidth == 800 )
	{
		m_nMaxSlotApplet = 5;
		bResult = CWndNeuz::InitDialog( g_Neuz.GetSafeHwnd(), APP_TASKBAR800, WBS_MANAGER | WBS_SOUND, CPoint( 0, 0 ), pWndParent );
	}
	else
	if( g_Option.m_nResWidth == 1024 )
	{
		m_nMaxSlotApplet = 10;
		bResult = CWndNeuz::InitDialog( g_Neuz.GetSafeHwnd(), APP_TASKBAR1024, WBS_MANAGER | WBS_SOUND, CPoint( 0, 0 ), pWndParent );
	}
	else
	if( g_Option.m_nResWidth == 1280 )
	{
		m_nMaxSlotApplet = MAX_SLOT_APPLET;
		bResult = CWndNeuz::InitDialog( g_Neuz.GetSafeHwnd(), APP_TASKBAR1280, WBS_MANAGER | WBS_SOUND, CPoint( 0, 0 ), pWndParent );
	}
#if __VER >= 9 // __CSC_VER9_RESOLUTION
	else if( g_Option.m_nResWidth == 1360 )
	{
		m_nMaxSlotApplet = MAX_SLOT_APPLET;
		bResult = CWndNeuz::InitDialog( g_Neuz.GetSafeHwnd(), APP_TASKBAR1360W, WBS_MANAGER | WBS_SOUND, CPoint( 0, 0 ), pWndParent );
	}
	else if( g_Option.m_nResWidth == 1400 )
	{
		m_nMaxSlotApplet = MAX_SLOT_APPLET;
		bResult = CWndNeuz::InitDialog( g_Neuz.GetSafeHwnd(), APP_TASKBAR1400, WBS_MANAGER | WBS_SOUND, CPoint( 0, 0 ), pWndParent );
	}
	else if( g_Option.m_nResWidth == 1440 )
	{
		m_nMaxSlotApplet = MAX_SLOT_APPLET;
		bResult = CWndNeuz::InitDialog( g_Neuz.GetSafeHwnd(), APP_TASKBAR1440W, WBS_MANAGER | WBS_SOUND, CPoint( 0, 0 ), pWndParent );
	}
	else if( g_Option.m_nResWidth == 1600 )
	{
		m_nMaxSlotApplet = MAX_SLOT_APPLET;
		bResult = CWndNeuz::InitDialog( g_Neuz.GetSafeHwnd(), APP_TASKBAR1600, WBS_MANAGER | WBS_SOUND, CPoint( 0, 0 ), pWndParent );
	}
	else if( g_Option.m_nResWidth == 1680 )
	{
		m_nMaxSlotApplet = MAX_SLOT_APPLET;
		bResult = CWndNeuz::InitDialog( g_Neuz.GetSafeHwnd(), APP_TASKBAR1680W, WBS_MANAGER | WBS_SOUND, CPoint( 0, 0 ), pWndParent );
	}	
#endif //__CSC_VER9_RESOLUTION
	
	DelWndStyle( WBS_MOVE );
	return bResult;
	
}
BOOL CWndTaskBar::RemoveDeleteObj()
{
	/*
	for( int i = 0; i < m_awndShortCut.GetSize(); i++ )
	{
		CWndButton* pWndButton = (CWndButton*)m_awndShortCut.GetAt( i );
		if( pWndButton ) 
		{
			if( pWndButton->m_shortcut.m_dwShortcut == SHORTCUT_OBJECT )
			{
				CObj* pObj = (CObj*) pWndButton->m_shortcut.m_dwData;
				if( IsValidObj( pObj ) == FALSE )
					pWndButton->m_shortcut.m_dwData = 0;
			}
			else
			if( pWndButton->m_shortcut.m_dwShortcut == SHORTCUT_ITEM )
			{
				CItemBase* pItemBase = (CItemBase*) pWndButton->m_shortcut.m_dwData;
				if( pItemBase && pItemBase->IsEmpty() )
					pWndButton->Destroy( TRUE );
			}
		}
	}
	*/
	return TRUE;
}
void CWndTaskBar::SetItemSlot( int nSlot )
{
	if( nSlot >= 0 && nSlot < MAX_SLOT_ITEM_COUNT)
		m_paSlotItem = m_aSlotItem[ m_nSlotIndex = nSlot ];
}
BOOL CWndTaskBar::OnChildNotify(UINT message,UINT nID,LRESULT* pLResult)
{
	CWndButton* pWndButton = (CWndButton*) pLResult;
	if( message == WIN_ITEMDROP )
	{
		/*
		LPSHORTCUT pShortcut = (LPSHORTCUT) pLResult;
		if( pShortcut && pShortcut->m_dwData == 2 ) // ��ų ť ��ư�� ���̵�� 1000 �̻� 
		{
			SetSkillQueue( nID - 1000, pShortcut->m_dwShortcut, pShortcut->m_dwType, pShortcut->m_dwId, pShortcut->m_dwData, pShortcut->m_pTexture );
		}
		*/
	}
	else
	switch( nID )
	{
		case 101:
			/*
			if( m_pWndQuickList )
				m_pWndQuickList->Destroy();
			else
			{
				m_pWndQuickList = new CWndQuickList;
				m_pWndQuickList->Initialize( this );//&g_WndMng );
			}
			*/
			break;
		case WIDC_UP:
			m_nSlotIndex--;
			if( m_nSlotIndex < 0 ) m_nSlotIndex = MAX_SLOT_ITEM_COUNT-1;
			m_paSlotItem = m_aSlotItem[ m_nSlotIndex ];
			break;
		case WIDC_DOWN:
			m_nSlotIndex++;
			if( m_nSlotIndex > MAX_SLOT_ITEM_COUNT-1 ) m_nSlotIndex = 0;
			m_paSlotItem = m_aSlotItem[ m_nSlotIndex ];
			break;
		case WIDC_BUTTON1: // Menu
		{
			g_WndMng.OpenMenu();
			CRect rect = g_Neuz.GetDeviceRect();
			CRect rectMenu = m_wndMenu.GetScreenRect();
			switch( m_nPosition )
			{
			case TASKBAR_TOP:
				if( g_WndMng.m_pWndMenu )
					g_WndMng.m_pWndMenu->Move( CPoint( 0, TASKBAR_HEIGHT ) );
				break;
			case TASKBAR_BOTTOM:
				if( g_WndMng.m_pWndMenu )
					g_WndMng.m_pWndMenu->Move( CPoint( 0, rect.bottom - TASKBAR_HEIGHT - g_WndMng.m_pWndMenu->GetWndRect().Height() ) );
				break;
			case TASKBAR_LEFT:
				if( g_WndMng.m_pWndMenu )
					g_WndMng.m_pWndMenu->Move( CPoint( TASKBAR_HEIGHT, 0 ) );
				break;
			case TASKBAR_RIGHT:
				if( g_WndMng.m_pWndMenu )
					g_WndMng.m_pWndMenu->Move( CPoint( rect.right - TASKBAR_HEIGHT - g_WndMng.m_pWndMenu->GetWndRect().Width(), 0 ) );
				break;
			}

		}
		default:
			{
				switch( pWndButton->m_shortcut.m_dwIndex )
				{
					case APP_TRADE:		g_DPlay.SendTrade( (CMover*)g_WorldMng.Get()->GetObjFocus() );	break;
					default:
						g_WndMng.ObjectExecutor( &pWndButton->m_shortcut );	
						break;
				}
			}
	}
	return TRUE;
}
BOOL CWndTaskBar::OnCommand( UINT nID, DWORD dwMessage, CWndBase* pWndBase )
{
	return TRUE;
}
void CWndTaskBar::OnSize(UINT nType, int cx, int cy)
{
	CWndNeuz::OnSize( nType, cx, cy );
//	CRect rect = GetClientRect();
//	rect.DeflateRect( 5, 5);
//	rect.right = 37;
	//ect rect( 5, 5, 44, 40 );//GetClientRect();
	//wndMenu.SetWndRect( rect );

//ect = GetClientRect();

	// Create Command button
	//for(int i = 0; i < 10; i++)
		//m_pWndCommand[i].SetWndRect(CRect(60+i*18,3,76+i*18,21));

	//int i;
	// Create Tray button
	//int nMax = 3;
	//int nStart = (rect.Width() - nMax * 26);
	//for(i = 0; i < nMax; i++)
//		m_pWndTray[i].SetWndRect(CRect(nStart + i * 25, 6, nStart + 24 + i * 25, 30));
}
void CWndTaskBar::RemoveSkillQueue( int nIndex, BOOL bSend )
{
	if( m_nExecute )	return;		// ��ųť �����߿� �������� �ʴ´�.
BACK:
	if( !m_aSlotQueue[ nIndex ].IsEmpty() )
	{
		ItemProp* pItemProp = g_pPlayer->GetSkill( 0, m_aSlotQueue[ nIndex ].m_dwId )->GetProp();
		DWORD dwComboStyleSrc = pItemProp->dwComboStyle;
		int i = NULL;
		for( i = nIndex; i < MAX_SLOT_QUEUE - 1; i++ )
		{
			memcpy( &m_aSlotQueue[ i ], &m_aSlotQueue[ i + 1 ], sizeof( SHORTCUT ) );
			m_aSlotQueue[ i ].m_dwIndex = i;
		}
		m_aSlotQueue[ i ].m_dwShortcut = SHORTCUT_NONE;
		m_aSlotQueue[ i ].m_dwId = 0;
		m_nCurQueueNum--;
		if( m_nCurQueueNum < 0 ) 
			m_nCurQueueNum = 0;
		
#ifdef __NEW_TASKBAR_V19
		PLAYSND(SND_PC_ACTIONREMOVE);
#endif // __NEW_TASKBAR_V19
		if( CheckAddSkill( dwComboStyleSrc, nIndex /*- 1*/ ) == FALSE )
			goto BACK;
	}
	if( bSend )
		g_DPlay.SendSkillTaskBar( );
	// ��ų�� ����� �� ������ ��������.	

}
void CWndTaskBar::OnRButtonUp( UINT nFlags, CPoint point )
{
	CRect rect = RECT_APPLET;
	if( rect.PtInRect( point ) )
	{
		point.x -= rect.left;
		point.x /= ICON_SIZE;
		if( FALSE == m_aSlotApplet[ point.x ].IsEmpty() )
		{
			m_aSlotApplet[ point.x ].Empty();			
			g_DPlay.SendRemoveAppletTaskBar( (BYTE)( point.x ) );		// ������ ���� ������ ����
		}
	}
	rect = RECT_ITEM;
	if( rect.PtInRect( point ) )
	{
		point.x -= rect.left;

		point.x /= ICON_SIZE;
		if( FALSE == m_paSlotItem[ point.x ].IsEmpty() )
		{
			m_paSlotItem[ point.x ].Empty();
			g_DPlay.SendRemoveItemTaskBar( (BYTE)( m_nSlotIndex ), (BYTE)( point.x ) );	// ������ ���� ������ ����			
		}

	}
	rect = RECT_QUEUE;
	if( rect.PtInRect( point ) )
	{
		point.x -= rect.left;
		point.y -= rect.top;
		point.x /= SKILL_SIZE;
		RemoveSkillQueue( point.x );
	}
}

BOOL CWndTaskBar::SetShortcut( int nIndex, DWORD dwShortcut, DWORD dwType, DWORD dwId, CTexture* pTexture, int nWhere )
{
	LPSHORTCUT pShortcut = NULL;
	//CWndShortcut* pWndButton = new CWndShortcut;
//	pWndButton->Create( _T( "" ), 0, CRect( 65 + nIndex * 32, 3, 65 + nIndex * 32 + 32 , 3 + 32), this, dwId );

	//pShortcut = m_aSlotApplet[ nIndex ];
#if __VER >= 11 // __CSC_VER11_5
	// Chat Shortcut 10���� ����
	if(dwShortcut == SHORTCUT_CHAT)
	{
		int nchatshortcut = 0;
		for( int i=0; i<MAX_SLOT_ITEM_COUNT; i++ )
		{
			for( int j=0; j<MAX_SLOT_ITEM; j++ )
			{
				if( m_aSlotItem[i][j].m_dwShortcut == SHORTCUT_CHAT )
					nchatshortcut++;
			}
		}
		for( int k = 0; k < m_nMaxSlotApplet; ++k )
			if( m_aSlotApplet[ k ].m_dwShortcut == SHORTCUT_CHAT )
				++nchatshortcut;

		if(nchatshortcut > 9)
		{
			g_WndMng.PutString( prj.GetText( TID_GAME_MAX_SHORTCUT_CHAT ), NULL, prj.GetTextColor( TID_GAME_MAX_SHORTCUT_CHAT ) );
			return FALSE;
		}
	}
#endif //__CSC_VER11_5

	switch( m_nPosition )
	{
	case TASKBAR_TOP:
	case TASKBAR_BOTTOM:
		if( nWhere == 0 )
			pShortcut = &m_aSlotApplet[ nIndex ];
		else
		if( nWhere == 1 )
			pShortcut = &m_paSlotItem[ nIndex ];
		break;
	case TASKBAR_LEFT:
	case TASKBAR_RIGHT:
		if( nWhere == 0 )
			pShortcut = &m_aSlotApplet[ nIndex ];
		else
		if( nWhere == 1 )
			pShortcut = &m_paSlotItem[ nIndex ];
		break;
	}
	if( pTexture == NULL )
	{
		CItemBase* pItemBase;
		if( dwShortcut == SHORTCUT_APPLET ) 
		{
			AppletFunc* pAppletFunc = g_WndMng.GetAppletFunc( dwId );
			pShortcut->m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice,  MakePath( DIR_ICON, pAppletFunc->m_pszIconName ), 0xffff00ff );
				//pWndButton->SetTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, pAppletFunc->m_pszIconName ) );
			//pCardElem->m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ITEM, pCardElem->GetProp()->szIcon), 0xff000000 );

		}
		else
		if( dwShortcut == SHORTCUT_ITEM ) 
		{
			pItemBase = g_pPlayer->GetItemId( dwId );
			CTexture* pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ITEM, pItemBase->GetProp()->szIcon), 0xffff00ff );
			pItemBase->SetTexture( pTexture ); 
			pShortcut->m_pTexture = pTexture ;
		}
		else
		if( dwShortcut == SHORTCUT_MOTION ) 
		{
			MotionProp* pMotionProp = prj.GetMotionProp( dwId );
			if(pMotionProp)		//061206 ma	8���� �� ��ǰ����� ���� ���� �߰�	propMotion.txt
			{
				pMotionProp->pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, pMotionProp->szIconName ), 0xffff00ff );
				pShortcut->m_pTexture = pMotionProp->pTexture;
				//pWndButton->SetTexture( g_Neuz.m_pd3dDevice, pItemBase->m_pTexture );
			}
			else
				return FALSE;
		}
		/*
		else
		if( dwShortcut == SHORTCUT_CARD ) 
		{
			pItemBase = g_pPlayer->m_Card.GetAt( dwId );//m_apItem[ i ] ;
			pItemBase->m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ITEM, pItemBase->GetProp()->szIcon), 0xff000000 );
			pWndButton->SetTexture( g_Neuz.m_pd3dDevice, pItemBase->m_pTexture );
		}
		else
		if( dwShortcut == SHORTCUT_JACKBOX ) 
		{
			pItemBase = g_pPlayer->m_Cube.GetAt( dwId );//m_apItem[ i ] ;
			pItemBase->m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ITEM, pItemBase->GetProp()->szIcon), 0xff000000 );
			pWndButton->SetTexture( g_Neuz.m_pd3dDevice, pItemBase->m_pTexture );
		}
		*/
		else
		if( dwShortcut == SHORTCUT_SKILL ) 
		{
			if( pShortcut->m_dwType == 2 )
			{
				ItemProp* pProp =  prj.GetPartySkill( pShortcut->m_dwId );
				pShortcut->m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, pProp->szIcon/*pItemBase->GetProp()->szIcon*/), 0xffff00ff );
			}
			else
			{	
				LPSKILL lpSkill = g_pPlayer->GetSkill( dwType, dwId );
				//pWndButton->SetTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, lpSkill->GetProp()->szIcon ) );
				pShortcut->m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ITEM, lpSkill->GetProp()->szIcon/*pItemBase->GetProp()->szIcon*/), 0xffff00ff, TRUE );
			}
		}	
		else
		if( dwShortcut == SHORTCUT_SKILLFUN ) 
			pShortcut->m_pTexture = pTexture;
			
	}
	else 
		pShortcut->m_pTexture = pTexture;

#if __VER >= 8	// __JEFF_VER_8
	if( dwShortcut == SHORTCUT_ITEM )
	{
		CItemBase* pItemBase	= g_pPlayer->GetItemId( dwId );
		if( pShortcut && pItemBase && pItemBase->GetProp()->dwPackMax > 1 )	// ���� ������ �������̸�?
			pShortcut->m_dwItemId	= pItemBase->m_dwItemId;
	}
#endif	// __JEFF_VER_8

	pShortcut->m_dwShortcut = dwShortcut   ;
	pShortcut->m_dwType     = dwType;
	pShortcut->m_dwIndex    = nIndex;//0;//dwIndex;
	pShortcut->m_dwId       = dwId;
	pShortcut->m_dwUserId   = 0 ;
	pShortcut->m_dwData     = nWhere;
	strcpy( pShortcut->m_szString, m_GlobalShortcut.m_szString );//, sizeof(pShortcut->m_szString) );
	//pWndButton->SetTitle( m_GlobalShortcut.m_szString );
#if __VER >= 12 // __LORD
	if( dwShortcut == SHORTCUT_LORDSKILL)
		pShortcut->m_dwId--;
#endif
	if( nWhere == 0 ) //m_aSlotApplet
	{
		g_DPlay.SendAddAppletTaskBar( nIndex, pShortcut );
	}
	else
	if( nWhere == 1 ) //m_paSlotItem
	{
		g_DPlay.SendAddItemTaskBar( m_nSlotIndex, nIndex, pShortcut );
	}
	return TRUE;
}
BOOL CWndTaskBar::CheckAddSkill( int nSkillStyleSrc, int nQueueDest  )
{
	/*
	START -> FINISH, FG 
	CIRCLE -> START, CIRCLE
	FINISH -> START, CIRCLE
	*/
	DWORD dwComboStyleSrc = nSkillStyleSrc;
	if( nQueueDest == 0 )		// ùĭ�� ������ �õ� �������
	{
		/*
		if( �̹� ��ųâ�� ��ϵǾ� �ִ� )
		{
			if( �����Ϸ��°� CT_GENERAL�ΰ� )
				if( �̹� ���ԵǾ� �ִ°� CT_GENERAL�ΰ� )
				return TRUE;
			return FALSE;		// CT_GENERAL�̿��� ���� ùĭ�� �����Ϸ��� ��� ����.
		} else
		{
			// �ƹ��͵� ��ϵǾ� ���� �ʴ�.
			// ����, ���׷��� �հ�.
			if( dwComboStyleSrc == CT_STEP  || dwComboStyleSrc == CT_GENERAL  ) 
				return TRUE;
			return FALSE;	// �׿ܿ� ��� ���հ�.
		}
		 */
		if( m_nCurQueueNum == 0 )		// ����ִ�
		{
			if( dwComboStyleSrc == CT_STEP  || dwComboStyleSrc == CT_GENERAL  )		// �����̳� ���׷��̸� �հ�
				return TRUE;
			return	FALSE;
		} else
		// ���� �ִ�.
		{
			DWORD dwComboStyleDest;
			DWORD dwSkill = g_pPlayer->GetSkill( 0, m_aSlotQueue[ nQueueDest ].m_dwId )->dwSkill;
				//m_aSlotQueue[ nQueueDest ].m_dwId;	// �������� ĭ�� ��ų
			if( dwSkill )
				dwComboStyleDest = prj.GetSkillProp( dwSkill )->dwComboStyle;		// ��ĭ�� ��Ÿ��
			else 
				dwComboStyleDest = 0;
			if( dwComboStyleSrc == CT_GENERAL && dwComboStyleDest == CT_GENERAL )	// �̹��ִ°͵� ���׷��̰� �����Ϸ��°͵� ���׷��̸� �հ�
				return TRUE;
			return FALSE;	// �׿ܴ� ��� ùĭ�� ������ �� ����.
		}
	}
	else
	if( nQueueDest == 4 )		// ������ĭ�� �������� �������
	{
		if( dwComboStyleSrc == CT_STEP )	// ������ ùĭ�� �ƴϸ� ������ ���ִ´�.
			return FALSE;
		DWORD dwSkill = g_pPlayer->GetSkill( 0, m_aSlotQueue[ nQueueDest - 1 ].m_dwId )->dwSkill;
			//m_aSlotQueue[ nQueueDest - 1 ].m_dwId;	// �������� ĭ�� �տ��ִ� ��ų
		DWORD dwComboStylePrev;
		if( dwSkill )
			dwComboStylePrev = prj.GetSkillProp( dwSkill )->dwComboStyle;		// ��ĭ�� ��Ÿ��
		else
			dwComboStylePrev = 0;
		if( dwComboStylePrev == CT_FINISH )		// �� ��ų�� �ǴϽ��� ���̻� ���� �� ����.
			return FALSE;
		// ��Ŭ����� �������ϰ� ��ĭ�� ���׷��̸� ������.
		if( dwComboStyleSrc == CT_CIRCLE && dwComboStylePrev == CT_GENERAL )
			return FALSE;
		// �ǴϽ�(�ϳ�)�� �������ϰ� ��ĭ�� ���׷��̸� ������.
		if( dwComboStyleSrc == CT_FINISH && dwComboStylePrev == CT_GENERAL )
			return FALSE;
		// ���׷��� �������ϰ� ��ĭ�� ���׷��� �ƴϸ� ������.
		if( dwComboStyleSrc == CT_GENERAL && dwComboStylePrev != CT_GENERAL )
			return FALSE;
		
		return TRUE;	// �׿ܴ� ��� �հ�
	}
	else
	// �׿� �߰��� ������ �Ѱ��.
	{
		// ��°ĭ �̻���� �������� ������ ó��.
		if( dwComboStyleSrc == CT_STEP )	// ������ ùĭ�� �ƴϸ� ������ ���ִ´�.
			return FALSE;
		DWORD dwComboStylePrev;
		DWORD dwComboStyleDest;
		DWORD dwSkill = g_pPlayer->GetSkill( 0, m_aSlotQueue[ nQueueDest - 1 ].m_dwId )->dwSkill;
			//m_aSlotQueue[ nQueueDest - 1 ].m_dwId;	// �������� ĭ�� �տ��ִ� ��ų
		if( dwSkill )
			dwComboStylePrev = prj.GetSkillProp( dwSkill )->dwComboStyle;		// ��ĭ�� ��Ÿ��
		else
			dwComboStylePrev = 0;
		dwSkill = g_pPlayer->GetSkill( 0, m_aSlotQueue[ nQueueDest ].m_dwId )->dwSkill;
		//dwSkill = m_aSlotQueue[ nQueueDest ].m_dwId;	// �������� ĭ�� ��ų
		if( dwSkill )
			dwComboStyleDest = prj.GetSkillProp( dwSkill )->dwComboStyle;		// ��ĭ�� ��Ÿ��
		else
			dwComboStyleDest = 0;
		if( dwComboStylePrev == CT_FINISH )		// �� ��ų�� �ǴϽ��� ���̻� ���� �� ����.
			return FALSE;
		// ��Ŭ����� �������ϰ� ��ĭ�� ���׷��̸� ������.
		if( dwComboStyleSrc == CT_CIRCLE && dwComboStylePrev == CT_GENERAL )
			return FALSE;
		// �ǴϽ�(�ϳ�)�� �������ϰ� ��ĭ�� ���׷��̸� ������.
		if( dwComboStyleSrc == CT_FINISH && dwComboStylePrev == CT_GENERAL )
			return FALSE;
		// �ǴϽ��� �������ϰ� ��ĭ�� ��Ŭ�̸� ������.
		if( dwComboStyleSrc == CT_FINISH && dwComboStyleDest == CT_CIRCLE )
			return FALSE;
		// �ǴϽ��� �������ϰ� ��ĭ�� �ǴϽ��̸� ������.
		if( dwComboStyleSrc == CT_FINISH && dwComboStyleDest == CT_FINISH )
			return FALSE;
		// ���׷��� �������ϰ� 
		if( dwComboStyleSrc == CT_GENERAL )
		{
			if( dwComboStylePrev != CT_GENERAL )	// ��ĭ�� ���׷��� �ƴϸ� ������.
				return FALSE;
			if( dwComboStyleDest != CT_GENERAL && m_nCurQueueNum > nQueueDest )	// ��ĭ�� ���׷��� �ƴϸ� ���ִµ� �� ���̸� ������ �ִ�.
					return FALSE;
		}
		
		return TRUE;	// �� �ܴ� ��� �հ�
	}
	return FALSE;
}
BOOL CWndTaskBar::SetSkillQueue( int nIndex, DWORD dwType, DWORD dwId, CTexture* pTexture )
{
	if( m_nExecute )		return FALSE;		// ��ųť �����߿� ��� �ȵ�.
#ifdef __NEW_TASKBAR_V19
	if( m_nCurQueueNum >= 6 )
#else // __NEW_TASKBAR_V19
	if (m_nCurQueueNum >= 5)
#endif // __NEW_TASKBAR_V19
	{
		return FALSE;
	}
	// m_nCurQueueNum ���� ���� ���Կ� ����ִ°� �ִٸ� ���� ���´�. Ŭ��������.
	for( int i = 0; i < m_nCurQueueNum; i++ )
	{
		if( m_aSlotQueue[ i ].IsEmpty() )
		{
			for( i = 0; i < m_nCurQueueNum; i++ )
				m_aSlotQueue[ i ].Empty();
			m_nCurQueueNum = 0;
			break;
		}
	}
	 if( nIndex > m_nCurQueueNum )
		 nIndex = m_nCurQueueNum;
	 
#ifdef __NEW_TASKBAR_V19
	 for (int i = 0; i < MAX_SLOT_QUEUE; i++)
	 {
		 PLAYSND(SND_PC_ACTIONREGISTER);
		 break;
	 }
#endif // __NEW_TASKBAR_V19

	LPSHORTCUT pShortcut = NULL;
	CRect rect = GetWindowRect();
	LPSKILL lpSkill = g_pPlayer->GetSkill( 0, dwId );
	DWORD dwSkill = lpSkill->dwSkill;
	DWORD dwLevel = lpSkill->dwLevel;
	ItemProp *pSkillProp = prj.GetSkillProp( dwSkill );
	DWORD dwComboStyleSrc = pSkillProp->dwComboStyle;

	if( dwLevel <= 0 )
		return FALSE;

#if __VER >= 9	// __SKILL_0706
	AddSkillProp* pAddSkillProp	= prj.GetAddSkillProp( pSkillProp->dwSubDefine, dwLevel );
	ASSERT( pAddSkillProp );
	if( (int)pAddSkillProp->dwCooldown > 0 )	//  ��Ÿ���ִ� ��ų�� �׼ǽ��Կ� ����
#else	// __SKILL_0705
	if( (int)(pSkillProp->dwSkillReady) > 0 )	//  ��Ÿ���ִ� ��ų�� �׼ǽ��Կ� ����
#endif	// __SKILL_0705
	{
		CString str;
		str.Format( prj.GetText(TID_GAME_SKILLLNOTUSE), pSkillProp->szName );
		g_WndMng.PutString( str , NULL, prj.GetTextColor(TID_GAME_SKILLLNOTUSE) );
		return FALSE;
	}

//	DWORD dwComboStyleDest;
//	ItemProp* pItemProp1, * pItemProp2,* pItemProp3; 
	if( nIndex < m_nCurQueueNum ) // insert		// nIndex�� ������ ĭ�� �ε���
	{
		if( !CheckAddSkill( dwComboStyleSrc, nIndex ) )		// Src�� nIndex�� �־ �Ǵ��� üũ
			return FALSE;
		for( int i = m_nCurQueueNum; i > nIndex; i-- )
		{
			memcpy( &m_aSlotQueue[ i ], &m_aSlotQueue[ i - 1 ], sizeof( SHORTCUT ) );
		}
		pShortcut = &m_aSlotQueue[ nIndex ];
		m_nCurQueueNum++;
	}
	else // add
	{
		if( !CheckAddSkill( dwComboStyleSrc,  m_nCurQueueNum ) )	// ���� ������ ĭ�� �־ �Ǵ��� �׽�Ʈ.
			return FALSE;
		pShortcut = &m_aSlotQueue[ m_nCurQueueNum ];
		nIndex = m_nCurQueueNum;
		m_nCurQueueNum++;
	}
	m_nCurQueue = -1;
	if( pTexture == NULL )
	{
		LPSKILL lpSkill = g_pPlayer->GetSkill( dwType, dwId );
		pShortcut->m_pTexture = m_textureMng.AddTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, lpSkill->GetProp()->szIcon), 0xff000000, FALSE );
	}
	else pShortcut->m_pTexture = pTexture;


	pShortcut->m_dwShortcut = SHORTCUT_SKILL   ;
	pShortcut->m_dwType     = dwType; // ���� 
	pShortcut->m_dwIndex    = nIndex;//dwIndex; // ��ų ��Ʈ�ѿ����� ���� 
	pShortcut->m_dwId       = dwId; // ��ų �ε��� 
	pShortcut->m_dwUserId   = 0 ;
	pShortcut->m_dwData     = 2;
	_tcscpy( pShortcut->m_szString, m_GlobalShortcut.m_szString );
	g_DPlay.SendSkillTaskBar();
	// ��ų ��� ���⼭ ������ ������ ��
	return TRUE;
}

BOOL CWndTaskBar::OnDropIcon( LPSHORTCUT pShortcut, CPoint point )
{
	CRect rect = GetWindowRect();
	rect.DeflateRect( 3, 3);
	// ������ ������ ��� 
	if( pShortcut->m_pFromWnd == this )
	{
		LPSHORTCUT lpShortcut = (LPSHORTCUT) pShortcut->m_dwData;
		// ����Ʈ�� �׽�ũ�ٰ� �ƴ� ���̶��. �ǵ������� ������ ������� �½�ũ�� �ۿ� ���� ����. ������.
		if( GetClientRect().PtInRect( point ) == FALSE )
		{
			// ������ ���� ������ ����
			if( lpShortcut->m_dwData == 0 )
				g_DPlay.SendRemoveAppletTaskBar( (BYTE)( lpShortcut->m_dwIndex ) );
			else
			if( lpShortcut->m_dwData == 1 )
				g_DPlay.SendRemoveItemTaskBar( m_nSlotIndex, (BYTE)( lpShortcut->m_dwIndex ) );
			else
			if( lpShortcut->m_dwData == 2 )
			{
				RemoveSkillQueue( lpShortcut->m_dwIndex );
				return TRUE;
				//g_DPlay.SendSkillTaskBar( );
			}
			lpShortcut->Empty();
			return TRUE;
		}
	//	return TRUE;
	}
	CWndBase* pWndFrame =  pShortcut->m_pFromWnd->GetFrameWnd();

#ifdef __NEW_SKILL_TREE
	if( pWndFrame && ( pWndFrame->GetWndId() != APP_INVENTORY && pWndFrame != g_WndMng.m_pWndTaskBar && pWndFrame->GetWndId() != APP_COMMUNICATION_CHAT && pWndFrame->GetWndId() != APP_SKILL4 && pWndFrame->GetWndId() != APP_MOTION && pWndFrame->GetWndId() != APP_PARTY && pWndFrame->GetWndId() != APP_LORD_SKILL) )
#else // __NEW_SKILL_TREE
#if __VER >= 10 // __CSC_VER9_1
#if __VER >= 12 // __LORD
	if( pWndFrame && ( pWndFrame->GetWndId() != APP_INVENTORY && pWndFrame != g_WndMng.m_pWndTaskBar && pWndFrame->GetWndId() != APP_COMMUNICATION_CHAT && pWndFrame->GetWndId() != APP_SKILL3 && pWndFrame->GetWndId() != APP_MOTION && pWndFrame->GetWndId() != APP_PARTY && pWndFrame->GetWndId() != APP_LORD_SKILL) )
#else
	if( pWndFrame && ( pWndFrame->GetWndId() != APP_INVENTORY && pWndFrame != g_WndMng.m_pWndTaskBar && pWndFrame->GetWndId() != APP_COMMUNICATION_CHAT && pWndFrame->GetWndId() != APP_SKILL3 && pWndFrame->GetWndId() != APP_MOTION && pWndFrame->GetWndId() != APP_PARTY ) )
#endif
#else
	if( pWndFrame && ( pWndFrame->GetWndId() != APP_INVENTORY && pWndFrame != g_WndMng.m_pWndTaskBar && pWndFrame->GetWndId() != APP_COMMUNICATION_CHAT && pWndFrame->GetWndId() != APP_SKILL1 && pWndFrame->GetWndId() != APP_MOTION && pWndFrame->GetWndId() != APP_PARTY ) )
#endif //__CSC_VER9_1
#endif // __NEW_SKILL_TREE	
	{
		SetForbid( TRUE );
		return FALSE;
	}
	
	if( pShortcut->m_dwShortcut == SHORTCUT_SKILL && pShortcut->m_dwType != 2 ) // �شܽ�ų�� �ȵ�
	{
		LPSKILL pSkill = g_pPlayer->GetSkill( 0, pShortcut->m_dwId );
		if( pSkill && (pSkill->dwLevel <= 0 || g_pPlayer->CheckSkill( pSkill->dwSkill ) == FALSE) )
		{
			SetForbid( TRUE );
			return FALSE;
		}
	}
#if __VER >= 12 // __LORD
	if( pShortcut->m_dwId == 0 && strlen( pShortcut->m_szString ) < 1 && pShortcut->m_dwShortcut != SHORTCUT_SKILLFUN && pShortcut->m_dwShortcut != SHORTCUT_LORDSKILL)
#else
	if( pShortcut->m_dwId == 0 && strlen( pShortcut->m_szString ) < 1 && pShortcut->m_dwShortcut != SHORTCUT_SKILLFUN)
#endif
	{
		SetForbid( TRUE );
		return FALSE;
	}
	// ���ο��� �̵��ǰų�, �ܺο��� ���η� 
	if( m_nPosition == TASKBAR_TOP || m_nPosition == TASKBAR_BOTTOM )
	{
		BOOL bForbid = TRUE;
		CRect rect = RECT_APPLET;
		if( rect.PtInRect( point ) )
		{
			point.x -= rect.left;
			point.y -= rect.top;
			point.x /= ICON_SIZE;
			// ���ο��� �̵� 
			if( pShortcut->m_pFromWnd == this )
			{
				LPSHORTCUT lpCurShortcut = (LPSHORTCUT) pShortcut->m_dwData;			

				if( &m_aSlotApplet[ point.x ] == lpCurShortcut )
				{
					//SetForbid( TRUE );
					return FALSE;
				}
				// ���������� �׼ǽ����̴�.
				//if( lpCurShortcut->m_dwData == 2 )
				//	RemoveSkillQueue( lpCurShortcut->m_dwIndex );
			}
			if( pShortcut->m_dwShortcut == SHORTCUT_SKILL )	
			{
				ItemProp* pProp;
				if( pShortcut->m_dwType == 2 )
					pProp =  prj.GetPartySkill( pShortcut->m_dwId );
				else
				{
					LPSKILL pSkill = g_pPlayer->GetSkill( 0, pShortcut->m_dwId );
					pProp = prj.GetSkillProp( pSkill->dwSkill );	
				}
				if( pProp->dwComboStyle != CT_STEP && pProp->dwComboStyle != CT_GENERAL )	
				{
					SetForbid( TRUE );
					return FALSE;	// �����Կ� ����Ϸ��� ��ų�� ���ܱ���� �ƴѰ� ��� ����.
				}
/*				
				ItemProp *pProp = prj.GetSkillProp( pShortcut->m_dwId );	
				if( pProp->dwComboStyle != CT_STEP && pProp->dwComboStyle != CT_GENERAL )	
				{
					SetForbid( TRUE );
					return FALSE;	// �����Կ� ����Ϸ��� ��ų�� ���ܱ���� �ƴѰ� ��� ����.
				}				
				*/
				//if( pProp->dwComboStyle != CT_STEP )
				//{
				//	SetForbid( TRUE );
				//	return FALSE;	// �����Կ� ����Ϸ��� ��ų�� ���ܱ���� �ƴѰ� ��� ����.
				//}
			}

			SetShortcut( point.x, pShortcut->m_dwShortcut, pShortcut->m_dwType, pShortcut->m_dwId, pShortcut->m_pTexture, 0 );
			bForbid = FALSE;
		}
		rect = RECT_ITEM;
//		rect.right += 32;
		if( rect.PtInRect( point ) )
		{
			point.x -= rect.left;
			point.y -= rect.top;
			point.x /= ICON_SIZE;
			// ���ο��� �̵� 
			if( pShortcut->m_pFromWnd == this )
			{
				LPSHORTCUT lpCurShortcut = (LPSHORTCUT) pShortcut->m_dwData;
				if( &m_aSlotItem[ m_nSlotIndex ][ point.x ] == lpCurShortcut )
					return FALSE;
				// ���������� �׼ǽ����̴�.
				//if( lpCurShortcut->m_dwData == 2 )
				//	RemoveSkillQueue( lpCurShortcut->m_dwIndex );
			}
			if( pShortcut->m_dwShortcut == SHORTCUT_CHAT )
			{
				CString sChat	= m_GlobalShortcut.m_szString;
				sChat.Replace( "--", "" );
				sChat.Replace( "'", "" );
				sChat.Replace( "/*", "" );
				sChat.Replace( "*/", "" );
				strcpy( m_GlobalShortcut.m_szString, (const char*)sChat );
			}
			else if( pShortcut->m_dwShortcut == SHORTCUT_SKILL )	
			{
				ItemProp* pProp;
				if( pShortcut->m_dwType == 2 )
					pProp =  prj.GetPartySkill( pShortcut->m_dwId );
				else
				{
					LPSKILL pSkill = g_pPlayer->GetSkill( 0, pShortcut->m_dwId );
					pProp = prj.GetSkillProp( pSkill->dwSkill );	
				}
				if( pProp->dwComboStyle != CT_STEP && pProp->dwComboStyle != CT_GENERAL )	
				{
					SetForbid( TRUE );
					return FALSE;	// �����Կ� ����Ϸ��� ��ų�� ���ܱ���� �ƴѰ� ��� ����.
				}
			}
			SetShortcut( point.x, pShortcut->m_dwShortcut, pShortcut->m_dwType, pShortcut->m_dwId, pShortcut->m_pTexture, 1 );
			bForbid = FALSE;
		}
		rect = RECT_QUEUE;
		if( rect.PtInRect( point ) )
		{
			if( pShortcut->m_dwShortcut == SHORTCUT_SKILL && pShortcut->m_dwType == 0 )		// ��ų�ϰ�츸 ���
			{
				point.x -= rect.left;
				point.y -= rect.top;
				point.x /= SKILL_SIZE;
				// ���ο��� �̵� ; ������ �Ʒ� �κп��� ������ ó���ϳ�, ��ų ť������ �̵��� ������ �ٷ� �߰��ؾ��ϱ� ������ ���⼭ ������ �Ѵ�.
				if( pShortcut->m_pFromWnd == this )
				{
					LPSHORTCUT lpShortcut = (LPSHORTCUT) pShortcut->m_dwData;
					if( lpShortcut->m_dwData == 2 )
					{
						RemoveSkillQueue( lpShortcut->m_dwIndex, FALSE );
						SetSkillQueue( point.x, pShortcut->m_dwType, pShortcut->m_dwId, pShortcut->m_pTexture );// == FALSE )
						return TRUE;
					}
				}
				if( SetSkillQueue( point.x, pShortcut->m_dwType, pShortcut->m_dwId, pShortcut->m_pTexture ) == FALSE )
					SetForbid( TRUE );
				bForbid = FALSE;
			}
		}
		if( pShortcut->m_pFromWnd != this )
			SetForbid( bForbid );
	}
	// ������ ������ ���, �Ǵ� �ȿ��� �̵����� ��� �������� �κ� ����  
	// �½�ũ�ٿ� �ִ� �������� ���� ���� ���� �κп� �巡������ ��� 
	if( pShortcut->m_pFromWnd == this )
	{
		LPSHORTCUT lpShortcut = (LPSHORTCUT) pShortcut->m_dwData;
		// ������ ���� ������ ����
		if( lpShortcut->m_dwData == 0 )
			g_DPlay.SendRemoveAppletTaskBar( (BYTE)( lpShortcut->m_dwIndex ) );
		else
		if( lpShortcut->m_dwData == 1 )
			g_DPlay.SendRemoveItemTaskBar( m_nSlotIndex, (BYTE)( lpShortcut->m_dwIndex ) );
		else
		if( lpShortcut->m_dwData == 2 )
		{
			RemoveSkillQueue( lpShortcut->m_dwIndex );
			//g_DPlay.SendSkillTaskBar( );
			return TRUE;
		}
		lpShortcut->Empty();
	}
	return TRUE;
}
LPSHORTCUT CWndTaskBar::Select( CPoint point )
{
	CRect rect = RECT_APPLET;
	LPSHORTCUT pShortcut = NULL;
	if( rect.PtInRect( point ) )
	{
		point.x -= rect.left;
		point.y -= rect.top;
		point.x /= ICON_SIZE;
		pShortcut = &m_aSlotApplet[ point.x ];
		if( !pShortcut->IsEmpty() )
		{
			return pShortcut;
		}
	}
	rect = RECT_ITEM;
	if( rect.PtInRect( point ) )
	{
		point.x -= rect.left;
		point.y -= rect.top;
		point.x /= ICON_SIZE;
		pShortcut = &m_paSlotItem[ point.x ];
		if( !pShortcut->IsEmpty() )
			return pShortcut;
	}
	rect = RECT_QUEUE;
	if( rect.PtInRect( point ) )
	{
		point.x -= rect.left;
		point.y -= rect.top;
		point.x /= SKILL_SIZE;
		pShortcut = &m_aSlotQueue[ point.x ];
		if( !pShortcut->IsEmpty() )
			return pShortcut;

	}
	rect = CRect( POINT_QUEUE_X - ICON_SIZE - 5, POINT_QUEUE_Y, (POINT_QUEUE_X - ICON_SIZE - 5) + 32, POINT_QUEUE_Y + 32);
	if( rect.PtInRect( point ) )
	{
		m_aSlotSkill.m_dwShortcut = SHORTCUT_SKILLFUN;

		pShortcut   = &m_aSlotSkill;

		if( !pShortcut->IsEmpty() )
			return pShortcut;
	}

	return NULL;
}
void CWndTaskBar::OnMouseMove(UINT nFlags, CPoint point)
{
	if( m_bLButtonDown && IsPush() )
	{
	//PSHORTCUT pShortcut = Select( point );
	//	if( pShortcut && pShortcut == m_pSelectShortcut && !pShortcut->IsEmpty() )
		if( m_pSelectShortcut && !m_pSelectShortcut->IsEmpty() ) //&& m_pSelectShortcut->m_dwShortcut != SHORTCUT_SKILL )
		{
#if __VER >= 12 // __LORD
			if(m_pSelectShortcut->m_dwShortcut == SHORTCUT_LORDSKILL)
			{
				m_pSelectShortcut->m_dwId++;
			}
#endif
			memcpy( &m_GlobalShortcut, m_pSelectShortcut, sizeof( m_GlobalShortcut ) );
			m_GlobalShortcut.m_pFromWnd = this;
			m_GlobalShortcut.m_dwData = (DWORD)m_pSelectShortcut;
			m_pSelectShortcut = NULL;
		}
	}
	CWndNeuz::OnMouseMove( nFlags, point );
}

void CWndTaskBar::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(g_WndMng.m_pWndMenu && g_WndMng.m_pWndMenu->IsVisible())
		g_WndMng.m_pWndMenu->SetVisible(FALSE);

	m_pSelectShortcut = Select( point );
	SetCapture();
}
void CWndTaskBar::OnLButtonUp(UINT nFlags, CPoint point)
{
	ReleaseCapture();
	LPSHORTCUT pShortcut = Select( point );
	
	if( pShortcut && pShortcut == m_pSelectShortcut && !pShortcut->IsEmpty() && pShortcut->m_dwData != 2 )
	{
		g_WndMng.ObjectExecutor( pShortcut );
	}

}

BOOL CWndTaskBar::OnEraseBkgnd(C2DRender* p2DRender)
{
	return TRUE;
}
void CWndTaskBar::PaintFrame( C2DRender* p2DRender )
{
	CRect rect = GetWindowRect();
	//m_pTheme->RenderWndTaskBar( p2DRender, &rect );
	CWndBase::PaintFrame( p2DRender );
}

LPSKILL CWndTaskBar::GetCurrentSkillQueue()
{
	LPSKILL pSkill = NULL;
	LPSHORTCUT pShortcut = &m_aSlotQueue[ m_nUsedSkillQueue ];

	if( pShortcut && pShortcut->IsEmpty() == FALSE )
		pSkill = g_pPlayer->GetSkill( 0, pShortcut->m_dwId );

	return pSkill;
}
//
// ��ųť ���� ��!
//

#ifdef __NEW_TASKBAR_V19
BOOL CWndTaskBar::UseSkillQueue1(CCtrl* pTargetObj)
{
	if (m_nExecute == 2)	return FALSE;	// �̹� ��ų�� �������̶�� �ٽ� ������ ����.
	if (g_pPlayer->m_pActMover->IsActAttack())			return FALSE;		// �̹� ���ݵ����� �̷����� ������ ������ ����.
	if (g_pPlayer->m_pActMover->IsActJump())			return FALSE;		// �����߿� ��ų��� �ȵ�.
	if (g_pPlayer->m_pActMover->IsFly())				return FALSE;
#ifdef __SYS_MOUNT
	if(g_pPlayer->IsMount())				return FALSE;
#endif // __SYS_MOUNT
	if (pTargetObj && pTargetObj->GetType() != OT_MOVER)	return FALSE;

	if (pTargetObj)
	{
		if (pTargetObj->GetType() == OT_OBJ)
			m_idTarget = NULL_ID;
		else
			m_idTarget = ((CCtrl*)pTargetObj)->GetId();
	}
	else
		m_idTarget = NULL_ID;
	CMover* pTargetMover = (CMover*)pTargetObj;
	if (IsInvalidObj(pTargetMover))
		m_idTarget = NULL_ID;

	LPSHORTCUT pShortcut = &m_aSlotQueue[m_nUsedSkillQueue];
	if (pShortcut->IsEmpty() == FALSE)
	{
		LPSKILL pSkill = g_pPlayer->GetSkill(0, pShortcut->m_dwId);
		if (pSkill == NULL)
			return FALSE;

		if (g_pPlayer->IsBullet(pSkill->GetProp()) == FALSE)
			return FALSE;

		m_nExecute = 1;

		if (g_pPlayer->CMD_SetUseSkill(m_idTarget, pShortcut->m_dwId, SUT_QUEUESTART) == 0)		// ������ ����� ����. �̵� + ��ų����� ������ ���.
		{
			OnCancelSkill();
		}
		else
		{
			ItemProp* pItemProp = g_pPlayer->GetActiveHandItemProp();
			if (pItemProp)
			{
				if (pItemProp->dwItemKind3 != IK3_STAFF && pItemProp->dwItemKind3 != IK3_CHEERSTICK)
				{
					g_WndMng.m_pWndWorld->SetNextSkill(NEXTSKILL_NONE);
				}
			}
		}
		return TRUE;
	}
	else
		g_WndMng.m_pWndWorld->SetNextSkill(NEXTSKILL_NONE);

	return FALSE;
}

BOOL CWndTaskBar::UseSkillQueue(CCtrl * pTargetObj)
{
	CWndNewSkillSlot* m_SkillSL = (CWndNewSkillSlot*)g_WndMng.GetWndBase(APP_SLOT);
	if (UseSkillQueue1(pTargetObj))
	{
		if ((g_WndMng.m_pWndTaskBar->m_nUsedSkillQueue == 0) && (m_SkillSL->m_nActionSlot > 0))
		{
			g_WndMng.m_pWndWorld->m_dwNextSkill = NEXTSKILL_ACTIONSLOT;
		}
	}
	return FALSE;
}
#else // __NEW_TASKBAR_V19
BOOL CWndTaskBar::UseSkillQueue(CCtrl * pTargetObj)
{
	if (m_nExecute == 2)	return FALSE;	// �̹� ��ų�� �������̶�� �ٽ� ������ ����.
	if (g_pPlayer->m_pActMover->IsActAttack())			return FALSE;		// �̹� ���ݵ����� �̷����� ������ ������ ����.
	if (g_pPlayer->m_pActMover->IsActJump())			return FALSE;		// �����߿� ��ų��� �ȵ�.
//	if( g_pPlayer->m_pActMover->IsActDamage() )			return FALSE;		// ������ ����߿� ��ų��� �ȵ�.
	if (g_pPlayer->m_pActMover->IsFly())				return FALSE;
#ifdef __SYS_MOUNT
	if(g_pPlayer->IsMount())				return FALSE;
#endif // __SYS_MOUNT
	//	if( g_pPlayer->m_dwFlag & MVRF_SKILL )		return FALSE;				// �̹� ��ų ������̸� ��� �ȵ�.
	if (pTargetObj && pTargetObj->GetType() != OT_MOVER)	return FALSE;

	// ������Ʈ�� ������ Ŭ�� ������
	if (pTargetObj)
	{
		if (pTargetObj->GetType() == OT_OBJ)		// ������Ʈ�� OT_OBJ(���)�̸� ���� ���Ѱɷ� ������.
			m_idTarget = NULL_ID;
		else
			m_idTarget = ((CCtrl*)pTargetObj)->GetId();		// OT_OBJ�� �ƴϸ� ���̵� ������
	}
	else
		m_idTarget = NULL_ID;		// Ÿ���� �������� �ʾ����� NULL_ID
	CMover* pTargetMover = (CMover*)pTargetObj;		// prj.GetMover( m_idTarget );
	if (IsInvalidObj(pTargetMover))		// �Žñ��� Ÿ���̾����� Ÿ�� ���Ѱɷ� ����.
		m_idTarget = NULL_ID;


	m_nUsedSkillQueue = 0;

	LPSHORTCUT pShortcut = &m_aSlotQueue[m_nUsedSkillQueue];

	if (pShortcut->IsEmpty() == FALSE)
	{
		LPSKILL pSkill = g_pPlayer->GetSkill(0, pShortcut->m_dwId);
		if (pSkill == NULL)	return FALSE;

		if (g_pPlayer->IsBullet(pSkill->GetProp()) == FALSE)
			return FALSE;

		m_nExecute = 1;		// 1 ��ų�ٻ�� �������� 
		// ���⿣ m_idTarget�� NULL_ID�� ������ �ִ�.
		if (g_pPlayer->CMD_SetUseSkill(m_idTarget, pShortcut->m_dwId, SUT_QUEUESTART) == 0)		// ������ ����� ����. �̵� + ��ų����� ������ ���.
		{
			OnCancelSkill();	// ù��ų���� �����ߴٸ� ��ųť ����� ���.
		} else
		{	// success
			// 1�ܰ� ������ ap�� �Ҹ���� �ʴ´�.
			ItemProp* pItemProp = g_pPlayer->GetActiveHandItemProp();
			if (pItemProp)
			{   // �տ� ��� �ִ°� �������� ġ�ƽ�� �ƴҶ��� NEXTSKILL_NONE�� ����. ���ϸ� ��ų�� �̾����� ����.
				if (pItemProp->dwItemKind3 != IK3_STAFF && pItemProp->dwItemKind3 != IK3_CHEERSTICK)
					g_WndMng.m_pWndWorld->SetNextSkill(NEXTSKILL_NONE);	// 2006/06/12 ��ųť�� ���������� ��ųť��� ��� Ŭ����.-xuzhu-
			}

		}
		return TRUE;
	}
	else
		g_WndMng.m_pWndWorld->SetNextSkill(NEXTSKILL_NONE);	// �׼ǽ�ų�� ��������� ���.

	return FALSE;
}
#endif // __NEW_TASKBAR_V19

BOOL CWndTaskBar::Process( void )
{
	// ���� ��� �����ؾ��ϴ°͵��� ���⼭...
	CPoint point = GetMousePoint();
#ifdef __SECURITY_FIXES
	CRect wndRect = GetWindowRect();
	if( wndRect.PtInRect( point ) )
#endif
	{
#ifndef __NEW_TASKBAR_V19
		CRect rect = CRect( POINT_APPLET_X, POINT_APPLET_Y, POINT_APPLET_X + ICON_SIZE, POINT_APPLET_Y + ICON_SIZE );
		for( int i = 0; i < m_nMaxSlotApplet; i++ )
		{
			LPSHORTCUT lpShortcut = &m_aSlotApplet[ i ] ;
			if( !lpShortcut->IsEmpty() && rect.PtInRect( point) )
			{
				MotionProp* pMotionProp = prj.GetMotionProp( lpShortcut->m_dwId );
				
				if( IsShortcut( lpShortcut, SHORTCUT_MOTION, MOT_BASE_CHEER ) )
					PutTooTip( lpShortcut, point, &rect );
			}
			rect += CPoint( ICON_SIZE, 0 );
		}
		
		rect = CRect( POINT_ITEM_X, POINT_ITEM_Y, POINT_ITEM_X + ICON_SIZE, POINT_ITEM_Y + ICON_SIZE );
		for( int i = 0; i < MAX_SLOT_ITEM; i++ )
		{
			LPSHORTCUT lpShortcut = &m_paSlotItem[ i ] ;
			if( !lpShortcut->IsEmpty() && rect.PtInRect( point)  )
			{
				if( IsShortcut( lpShortcut, SHORTCUT_MOTION, MOT_BASE_CHEER ) )
					PutTooTip( lpShortcut, point,&rect );
			}
			rect += CPoint( ICON_SIZE, 0 );
		}
		rect = CRect( POINT_QUEUE_X, POINT_QUEUE_Y, POINT_QUEUE_X + SKILL_SIZE, POINT_QUEUE_Y + SKILL_SIZE );
		for( int i = 0; i < MAX_SLOT_QUEUE; i++ )
		{
			LPSHORTCUT lpShortcut = &m_aSlotQueue[ i ] ;
			if( !lpShortcut->IsEmpty() && rect.PtInRect( point)  )
			{
				if( IsShortcut( lpShortcut, SHORTCUT_MOTION, MOT_BASE_CHEER ) )
					PutTooTip( lpShortcut, point,&rect );
			}
			rect += CPoint( SKILL_SIZE, 0 );
		}
#endif
	}
	
	if( m_nExecute )
	{
		if( m_idTarget != NULL_ID )		// m_idTarget�� NULL_ID�ΰ��� �ڱ� �ڽſ��� �����ⶫ�� ĵ�����Ѽ� �ȵȴ�.
		{
			CMover* pObj = prj.GetMover( m_idTarget );
			if( IsInvalidObj(pObj) )						// �����߿� ����� �������ٸ� ��ų����� ����.
				OnCancelSkill();
		}
//		if( pObj && pObj->IsDie() )						// ������ ����� �׾����� ��ų�� ���� ����.
//			OnCancelSkill();

//		if( (g_pPlayer->m_dwFlag & MVRF_SKILL) == 0 )
//			OnCancelSkill();													// ��ų��� ����
	}
	// �巡�� ���̶���Ʈ ���� ���� ó�� 
	if( m_GlobalShortcut.IsEmpty() == FALSE )
	{
		m_dwHighAlpha += 10;
		if( m_dwHighAlpha >= 256 )
			m_dwHighAlpha = 0;
	}
	// �巡���߿��� ��Ű�� ����� �� ���� 
	else
	{
#ifdef __NEW_TASKBAR_V19
		if (g_bKeyTable[VK_HOME])
		{
			g_bKeyTable[VK_HOME] = FALSE;
			g_WndMng.ScreenCapture();
		}
#endif // __NEW_TASKBAR_V19
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// ��Ű ó�� 
		////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if( g_bKeyTable[ VK_RETURN ] ) 
		{
			g_bKeyTable[ VK_RETURN ] = FALSE;
			CWndBase* pWndBase = GetWndBase( APP_COMMUNICATION_CHAT );
			if( pWndBase == NULL )
			{
				g_WndMng.ObjectExecutor( SHORTCUT_APPLET, APP_COMMUNICATION_CHAT );
				CWndChat* pWndChat = (CWndChat*)GetWndBase( APP_COMMUNICATION_CHAT );
				if( pWndChat != NULL )
				{
					pWndChat->m_wndEdit.SetFocus();
				}
			}
		}
		else
		{
			AppletFunc* pApplet;
			DWORD dwIdApplet;
			POSITION pos = g_WndMng.m_mapAppletFunc.GetStartPosition();
			BOOL bKey = FALSE;
			while( pos )
			{
				g_WndMng.m_mapAppletFunc.GetNextAssoc( pos, dwIdApplet, (void*&)pApplet );
				
#ifdef __XKEYEDGE
				bKey = g_bKeyTable[ pApplet->m_cHotkey ];
				if( bKey && !g_bKeyTable2[ pApplet->m_cHotkey ] )
#else
				if( g_bKeyTable[ pApplet->m_cHotkey ] )			//gmpbigsun: �Ͽ�¡ YŰ( ����â ) �˻� 
#endif
				{
					g_Error_State.m_ch = pApplet->m_cHotkey;
					g_Error_State.m_bIsShowWnd = TRUE;
					g_Error_State.m_dwWndId = pApplet->m_dwIdApplet;
					
					g_WndMng.ObjectExecutor( SHORTCUT_APPLET, pApplet->m_dwIdApplet );
#ifndef __XKEYEDGE					
					g_bKeyTable[ pApplet->m_cHotkey ] = FALSE;
#endif					
				}			
#ifdef __XKEYEDGE
				g_bKeyTable2[ pApplet->m_cHotkey ] = bKey;
				bKey = FALSE;
#endif

			}

#ifndef __NEW_TASKBAR_V19
			CWndRegVend* pWndRegVend = (CWndRegVend*)g_WndMng.GetWndBase(APP_VENDOREX_SELL);
			CWndRegVend* pWndVendorBuy = (CWndRegVend*)g_WndMng.GetWndBase(APP_VENDOREX_BUY);

			if (!pWndRegVend || !pWndVendorBuy)
			{
				DWORD* dwHotkey;
#ifdef __Y_INTERFACE_VER3				
				DWORD dwHotkey1[10] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };
				DWORD dwHotkey2[10] = { 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79 };

				if (g_Option.m_nInterface == 2)
					dwHotkey = dwHotkey1;
				else
					dwHotkey = dwHotkey2;
#else //__Y_INTERFACE_VER3
				DWORD dwHotkey1[10] = { 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79 };
				dwHotkey = dwHotkey1;
#endif //__Y_INTERFACE_VER3

				for (int i = 0; i < 10; i++)
				{
					if (g_bKeyTable[dwHotkey[i]] && g_bSlotSwitchAboutEquipItem[i] == FALSE)
					{
						LPSHORTCUT lpShortcut = &m_paSlotItem[i];
						if (lpShortcut->m_dwShortcut == SHORTCUT_ITEM)
						{
							CItemBase* pItemBase = g_pPlayer->GetItemId(lpShortcut->m_dwId);
							if (pItemBase)
							{
								int nPart = pItemBase->GetProp()->dwParts;
								if (nPart != -1)
									g_bSlotSwitchAboutEquipItem[i] = TRUE;
							}
						}
						g_WndMng.ObjectExecutor(lpShortcut);
						g_bKeyTable[dwHotkey[i]] = 0;
					}
				}
			}
#endif // __NEW_TASKBAR_V19
		}
	}

	UpdateItem();
	return CWndBase::Process();
}

// ��ų�� ����� ���(�ߴ�)��.
void CWndTaskBar::OnCancelSkill( void )
{
	if( g_pPlayer->m_dwReqFlag & REQ_USESKILL )
		return;

#ifdef __NEW_TASKBAR_V19
	int tempoespera = 0;
	bool podeusar;
	tempoespera--;
	podeusar = false;
#endif // __NEW_TASKBAR_V19
	m_nExecute = 0;
	m_nUsedSkillQueue = 0;
	g_pPlayer->ClearDestObj();
	g_WndMng.m_pWndWorld->SetNextSkill( NEXTSKILL_NONE );
}

// ��ų ���� �������� ȣ��.
void CWndTaskBar::OnEndSkill( void )
{
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// �½�ũ ���� �Ŵ� ó�� ����  
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////

CWndTaskMenu::CWndTaskMenu()
{
	m_pMenu1 = NULL;
	m_pMenu2 = NULL;
	m_pMenu3 = NULL;
	m_pMenu4 = NULL;
	m_pMenu5 = NULL;
	m_pMenu6 = NULL;
	m_pMenu7 = NULL;
}

CWndTaskMenu::~CWndTaskMenu()
{
	SAFE_DELETE( m_pMenu1 );
	SAFE_DELETE( m_pMenu2 );
	SAFE_DELETE( m_pMenu3 );
	SAFE_DELETE( m_pMenu4 );
	SAFE_DELETE( m_pMenu5 );
	SAFE_DELETE( m_pMenu6 );
	SAFE_DELETE( m_pMenu7 );
}
void CWndTaskMenu::OnDraw(C2DRender* p2DRender)
{
	return;
	p2DRender->TextOut( 10, 20,  _T( "MASQUERADE" ),  D3DCOLOR_ARGB( 255, 250, 250, 250 ) );

	CRect rect = GetWindowRect();
	// �׵θ� �ڽ� 
	DWORD dwColor1t = D3DCOLOR_ARGB( 055,  91, 104, 205 );
	DWORD dwColor2t = D3DCOLOR_ARGB( 055, 116, 128, 220 );
	DWORD dwColor4t = D3DCOLOR_ARGB( 055, 143, 173, 245 );
	DWORD dwColor1b = D3DCOLOR_ARGB( 055,  41, 104, 155 );
	DWORD dwColor2b = D3DCOLOR_ARGB( 055,  66,  78, 170 );
	DWORD dwColor4b = D3DCOLOR_ARGB( 055, 143, 173, 245 );

	DWORD dwColor3t = D3DCOLOR_ARGB( 155, 250, 250, 250 );
	DWORD dwColor3b = D3DCOLOR_ARGB(  55,  00,  00,  00 );
	
	//p2DRender->RenderRoundRect( rect, dwColor1t, dwColor1t, dwColor1b, dwColor1b );
	rect.DeflateRect(1,1);
	//p2DRender->RenderRoundRect( rect, dwColor2t, dwColor2t, dwColor2b, dwColor2b );
//	rect.DeflateRect(1,1);

	CRect rect1 = rect; rect1.bottom = rect1.top + 40;
	CRect rect2 = rect; rect2.top    = rect2.top + 40;

	p2DRender->RenderFillRect( rect1, dwColor3t, dwColor3t, dwColor3b, dwColor3b );
	p2DRender->RenderFillRect( rect2, dwColor3b, dwColor3b, dwColor4b, dwColor4b );

//	p2DRender->RenderLine( CPoint( 10, 5 * 22 + 54 ), CPoint( 140, 5 * 22 + 54 ), dwColor1t );
	// client ���� ĥ�ϱ� 
	//OnEraseBkgnd(p2DRender);
	//.OffsetRect(-rect.TopLeft());
	//p2DRender->PaintRect( rect,MKHIGHRGB(255>>3,255>>3,255>>3) );
	//p2DRender->TextOut( 5,20,"HP : 100 / 100", dwColor1t );
	//p2DRender->TextOut( 5,35,"MP : 100 / 100", dwColor1t );
}
BOOL CWndTaskMenu::Process()
{
	if(	CWndBase::m_GlobalShortcut.m_dwShortcut != SHORTCUT_NONE )
		return CWndBase::Process();

	if( IsVisible() == FALSE )
		return CWndBase::Process();

	for( int i = 0; i < m_awndMenuItem.GetSize(); i++ )
	{
		BOOL bHighLight = FALSE;
		CWndButton* pWndButton = (CWndButton*)m_awndMenuItem.GetAt( i );
		if( pWndButton->GetClientRect( TRUE ).PtInRect( m_ptMouse ) )
		{
			// ��� ����� 
			if( pWndButton->m_pWndMenu == NULL || pWndButton->m_pWndMenu->IsVisible( ) == FALSE ) 
			{
				for( int i2 = 0; i2 < m_awndMenuItem.GetSize(); i2++)
				{
					if( ((CWndButton*)m_awndMenuItem.GetAt( i2 ) )->m_pWndMenu )
						((CWndButton*)m_awndMenuItem.GetAt( i2 ) )->m_pWndMenu->SetVisibleSub( FALSE );
				}
			}
			// �� �Ŵ��� ���̰� ��Ŀ�� �ֱ� 
			if( pWndButton->m_pWndMenu )
			{
				if( pWndButton->m_pWndMenu->IsVisible() == FALSE )
				{
					CRect rect = pWndButton->GetScreenRect();
					pWndButton->m_pWndMenu->Move( CPoint( rect.right , rect.top ) );
				}
				// �޴��� ��ǥ ���� 
				CRect rcButton = pWndButton->GetScreenRect();
				pWndButton->m_pWndMenu->Move( CPoint( rcButton.right, rcButton.top ) );
				// �׷��� �� �޴��� ȭ���� ����ٸ� ��ġ�� ���� 
				CRect rcMenu = pWndButton->m_pWndMenu->GetScreenRect();
				CRect rcLayout = m_pWndRoot->GetLayoutRect();
				CPoint pt = rcMenu.TopLeft();
				if( rcMenu.right > rcLayout.right )
				{
					pt.x = rcButton.left - rcMenu.Width();
					//pWndButton->m_pWndMenu->Move( CPoint( rcButton.left - rcMenu.Width(), rcButton.top ) );
				}
				if( rcMenu.bottom > rcLayout.bottom )
				{
					pt.y -= rcMenu.bottom - rcLayout.bottom;
					//pWndButton->m_pWndMenu->Move( CPoint( rcButton.left - rcMenu.Width(), rcButton.top ) );
				}
				pWndButton->m_pWndMenu->Move( pt );
				pWndButton->m_pWndMenu->SetVisible( TRUE );
				pWndButton->m_pWndMenu->SetFocus();
			}
		}
	}
	return CWndBase::Process();
}
void CWndTaskMenu::SetTexture( CWndButton* pWndButton )
{
	pWndButton->SetTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, g_WndMng.GetAppletFunc( pWndButton->GetWndId() )->m_pszIconName ) );
}

void CWndTaskMenu::OnInitialUpdate()
{
	CWndMenu::OnInitialUpdate();

	CWndButton* pWndButton;
	// 0 ~ 9�� 
	if( g_pPlayer->IsAuthHigher( AUTH_GAMEMASTER ) )
	{
		pWndButton = AppendMenu( this, 0, APP_DEBUGINFO     , GETTEXT( TID_APP_DEBUGINFO     ) ); 
	}

	pWndButton = AppendMenu( this, 0, APP_STATUS1    , GETTEXT( TID_APP_STATUS        ) );
	pWndButton = AppendMenu( this, 0, APP_NAVIGATOR , GETTEXT( TID_APP_NAVIGATOR     ) );
#if __VER >= 13 // __RENEW_CHARINFO
	pWndButton = AppendMenu( this, 0, APP_CHARACTER3 , GETTEXT( TID_APP_CHARACTER     ) );
#elif __VER >= 9 // __CSC_VER9_2
	pWndButton = AppendMenu( this, 0, APP_CHARACTER2 , GETTEXT( TID_APP_CHARACTER     ) );
#else //__CSC_VER9_2
	pWndButton = AppendMenu( this, 0, APP_CHARACTER , GETTEXT( TID_APP_CHARACTER     ) );
#endif //__CSC_VER9_2
	pWndButton = AppendMenu( this, 0, APP_INVENTORY , GETTEXT( TID_APP_INVENTORY     ) );
#if __VER >= 11 // __SYS_POCKET
#ifndef __TMP_POCKET
	pWndButton = AppendMenu( this, 0, APP_BAG_EX , GETTEXT( TID_APP_BAG_EX     ) );
#endif
#if __VER >= 13 // __HOUSING
	pWndButton = AppendMenu( this, 0, APP_HOUSING, GETTEXT(TID_GAME_HOUSING_BOX));
#endif // __HOUSING
#endif // __SYS_POCKET
#if __VER >= 8 // __S8_VENDOR_REVISION
	pWndButton = AppendMenu( this, 0, APP_VENDOR_REVISION , GETTEXT( TID_APP_VENDOR     ) );
#else // __VER >= 8 // __S8_VENDOR_REVISION
	pWndButton = AppendMenu( this, 0, APP_VENDOREX , GETTEXT( TID_APP_VENDOR     ) );
#endif // __VER >= 8 // __S8_VENDOR_REVISION
#if __VER >= 10 // __CSC_VER9_1
#ifdef __NEW_SKILL_TREE
	pWndButton = AppendMenu( this, 0, APP_SKILL4     , GETTEXT( TID_APP_SKILL         ) );
#else // __NEW_SKILL_TREE
	pWndButton = AppendMenu( this, 0, APP_SKILL3     , GETTEXT( TID_APP_SKILL         ) );
#endif // __NEW_SKILL_TREE
#else
	pWndButton = AppendMenu( this, 0, APP_SKILL1     , GETTEXT( TID_APP_SKILL         ) );
#endif //__CSC_VER9_1
#if __VER >= 15 // __IMPROVE_QUEST_INTERFACE
	pWndButton = AppendMenu( this, 0, APP_QUEST_EX_LIST     , GETTEXT( TID_APP_QUEST         ) );
#else // __IMPROVE_QUEST_INTERFACE
	pWndButton = AppendMenu( this, 0, APP_QUEST     , GETTEXT( TID_APP_QUEST         ) );
#endif // __IMPROVE_QUEST_INTERFACE
	pWndButton = AppendMenu( this, 0, APP_MOTION   , GETTEXT( TID_APP_MOTION       ) );

#if __VER >= 9  // __INSERT_MAP
#ifdef __IMPROVE_MAP_SYSTEM
	pWndButton = AppendMenu( this, 0, APP_MAP_EX, GETTEXT( TID_APP_MAP ) );
#else // __IMPROVE_MAP_SYSTEM
	pWndButton = AppendMenu( this, 0, APP_MAP, GETTEXT( TID_APP_MAP));//GETTEXT( TID_APP_MAP));
#endif // __IMPROVE_MAP_SYSTEM
#endif
	CWndButton* pWndButton7 = NULL;
	pWndButton7 = AppendMenu( this, 0, 0 , GETTEXT( TID_APP_COMMITEM  ) ); pWndButton7->SetTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, _T( "icon_Folder.dds" ) ) ); 

	CWndButton* pWndButton1 = AppendMenu( this, 0, 0 , GETTEXT( TID_APP_COMMUNICATION ) ); pWndButton1->SetTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, _T( "icon_Folder.dds" ) ) );
	CWndButton* pWndButton2 = AppendMenu( this, 0, 0 , GETTEXT( TID_APP_COMMUNITY     ) ); pWndButton2->SetTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, _T( "icon_Folder.dds" ) ) );
//	CWndButton* pWndButton3 = AppendMenu( this, 0, 0 , GETTEXT( TID_APP_FIND          ) ); pWndButton3->SetTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, _T( "icon_Folder.dds" ) ) );
	CWndButton* pWndButton5 = AppendMenu( this, 0, 0 , GETTEXT( TID_APP_INFOMATION    ) ); pWndButton5->SetTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, _T( "icon_Folder.dds" ) ) );
	CWndButton* pWndButton6 = AppendMenu( this, 0, 0 , GETTEXT( TID_APP_HELPER        ) ); pWndButton6->SetTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, _T( "icon_Folder.dds" ) ) ); // �����, �ó���
	CWndButton* pWndButton4 = AppendMenu( this, 0, APP_OPTIONEX, GETTEXT(TID_APP_OPTION) );

	pWndButton = AppendMenu( this, 0, APP_LOGOUT    , GETTEXT( TID_APP_LOGOUT      ) );
	pWndButton = AppendMenu( this, 0, APP_QUIT      , GETTEXT( TID_APP_QUIT          ) );

//	if( GetLanguage() == LANG_TWN )
//		pWndButton	= AppendMenu( this, 0, APP_WEBBOX2	, GETTEXT( TID_TIP_QOODO	) );

	CWndBase::SetTexture(m_pApp->m_pd3dDevice, MakePath( DIR_THEME, _T("WndTaskMenu.tga")), TRUE);

	for(int i = 0; i < m_awndMenuItem.GetSize(); i++)
	{
		CWndButton* pWndButton = GetMenuItem( i );
		pWndButton->SetWndRect( CRect(  10, 50 + ( i * 22 ), m_pTexture->m_size.cx - 20, 50 + 20 + ( i * 22 ) ) );
	}
	SetWndRect( CRect( 0, 0, m_pTexture->m_size.cx, m_pTexture->m_size.cy ) );

//	CRect rect = g_WndMng.m_pWndTaskBar->m_wndMenu.GetScreenRect();
//	Move( CPoint( 0, rect.top - GetWindowRect().Height() ) );

	m_pMenu1 = new CWndMenu;
	m_pMenu1->CreateMenu( this );
	pWndButton = AppendMenu( m_pMenu1, 0, APP_COMMUNICATION_CHAT , GETTEXT( TID_APP_COMMUNICATION_CHAT    ) );
	pWndButton = AppendMenu( m_pMenu1, 0, APP_MESSENGER_         , GETTEXT( TID_APP_MESSENGER ) );
#if __VER >= 13 // __CSC_VER13_2
	pWndButton = AppendMenu( m_pMenu1, 0, APP_COUPLE_MAIN        , GETTEXT( TID_GAME_COUPLE ) );
#endif //__CSC_VER13_2
	pWndButton->m_shortcut.m_dwShortcut = SHORTCUT_APPLET; SetTexture( pWndButton );
	pWndButton1->SetMenu( m_pMenu1 );

	m_pMenu2 = new CWndMenu;
	m_pMenu2->CreateMenu( this );
	pWndButton = AppendMenu( m_pMenu2, 0, APP_PARTY      , GETTEXT( TID_APP_PARTY          ) ) ;
	pWndButton = AppendMenu( m_pMenu2, 0, APP_GUILD      , GETTEXT( TID_APP_COMPANY         ) ) ;
	
#ifdef __GUILDVOTE
	pWndButton = AppendMenu( m_pMenu2, 0, APP_GUILD_VOTE      , GETTEXT( TID_GAME_TOOLTIP_GUILDVOTE     ) ) ;
#endif	
	pWndButton2->SetMenu( m_pMenu2 );

	m_pMenu5 = new CWndMenu;
	m_pMenu5->CreateMenu( this );
	pWndButton = AppendMenu( m_pMenu5, 0, APP_INFO_NOTICE   , GETTEXT( TID_APP_INFO_NOTICE   ) ); 
	pWndButton5->SetMenu( m_pMenu5 );

	m_pMenu6 = new CWndMenu;
	m_pMenu6->CreateMenu( this );
	pWndButton = AppendMenu( m_pMenu6, 0, APP_HELPER_HELP , GETTEXT( TID_APP_HELPER_HELP ) );
	pWndButton = AppendMenu( m_pMenu6, 0, APP_HELPER_TIP  , GETTEXT( TID_APP_HELPER_TIP  ) );
	pWndButton = AppendMenu( m_pMenu6, 0, APP_HELPER_FAQ  , GETTEXT( TID_APP_HELPER_FAQ  ) );
#if __VER >= 12 // __MOD_TUTORIAL
	pWndButton = AppendMenu( m_pMenu6, 0, APP_INFOPANG , GETTEXT( TID_APP_INFOPANG ) );
	//pWndButton->SetTexture( g_Neuz.m_pd3dDevice, MakePath( DIR_ICON, _T( "icon_Folder.dds" ) ) );
#endif
#ifdef __NEW_WEB_BOX
#ifdef __INTERNALSERVER
	pWndButton = AppendMenu( m_pMenu6, 0, APP_WEBBOX2 , GETTEXT( TID_GAME_HELPER_WEB_BOX_ICON_TITLE ) );
#else // __INTERNALSERVER
	if( ( GetLanguage() == LANG_ENG && GetSubLanguage() == LANG_SUB_USA ) )
	{
		pWndButton = AppendMenu( m_pMenu6, 0, APP_WEBBOX2 , GETTEXT( TID_GAME_HELPER_WEB_BOX_ICON_TITLE ) );
	}
#endif // __INTERNALSERVER
#endif // __NEW_WEB_BOX
	pWndButton6->SetMenu( m_pMenu6 );
	
	m_pMenu7 = new CWndMenu;
	m_pMenu7->CreateMenu( this );
	pWndButton = AppendMenu( m_pMenu7, 0, APP_WEBBOX, GETTEXT( TID_APP_ITEMMALL ) ); pWndButton->m_shortcut.m_dwShortcut = SHORTCUT_APPLET; SetTexture( pWndButton );
	pWndButton = AppendMenu( m_pMenu7, 0, APP_COMM_ITEM , GETTEXT( TID_APP_ITEMTIME ) ); pWndButton->m_shortcut.m_dwShortcut = SHORTCUT_APPLET; SetTexture( pWndButton );
	pWndButton7->SetMenu( m_pMenu7 );
}
CWndButton* CWndTaskMenu::AppendMenu( CWndMenu* pWndMenu, UINT nFlags, UINT nIDNewItem,	LPCTSTR lpszNewItem )
{
	CWndButton* pWndButton = (CWndButton*)pWndMenu->AppendMenu( nFlags, nIDNewItem, lpszNewItem );
	AppletFunc* pAppletFunc = g_WndMng.GetAppletFunc( nIDNewItem ); 
	if( pAppletFunc )
	{
		pWndButton->m_cHotkey = pAppletFunc->m_cHotkey;
		CString string;
		if( pAppletFunc->m_cHotkey == 0 )
			string.Format( "%s", pAppletFunc->m_pAppletDesc );
		else
			string.Format( "%s\n[%s %c]", pAppletFunc->m_pAppletDesc,  prj.GetText( TID_GAME_TOOLTIP_HOTKEY ), pAppletFunc->m_cHotkey );
		pWndButton->m_strToolTip = string;
		pWndButton->m_shortcut.m_dwShortcut = SHORTCUT_APPLET; 
		SetTexture( pWndButton );
	}
	
//	SetWndRect( CRect( 0, 0, 180, 50 + 5 + 5 + ( m_awndMenuItem.GetSize() * 22 ) ) );

	return pWndButton;
	/*

  CString string;
  if( pAppletFunc->m_cHotkey == 0 )
  string.Format( "���÷�\n%s", pAppletFunc->m_pAppletDesc );
  else
  string.Format( "���÷�\n%s\n[����Ű %c]", pAppletFunc->m_pAppletDesc, pAppletFunc->m_cHotkey );
  g_toolTip.PutToolTip( pShortcut->m_dwId , string, *pRect, point, 0 );
  
	CWndButton* pWndButton = new CWndButton;
	int nCount = m_awndMenuItem.GetSize();
	CSize size = m_pFont->GetTextExtent( lpszNewItem );
	if( size.cx > m_nLargeWidth )
		m_nLargeWidth = size.cx + 60;
	pWndButton->Create(lpszNewItem, WBS_MENUITEM | WBS_HIGHLIGHT, CRect( 2, 2 + ( nCount * 22 ), m_nLargeWidth, 2 + ( nCount * 22 ) + 20 ), this, nIDNewItem );
	m_awndMenuItem.Add( pWndButton );
	for( int i = 0; i < m_awndMenuItem.GetSize(); i++ )
	{
		pWndButton = (CWndButton*)m_awndMenuItem.GetAt( i );
		CRect rect = pWndButton->GetWindowRect( TRUE );
		rect.right = rect.left + m_nLargeWidth; 
		pWndButton->SetWndRect( rect );
	}
	SetWndRect( CRect( 0, 0, m_nLargeWidth + 10, 5 + 5 + ( ( nCount + 1 ) * 22 ) ) );
	return pWndButton;
	*/
}

BOOL CWndTaskMenu::Initialize(CWndBase* pWndParent,DWORD dwWndId)
{
	CreateMenu( &g_WndMng );
	SetVisible(TRUE);
	return TRUE;
}

void CWndTaskMenu::OnKillFocus(CWndBase* pNewWnd)
{
	if(g_WndMng.m_pWndTaskBar != pNewWnd)
		CWndMenu::OnKillFocus(pNewWnd);
}

BOOL CWndTaskMenu::OnCommand( UINT nID, DWORD dwMessage, CWndBase* pWndBase )
{
//	g_WndMng.ObjectExecutor( SHORTCUT_APPLET, nID );
	return TRUE;
}
BOOL CWndTaskMenu::OnChildNotify(UINT message,UINT nID,LRESULT* pLResult)
{
	if( message == WNM_CLICKED )
		g_WndMng.ObjectExecutor( SHORTCUT_APPLET, nID );
	return TRUE;
}
void CWndTaskMenu::OnSize(UINT nType, int cx, int cy)
{
	CWndMenu::OnSize( nType, cx, cy );
}
void CWndTaskMenu::OnLButtonUp(UINT nFlags, CPoint point)
{
	//if(IsWndStyle(WBS_CAPTION) && m_bPickup)
	{//
	//	m_wndTitleBar.m_wndMinimize.SetVisible(TRUE);
		//m_wndTitleBar.m_wndMaximize.SetVisible(TRUE);
	}
}
void CWndTaskMenu::OnLButtonDown(UINT nFlags, CPoint point)
{
//	CWndBase::OnLButtonDown(nFlags,point
	if(IsWndRoot())
		return;
//	return;

}

void CWndTaskMenu::PaintFrame( C2DRender* p2DRender )
{
//	p2DRender->RenderFillRect( GetWindowRect(), D3DCOLOR_ARGB( 255, 76,124,193 ) );
//	p2DRender->RenderRect( GetWindowRect(), D3DCOLOR_ARGB( 255, 36,74,100 ) );
	CWndBase::PaintFrame( p2DRender );
}
BOOL CWndTaskMenu::OnEraseBkgnd( C2DRender* p2DRender )
{
	CRect rect = GetWindowRect();
	rect.top += 50;
//	p2DRender->RenderFillRect(rect, D3DCOLOR_ARGB( 255, 255,255,255 ) );
	return CWndBase::OnEraseBkgnd( p2DRender );
}


void CWndTaskBar::RenderCollTime(CPoint pt, DWORD dwSkillId, C2DRender* p2DRender )
{
	LPSKILL lpSkill = &g_pPlayer->m_aJobSkill[ dwSkillId ];
	if( lpSkill )
	{
		DWORD dwDelay = g_pPlayer->GetReuseDelay( dwSkillId );
		if( dwDelay > 0 )
		{
#if __VER >= 9	// __SKILL_0706
			ItemProp* pSkillProp	= lpSkill->GetProp();
			ASSERT( pSkillProp );
			AddSkillProp* pAddSkillProp	= prj.GetAddSkillProp( pSkillProp->dwSubDefine, lpSkill->dwLevel );
			ASSERT( pAddSkillProp );
			RenderRadar( p2DRender, pt, 
			             pAddSkillProp->dwCooldown - dwDelay, 
						 pAddSkillProp->dwCooldown );	
#else	// __SKILL_0706
			RenderRadar( p2DRender, pt, 
			             lpSkill->GetProp()->dwSkillReady - dwDelay, 
						 lpSkill->GetProp()->dwSkillReady );	
#endif	// __SKILL_0706
		}
	}				
}

#if __VER >= 12 // __LORD
	void CWndTaskBar::RenderLordCollTime( CPoint pt, DWORD dwSkillId, C2DRender* p2DRender )
	{
		CCLord* pLord									= CCLord::Instance();
		CLordSkillComponentExecutable* pComponent		= pLord->GetSkills()->GetSkill(dwSkillId);
		if(!pComponent) return;
		DWORD dwDelay = 0;
		if(pComponent->GetTick() > 0)
			RenderRadar( p2DRender, pt, pComponent->GetCooltime() - pComponent->GetTick(), pComponent->GetCooltime() );	
	}
#endif

void CWndTaskBar::RenderOutLineLamp(int x, int y, int num, DWORD size)
{
	CPoint Point = CPoint( x, y );
	LONG   thick = 10;

	D3DXCOLOR dwColorDest2  = D3DCOLOR_ARGB( 0, 40, 0, 255 );

	D3DXCOLOR dwColor  = D3DCOLOR_ARGB( 196, 40, 0, 255 );

	D3DXCOLOR dwColor1 = D3DCOLOR_ARGB( 0, 255, 255, 255 );
	D3DXCOLOR dwColor2 = D3DCOLOR_ARGB( 0, 255, 255, 255 );

	static BOOL  bReverse = FALSE;
	static FLOAT fLerp = 0.0f;

	if( bReverse )
		fLerp-=0.05f;
	else
		fLerp+=0.05f;

	if( fLerp > 1.0f )
	{
		bReverse = TRUE;
		fLerp = 1.0f;
	}
	else
	if( fLerp < 0.0f )
	{
		bReverse = FALSE;
		fLerp = 0.0f;
	}
	
	D3DXColorLerp( &dwColor2, &dwColor, &dwColorDest2, fLerp);
	
	CRect Rect = CRect( 0, 0, (size * num), size );
	
	m_p2DRender->RenderFillRect( CRect( (Point.x+Rect.left)-thick, Point.y+Rect.top, (Point.x+Rect.left), Point.y+Rect.bottom ),
		dwColor1, dwColor2, dwColor1, dwColor2 );
	
	m_p2DRender->RenderFillRect( CRect( (Point.x+Rect.left), (Point.y+Rect.top)-thick, (Point.x+Rect.right), Point.y+Rect.top ),
		dwColor1, dwColor1, dwColor2, dwColor2 );
	
	m_p2DRender->RenderFillRect( CRect( (Point.x+Rect.right), Point.y+Rect.top, (Point.x+Rect.right)+thick, Point.y+Rect.bottom ),
		dwColor2, dwColor1, dwColor2, dwColor1 );
	
	m_p2DRender->RenderFillRect( CRect( (Point.x+Rect.left), (Point.y+Rect.bottom), (Point.x+Rect.right), (Point.y+Rect.bottom)+thick ),
		dwColor2, dwColor2, dwColor1, dwColor1 );
}

BOOL CWndTaskBar::IsShortcut( LPSHORTCUT lpShortcut, DWORD dwShortcut, DWORD dwId )
{
	if( lpShortcut->m_dwShortcut == SHORTCUT_APPLET )
	{
	}
	else
	if( lpShortcut->m_dwShortcut == SHORTCUT_SKILL )
	{
	}
	else
	if( lpShortcut->m_dwShortcut == SHORTCUT_ITEM )
	{
	}
	else
	if( lpShortcut->m_dwShortcut == SHORTCUT_CHAT )
	{
	}
	else
	if( lpShortcut->m_dwShortcut == SHORTCUT_MOTION )
	{
		if( lpShortcut->m_dwShortcut == dwShortcut )
		{
			MotionProp* pMotionProp = prj.GetMotionProp( dwId );
		
			if( pMotionProp )
			{
				return TRUE;
			}
		}
	}
	
	return FALSE;
}

#ifdef __NEW_TASKBAR_V19
CWndTaskBar_HUD::CWndTaskBar_HUD()
{
	CWndTaskBarInterface::CWndTaskBarInterface();
	m_nDisplay = 2;
	m_nHPWidth = -1;
	m_nMPWidth = -1;
	m_nFPWidth = -1;
	m_nEXPWidth = -1;

	m_pAppletSlotOpen = FALSE;
	m_paltSlotOpen = FALSE;
	m_pfSlotOpen = FALSE;
	m_pVBHPGauge = NULL;
	m_pVBMPGauge = NULL;
	m_pVBFPGauge = NULL;
	m_pVBEXPGauge = NULL;

	m_bVBHPGauge = TRUE;
	m_bVBMPGauge = TRUE;
	m_bVBFPGauge = TRUE;

	m_nSlotIndex = 0;
	m_nActionListener[0] = '1';
	m_nActionListener[1] = '2';
	m_nActionListener[2] = '3';
	m_nActionListener[3] = '4';
	m_nActionListener[4] = '5';
	m_nActionListener[5] = '6';
	m_nActionListener[6] = '7';
	m_nActionListener[7] = '8';
	m_nActionListener[8] = '9';
	m_nActionListener[9] = '0';
}

void CWndTaskBar_HUD::OnInitialUpdate()
{
	CWndTaskBarInterface::OnInitialUpdate();
	{
		m_HPGaugeTexture.LoadTexture(m_pApp->m_pd3dDevice, MakePath(DIR_THEME, "Targetgauge01.tga"), 0xffff00ff, TRUE);
		m_MPGaugeTexture.LoadTexture(m_pApp->m_pd3dDevice, MakePath(DIR_THEME, "Targetgauge02.tga"), 0xffff00ff, TRUE);
		m_FPGaugeTexture.LoadTexture(m_pApp->m_pd3dDevice, MakePath(DIR_THEME, "Targetgauge03.tga"), 0xffff00ff, TRUE);
	}
	m_EXPGaugeTexture.LoadTexture(m_pApp->m_pd3dDevice, MakePath(DIR_THEME, "WndMainBarGauge.tga"), 0xffff00ff, TRUE);

	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rectWindow = GetWindowRect();
	CPoint point((rectRoot.right - 166) - rectWindow.Width(), rectRoot.bottom - rectWindow.Height());
	Move(point);

	pWndTaskBar_HUD_EX3 = new CWndTaskBar_HUD_EX3;
	pWndTaskBar_HUD_EX2 = new CWndTaskBar_HUD_EX2;
	pWndTaskBar_HUD_EX1 = new CWndTaskBar_HUD_EX1;
	pWndTaskBar_HUD_EX3->Initialize(&g_WndMng);
	pWndTaskBar_HUD_EX2->Initialize(&g_WndMng);
	pWndTaskBar_HUD_EX1->Initialize(&g_WndMng);

	if (g_Option.m_nTBDisplay == 0)
	{
		pWndTaskBar_HUD_EX1->SetVisible(FALSE);
		pWndTaskBar_HUD_EX3->SetVisible(FALSE);
		pWndTaskBar_HUD_EX2->SetVisible(FALSE);
	}
	else if (g_Option.m_nTBDisplay == 1)
	{
		pWndTaskBar_HUD_EX3->SetVisible(FALSE);
		pWndTaskBar_HUD_EX2->SetVisible(FALSE);
		m_paltSlotOpen = TRUE;
	}
	else if (g_Option.m_nTBDisplay == 2)
	{
		pWndTaskBar_HUD_EX3->SetVisible(FALSE);
		m_pfSlotOpen = TRUE;
		m_paltSlotOpen = TRUE;
	}
	else
	{
		m_pAppletSlotOpen = TRUE;
		m_pfSlotOpen = TRUE;
		m_paltSlotOpen = TRUE;
	}
	for (int i = 0; i < 10; i++)
	{
		m_pSlotItem[i] = &g_WndMng.m_pWndTaskBar->m_aSlotItem[0][i];
		pWndTaskBar_HUD_EX1->m_pSlotItem[i] = &g_WndMng.m_pWndTaskBar->m_aSlotItem[1][i];
		pWndTaskBar_HUD_EX2->m_pSlotItem[i] = &g_WndMng.m_pWndTaskBar->m_aSlotItem[2][i];
		pWndTaskBar_HUD_EX3->m_pSlotItem[i] = &g_WndMng.m_pWndTaskBar->m_aSlotItem[3][i];
	}

	CWndButton* pWndButton = (CWndButton*)GetDlgItem(WIDC_BUTTON1);
	pWndButton->SetCheck(!CWndTaskBarInterface::IsLock());
	RestoreDeviceObjects();

	DelWndStyle(WBS_MOVE);
}

BOOL CWndTaskBar_HUD::Initialize(CWndBase* pWndParent, DWORD dwWndId)
{
	return CWndNeuz::InitDialog(g_Neuz.GetSafeHwnd(), APP_NEWTASKBAR, WBS_MANAGER | WBS_SOUND, CPoint(0, 0), pWndParent);
}

BOOL CWndTaskBar_HUD::Process()
{
	if (g_bKeyTable[VK_OEM_3])
	{
		g_bKeyTable[VK_OEM_3] = 0;
		ScrollTaskBars();
	}

	return CWndTaskBarInterface::Process();
}

void CWndTaskBar_HUD::MakeGaugeVertex()
{
	LPWNDCTRL lpHP = GetWndCtrl(WIDC_CUSTOM11);
	LPWNDCTRL lpMP = GetWndCtrl(WIDC_CUSTOM12);
	LPWNDCTRL lpFP = GetWndCtrl(WIDC_CUSTOM13);
	LPWNDCTRL lpExp = GetWndCtrl(WIDC_CUSTOM14);

	CMover* pMover = CMover::GetActiveMover();
	if (pMover)
	{
		CRect rect = GetClientRect();
		CRect rectTemp;

		int nWidthClient;
		int nWidth;

		{
			nWidthClient = lpHP->rect.Width();
			nWidth = (int)((__int64)nWidthClient * (__int64)pMover->GetHitPoint() / (__int64)pMover->GetMaxHitPoint());
			if (m_nHPWidth != nWidth)
			{
				m_nHPWidth = nWidth;
				rect = lpHP->rect;
				rectTemp = rect;
				rectTemp.right = rectTemp.left + nWidth;
				ClientToScreen(rectTemp);
				m_bVBHPGauge = m_pTheme->MakeGaugeVertex(m_pApp->m_pd3dDevice, &rectTemp, 0xffffffff, m_pVBHPGauge, &m_HPGaugeTexture);
			}
			nWidth = nWidthClient * pMover->GetManaPoint() / pMover->GetMaxManaPoint();
			if (m_nMPWidth != nWidth)
			{
				m_nMPWidth = nWidth;
				rect = lpMP->rect;
				rectTemp = rect;
				rectTemp.right = rectTemp.left + nWidth;
				ClientToScreen(rectTemp);
				m_bVBMPGauge = m_pTheme->MakeGaugeVertex(m_pApp->m_pd3dDevice, &rectTemp, 0xffffffff, m_pVBMPGauge, &m_MPGaugeTexture);
			}
			nWidth = nWidthClient * pMover->GetFatiguePoint() / pMover->GetMaxFatiguePoint();
			if (m_nFPWidth != nWidth)
			{
				m_nFPWidth = nWidth;
				rect = lpFP->rect;
				rectTemp = rect;
				rectTemp.right = rectTemp.left + nWidth;
				ClientToScreen(rectTemp);
				m_bVBFPGauge = m_pTheme->MakeGaugeVertex(m_pApp->m_pd3dDevice, &rectTemp, 0xffffffff, m_pVBFPGauge, &m_FPGaugeTexture);
			}
		}

		nWidthClient = lpExp->rect.Width();
		nWidth = (int)(((float)nWidthClient / pMover->GetMaxExp1()) * pMover->GetExp1());
		if (m_nEXPWidth != nWidth)
		{
			m_nEXPWidth = nWidth;
			rect = lpExp->rect;
			rectTemp = rect;
			rectTemp.right = rectTemp.left + nWidth;
			ClientToScreen(rectTemp);
			m_bVBEXPGauge = m_pTheme->MakeGaugeVertex(m_pApp->m_pd3dDevice, &rectTemp, 0xffffffff, m_pVBEXPGauge, &m_EXPGaugeTexture);
		}
	}
}

void CWndTaskBar_HUD::OnDraw(C2DRender* p2DRender)
{
	CWndTaskBarInterface::OnDraw(p2DRender);
	CMover* pMover = CMover::GetActiveMover();
	if (pMover == NULL)
		return;

	CRect rect = GetClientRect();
	int nWidthClient = GetClientRect().Width() - 110;

	CRect rectTemp;
	LPWNDCTRL lpHP = GetWndCtrl(WIDC_CUSTOM11);
	LPWNDCTRL lpMP = GetWndCtrl(WIDC_CUSTOM12);
	LPWNDCTRL lpFP = GetWndCtrl(WIDC_CUSTOM13);
	LPWNDCTRL lpExp = GetWndCtrl(WIDC_CUSTOM14);

	if (pMover)
	{
		MakeGaugeVertex();

		{
			if (m_bVBHPGauge)
				m_pTheme->RenderGauge(p2DRender->m_pd3dDevice, m_pVBHPGauge, &m_HPGaugeTexture);
			if (m_bVBMPGauge)
				m_pTheme->RenderGauge(p2DRender->m_pd3dDevice, m_pVBMPGauge, &m_MPGaugeTexture);
			if (m_bVBFPGauge)
				m_pTheme->RenderGauge(p2DRender->m_pd3dDevice, m_pVBFPGauge, &m_FPGaugeTexture);
		}

		if (m_bVBEXPGauge)
			m_pTheme->RenderGauge(p2DRender->m_pd3dDevice, m_pVBEXPGauge, &m_EXPGaugeTexture);
	}
	if (m_nDisplay != 0)
	{
		DWORD dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
		char cbufHp[16] = { 0, };
		char cbufMp[16] = { 0, };
		char cbufFp[16] = { 0, };
		char cbufExp[16] = { 0, };

		char cbufPxp[16] = { 0, };
		int nCharHP, nCharMP, nCharFP;
		CSize size = p2DRender->m_pFont->GetTextExtent("8");
		int nMaxHeight = p2DRender->m_pFont->GetMaxHeight();
		int nTopGap = 0;

		if (::GetLanguage() == LANG_FRE || ::GetLanguage() == LANG_GER)
		{
			nTopGap = 3;
		}
		else
		{
			if (nMaxHeight > 14)
				nTopGap = nMaxHeight - 14;
		}
		if (m_nDisplay != 1)
		{

			{
				CString szbufHp = Separator(pMover->GetHitPoint(), '.');
				CString szbufMp = Separator(pMover->GetManaPoint(), '.');
				CString szbufFp = Separator(pMover->GetFatiguePoint(), '.');

				if (pMover->GetHitPoint() >= 10000 && pMover->GetHitPoint() < 1000000)
					szbufHp.Format("%.1fk", float(pMover->GetHitPoint()) / 1000);
				else if (pMover->GetHitPoint() >= 1000000 && pMover->GetHitPoint() < 1000000000)
					szbufHp.Format("%.1fm", float(pMover->GetHitPoint()) / 1000000);
				else if (pMover->GetHitPoint() >= 1000000000)
					szbufHp.Format("%.1fb", float(pMover->GetHitPoint()) / 1000000000);

				if (pMover->GetManaPoint() >= 10000 && pMover->GetManaPoint() < 1000000)
					szbufMp.Format("%.1fk", float(pMover->GetManaPoint()) / 1000);
				else if (pMover->GetManaPoint() >= 1000000 && pMover->GetManaPoint() < 1000000000)
					szbufMp.Format("%.1fm", float(pMover->GetManaPoint()) / 1000000);
				else if (pMover->GetManaPoint() >= 1000000000)
					szbufMp.Format("%.1fb", float(pMover->GetManaPoint()) / 1000000000);

				if (pMover->GetFatiguePoint() >= 10000 && pMover->GetFatiguePoint() < 1000000)
					szbufFp.Format("%.1fk", float(pMover->GetFatiguePoint()) / 1000);
				else if (pMover->GetFatiguePoint() >= 1000000 && pMover->GetFatiguePoint() < 1000000000)
					szbufFp.Format("%.1fm", float(pMover->GetFatiguePoint()) / 1000000);
				else if (pMover->GetFatiguePoint() >= 1000000000)
					szbufFp.Format("%.1fb", float(pMover->GetFatiguePoint()) / 1000000000);

				nCharHP = wsprintf(cbufHp, "%s", szbufHp);
				nCharMP = wsprintf(cbufMp, "%s", szbufMp);
				nCharFP = wsprintf(cbufFp, "%s", szbufFp);

				int x = lpHP->rect.right - 82 - 10;
				p2DRender->TextOut(x - (int)(((float)nCharHP / 2.0f) * size.cx), lpHP->rect.top - nTopGap, cbufHp, dwColor, 0xff000000);
				p2DRender->TextOut(x - (int)(((float)nCharMP / 2.0f) * size.cx), lpMP->rect.top - nTopGap, cbufMp, dwColor, 0xff000000);
				p2DRender->TextOut(x - (int)(((float)nCharFP / 2.0f) * size.cx), lpFP->rect.top - nTopGap, cbufFp, dwColor, 0xff000000);

				szbufHp = Separator(pMover->GetMaxHitPoint(), '.');
				szbufMp = Separator(pMover->GetMaxManaPoint(), '.');
				szbufFp = Separator(pMover->GetMaxFatiguePoint(), '.');

				if (pMover->GetMaxHitPoint() >= 10000 && pMover->GetMaxHitPoint() < 1000000)
					szbufHp.Format("%.1fk", float(pMover->GetMaxHitPoint()) / 1000);
				else if (pMover->GetMaxHitPoint() >= 1000000 && pMover->GetMaxHitPoint() < 1000000000)
					szbufHp.Format("%.1fm", float(pMover->GetMaxHitPoint()) / 1000000);
				else if (pMover->GetMaxHitPoint() >= 1000000000)
					szbufHp.Format("%.1fb", float(pMover->GetMaxHitPoint()) / 1000000000);

				if (pMover->GetMaxManaPoint() >= 10000 && pMover->GetMaxManaPoint() < 1000000)
					szbufMp.Format("%.1fk", float(pMover->GetMaxManaPoint()) / 1000);
				else if (pMover->GetMaxManaPoint() >= 1000000 && pMover->GetMaxManaPoint() < 1000000000)
					szbufMp.Format("%.1fm", float(pMover->GetMaxManaPoint()) / 1000000);
				else if (pMover->GetMaxManaPoint() >= 1000000000)
					szbufMp.Format("%.1fb", float(pMover->GetMaxManaPoint()) / 1000000000);

				if (pMover->GetMaxFatiguePoint() >= 10000 && pMover->GetMaxFatiguePoint() < 1000000)
					szbufFp.Format("%.1fk", float(pMover->GetMaxFatiguePoint()) / 1000);
				else if (pMover->GetMaxFatiguePoint() >= 1000000 && pMover->GetMaxFatiguePoint() < 1000000000)
					szbufFp.Format("%.1fm", float(pMover->GetMaxFatiguePoint()) / 1000000);
				else if (pMover->GetMaxFatiguePoint() >= 1000000000)
					szbufFp.Format("%.1fb", float(pMover->GetMaxFatiguePoint()) / 1000000000);

				nCharHP = wsprintf(cbufHp, "%s", szbufHp);
				nCharMP = wsprintf(cbufMp, "%s", szbufMp);
				nCharFP = wsprintf(cbufFp, "%s", szbufFp);

				x = lpHP->rect.right - 30 - 10;//30
				p2DRender->TextOut(x - (int)(((float)nCharHP / 2.0f) * size.cx), lpHP->rect.top - nTopGap, cbufHp, dwColor, 0xff000000);
				p2DRender->TextOut(x - (int)(((float)nCharMP / 2.0f) * size.cx), lpMP->rect.top - nTopGap, cbufMp, dwColor, 0xff000000);
				p2DRender->TextOut(x - (int)(((float)nCharFP / 2.0f) * size.cx), lpFP->rect.top - nTopGap, cbufFp, dwColor, 0xff000000);

				LPWNDCTRL lpHP = GetWndCtrl(WIDC_CUSTOM1);
				int nWidthCustom = lpHP->rect.Width();
				int nGap = lpHP->rect.left + 25 + 10;

				p2DRender->TextOut(lpMP->rect.right - nGap, lpHP->rect.top - (nTopGap + 2), "/", dwColor, 0xff000000);
				p2DRender->TextOut(lpMP->rect.right - nGap, lpMP->rect.top - nTopGap, "/", dwColor, 0xff000000);
				p2DRender->TextOut(lpFP->rect.right - nGap, lpFP->rect.top - nTopGap, "/", dwColor, 0xff000000);
			}
		}

		CRect therect = lpExp->rect;
		if (therect.PtInRect(GetMousePoint()))
		{
			CPoint point = GetMousePoint();;
			ClientToScreen(&point);
			ClientToScreen(&therect);

			CString strEdit;

			EXPINTEGER	nExpResult = pMover->GetExp1() * (EXPINTEGER)10000 / pMover->GetMaxExp1();
			float fExp = (float)nExpResult / 100.0f;

			if (fExp >= 99.99f)
				fExp = 99.99f;
			if (fExp < 0.0f)
				fExp = 0.0f;

			strEdit.Format(prj.GetText(TID_MMI_UIEXPTOOLTIP), pMover->GetExp1(), pMover->GetMaxExp1(), fExp);
			g_toolTip.PutToolTip(10000, strEdit, therect, point, 0);
		}

		int x = lpHP->rect.right - 10; // -40
	}
	CTexture* mainbar_EXP;
	mainbar_EXP = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "WndMainBar.tga"), 0xffff00ff, TRUE);
	if (mainbar_EXP != NULL)
	{
		CPoint point;

		point.y = 78;
		point.x = 30;

		mainbar_EXP->Render(&g_Neuz.m_2DRender, point);
	}
	for (int i = 0; i < 10; i++)
	{
		CString szTemp;
		CPoint point = CPoint(wndCtrl[i]->rect.left, wndCtrl[i]->rect.top);
		switch (i)
		{
		case 0:  szTemp = "1"; break;
		case 1:  szTemp = "2"; break;
		case 2:  szTemp = "3"; break;
		case 3:  szTemp = "4"; break;
		case 4:  szTemp = "5"; break;
		case 5:  szTemp = "6"; break;
		case 6:  szTemp = "7"; break;
		case 7:  szTemp = "8"; break;
		case 8:  szTemp = "9"; break;
		case 9:  szTemp = "0"; break;
		}

		point.x += 8;
		CD3DFont* pOldFont = p2DRender->GetFont();
		p2DRender->SetFont(CWndBase::m_Theme.m_pFontWndTitle);
		p2DRender->TextOut((1 + (point.x / point.x + point.x)), point.y - 12, szTemp);
		p2DRender->SetFont(pOldFont);
	}
}

HRESULT CWndTaskBar_HUD::RestoreDeviceObjects()
{
	CWndBase::RestoreDeviceObjects();
	if (m_pVBHPGauge == NULL)
	{
		m_pApp->m_pd3dDevice->CreateVertexBuffer(sizeof(TEXTUREVERTEX2) * 3 * 6, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, D3DFVF_TEXTUREVERTEX2, D3DPOOL_DEFAULT, &m_pVBHPGauge, NULL);
		m_pApp->m_pd3dDevice->CreateVertexBuffer(sizeof(TEXTUREVERTEX2) * 3 * 6, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, D3DFVF_TEXTUREVERTEX2, D3DPOOL_DEFAULT, &m_pVBMPGauge, NULL);
		m_pApp->m_pd3dDevice->CreateVertexBuffer(sizeof(TEXTUREVERTEX2) * 3 * 6, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, D3DFVF_TEXTUREVERTEX2, D3DPOOL_DEFAULT, &m_pVBFPGauge, NULL);
		m_pApp->m_pd3dDevice->CreateVertexBuffer(sizeof(TEXTUREVERTEX2) * 3 * 6, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, D3DFVF_TEXTUREVERTEX2, D3DPOOL_DEFAULT, &m_pVBEXPGauge, NULL);

		m_nHPWidth = -1;
		m_nMPWidth = -1;
		m_nFPWidth = -1;
		m_nEXPWidth = -1;
	}
	m_HPGaugeTexture.SetInvalidate(m_pApp->m_pd3dDevice);
	m_MPGaugeTexture.SetInvalidate(m_pApp->m_pd3dDevice);
	m_FPGaugeTexture.SetInvalidate(m_pApp->m_pd3dDevice);
	m_EXPGaugeTexture.SetInvalidate(m_pApp->m_pd3dDevice);

	return S_OK;
}

HRESULT CWndTaskBar_HUD::InvalidateDeviceObjects()
{
	CWndBase::InvalidateDeviceObjects();
	SAFE_RELEASE(m_pVBHPGauge);
	SAFE_RELEASE(m_pVBMPGauge);
	SAFE_RELEASE(m_pVBFPGauge);
	SAFE_RELEASE(m_pVBEXPGauge);

	m_HPGaugeTexture.Invalidate();
	m_MPGaugeTexture.Invalidate();
	m_FPGaugeTexture.Invalidate();
	m_EXPGaugeTexture.Invalidate();

	return S_OK;
}

HRESULT CWndTaskBar_HUD::DeleteDeviceObjects()
{
	CWndBase::DeleteDeviceObjects();
	return InvalidateDeviceObjects();
}

void CWndTaskBar_HUD::SetWndRect(CRect rectWnd, BOOL bOnSize)
{
	m_nHPWidth = -1;
	m_nMPWidth = -1;
	m_nFPWidth = -1;
	m_nEXPWidth = -1;
	CWndNeuz::SetWndRect(rectWnd, bOnSize);
}

BOOL CWndTaskBar_HUD::OnChildNotify(UINT message, UINT nID, LRESULT* pLResult)
{
	switch (nID)
	{
	case WIDC_BUTTON1:
	{
		CWndButton* pWndButton = (CWndButton*)GetDlgItem(WIDC_BUTTON1);
		CWndTaskBarInterface::Lock();
		pWndButton->SetCheck(!CWndTaskBarInterface::IsLock());
		break;
	}
	case WIDC_BUTTON2:
	{
		if (!CWndTaskBarInterface::IsLock())
		{
			if (m_paltSlotOpen == FALSE)
			{
				pWndTaskBar_HUD_EX1->SetVisible(TRUE);
				m_paltSlotOpen = TRUE;
				g_Option.m_nTBDisplay = 1;
				break;
			}
			if (m_pfSlotOpen == FALSE)
			{
				pWndTaskBar_HUD_EX2->SetVisible(TRUE);
				m_pfSlotOpen = TRUE;
				g_Option.m_nTBDisplay = 2;
				break;
			}
			if (m_pAppletSlotOpen == FALSE)
			{
				pWndTaskBar_HUD_EX3->SetVisible(TRUE);
				m_pAppletSlotOpen = TRUE;
				g_Option.m_nTBDisplay = 3;
				break;
			}
		}
		break;
	}
	case WIDC_BUTTON3:
	{
		if (!CWndTaskBarInterface::IsLock())
		{
			if (pWndTaskBar_HUD_EX3->IsVisible())
			{
				pWndTaskBar_HUD_EX3->SetVisible(FALSE);
				m_pAppletSlotOpen = FALSE;
				g_Option.m_nTBDisplay = 2;
				break;
			}
			else if (pWndTaskBar_HUD_EX2->IsVisible())
			{
				pWndTaskBar_HUD_EX2->SetVisible(FALSE);
				m_pfSlotOpen = FALSE;
				g_Option.m_nTBDisplay = 1;
				break;
			}
			else if (pWndTaskBar_HUD_EX1->IsVisible())
			{
				pWndTaskBar_HUD_EX1->SetVisible(FALSE);
				m_paltSlotOpen = FALSE;
				g_Option.m_nTBDisplay = 0;
				break;
			}
		}
		break;
	}
	case WIDC_BUTTON4:
	{
		if (!CWndTaskBarInterface::IsLock())
			ScrollTaskBars();
		break;
	}
	}

	return TRUE;
}

void CWndTaskBar_HUD::ScrollTaskBars()
{
	for (int i = 0; i < 10; ++i)
	{
		SHORTCUT scTemp = *m_pSlotItem[i];
		*m_pSlotItem[i] = *pWndTaskBar_HUD_EX1->m_pSlotItem[i];
		*pWndTaskBar_HUD_EX1->m_pSlotItem[i] = *pWndTaskBar_HUD_EX2->m_pSlotItem[i];
		*pWndTaskBar_HUD_EX2->m_pSlotItem[i] = scTemp;
	}

	g_DPlay.SendScrollTaskBar();
}

void CWndTaskBar_HUD::OnMouseWndSurface(CPoint point)
{
	CWndTaskBarInterface::OnMouseWndSurface(point);
}

BOOL CWndTaskBar_HUD_EX3::Initialize(CWndBase* pWndParent, DWORD dwType)
{
	return CWndNeuz::InitDialog(g_Neuz.GetSafeHwnd(), APP_NEWTASKBAR04, WBS_MANAGER | WBS_SOUND, CPoint(0, 0), pWndParent);
}

void CWndTaskBar_HUD_EX3::OnInitialUpdate(void)
{
	CWndTaskBarInterface::OnInitialUpdate();

	m_nSlotIndex = 3;
	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rectWindow = GetWindowRect();
	CRect rect = g_Neuz.GetDeviceRect();
	CPoint point(rectRoot.right - rectWindow.Width(), (rect.Height() - rectWindow.Height()) / 2);
	Move(point);

	CWndStatic* pStatic = (CWndStatic*)GetDlgItem(WIDC_STATIC1);
	CWndStatic* pStatic2 = (CWndStatic*)GetDlgItem(WIDC_STATIC2);
	pStatic->Move(rectWindow.right + 40, rectWindow.bottom + 40);
	pStatic2->Move(rectWindow.right + 40, rectWindow.bottom + 40);
	DelWndStyle(WBS_MOVE);
	RestoreDeviceObjects();
}

BOOL CWndTaskBar_HUD_EX1::Initialize(CWndBase* pWndParent, DWORD dwType)
{
	return CWndNeuz::InitDialog(g_Neuz.GetSafeHwnd(), APP_NEWTASKBAR03, WBS_MANAGER | WBS_SOUND, CPoint(0, 0), pWndParent);
}

void CWndTaskBar_HUD_EX1::OnDraw(C2DRender* p2DRender)
{
	if (IsValidObj(g_pPlayer))
	{
		CWndTaskBarInterface::OnDraw(p2DRender);
		for (int i = 0; i < 10; i++)
		{
			CString szTemp;
			CPoint point = CPoint(wndCtrl[i]->rect.left, wndCtrl[i]->rect.top);
			switch (i)
			{
			case 0: { szTemp = "A1"; break; }
			case 1: { szTemp = "A2"; break; }
			case 2: { szTemp = "A3"; break; }
			case 3: { szTemp = "A4"; break; }
			case 4: { szTemp = "A5"; break; }
			case 5: { szTemp = "A6"; break; }
			case 6: { szTemp = "A7"; break; }
			case 7: { szTemp = "A8"; break; }
			case 8: { szTemp = "A9"; break; }
			case 9: { szTemp = "A0"; break; }
			}
			point.x += 4;
			CD3DFont* pOldFont = p2DRender->GetFont();
			p2DRender->SetFont(CWndBase::m_Theme.m_pFontWndTitle);
			p2DRender->TextOut((1 + (point.x / point.x + point.x)), point.y - 8, szTemp);
			p2DRender->SetFont(pOldFont);
		}
	}
}

void CWndTaskBar_HUD_EX1::OnInitialUpdate(void)
{
	CWndTaskBarInterface::OnInitialUpdate();
	m_nActionListener[0] = '1';
	m_nActionListener[1] = '2';
	m_nActionListener[2] = '3';
	m_nActionListener[3] = '4';
	m_nActionListener[4] = '5';
	m_nActionListener[5] = '6';
	m_nActionListener[6] = '7';
	m_nActionListener[7] = '8';
	m_nActionListener[8] = '9';
	m_nActionListener[9] = '0';
	m_bReqAlt = true;
	m_nSlotIndex = 1;

	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rectWindow = GetWindowRect();
	CRect rect = g_Neuz.GetDeviceRect();

	CPoint point(rectRoot.right - rectWindow.Width() - 185, rect.Height() - rectWindow.Height() - 70);
	Move(point);

	CWndStatic* pStatic = (CWndStatic*)GetDlgItem(WIDC_STATIC1);
	CWndStatic* pStatic2 = (CWndStatic*)GetDlgItem(WIDC_STATIC2);
	pStatic->Move(rectWindow.right + 40, rectWindow.bottom + 40);
	pStatic2->Move(rectWindow.right + 40, rectWindow.bottom + 40);

	RestoreDeviceObjects();
	DelWndStyle(WBS_MOVE);
}

BOOL CWndTaskBar_HUD_EX2::Initialize(CWndBase* pWndParent, DWORD dwType)
{
	return CWndNeuz::InitDialog(g_Neuz.GetSafeHwnd(), APP_NEWTASKBAR03, WBS_MANAGER | WBS_SOUND, CPoint(0, 0), pWndParent);
}

void CWndTaskBar_HUD_EX2::OnDraw(C2DRender* p2DRender)
{
	CWndTaskBarInterface::OnDraw(p2DRender);
	for (int i = 0; i < 10; i++)
	{
		CString szTemp;
		CPoint point = CPoint(wndCtrl[i]->rect.left, wndCtrl[i]->rect.top);
		switch (i)
		{
		case 0: { szTemp = "F1"; break; }
		case 1: { szTemp = "F2"; break; }
		case 2: { szTemp = "F3"; break; }
		case 3: { szTemp = "F4"; break; }
		case 4: { szTemp = "F5"; break; }
		case 5: { szTemp = "F6"; break; }
		case 6: { szTemp = "F7"; break; }
		case 7: { szTemp = "F8"; break; }
		case 8: { szTemp = "F9"; break; }
		case 9: { szTemp = "F10"; break; }
		}
		point.x += 2;
		CD3DFont* pOldFont = p2DRender->GetFont();
		p2DRender->SetFont(CWndBase::m_Theme.m_pFontWndTitle);
		p2DRender->TextOut((1 + (point.x / point.x + point.x)), point.y - 8, szTemp);
		p2DRender->SetFont(pOldFont);
	}
}

void CWndTaskBar_HUD_EX2::OnInitialUpdate(void)
{
	CWndTaskBarInterface::OnInitialUpdate();
	m_nActionListener[0] = VK_F1;
	m_nActionListener[1] = VK_F2;
	m_nActionListener[2] = VK_F3;
	m_nActionListener[3] = VK_F4;
	m_nActionListener[4] = VK_F5;
	m_nActionListener[5] = VK_F6;
	m_nActionListener[6] = VK_F7;
	m_nActionListener[7] = VK_F8;
	m_nActionListener[8] = VK_F9;
	m_nActionListener[9] = VK_F10;
	m_nSlotIndex = 2;

	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rectWindow = GetWindowRect();
	CRect rect = g_Neuz.GetDeviceRect();

	CPoint point(rectRoot.right - rectWindow.Width() - 185, rect.Height() - rectWindow.Height() - 115);
	Move(point);

	CWndStatic* pStatic = (CWndStatic*)GetDlgItem(WIDC_STATIC1);
	CWndStatic* pStatic2 = (CWndStatic*)GetDlgItem(WIDC_STATIC2);
	pStatic->Move(rectWindow.right + 40, rectWindow.bottom + 40);
	pStatic2->Move(rectWindow.right + 40, rectWindow.bottom + 40);

	DelWndStyle(WBS_MOVE);
	RestoreDeviceObjects();
}

class CTimers
{
public:
	CTimers(void)
	{
		dwStop = 0;
	}
	~CTimers(void)
	{
	}
	void Start(float fSec)
	{
		dwStop = (DWORD)(fSec * 1) + timeGetTime();
	}
	void Stop(void)
	{
		dwStop = 0;
	}
	float TimeLeft(void)
	{
		if (Running())
			return (((float)(dwStop - timeGetTime()) / 1));

		return 0;
	}
	bool Running(void)
	{
		return (dwStop > timeGetTime());
	}

protected:
	DWORD dwStop;
};

CTimers RotateTimer;

CWndNewSkillSlot::CWndNewSkillSlot(void)
{
	rotates = 0;
	RotateAllEffect = 1;
	RotateSkillEffect = 1;

	Time = 0;

	m_RotateAtiv = FALSE;
	m_SFire0 = NULL;
	m_SFire1 = NULL;
	m_SFire2 = NULL;
	m_SFire3 = NULL;
	m_SFire4 = NULL;
	m_SFire5 = NULL;
	m_SFireALPHA0 = 0;

	m_DROPFireALPHA = 0;
	m_bFireFLASH = TRUE;

	m_USEFireALPHA = 115;

	m_pSelectShortcut = NULL;
	m_aSlotSkill.Empty();

	memset(m_pSlotQueue, 0, sizeof(m_pSlotQueue));
	for (int i = 0; i < 6; i++)
	{
		m_SlotEffectSoltaAL = 0;
		slot1[i] = NULL;
		slot12[i] = NULL;
		m_bFlash = TRUE;
		m_SURF_FIRE[i] = NULL;

		m_nFlashAlpha[i] = 0;
		m_SURF_FireALPHA[i] = 0;
		m_bSURF_FireFLASH = TRUE;
		bRenderIllu[i] = false;
	}

	m_nActionSlot = 0;
	EffectRotate = 0;
	m_pTexture = NULL;
	rotate = 0;
	rotate1 = 0.0f;
	rotate2 = 0.0f;
	rotate3 = 5.0f;
	rot1 = TRUE;
	rot3 = FALSE;
	reload = FALSE;
	xPos = 0.0f;
	zPos = -5.0f;

	xPosition[0] = 0;
	yPosition[0] = 50.5f;
	xPosition[1] = 44;
	yPosition[1] = 24.5f;
	xPosition[2] = 44;
	yPosition[2] = -25.5f;
	xPosition[3] = 0;
	yPosition[3] = -50.5f;
	xPosition[4] = -44;
	yPosition[4] = -25.5f;
	xPosition[5] = -44;
	yPosition[5] = 24.5f;

	usedskill1 = usedskill2 = usedskill3 = usedskill4 = usedskill5 = FALSE;
	fusedskill1 = fusedskill2 = fusedskill3 = fusedskill4 = fusedskill5 = FALSE;
	useskill = FALSE;

	RotateSLOT = false;
	m_tmStartCoolDown = clock();
	m_tmCoolDown = clock();
	m_bStopCoolDown = false;
	RotateCoolDownEffect = 721;
	m_bArrival = false;
}

CWndNewSkillSlot::~CWndNewSkillSlot(void)
{
	for (int i = 0; i < 6; i++)
	{
		slot1[i] = NULL;
		slot12[i] = NULL;
		m_SURF_FIRE[i] = NULL;
	}

	CWndBase::m_textureMng.RemoveTexture(MakePath(DIR_THEME, "slot02.tga"));
	CWndBase::m_textureMng.RemoveTexture(MakePath(DIR_THEME, "slot03.tga"));

	m_SFire0 = NULL;
	m_SFire1 = NULL;
	m_SFire2 = NULL;
	m_SFire3 = NULL;
	m_SFire4 = NULL;
	m_SFire5 = NULL;
	m_pTexture = NULL;

	CWndBase::DeleteDeviceObjects();
}

BOOL CWndNewSkillSlot::Initialize(CWndBase* pWndParent, DWORD dwType)
{
	return CWndNeuz::InitDialog(g_Neuz.GetSafeHwnd(), APP_SLOT, WBS_MANAGER | WBS_SOUND, CPoint(0, 0), pWndParent);
}

BOOL CWndNewSkillSlot::OnCommand(UINT nID, DWORD dwMessage, CWndBase* pWndBase)
{
	return CWndNeuz::OnCommand(nID, dwMessage, pWndBase);
}

void CWndNewSkillSlot::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWndNeuz::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CWndNewSkillSlot::OnSize(UINT nType, int cx, int cy)
{
	CWndNeuz::OnSize(nType, cx, cy);
}

void CWndNewSkillSlot::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_pSelectShortcut != NULL)
	{
		if (m_pSelectShortcut->m_dwShortcut == SHORTCUT_SKILL)
		{
			g_WndMng.m_pWndTaskBar->RemoveSkillQueue(m_pSlotQueue[m_pSelectShortcut->m_dwIndex]->m_dwIndex);
			m_pSelectShortcut = m_pSlotQueue[0];
		}
	}

	ReleaseCapture();
}

void CWndNewSkillSlot::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWndNewSkillSlot* m_SkillSL = (CWndNewSkillSlot*)g_WndMng.GetWndBase(APP_SLOT);
	LPSHORTCUT pShortcut = NULL;
	CWorld* pWorld = g_WorldMng.Get();
	if (PtInRect(SlotCustom->rect, point))
	{
		if (clock() < m_SkillSL->m_tmCoolDown || m_SkillSL->m_bStopCoolDown)
		{
			return;
		}
		if (g_WndMng.m_pWndTaskBar->m_nExecute == 0)
		{
			if ((g_WndMng.m_pWndTaskBar->m_nUsedSkillQueue == 0) && (m_SkillSL->m_nActionSlot > 0))
			{
				g_WndMng.m_pWndWorld->m_dwNextSkill = NEXTSKILL_ACTIONSLOT;
			}
		}
	}

	ReleaseCapture();
}

void CWndNewSkillSlot::OnLButtonDblClk(UINT nFlags, CPoint point)
{
}

void CWndNewSkillSlot::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	CPoint PTM = CPoint(SlotRt->m_ptCenter.x - 36, SlotRt->m_ptCenter.y);
	CTRECT[0] = CRect(PTM.x + 97, PTM.y + 116, PTM.x + 97 + 34, PTM.y + 116 + 34);
	CTRECT[1] = CRect(PTM.x + 141, PTM.y + 90, PTM.x + 141 + 34, PTM.y + 90 + 34);
	CTRECT[2] = CRect(PTM.x + 141, PTM.y + 40, PTM.x + 141 + 34, PTM.y + 40 + 34);
	CTRECT[3] = CRect(PTM.x + 97, PTM.y + 15, PTM.x + 97 + 34, PTM.y + 15 + 34);
	CTRECT[4] = CRect(PTM.x + 53, PTM.y + 40, PTM.x + 53 + 34, PTM.y + 40 + 34);
	CTRECT[5] = CRect(PTM.x + 53, PTM.y + 90, PTM.x + 53 + 34, PTM.y + 90 + 34);

	if (m_bLButtonDown && IsPush())
	{
		for (int i = 0; i < MAX_SLOT_QUEUE; i++)
		{
			if (CTRECT[i].PtInRect(GetMousePoint()))
			{
				g_WndMng.m_pWndTaskBar->RemoveSkillQueue(m_pSlotQueue[i]->m_dwIndex);
			}
		}
	}
}

BOOL CWndNewSkillSlot::Process(void)
{
	if ((m_pSlotQueue[0]->m_dwShortcut != SHORTCUT_NONE) && (m_pSlotQueue[0]->m_pTexture != NULL))
	{
		m_nActionSlot = 1;
	}
	else
	{
		m_nActionSlot = NULL;
	}

	m_DROPFireALPHA -= 5;

	if (m_DROPFireALPHA < 5)
	{
		m_DROPFireALPHA = 0;
	}

	if (RotateSLOT == rotate1 && m_USEFireALPHA != 115 && g_WndMng.m_pWndTaskBar->m_nExecute > 0 && useskill)
	{
		m_USEFireALPHA += 3;
		if (m_USEFireALPHA >= 200)
		{
			int nPos = (int)RotateSLOT / 60;
			bRenderIllu[nPos] = true;
		}
		if (m_USEFireALPHA >= 255)
		{
			m_USEFireALPHA = 115;
		}
	}

	if (m_bFireFLASH == TRUE)
	{
		m_SFireALPHA0 += 4;

		if ((m_SFireALPHA0 > 80))
		{
			m_SFireALPHA0 = 80;
			m_bFireFLASH = FALSE;
		}
	}
	else
	{
		m_SFireALPHA0 -= 4;

		if ((m_SFireALPHA0 < 10))
		{
			m_SFireALPHA0 = 10;
			m_bFireFLASH = TRUE;
		}
	}

	for (int i = 0; i < 6; i++)
	{
		if (m_bFlash == TRUE)
		{
			m_nFlashAlpha[i] += 8;
			if ((m_nFlashAlpha[i] > 250))
			{
				m_nFlashAlpha[i] = 250;
				m_bFlash = FALSE;
			}
		}
		else
		{
			m_nFlashAlpha[i] -= 8;
			if ((m_nFlashAlpha[i] < 80))
			{
				m_nFlashAlpha[i] = 80;
				m_bFlash = TRUE;
			}
		}
	}

	CPoint PTM = CPoint(SlotRt->m_ptCenter.x - 36, SlotRt->m_ptCenter.y);
	CTRECT[0] = CRect(PTM.x + 97, PTM.y + 116, PTM.x + 97 + 34, PTM.y + 116 + 34);
	CTRECT[1] = CRect(PTM.x + 141, PTM.y + 90, PTM.x + 141 + 34, PTM.y + 90 + 34);
	CTRECT[2] = CRect(PTM.x + 141, PTM.y + 40, PTM.x + 141 + 34, PTM.y + 40 + 34);
	CTRECT[3] = CRect(PTM.x + 97, PTM.y + 15, PTM.x + 97 + 34, PTM.y + 15 + 34);
	CTRECT[4] = CRect(PTM.x + 53, PTM.y + 40, PTM.x + 53 + 34, PTM.y + 40 + 34);
	CTRECT[5] = CRect(PTM.x + 53, PTM.y + 90, PTM.x + 53 + 34, PTM.y + 90 + 34);

	for (int i = 0; i < MAX_SLOT_QUEUE; i++)
	{
		BOOL bInRect = CTRECT[i].PtInRect(GetMousePoint());
		if (!bInRect)
		{
			m_SURF_FIRE[i] = NULL;
		}
		else
		{
			if (m_SURF_FIRE[i] != NULL)
			{
				if (m_bSURF_FireFLASH == TRUE)
				{
					m_SURF_FireALPHA[i] += 10;
					if ((m_SURF_FireALPHA[i] > 250))
					{
						m_SURF_FireALPHA[i] = 250;
						PLAYSND(SND_PC_ACTIONSLOTMOVE01);
						m_bSURF_FireFLASH = FALSE;
					}
				}
				else
				{
					m_SURF_FireALPHA[i] -= 10;
					if ((m_SURF_FireALPHA[i] < 50))
					{
						m_SURF_FireALPHA[i] = 50;
						m_bSURF_FireFLASH = TRUE;
					}
				}
			}
		}
	}

	return CWndBase::Process();
}

void CWndNewSkillSlot::OnRButtonDown(UINT nFlags, CPoint point)
{
	LPSHORTCUT pShortcut = NULL;
	CPoint PTM = CPoint(SlotRt->m_ptCenter.x - 36, SlotRt->m_ptCenter.y);
	CTRECT[0] = CRect(PTM.x + 97, PTM.y + 116, PTM.x + 97 + 34, PTM.y + 116 + 34);
	CTRECT[1] = CRect(PTM.x + 141, PTM.y + 90, PTM.x + 141 + 34, PTM.y + 90 + 34);
	CTRECT[2] = CRect(PTM.x + 141, PTM.y + 40, PTM.x + 141 + 34, PTM.y + 40 + 34);
	CTRECT[3] = CRect(PTM.x + 97, PTM.y + 15, PTM.x + 97 + 34, PTM.y + 15 + 34);
	CTRECT[4] = CRect(PTM.x + 53, PTM.y + 40, PTM.x + 53 + 34, PTM.y + 40 + 34);
	CTRECT[5] = CRect(PTM.x + 53, PTM.y + 90, PTM.x + 53 + 34, PTM.y + 90 + 34);

	for (int i = 0; i < 6; i++)
	{
		if (SlotCustom->rect.PtInRect(point))
		{
			&CWndBase::OnRButtonDown;
		}
		if (PtInRect(CTRECT[i], point))
		{
			CRect rect = CTRECT[i];
			ClientToScreen(&point);
			ClientToScreen(&rect);
			m_pSelectShortcut = m_pSlotQueue[i];

			SetCapture();
		}
	}
}

void CWndNewSkillSlot::OnLButtonDown(UINT nFlags, CPoint point)
{
	LPSHORTCUT pShortcut = NULL;
	CPoint PTM = CPoint(SlotRt->m_ptCenter.x - 36, SlotRt->m_ptCenter.y);
	CTRECT[0] = CRect(PTM.x + 97, PTM.y + 116, PTM.x + 97 + 34, PTM.y + 116 + 34);
	CTRECT[1] = CRect(PTM.x + 141, PTM.y + 90, PTM.x + 141 + 34, PTM.y + 90 + 34);
	CTRECT[2] = CRect(PTM.x + 141, PTM.y + 40, PTM.x + 141 + 34, PTM.y + 40 + 34);
	CTRECT[3] = CRect(PTM.x + 97, PTM.y + 15, PTM.x + 97 + 34, PTM.y + 15 + 34);
	CTRECT[4] = CRect(PTM.x + 53, PTM.y + 40, PTM.x + 53 + 34, PTM.y + 40 + 34);
	CTRECT[5] = CRect(PTM.x + 53, PTM.y + 90, PTM.x + 53 + 34, PTM.y + 90 + 34);

	for (int i = 0; i < MAX_SLOT_QUEUE; i++)
	{
		if (PtInRect(CTRECT[i], point))
		{
			CRect rect = CTRECT[i];
			ClientToScreen(&point);
			ClientToScreen(&rect);

			m_pSelectShortcut = m_pSlotQueue[i];
			SetCapture();
		}
	}
	if (SlotCustom->rect.PtInRect(point))
	{
		m_aSlotSkill.m_dwShortcut = SHORTCUT_SKILLFUN;
		m_pSelectShortcut = &m_aSlotSkill;
	}
}

void CWndNewSkillSlot::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint PTM = CPoint(SlotRt->m_ptCenter.x - 36, SlotRt->m_ptCenter.y);
	CTRECT[0] = CRect(PTM.x + 97, PTM.y + 116, PTM.x + 97 + 34, PTM.y + 116 + 34);
	CTRECT[1] = CRect(PTM.x + 141, PTM.y + 90, PTM.x + 141 + 34, PTM.y + 90 + 34);
	CTRECT[2] = CRect(PTM.x + 141, PTM.y + 40, PTM.x + 141 + 34, PTM.y + 40 + 34);
	CTRECT[3] = CRect(PTM.x + 97, PTM.y + 15, PTM.x + 97 + 34, PTM.y + 15 + 34);
	CTRECT[4] = CRect(PTM.x + 53, PTM.y + 40, PTM.x + 53 + 34, PTM.y + 40 + 34);
	CTRECT[5] = CRect(PTM.x + 53, PTM.y + 90, PTM.x + 53 + 34, PTM.y + 90 + 34);

	if (m_bLButtonDown && IsPush())
	{
		for (int i = 0; i < MAX_SLOT_QUEUE; i++)
		{
			if (CTRECT[i].PtInRect(GetMousePoint()))
			{
				if (m_pSelectShortcut)
				{
					memcpy(&m_GlobalShortcut, m_pSelectShortcut, sizeof(m_GlobalShortcut));
					m_GlobalShortcut.m_pFromWnd = this;
					m_GlobalShortcut.m_dwData = (DWORD)m_pSelectShortcut;
					m_pSelectShortcut = NULL;
				}
			}
		}
	}

	CWndNeuz::OnMouseMove(nFlags, point);
}

BOOL CWndNewSkillSlot::OnDropIcon(LPSHORTCUT pShortcut, CPoint point)
{
	CPoint point2;
	CPoint PTM = CPoint(SlotRt->m_ptCenter.x - 36, SlotRt->m_ptCenter.y);
	CTRECT[0] = CRect(PTM.x + 97, PTM.y + 116, PTM.x + 97 + 34, PTM.y + 116 + 36);
	CTRECT[1] = CRect(PTM.x + 141, PTM.y + 90, PTM.x + 141 + 34, PTM.y + 90 + 36);
	CTRECT[2] = CRect(PTM.x + 141, PTM.y + 40, PTM.x + 141 + 34, PTM.y + 40 + 36);
	CTRECT[3] = CRect(PTM.x + 97, PTM.y + 15, PTM.x + 97 + 34, PTM.y + 15 + 36);
	CTRECT[4] = CRect(PTM.x + 53, PTM.y + 40, PTM.x + 53 + 34, PTM.y + 40 + 36);
	CTRECT[5] = CRect(PTM.x + 53, PTM.y + 90, PTM.x + 53 + 34, PTM.y + 90 + 36);

	if (pShortcut->m_dwShortcut != SHORTCUT_SKILL && pShortcut->m_dwShortcut != SHORTCUT_LORDSKILL)
	{
		return FALSE;
	}
	CRect rect = GetWindowRect();
	rect.DeflateRect(3, 3);

	if ((pShortcut->m_pFromWnd == this) && (pShortcut->m_dwShortcut != SHORTCUT_SKILLFUN))
	{
		LPSHORTCUT lpShortcut = (LPSHORTCUT)pShortcut->m_dwData;
		if (GetClientRect().PtInRect(point) == FALSE)
		{
			g_WndMng.m_pWndTaskBar->RemoveSkillQueue(lpShortcut->m_dwIndex);
			return TRUE;
		}
	}
	CWndBase* pWndFrame = pShortcut->m_pFromWnd->GetFrameWnd();

	if (pWndFrame && (pWndFrame->GetWndId() != APP_INVENTORY
		&& pWndFrame != g_WndMng.m_pWndTaskBar && pWndFrame->GetWndId() != APP_COMMUNICATION_CHAT
		&& pWndFrame->GetWndId() != APP_SKILL4 && pWndFrame->GetWndId() != APP_MOTION && pWndFrame->GetWndId() != APP_PARTY
		&& pWndFrame->GetWndId() != APP_LORD_SKILL && pWndFrame->GetWndId() != APP_NEWTASKBAR
		&& pWndFrame->GetWndId() != APP_NEWTASKBAR02 && pWndFrame->GetWndId() != APP_NEWTASKBAR03
		&& pWndFrame->GetWndId() != APP_NEWTASKBAR04 && pWndFrame->GetWndId() != APP_SLOT))
	{
		SetForbid(TRUE);
		return FALSE;
	}

	for (int i = 0; i < 6; i++)
	{
		PLAYSND(SND_PC_ACTIONREGISTER);
		if (PtInRect(CTRECT[i], point))
		{
			CRect rect = CTRECT[i];
			ClientToScreen(&point);
			ClientToScreen(&rect);

			if (m_pSlotQueue[0]->m_dwShortcut == SHORTCUT_NONE)
				i = 0;
			else if (m_pSlotQueue[1]->m_dwShortcut == SHORTCUT_NONE)
				i = 1;
			else if (m_pSlotQueue[2]->m_dwShortcut == SHORTCUT_NONE)
				i = 2;
			else if (m_pSlotQueue[3]->m_dwShortcut == SHORTCUT_NONE)
				i = 3;
			else if (m_pSlotQueue[4]->m_dwShortcut == SHORTCUT_NONE)
				i = 4;
			else if (m_pSlotQueue[5]->m_dwShortcut == SHORTCUT_NONE)
				i = 5;
			else
			{
				SetForbid(TRUE);
				return FALSE;
			}
			if (g_WndMng.m_pWndTaskBar->SetSkillQueue(i, pShortcut->m_dwType, pShortcut->m_dwId, pShortcut->m_pTexture))
				m_DROPFireALPHA = 255;
			return TRUE;
		}
	}

	return TRUE;
}

void CWndNewSkillSlot::OnMouseWndSurface(CPoint point)
{
	CRect DrawRect[MAX_SLOT_QUEUE];
	for (int i = 0; i < MAX_SLOT_QUEUE; i++)
	{
		LPSHORTCUT lpShortcut = m_pSlotQueue[i];
		DrawRect[i] = CTRECT[i];

		if (DrawRect[i].PtInRect(point) && !g_WndMng.m_pLogOutWaitting)
		{
			CPoint point2 = point;
			ClientToScreen(&point2);
			ClientToScreen(&DrawRect[i]);

			if (!lpShortcut->IsEmpty())
			{
				if (lpShortcut->m_dwShortcut == SHORTCUT_SKILL)
				{
					if (lpShortcut->m_dwType == 2)
					{
						g_WndMng.PutToolTip_Troupe(lpShortcut->m_dwId, point2, &DrawRect[i]);
					}
					else
					{
						LPSKILL lpSkill = g_pPlayer->GetSkill(0, lpShortcut->m_dwId);
						g_WndMng.PutToolTip_Skill(lpSkill->dwSkill, lpSkill->dwLevel, point2, &DrawRect[i]);
					}
				}
			}
			if (m_SURF_FIRE[i] == NULL)
			{
				m_SURF_FIRE[i] = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "ActionSlotEff.tga"), 0xffff00ff, TRUE);
			}
		}
		else
		{
			m_SURF_FIRE[i] = NULL;
		}
	}

	if (g_WndMng.m_pLogOutWaitting == NULL)
	{
		if (PtInRect(SlotCustom->rect, point))
		{
			CRect rect = SlotCustom->rect;
			CPoint point2 = point;
			ClientToScreen(&point2);
			ClientToScreen(&rect);
			g_toolTip.PutToolTip(100000, prj.GetText(TID_GAME_SKILLSHORTCUT), rect, point2);
		}
	}
}

void CWndNewSkillSlot::OnDraw(C2DRender* p2DRender)
{
	CRect rect = GetWindowRect();
	CPoint point;
	CPoint point2;
	CTexture* pTop, * pBottom;
	clock_t tmCur = clock();

	if (tmCur > m_tmCoolDown && RotateCoolDownEffect == 0)
	{
		m_bStopCoolDown = true;
		for (int i = 0; i < MAX_SLOT_QUEUE; i++)
			bRenderIllu[i] = false;
	}
	if (m_bStopCoolDown)
	{
		RotateCoolDownEffect++;
		if (RotateCoolDownEffect > 25)
		{
			PLAYSND(SND_PC_ACTIONOULINE01);
			m_bStopCoolDown = false;
			m_bArrival = false;
		}
	}

	pTop = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "slot02.tga"), 0xffff00ff, TRUE);
	pBottom = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "slot03.tga"), 0xffff00ff, TRUE);

	CPoint PTM = CPoint(SlotRt->m_ptCenter.x - 36, SlotRt->m_ptCenter.y);

	if (RotateSLOT != rotate1)
	{
		if (RotateSLOT > rotate1)
		{
			rotate1 += 10;
			if (rotate1 > RotateSLOT)
				rotate1 = RotateSLOT - 10;
		}
		else
		{
			RotateSLOT = 0;
			rotate1 -= 6;
			if (rotate1 < RotateSLOT)
				rotate1 = RotateSLOT;
		}

		for (int i = 0; i < 6; ++i)
		{
			float fAngle = 90 + rotate1 - 60 * i;
			float fRadianEnd;
			fRadianEnd = fAngle * (M_PI / 180);
			xPosition[i] = cos(fRadianEnd) * 50.5f;
			yPosition[i] = sin(fRadianEnd) * 50.5f;
		}
	}

	for (int i = 0; i < 6; ++i)
		m_wndCustom[i].SetWndRect(CRect((int)(xPosition[i] + 97 + PTM.x), (int)(yPosition[i] + 65.5f + PTM.y), 34, 34));

	CTRECT[0] = CRect(PTM.x + 97, PTM.y + 116, PTM.x + 97 + 34, PTM.y + 116 + 34);
	CTRECT[1] = CRect(PTM.x + 141, PTM.y + 90, PTM.x + 141 + 34, PTM.y + 90 + 34);
	CTRECT[2] = CRect(PTM.x + 141, PTM.y + 40, PTM.x + 141 + 34, PTM.y + 40 + 34);
	CTRECT[3] = CRect(PTM.x + 97, PTM.y + 15, PTM.x + 97 + 34, PTM.y + 15 + 34);
	CTRECT[4] = CRect(PTM.x + 53, PTM.y + 40, PTM.x + 53 + 34, PTM.y + 40 + 34);
	CTRECT[5] = CRect(PTM.x + 53, PTM.y + 90, PTM.x + 53 + 34, PTM.y + 90 + 34);

	if ((m_nActionSlot > 0) && (g_WndMng.m_pWndTaskBar->m_nExecute > 0))
	{
		float Time = 1000.0f;
		if (!RotateTimer.Running())
		{
			RotateTimer.Start(Time);
		}
		if (Time <= 1)
		{
			rotates += 180;
			Time += 1000.0f;
		}
	}
	else if ((m_nActionSlot == 0) && (g_WndMng.m_pWndTaskBar->m_nExecute == 0))
	{
		rotates = 0;
	}

	float fRadian = rotate1 * (M_PI / 180);
	SlotRt->RenderRotate(p2DRender, CPoint(0, 0), fRadian, TRUE, 255, 1.0f, 1.0f);

	if ((m_nActionSlot > 0) && (g_WndMng.m_pWndTaskBar->m_nExecute > 0))
		SlotEffect2->RenderRotate(p2DRender, CPoint(0, 0), fRadian, TRUE, m_nFlashAlpha[0], 1.0f, 1.0f);
	else
		SlotEffect2->Render(p2DRender, CPoint(0, 0), 0);

	for (int i = 0; i < MAX_SLOT_QUEUE; i++)
	{
		LPSHORTCUT lpShortcut = m_pSlotQueue[i];
		if (!lpShortcut->IsEmpty())
		{
			float fScal = 1.25f;
			FLOAT fBlend = 0.20f;
			if (bRenderIllu[i])
				fBlend = 0.85f;

			point = CPoint(m_wndCustom[i].m_rectClient.left + 2, m_wndCustom[i].m_rectClient.top - 1);
			if (lpShortcut->m_pTexture)
			{
				p2DRender->RenderTextureRotateALPHA(point, m_Marronzinha, lpShortcut->m_pTexture, fRadian, fBlend, fScal, fScal);
			}
		}
	}

	CPoint DropFPoint;
	if (m_pSlotQueue[1]->m_dwShortcut == SHORTCUT_NONE)
		DropFPoint = CPoint(CTRECT[0].left - 12, CTRECT[0].top - 14);
	else if (m_pSlotQueue[2]->m_dwShortcut == SHORTCUT_NONE)
		DropFPoint = CPoint(CTRECT[1].left - 12, CTRECT[1].top - 14);
	else if (m_pSlotQueue[3]->m_dwShortcut == SHORTCUT_NONE)
		DropFPoint = CPoint(CTRECT[2].left - 12, CTRECT[2].top - 14);
	else if (m_pSlotQueue[4]->m_dwShortcut == SHORTCUT_NONE)
		DropFPoint = CPoint(CTRECT[3].left - 12, CTRECT[3].top - 14);
	else if (m_pSlotQueue[5]->m_dwShortcut == SHORTCUT_NONE)
		DropFPoint = CPoint(CTRECT[4].left - 12, CTRECT[4].top - 14);
	else
	{
		DropFPoint = CPoint(CTRECT[5].left - 12, CTRECT[5].top - 14);
	}

	m_DROP_Fire->Render(&g_Neuz.m_2DRender, DropFPoint, m_DROPFireALPHA);

	for (int i = 0; i < 6; i++)
	{
		if ((m_nActionSlot > 0) && (g_WndMng.m_pWndTaskBar->m_nExecute > 0))
		{
			m_SURF_FIRE[i] = NULL;
		}
		if (m_SURF_FIRE[i] != NULL)
		{
			m_SURF_FIRE[i]->Render(p2DRender, CPoint(m_wndCustom[i].m_rectClient.left - 10, m_wndCustom[i].m_rectClient.top - 14), m_nFlashAlpha[i]);
		}

	}
	if (pTop && pBottom)
	{
		point.y = ((rect.top + rect.bottom) / 2 - (pTop->m_size.cy / 2));
		point.x = ((rect.right / 2) - (pTop->m_size.cx / 2));
		if ((m_nActionSlot > 0) && (g_WndMng.m_pWndTaskBar->m_nExecute > 0) && !m_bArrival)
		{
			pTop->Render(p2DRender, point);
		}
		else
		{
			float fPercent = 1.0f - (float)(tmCur - m_tmStartCoolDown) / (float)(m_tmCoolDown - m_tmStartCoolDown);
			if (fPercent > 1.0f)
				fPercent = 1.0f;
			else if (fPercent < 0.0f)
				fPercent = 0.0f;

			LPDIRECT3DTEXTURE9 pTexture = NULL;

			pTexture = p2DRender->RenderMergeTextures(pTop, pBottom, 64, 64, fPercent);
			if (pTexture)
				p2DRender->RenderTextureNative(point, pTexture, 64, 64, TRUE);
		}
	}
	if (slot5 != NULL && pTop != NULL)
	{
		point.y = 0;
		point.x = ((rect.right / 2) - (pTop->m_size.cx / 2) - (pTop->m_size.cx + 7));
		slot5->Render(&g_Neuz.m_2DRender, point);

	}
	if (m_bStopCoolDown)
	{
		SlotEffect5->RenderRotate(p2DRender, CPoint(0, 0), (FLOAT)RotateCoolDownEffect / 8.0f, 1);
		SlotEffect5->RenderRotate(p2DRender, CPoint(0, 0), 180.0f - (FLOAT)RotateCoolDownEffect / 8.0f, 1);
	}
	if ((m_nActionSlot > 0) && (g_WndMng.m_pWndTaskBar->m_nExecute > 0))
	{
		if (m_bArrival)
		{
			RotateAllEffect++;
			RotateSkillEffect++;
			SlotEffect5->RenderRotate(p2DRender, CPoint(0, 0), RotateAllEffect / 8, 1);
			int nPos = (int)(RotateSLOT / 60.0f);
			if (RotateSLOT == rotate1)
			{
				SlotEffect3->RenderRotate(p2DRender, CPoint(CTRECT[0].left - 10, CTRECT[0].top - 14), RotateSkillEffect / 3, 1);
				if (m_USEFireALPHA != 115 && useskill)
					m_DROP_Fire->Render(p2DRender, CPoint(CTRECT[0].left - 10, CTRECT[0].top - 12), m_USEFireALPHA);
				else if (m_USEFireALPHA == 115 && useskill)
					useskill = FALSE;
			}
		}
	}
}

HRESULT CWndNewSkillSlot::RestoreDeviceObjects()
{
	CWndBase::RestoreDeviceObjects();
	return S_OK;
}

HRESULT CWndNewSkillSlot::InvalidateDeviceObjects()
{
	CWndBase::InvalidateDeviceObjects();
	return S_OK;
}

HRESULT CWndNewSkillSlot::DeleteDeviceObjects()
{
	CWndBase::DeleteDeviceObjects();
	return InvalidateDeviceObjects();
}

void CWndNewSkillSlot::OnInitialUpdate(void)
{
	CWndNeuz::OnInitialUpdate();
	RestoreDeviceObjects();
	m_wndCustom[0].Create("", 0, CRect(97, 116, 34, 34), this, 101);
	m_wndCustom[1].Create("", 0, CRect(141, 90, 34, 34), this, 102);
	m_wndCustom[2].Create("", 0, CRect(141, 40, 34, 34), this, 103);
	m_wndCustom[3].Create("", 0, CRect(97, 15, 34, 34), this, 104);
	m_wndCustom[4].Create("", 0, CRect(53, 40, 34, 34), this, 105);
	m_wndCustom[5].Create("", 0, CRect(53, 90, 34, 34), this, 106);

	SlotCustom = GetWndCtrl(WIDC_CUSTOM1);
	slot5 = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "slot05.tga"), 0xffff00ff, TRUE);
	SlotRt = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "slot04.tga"), 0xffff00ff, TRUE);
	SlotEffect5 = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "ActionSlotEff5.tga"), 0xffffffff, TRUE);
	SlotEffect3 = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "ActionSlotEff3_02.tga"), 0xffffffff, TRUE);
	SlotEffect2 = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "ActionSlotEff4.tga"), 0xffffffff, TRUE);
	m_Marronzinha = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "slot07.tga"), 0xffffffff, TRUE);
	m_DROP_Fire = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "ActionSlotEff2.tga"), 0xffff00ff, TRUE);

	m_aSlotSkill.m_pTexture = m_textureMng.AddTexture(g_Neuz.m_pd3dDevice, MakePath(DIR_ICON, "icon_ActionSkill.dds"), 0xffff00ff, TRUE);
	m_aSlotSkill.m_dwShortcut = SHORTCUT_SKILLFUN;

	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CPoint point(rectRoot.right - 166, rectRoot.bottom - 170);
	Move(point);
	DelWndStyle(WBS_MOVE);
}

CWndTaskBar_HUD_SLIDE::CWndTaskBar_HUD_SLIDE(void)
{
	CWndTaskBarInterface::CWndTaskBarInterface();
	m_bPick = &m_bPickup_SLIDE;
	m_nSlotIndex = 4;
	m_TEXTUCtrl = NULL;
	for (int i = 0; i < 10; i++)
	{
		m_dwALPHA[i] = 255;
	}
}

BOOL CWndTaskBar_HUD_SLIDE::Initialize(CWndBase* pWndParent, DWORD dwType)
{
	return CWndNeuz::InitDialog(g_Neuz.GetSafeHwnd(), APP_NEWTASKBAR02, WBS_MANAGER | WBS_SOUND, CPoint(0, 0), pWndParent);
}

BOOL CWndTaskBar_HUD_SLIDE::Process(void)
{
	BOOL bInRect = GetWindowRect().PtInRect(GetMousePoint());
	for (int i = 0; i < 10; i++)
	{
		if (!bInRect)
			slot1[i] = NULL;
		m_USEFireALPHA[i] -= 20;

		if (m_USEFireALPHA[i] < 5)
		{
			m_USEFireALPHA[i] = 0;
		}
	}

	return CWndBase::Process();
}

void CWndTaskBar_HUD_SLIDE::OnDraw(C2DRender* p2DRender)
{
	if (IsValidObj(g_pPlayer))
	{
		for (int i = 0; i < 10; i++)
		{
			if (wndCtrl[i]->rect.Width() <= 48 + 50)
				m_bCtrlVisible[i] = false;
			if (GetWindowRect().Width() >= 34 * (i + 1) + 50 + 2 * (i + 1))
				m_bCtrlVisible[i] = true;
			if (m_bCtrlVisible[i])
				m_TEXTUCtrl->Render(p2DRender, CPoint(wndCtrl[i]->rect.left, wndCtrl[i]->rect.top));
		}
		CWndTaskBarInterface::OnDraw(p2DRender);
	}
}

void CWndTaskBar_HUD_SLIDE::OnInitialUpdate(void)
{
	CWndTaskBarInterface::OnInitialUpdate();
	CRect rectRoot = m_pWndRoot->GetLayoutRect();
	CRect rectWindow = GetWindowRect();

	CPoint point(rectRoot.right - rectWindow.Width() - 270, rectRoot.bottom - 70);
	Move(point);
	SetWndRect(CRect(GetWndRect().left, rectRoot.bottom - 70, rectRoot.right - 672, GetWndRect().bottom));

	CWndStatic* pStatic = (CWndStatic*)GetDlgItem(WIDC_STATIC1);
	pStatic->Move(rectWindow.right, rectWindow.bottom);
	CRect rect = GetWndRect();
	rect.left = rect.right - g_Option.m_nWidthSlideBar;
	SetWndRect(rect);

	m_TEXTUCtrl = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "WndExpansionSlot01_1.tga"), 0xffff00ff);

	DelWndStyle(WBS_MOVE);
	RestoreDeviceObjects();
}

CWndTaskBarInterface::CWndTaskBarInterface(void)
{
	m_pSelectShortcut = NULL;
	for (int i = 0; i < 10; i++)
	{
		slot1[i] = NULL;
		m_USEFireALPHA[i] = 0;
		m_nActionListener[i] = -1;
		m_pSlotItem[i] = NULL;
		m_bCtrlVisible[i] = true;
	}

	m_bReqAlt = false;
	m_bPick = &m_bPickup;
	m_nSlotIndex = 0;
}

CWndTaskBarInterface::~CWndTaskBarInterface(void)
{
	m_pSelectShortcut = NULL;
	for (int i = 0; i < 10; i++)
	{
		slot1[i] = NULL;
	}
	DeleteDeviceObjects();
}

void CWndTaskBarInterface::OnSize(UINT nType, int cx, int cy)
{
	CWndNeuz::OnSize(nType, cx, cy);
}

void CWndTaskBarInterface::OnLButtonUp(UINT nFlags, CPoint point)
{
	LPSHORTCUT pShortcut = NULL;
	if (!CWndTaskBarInterface::IsLock())
		*m_bPick = FALSE;

	for (int i = 0; i < 10; i++)
	{
		if (!m_bCtrlVisible[i])
			continue;
		if (wndCtrl[i]->rect.PtInRect(point))
		{
			pShortcut = m_pSlotItem[i];
			m_USEFireALPHA[i] = 255;
		}
	}
	if (pShortcut && pShortcut == m_pSelectShortcut && !pShortcut->IsEmpty() && pShortcut->m_dwData != 2)
	{
		if (pShortcut->m_dwShortcut == SHORTCUT_SKILLFUN)
		{
			CWndNewSkillSlot* m_SkillSL = (CWndNewSkillSlot*)g_WndMng.GetWndBase(APP_SLOT);
			if (clock() < m_SkillSL->m_tmCoolDown || m_SkillSL->m_bStopCoolDown)
			{
				return;
			}
			else
			{
				if (g_WndMng.m_pWndTaskBar->m_nExecute == 0)
					g_WndMng.ObjectExecutor(pShortcut);
			}
		}
		g_WndMng.ObjectExecutor(pShortcut);
	}
	ReleaseCapture();
}

void CWndTaskBarInterface::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (g_WndMng.m_pWndMenu && g_WndMng.m_pWndMenu->IsVisible())
		g_WndMng.m_pWndMenu->SetVisible(FALSE);

	CRect ST_Rect = CRect(2, 4, 20, 36);
	CRect ST_Rect2 = CRect(384, 4, 390, 36);

	if (PtInRect(ST_Rect, point) || PtInRect(ST_Rect2, point))
	{
		ClientToScreen(&point);

		if (!CWndTaskBarInterface::IsLock())
		{
			*m_bPick = TRUE;
		}
	}

	LPSHORTCUT pShortcut = NULL;
	for (int i = 0; i < 10; i++)
	{
		if (!m_bCtrlVisible[i])
			continue;
		if (wndCtrl[i]->rect.PtInRect(point))
		{
			if (!m_pSlotItem[i]->IsEmpty())
			{
				if (!CWndTaskBarInterface::IsLock())
				{
					*m_bPick = FALSE;
				}
				m_pSelectShortcut = m_pSlotItem[i];
			}
		}
	}
	SetCapture();
}

void CWndTaskBarInterface::OnRButtonUp(UINT nFlags, CPoint point)
{
	for (int i = 0; i < 10; i++)
	{
		if (!m_bCtrlVisible[i])
			continue;
		CRect rect = wndCtrl[i]->rect;
		if (rect.PtInRect(point))
		{
			CPoint point2 = point;
			ClientToScreen(&point2);
			ClientToScreen(&rect);

			if (!m_pSlotItem[i]->IsEmpty())
			{
				m_pSlotItem[i]->Empty();
				g_DPlay.SendRemoveItemTaskBar(m_nSlotIndex, (BYTE)(i));
			}
		}
	}
}

void CWndTaskBarInterface::OnMouseMove(UINT nFlags, CPoint point)
{
	CWndTaskBar_HUD* pWndTB = (CWndTaskBar_HUD*)g_WndMng.GetWndBase(APP_NEWTASKBAR);
	CRect ST_Rect = CRect(2, 4, 20, 36);
	CRect ST_Rect2 = CRect(384, 4, 390, 36);

	if (m_bLButtonDown && IsPush())
	{
		if (m_pSelectShortcut && !m_pSelectShortcut->IsEmpty())
		{
			if (m_pSelectShortcut->m_dwId == 400)
				return;

			if (m_pSelectShortcut->m_dwShortcut == SHORTCUT_LORDSKILL)
			{
				m_pSelectShortcut->m_dwId++;
			}
			memcpy(&m_GlobalShortcut, m_pSelectShortcut, sizeof(m_GlobalShortcut));
			m_GlobalShortcut.m_pFromWnd = this;
			m_GlobalShortcut.m_dwData = (DWORD)m_pSelectShortcut;
			m_pSelectShortcut = NULL;
		}
	}
	CWndNeuz::OnMouseMove(nFlags, point);
}

void CWndTaskBarInterface::OnMouseWndSurface(CPoint point)
{
	for (int i = 0; i < MAX_SLOT_ITEM; i++)
	{
		LPSHORTCUT lpShortcut = m_pSlotItem[i];
		CRect DrawRect = wndCtrl[i]->rect;
		if (DrawRect.PtInRect(point) && !g_WndMng.m_pLogOutWaitting)
		{
			CPoint point2 = point;
			ClientToScreen(&point2);
			ClientToScreen(&DrawRect);

			if (!m_pSlotItem[i]->IsEmpty())
			{
				if (lpShortcut->m_dwShortcut >= 0 && lpShortcut->m_dwShortcut <= 11)
				{
					g_WndMng.m_pWndTaskBar->PutTooTip(m_pSlotItem[i], point2, &DrawRect);
				}
			}
			if (slot1[i] == NULL)
			{
				slot1[i] = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "SlotSelect.tga"), 0xffff00ff);
			}
		}
		else
			slot1[i] = NULL;
	}
}

BOOL CWndTaskBarInterface::Process(void)
{
	CWndRegVend* pWndRegVend = (CWndRegVend*)g_WndMng.GetWndBase(APP_VENDOREX_SELL);
	CWndRegVend* pWndVendorBuy = (CWndRegVend*)g_WndMng.GetWndBase(APP_VENDOREX_BUY);
	if (pWndRegVend || pWndVendorBuy)
	{
		return CWndBase::Process();
	}
	CWndEdit* pWndEdit = CWndEdit::GetWndEditCtrl();
	if ((g_Neuz.m_bActiveNeuz != FALSE) && (pWndEdit == NULL))
	{
		for (int i = 0; i < 10; i++)
		{
			m_USEFireALPHA[i] -= 20;

			if (m_USEFireALPHA[i] < 5)
			{
				m_USEFireALPHA[i] = 0;
			}
		}
		BOOL bALTKeySwitch = (GetKeyState(VK_MENU) & 0x8000);
		bool bALT = (bALTKeySwitch && m_bReqAlt || !bALTKeySwitch && !m_bReqAlt);
		BOOL bInRect = GetWindowRect().PtInRect(GetMousePoint());
		for (int i = 0; i < 10; i++)
		{
			if (!bInRect)
				slot1[i] = NULL;
			if (m_nActionListener[i] == -1)
				continue;

			if (GetKeyState(m_nActionListener[i]) & 0x8000 && m_USEFireALPHA[i] == 0 && bALT)
			{
				if (m_pSlotItem[i]->IsEmpty())
					return CWndBase::Process();
				if (m_pSlotItem[i]->m_dwShortcut == SHORTCUT_ITEM)
				{
					CItemBase* pItemBase = g_pPlayer->GetItemId(m_pSlotItem[i]->m_dwId);
					if (pItemBase)
					{
						int nPart = pItemBase->GetProp()->dwParts;
						if (nPart != -1)
							g_bSlotSwitchAboutEquipItem[i] = TRUE;
					}
				}
				if (m_pSlotItem[i]->m_dwShortcut == SHORTCUT_SKILLFUN)
				{
					CWndNewSkillSlot* m_SkillSL = (CWndNewSkillSlot*)g_WndMng.GetWndBase(APP_SLOT);
					if (clock() < m_SkillSL->m_tmCoolDown || m_SkillSL->m_bStopCoolDown)
					{
						return CWndBase::Process();
					}
					if (g_WndMng.m_pWndTaskBar->m_nExecute != 0)
					{
						return CWndBase::Process();
					}
				}
				g_WndMng.ObjectExecutor(m_pSlotItem[i]);
				m_USEFireALPHA[i] = 255;
			}
		}
	}
	return CWndBase::Process();
}

BOOL CWndTaskBarInterface::OnDropIcon(LPSHORTCUT pShortcut, CPoint point)
{
	if (CWndTaskBarInterface::IsLock())
		return FALSE;

	CRect rect = GetWindowRect();
	rect.DeflateRect(3, 3);

	if (pShortcut->m_pFromWnd == this)
	{
		LPSHORTCUT lpShortcut = (LPSHORTCUT)pShortcut->m_dwData;
		if (GetClientRect().PtInRect(point) == FALSE)
		{
			g_DPlay.SendRemoveItemTaskBar(m_nSlotIndex, (BYTE)(lpShortcut->m_dwIndex));
			m_pSlotItem[lpShortcut->m_dwIndex]->Empty();
			lpShortcut->Empty();
			return TRUE;
		}
	}
	CWndBase* pWndFrame = pShortcut->m_pFromWnd->GetFrameWnd();

	if (pWndFrame && (pWndFrame->GetWndId() != APP_SLOT && pWndFrame->GetWndId() != APP_INVENTORY
		&& pWndFrame != g_WndMng.m_pWndTaskBar && pWndFrame->GetWndId() != APP_COMMUNICATION_CHAT
		&& pWndFrame->GetWndId() != APP_SKILL4 && pWndFrame->GetWndId() != APP_MOTION && pWndFrame->GetWndId() != APP_PARTY
		&& pWndFrame->GetWndId() != APP_LORD_SKILL && pWndFrame->GetWndId() != APP_NEWTASKBAR
		&& pWndFrame->GetWndId() != APP_NEWTASKBAR02 && pWndFrame->GetWndId() != APP_NEWTASKBAR03
		&& pWndFrame->GetWndId() != APP_NEWTASKBAR04))
	{
		SetForbid(TRUE);
		return FALSE;
	}

	for (int i = 0; i < 10; i++)
	{
		if (!m_bCtrlVisible[i])
			continue;

		if (wndCtrl[i]->rect.PtInRect(point))
		{
			if (pShortcut->m_pFromWnd == this)
			{
				LPSHORTCUT lpCurShortcut = (LPSHORTCUT)pShortcut->m_dwData;
				if (m_pSlotItem[i] == lpCurShortcut)
					return FALSE;
			}
			if (pShortcut->m_dwShortcut == SHORTCUT_CHAT)
			{
				CString sChat = m_GlobalShortcut.m_szString;
				sChat.Replace("--", "");
				sChat.Replace("'", "");
				sChat.Replace("/*", "");
				sChat.Replace("*/", "");
				strcpy(m_GlobalShortcut.m_szString, (const char*)sChat);
			}
			else if (pShortcut->m_dwShortcut == SHORTCUT_SKILL)
			{
				ItemProp* pProp;
				if (pShortcut->m_dwType == 2)
					pProp = prj.GetPartySkill(pShortcut->m_dwId);
				else
				{
					LPSKILL pSkill = g_pPlayer->GetSkill(0, pShortcut->m_dwId);
					pProp = prj.GetSkillProp(pSkill->dwSkill);
				}
				if (pProp->dwComboStyle != CT_STEP && pProp->dwComboStyle != CT_GENERAL)
				{
					SetForbid(TRUE);
					return FALSE;
				}
			}
			if (pShortcut->m_dwShortcut == SHORTCUT_APPLET)
			{
				AppletFunc* pAppletFunc = g_WndMng.GetAppletFunc(pShortcut->m_dwId);
				m_pSlotItem[i]->m_pTexture = m_textureMng.AddTexture(g_Neuz.m_pd3dDevice, MakePath(DIR_ICON, pAppletFunc->m_pszIconName), 0xffff00ff);
			}
			else if (pShortcut->m_dwShortcut == SHORTCUT_SKILL)
			{
				if (pShortcut->m_dwType == 2)
				{
					ItemProp* pProp = prj.GetPartySkill(pShortcut->m_dwId);
					m_pSlotItem[i]->m_pTexture = m_textureMng.AddTexture(g_Neuz.m_pd3dDevice, MakePath(DIR_ICON, pProp->szIcon), 0xffff00ff);
				}
				else
				{
					LPSKILL lpSkill = g_pPlayer->GetSkill(pShortcut->m_dwType, pShortcut->m_dwId);
					ItemProp* pSkillProp = prj.m_aPropSkill.GetAt(lpSkill->dwSkill);
					if (pSkillProp)
						m_pSlotItem[i]->m_pTexture = m_textureMng.AddTexture(g_Neuz.m_pd3dDevice, MakePath(DIR_ICON, pSkillProp->szIcon), 0xffff00ff);
				}
			}
			else if (pShortcut->m_dwShortcut == SHORTCUT_CHAT)
			{
				m_pSlotItem[i]->m_pTexture = m_textureMng.AddTexture(g_Neuz.m_pd3dDevice, MakePath(DIR_ICON, "icon_MacroChat.dds"), 0xffff00ff);
			}
			else if (pShortcut->m_dwShortcut == SHORTCUT_EMOTICON)
			{
				if (pShortcut->m_dwId >= 0 && pShortcut->m_dwId < MAX_EMOTICON_NUM)
				{
					TCHAR buffer[MAX_SHORTCUT_STRING] = { 0 };
					_tcscat(buffer, "/");
					_tcscat(buffer, g_DialogMsg.m_EmiticonCmd[pShortcut->m_dwId].m_szCommand);
					_tcscpy(pShortcut->m_szString, buffer);
					m_pSlotItem[i]->m_pTexture = g_DialogMsg.m_texEmoticonUser.GetAt(pShortcut->m_dwId);
				}
			}
			else if (pShortcut->m_dwShortcut == SHORTCUT_ITEM)
			{
				CItemBase* pItemBase;
				pItemBase = g_pPlayer->GetItemId(pShortcut->m_dwId);
				if (pItemBase)
					m_pSlotItem[i]->m_pTexture = pItemBase->GetTexture();
			}
			else if (pShortcut->m_dwShortcut == SHORTCUT_MOTION)
			{
				MotionProp* pMotionProp = prj.GetMotionProp(pShortcut->m_dwId);
				if (pMotionProp)
				{
					pMotionProp->pTexture = m_textureMng.AddTexture(g_Neuz.m_pd3dDevice, MakePath(DIR_ICON, pMotionProp->szIconName), 0xffff00ff);
					m_pSlotItem[i]->m_pTexture = pMotionProp->pTexture;
				}
				else
					return FALSE;
			}
			else if (pShortcut->m_dwShortcut == SHORTCUT_SKILL)
			{
				LPSKILL lpSkill = g_pPlayer->GetSkill(pShortcut->m_dwType, pShortcut->m_dwId);
				m_pSlotItem[i]->m_pTexture = m_textureMng.AddTexture(g_Neuz.m_pd3dDevice, MakePath(DIR_ITEM, lpSkill->GetProp()->szIcon), 0xffff00ff, TRUE);
			}
			else if (pShortcut->m_dwShortcut == SHORTCUT_SKILLFUN)
				m_pSlotItem[i]->m_pTexture = pShortcut->m_pTexture;

			if (pShortcut->m_dwShortcut == SHORTCUT_ITEM)
			{
				CItemBase* pItemBase = g_pPlayer->GetItemId(pShortcut->m_dwId);
				if (pShortcut && pItemBase && pItemBase->GetProp()->dwPackMax > 1)
					m_pSlotItem[i]->m_dwItemId = pItemBase->m_dwItemId;
			}
			if (pShortcut->m_pFromWnd == this)
			{
				LPSHORTCUT lpShortcut = (LPSHORTCUT)pShortcut->m_dwData;
				g_DPlay.SendRemoveItemTaskBar(m_nSlotIndex, (BYTE)(lpShortcut->m_dwIndex));
			}

			if (pShortcut->m_pTexture != NULL)
				m_pSlotItem[i]->m_pTexture = pShortcut->m_pTexture;

			m_pSlotItem[i]->m_dwShortcut = pShortcut->m_dwShortcut;
			m_pSlotItem[i]->m_dwType = pShortcut->m_dwType;
			m_pSlotItem[i]->m_dwIndex = i;
			m_pSlotItem[i]->m_dwId = pShortcut->m_dwId;
			m_pSlotItem[i]->m_dwUserId = 0;
			m_pSlotItem[i]->m_dwData = 1;

			if (pShortcut->m_dwShortcut == SHORTCUT_LORDSKILL)
				m_pSlotItem[i]->m_dwId--;

			strcpy(m_pSlotItem[i]->m_szString, m_GlobalShortcut.m_szString);
			g_DPlay.SendAddItemTaskBar(m_nSlotIndex, i, pShortcut);

			return TRUE;
		}
	}
	return TRUE;
}

void CWndTaskBarInterface::RenderCollTime(CPoint pt, DWORD dwSkillId, C2DRender* p2DRender)
{
	LPSKILL lpSkill = &g_pPlayer->m_aJobSkill[dwSkillId];
	if (lpSkill)
	{
		DWORD dwDelay = g_pPlayer->GetReuseDelay(dwSkillId);
		if (dwDelay > 0)
		{
#if __VER >= 9
			ItemProp* pSkillProp = lpSkill->GetProp();
			ASSERT(pSkillProp);
			AddSkillProp* pAddSkillProp = prj.GetAddSkillProp(pSkillProp->dwSubDefine, lpSkill->dwLevel);
			ASSERT(pAddSkillProp);
			RenderRadar(p2DRender, pt,
				pAddSkillProp->dwCooldown - dwDelay,
				pAddSkillProp->dwCooldown);
#else
			RenderRadar(p2DRender, pt,
				lpSkill->GetProp()->dwSkillReady - dwDelay,
				lpSkill->GetProp()->dwSkillReady);
#endif
		}
	}
}

#if __VER >= 12
void CWndTaskBarInterface::RenderLordCollTime(CPoint pt, DWORD dwSkillId, C2DRender* p2DRender)
{
	CCLord* pLord = CCLord::Instance();
	CLordSkillComponentExecutable* pComponent = pLord->GetSkills()->GetSkill(dwSkillId);
	if (!pComponent) return;
	DWORD dwDelay = 0;
	if (pComponent->GetTick() > 0)
		RenderRadar(p2DRender, pt, pComponent->GetCooltime() - pComponent->GetTick(), pComponent->GetCooltime());
}
#endif

void CWndTaskBarInterface::OnDraw(C2DRender* p2DRender)
{
	if (IsValidObj(g_pPlayer))
	{
		CPoint point;
		DWORD dwCur = g_tmCurrent;
		if (m_GlobalShortcut.IsEmpty() == FALSE)
		{
			for (int i = 0; i < MAX_SLOT_ITEM; i++)
			{
				DWORD dwColor = D3DCOLOR_ARGB(15, 20, 0, 200);
				CRect Rectskill = wndCtrl[i]->rect;

				switch (m_GlobalShortcut.m_dwShortcut)
				{
				case SHORTCUT_APPLET:
				case SHORTCUT_ITEM:
				case SHORTCUT_MOTION:
					p2DRender->RenderFillRect(Rectskill, dwColor);
					p2DRender->RenderFillRect(Rectskill, dwColor);
					break;
				case SHORTCUT_SKILL:
					if (m_GlobalShortcut.m_dwType == 0)
					{
						DWORD dwSkill = g_pPlayer->GetSkill(0, m_GlobalShortcut.m_dwId)->dwSkill;
						DWORD dwComboStyleSrc = prj.GetSkillProp(dwSkill)->dwComboStyle;
						if (dwComboStyleSrc == CT_STEP || dwComboStyleSrc == CT_GENERAL)
							p2DRender->RenderFillRect(Rectskill, dwColor);
						p2DRender->RenderFillRect(Rectskill, dwColor);
					}
					else
						p2DRender->RenderFillRect(Rectskill, dwColor);
					break;
				case SHORTCUT_SKILLFUN:
					p2DRender->RenderFillRect(Rectskill, dwColor);
					break;
				}
			}
		}
		for (int i = 0; i < MAX_SLOT_ITEM; i++)
		{
			if (!m_bCtrlVisible[i])
				continue;
			point = CPoint(wndCtrl[i]->rect.left, wndCtrl[i]->rect.top);
			LPSHORTCUT lpShortcut = m_pSlotItem[i];

			if (!lpShortcut->IsEmpty())
			{
				if (lpShortcut->m_pTexture)
					p2DRender->RenderTexture(point, lpShortcut->m_pTexture);


				if (lpShortcut->m_dwShortcut == SHORTCUT_ITEM)
				{
					CItemBase* pItemBase = g_pPlayer->GetItemId(lpShortcut->m_dwId);
					CItemElem* pItemElem = (CItemElem*)pItemBase;
					if (pItemElem)
					{
						if (pItemElem->GetProp()->dwPackMax > 1)
						{
							TCHAR szTemp[32];
							_stprintf(szTemp, "%d", g_pPlayer ? g_pPlayer->m_Inventory.GetItemCount(pItemElem->m_dwItemId) : 0);
							CSize size = m_p2DRender->m_pFont->GetTextExtent(szTemp);
							CD3DFont* pOldFont = p2DRender->GetFont();
							p2DRender->SetFont(CWndBase::m_Theme.m_pFontWndNewTitle2);
							p2DRender->TextOut(point.x + 32 - size.cx, point.y + 35 - size.cy, szTemp, 0xffeaebdd);
							p2DRender->SetFont(pOldFont);
						}
						DWORD dwGroup = g_pPlayer->m_cooltimeMgr.GetGroup(pItemElem->GetProp());
						if (dwGroup)
						{
							DWORD dwEnd = g_pPlayer->m_cooltimeMgr.GetTime(dwGroup);
							if (dwEnd != 0 && dwEnd > dwCur)
							{
								DWORD dwBase = g_pPlayer->m_cooltimeMgr.GetBase(dwGroup);
								RenderRadar(p2DRender, point, dwCur - dwBase, dwEnd - dwBase);
							}
						}
					}
					else
					{
						ItemProp* pItemProp = prj.GetItemProp(lpShortcut->m_dwItemId);
						if (pItemProp && pItemProp->dwPackMax > 1)
						{
							DWORD dwId = g_pPlayer->m_Inventory.Find(lpShortcut->m_dwItemId);
							if (dwId != NULL_ID)
							{
								lpShortcut->m_dwId = dwId;
								g_DPlay.SendAddAppletTaskBar(i, lpShortcut);
							}
							else
							{
								lpShortcut->Empty();
								g_DPlay.SendRemoveAppletTaskBar(i);
							}
						}
						else
						{
							lpShortcut->Empty();
							g_DPlay.SendRemoveAppletTaskBar(i);
						}
					}
				}
				else if (lpShortcut->m_dwShortcut == SHORTCUT_APPLET)
				{
					AppletFunc* pAppletFunc = g_WndMng.GetAppletFunc(lpShortcut->m_dwId);
					if (pAppletFunc && pAppletFunc->m_cHotkey)
					{
						CPoint ptHotkey(point.x + 8, point.y - 9);
						DRAW_HOTKEY(p2DRender, ptHotkey, pAppletFunc->m_cHotkey);
					}
				}
				else if (lpShortcut->m_dwShortcut == SHORTCUT_SKILL && lpShortcut->m_dwType != 2)
				{
					RenderCollTime(point, lpShortcut->m_dwId, p2DRender);
				}
#if __VER >= 12
				else if (lpShortcut->m_dwShortcut == SHORTCUT_LORDSKILL)
				{
					RenderLordCollTime(point, lpShortcut->m_dwId, p2DRender);
				}
#endif
				else if (lpShortcut->m_dwShortcut == SHORTCUT_MOTION)
				{
					if (lpShortcut->m_dwId == MOT_BASE_ESCAPE)
					{
						ItemProp* pItem = prj.GetItemProp(g_AddSMMode.dwSMItemID[SM_ESCAPE]);

						if (pItem && g_pPlayer)
						{
							CTimeSpan ct(g_pPlayer->m_dwSMTime[SM_ESCAPE]);

							if (ct.GetTotalSeconds())
							{
								point.y -= 1;
								point.x += 1;
								RenderRadar(m_p2DRender, point, (DWORD)(pItem->dwCircleTime - ct.GetTotalSeconds()), pItem->dwCircleTime);
							}
						}
					}
				}
				else if (lpShortcut->m_dwShortcut == SHORTCUT_SKILLFUN)
				{
					CWndNewSkillSlot* m_SkillSL = (CWndNewSkillSlot*)g_WndMng.GetWndBase(APP_SLOT);
					if (clock() < m_SkillSL->m_tmCoolDown || m_SkillSL->m_bStopCoolDown)
					{
						RenderRadar(m_p2DRender, point, (DWORD)(m_SkillSL->m_tmCoolDown), m_SkillSL->m_tmStartCoolDown);
					}
				}
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (!m_bCtrlVisible[i])
			continue;
		if (slot1[i] != NULL)
		{
			slot1[i]->Render(p2DRender, CPoint(wndCtrl[i]->rect.left - 3, wndCtrl[i]->rect.top - 3));
		}
		if ((m_USEFIRE[i] != NULL) && (!m_pSlotItem[i]->IsEmpty()))
		{
			m_USEFIRE[i]->Render(p2DRender, CPoint(wndCtrl[i]->rect.left, wndCtrl[i]->rect.top), m_USEFireALPHA[i]);
		}
	}
}

void CWndTaskBarInterface::OnInitialUpdate(void)
{
	CWndNeuz::OnInitialUpdate();

	if (CWndTaskBarInterface::IsLock())
		*m_bPick = FALSE;

	wndCtrl[0] = GetWndCtrl(WIDC_CUSTOM1);
	wndCtrl[1] = GetWndCtrl(WIDC_CUSTOM2);
	wndCtrl[2] = GetWndCtrl(WIDC_CUSTOM3);
	wndCtrl[3] = GetWndCtrl(WIDC_CUSTOM4);
	wndCtrl[4] = GetWndCtrl(WIDC_CUSTOM5);
	wndCtrl[5] = GetWndCtrl(WIDC_CUSTOM6);
	wndCtrl[6] = GetWndCtrl(WIDC_CUSTOM7);
	wndCtrl[7] = GetWndCtrl(WIDC_CUSTOM8);
	wndCtrl[8] = GetWndCtrl(WIDC_CUSTOM9);
	wndCtrl[9] = GetWndCtrl(WIDC_CUSTOM10);

	for (int i = 0; i < 10; i++)
	{
		m_USEFIRE[i] = CWndBase::m_textureMng.AddTexture(D3DDEVICE, MakePath(DIR_THEME, "UseSlot.tga"), 0xffff00ff, TRUE);
	}
}

#endif