#pragma once

namespace Core {
	namespace Network {
		namespace Protocol {
			class TypeCode {
			public:
				template<typename T>
				static int Get() { return 0; }
			};
		}
	}
}

#define USE_PROTOCOL(P)\
template<>\
int Core::Network::Protocol::TypeCode::Get<P>();

#define DEFINE_PROTOCOL(P, V)\
template<>\
int Core::Network::Protocol::TypeCode::Get<P>() { return (int)V; }