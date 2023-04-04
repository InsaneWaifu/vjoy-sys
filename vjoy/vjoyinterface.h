#define CALLBACK __stdcall

// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the VJOYINTERFACE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// VJOYINTERFACE_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef VJOYINTERFACE_EXPORTS
#define VJOYINTERFACE_API __declspec(dllexport)
#else
#define VJOYINTERFACE_API __declspec(dllimport)
#endif

#ifdef STATIC
#undef VJOYINTERFACE_API
#define VJOYINTERFACE_API
#endif

///////////////////////////// vJoy device (collection) status ////////////////////////////////////////////
#ifndef VJDSTAT
#define VJDSTAT
enum VjdStat  /* Declares an enumeration data type */
{
	VJD_STAT_OWN,	// The  vJoy Device is owned by this application.
	VJD_STAT_FREE,	// The  vJoy Device is NOT owned by any application (including this one).
	VJD_STAT_BUSY,	// The  vJoy Device is owned by another application. It cannot be acquired by this application.
	VJD_STAT_MISS,	// The  vJoy Device is missing. It either does not exist or the driver is down.
	VJD_STAT_UNKN	// Unknown
}; 

/* Error codes for some of the functions */
#define NO_HANDLE_BY_INDEX				 -1
#define BAD_PREPARSED_DATA				 -2
#define NO_CAPS				 			 -3
#define BAD_N_BTN_CAPS				 	 -4
#define BAD_CALLOC				 	 	 -5
#define BAD_BTN_CAPS				 	 -6
#define BAD_BTN_RANGE				 	 -7
#define BAD_N_VAL_CAPS				 	 -8
#define BAD_ID_RANGE				 	 -9
#define NO_SUCH_AXIS				 	 -10
#define BAD_DEV_STAT				 	 -11
#define NO_DEV_EXIST				 	 -12
#define NO_FILE_EXIST				 	 -13

/* Registry Constants */
#define REG_PARAM		L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters"
#define REG_PARAM_DEV0	L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters\\Device0"
#define REG_PARAM_DEV	L"SYSTEM\\CurrentControlSet\\services\\vjoy\\Parameters\\Device"
#define REG_DEVICE		L"Device"
#define REG_INIT		L"Init"
#define BTN_INIT		L"BTNS"

/* Environment Variables */
#define INTERFACE_LOG_LEVEL "VJOYINTERFACELOGLEVEL"
#define INTERFACE_LOG_FILE  "VJOYINTERFACELOGFILE"
#define INTERFACE_DEF_LOG_FILE	"vJoyInterface.log"

/* Compatibility definitions */
#define FFB_EFF_CONST 	FFB_EFF_REPORT
#define PFFB_EFF_CONST 	PFFB_EFF_REPORT
#define Ffb_h_Eff_Const Ffb_h_Eff_Report

// Device Axis/POVs/Buttons
struct DEVCTRLS {
	int Init;
	int	Rudder;
	int	Aileron;
	int	AxisX;
	int	AxisY;
	int	AxisZ;
	int	AxisXRot;
	int	AxisYRot;
	int	AxisZRot;
	int	Slider;
	int	Dial;
	int	Wheel;
	int	AxisVX;
	int	AxisVY;
	int	AxisVZ;
	int	AxisVBRX;
	int	AxisVBRY;
	int	AxisVBRZ;
	int		nButtons;	
	int		nDescHats;
	int		nContHats;
};

struct DeviceStat {
	void* h;								// Handle to the PDO interface that represents the virtual device
	enum VjdStat stat;							// Status of the device
	JOYSTICK_POSITION_V2 position;			// Current Position of the device
	void* hDeviceNotifyHandle;			// Device Notification Handle
	struct DEVCTRLS	DeviceControls;				// Structure Holding the data about the device's controls
	void*		 pPreParsedData;	// structure contains a top-level collection's preparsed data.
};

struct DEV_INFO {
	unsigned char	DeviceID;		// Device ID: Valid values are 1-16
	unsigned char	nImplemented;	// Number of implemented device: Valid values are 1-16
	unsigned char	isImplemented;	// Is this device implemented?
	unsigned char	MaxDevices;		// Maximum number of devices that may be implemented (16)
	unsigned char	DriverFFB;		// Does this driver support FFB (False)
	unsigned char	DeviceFFB;		// Does this device support FFB (False)
} ;



