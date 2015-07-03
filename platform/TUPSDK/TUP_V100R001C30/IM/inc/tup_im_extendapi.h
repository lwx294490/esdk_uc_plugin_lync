#ifndef _TUP_IM_EXTENDAPI_H_
#define _TUP_IM_EXTENDAPI_H_

#include "tup_im_extenddef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */


/**
* <b>Description:</b> This function is used to send file transfer request
* <br><b>Purpose:</b> Start file transfer user this function
*
* @param[in] arg request
* @return TUP_SUCCESS Indicates operation succeeds
*	<br>Other value Indicates operation fails
* @see 
*/
TUP_API TUP_RESULT tup_im_sendp2pfile(const IM_S_SENDP2PFILE_ARG* arg);

/**
* <b>Description:</b> This function is used to accept file transfer
* <br><b>Purpose:</b> Accept file transfer use this function
*
* @param[in] arg request
* @return TUP_SUCCESS Indicates operation succeeds
*	<br>Other value Indicates operation fails
* @see 
*/
TUP_API TUP_RESULT tup_im_acceptp2pfile(const IM_S_ACCEPTP2PFILE_ARG* arg);

/**
* <b>Description:</b> This function is used to reject file transfer
* <br><b>Purpose:</b> User want to reject request of file transfer, use this function.
*
* @param[in] arg request
* @return TUP_SUCCESS Indicates operation succeeds
*	<br>Other value Indicates operation fails
* @see 
*/
TUP_API TUP_RESULT tup_im_rejectp2pfile(const IM_S_REJECTP2PFILE_ARG* arg);

/**
* <b>Description:</b> This function is used to cancel file transfer
* <br><b>Purpose:</b> Sender want to cancel file transfer, use this function.
*
* @param[in] arg request
* @return TUP_SUCCESS Indicates operation succeeds
*	<br>Other value Indicates operation fails
* @see 
*/
TUP_API TUP_RESULT tup_im_cancelp2pfile(const IM_S_CANCELP2PFILE_ARG* arg);

/**
* <b>Description:</b> This function is used to send SMS
* <br><b>Purpose:</b> User want to send SMS, use this function
*
* @param[in] arg request
* @return TUP_SUCCESS Indicates operation succeeds
*	<br>Other value Indicates operation fails
* @see 
*/
TUP_API TUP_RESULT tup_im_sendsms(const IM_S_SENDSMS_ARG* arg);


#ifdef __cplusplus
#if __cplusplus
}
#endif /*  __cpluscplus */
#endif /*  __cpluscplus */



#endif //_TUP_IM_EXTENDAPI_H_