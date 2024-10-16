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
	virtual HRESULT __stdcall Molarity(float, float,float, float *) = 0;
};

class IMolality :public IUnknown
{
	virtual HRESULT __stdcall Molality(float, float, float,float *) = 0;
};

//CLSID of SolutionProperties component // {57CEE278-81F2-43F3-8E73-A9260BD7751E}*
const CLSID CLSID_SolutionProperties = { 0x57cee278, 0x81f2, 0x43f3, 0x8e, 0x73, 0xa9, 0x26, 0xb, 0xd7, 0x75, 0x1e };

//IID of IConcentration Interface // {1464E1FE-E184-423B-97DA-676C1D990519}*
const IID IID_IConcentration = { 0x1464e1fe, 0xe184, 0x423b, 0x97, 0xda, 0x67, 0x6c, 0x1d, 0x99, 0x5, 0x19 };

//IID of IMoleFraction Interface // {FF6EA09C-0A32-44AF-AB2D-0522521AAFFF}*
const IID IID_IMoleFraction = { 0xff6ea09c, 0xa32, 0x44af, 0xab, 0x2d, 0x5, 0x22, 0x52, 0x1a, 0xaf, 0xff };

//IID of IMolarity Interface // {6AD7CF71-EF03-496D-A5C8-C4E902F56E7C}*
const IID IID_IMolarity = { 0x6ad7cf71, 0xef03, 0x496d, 0xa5, 0xc8, 0xc4, 0xe9, 0x2, 0xf5, 0x6e, 0x7c };

//IID of IMolality Interface // {2AC03E08-DAAE-4FA0-828E-D0D0AC7B3280}*
const IID IID_IMolality = { 0x2ac03e08, 0xdaae, 0x4fa0, 0x82, 0x8e, 0xd0, 0xd0, 0xac, 0x7b, 0x32, 0x80 };
