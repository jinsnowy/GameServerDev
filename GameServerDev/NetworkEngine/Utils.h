#pragma once

class Utils
{
public:
	static std::wstring WSAGetLastErrorMsg();
	static std::wstring WSAGetLastErrorMsg(int errCode);

	template<typename T>
	static shared_ptr<T> SharedGlobal()
	{
		static shared_ptr<T> inst = make_shared<T>();

		return inst;
	}
};