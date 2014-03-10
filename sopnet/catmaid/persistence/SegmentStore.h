#ifndef SEGMENT_STORE_H__
#define SEGMENT_STORE_H__

#include <boost/unordered_map.hpp>

#include <sopnet/segments/Segment.h>
#include <sopnet/segments/Segments.h>
#include <sopnet/block/Block.h>
#include <sopnet/block/Blocks.h>
#include <pipeline/Data.h>
#include <pipeline/Value.h>
#include <sopnet/features/Features.h>
#include <catmaid/persistence/SegmentPointerHash.h>

/**
 * Abstract Data class that handles the practicalities of storing and retrieving Segments from a store.
 */
class SegmentStore : public pipeline::Data
{
public:
	typedef boost::unordered_map<boost::shared_ptr<Segment>,
								 std::vector<double>,
								 SegmentPointerHash,
								 SegmentPointerEquals> SegmentFeaturesMap;
	
    /**
     * Associates a segment with a block
     * @param segment - the segment to store.
     * @param block - the block containing the segment.
     */
    virtual void associate(pipeline::Value<Segments> segments,
						   pipeline::Value<Block> block) = 0;

    /**
     * Retrieve all segments that are at least partially contained in the given block.
     * @param block - the Block for which to retrieve all segments.
     */
    virtual pipeline::Value<Segments> retrieveSegments(pipeline::Value<Blocks> blocks) = 0;

	/**
	 * Retrieve a set of Blocks that are associated with the given Segment.
	 * @param segment - the Segment for which to retrieve associated Blocks
	 */
	virtual pipeline::Value<Blocks> getAssociatedBlocks(pipeline::Value<Segment> segment) = 0;
	
	/**
	 * Store a set of Features associated to a set of Segments. Segments must be associated before
	 * Features may be associated with them.
	 * @param features - the Features to store
	 * @return the number of Segments for which Features were stored. For instance, if this is not
	 * equal to the size of features, then there were Segments for which Features were calculated
	 * but not stored. This may not necessarily be an error, however.
	 */
	virtual int storeFeatures(pipeline::Value<Features> features) = 0;

	/**
	 * Retrieve a set of Feautres associated to the set of given Segments.
	 * @param segments - the Segments for which to retrieve Features
	 * @return a map from a shared_ptr to a Segment to a vector of double values representing the
	 * features for that Segment.
	 * 
	 * Conversion to a Features object is handled in SegmentReader.
	 */
	virtual pipeline::Value<SegmentFeaturesMap>
		retrieveFeatures(pipeline::Value<Segments> segments) = 0;
	
	virtual std::vector<std::string> getFeatureNames() = 0;

	virtual void dumpStore() = 0;
};


#endif //SEGMENT_STORE_H__