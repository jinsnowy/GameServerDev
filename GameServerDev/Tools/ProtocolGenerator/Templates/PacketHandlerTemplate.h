#pragma once

#pragma warning( push )
#pragma warning(disable : 4946)
#pragma warning(disable : 4251)
#include "{{parser.package_name}}.pb.h"
#pragma warning( pop ) 

#include "Engine/Core/Network/Protocol/Protocol.h"
#include "Engine/Core/Network/Packet/PacketHeader.h"
#include "Engine/Core/Network/Packet/PacketHandler.h"

{%- for pkt in parser.total_pkt %}
USE_PROTOCOL({{parser.package_name}}::{{pkt.name}});
{%- endfor %}

namespace Core
{
namespace Network
{
namespace Packet
{
	enum class {{parser.package_name}}Protocol : int
	{
	{%- for pkt in parser.total_pkt %}
		{{pkt.name}} = {{pkt.id}},
	{%- endfor %}

		START = {{parser.start_id}},
		END = {{parser.end_id}}
	};

	class {{parser.package_name}}PacketHandler: public PacketHandler
	{
	public:
		virtual bool IsValidProtocol(int protocol) override
		{
			return protocol >= (int){{parser.package_name}}Protocol::START && protocol <= (int){{parser.package_name}}Protocol::END;
		}

		virtual void HandleRecv(const std::shared_ptr<Session::SessionBase>& session, const PacketHeader & header, char* buffer) override
		{
			switch (({{parser.package_name}}Protocol)header.protocol)
			{
	{%- for pkt in parser.total_pkt %}
			case {{parser.package_name}}Protocol::{{pkt.name}}:
				on{{pkt.name_res}}(session, Parse<{{parser.package_name}}::{{pkt.name}}> (buffer, header.size));
				break;
	{%- endfor %}
			}
		}

	public:
	{%- for pkt in parser.total_pkt %}
		virtual void on{{pkt.name_res}}(const std::shared_ptr<Session::SessionBase>&, {{parser.package_name}}::{{pkt.name}} pkt) {}
	{%- endfor %}
	};

}
}
}
