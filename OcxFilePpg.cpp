// OcxFilePpg.cpp : Implementation of the COcxFilePropPage property page class.

#include "stdafx.h"
#include "OcxFile.h"
#include "OcxFilePpg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(COcxFilePropPage, COlePropertyPage)


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(COcxFilePropPage, COlePropertyPage)
	//{{AFX_MSG_MAP(COcxFilePropPage)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(COcxFilePropPage, "OCXFILE.OcxFilePropPage.1",
	0x7d2db8c5, 0x70ec, 0x4341, 0xa5, 0x20, 0xb3, 0x6c, 0x95, 0xe6, 0x52, 0x6b)


/////////////////////////////////////////////////////////////////////////////
// COcxFilePropPage::COcxFilePropPageFactory::UpdateRegistry -
// Adds or removes system registry entries for COcxFilePropPage

BOOL COcxFilePropPage::COcxFilePropPageFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterPropertyPageClass(AfxGetInstanceHandle(),
			m_clsid, IDS_OCXFILE_PPG);
	else
		return AfxOleUnregisterClass(m_clsid, NULL);
}


/////////////////////////////////////////////////////////////////////////////
// COcxFilePropPage::COcxFilePropPage - Constructor

COcxFilePropPage::COcxFilePropPage() :
	COlePropertyPage(IDD, IDS_OCXFILE_PPG_CAPTION)
{
	//{{AFX_DATA_INIT(COcxFilePropPage)
	// NOTE: ClassWizard will add member initialization here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_INIT
}


/////////////////////////////////////////////////////////////////////////////
// COcxFilePropPage::DoDataExchange - Moves data between page and properties

void COcxFilePropPage::DoDataExchange(CDataExchange* pDX)
{
	//{{AFX_DATA_MAP(COcxFilePropPage)
	// NOTE: ClassWizard will add DDP, DDX, and DDV calls here
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA_MAP
	DDP_PostProcessing(pDX);
}


/////////////////////////////////////////////////////////////////////////////
// COcxFilePropPage message handlers
