#include <KGShell/Exception.h>

#include <stdio.h>
#include <cstring>
#include <sstream>

namespace KGShell
{
	/// KGThrowable 实现
	KGThrowable::KGThrowable ()
	{
		_message[0] = '\0';
		_origin[0] = '\0';
	}

	KGThrowable::KGThrowable (const char* message, const char* origin)
	{
		setMessage(message);
		setOrigin(origin);
	}

	KGThrowable::~KGThrowable () throw ()
	{
	}

	const char*
		KGThrowable::getMessage () const
	{
		return _message;
	}

	const std::string
		KGThrowable::getFormattedMessage () const
	{
		return std::string(getMessage());
	}

	void
		KGThrowable::setMessage (const char* message)
	{
		strncpy(_message, message, MAX_TEXT_LEN);
		_message[MAX_TEXT_LEN - 1] = '\0';

	}

	const char*
		KGThrowable::getOrigin () const
	{
		return _origin;
	}

	void
		KGThrowable::setOrigin (const char* origin)
	{
		if (origin) {
			strncpy(_origin, origin, MAX_TEXT_LEN);
			_origin[MAX_TEXT_LEN - 1] = '\0';
		} else {
			_origin[0] = '\0';
		}
	}

	const char* KGThrowable::what() const throw()
	{
		try {
			return getMessage();
		}
		catch (...) {
			return "";
		}
	}

	///KGError 实现
	KGError::KGError ()
		: KGThrowable ()
	{
	}

	KGError::KGError (const char* message, const char *origin)
		: KGThrowable(message, origin)
	{
	}

	KGError::KGError(const std::string& message, const std::string& origin)
		: KGThrowable(message.c_str(), origin.c_str())
	{
	}

	KGError::~KGError () throw ()
	{
	}

	///KGException 实现
	KGException::KGException ()
		: KGThrowable ()
	{
	}

	KGException::KGException (const char* message, const char* origin)
		: KGThrowable(message, origin)
	{
	}

	KGException::KGException( const std::string& message,
		const std::string& origin )
		: KGThrowable(message.c_str(), origin.c_str())
	{
	}

	KGException::~KGException () throw ()
	{
	}

}