typedef void (CALLBACK *RemovalCB)(int, int, void*);


enum FFBEType // FFB Effect Type
{

	// Effect Type
	ET_NONE		=	0,	  //    No Force
	ET_CONST	=	1,    //    Constant Force
	ET_RAMP		=	2,    //    Ramp
	ET_SQR		=	3,    //    Square
	ET_SINE		=	4,    //    Sine
	ET_TRNGL	=	5,    //    Triangle
	ET_STUP		=	6,    //    Sawtooth Up
	ET_STDN		=	7,    //    Sawtooth Down
	ET_SPRNG	=	8,    //    Spring
	ET_DMPR		=	9,    //    Damper
	ET_INRT		=	10,   //    Inertia
	ET_FRCTN	=	11,   //    Friction
	ET_CSTM		=	12,   //    Custom Force Data
};

enum FFBPType // FFB Packet Type
{
	// Write
	PT_EFFREP	=  HID_ID_EFFREP,	// Usage Set Effect Report
	PT_ENVREP	=  HID_ID_ENVREP,	// Usage Set Envelope Report
	PT_CONDREP	=  HID_ID_CONDREP,	// Usage Set Condition Report
	PT_PRIDREP	=  HID_ID_PRIDREP,	// Usage Set Periodic Report
	PT_CONSTREP	=  HID_ID_CONSTREP,	// Usage Set Constant Force Report
	PT_RAMPREP	=  HID_ID_RAMPREP,	// Usage Set Ramp Force Report
	PT_CSTMREP	=  HID_ID_CSTMREP,	// Usage Custom Force Data Report
	PT_SMPLREP	=  HID_ID_SMPLREP,	// Usage Download Force Sample
	PT_EFOPREP	=  HID_ID_EFOPREP,	// Usage Effect Operation Report
	PT_BLKFRREP	=  HID_ID_BLKFRREP,	// Usage PID Block Free Report
	PT_CTRLREP	=  HID_ID_CTRLREP,	// Usage PID Device Control
	PT_GAINREP	=  HID_ID_GAINREP,	// Usage Device Gain Report
	PT_SETCREP	=  HID_ID_SETCREP,	// Usage Set Custom Force Report

	// Feature
	PT_NEWEFREP	=  HID_ID_NEWEFREP+0x10,	// Usage Create New Effect Report
	PT_BLKLDREP	=  HID_ID_BLKLDREP+0x10,	// Usage Block Load Report
	PT_POOLREP	=  HID_ID_POOLREP+0x10,		// Usage PID Pool Report
};

enum FFBOP
{
	EFF_START	= 1, // EFFECT START
	EFF_SOLO	= 2, // EFFECT SOLO START
	EFF_STOP	= 3, // EFFECT STOP
};

enum FFB_CTRL
{
	CTRL_ENACT		= 1,	// Enable all device actuators.
	CTRL_DISACT		= 2,	// Disable all the device actuators.
	CTRL_STOPALL	= 3,	// Stop All Effects� Issues a stop on every running effect.
	CTRL_DEVRST		= 4,	// Device Reset� Clears any device paused condition, enables all actuators and clears all effects from memory.
	CTRL_DEVPAUSE	= 5,	// Device Pause� The all effects on the device are paused at the current time step.
	CTRL_DEVCONT	= 6,	// Device Continue� The all effects that running when the device was paused are restarted from their last time step.
};

enum FFB_EFFECTS {
	Constant	= 0x0001,
	Ramp		= 0x0002,
	Square		= 0x0004,
	Sine		= 0x0008,
	Triangle	= 0x0010,
	Sawtooth_Up = 0x0020,
	Sawtooth_Dn = 0x0040,
	Spring		= 0x0080,
	Damper		= 0x0100,
	Inertia		= 0x0200,
	Friction	= 0x0400,
	Custom		= 0x0800,
};

typedef struct _FFB_DATA {
	unsigned long	size;
	unsigned long	cmd;
	unsigned char	*data;
} FFB_DATA, * PFFB_DATA;

