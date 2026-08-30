#include "NodeRegistry.h"
#include "IFlowNode.h"

bool NodeRegistry::registerNode(const Meta& meta)
{
	auto& reg = registry();
	if (meta.typeKey.isEmpty() || reg.count(meta.typeKey))
		return false;   // 重复注册，忽略
	reg[meta.typeKey] = meta;
	return true;
}

std::unique_ptr<IFlowNode> NodeRegistry::create(const QString& typeKey)
{
	const Meta* meta = find(typeKey);
	if (!meta) return nullptr;
	return meta->creator(typeKey);
}

std::vector<NodeRegistry::Meta> NodeRegistry::all()
{
	std::vector<Meta> result;
	for (const auto& [key, meta] : registry())
		result.push_back(meta);
	return result;
}

const NodeRegistry::Meta* NodeRegistry::find(const QString& typeKey)
{
	auto& reg = registry();
	auto it = reg.find(typeKey);
	return (it == reg.end()) ? nullptr : &it->second;
}

std::map<QString, NodeRegistry::Meta>& NodeRegistry::registry()
{
	static std::map<QString, Meta> inst;
	return inst;
}
