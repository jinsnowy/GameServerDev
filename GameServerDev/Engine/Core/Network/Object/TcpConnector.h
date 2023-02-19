#pragma once

namespace Core {
	namespace Network {
		class TcpConnector : public enable_shared_from_this<TcpConnector>
		{
		private:
			shared_ptr<TcpNetwork> _network;

		public:
			TcpConnector(shared_ptr<TcpNetwork> network);

			void Connect(EndPoint endPoint);
		};
	}
}