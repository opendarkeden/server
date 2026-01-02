//////////////////////////////////////////////////////////////////////
// 
// Filename    : Exception.h 
// Written By  : reiot@ewestsoft.com
// Description :
// 
//////////////////////////////////////////////////////////////////////

#ifndef __EXCEPTION_H__
#define __EXCEPTION_H__


// include files
#include "Types.h"
#include "StringStream.h"

#if __WINDOWS__
#pragma warning (disable : 4786)
#endif

#include <list>


//////////////////////////////////////////////////////////////////////
//
// class Throwable
//
// Exception �� Error �� ���̽� Ŭ�����̴�. ���� �޽�� �� ����Ÿ��
// �����س��� �ִ�.
//
//////////////////////////////////////////////////////////////////////

class Throwable : public std::exception
{
public:

	// constructor
	Throwable ()  {}
	
	// constructor
	Throwable (const string& message)  : m_Message(message) {}

	// destructor
	virtual ~Throwable ()  {}

	// return class's name
	virtual string getName () const  { return what(); }

	// add function name to throwable object's function stack
	void addStack (const string & stackname) 
	{
		m_Stacks.push_front(stackname);
	}

	// return debug string - throwable object's function stack trace
	string getStackTrace () const 
	{
		StringStream buf;
		int i = 1;

		for (list<string>::const_iterator itr = m_Stacks.begin() ;
			  itr != m_Stacks.end() ;
			  itr ++, i ++) {
			for (int j = 0 ; j < i ; j ++)
				buf << " ";
			buf << *itr << '\n' ;
		}
		
		return string(buf.toString());
	}

	// get throwable object's message
	const string& getMessage () const  { return m_Message; }
	
	// set throwable object's message
	void setMessage (const string & message)  { m_Message = message; }
	
	// return debug string - throwable object's detailed information
	virtual string toString () const 
	{
		StringStream buf;
		buf << getName() << " : " << m_Message << '\n'
			<< getStackTrace () ;
		
		return string(buf.toString());
	}

private :
	
	// message string
	string m_Message;
	
	// function stack 
	list<string> m_Stacks;
};

//--------------------------------------------------------------------------------
// macro definition
//--------------------------------------------------------------------------------

//--------------------------------------------------------------------------------
//
// Throwable�� �ʿ��ϱ� ������ �Ʒ��� �����ߴ�.
// Exception/Error�� ������ ��� �޽���� ��/�Ʒ��� ���õǾ�� �Ѵ�.
// __END_CATCH�� Throwable�� �޼ҵ� ���ÿ� ����� �� ������ ������
// ������ �Ѵ�.
//
//--------------------------------------------------------------------------------

#if defined(NDEBUG)
	#define __BEGIN_TRY ((void)0);
	#define __END_CATCH ((void)0);
	#define __END_CATCH_NO_RETHROW ((void)0);
#else
	#define __BEGIN_TRY try {
	#define __END_CATCH } catch (Throwable & t) { t.addStack(__PRETTY_FUNCTION__); throw; }
	#define __END_CATCH_NO_RETHROW } catch (Throwable & t) { t.addStack(__PRETTY_FUNCTION__); }
#endif

// �޼��� ����� END_CATCH
//#define __END_CATCH } catch (Throwable & t) { t.addStack(__PRETTY_FUNCTION__); throw; }

// �޼��� ��� END_CATCH
//#define __END_CATCH } catch (Throwable & t) { cout << "\nCAUGHT Exception IN END_CATCH MACRO...\n[" << __PRETTY_FUNCTION__ << "]\n>>> " << t.toString() << endl; t.addStack(__PRETTY_FUNCTION__); throw; }


/*
//--------------------------------------------------------------------------------
//
//	#define __BEGIN_TRY \
//				try {
//	#define __END_CATCH \
//				} catch (Throwable & t) { \
//					t.addStack((func)); \
//					throw; \
//				}
//
//
// critical section
//
//--------------------------------------------------------------------------------
*/
#define __ENTER_CRITICAL_SECTION(mutex) mutex.lock(); try {
#define __LEAVE_CRITICAL_SECTION(mutex) } catch (Throwable & t) { mutex.unlock(); throw; } mutex.unlock(); 

//--------------------------------------------------------------------------------
//
// cout debugging
//
//--------------------------------------------------------------------------------
#if defined(NDEBUG) || defined(__WIN32__)
	#define __BEGIN_DEBUG ((void)0);
	#define __END_DEBUG ((void)0);
