// WndArcane.h: interface for the CWndNeuz class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDTASKBAR_H__A93F3186_63D6_43C1_956F_EC8691E0C7D9__INCLUDED_)
#define AFX_WNDTASKBAR_H__A93F3186_63D6_43C1_956F_EC8691E0C7D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef __NEW_TASKBAR_V19
class CWndTaskBarInterface : public CWndNeuz
{
public:
	CWndTaskBarInterface(void);
	~CWndTaskBarInterface(void);

	LPSHORTCUT     m_pSlotItem[MAX_SLOT_ITEM];
	LPSHORTCUT     m_pSelectShortcut;
	CTexture*	   slot1[10];
	LPWNDCTRL      wndCtrl[10];

	int            m_USEFireALPHA[10];
	CTexture*	   m_USEFIRE[10];

	int				m_nActionListener[10];
	bool			m_bReqAlt;
	bool			m_bCtrlVisible[10]; //slide bar
	BOOL			*m_bPick;

	BYTE			m_nSlotIndex;

	static bool m_bLock;
	static void Lock(){ m_bLock = !m_bLock; }
	static bool IsLock(){ return m_bLock; }
	void RenderCollTime(CPoint pt, DWORD dwSkillId, C2DRender* p2DRender);
#if __VER >= 12 // __LORD
	void RenderLordCollTime(CPoint pt, DWORD dwSkillId, C2DRender* p2DRender);
#endif // __LORD
	virtual void OnDraw(C2DRender* p2DRender);
	virtual void OnInitialUpdate();
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);

	virtual BOOL OnDropIcon(LPSHORTCUT pShortcut, CPoint point = 0);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnMouseWndSurface(CPoint point);
	virtual BOOL Process();

	void PickupModeSlide(){ m_bPick = &m_bPickup_SLIDE; }

};


class CWndTaskBar_HUD_EX1 : public CWndTaskBarInterface
{
public:
	virtual BOOL Initialize(CWndBase* pWndParent = NULL, DWORD nType = MB_OK);
	virtual void OnDraw(C2DRender* p2DRender);
	virtual void OnInitialUpdate();
};
class CWndTaskBar_HUD_EX2 : public CWndTaskBarInterface
{
public:
	virtual BOOL Initialize(CWndBase* pWndParent = NULL, DWORD nType = MB_OK);
	virtual void OnDraw(C2DRender* p2DRender);
	virtual void OnInitialUpdate();
};
class CWndTaskBar_HUD_EX3 : public CWndTaskBarInterface
{
public:
	virtual BOOL Initialize(CWndBase* pWndParent = NULL, DWORD nType = MB_OK);
	virtual void OnInitialUpdate();
};


class CWndTaskBar_HUD_SLIDE : public CWndTaskBarInterface
{
public:
	CWndTaskBar_HUD_SLIDE(void);

	CTexture*		m_TEXTUCtrl;
	CWndStatic*     pWndST;
	LPWNDCTRL       pWndST_SL;

public:
	virtual BOOL Initialize(CWndBase* pWndParent = NULL, DWORD nType = MB_OK);
	virtual void OnDraw(C2DRender* p2DRender);
	virtual void OnInitialUpdate();
	virtual BOOL Process();
};
class CWndTaskBar_HUD : public CWndTaskBarInterface
{
public:
	CWndTaskBar_HUD_EX3* pWndTaskBar_HUD_EX3;
	CWndTaskBar_HUD_EX2* pWndTaskBar_HUD_EX2;
	CWndTaskBar_HUD_EX1* pWndTaskBar_HUD_EX1;

	CTexture*      m_pTexture;
	BOOL m_pAppletSlotOpen;
	BOOL m_paltSlotOpen;
	BOOL m_pfSlotOpen;

public:
	int		m_nDisplay;

	CTexture m_HPGaugeTexture;
	CTexture m_MPGaugeTexture;
	CTexture m_FPGaugeTexture;
	CTexture m_EXPGaugeTexture;

