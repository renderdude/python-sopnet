#ifndef SOPNET_SEGMENTS_SEGMENT_HASH_H__
#define SOPNET_SEGMENTS_SEGMENT_HASH_H__

#include <cstddef>
#include <vector>
#include <slices/SliceHash.h>

typedef std::size_t SegmentHash;

// forward declaration
class Segment;

SegmentHash hash_value(const Segment& segment);

SegmentHash hash_value(std::vector<SliceHash> sliceHashes);

SegmentHash hash_value(const std::vector<SliceHash>& leftSliceHashes,
						const std::vector<SliceHash>& rightSliceHashes);

#endif // SOPNET_SEGMENTS_SEGMENT_HASH_H__

