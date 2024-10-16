#pragma once
class IConcentration :public IUnknown
{
public:
	//IConcentration specific methods
	virtual HRESULT __stdcall ConcentrationOfSoluteByMass(float, float, float *) = 0;	
	virtual HRESULT __stdcall ConcentrationOfSoluteByVolume(float, float, float *) = 0;
};

class IMoleFraction :public IUnknown
{
public:
	virtual HRESULT __stdcall MoleFractionOfSolvent(float, float, float *) = 0;
	virtual HRESULT __stdcall MoleFractionOfSolute(float, float, float *) = 0;
};

class IMolarity :public IUnknown
{
public:
	virtual HRESULT __stdcall Molarity(float, float,float, float *) = 0;
};

class IMolality :public IUnknown
{
public:
	virtual HRESULT __stdcall Molality(float, float, float,float *) = 0;
};

//CLSID of SolutionProperties component // {27179315-0CC5-422C-A6AA-C0D50BA94D39}*
const CLSID CLSID_SolutionProperties = { 0x27179315, 0xcc5, 0x422c, 0xa6, 0xaa, 0xc0, 0xd5, 0xb, 0xa9, 0x4d, 0x39 };

//IID of IConcentration Interface // {E05EFABE-7B7A-41A2-A48A-5F779F5FE5F3}*
const IID IID_IConcentration = { 0xe05efabe, 0x7b7a, 0x41a2, 0xa4, 0x8a, 0x5f, 0x77, 0x9f, 0x5f, 0xe5, 0xf3 };

//IID of IMoleFraction Interface {0461CA62-FBBF-42F2-8017-570EF70D0E9C}*
const IID IID_IMoleFraction = { 0x461ca62, 0xfbbf, 0x42f2, 0x80, 0x17, 0x57, 0xe, 0xf7, 0xd, 0xe, 0x9c };

//IID of IMolarity Interface // {09925C79-8137-4F99-8925-88E35DB6CB0F}*
const IID IID_IMolarity = { 0x9925c79, 0x8137, 0x4f99, 0x89, 0x25, 0x88, 0xe3, 0x5d, 0xb6, 0xcb, 0xf };

//IID of IMolality Interface // {55FE97AE-BFF6-474E-A6D3-851540CC349F}*
const IID IID_IMolality = { 0x55fe97ae, 0xbff6, 0x474e, 0xa6, 0xd3, 0x85, 0x15, 0x40, 0xcc, 0x34, 0x9f };

