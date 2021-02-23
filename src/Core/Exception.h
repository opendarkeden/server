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
// Exception 과 Error 의 베이스 클래스이다. 관련 메쏘드 및 데이타를
// 구현해놓고 있다.
//
//////////////////////////////////////////////////////////////////////

class Throwable : public std::exception
{
public:

	// constructor
	Throwable () throw () {}
	
	// constructor
	Throwable (const string& message) throw () : m_Message(message) {}

	// destructor
	virtual ~Throwable () throw () {}

	// return class's name
	virtual string getName () const throw () { return what(); }

	// add function name to throwable object's function stack
	void addStack (const string & stackname) throw ()
	{
		m_Stacks.push_front(stackname);
	}

	// return debug string - throwable object's function stack trace
	string getStackTrace () const throw ()
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
	const string& getMessage () const throw () { return m_Message; }
	
	// set throwable object's message
	void setMessage (const string & message) throw () { m_Message = message; }
	
	// return debug string - throwable object's detailed information
	virtual string toString () const throw ()
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
// Throwable이 필요하기 때문에 아래에 정의했다.
// Exception/Error를 던지는 모든 메쏘드의 위/아래에 명시되어야 한다.
// __END_CATCH는 Throwable의 메소드 스택에 등록한 후 상위로 던지는
// 역할을 한다.
//
//--------------------------------------------------------------------------------

#if defined(NDEBUG)
	#define __BEGIN_TRY ((void)0);
	#define __END_CATCH ((void)0);
#else
	#define __BEGIN_TRY try {
	#define __END_CATCH } catch (Throwable & t) { t.addStack(__PRETTY_FUNCTION__); throw; }
#endif

// 메세지 비출력 END_CATCH
//#define __END_CATCH } catch (Throwable & t) { t.addStack(__PRETTY_FUNCTION__); throw; }

// 메세지 출력 END_CATCH
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
	Exception () throw () : Throwable() {}
	Exception (const string& msg) throw () : Throwable(msg) {}
	string getName () const throw () { return "Exception"; }
};

	//////////////////////////////////////////////////////////////////////
	//
	// I/O Exception
	//
	// 파일, 소켓, IPC 입출력시 발생할 수 있는 예외
	//
	//////////////////////////////////////////////////////////////////////
	// 파일, 소켓, IPC 입출력시 발생할 수 있는 예외
	class IOException : public Exception {
	public :
		IOException () throw () : Exception () {}
		IOException (const string& msg) throw () : Exception (msg) {}
		string getName () const throw () { return "IOException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// Non Blocking I/O Exception
		//
		// I/O 시 nonblocking 이 발생할 경우
		//
		//////////////////////////////////////////////////////////////////////
		class NonBlockingIOException : public IOException {
		public :
			NonBlockingIOException () throw () : IOException () {}
			NonBlockingIOException (const string& msg) throw () : IOException (msg) {}
			string getName () const throw () { return "NonBlockingIOException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Interrupted I/O Exception
		//
		// I/O 시 인터럽트가 걸린 경우
		//
		//////////////////////////////////////////////////////////////////////
		class InterruptedIOException : public IOException {
		public :
			InterruptedIOException () throw () : IOException () {}
			InterruptedIOException (const string& msg) throw () : IOException (msg) {}
			string getName () const throw () { return "InterruptedIOException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// EOF Exception
		//
		// I/O 시 EOF 를 만난 경우
		//
		//////////////////////////////////////////////////////////////////////
		class EOFException : public IOException {
		public :
			EOFException () throw () : IOException () {}
			EOFException (const string& msg) throw () : IOException (msg) {}
			string getName () const throw () { return "EOFException"; }
		};
	
		//////////////////////////////////////////////////////////////////////
		//
		// File Not Opened Exception 
		//
		//////////////////////////////////////////////////////////////////////
		class FileNotOpenedException : public IOException {
		public :
			FileNotOpenedException () throw () : IOException() {}
			FileNotOpenedException (const string& msg) throw () : IOException(msg) {}
			string getName () const throw () { return "FileNotOpenedException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// File Already Exist Exception
		//
		//////////////////////////////////////////////////////////////////////
		class FileAlreadyExistException : public IOException {
		public :
			FileAlreadyExistException () throw () : IOException() {}
			FileAlreadyExistException (const string& msg) throw () : IOException(msg) {}
			string getName () const throw () { return "FileAlreadyExistException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// File Not Exist Exception
		//
		//////////////////////////////////////////////////////////////////////
		class FileNotExistException : public IOException {
		public :
			FileNotExistException () throw () : IOException() {}
			FileNotExistException (const string& msg) throw () : IOException(msg) {}
			string getName () const throw () { return "FileNotExistException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Time out Exception
		//
		// 지정 시간이 지났을 경우
		//
		//////////////////////////////////////////////////////////////////////
		class TimeoutException : public IOException {
		public :
			TimeoutException () throw () : IOException () {}
			TimeoutException (const string& msg) throw () : IOException (msg) {}
			string getName () const throw () { return "TimeoutException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Socket Exception
		//
		// 특히 소켓에서 발생하는 예외들
		//
		//////////////////////////////////////////////////////////////////////
		class SocketException : public IOException {
		public :
			SocketException () throw () : IOException () {}
			SocketException (const string& msg) throw () : IOException (msg) {}
			string getName () const throw () { return "SocketException"; }
		};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Bind Exception
			//
			// bind()시 발생하는 예외
			//
			//////////////////////////////////////////////////////////////////////
			class BindException : public SocketException {
			public :
				BindException () throw () : SocketException () {}
				BindException (const string& msg) throw () : SocketException (msg) {}
				string getName () const throw () { return "BindException"; }
			};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Connect Exception
			//
			// 소켓 연결이 끊길 경우 (가장 많이 발생한다고 보면 된다.)
			//
			//////////////////////////////////////////////////////////////////////
			class ConnectException : public SocketException {
			public :
				ConnectException () throw () : SocketException () {}
				ConnectException (const string& msg) throw () : SocketException (msg) {}
				string getName () const throw () { return "ConnectException"; }
			};
			
		//////////////////////////////////////////////////////////////////////
		//
		// Protocol Exception
		//
		// 패킷 파싱할때 발생하는 예외들
		//
		//////////////////////////////////////////////////////////////////////
		class ProtocolException : public IOException {
		public :
			ProtocolException () throw () : IOException () {}
			ProtocolException (const string& msg) throw () : IOException (msg) {}
			string getName () const throw () { return "ProtocolException"; }
		};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Idle Exception
			//
			// 일정 시간동안 peer 로부터 입력이 없는 경우
			//
			//////////////////////////////////////////////////////////////////////
			class IdleException : public ProtocolException {
			public :
				IdleException () throw () : ProtocolException () {}
				IdleException (const string& msg) throw () : ProtocolException (msg) {}
				string getName () const throw () { return "IdleException"; }
			};
	

			//////////////////////////////////////////////////////////////////////
			//
			// Invalid Protocol Exception
			//
			// 잘못된 프로토콜
			//
			//////////////////////////////////////////////////////////////////////
			class InvalidProtocolException : public ProtocolException {
			public :
				InvalidProtocolException () throw () : ProtocolException () {}
				InvalidProtocolException (const string& msg) throw () : ProtocolException (msg) {}
				string getName () const throw () { return "InvalidProtocolException"; }
			};
	
			//////////////////////////////////////////////////////////////////////
			//
			// Insufficient Data Exception
			//
			// 아직 패킷 데이타가 완전하게 도착하지 않았을 경우
			//
			//////////////////////////////////////////////////////////////////////
			class InsufficientDataException : public ProtocolException {
			public :
				InsufficientDataException (uint size = 0) throw () : ProtocolException (), m_Size(size) {}
				InsufficientDataException (const string& msg, uint size = 0) throw () : ProtocolException (msg), m_Size(size) {}
				string getName () const throw () { return "InsufficientDataException"; }
				uint getSize () const throw () { return m_Size; }
				string toString () const throw ()
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
			// 프로토콜 예외, 시스템 예외 등으로인해서 접속을 짤라야 할 경우
			// 이 예외를 사용한다.
			// 
			//////////////////////////////////////////////////////////////////////
			class DisconnectException : public ProtocolException {
			public :
				DisconnectException () throw () : ProtocolException () {}
				DisconnectException (const string& msg) throw () : ProtocolException (msg) {}
				string getName () const throw () { return "DisconnectException"; }
			};

			//////////////////////////////////////////////////////////////////////
			// 
			// 특정 상황때 무시해야 되는 패킷이 들어왔을 경우
			// 
			//////////////////////////////////////////////////////////////////////
			class IgnorePacketException : public ProtocolException {
			public :
				IgnorePacketException () throw () : ProtocolException () {}
				IgnorePacketException (const string& msg) throw () : ProtocolException (msg) {}
				string getName () const throw () { return "IgnorePacketException"; }
			};


	//////////////////////////////////////////////////////////////////////
	//
	// Thread Exception
	//
	// 쓰레드 및 동기화 도구들에서 발생하는 예외들
	//
	//////////////////////////////////////////////////////////////////////
	class ThreadException : public Exception {
	public :
		ThreadException () throw () : Exception () {}
		ThreadException (const string& msg) throw () : Exception (msg) {}
		string getName () const throw () { return "ThreadException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// Mutex Exception
		//
		// 뮤텍스에서 발생하는 예외들
		//
		//////////////////////////////////////////////////////////////////////
		class MutexException : public ThreadException {
		public :
			MutexException () throw () : ThreadException () {}
			MutexException (const string& msg) throw () : ThreadException (msg) {}
			string getName () const throw () { return "MutexException"; }
		};

			//////////////////////////////////////////////////////////////////////
			//
			// Mutex Attribute Exception
			//
			// 뮤텍스 속성에서 발생하는 예외들
			//
			//////////////////////////////////////////////////////////////////////
			class MutexAttrException : public MutexException {
			public :
				MutexAttrException () throw () : MutexException () {}
				MutexAttrException (const string& msg) throw () : MutexException (msg) {}
				string getName () const throw () { return "MutexAttrException"; }
			};


		//////////////////////////////////////////////////////////////////////
		//
		// Conditional Variable Exception
		//
		// Conditional Variable 에서 발생하는 예외 (이름이 너무 길다.. - -)
		//
		//////////////////////////////////////////////////////////////////////
		class CondVarException : public ThreadException {
		public :
			CondVarException () throw () : ThreadException () {}
			CondVarException (const string& msg) throw () : ThreadException (msg) {}
			string getName () const throw () { return "CondVarException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Semaphore Exception
		//
		// Semaphore 에서 발생하는 예외
		//
		//////////////////////////////////////////////////////////////////////
		class SemaphoreException : public ThreadException {
		public :
			SemaphoreException () throw () : ThreadException () {}
			SemaphoreException (const string& msg) throw () : ThreadException (msg) {}
			string getName () const throw () { return "SemaphoreException"; }
		};


	//////////////////////////////////////////////////////////////////////
	//
	// SQL Exception 
	//
	// SQL 관련 예외
	//
	//////////////////////////////////////////////////////////////////////
	class SQLException : public Exception {
	public :
		SQLException () throw () : Exception() {}
		SQLException (const string& msg) throw () : Exception(msg) {}
		string getName () const throw () { return "SQLException"; }
	};

		//////////////////////////////////////////////////////////////////////
		//
		// SQL Warning
		//
		// SQL 경고문을 나타내는 예외~~
		//
		//////////////////////////////////////////////////////////////////////
		class SQLWarning : public SQLException {
		public :
			SQLWarning () throw () : SQLException() {}
			SQLWarning (const string& msg) throw () : SQLException(msg) {}
			string getName () const throw () { return "SQLWarning"; }
		};


		//////////////////////////////////////////////////////////////////////
		//
		// SQL Connect Exception
		//
		// SQL에 대한 연결 시도가 실패한 경우, 연결이 끊어졌을 경우 등
		//
		//////////////////////////////////////////////////////////////////////
		class SQLConnectException : public SQLException {
		public :
			SQLConnectException () throw () : SQLException() {}
			SQLConnectException (const string& msg) throw () : SQLException(msg) {}
			string getName () const throw () { return "SQLConnectException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Query Exception
		//
		//////////////////////////////////////////////////////////////////////
		class SQLQueryException : public SQLException {
		public :
			SQLQueryException () throw () : SQLException() {}
			SQLQueryException (const string& msg) throw () : SQLException(msg) {}
			string getName () const throw () { return "SQLQueryException"; }
		};


	//////////////////////////////////////////////////////////////////////
	//
	// Runtime Exception
	//
	// 런타임에 발생가능한 generic 한 용도로 사용될 수 있는 예외들
	//
	//////////////////////////////////////////////////////////////////////
	class RuntimeException : public Exception {
	public :
		RuntimeException () throw () : Exception () {}
		RuntimeException (const string& msg) throw () : Exception (msg) {}
		string getName () const throw () { return "RuntimeException"; }
	};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Invalid Arguemnt Exception
		//
		// 함수, 멤버함수의 파라미터가 잘못된 경우 
		//
		//////////////////////////////////////////////////////////////////////
		class InvalidArgumentException : public RuntimeException {
		public :
			InvalidArgumentException () throw () : RuntimeException () {}
			InvalidArgumentException (const string& msg) throw () : RuntimeException (msg) {}
			string getName () const throw () { return "InvalidArgumentException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Out Of Bound Exception
		//
		// 말그대로. Out Of Bound!
		//
		//////////////////////////////////////////////////////////////////////
		class OutOfBoundException : public RuntimeException {
		public :
			OutOfBoundException () throw () : RuntimeException () {}
			OutOfBoundException (const string& msg) throw () : RuntimeException (msg) {}
			string getName () const throw () { return "OutOfBoundException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Interrupted Exception
		//
		// System Call 등이 인터럽트 당했을 경우
		//
		//////////////////////////////////////////////////////////////////////
		class InterruptedException : public RuntimeException {
		public :
			InterruptedException () throw () : RuntimeException () {}
			InterruptedException (const string& msg) throw () : RuntimeException (msg) {}
			string getName () const throw () { return "InterruptedException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// No Such Element Exception
		//
		// 컬렉션에서 특정 키값을 검색했을때 그런 엘리먼트가 없는 경우
		//
		//////////////////////////////////////////////////////////////////////
		class NoSuchElementException : public RuntimeException {
		public :
			NoSuchElementException () throw () : RuntimeException () {}
			NoSuchElementException (const string& msg) throw () : RuntimeException (msg) {}
			string getName () const throw () { return "NoSuchElementException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// Duplicated Exception
		//
		// 컬렉션의 특정 키가 중복되었을 때 
		//
		//////////////////////////////////////////////////////////////////////
		class DuplicatedException : public RuntimeException {
		public :
			DuplicatedException () throw () : RuntimeException () {}
			DuplicatedException (const string& msg) throw () : RuntimeException (msg) {}
			string getName () const throw () { return "DuplicatedException"; }
		};

	//////////////////////////////////////////////////////////////////////
	//
	// Game Exception
	//
	// 게임에서 goto 용도로 사용하는 예외들.. -_-;
	//
	//////////////////////////////////////////////////////////////////////
	class GameException : public Exception {
	public :
		GameException () throw () : Exception () {}
		GameException (const string& msg) throw () : Exception (msg) {}
		string getName () const throw () { return "GameException"; }
	};
	
		//////////////////////////////////////////////////////////////////////
		//
		// Portal Exception
		//
		// PC 가 포탈을 밟았을때...�
		//
		//////////////////////////////////////////////////////////////////////
		class PortalException : public GameException {
		public :
			PortalException () throw () : GameException () {}
			PortalException (const string& msg) throw () : GameException (msg) {}
			string getName () const throw () { return "PortalException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		// 특정 좌표 주위가 꽉차서 크리처를 존에 집어넣을 수 없을 때
		//
		//////////////////////////////////////////////////////////////////////
		class EmptyTileNotExistException : public GameException {
		public :
			EmptyTileNotExistException () throw () : GameException () {}
			EmptyTileNotExistException (const string& msg) throw () : GameException (msg) {}
			string getName () const throw () { return "EmptyTileNotExistException"; }
		};

		//////////////////////////////////////////////////////////////////////
		//
		//
		//
		//////////////////////////////////////////////////////////////////////
		class InventoryFullException : public GameException {
		public :
			InventoryFullException () throw () : GameException () {}
			InventoryFullException (const string& msg) throw () : GameException (msg) {}
			string getName () const throw () { return "InventoryFullException"; }
		};


//////////////////////////////////////////////////////////////////////
//
// Error
//
//////////////////////////////////////////////////////////////////////
class Error : public Throwable {
public :
	Error () throw () : Throwable() {}
	Error (const string & msg) throw () : Throwable(msg) {}
	string getName () const throw () { return "Error"; }
};	
	//////////////////////////////////////////////////////////////////////
	//
	// Game Error
	//
	//////////////////////////////////////////////////////////////////////
	class GameError : public Error {
	public :
		GameError () throw () : Error () {}
		GameError (const string& msg) throw () : Error(msg) {}
		string getName () const throw () { return "GameError"; }
	};


	//////////////////////////////////////////////////////////////////////
	//
	// Assertion Error
	//
	//////////////////////////////////////////////////////////////////////
	class AssertionError : public Error {
	public :
		AssertionError () throw () : Error () {}
		AssertionError (const string& msg) throw () : Error(msg) {}
		string getName () const throw () { return "AssertionError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Unsupported Error
	//
	//////////////////////////////////////////////////////////////////////
	class UnsupportedError : public Error {
	public :
		UnsupportedError () throw () : Error () {}
		UnsupportedError (const string& msg) throw () : Error(msg) {}
		string getName () const throw () { return "UnsupportedError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Log Error
	//
	// 일반적인 에러와는 달리 LogError는 디폴트 로그파일에 로그될 수 없다.
	// (생각해보라. 로그매니저 자체의 에러를 어떻게 로그한다는 말인가?)
	//
	//////////////////////////////////////////////////////////////////////
	class LogError : public Error {
	public :
		LogError () throw () : Error () {}
		LogError (const string& msg) throw () : Error(msg) {}
		string getName () const throw () { return "LogError"; }
	};

	//////////////////////////////////////////////////////////////////////
	//
	// Unknown Error
	//
	//////////////////////////////////////////////////////////////////////
	class UnknownError : public Error {
	public :
		UnknownError () throw () : Error() {}
		UnknownError (const string & msg) throw () : Error(msg) {}
		UnknownError (const string & msg, uint ErrorCode) throw () : Error(msg), m_ErrorCode(ErrorCode) {}
		string getName () const throw () { return "UnknownError"; }
		uint getErrorCode () const throw () { return m_ErrorCode; }
		string toString () const throw ()
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
