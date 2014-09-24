#ifndef DJANGO_USER_CONSTRAINT_STORE_H__
#define DJANGO_USER_CONSTRAINT_STORE_H__

#include <catmaid/persistence/UserConstraintStore.h>
#include <catmaid/persistence/django/DjangoBlockManager.h>

/**
 * DjangoUserConstraintStore is a CATMAID/Django-backed user constraint store. UserConstraints are
 * stored in the django database and transferred via http requests.
 */
class DjangoUserConstraintStore : public UserConstraintStore
{
public:
	/**
	 * Create a DjangoUserConstraintStore over the same parameters given to the DjangoBlockManager here.
	 */
	DjangoUserConstraintStore(const boost::shared_ptr<DjangoBlockManager> blockManager);

    pipeline::Value<UserConstraints> retrieveUserConstraints(const Blocks& blocks);

	//pipeline::Value<Blocks> getAssociatedBlocks(pipeline::Value<unsigned int> constraintId);

	//void dumpStore();

private:

	const boost::shared_ptr<DjangoBlockManager> _blockManager;
	const std::string _server;
	const unsigned int _project, _stack;
};


#endif //DJANGO_USER_CONSTRAINT_STORE_H__