#include "{{parser.package_name}}Handler.h"

{%- for pkt in parser.total_pkt %}
DEFINE_PROTOCOL({{parser.package_name}}::{{pkt.name}}, Core::Network::Packet::{{parser.package_name}}Protocol::{{pkt.name}});
{%- endfor %}
