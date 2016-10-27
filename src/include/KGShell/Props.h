#ifndef _PROPS_H_
#define _PROPS_H_

#include <algorithm>

#include <osg/Referenced>
#include <osg/Vec2>
#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Vec2d>
#include <osg/Vec3d>
#include <osg/Vec4d>
#include <osg/Matrixd>

#include <KGShell/Export.h>

namespace KGShell
{
#if 1
	//////////////////////////////////////////////////////////////////////////
	//属性的模板类
	//////////////////////////////////////////////////////////////////////////
	template<typename T> 
	struct CKGProperty {
		CKGProperty() : _set(false), _value(T()), _defaultValue(T()) { }
		CKGProperty(T defaultValue) : _set(false), _value(defaultValue), _defaultValue(defaultValue) { }
		CKGProperty(T defaultValue, T value) : _set(true), _value(value), _defaultValue(defaultValue) { }
		CKGProperty(const CKGProperty<T>& rhs) { (*this)=rhs; }
		virtual ~CKGProperty() { }
		CKGProperty<T>& operator =(const CKGProperty<T>& rhs) { _set=rhs._set; _value=rhs._value; _defaultValue=rhs._defaultValue; return *this; }
		const T& operator =(const T& value) { _set=true; _value=value; return _value; }
		bool operator ==(const CKGProperty<T>& rhs) const { return _set && rhs._set && _value==rhs._value; }
		bool operator !=(const CKGProperty<T>& rhs) const { return !( (*this)==rhs); }
		bool operator ==(const T& value) const { return _value==value; }
		bool operator !=(const T& value) const { return _value!=value; }
		bool operator > (const T& value) const { return _value>value; }
		bool operator >=(const T& value) const { return _value>=value; }
		bool operator < (const T& value) const { return _value<value; }
		bool operator <=(const T& value) const { return _value<=value; }
		bool isSetTo(const T& value) const { return _set && _value==value; }
		bool isSet() const { return _set; }
		void unset() { _set = false; _value=_defaultValue; }

		const T& get() const { return _value; }
		const T& value() const { return _value; }
		const T& defaultValue() const { return _defaultValue; }
		T temp_copy() const { return _value; }

		const T& getOrUse(const T& fallback) const { return _set ? _value : fallback; }

		T& mutable_value() { _set = true; return _value; }

		void init(T defValue) { _value=defValue; _defaultValue=defValue; unset(); }

		operator const T*() const { return &_value; }

		T* operator ->() { _set=true; return &_value; }
		const T* operator ->() const { return &_value; }

	private:
		bool _set;
		T _value;
		T _defaultValue;
		typedef T* CKGProperty::*unspecified_bool_type;

	public:
		operator unspecified_bool_type() const { return 0; }
	};

#endif

	//////////////////////////////////////////////////////////////////////////
	///属性树
	//////////////////////////////////////////////////////////////////////////
	enum ECellType {
		ECellType_NONE = 0,
		ECellType_UNSPECIFIED,
		ECellType_VOID,
		ECellType_BOOL,
		ECellType_SHORT,
		ECellType_INT,
		ECellType_LONG,
		ECellType_FLOAT,
		ECellType_DOUBLE,
		ECellType_STRING,
		ECellType_OSGVEC3D,
		ECellType_OSGVEC3,
		ECellType_OSGVEC2D,
		ECellType_OSGVEC2,
		ECellType_OSGVEC4D,
		ECellType_OSGVEC4,
		ECellType_OSGMATRIX4D,
		ECellType_OSGMATRIX4,
	};

	//////////////////////////////////////////////////////////////////////////
	//模拟属性模板的属性细胞集
	//////////////////////////////////////////////////////////////////////////
	class KGSHELL_EXPORT CKGPropertyCell : public osg::Referenced
	{
	public:
		enum { MAX_STRING_LEN = 1024 };
		//细胞单元的属性, 控制细胞单元是否可读可写。
		enum Attribute{
			NO_ATTR = 0, //未设置属性
			READ = 1,		  //只读
			WRITE = 2,     //只写
		};
		//构造
		CKGPropertyCell( );
		CKGPropertyCell( const std::string& name );
		//拷贝构造
		CKGPropertyCell( const CKGPropertyCell& cell);
		//析构
		virtual ~CKGPropertyCell();

		//细胞单元是否包含一个有效值
		bool hasValue() const { return (_type != ECellType_NONE); }

		//获取细胞单元的名字（这个名字可与用于xml的序列化）
		const char* getName() const { return _name.c_str();  }

		//获得细胞单元的父单元指针
		const CKGPropertyCell* getParent() const { return _parent;  }
		CKGPropertyCell* getParent() { return _parent; }

		//获得细胞单元直属子单元数量
		int getNumCells() const { return (int)_children.size(); }

