#pragma once

class Utils
{
public:
	static std::string WSAGetLastErrorMsg();
	static std::string WSAGetLastErrorMsg(int errCode);

	template<typename T>
	static shared_ptr<T> SharedGlobal()
	{
		static shared_ptr<T> inst = make_shared<T>();

		return inst;
	}
};