	LPDIRECT3DVERTEXBUFFER9 m_pVBHPGauge;
	LPDIRECT3DVERTEXBUFFER9 m_pVBMPGauge;
	LPDIRECT3DVERTEXBUFFER9 m_pVBFPGauge;
	LPDIRECT3DVERTEXBUFFER9 m_pVBEXPGauge;


	BOOL m_bVBHPGauge;
	BOOL m_bVBMPGauge;
	BOOL m_bVBFPGauge;
	BOOL m_bVBEXPGauge;

	int m_nHPWidth;
	int m_nMPWidth;
	int m_nFPWidth;
	int m_nEXPWidth;

	void MakeGaugeVertex();

	CWndTaskBar_HUD();
	virtual void OnDraw(C2DRender* p2DRender);
	virtual	void OnInitialUpdate();
	virtual BOOL Initialize(CWndBase* pWndParent = NULL, DWORD dwWndId = 0);

	virtual	void SetWndRect(CRect rectWnd, BOOL bOnSize = TRUE);
	virtual BOOL OnChildNotify(UINT message, UINT nID, LRESULT* pLResult);
	virtual void OnMouseWndSurface(CPoint point);
	virtual BOOL Process();

	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();

	void ScrollTaskBars();

};
class CWndNewSkillSlot : public CWndNeuz
{
public:
	float rotates;

	LPSHORTCUT     m_pSlotQueue[MAX_SLOT_QUEUE];

	LPSHORTCUT     m_pSelectShortcut;
	LPWNDCTRL      wndCtrl[6];
	SHORTCUT       m_aSlotSkill;
	CTexture* m_pTexture;
	CTexture* slot1[6];
	CTexture* slot12[MAX_SLOT_QUEUE];
	CTexture* SlotEffectSolta[MAX_SLOT_QUEUE];
	CTexture   m_texArrow;
	CTexture   m_texArrow1;
	CTexture   m_texArrow2;
	CBillboard m_billArrow;
	CBillboard m_billArrow1;
	CBillboard m_billArrow2;
	BILLBOARD  m_billboard;
	BOOL reload;

	//CTexture* slot2;
	CTexture* slot5;
	CTexture* SlotRt;
	CTexture* SlotRt2;
	CTexture* SlotEffect2;
	CTexture* SlotEffect3;
	CTexture* SlotEffect5;
	CTexture* m_Marronzinha;

	CTexture* m_SFire0;
	CTexture* m_SFire1;
	CTexture* m_SFire2;
	CTexture* m_SFire3;
	CTexture* m_SFire4;
	CTexture* m_SFire5;

	CTexture* m_DROP_Fire;
	bool      m_bFireFLASH;

	int          m_SFireALPHA0;
	int          m_DROPFireALPHA;

	int m_USEFireALPHA;

	CWndCustom   m_wndCustom[6];
	int          m_nFlashAlpha[MAX_SLOT_QUEUE];
	int          m_SlotEffectSoltaAL;
	bool         m_bFlash;
	float        EffectRotate;
	int          m_nActionSlot;

	DWORD        dwALPHA_M;

	int       m_nTime;
	CTimeSpan    m_ct;

	BOOL usedskill1, usedskill2, usedskill3, usedskill4, usedskill5;
	BOOL fusedskill1, fusedskill2, fusedskill3, fusedskill4, fusedskill5;
	BOOL useskill;
	float xPosition[6];
	float yPosition[6];
	float rotate1;
	float rotate2;
	float rotate3;
	float xPos, zPos;
	bool rot1;
	bool rot3;

	float RotateSLOT;
	float RotateAllEffect;
	float RotateSkillEffect;

	short	Time;
	CRect CTRECT[MAX_SLOT_QUEUE];

	int            m_SURF_FireALPHA[6];
	CTexture*	   m_SURF_FIRE[6];
	bool           m_bSURF_FireFLASH;

	bool m_RotateAtiv;

	bool m_bArrival;

	bool bRenderIllu[MAX_SLOT_QUEUE];

	LPWNDCTRL SlotCustom;