		//获得索引为index的直属子单元指针
		virtual CKGPropertyCell getCell(unsigned int index) { return CKGPropertyCell();  };

		//添加子细胞
		bool addSubCell(CKGPropertyCell cell){ return false;  }
		
		//删除子细胞。优先根据名字查找子细胞，如果找到则删除返回true，否则查找并删除索引为index的子细胞。
		//如果存在索引为index的子细胞存在删除之返回true，否则返回false
		bool removeCell(std::string name, unsigned int index = 0){ return false;  }
		
		//删除所有子细胞
		bool removeAllCells(){ return false; }

		//赋值方法重新
		CKGPropertyCell& operator =(const CKGPropertyCell& cell){
			_type = cell._type;
			_attr = cell._attr;
			_name = cell._name.c_str();
			_local_val = cell._local_val;
			for (int i=0; i<cell._children.size(); i++)
			{
				_children.push_back(cell._children.at(i));
			}
			return *this;
		}
		
		template<typename T>
		bool setValue(const T& value);

	protected:
		//设置属性值
		bool setBoolValue(bool value);
		bool getBoolValue() const;
// 		bool setShortValue(short value);
// 		bool setIntValue(int value);
// 		bool setLongValue(long value);
// 		bool setFloatValue(float value);
// 		bool setDoubleValue(double value);
// 		bool setStringValue(std::string value);
// 		bool setVec2Value(osg::Vec2 value);
// 		bool setVec3Value(osg::Vec3 value);
// 		bool setVec4Value(osg::Vec4 value);
// 		bool setVec2dValue(osg::Vec2d value);
// 		bool setVec3dValue(osg::Vec3d value);
// 		bool setVec4dValue(osg::Vec4d value);
// 		bool setMatrix4dValue(osg::Matrixd value);
	private:
		//设置、获取细胞单元值
		void set_bool(bool value) { _local_val.bool_val = value; }
		bool get_bool() const { return _local_val.bool_val; };
		void set_short(short value) { _local_val.short_val = value; }
		short get_short() const { return _local_val.short_val; };
		void set_int(int value) { _local_val.int_val = value; }
		int get_int() const { return _local_val.int_val; };
		void set_long(long value) { _local_val.long_val = value; }
		long get_long() const { return _local_val.long_val; };
		void set_float(float value) { _local_val.float_val = value; }
		float get_float() const { return _local_val.float_val; };
		void set_double(double value) { _local_val.double_val = value; }
		double get_double() const { return _local_val.double_val; };
		void set_string(std::string value) { _local_val.string_val;  }
		std::string get_string() const { return _local_val.string_val;  }
		void set_pointer(void* value){ _local_val.void_val = value; }
		void* get_pointer() const{ return _local_val.void_val;  }
		void set_vec2(osg::Vec2 value){ _local_val.vec2_val[0] = value.x();   _local_val.vec2_val[1] = value.y(); }
		osg::Vec2 get_vec2() { return osg::Vec2(_local_val.vec2_val[0], _local_val.vec2_val[1]); }
		void set_vec3(osg::Vec3 value){ _local_val.vec3_val[0] = value.x();   _local_val.vec3_val[1] = value.y(); _local_val.vec3_val[2] = value.z(); }
		osg::Vec3 get_vec3() { return osg::Vec3(_local_val.vec3_val[0], _local_val.vec3_val[1], _local_val.vec3_val[2]); }
		void set_vec4(osg::Vec4 value){ _local_val.vec4_val[0] = value.x();   _local_val.vec4_val[1] = value.y(); _local_val.vec4_val[2] = value.z(); _local_val.vec4_val[3] = value.w(); }
		osg::Vec4 get_vec4() { return osg::Vec4(_local_val.vec4_val[0], _local_val.vec4_val[1], _local_val.vec4_val[2], _local_val.vec4_val[3]); }
		void set_vec2d(osg::Vec2d value){ _local_val.vec2d_val[0] = value.x();   _local_val.vec2d_val[1] = value.y(); }
		osg::Vec2d get_vec2d() { return osg::Vec2d(_local_val.vec2d_val[0], _local_val.vec2d_val[1]); }
		void set_vec3d(osg::Vec3d value){ _local_val.vec3d_val[0] = value.x();   _local_val.vec3d_val[1] = value.y(); _local_val.vec3d_val[2] = value.z(); }
		osg::Vec3d get_vec3d() { return osg::Vec3d(_local_val.vec3d_val[0], _local_val.vec3d_val[1], _local_val.vec3d_val[2]); }
		void set_vec4d(osg::Vec4d value){ _local_val.vec4d_val[0] = value.x();   _local_val.vec4d_val[1] = value.y(); _local_val.vec4d_val[2] = value.z(); _local_val.vec4d_val[3] = value.w(); }
		osg::Vec4d get_vecd4d() { return osg::Vec4d(_local_val.vec4d_val[0], _local_val.vec4d_val[1], _local_val.vec4d_val[2], _local_val.vec4d_val[3]); }
		void set_matrix4d(osg::Matrixd value){}
		osg::Matrixd get_matrix4d(){ return osg::Matrixd(_local_val.matrix4d_val); }