typedef struct _FFB_EFF_CONSTANT { 
	unsigned char EffectBlockIndex; 
	long Magnitude; 			  // Constant force magnitude: 	-10000 - 10000
} FFB_EFF_CONSTANT, *PFFB_EFF_CONSTANT;

typedef struct _FFB_EFF_RAMP {
	unsigned char		EffectBlockIndex;
	long 		Start;             // The Normalized magnitude at the start of the effect (-10000 - 10000)
	long 		End;               // The Normalized magnitude at the end of the effect	(-10000 - 10000)
} FFB_EFF_RAMP, *PFFB_EFF_RAMP;

//typedef struct _FFB_EFF_CONST {
typedef struct _FFB_EFF_REPORT {
	unsigned char		EffectBlockIndex;
	enum FFBEType	EffectType;
	unsigned short		Duration;// Value in milliseconds. 0xFFFF means infinite
	unsigned short		TrigerRpt;
	unsigned short		SamplePrd;
	unsigned char		Gain;
	unsigned char		TrigerBtn;
	int		Polar; // How to interpret force direction Polar (0-360�) or Cartesian (X,Y)
	union
	{
		unsigned char	Direction; // Polar direction: (0x00-0xFF correspond to 0-360�)
		unsigned char	DirX; // X direction: Positive values are To the right of the center (X); Negative are Two's complement
	};
	unsigned char		DirY; // Y direction: Positive values are below the center (Y); Negative are Two's complement
} FFB_EFF_REPORT, *PFFB_EFF_REPORT;
//} FFB_EFF_CONST, *PFFB_EFF_CONST;

typedef struct _FFB_EFF_OP {
	unsigned char		EffectBlockIndex;
	enum FFBOP		EffectOp;
	unsigned char		LoopCount;
} FFB_EFF_OP, *PFFB_EFF_OP;

typedef struct _FFB_EFF_PERIOD {
	unsigned char		EffectBlockIndex;
	unsigned long		Magnitude;			// Range: 0 - 10000
	long 		Offset;				// Range: �10000 - 10000
	unsigned long 		Phase;				// Range: 0 - 35999
	unsigned long 		Period;				// Range: 0 - 32767
} FFB_EFF_PERIOD, *PFFB_EFF_PERIOD;

typedef struct _FFB_EFF_COND {
	unsigned char		EffectBlockIndex;
	int		isY;
	long 		CenterPointOffset; // CP Offset:  Range -�10000 �- 10000
	long 		PosCoeff; // Positive Coefficient: Range -�10000 �- 10000
	long 		NegCoeff; // Negative Coefficient: Range -�10000 �- 10000
	unsigned long 		PosSatur; // Positive Saturation: Range 0 � 10000
	unsigned long 		NegSatur; // Negative Saturation: Range 0 � 10000
	long 		DeadBand; // Dead Band: : Range 0 � 1000
} FFB_EFF_COND, *PFFB_EFF_COND;

typedef struct _FFB_EFF_ENVLP {
	unsigned char		EffectBlockIndex;
	unsigned long 		AttackLevel;   // The Normalized magnitude of the stating point: 0 - 10000
	unsigned long 		FadeLevel;	   // The Normalized magnitude of the stopping point: 0 - 10000
	unsigned long 		AttackTime;	   // Time of the attack: 0 - 4294967295
	unsigned long 		FadeTime;	   // Time of the fading: 0 - 4294967295
} FFB_EFF_ENVLP, *PFFB_EFF_ENVLP;

#define FFB_DATA_READY	 WM_USER+31

typedef void (CALLBACK *FfbGenCB)(void*, void*);
#endif
	///////////////////////////// vJoy device (collection) Control interface /////////////////////////////////
	/*
		These functions allow writing feeders and other applications that interface with vJoy
		It is assumed that only one vJoy top-device (= Raw PDO) exists.
		This top-level device can have up to 16 siblings (=top-level Reports/collections)
		Each sibling is refered to as a "vJoy Device" and is attributed a unique Report ID (Range: 1-16).

		Naming convetion:
			VJD = vJoy Device
			rID = Report ID
	*/
