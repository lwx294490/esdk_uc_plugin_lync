#pragma once

#define CONVERSATION_TAB "ConversationTab"
#define CONVERSATION_MSGID_TAB "ConversationMsgIdTab"

namespace ecs {
    namespace ecsdata {
        namespace history {

            ///////////////////////////////////////////////////////////////////////////
            class   CreateConversationTabCommand : public DDLBase
            {
            public:
                CreateConversationTabCommand(const std::string& _dbName = HISTORYDB_NAME) : DDLBase(_dbName) {}

            protected:
                virtual void ComposeSQL(std::string & sql);

            }; 

            class   AddConversationCommand 
                : public DMLBase<Cvs>
            {
            public:
                AddConversationCommand(const std::string& _dbName = HISTORYDB_NAME) : DMLBase<Cvs>(_dbName) {}

				static int BatchInsert(const std::string& _dbName,ArgCtnType _resCtn);

                DEFINE_BATCH_SINGLE_ADD_MOTHOD(AddConversationCommand)

            protected:
                virtual void ComposeSQL(std::string & sql);
                virtual void Bind(IDataManipulation * dm, 
                    const DMLBase<Cvs>::ArgObjType & argObj);

            };

            class   UpdateConversationCommand 
                : public DMLBase<Cvs>
            {
            public:
                UpdateConversationCommand() : DMLBase<Cvs>(HISTORYDB_NAME) {}

            public:
                static bool UpdateParticipantsByConversationId(
                    const std::string & cvsId, const std::string & participants);

                static bool UpdateGroupNameByConversationId(
                    const std::string & cvsId, const std::string & newname);

                static bool UpdateUnReadMsgTotalByConversationId(
                    const std::string & cvsId, const int total);

                static bool UpdateMinMsgIdByConversationId(
                    const std::string & cvsId, const std::string& strMinMsgId);
            protected:
                enum
                {
                    INVALID, 
                    PARTICIPANTS,
                    CONVGROUPNAME,
                    UNREADMSGTOTAL,
                    MINMSGID
                };

            protected:
                virtual void ComposeSQL(std::string & sql);
                virtual void Bind(IDataManipulation * dm, 
                    const DMLBase<Cvs>::ArgObjType & argObj);

                DEFINE_SINGLE_EXECUTE_MOTHOD(
                    UpdateConversationCommand, UpdateParticipants, PARTICIPANTS)
                DEFINE_SINGLE_EXECUTE_MOTHOD(
                    UpdateConversationCommand, UpdateGroupName, CONVGROUPNAME)
                DEFINE_SINGLE_EXECUTE_MOTHOD(
                    UpdateConversationCommand, UpdateUnReadMsgTotal, UNREADMSGTOTAL)
                DEFINE_SINGLE_EXECUTE_MOTHOD(
                    UpdateConversationCommand, UpdateMinMsgId, MINMSGID)

            };

            class   RemoveConversationCommand 
                : public DMLBase<Cvs>
            {
            public:
                RemoveConversationCommand(const std::string& _dbName = HISTORYDB_NAME) : DMLBase<Cvs>(_dbName) {}

            public:
                static int RemoveAll();
				static int RemoveByConversationId(const std::string & cvsId);

            protected:
                enum
                {
                    INVALID, 
                    ALL, 
					CONVERSATION_ID, 
                };

            protected:
                virtual void ComposeSQL(std::string & sql);
                virtual void Bind(IDataManipulation * dm, 
                    const DMLBase<Cvs>::ArgObjType & argObj);

            };

            class   ConversationQuery : public DQLBase<Cvs>
            {
                friend class AdvConversationQuery;

            public:
                ConversationQuery(const std::string& _dbName = HISTORYDB_NAME) : DQLBase<Cvs>(_dbName) {}

            public:
                static bool QueryByConversationId(const std::string & cvsId, 
                    DQLBase<Cvs>::ResObjType & resObj);
                static int QueryByConversationType(int cvsType, 
                    DQLBase<Cvs>::ResCtnType & resCtn,const std::string& _dbName = HISTORYDB_NAME);
                static int QueryAll(DQLBase<Cvs>::ResCtnType & resCtn); 

            protected:
                enum
                {
                    INVALID, 
                    ALL, 
                    CONVERSATION_ID, 
                    CONVERSATION_TYPE
                };

            protected:
                virtual void ComposeSQL(std::string & sql);
                virtual void Bind(
                    IDataManipulation * dm, const DQLBase<Cvs>::ArgObjType & argObj);
                virtual void Extract(
                    IDataManipulation * dm, DQLBase<Cvs>::ResObjType & resObj)
                { ExtractFromConversationTab(dm, resObj, 0); }

                static int ExtractFromConversationTab(IDataManipulation * dm, 
                    DQLBase<Cvs>::ResObjType & resObj, int startIndex);

            };

