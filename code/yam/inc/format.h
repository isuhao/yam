#ifndef Y_FORMAT_H
#define Y_FORMAT_H

#include "common.h"

#include "tree.h"

namespace yam{ namespace base{

class YIFormat : public YITree<YIFormat>
{
public:
	virtual ~YIFormat() { ; }

public:
	virtual GET_DECL_CONST(YRect2D&, GetBound) = 0;
	virtual GET_DECL_CONST(ycolorptr&, GetColorData) = 0;
	virtual void SetBoundAndColorData(const YRect2D& rstBound, ycolorptr pColorData) = 0;
};

template<typename TNBase, typename TNReal>
class YTFormat : public YTTree<TNBase, YIFormat, TNReal>
{
public:
	YTFormat() : m_pColorData(YNULL) { ; }
	virtual ~YTFormat() { ; }

public:
	virtual GET_FUNC_CONST(YRect2D&, GetBound, m_stBound);
	virtual GET_FUNC_CONST(ycolorptr&, GetColorData, m_pColorData);
	virtual void SetBoundAndColorData(const YRect2D& rstBound, ycolorptr pColorData)
	{
		//
	}

protected:
	YRect2D		m_stBound;
	ycolorptr	m_pColorData;
};

class YCFormat : public YTFormat<YIFormat, YCFormat>
{
	YOBJECT_DECL(YCFormat);

public:
	YCFormat();
	virtual ~YCFormat();

public:
	virtual bool operator>>(base::YCBuffer& rBuffer) const;
	virtual bool operator<<(base::YCBuffer& rBuffer);

public:
	virtual void SetBoundAndColorData(const YRect2D& rstBound, ycolorptr pColorData);

private:
	void SetColorData(const yint32& riSize, const ycolorptr& rpColorData);
};

}}

#endif // Y_FORMAT_H