		//清除属性值，并设置为默认值
		void clearValue();

	protected:
		//细胞集
		typedef std::vector<CKGPropertyCell> PropertyCellList;
		PropertyCellList _children;
		//父单元
		CKGPropertyCell* _parent;
		//细胞单元值的类型
		ECellType _type;
		//细胞的属性
		int _attr;
		//细胞的名字
		std::string _name;
		//细胞值的共同体
		union{
			bool bool_val;
			short short_val;
			int int_val;
			long long_val;
			float float_val;
			double double_val;
			char* string_val;
			void* void_val;
			float vec2_val[2];
			float vec3_val[3];
			float vec4_val[4];
			double vec2d_val[2];
			double vec3d_val[3];
			double vec4d_val[4];
			double matrix4d_val[16];
		} _local_val;

	};

	template<typename T>
	bool CKGPropertyCell::setValue(const T& value)
	{
		if (typeid(value) == typeid(bool))
		{
			return setBoolValue(value);
		}
		else
		{
			return false;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//设置/获取变量, 提供各类型实例的初始值
	//////////////////////////////////////////////////////////////////////////
	template <class T> struct CKGRawValue 
	{
	public:
		static T defaultValue() { return T(); }

		CKGRawValue() { }
		virtual ~CKGRawValue() { }

		virtual T getValue() const = 0;
		virtual bool setValue(T) = 0;
	};

	template<> inline bool CKGRawValue<bool>::defaultValue() { return false; }
	template<> inline int CKGRawValue<int>::defaultValue() { 	return 0; } 
	template<> inline long CKGRawValue<long>::defaultValue() { return 0; }
	template<> inline float CKGRawValue<float>::defaultValue() { 	return 0.0; } 
	template<> inline double CKGRawValue<double>::defaultValue() { return 0.0; }
	template<> inline char * CKGRawValue<char *>::defaultValue() { 	return ""; } 
	template<> inline std::string CKGRawValue<std::string >::defaultValue() { 	return ""; } 
	template<> inline CKGPropertyCell CKGRawValue<CKGPropertyCell >::defaultValue() { 	return CKGPropertyCell(""); } 

	template <class C, class T> struct CKGRawValueMethod : public CKGRawValue<T>
	{
	public:
		typedef T (C::*getter_t)() const;
		typedef bool (C::*setter_t)(T);

		CKGRawValueMethod() : _obj(0), _getter(0), _setter(0) { }
		CKGRawValueMethod(C* obj, getter_t getter=0, setter_t setter=0)
			:_obj(obj), _getter(getter), _setter(setter) { }

		virtual ~CKGRawValueMethod() { }

		virtual T getValue() const{
			if (_obj&&_getter) return ((*_obj).*_getter)();
			else{
				osg::notify(osg::WARN)<<"CKGRawValueMethod: 获取对象实例属性异常"<<std::endl;				
				return CKGRawValue<T>::defaultValue();
			}
		}

		virtual bool setValue(T value){
			if (_obj&&_setter) { ((*_obj).*_setter)(value); return false; }
			else{
				osg::notify(osg::WARN)<<"CKGRawValueMethod: 设置对象实例属性异常"<<std::endl;					
				return false;
			}
		}

		const T& operator = (const T& value) {
			if (_obj&&_setter) { ((*_obj).*_setter)(value); return value; }
			osg::notify(osg::WARN)<<"CKGRawValueMethod: 对象属性赋值异常"<<std::endl;				
			return CKGRawValue<T>::defaultValue();
		}

		const T& operator () (){
			if (_obj&&_getter) return ((*_obj).*_getter)();
			else {
				osg::notify(osg::WARN)<<"CKGRawValueMethod: 对象属性赋值异常"<<std::endl;				
				return CKGRawValue<T>::defaultValue();
			}
		}

		CKGRawValueMethod<C, T>& operator =(const CKGRawValueMethod<C, T>& rhs) { 
			_getter=rhs._getter; _setter=rhs._setter; _obj=rhs._obj; 
			return *this; 
		}

	protected:
		getter_t _getter;
		setter_t _setter;
		C* _obj;
	};

//#define KG_PROPERTY(_prop_, _classname_, _typename_)  CKGRawValueMethod<_classname_, _typename_>* _prop_

}


#endif