#include "DjangoUserConstraintStore.h"
#include <util/httpclient.h>
#include <util/Logger.h>
#include <catmaid/persistence/django/DjangoUtils.h>
#include <boost/algorithm/string/replace.hpp>

logger::LogChannel djangouserconstraintstorelog("djangouserconstraintstorelog", "[DjangoUserConstraintStore] ");

DjangoUserConstraintStore::DjangoUserConstraintStore(const boost::shared_ptr<DjangoBlockManager> blockManager):
	_server(blockManager->getServer()),
	_project(blockManager->getProject()),
	_stack(blockManager->getStack())
{

}

pipeline::Value<UserConstraints>
DjangoUserConstraintStore::retrieveUserConstraints(const Blocks& blocks)
{
	std::ostringstream url;
	std::ostringstream post;
	std::string delim = "";
	boost::shared_ptr<ptree> pt;
	pipeline::Value<UserConstraints> userConstraintSets = pipeline::Value<UserConstraints>();
	ptree constraintsTree;

	DjangoUtils::appendProjectAndStack(url, _server, _project, _stack);
	url << "/user_constraints_by_blocks";
	post << "block_ids=";

	foreach (boost::shared_ptr<Block> block, blocks)
	{
		post << delim << block->getId();
		delim = ",";
	}

	pt = HttpClient::postPropertyTree(url.str(), post.str());

	DjangoUtils::checkDjangoError(pt, url.str());
	if (pt->get_child("ok").get_value<std::string>().compare("true") != 0)
	{
		UTIL_THROW_EXCEPTION(
			DjangoException,
			"Error finding user constraints associated to blocks. URL: " << url.str());
	}
	constraintsTree = pt->get_child("constraints");
	foreach (ptree::value_type constraintV, constraintsTree)
	{
		std::vector<unsigned int> segmentIds = std::vector<unsigned int>();
		foreach (ptree::value_type segment, constraintV.second.get_child("segment_ids"))
		{
			segmentIds.push_back(segment.second.get_value<unsigned int>());
		}
		userConstraintSets->insert(UserConstraints::value_type(
				constraintV.second.get<unsigned int>("constraint_id"),
				segmentIds));
	}

	return userConstraintSets;
}