	CWndNewSkillSlot(void);
	~CWndNewSkillSlot(void);
	int rotate;

	virtual HRESULT RestoreDeviceObjects();
	virtual HRESULT InvalidateDeviceObjects();
	virtual HRESULT DeleteDeviceObjects();
private:
	CWndTaskBar_HUD*   pWndTaskBar_HUD;
	CWndTaskBar_HUD_EX2* CWndTaskBar_HUD_EX1;
	CWndNewSkillSlot* pWndNewSkillSlot;

public:
	clock_t m_tmCoolDown;
	clock_t m_tmStartCoolDown;
	bool	m_bStopCoolDown;
	int		RotateCoolDownEffect;
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnMouseWndSurface(CPoint point);
	virtual	BOOL Process();
	virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL OnDropIcon(LPSHORTCUT pShortcut, CPoint point = 0);
	virtual BOOL Initialize(CWndBase* pWndParent = NULL, DWORD nType = MB_OK);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnRButtonDown(UINT nFlags, CPoint point);
	virtual void OnDraw(C2DRender* p2DRender);
	virtual void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnRButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnInitialUpdate();
	virtual BOOL OnCommand(UINT nID, DWORD dwMessage, CWndBase* pWndBase);
	virtual void OnSize(UINT nType, int cx, int cy);
};
#endif // __NEW_TASKBAR_V19

class CWndShortcut : public CWndButton
{
public:
	CWndShortcut();
	~CWndShortcut();

	//BOOL Create(LPCTSTR lpszCaption,DWORD dwStyle,const RECT& rect,CWndBase* pParentWnd,UINT nID,CSprPack* pSprPack,int nSprIdx,int nColorTable = 0);
	//BOOL Create(LPCTSTR lpszCaption,DWORD dwStyle,const RECT& rect,CWndBase* pParentWnd,UINT nID);// { return Create(lpszCaption,dwStyle,rect,pParentWnd,nID,NULL,0); }
	virtual void OnDraw(C2DRender* p2DRender);
	virtual	BOOL Process();
	virtual	void PaintFrame( C2DRender* p2DRender );
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnRButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnRButtonDblClk(UINT nFlags, CPoint point);
	virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnMouseMove(UINT nFlags, CPoint point);

/*
	void SetMenu(CWndMenu* pWndMenu);

	// Attributes
	//BOOL IsButtonStyle( DWORD dwStyle ) { return ( m_dwButtonStyle & dwStyle ) ? TRUE : FALSE; }
	void SetPushTime(int nTime); // ��ư�� ������ nTime���Ŀ� ��� OnCommand�� �оƮ���� ������.
	UINT GetState() const; // Retrieves the check state, highlight state, and focus state of a button control.
	void SetState(BOOL bHighlight); // Sets the highlighting state of a button control
	int  GetCheck() const; // Retrieves the check state of a button control.
	void SetCheck(int nCheck); // Sets the check state of a button control.
	//UINT GetButtonStyle() const; // Retrieves information about the button control style.
	//void SetButtonStyle(UINT nStyle, BOOL bRedraw = TRUE); // Changes the style of a button.
	void SetString(CString strSndEffect); 
	BOOL IsHighLight() { return m_bHighLight; }
	void SetFontColor     (DWORD dwColor) { m_nFontColor      = (DWORD)dwColor; }
	void SetPushColor     (DWORD dwColor) { m_nPushColor      = (DWORD)dwColor; }
	void SetDisableColor  (DWORD dwColor) { m_nDisableColor   = (DWORD)dwColor; }
	void SetHighLightColor(DWORD dwColor) { m_nHighlightColor = (DWORD)dwColor; }
	DWORD GetFontColor     () { return m_nFontColor     ; }
	DWORD GetPushColor     () { return m_nPushColor     ; }
	DWORD GetDisableColor  () { return m_nDisableColor  ; }
	DWORD GetHighLightColor() { return m_nHighlightColor; }
	void SetWndExecute(CWndBase* pWndBase);
	CWndBase* GetWndExecute() { return m_pWndExecute; }
	void SetPushPoint(int x,int y) { m_ptPush = CPoint(x,y); }
	*/
};
class CWndQuickList : public CWndNeuz 
{ 
public: 
	CWndQuickList(); 
	~CWndQuickList(); 

