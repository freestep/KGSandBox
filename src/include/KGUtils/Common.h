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
	/// 字符串列表
	typedef std::vector<std::string> string_list;

	/// 渲染顺序
	typedef enum ERenderBin
	{
		ERenderBin_GEOM = 1,
		ERenderBin_CLOUDS,
		ERenderBin_LABEL,
		//用枚举确定场景节点的渲染顺序
	}ERenderBin;

	/// 开启透明状态
	struct KGUTIL_EXPORT ActivateTransparencyOnType
	{
		ActivateTransparencyOnType(const std::type_info& t, const ERenderBin renderorder);
		void operator()(osg::Node* nptr) const;
		const std::type_info&  _t;
		const ERenderBin _renderorder;
	protected:
		ActivateTransparencyOnType& operator = (const ActivateTransparencyOnType&) { return *this; }
	};

	/// 关闭透明状态
	struct KGUTIL_EXPORT DeactivateTransparencyOnType
	{
		DeactivateTransparencyOnType(const std::type_info& t, const ERenderBin renderorder);
		void operator()(osg::Node* nptr) const;
	
		const std::type_info&  _t;
		const ERenderBin _renderorder;
	protected:
		DeactivateTransparencyOnType& operator = (const DeactivateTransparencyOnType&) { return *this; }
	};
	///开启关闭透明度和设置渲染顺序的宏
#define ACTIVE_TRANSPARENCY(_typename_, _render_order_, _nptr_)  ActivateTransparencyOnType(_typename_, _render_order_)(_nptr_)
#define DEACTIVE_TRANSPARENCY(_typename_, _render_order_,  _nptr_)  DeactivateTransparencyOnType(_typename_, _render_order_)(_nptr_)

	//////////////////////////////////////////////////////////////////////////
	//共通函数
	//////////////////////////////////////////////////////////////////////////
#define KG_META_Object(library,name) \
	virtual name* cloneType() const { return new name (); } \
	virtual bool isSameKindAs(const CKGGraph* obj) const { return dynamic_cast<const name *>(obj)!=NULL; } \
	virtual const char* libraryName() const { return #library; }\
	virtual const char* className() const { return #name; }

}

#endif