#pragma warning( push )
#pragma warning( disable : 4995 )
	/////	General driver data
	VJOYINTERFACE_API short __cdecl GetvJoyVersion(void);
	VJOYINTERFACE_API int	__cdecl vJoyEnabled(void);
	VJOYINTERFACE_API void*	__cdecl	GetvJoyProductString(void);
	VJOYINTERFACE_API void*	__cdecl	GetvJoyManufacturerString(void);
	VJOYINTERFACE_API void*	__cdecl	GetvJoySerialNumberString(void);
	VJOYINTERFACE_API int	__cdecl	DriverMatch(unsigned short * DllVer, unsigned short * DrvVer);
	VJOYINTERFACE_API void	__cdecl	RegisterRemovalCB(RemovalCB cb, void* data);
	VJOYINTERFACE_API int	__cdecl	vJoyFfbCap(int * Supported);	// Is this version of vJoy capable of FFB?
	VJOYINTERFACE_API int	__cdecl	GetvJoyMaxDevices(int * n);	// What is the maximum possible number of vJoy devices
	VJOYINTERFACE_API int	__cdecl	GetNumberExistingVJD(int * n);	// What is the number of vJoy devices currently enabled


	/////	vJoy Device properties
	VJOYINTERFACE_API int	__cdecl  GetVJDButtonNumber(unsigned int rID);	// Get the number of buttons defined in the specified VDJ
	VJOYINTERFACE_API int	__cdecl  GetVJDDiscPovNumber(unsigned int rID);	// Get the number of descrete-type POV hats defined in the specified VDJ
	VJOYINTERFACE_API int	__cdecl  GetVJDContPovNumber(unsigned int rID);	// Get the number of descrete-type POV hats defined in the specified VDJ
	VJOYINTERFACE_API int	__cdecl  GetVJDAxisExist(unsigned int rID, unsigned int Axis); // Test if given axis defined in the specified VDJ
	VJOYINTERFACE_API int	__cdecl  GetVJDAxisMax(unsigned int rID, unsigned int Axis, long * Max); // Get logical Maximum value for a given axis defined in the specified VDJ
	VJOYINTERFACE_API int	__cdecl  GetVJDAxisMin(unsigned int rID, unsigned int Axis, long * Min); // Get logical Minimum value for a given axis defined in the specified VDJ
	VJOYINTERFACE_API enum VjdStat	__cdecl	GetVJDStatus(unsigned int rID);			// Get the status of the specified vJoy Device.
	// Added in 2.1.6
	VJOYINTERFACE_API int	__cdecl	isVJDExists(unsigned int rID);					// TRUE if the specified vJoy Device exists																			
	// Added in 2.1.8
	VJOYINTERFACE_API int	__cdecl	GetOwnerPid(unsigned int rID);					// Reurn owner's Process ID if the specified vJoy Device exists


	/////	Write access to vJoy Device - Basic
	VJOYINTERFACE_API int		__cdecl	AcquireVJD(unsigned int rID);				// Acquire the specified vJoy Device.
	VJOYINTERFACE_API void		__cdecl	RelinquishVJD(unsigned int rID);			// Relinquish the specified vJoy Device.
	VJOYINTERFACE_API int		__cdecl	UpdateVJD(unsigned int rID, void* pData);	// Update the position data of the specified vJoy Device.

	/////	Write access to vJoy Device - Modifyiers
	// This group of functions modify the current value of the position data
	// They replace the need to create a structure of position data then call UpdateVJD

	//// Reset functions
	VJOYINTERFACE_API int		__cdecl	ResetVJD(unsigned int rID);			// Reset all controls to predefined values in the specified VDJ
	VJOYINTERFACE_API void		__cdecl	ResetAll(void);				// Reset all controls to predefined values in all VDJ
	VJOYINTERFACE_API int		__cdecl	ResetButtons(unsigned int rID);		// Reset all buttons (To 0) in the specified VDJ
	VJOYINTERFACE_API int		__cdecl	ResetPovs(unsigned int rID);		// Reset all POV Switches (To -1) in the specified VDJ

	// Write data
	VJOYINTERFACE_API int		__cdecl	SetAxis(long Value, unsigned int rID, unsigned int Axis);		// Write Value to a given axis defined in the specified VDJ 
	VJOYINTERFACE_API int		__cdecl	SetBtn(int Value, unsigned int rID, unsigned char nBtn);		// Write Value to a given button defined in the specified VDJ 
	VJOYINTERFACE_API int		__cdecl	SetDiscPov(int Value, unsigned int rID, unsigned char nPov);	// Write Value to a given descrete POV defined in the specified VDJ 
	VJOYINTERFACE_API int		__cdecl	SetContPov(unsigned long Value, unsigned int rID, unsigned char nPov);	// Write Value to a given continuous POV defined in the specified VDJ 


