/**
@file
Header which defines structures for handling EPT translations

@date 1/17/2012
***************************************************************/

#ifndef _MORE_EPT_H_
#define _MORE_EPT_H_


#define	PML4_BASE	0xFFFFF6FB7DBED000
#define	PDP_BASE	0xFFFFF6FB7DA00000
#define	PD_BASE		0xFFFFF6FB40000000
#define	PT_BASE		0xFFFFF68000000000

#pragma pack(push, ept, 1)
struct EptTablePointer_s
{

	ULONG64 MemoryType : 3;//2
	ULONG64 PageWalkLength : 3;//5
	ULONG64 D : 1;//6
	ULONG64 reserved : 5;//11
	ULONG64 PhysAddr : 28;//39
	ULONG64 reserved2 : 24;//63
};

union EptTablePointer_u
{
	ULONG64 unsignedVal;
	struct EptTablePointer_s Bits;
};

typedef union EptTablePointer_u EptTablePointer;

struct EptPml4Entry_s
{
	ULONG64 Read : 1; // If the 512 GB region is Read (read access)
	ULONG64 Write : 1; // If the 512 GB region is writable
	ULONG64 Execute : 1; // If the 512 GB region is executable
	ULONG64 reserved1 : 9; // Reserved
	ULONG64 PhysAddr : 28; // Physical address
	ULONG64 reserved2 : 24; // Reserved
};

typedef struct EptPml4Entry_s EptPml4Entry;

struct EptPdpteEntry_s
{
	ULONG64 Read : 1; // If the 1 GB region is Read (read access)
	ULONG64 Write : 1; // If the 1 GB region is writable
	ULONG64 Execute : 1; // If the 1 GB region is executable
	ULONG64 reserved1 : 9; // Reserved
	ULONG64 PhysAddr : 28; // Physical address
	ULONG64 reserved2 : 24; // Reserved
};

typedef struct EptPdpteEntry_s EptPdpteEntry;

struct EptPdeEntry_s
{
	ULONG64 Read : 1; // If the 2 MB region is Read (read access)
	ULONG64 Write : 1; // If the 2 MB region is writable
	ULONG64 Execute : 1; // If the 2 MB region is executable
	ULONG64 reserved1 : 9; // Reserved
	ULONG64 PhysAddr : 28; // Physical address
	ULONG64 reserved2 : 24; // Reserved
};

typedef struct EptPdeEntry_s EptPdeEntry;

struct EptPteEntry_s
{
	ULONG64 Read : 1; // If the 1 GB region is Read (read access)
	ULONG64 Write : 1; // If the 1 GB region is writable
	ULONG64 Execute : 1; // If the 1 GB region is executable
	ULONG64 MemoryType : 3; // EPT Memory type
	ULONG64 IgnorePat : 1; // Flag for whether to ignore PAT
	ULONGLONG LargePage : 1;//7ҳ��ߴ�λ
	ULONGLONG Accessed : 1;//// 8����״̬ ��ҳδ����/д��=0 ��ҳ�ѱ���/д��=1

	ULONGLONG Dirty : 1;//// 9��ҳ״̬ ��ҳδ���Ķ���=0 ��ҳ�ѱ��Ķ���=1

	ULONGLONG reserved1 : 2;//11
	ULONG64 PhysAddr : 28; // Physical address
	ULONG64 reserved2 : 24; // Reserved
};

typedef struct EptPteEntry_s EptPteEntry;

