#ifndef cmdDef_h__
#define cmdDef_h__

namespace StateDataCMD
{
	typedef struct stPlaneState
	{
		enum
		{
			Start = 0x10,
			Stop
		};
		int nCode;

		stPlaneState()
		{
			nCode = Start;
		}
	}PlaneState;


}

#endif // cmdDef_h__
