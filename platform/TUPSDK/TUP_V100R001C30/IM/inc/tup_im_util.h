#include "tup_im_baseapi.h"
#include <string>

#include "ctk/ctk.h"
#include "cli/cli.h"
#include "cli/cleanup.h"
#include "imp/imp.h"

#include "imutil/imutil.h"

/** \brief eSpace日志实例名 */
#define TUP_IMSERVICE_LOG_INSTANCE "UC.IMClib"

/** \brief eSpace日志文件 */
#define TUP_IMSERVICE_LOG_FILE "tup_imclib.log"

TUP_UINT16 CheckValidCounts(const TUP_CHAR data[],int count);

/*******************************************
* 实现将字符串中的字符拷贝到字符数组中
* param: 入参：inStr 源字符串
*              inArrSize 目的数组长度
*        出参：outstr    目的数组
* return : true 拷贝成功， false 拷贝失败
*********************************************/
bool stringcopy(const std::string& inStr,TUP_UINT16 inArrSize, TUP_CHAR outstr[]);

void InsertDataNodeToList(TUP_S_LIST** pListHead, void* pDataNode);
