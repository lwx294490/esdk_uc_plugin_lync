#pragma once
//去掉缺省构造函数未定义的pclint1712 报告
//lint -e1712

#include <string>


namespace ecs {
  namespace ecsdata {

/**
* \brief Base class of all exception classes in ecsdata module.
* \note Should be try-catch-ed by all the business modules that use ecsdata.
* \author c00161520 (chenchangxuan)
* \version 1.0.0 initial version
*/
class   ECSDataException : public std::exception
{
public:
  /**
  * \brief Constructor.
  * \param[in] errCode  error code
  * \param[in] errMsg   error message
  * \param[out] N/A
  * \return N/A
  */
  explicit ECSDataException(int errCode, std::string errMsg = "") 
    : errCode_(errCode), errMsg_(errMsg) {}

  /**
  * \brief Destructor.
  * \param[in] N/A
  * \param[out] N/A
  * \return N/A
  */
  virtual ~ECSDataException() throw(){}

  /**
  * \brief Get error name.\n
  *        Should be overridden by sub-classes.
  *        Its value is the name of the exception class by default.
  * \param[in] N/A
  * \param[out] N/A
  * \return error name (name of exception class)
  */
  virtual std::string GetErrorName() const { return "ECSDataException"; }

  /**
  * \brief Get error code.
  * \param[in] N/A
  * \param[out] N/A
  * \return error code
  */
  int GetErrorCode() const { return errCode_; }

  /**
  * \brief Get detailed error message.
  * \param[in] N/A
  * \param[out] N/A
  * \return error message
  */
  virtual std::string GetErrorMsg() { return errMsg_; }

protected:
  int errCode_; // error code
  std::string errMsg_; // error message

}; // ECSDataException

/**
* \brief SQLite exception.
* \note Will be thrown when SQLite API returns an error code.
* \author c00161520 (chenchangxuan)
* \version 1.0.0 initial version
*/
class   SQLiteException : public ECSDataException
{
public:
  /**
  * \brief Constructor
  * \param[in] errCode      result code of SQLite API.\n
  * \param[in] sqliteErrMsg detailed error message.
  *                         will be generated based on errCode if not supplied.
  * \param[out] N/A
  * \return N/A
  */
  explicit SQLiteException(int errCode, const std::string & sqliteErrMsg = "") 
    : ECSDataException(errCode, sqliteErrMsg)
  {
      if (errMsg_.empty())
        errMsg_ = GetErrorMsgFromErrorCode(errCode);
  }

  /**
  * \brief Destructor
  * \param[in] N/A
  * \param[out] N/A
  * \return N/A
  */
  ~SQLiteException() throw(){}

  /**
  * \brief Get error name.
  * \param[in] N/A
  * \param[out] N/A
  * \return error name (name of this class)
  */
  virtual std::string GetErrorName() const { return "SQLiteException"; }

protected:
  // if the error message parameter is not supplied in constructor, 
  // this function will be called to generate it based on errCode parameter.
  // its implementation simply stringlize SQLite result code, for example : 
  // SQLITE_ERROR(1) result code will generate "SQLITE_ERROR" string message.
  // implemented in SQLiteWrapper.cpp
  static const char * GetErrorMsgFromErrorCode(int errCode);

}; // class SQLiteException

  } // namespace ecsdata
} // namespace ecs