#elif defined(__LINUX__) || defined(__WIN_CONSOLE__)
	#define __BEGIN_DEBUG try {
	#define __END_DEBUG  } catch (Throwable & t) { cout << t.toString() << endl; throw; } catch (exception & e) { cout << e.what() << endl; throw; }
#elif defined(__MFC__)
	#define __BEGIN_DEBUG try {
	#define __END_DEBUG } catch (Throwable & t) { AfxMessageBox(t.toString()); throw; }
#endif


//////////////////////////////////////////////////////////////////////
//
// Exception
//
//////////////////////////////////////////////////////////////////////
class Exception : public Throwable {
public :
	Exception ()  : Throwable() {}
	Exception (const string& msg)  : Throwable(msg) {}
	string getName () const  { return "Exception"; }
};

	//////////////////////////////////////////////////////////////////////
	//
	// I/O Exception
	//
	// ����, ����, IPC ����½� �߻��� �� �ִ� ����
	//
	//////////////////////////////////////////////////////////////////////
	// ����, ����, IPC ����½� �߻��� �� �ִ� ����
	class IOException : public Exception {
	public :
		IOException ()  : Exception () {}
		IOException (const string& msg)  : Exception (msg) {}
		string getName () const  { return "IOException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// Non Blocking I/O Exception
		//
		// I/O �� nonblocking �� �߻��� ���
		//
		//////////////////////////////////////////////////////////////////////
		class NonBlockingIOException : public IOException {
		public :
			NonBlockingIOException ()  : IOException () {}
			NonBlockingIOException (const string& msg)  : IOException (msg) {}
			string getName () const  { return "NonBlockingIOException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Interrupted I/O Exception
		//
		// I/O �� ���ͷ�Ʈ�� �ɸ� ���
		//
		//////////////////////////////////////////////////////////////////////
		class InterruptedIOException : public IOException {
		public :
			InterruptedIOException ()  : IOException () {}
			InterruptedIOException (const string& msg)  : IOException (msg) {}
			string getName () const  { return "InterruptedIOException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// EOF Exception
		//
		// I/O �� EOF �� ���� ���
		//
		//////////////////////////////////////////////////////////////////////
		class EOFException : public IOException {
		public :
			EOFException ()  : IOException () {}
			EOFException (const string& msg)  : IOException (msg) {}
			string getName () const  { return "EOFException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// File Not Opened Exception 
		//
		//////////////////////////////////////////////////////////////////////
		class FileNotOpenedException : public IOException {
		public :
			FileNotOpenedException ()  : IOException() {}
			FileNotOpenedException (const string& msg)  : IOException(msg) {}
			string getName () const  { return "FileNotOpenedException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// File Already Exist Exception
		//
		//////////////////////////////////////////////////////////////////////
		class FileAlreadyExistException : public IOException {
		public :
			FileAlreadyExistException ()  : IOException() {}
			FileAlreadyExistException (const string& msg)  : IOException(msg) {}
			string getName () const  { return "FileAlreadyExistException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// File Not Exist Exception
		//
		//////////////////////////////////////////////////////////////////////
		class FileNotExistException : public IOException {
		public :
			FileNotExistException ()  : IOException() {}
			FileNotExistException (const string& msg)  : IOException(msg) {}
			string getName () const  { return "FileNotExistException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Time out Exception
		//
		// ���� �ð��� ������ ���
		//
		//////////////////////////////////////////////////////////////////////
		class TimeoutException : public IOException {
		public :
			TimeoutException ()  : IOException () {}
			TimeoutException (const string& msg)  : IOException (msg) {}
			string getName () const  { return "TimeoutException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Socket Exception
		//
		// Ư�� ���Ͽ��� �߻��ϴ� ���ܵ�
		//
		//////////////////////////////////////////////////////////////////////
		class SocketException : public IOException {
		public :
			SocketException ()  : IOException () {}
			SocketException (const string& msg)  : IOException (msg) {}
			string getName () const  { return "SocketException"; }
		};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Bind Exception
			//
			// bind()�� �߻��ϴ� ����
			//
			//////////////////////////////////////////////////////////////////////
			class BindException : public SocketException {
			public :
				BindException ()  : SocketException () {}
				BindException (const string& msg)  : SocketException (msg) {}
				string getName () const  { return "BindException"; }
			};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Connect Exception
			//
			// ���� ������ ���� ��� (���� ���� �߻��Ѵٰ� ���� �ȴ�.)
			//
			//////////////////////////////////////////////////////////////////////
			class ConnectException : public SocketException {
			public :
				ConnectException ()  : SocketException () {}
				ConnectException (const string& msg)  : SocketException (msg) {}
				string getName () const  { return "ConnectException"; }
			};
			
		//////////////////////////////////////////////////////////////////////
		//
		// Protocol Exception
		//
		// ��Ŷ �Ľ��Ҷ� �߻��ϴ� ���ܵ�
		//
		//////////////////////////////////////////////////////////////////////
		class ProtocolException : public IOException {
		public :
			ProtocolException ()  : IOException () {}
			ProtocolException (const string& msg)  : IOException (msg) {}
			string getName () const  { return "ProtocolException"; }
		};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Idle Exception
			//
			// ���� �ð����� peer �κ��� �Է��� ���� ���
			//
			//////////////////////////////////////////////////////////////////////
			class IdleException : public ProtocolException {
			public :
				IdleException ()  : ProtocolException () {}
				IdleException (const string& msg)  : ProtocolException (msg) {}
				string getName () const  { return "IdleException"; }
			};
	

			//////////////////////////////////////////////////////////////////////
			//
			// Invalid Protocol Exception
			//
			// �߸��� ��������
			//
			//////////////////////////////////////////////////////////////////////
			class InvalidProtocolException : public ProtocolException {
			public :
				InvalidProtocolException ()  : ProtocolException () {}
				InvalidProtocolException (const string& msg)  : ProtocolException (msg) {}
				string getName () const  { return "InvalidProtocolException"; }
			};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Insufficient Data Exception
			//
			// ���� ��Ŷ ����Ÿ�� �����ϰ� �������� �ʾ��� ���
			//
			//////////////////////////////////////////////////////////////////////
			class InsufficientDataException : public ProtocolException {
			public :
				InsufficientDataException (uint size = 0)  : ProtocolException (), m_Size(size) {}
				InsufficientDataException (const string& msg, uint size = 0)  : ProtocolException (msg), m_Size(size) {}
				string getName () const  { return "InsufficientDataException"; }
				uint getSize () const  { return m_Size; }
				string toString () const 
				{
					StringStream buf;
					buf << getName() << " : " << getMessage();
					if (m_Size > 0) {
						buf << " (lack of " << m_Size << " bytes)\n";
					}
					buf << getStackTrace ();
			
					return buf.toString();
				}
	
			private :
				uint m_Size;
			};

			//////////////////////////////////////////////////////////////////////
			// 
			// �������� ����, �ý��� ���� ���������ؼ� ������ ©��� �� ���
			// �� ���ܸ� ����Ѵ�.
			// 
			//////////////////////////////////////////////////////////////////////
			class DisconnectException : public ProtocolException {
			public :
				DisconnectException ()  : ProtocolException () {}
				DisconnectException (const string& msg)  : ProtocolException (msg) {}
				string getName () const  { return "DisconnectException"; }
			};

			//////////////////////////////////////////////////////////////////////
			// 
			// Ư�� ��Ȳ�� �����ؾ� �Ǵ� ��Ŷ�� ������ ���
			// 
			//////////////////////////////////////////////////////////////////////
			class IgnorePacketException : public ProtocolException {
			public :
				IgnorePacketException ()  : ProtocolException () {}
				IgnorePacketException (const string& msg)  : ProtocolException (msg) {}
				string getName () const  { return "IgnorePacketException"; }
			};


	//////////////////////////////////////////////////////////////////////
	//
	// Thread Exception
	//
	// ������ �� ����ȭ �����鿡�� �߻��ϴ� ���ܵ�
	//
	//////////////////////////////////////////////////////////////////////
	class ThreadException : public Exception {
	public :
		ThreadException ()  : Exception () {}
		ThreadException (const string& msg)  : Exception (msg) {}
		string getName () const  { return "ThreadException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// Mutex Exception
		//
		// ���ؽ����� �߻��ϴ� ���ܵ�
		//
		//////////////////////////////////////////////////////////////////////
		class MutexException : public ThreadException {
		public :
			MutexException ()  : ThreadException () {}
			MutexException (const string& msg)  : ThreadException (msg) {}
			string getName () const  { return "MutexException"; }
		};

			//////////////////////////////////////////////////////////////////////
			//
			// Mutex Attribute Exception
			//
			// ���ؽ� �Ӽ����� �߻��ϴ� ���ܵ�
			//
			//////////////////////////////////////////////////////////////////////
			class MutexAttrException : public MutexException {
			public :
				MutexAttrException ()  : MutexException () {}
				MutexAttrException (const string& msg)  : MutexException (msg) {}
				string getName () const  { return "MutexAttrException"; }
			};


		//////////////////////////////////////////////////////////////////////
		//
		// Conditional Variable Exception
		//
		// Conditional Variable ���� �߻��ϴ� ���� (�̸��� �ʹ� ���.. - -)
		//
		//////////////////////////////////////////////////////////////////////
		class CondVarException : public ThreadException {
		public :
			CondVarException ()  : ThreadException () {}
			CondVarException (const string& msg)  : ThreadException (msg) {}
			string getName () const  { return "CondVarException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Semaphore Exception
		//
		// Semaphore ���� �߻��ϴ� ����
		//
		//////////////////////////////////////////////////////////////////////
		class SemaphoreException : public ThreadException {
		public :
			SemaphoreException ()  : ThreadException () {}
			SemaphoreException (const string& msg)  : ThreadException (msg) {}
			string getName () const  { return "SemaphoreException"; }
		};


	//////////////////////////////////////////////////////////////////////
	//
	// SQL Exception 
	//
	// SQL ���� ����
	//
	//////////////////////////////////////////////////////////////////////
	class SQLException : public Exception {
	public :
		SQLException ()  : Exception() {}
		SQLException (const string& msg)  : Exception(msg) {}
		string getName () const  { return "SQLException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// SQL Warning
		//
		// SQL ������� ��Ÿ���� ����~~
		//
		//////////////////////////////////////////////////////////////////////
		class SQLWarning : public SQLException {
		public :
			SQLWarning ()  : SQLException() {}
			SQLWarning (const string& msg)  : SQLException(msg) {}
			string getName () const  { return "SQLWarning"; }
		};


		//////////////////////////////////////////////////////////////////////
		//
		// SQL Connect Exception
		//
		// SQL�� ���� ���� �õ��� ������ ���, ������ �������� ��� ��
		//
		//////////////////////////////////////////////////////////////////////
		class SQLConnectException : public SQLException {
		public :
			SQLConnectException ()  : SQLException() {}
			SQLConnectException (const string& msg)  : SQLException(msg) {}
			string getName () const  { return "SQLConnectException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Query Exception
		//
		//////////////////////////////////////////////////////////////////////
		class SQLQueryException : public SQLException {
		public :
			SQLQueryException ()  : SQLException() {}
			SQLQueryException (const string& msg)  : SQLException(msg) {}
			string getName () const  { return "SQLQueryException"; }
		};


	//////////////////////////////////////////////////////////////////////
	//
	// Runtime Exception
	//
	// ��Ÿ�ӿ� �߻������� generic �� �뵵�� ���� �� �ִ� ���ܵ�
	//
	//////////////////////////////////////////////////////////////////////
	class RuntimeException : public Exception {
	public :
		RuntimeException ()  : Exception () {}
		RuntimeException (const string& msg)  : Exception (msg) {}
		string getName () const  { return "RuntimeException"; }
	};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Invalid Arguemnt Exception
		//
		// �Լ�, ����Լ��� �Ķ���Ͱ� �߸��� ��� 
		//
		//////////////////////////////////////////////////////////////////////
		class InvalidArgumentException : public RuntimeException {
		public :
			InvalidArgumentException ()  : RuntimeException () {}
			InvalidArgumentException (const string& msg)  : RuntimeException (msg) {}
			string getName () const  { return "InvalidArgumentException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Out Of Bound Exception
		//
		// ���״��. Out Of Bound!
		//
		//////////////////////////////////////////////////////////////////////
		class OutOfBoundException : public RuntimeException {
		public :
			OutOfBoundException ()  : RuntimeException () {}
			OutOfBoundException (const string& msg)  : RuntimeException (msg) {}
			string getName () const  { return "OutOfBoundException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Interrupted Exception
		//
		// System Call ���� ���ͷ�Ʈ ������ ���
		//
		//////////////////////////////////////////////////////////////////////
		class InterruptedException : public RuntimeException {
		public :
			InterruptedException ()  : RuntimeException () {}
			InterruptedException (const string& msg)  : RuntimeException (msg) {}
			string getName () const  { return "InterruptedException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// No Such Element Exception
		//
		// �÷��ǿ��� Ư�� Ű���� �˻������� �׷� ������Ʈ�� ���� ���
		//
		//////////////////////////////////////////////////////////////////////
		class NoSuchElementException : public RuntimeException {
		public :
			NoSuchElementException ()  : RuntimeException () {}
			NoSuchElementException (const string& msg)  : RuntimeException (msg) {}
			string getName () const  { return "NoSuchElementException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Duplicated Exception
		//
		// �÷����� Ư�� Ű�� �ߺ��Ǿ��� �� 
		//
		//////////////////////////////////////////////////////////////////////
		class DuplicatedException : public RuntimeException {
		public :
			DuplicatedException ()  : RuntimeException () {}
			DuplicatedException (const string& msg)  : RuntimeException (msg) {}
			string getName () const  { return "DuplicatedException"; }
		};

	//////////////////////////////////////////////////////////////////////
	//
	// Game Exception
	//
	// ���ӿ��� goto �뵵�� ����ϴ� ���ܵ�.. -_-;
	//
	//////////////////////////////////////////////////////////////////////
	class GameException : public Exception {
	public :
		GameException ()  : Exception () {}
		GameException (const string& msg)  : Exception (msg) {}
		string getName () const  { return "GameException"; }
	};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Portal Exception
		//
		// PC �� ��Ż�� �������...�
		//
		//////////////////////////////////////////////////////////////////////
		class PortalException : public GameException {
		public :
			PortalException ()  : GameException () {}
			PortalException (const string& msg)  : GameException (msg) {}
			string getName () const  { return "PortalException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Ư�� ��ǥ ������ ������ ũ��ó�� ���� ������� �� ���� ��
		//
		//////////////////////////////////////////////////////////////////////
		class EmptyTileNotExistException : public GameException {
		public :
			EmptyTileNotExistException ()  : GameException () {}
			EmptyTileNotExistException (const string& msg)  : GameException (msg) {}
			string getName () const  { return "EmptyTileNotExistException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		//
		//
		//////////////////////////////////////////////////////////////////////
		class InventoryFullException : public GameException {
		public :
			InventoryFullException ()  : GameException () {}
			InventoryFullException (const string& msg)  : GameException (msg) {}
			string getName () const  { return "InventoryFullException"; }
		};


//////////////////////////////////////////////////////////////////////
//
// Error
//
//////////////////////////////////////////////////////////////////////
class Error : public Throwable {
public :
	Error ()  : Throwable() {}
	Error (const string & msg)  : Throwable(msg) {}
	string getName () const  { return "Error"; }
};	
	//////////////////////////////////////////////////////////////////////
	//
	// Game Error
	//
	//////////////////////////////////////////////////////////////////////
	class GameError : public Error {
	public :
		GameError ()  : Error () {}
		GameError (const string& msg)  : Error(msg) {}
		string getName () const  { return "GameError"; }
	};


	//////////////////////////////////////////////////////////////////////
	//
	// Assertion Error
	//
	//////////////////////////////////////////////////////////////////////
	class AssertionError : public Error {
	public :
		AssertionError ()  : Error () {}
		AssertionError (const string& msg)  : Error(msg) {}
		string getName () const  { return "AssertionError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Unsupported Error
	//
	//////////////////////////////////////////////////////////////////////
	class UnsupportedError : public Error {
	public :
		UnsupportedError ()  : Error () {}
		UnsupportedError (const string& msg)  : Error(msg) {}
		string getName () const  { return "UnsupportedError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Log Error
	//
	// �Ϲ����� �����ʹ� �޸� LogError�� ����Ʈ �α����Ͽ� �α׵� �� ����.
	// (�����غ���. �α׸Ŵ��� ��ü�� ������ ��� �α��Ѵٴ� ���ΰ�?)
	//
	//////////////////////////////////////////////////////////////////////
	class LogError : public Error {
	public :
		LogError ()  : Error () {}
		LogError (const string& msg)  : Error(msg) {}
		string getName () const  { return "LogError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Unknown Error
	//
	//////////////////////////////////////////////////////////////////////
	class UnknownError : public Error {
	public :
		UnknownError ()  : Error() {}
		UnknownError (const string & msg)  : Error(msg) {}
		UnknownError (const string & msg, uint ErrorCode)  : Error(msg), m_ErrorCode(ErrorCode) {}
		string getName () const  { return "UnknownError"; }
		uint getErrorCode () const  { return m_ErrorCode; }
		string toString () const 
		{
			StringStream buf;
			buf << getName() << " : " << getMessage() << " (" << getErrorCode() << ") \n"
				<< getStackTrace () ;
			
			return buf.toString();
		}
	private :
		uint m_ErrorCode;
	};

#define __BEGIN_DEBUG_EX try {
#define __END_DEBUG_EX  } catch (ProtocolException&) { throw; } catch (Error&) { throw; } catch (Exception & e) { ofstream file("packet_exception.txt", ios::out | ios::app); file << e.toString() << endl; file.close(); cout << e.toString() << endl; } 

#endif
