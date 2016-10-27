//////////////////////////////////////////////////////////////////////////
// 异常报警与异常信息提示、错误信息提示
//////////////////////////////////////////////////////////////////////////
#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <KGShell/Export.h>

#include <exception>
#include <string>

namespace KGShell
{
	//////////////////////////////////////////////////////////////////////////
	// 异常信息基类
	//////////////////////////////////////////////////////////////////////////
	class KGSHELL_EXPORT KGThrowable : public std::exception
	{
	public:
		enum {MAX_TEXT_LEN = 1024};
		KGThrowable();
		KGThrowable(const char* message, const char* origin = 0);
		virtual ~KGThrowable() throw();
		virtual const char* getMessage() const;
		virtual const std::string getFormattedMessage() const;
		virtual void setMessage( const char* message);
		virtual const char* getOrigin() const;
		virtual void setOrigin (const char *origin);
		virtual const char* what() const throw();
	private:
		char _message[MAX_TEXT_LEN];
		char _origin[MAX_TEXT_LEN];
	};

	//////////////////////////////////////////////////////////////////////////
	// 错误及其错误信息
	//////////////////////////////////////////////////////////////////////////
	class KGSHELL_EXPORT KGError : public KGThrowable
	{
	public:
		KGError ();
		KGError (const char* message, const char* origin = 0);
		KGError (const std::string& message, const std::string& origin = "");  
		virtual ~KGError () throw ();
	};

	//////////////////////////////////////////////////////////////////////////
	// 异常及异常信息
	//////////////////////////////////////////////////////////////////////////
	class KGSHELL_EXPORT KGException : public KGThrowable
	{
	public:
		KGException ();
		KGException (const char* message, const char* origin = 0);
		KGException (const std::string& message, const std::string& = "");
		virtual ~KGException () throw ();
	};
}



#endif