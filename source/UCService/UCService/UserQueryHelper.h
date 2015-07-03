#pragma once

class CUserQueryHelper
{
public:
	bool GetUserInfoFromList(const IM_S_QUERY_USERINFO_ACK& ack
		, const TUP_INT8 acTelNum[]
	, IM_S_USERINFO& userInfo
		) const;

	bool GetTargetUserInfo(const TUP_INT8 acTelNum[], IM_S_USERINFO& userInfo)const;
};
