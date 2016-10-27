#ifndef _COMMON_FUNC_
#define _COMMON_FUNC_

#include <osg/Node>
#include <osg/Drawable>
#include <osg/StateSet>

#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

#include <KGUtils/Export.h>

namespace KGUtil
{
	/// �ַ����б�
	typedef std::vector<std::string> string_list;

	/// ��Ⱦ˳��
	typedef enum ERenderBin
	{
		ERenderBin_GEOM = 1,
		ERenderBin_CLOUDS,
		ERenderBin_LABEL,
		//��ö��ȷ�������ڵ����Ⱦ˳��
	}ERenderBin;

	/// ����͸��״̬
	struct KGUTIL_EXPORT ActivateTransparencyOnType
	{
		ActivateTransparencyOnType(const std::type_info& t, const ERenderBin renderorder);
		void operator()(osg::Node* nptr) const;
		const std::type_info&  _t;
		const ERenderBin _renderorder;
	protected:
		ActivateTransparencyOnType& operator = (const ActivateTransparencyOnType&) { return *this; }
	};

	/// �ر�͸��״̬
	struct KGUTIL_EXPORT DeactivateTransparencyOnType
	{
		DeactivateTransparencyOnType(const std::type_info& t, const ERenderBin renderorder);
		void operator()(osg::Node* nptr) const;
	
		const std::type_info&  _t;
		const ERenderBin _renderorder;
	protected:
		DeactivateTransparencyOnType& operator = (const DeactivateTransparencyOnType&) { return *this; }
	};
	///�����ر�͸���Ⱥ�������Ⱦ˳��ĺ�
#define ACTIVE_TRANSPARENCY(_typename_, _render_order_, _nptr_)  ActivateTransparencyOnType(_typename_, _render_order_)(_nptr_)
#define DEACTIVE_TRANSPARENCY(_typename_, _render_order_,  _nptr_)  DeactivateTransparencyOnType(_typename_, _render_order_)(_nptr_)

	//////////////////////////////////////////////////////////////////////////
	//��ͨ����
	//////////////////////////////////////////////////////////////////////////
#define KG_META_Object(library,name) \
	virtual name* cloneType() const { return new name (); } \
	virtual bool isSameKindAs(const CKGGraph* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
	virtual const char* libraryName() const { return #library; }\
	virtual const char* className() const { return #name; }

}

#endif