#pragma region FFB Function prototypes
// Force Feedback (FFB) functions
	VJOYINTERFACE_API enum FFBEType	__cdecl	FfbGetEffect();	// Returns effect serial number if active, 0 if inactive
	VJOYINTERFACE_API void		__cdecl	FfbRegisterGenCB(FfbGenCB cb, void* data);
	__declspec(deprecated("** FfbStart function was deprecated - you can remove it from your code **")) \
		VJOYINTERFACE_API int		__cdecl	FfbStart(unsigned int rID);				  // Start the FFB queues of the specified vJoy Device.
	__declspec(deprecated("** FfbStop function was deprecated - you can remove it from your code **")) \
		VJOYINTERFACE_API void		__cdecl	FfbStop(unsigned int rID);				  // Stop the FFB queues of the specified vJoy Device.

		// Added in 2.1.6
	VJOYINTERFACE_API int		__cdecl	IsDeviceFfb(unsigned int rID);
	VJOYINTERFACE_API int		__cdecl	IsDeviceFfbEffect(unsigned int rID, unsigned int Effect);

	//  Force Feedback (FFB) helper functions
	VJOYINTERFACE_API unsigned long 	__cdecl	Ffb_h_DeviceID(const FFB_DATA * Packet, int *DeviceID);
	VJOYINTERFACE_API unsigned long 	__cdecl Ffb_h_Type(const FFB_DATA * Packet, enum FFBPType *Type);
	VJOYINTERFACE_API unsigned long 	__cdecl Ffb_h_Packet(const FFB_DATA * Packet, unsigned short *Type, int *DataSize, unsigned char *Data[]);
	VJOYINTERFACE_API unsigned long 	__cdecl Ffb_h_EBI(const FFB_DATA * Packet, int *Index);
	VJOYINTERFACE_API unsigned long 	__cdecl Ffb_h_Eff_Report(const FFB_DATA * Packet, FFB_EFF_REPORT*  Effect);
	__declspec(deprecated("** Ffb_h_Eff_Const function was deprecated - Use function Ffb_h_Eff_Report **")) \
	VJOYINTERFACE_API unsigned long 	__cdecl Ffb_h_Eff_Const(const FFB_DATA * Packet, FFB_EFF_CONST*  Effect);
	VJOYINTERFACE_API unsigned long		__cdecl Ffb_h_Eff_Ramp(const FFB_DATA * Packet, FFB_EFF_RAMP*  RampEffect);
	VJOYINTERFACE_API unsigned long 	__cdecl Ffb_h_EffOp(const FFB_DATA * Packet, FFB_EFF_OP*  Operation);
	VJOYINTERFACE_API unsigned long 	__cdecl Ffb_h_DevCtrl(const FFB_DATA * Packet, enum FFB_CTRL *  Control);
	VJOYINTERFACE_API unsigned long 	__cdecl Ffb_h_Eff_Period(const FFB_DATA * Packet, FFB_EFF_PERIOD*  Effect);
	VJOYINTERFACE_API unsigned long 	__cdecl Ffb_h_Eff_Cond(const FFB_DATA * Packet, FFB_EFF_COND*  Condition);
	VJOYINTERFACE_API unsigned long 	__cdecl Ffb_h_DevGain(const FFB_DATA * Packet, unsigned char * Gain);
	VJOYINTERFACE_API unsigned long		__cdecl Ffb_h_Eff_Envlp(const FFB_DATA * Packet, FFB_EFF_ENVLP*  Envelope);
	VJOYINTERFACE_API unsigned long		__cdecl Ffb_h_EffNew(const FFB_DATA * Packet, enum FFBEType * Effect);

	// Added in 2.1.6
	VJOYINTERFACE_API unsigned long		__cdecl Ffb_h_Eff_Constant(const FFB_DATA * Packet, FFB_EFF_CONSTANT *  ConstantEffect);
#pragma endregion

#pragma warning( pop )