typedef struct _EPT_ATTRIBUTE_PAE {
	ULONGLONG Read : 1;      //0��
	ULONGLONG Write : 1;     //1д
	ULONGLONG Execute : 1;  //2ִ��
	ULONGLONG ReadAble : 1; //3Ϊ1ʱ���ʾGPA�ɶ�
	ULONGLONG WriteAble : 1;   //4Ϊ1ʱ���ʾGPA��д
	ULONGLONG ExecuteAble : 1;//5Ϊ1ʱ���ʾGPA��ִ��
	ULONGLONG reserved : 1;//// 6����
	ULONGLONG Valid : 1;//Ϊ1ʱ 7��������һ�����Ե�ַ
	ULONGLONG TranSlation : 1;////8Ϊ1ʱ����EPT VIOLATION������GPAתHPA Ϊ0���������ڶ�guest paging-stucture���ַ��ʻ���
	ULONGLONG reserved2 : 1;//9���� Ϊ0
	ULONGLONG NMIunblocking : 1;//10Ϊ1����ִ����IRETָ�����NMI�����Ѿ����
	ULONGLONG reserved3 : 1;//11
	ULONGLONG reserved4 : 13;//23:11
	ULONGLONG GET_PTE : 1;//24
	ULONGLONG GET_PAGE_FRAME : 1;//25
	ULONGLONG FIX_ACCESS : 1;//26Ϊ1ʱ ����access ringht�޸�����
	ULONGLONG FIX_MISCONF : 1;//27Ϊ1ʱ ����misconfiguration�޸�����
	ULONGLONG FIX_FIXING : 1;//28Ϊ1ʱ �޸� Ϊ0ӳ��
	ULONGLONG EPT_FORCE : 1;//29Ϊ1ʱ ǿ�ƽ���ӳ��
	ULONGLONG reserved5 : 1;
} EPT_ATTRIBUTE_PAGE, *PEPT_ATTRIBUTE_PAGE;
#pragma pack(pop, ept)

#pragma  pack(push,1)
typedef struct _EPTREWATCHINFO
{
	EptPteEntry* pPte;
	EptPteEntry pOldPte;
	PVOID pHookedAddress;
	PVOID pJmpAddress;
	PVOID64 pContext;
}EPTREWATCHINFO,*PEPTREWATCHINFO;
#pragma  pack(pop)
typedef struct _EPTHOOKITEM
{
	EptPteEntry* pPte;
	EptPteEntry pOldPte;

	PVOID pHookedVA;
	PVOID pJmpVA;
	PHYSICAL_ADDRESS pPA;

	BOOLEAN bDisabled;
	ULONG64 nHitCount;
	char szName[100];
}EPTHOOKITEM,*PEPTHOOKITEM;

/** Intel-defined EPT memory types */
enum EPT_MEMORY_TYPE_E
{
	EPT_MEMORY_TYPE_UC = 0,
	EPT_MEMORY_TYPE_WC = 1,
	EPT_MEMORY_TYPE_WT = 4,
	EPT_MEMORY_TYPE_WP = 5,
	EPT_MEMORY_TYPE_WB = 6,
};

typedef enum EPT_MEMORY_TYPE_E EPT_MEMORY_TYPE;

/** Boolean for whether or not to split the TLB */
#define SPLIT_TLB 1
/** Maximum addressing width for the processor */
#define PHYSICAL_ADDRESS_WIDTH 36
/** Guest VPID value (must be non-zero) */
#define VM_VPID 1

/** Number of pages to pre-allocate for later use */
#define NUM_PAGES_ALLOC 1024


// Defines for parsing the EPT violation exit qualification
/** Bitmask for data read violation */
#define EPT_MASK_DATA_READ 0x1
/** Bitmask for data write violation */
#define EPT_MASK_DATA_WRITE (1 << 1)
/** Bitmask for data execute violation */
#define EPT_MASK_DATA_EXEC (1 << 2)
/** Bitmask for if the guest linear address is valid */
#define EPT_MASK_GUEST_LINEAR_VALID (1 << 7)

#endif

// This function can load our ept page system.
EptPml4Entry* EptInitialization();

// Release All EPT Pages
BOOLEAN EptReleasePages();

// We can get a physcial address with a PA
// If it is a usermode address,please change the cr3 and then MmGetPhysicalAddress to get its PA
EptPteEntry* EptGetPteAddressByPA(IN PHYSICAL_ADDRESS PA);

PVOID EptAllocateNewPage();

// To refresh the ept page
void EptInvept();

// Handle EPT Violation Event
void HandleEptViolation();
// Handle EPT Misconfig Event(remark:If it hit this function,it means that the PML4T is error.)
void HandleEptMisconfig();
// Handle MTF to rewat
void HandleMTF();

void EnableMTF();
void DisableMTF();

VOID EnableTF();
VOID DisableTF();

// Add a EPTHook Item
int AddEPTHookItem(IN PEPTHOOKITEM pItem);

// Remove a EPTHook Item
BOOLEAN RemoveEPTHookItem(IN int uItemID);

// Set Rewatch Information
PEPTREWATCHINFO SetRewathInfo(IN EptPteEntry* pPte, IN EptPteEntry pOldPte, IN PVOID64 pContext);
