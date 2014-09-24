#ifndef USER_CONSTRAINT_STORE_H__
#define USER_CONSTRAINT_STORE_H__

#include <catmaid/blocks/Blocks.h>
#include <sopnet/inference/UserConstraints.h>
#include <pipeline/Data.h>
#include <pipeline/Value.h>

/**
 * Abstract Data class that handles the practicalities of storing and retrieving UserConstraints from a store.
 */
class UserConstraintStore : public pipeline::Data
{
public:
    /**
     * Retrieve all user constraints that are at least partially contained in the given block.
     * @param block - the Block for which to retrieve all segments.
     */
    virtual pipeline::Value<UserConstraints> retrieveUserConstraints(const Blocks& blocks) = 0;

	/**
	 * Retrieve a set of Blocks that are associated with the given user constraint.
	 * @param constraintId - the ID of the user constraints for which to retrieve associated Blocks
	 */
	//virtual pipeline::Value<Blocks> getAssociatedBlocks(pipeline::Value<unsigned int> constraintId) = 0;
};


#endif //USER_CONSTRAINT_STORE_H__