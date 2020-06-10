//-----------------------------------------------------------------------------
//
// DESCRIPTION:
//              Simple basic typedefs, isolated here to make it easier
//               separating modules.
//        
//-----------------------------------------------------------------------------


#ifndef __DOOMTYPE__
#define __DOOMTYPE__

#ifdef _MSC_VER
// VC++ does not define PATH_MAX, but the Windows headers do define MAX_PATH.
// However, we want to avoid including the Windows headers in most of the
// source files, so we can't use it. So define PATH_MAX to be what MAX_PATH
// currently is:
#define PATH_MAX 260

// Disable warning about using unsized arrays in structs. It supports it just
// fine, and so do Clang and GCC, but the latter two don't warn about it.
#pragma warning(disable:4200)
#endif

#include <limits.h>
#include <tuple>
#include <algorithm>
#include "tarray.h"
#include "name.h"
#include "zstring.h"
#include "cmdlib.h"

class PClassActor;
typedef TMap<int, PClassActor *> FClassMap;


#if defined(_MSC_VER)
#define NOVTABLE __declspec(novtable)
#else
#define NOVTABLE
#endif

#if defined(__GNUC__)
// With versions of GCC newer than 4.2, it appears it was determined that the
// cost of an unaligned pointer on PPC was high enough to add padding to the
// end of packed structs.  For whatever reason __packed__ and pragma pack are
// handled differently in this regard. Note that this only needs to be applied
// to types which are used in arrays or sizeof is needed. This also prevents
// code from taking references to the struct members.
#define FORCE_PACKED __attribute__((__packed__))
#else
#define FORCE_PACKED
#endif

#include "basics.h"
#include "printf.h"

extern bool batchrun;

// Bounding box coordinate storage.
#include "palentry.h"

enum class ETextureType : uint8_t
{
	Any,
	Wall,
	Flat,
	Sprite,
	WallPatch,
	Build,		// no longer used but needs to remain for ZScript
	SkinSprite,
	Decal,
	MiscPatch,
	FontChar,
	Override,	// For patches between TX_START/TX_END
	Autopage,	// Automap background - used to enable the use of FAutomapTexture
	SkinGraphic,
	Null,
	FirstDefined,
	SWCanvas,
};

class FTextureID
{
	friend class FTextureManager;
	friend void R_InitSpriteDefs();

public:
	FTextureID() = default;
	bool isNull() const { return texnum == 0; }
	bool isValid() const { return texnum > 0; }
	bool Exists() const { return texnum >= 0; }
	void SetInvalid() { texnum = -1; }
	void SetNull() { texnum = 0; }
	bool operator ==(const FTextureID &other) const { return texnum == other.texnum; }
	bool operator !=(const FTextureID &other) const { return texnum != other.texnum; }
	FTextureID operator +(int offset) throw();
	int GetIndex() const { return texnum; }	// Use this only if you absolutely need the index!

											// The switch list needs these to sort the switches by texture index
	int operator -(FTextureID other) const { return texnum - other.texnum; }
	bool operator < (FTextureID other) const { return texnum < other.texnum; }
	bool operator > (FTextureID other) const { return texnum > other.texnum; }

protected:
	FTextureID(int num) { texnum = num; }
private:
	int texnum;
};

// This is for the script interface which needs to do casts from int to texture.
class FSetTextureID : public FTextureID
{
public:
	FSetTextureID(int v) : FTextureID(v) {}
};


struct VersionInfo
{
	uint16_t major;
	uint16_t minor;
	uint32_t revision;

	bool operator <=(const VersionInfo &o) const
	{
		return o.major > this->major || (o.major == this->major && o.minor > this->minor) || (o.major == this->major && o.minor == this->minor && o.revision >= this->revision);
	}
	bool operator >=(const VersionInfo &o) const
	{
		return o.major < this->major || (o.major == this->major && o.minor < this->minor) || (o.major == this->major && o.minor == this->minor && o.revision <= this->revision);
	}
	bool operator > (const VersionInfo &o) const
	{
		return o.major < this->major || (o.major == this->major && o.minor < this->minor) || (o.major == this->major && o.minor == this->minor && o.revision < this->revision);
	}
	bool operator < (const VersionInfo &o) const
	{
		return o.major > this->major || (o.major == this->major && o.minor > this->minor) || (o.major == this->major && o.minor == this->minor && o.revision > this->revision);
	}
	void operator=(const char *string);
};

// Cannot be a constructor because Lemon would puke on it.
inline VersionInfo MakeVersion(unsigned int ma, unsigned int mi, unsigned int re = 0)
{
	return{ (uint16_t)ma, (uint16_t)mi, (uint32_t)re };
}

enum class ELightMode : int8_t
{
	NotSet = -1,
	LinearStandard = 0,
	DoomBright = 1,
	Doom = 2,
	DoomDark = 3,
	DoomLegacy = 4,
	ZDoomSoftware = 8,
	DoomSoftware = 16
};

// always use our own definition for consistency.
#ifdef M_PI
#undef M_PI
#endif

const double M_PI = 3.14159265358979323846;	// matches value in gcc v2 math.h

inline float DEG2RAD(float deg)
{
	return deg * float(M_PI / 180.0);
}

inline double DEG2RAD(double deg)
{
	return deg * (M_PI / 180.0);
}

inline float RAD2DEG(float deg)
{
	return deg * float(180. / M_PI);
}


// Auto-registration sections for GCC.
// Apparently, you cannot do string concatenation inside section attributes.
#ifdef __MACH__
#define SECTION_AREG "__DATA,areg"
#define SECTION_CREG "__DATA,creg"
#define SECTION_FREG "__DATA,freg"
#define SECTION_GREG "__DATA,greg"
#define SECTION_MREG "__DATA,mreg"
#define SECTION_YREG "__DATA,yreg"
#else
#define SECTION_AREG "areg"
#define SECTION_CREG "creg"
#define SECTION_FREG "freg"
#define SECTION_GREG "greg"
#define SECTION_MREG "mreg"
#define SECTION_YREG "yreg"
#endif

#endif
