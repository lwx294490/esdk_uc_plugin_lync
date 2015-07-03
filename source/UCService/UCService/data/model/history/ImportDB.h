#pragma once

#ifdef _lint
#define RECORD_TAB
#define CONVERSATION_TAB
#else
#define RECORD_TAB          "RecordTab"
#define CONVERSATION_TAB    "ConversationTab"
#endif

 namespace ecs {
     namespace ecsdata {
         namespace history {

class   ImportConvQuery : public DQLBase<Cvs>
{
    friend class AdvConversationQuery;
public:
    ImportConvQuery(const std::string& _dbpath = HISTORYDB_NAME) : DQLBase<Cvs>(_dbpath) {}

public:
    static bool QuerySingleConvByConvId(
        const std::string& dbPath, const std::string & cvsId, DQLBase<Cvs>::ResObjType & resObj);

    static int  QueryAllConv(
        const std::string& dbPath, DQLBase<Cvs>::ResCtnType& resCtn);
    static int  QueryAllConvByConvType(
        const std::string& dbPath, int cvsType, DQLBase<Cvs>::ResCtnType& resCtn);
    static int  QueryAllConvByOffsetAndPage(
        const std::string& dbPath, const std::size_t offset, const std::size_t page, DQLBase<Cvs>::ResCtnType & resCtn);

    static int QueryConvs(
        const std::string& dbPath, DQLBase<Cvs>::ResCtnType& resCtn, int _enumType = ALL_CONV);
protected:
    enum
    {
        INVALID,                            //��Ч�Ĳ�ѯ
        SINGLE_CONV_BY_ID,                  //�����Ựͨ���Ựid
        SINGLE_CONV_BY_OFFSET,              //��һ��¼ͨ��ƫ������ȡ
        ALL_CONV,                           //���еĻỰ
        ALL_CONV_BY_CONVTYPE,               //���еĻỰͨ���Ự����
        ALL_CONV_BY_OFFSET_AND_PAGE         //���еĻỰͨ��ƫ�ƺ�ҳ��
    };

    virtual void ComposeSQL(std::string& sql);
    virtual void Bind(IDataManipulation* dm, const DQLBase<Cvs>::ArgObjType& argObj);
    virtual void Extract(IDataManipulation* dm, DQLBase<Cvs>::ResObjType& resObj) 
    { (void)ExtractFromTab(dm, resObj, 0); }
private:
    
    int ExtractFromTab(IDataManipulation* dm, DQLBase<Cvs>::ResObjType& resObj, int startIndex) const;
};

class   ImportRecordQuery : public DQLBase<Record>
{
    /*ArgObjType : class Record, ArgCtnT    : std::vector<Record>
     *ResObjType : class Record, ResCtnType : std::vector<Record>
     */
    friend class AdvConversationQuery;

public:
    ImportRecordQuery(std::string dsName = HISTORYDB_NAME) : DQLBase<Record>(dsName) {}

public:

    //��һ��¼
    static bool QuerySingleRecordByRecordId(const std::string & dbPath, 
        const DataRecordId & recordId, DQLBase<Record>::ResObjType& resObj);
    static int  QuerySingleRecordByOffset(const std::string & dbPath, 
        const std::string& offset, DQLBase<Record>::ResObjType& resObj);

    static int QueryAllRecordCount(const std::string& dbPath);

    //������ѯ
    static int  QueryAllRecord(const std::string& dbPath, 
        DQLBase<Record>::ResCtnType & resCtn);
    static int  QueryAllRecordByRecordType(const std::string& dbPath, 
        int recordType, DQLBase<Record>::ResCtnType & resCtn);
    static int  QueryAllRecordByConvId(const std::string& dbPath, 
        const std::string & cvsId, DQLBase<Record>::ResCtnType & resCtn);
    static int  QueryAllRecordByOffsetAndPage(const std::string& dbPath, 
        const std::size_t offset, const std::size_t page, DQLBase<Record>::ResCtnType & resCtn);
    static int  QueryAllRecordByBetweenDate(const std::string & dbPath,
        const std::string& begindate, const std::string& enddate, DQLBase<Record>::ResCtnType & resCtn);

    static int QueryRecords(const std::string& dbPath, 
        DQLBase<Record>::ResCtnType& resCtn, int enumType = ALL_RECORD);

protected:
    enum
    {
        INVALID,                            //��Ч�Ĳ�ѯ

        RECORD_CNT,                         //�ܵļ�¼��
        //������ѯ
        SINGLE_RECORD_BY_ID,                //������¼ͨ��id
        SINGLE_RECORD_BY_OFFSET,            //������¼ͨ��ƫ��λ��

        //������ѯ
        ALL_RECORD,                         //������ѯ���еļ�¼
        ALL_RECORD_BY_TYPE,                 //������ѯ���м�¼ͨ������
        ALL_RECORD_BY_CONVID,               //������ѯ���еļ�¼ͨ���Ựid
        ALL_RECORD_BY_OFFSET_AND_PAGE,      //������ѯ���еļ�¼ͨ��ƫ�ƺ�ҳ��
        ALL_RECORD_BY_BETWEEN_DATE          //������ѯ���еļ�¼ͨ��ʱ��
    };

    virtual void ComposeSQL(std::string& _sql);
    virtual void Bind(IDataManipulation* dm, const DQLBase<Record>::ArgObjType& argObj);
    virtual void Extract(IDataManipulation* dm, DQLBase<Record>::ResObjType& resObj);
private:
    int ExtractFromRecordTab(IDataManipulation* dm, DQLBase<Record>::ResObjType& resObj, int startIndex) const;
};

    } // namespace history
  } // namespace ecsdata
} // namespace ecs
