#include "tup_im_baseapi.h"
#include <string>

#include "ctk/ctk.h"
#include "cli/cli.h"
#include "cli/cleanup.h"
#include "imp/imp.h"

#include "imutil/imutil.h"

/** \brief eSpace��־ʵ���� */
#define TUP_IMSERVICE_LOG_INSTANCE "UC.IMClib"

/** \brief eSpace��־�ļ� */
#define TUP_IMSERVICE_LOG_FILE "tup_imclib.log"

TUP_UINT16 CheckValidCounts(const TUP_CHAR data[],int count);

/*******************************************
* ʵ�ֽ��ַ����е��ַ��������ַ�������
* param: ��Σ�inStr Դ�ַ���
*              inArrSize Ŀ�����鳤��
*        ���Σ�outstr    Ŀ������
* return : true �����ɹ��� false ����ʧ��
*********************************************/
bool stringcopy(const std::string& inStr,TUP_UINT16 inArrSize, TUP_CHAR outstr[]);

void InsertDataNodeToList(TUP_S_LIST** pListHead, void* pDataNode);
