// dllmain.h : Declaration of module class.

class CLb3_autosvrModule : public ATL::CAtlDllModuleT< CLb3_autosvrModule >
{
public :
	DECLARE_LIBID(LIBID_Lb3_autosvrLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_LB3_AUTOSVR, "{699DA9D5-8A25-485F-AC8E-C1AB82DB07B2}")
};

extern class CLb3_autosvrModule _AtlModule;