	virtual BOOL Initialize( CWndBase* pWndParent = NULL, DWORD nType = MB_OK ); 
	virtual BOOL OnChildNotify( UINT message, UINT nID, LRESULT* pLResult ); 
	virtual void OnDraw( C2DRender* p2DRender ); 
	virtual	void OnInitialUpdate(); 
	virtual BOOL OnCommand( UINT nID, DWORD dwMessage, CWndBase* pWndBase ); 
	virtual void OnSize( UINT nType, int cx, int cy ); 
	virtual void OnLButtonUp( UINT nFlags, CPoint point ); 
	virtual void OnLButtonDown( UINT nFlags, CPoint point ); 
};

//////////////////////////////////////////////////////////////////////////////////////
// �۾� ���� 
// �޴� ��ư, ��� ������, ���� ������, Ȱ��ȭ ��� ���
//
class CWndTaskBar : public CWndNeuz
{
	DWORD m_dwHighAlpha;

public:
	BOOL		   IsShortcut( LPSHORTCUT lpShortcut, DWORD dwShortcut, DWORD dwId );
	CWndMenu       m_menuShortcut;
	CWndQuickList* m_pWndQuickList;
#ifdef __NEW_TASKBAR_V19
	CWndTaskBar_HUD     *pWndTaskBar_HUD;
	CWndTaskBar_HUD_EX3 *pWndTaskBar_HUD_EX3;
	CWndTaskBar_HUD_EX2 *pWndTaskBar_HUD_EX2;
	CWndTaskBar_HUD_EX1 *pWndTaskBar_HUD_EX1;
	CWndTaskBar_HUD_SLIDE*pWndTaskBar_HUD_SLIDE;
	CWndNewSkillSlot *pWndNewSkillSlot;
#endif // __NEW_TASKBAR_V19
	CTexturePack   m_texPack;
	CWndButton     m_wndMenu;
	CWndButton     m_wndQuickList;
	CWndButton     m_wndQuickListUp;
	CWndButton     m_wndQuickListDn;
	SHORTCUT       m_aSlotApplet[ MAX_SLOT_APPLET ]; // 1 ~ 20
	SHORTCUT       m_aSlotItem  [ MAX_SLOT_ITEM_COUNT ][ MAX_SLOT_ITEM ]; // 1 ~ 0(10)
	SHORTCUT       m_aSlotQueue [ MAX_SLOT_QUEUE  ];
	LPSHORTCUT     m_paSlotItem;
#ifdef __NEW_TASKBAR_V19
	BOOL m_changed;
#endif // __NEW_TASKBAR_V19
	LPSHORTCUT     m_pSelectShortcut;
	SHORTCUT       m_aSlotSkill;
	CTexture*      m_pTexture;
	int            m_nMaxSlotApplet;
	BOOL           m_bStartTimeBar;
	int            m_nUsedSkillQueue;
	int            m_nPosition;
	int            m_nSkillBar;
	int            m_nCurQueueNum;
	int            m_nCurQueue;
	CTimer         m_timer;
	int			   m_nExecute;		// 0: ���������� ���� 1:��������(��ų���� �޷�������) 2:������.
	OBJID		   m_idTarget;		// ��ų�����.
	int            m_nSlotIndex;
	int		       m_nActionPoint;		// �׼� ����Ʈ - �ø�������� ���.
#if __VER >= 12 // __LORD
	void RenderLordCollTime( CPoint pt, DWORD dwSkillId, C2DRender* p2DRender );
#endif
	void RenderCollTime( CPoint pt, DWORD dwSkillId, C2DRender* p2DRender );
	void UpdateItem();
	void PutTooTip( LPSHORTCUT pShortcut, CPoint point, CRect* pRect );
	void SetItemSlot( int nSlot );
	BOOL CheckAddSkill( int nSkillStyleSrc, int nQueueDest );
	BOOL UseSkillQueue( CCtrl* pTargetObj );
#ifdef 	__NEW_TASKBAR_V19
	BOOL UseSkillQueue1(CCtrl* pTargetObj);
#endif // __NEW_TASKBAR_V19
	LPSKILL GetCurrentSkillQueue();
	BOOL SetSkillQueue( int nIndex, DWORD dwType, DWORD dwId, CTexture* pTexture = NULL );
	BOOL SetShortcut( int nIndex, DWORD dwShortcut, DWORD dwType, DWORD dwId, CTexture* pTexture = NULL, int nWhere = 0 );
	void OnEndSkill( void );
	void OnCancelSkill( void );
	LPSHORTCUT Select( CPoint point );
	void RemoveSkillQueue( int nIndex, BOOL bSend = TRUE );
	BOOL RemoveDeleteObj();
	void InitTaskBar();

