/**
* @file $Header: ODBCError.cpp
* 
* NAME: ODBCError
* 
* BASE CLASSES: Error
* 
* PURPOSE: Concrete class which implements the error functions for ODBC
* 
* AUTHOR: Gowri Ramasubramanian
* 
* $Revision: 1.8 $
* 
* $Log: ODBCError.cpp,v $
* Revision 1.8  2005/08/30 05:23:25  Jignesh.Kanchanlal
* Bugs after Testing fixed
*
* Revision 1.7  2005/08/23 11:57:15  Jignesh.Kanchanlal
* Code Review Comments Incorporated
*
* Revision 1.4  2005/08/12 12:29:56  Jignesh.Kanchanlal
* Added for the first time
*
* 
* COPYRIGHT NOTICE:
* Copyright (c) 2005 C++ Capability team at Accenture. All rights reserved.
*/


///////////////////////////////////////////////////////////////
// Includes
#include <string>
#include <dbaccess/ODBCError.h> ///<header file
#include <common/GeneralException.h> ///<exceptions generated by ADBC

#ifdef ALOOGER
	#include <logger/Logger.h>
#endif

//Defines
#define BUFFSIZE 2056

namespace dbaccess {

	/** Overloaded default Constructor.
	* <BR>NAME: ODBCError
	* <BR>DESCRIPTION: Constructor for the ODBCError Object. 
	* <BR> Initialises the handle (statement, descriptor, environment
	* <BR> or connection) and the handle type to identify the handles.
	* <BR>SIDE EFFECTS: Nil
	* <BR>PARAMETERS: 
	* 	@param Nil
	* 
	*/
	ODBCError::ODBCError() : hdl_(NULL), handleType_(0)
	{
		#ifdef ALOGGER
		logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, "");
		#endif
	}

	/** Default Destructor.
	* <BR>NAME: ~ODBCError
	* <BR>DESCRIPTION: Destructor for the ODBCError Object.
	* <BR>SIDE EFFECTS: Nil
	* <BR>PARAMETERS: 
	* 	@param Nil
	* 
	*/
	ODBCError::~ODBCError()
	{
		#ifdef ALOGGER
		logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, "");
		#endif
	}

	/** Implementation in ODBC to check if there was an error.
	* <BR>NAME: isError
	* <BR>DESCRIPTION: Uses SQLGetDiagField with SQL_DIAG_RETURNCODE as the identifer. 
	* <BR> After executing any ADBC API it is recommended that the user should check whether there 
	* <BR> there was an error due to the connectivity, in this case ODBC with isError().
	* <BR> Record Number is 0 since SQL_DIAG_RETURNCODE is a header field and is ignored.
	* <BR>SIDE EFFECTS: Throws GeneralException if SQLGetDiagField returns error/invalid handle.
	* <BR>PARAMETERS: 
	* 	@param void
	* <BR>RETURN: 
	* 	@return bool - true if SQLGetDiagField returns SQL_ERROR else false.
	* 
	*/
	bool ODBCError::isError()
	{	
		SQLRETURN retCode;
		
		#ifdef ALOGGER
		logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, "SQLDiagField with ID_RETURN_CODE");
		#endif
		
		SQLRETURN rc = SQLGetDiagField(
					handleType_,
					hdl_,
					0,	
					ID_RETURN_CODE,
					&retCode,
					BUFFSIZE,
					NULL);
			
		if( (rc == SQL_ERROR) || (rc == SQL_INVALID_HANDLE) )
		{
			#ifdef ALOGGER
				logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"SQLDiagField returns error/invalid handle");
			#endif
			throw new GeneralException("SQLGetDiagField-Error/invalid handle");
		}
				
		if(retCode == SQL_ERROR)
		{	
			#ifdef ALOGGER
				logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"isError returns TRUE");
			#endif
			return true;
		}
		#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"isError returns FALSE");
		#endif
		return false;
	}

	/** Implentation in ODBC to check if there was a warning.
	* <BR>NAME: isWarning
	* <BR>DESCRIPTION: Uses SQLGetDiagField with SQL_DIAG_RETURNCODE as the identifer.
 	* <BR> After executing any ADBC API it is recommended that the user should check whether there 
	* <BR> there was a warning due to the connectivity, in this case ODBC with isWarning().
	* <BR> Record Number is 0 since SQL_DIAG_RETURNCODE is a header field and is ignored. 
	* <BR>SIDE EFFECTS: Throws GeneralException if SQLGetDiagField returns error/invalid handle.
	* <BR>PARAMETERS: 
	* 	@param void
	* <BR>RETURN: 
	* 	@return bool - true if SQLGetDiagField returns SQL_SUCCESS_WITH_INFO else false.
	*/
	bool ODBCError::isWarning()
	{
		#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"SQLDiagField with ID_RETURN_CODE");
		#endif
		SQLRETURN retCode;
			
		SQLRETURN rc = ::SQLGetDiagField(
						handleType_,
						hdl_,
						0,					
						ID_RETURN_CODE,
						&retCode,			
						BUFFSIZE,
						NULL);

		if( (rc == SQL_ERROR) || (rc == SQL_INVALID_HANDLE)  )
		{
			#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"SQLDiagField returns error/invalid handle");
			#endif
			throw new GeneralException("SQLGetDiagField-Error/invalid handle");
		}

		if( (retCode == SQL_SUCCESS_WITH_INFO) ||
			(retCode == SQL_INVALID_HANDLE) ||
			(retCode == SQL_NO_DATA) ||
			(retCode == SQL_NEED_DATA) ||
			(retCode == SQL_STILL_EXECUTING) )
		{	
			#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"SQLDiagField returns TRUE");
			#endif
			return true;
		}
		#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"SQLDiagField returns FALSE");
		#endif
		return false;
	}

	/** Implentation in ODBC to get the error code.
	* <BR>NAME: getErrorCode
	* <BR>DESCRIPTION: Uses SQLGetDiagField with SQL_DIAG_SQLSTATE as the identifer. 
	* <BR> After executing any ADBC API it is recommended that the user should check whether there 
	* <BR> was an Error due to the connectivity, in this case ODBC, using isError then use 
	* <BR> getErrorCode to retrieve the error code.
	* <BR> Record Number is 1 since ID_ERROR_CODE is not a header field and hence not ignored. 
	* <BR>SIDE EFFECTS: Throws GeneralException if SQLGetDiagField returns error/invalid handle.
	* <BR>PARAMETERS: 
	* 	@param void
	* <BR>RETURN: 
	* 	@return string - Returns the last returned error code.
	*/
	const string ODBCError::getErrorCode() const
	{	
		#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"SQLDiagField with ID_ERROR_CODE");
		#endif
		char temp[BUFFSIZE] = "";
		SQLRETURN rc = ::SQLGetDiagField(
						handleType_,
						hdl_,
						1,					
						ID_ERROR_CODE,
						temp,
						BUFFSIZE,
						NULL);
		
		if( (rc == SQL_ERROR) || (rc == SQL_INVALID_HANDLE) )
		{	
			#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"SQLDiagField returns error/invalid handle");
			#endif
			throw new GeneralException("SQLGetDiagField-Error/invalid handle");
		}
		if(rc == SQL_NO_DATA)
		{	
			#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"SQLDiagField returns no diagnostic error code");
			#endif
			return "No Diagnostic Data Found";
		}
		/*#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"ErrorCode is", string(temp) );
		#endif*/
		return string(temp);
	}

	/** Implentation in ODBC to get the error message.
	* <BR>NAME: getErrorMessage
	* <BR>DESCRIPTION: Uses SQLGetDiagField with SQL_DIAG_MESSAGE_TEXT as the identifer.
	* <BR> After executing any ADBC API it is recommended that the user should check whether there 
	* <BR> was an Error due to the connectivity, in this case ODBC, using isError then use 
	* <BR> getErrorMessage to retrieve the error message.
	* <BR> Record Number is 1 since ID_ERROR_CODE is not a header field and hence not ignored.  
	* <BR>SIDE EFFECTS: Throws GeneralException if SQLGetDiagField returns error/invalid handle.
	* <BR>PARAMETERS: 
	* 	@param void
	* <BR>RETURN: 
	* 	@return string - Returns the last returned error message.
	*/
	const string ODBCError::getErrorMessage() const
	{	
		#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"SQLDiagField with ID_ERROR_MSG");
		#endif	
		char temp[BUFFSIZE] = "";
		SQLRETURN rc = ::SQLGetDiagField(
						handleType_,
						hdl_,
						1,
						ID_ERROR_MSG,
						temp,
						BUFFSIZE ,
						NULL);

		if( (rc == SQL_ERROR) || (rc == SQL_INVALID_HANDLE) )
		{	
			#ifdef ALOGGER
				logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"SQLDiagField returns error/invalid handle");
			#endif
			throw new GeneralException("SQLGetDiagField-Error/invalid handle");
		}
		if(rc == SQL_NO_DATA)
		{	
			#ifdef ALOGGER
				logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"SQLDiagField returns no diagnostic messages");
			#endif
			return "No Diagnostic Data Found";
		}
		/*#ifdef ALOGGER
				logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
						"Error message is", getErrorCode() + ":" + string(temp) );
		#endif*/
		return getErrorCode() + ":" + string(temp);
	}

	/** Overloaded copy constructor.
	* <BR>NAME: ODBCError(const ODBCError &)
	* <BR>DESCRIPTION: Copy Constructor for the ODBCError Object.
	* <BR>SIDE EFFECTS: Being protected and overloaded the user cannot call this. Hence empty implementation.
	* <BR>PARAMETERS: 
	* 	@param Const reference to ODBCError object
	* 
	*/
	ODBCError::ODBCError(const ODBCError& other)
	{	
		#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, "CopyConstructor");
		#endif
	}

	/** Overloaded assignment operator.
	* <BR>NAME: ODBCError & operator=(const ODBCError &)
	* <BR>DESCRIPTION: Assignment operator overload for the ODBCError Object.
	* <BR>SIDE EFFECTS: Being protected and overloaded the user cannot call this. 
	* Hence empty implementation.
	* <BR>PARAMETERS: 
	* 	@param const Reference to ODBCError object
	* <BR>RETURN: 
	* 	@return Reference to ODBCError Object
	* 
	*/
	ODBCError& ODBCError::operator =(const ODBCError& other)
	{	
		#ifdef ALOGGER
			logger::Logger::getInstance().debug(__FILE__, __LINE__, __FUNCTION__, 
					"Overloaded Assignment Operator");
		#endif
		return *this;
	}

}	//namespace dbaccess