            ///////////////////////////////////////////////////////////////////////////
            class   CreateConversationMsgIdTabCommand : public DDLBase
            {
            public:
                CreateConversationMsgIdTabCommand() : DDLBase(HISTORYDB_NAME) {}

            protected:
                virtual void ComposeSQL(std::string & sql);

            };

            class   AddConversationMsgIdCommand
                : public DMLBase <CvsMsgId>
            {
            public:
                AddConversationMsgIdCommand() : DMLBase <CvsMsgId>(HISTORYDB_NAME) {}

                DEFINE_BATCH_SINGLE_ADD_MOTHOD(AddConversationMsgIdCommand)

            protected:
                virtual void ComposeSQL(std::string & sql);
                virtual void Bind(IDataManipulation *                    dm,
                    const DMLBase <CvsMsgId>::ArgObjType & argObj);

            };

            class   UpdateConversationMsgIdCommand
                : public DMLBase <CvsMsgId>
            {
            public:
                UpdateConversationMsgIdCommand() : DMLBase <CvsMsgId>(HISTORYDB_NAME) {}

            public:
                static int UpdateState(int oldState, int newState);
                static int UpdateStateByConversationId(const std::string & cvsId, int oldState, int newState);

            protected:
                enum
                {
                    INVALID,
                    STATE_CHANGE,
                    STATE_CHANGE_BY_CONVERSATION_ID,
                };

            protected:
                virtual void ComposeSQL(std::string & sql);
                virtual void Bind(IDataManipulation *                    dm,
                    const DMLBase <CvsMsgId>::ArgObjType & argObj);

                DEFINE_SINGLE_EXECUTE_MOTHOD(
                    UpdateConversationMsgIdCommand, UpdateStateChange, STATE_CHANGE)
                    DEFINE_SINGLE_EXECUTE_MOTHOD(
                    UpdateConversationMsgIdCommand, UpdateStateChangeByConversationId,
                    STATE_CHANGE_BY_CONVERSATION_ID)
            };

            class   RemoveConversationMsgIdCommand
                : public DMLBase <CvsMsgId>
            {
            public:
                RemoveConversationMsgIdCommand() : DMLBase <CvsMsgId>(HISTORYDB_NAME) {}

            public:
                static int RemoveAll();
                static int RemoveByState(int state);
                static int RemoveByConversationIdAndState(const std::string & cvsId, int state);
                static int RemoveAllNotMaxByConversationIdAndState(const DMLBase<CvsMsgId>::ArgCtnType& _argCtnObj);

            protected:
                enum
                {
                    INVALID,
                    ALL,
                    STATE,
                    CONVERSATION_ID_AND_STATE,
                    ALLNOTMAX
                };

            protected:
                virtual void ComposeSQL(std::string & sql);
                virtual void Bind(IDataManipulation *                    dm,
                    const DMLBase <CvsMsgId>::ArgObjType & argObj);

            };

            class   ConversationMsgIdQuery : public DQLBase <CvsMsgId>
            {
            public:
                ConversationMsgIdQuery() : DQLBase <CvsMsgId>(HISTORYDB_NAME) {}

            public:
                static int QueryAllByConversationIdAndState(const std::string & cvsId, int state,
                    DQLBase <CvsMsgId>::ResCtnType & resCtn);
                static bool QueryLastByConversationIdAndState(const std::string & cvsId, int state,
                    DQLBase <CvsMsgId>::ResObjType & resObj);
                static int QueryLastByState(int state, DQLBase <CvsMsgId>::ResCtnType & resCtn);
                static int QueryLastByMsgtypeAndState(int msgType, int state, DQLBase <CvsMsgId>::ResCtnType & resCtn);
                static int QueryALLByMsgtypeAndState(int msgType, int state,
                    DQLBase <CvsMsgId>::ResCtnType & resCtn);
                static int QueryConversationMaxMsgID(int _type,int _state,DQLBase <CvsMsgId>::ResCtnType & _resObj);

            protected:
                enum
                {
                    INVALID,
                    ALL_BY_CONVERSATION_ID_AND_STATE,
                    LAST_BY_CONVERSATION_ID_AND_STATE,
                    LAST_BY_STATE,
                    LAST_BY_MSGTYPE_AND_STATE,
                    ALL_BY_MSGTYPE_AND_STATE,
                    CONVERSATION_MAX_MSGID
                };

            protected:
                virtual void ComposeSQL(std::string & sql);
                virtual void Bind(IDataManipulation * dm, const DQLBase <CvsMsgId>::ArgObjType & argObj);
                virtual void Extract(IDataManipulation * dm, DQLBase <CvsMsgId>::ResObjType & resObj)
                { ExtractFromConversationMsgIdTab(dm, resObj, 0); }

                static int ExtractFromConversationMsgIdTab(IDataManipulation * dm,
                    DQLBase <CvsMsgId>::ResObjType & resObj, int startIndex);

            };

        } // namespace history
    } // namespace ecsdata
} // namespace ecs