	CWndTaskBar();
	virtual ~CWndTaskBar();
//	virtual CItem* GetFocusItem() { return NULL; }
	virtual void OnDraw(C2DRender* p2DRender);
	virtual	void OnInitialUpdate();
	virtual BOOL Initialize(CWndBase* pWndParent = NULL,DWORD dwWndId = 0);
	// message
	virtual BOOL OnCommand( UINT nID, DWORD dwMessage, CWndBase* pWndBase );
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnRButtonUp(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnDropIcon( LPSHORTCUT pShortcut, CPoint point = 0 );
	virtual BOOL OnChildNotify(UINT message,UINT nID,LRESULT* pLResult);
	virtual	void PaintFrame( C2DRender* p2DRender );
	virtual BOOL OnEraseBkgnd(C2DRender* p2DRender);
	virtual BOOL Process();
	virtual void OnMouseWndSurface( CPoint point );
	virtual void OnMouseMove(UINT nFlags, CPoint point);
	virtual	void OnDestroyChildWnd( CWndBase* pWndChild );
	void	Serialize( CAr & ar );
	void	SetTaskBarTexture( LPSHORTCUT pShortcut );
	
	HRESULT	RestoreDeviceObjects();
	HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();
protected:
	void RenderOutLineLamp(int x, int y, int num, DWORD size);
};
//////////////////////////////////////////////////////////////////////////////////////
// �½�ũ���� �Ŵ� 
//
class CWndTaskMenu : public CWndMenu //Neuz
{
public:
	CWndTaskMenu();
	virtual ~CWndTaskMenu();
	void SetTexture( CWndButton* pWndButton );
//	virtual CItem* GetFocusItem() { return NULL; }
	virtual CWndButton* AppendMenu( CWndMenu* pWndMenu, UINT nFlags, UINT nIDNewItem, LPCTSTR lpszNewItem );
	virtual void OnDraw(C2DRender* p2DRender);
	virtual void PaintFrame(C2DRender* p2DRender);
	virtual BOOL OnEraseBkgnd(C2DRender* p2DRender);
	virtual	void OnInitialUpdate();
	virtual BOOL Initialize(CWndBase* pWndParent = NULL,DWORD dwWndId = 0);
	// message
	virtual BOOL OnCommand( UINT nID, DWORD dwMessage, CWndBase* pWndBase = NULL );
	virtual void OnSize(UINT nType, int cx, int cy);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnChildNotify(UINT message,UINT nID,LRESULT* pLResult);
	virtual BOOL Process();
	virtual void OnKillFocus(CWndBase* pNewWnd);
private:
	CWndMenu* m_pMenu1;
	CWndMenu* m_pMenu2;
	CWndMenu* m_pMenu3;
	CWndMenu* m_pMenu4;
	CWndMenu* m_pMenu5;
	CWndMenu* m_pMenu6;
	CWndMenu* m_pMenu7;
};
 
#endif // !defined(AFX_WNDTASKBAR_H__A93F3186_63D6_43C1_956F_EC8691E0C7D9__INCLUDED_)

