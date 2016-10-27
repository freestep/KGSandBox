#include <KGShell/Props.h>

namespace KGShell
{
	CKGPropertyCell::CKGPropertyCell() : osg::Referenced() ,
		_type(ECellType_NONE),
		_attr(READ | WRITE),
		_name("")
	{
		
	}
	CKGPropertyCell::CKGPropertyCell(const std::string& name ) : osg::Referenced() ,
		_type(ECellType_NONE),
		_attr(READ | WRITE),
		_name(name)
	{
		_local_val.string_val = 0;
	}

	CKGPropertyCell::CKGPropertyCell( const CKGPropertyCell& cell ): osg::Referenced(),
		_type(cell._type),
		_attr(cell._attr),
		_name(cell._name)
	{
		_local_val.string_val = 0;
		if (_type == ECellType_NONE)
			return;
		switch (_type)
		{
		case ECellType_BOOL:
			set_bool(cell.get_bool());
			break;
		///还有几种基本类型……
		default:
			break;
		}
	}

	CKGPropertyCell::~CKGPropertyCell()
	{
		 clearValue();
		 _children.clear();
	}
	
	void CKGPropertyCell::clearValue()
	{
		if (_type != ECellType_NONE)  return;
			switch (_type) {
			case ECellType_BOOL:
				_local_val.bool_val = false;
				break;
			default: 
				break;
			}
	}

	bool CKGPropertyCell::setBoolValue(bool value)
	{
		if (_attr == (READ | WRITE) && _type == ECellType_BOOL)
		{
			set_bool(value);
		}
		if (_type == ECellType_NONE || _type == ECellType_UNSPECIFIED)
		{
			clearValue();
			_type = ECellType_BOOL;
		} 
		else
		{
			switch(_type)
			{
			case ECellType_BOOL:
				set_bool(value);
				break;
			case ECellType_SHORT:
				set_short(short(value));
				break;
			case ECellType_INT:
				set_int(int(value));
				break;
			case ECellType_LONG:
				set_long(long(value));
				break;
			case ECellType_DOUBLE:
				set_double(double(value));
				break;
			case ECellType_NONE:
			default:
				break;
			}
		}
		return true;
	}

	bool CKGPropertyCell::getBoolValue() const
	{
		return false;
	}

}