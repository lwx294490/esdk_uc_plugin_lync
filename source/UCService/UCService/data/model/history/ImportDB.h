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
        INVALID,                            //无效的查询
        SINGLE_CONV_BY_ID,                  //单条会话通过会话id
        SINGLE_CONV_BY_OFFSET,              //单一记录通过偏移来获取
        ALL_CONV,                           //所有的会话
        ALL_CONV_BY_CONVTYPE,               //所有的会话通过会话类型
        ALL_CONV_BY_OFFSET_AND_PAGE         //所有的会话通过偏移和页数
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

    //单一记录
    static bool QuerySingleRecordByRecordId(const std::string & dbPath, 
        const DataRecordId & recordId, DQLBase<Record>::ResObjType& resObj);
    static int  QuerySingleRecordByOffset(const std::string & dbPath, 
        const std::string& offset, DQLBase<Record>::ResObjType& resObj);

    static int QueryAllRecordCount(const std::string& dbPath);

    //批量查询
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
        INVALID,                            //无效的查询

        RECORD_CNT,                         //总的记录数
        //单个查询
        SINGLE_RECORD_BY_ID,                //单条记录通过id
        SINGLE_RECORD_BY_OFFSET,            //单条记录通过偏移位置

        //批量查询
        ALL_RECORD,                         //批量查询所有的记录
        ALL_RECORD_BY_TYPE,                 //批量查询所有记录通过类型
        ALL_RECORD_BY_CONVID,               //批量查询所有的记录通过会话id
        ALL_RECORD_BY_OFFSET_AND_PAGE,      //批量查询所有的记录通过偏移和页数
        ALL_RECORD_BY_BETWEEN_DATE          //批量查询所有的记录通过时间
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
