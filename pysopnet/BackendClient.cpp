#include "config.h"
#include <catmaid/persistence/django/DjangoSegmentStore.h>
#include <catmaid/persistence/catmaid/CatmaidStackStore.h>
#ifdef HAVE_PostgreSQL
#include <catmaid/persistence/postgresql/PostgreSqlSliceStore.h>
#endif
#include <catmaid/persistence/local/LocalBlockManager.h>
#include <catmaid/persistence/local/LocalStackStore.h>
#include <catmaid/persistence/local/LocalSliceStore.h>
#include <catmaid/persistence/local/LocalSegmentStore.h>
#include "BackendClient.h"
#include "logging.h"

namespace python {

#if 0
boost::shared_ptr<BlockManager>
BackendClient::createBlockManager(const ProjectConfiguration& configuration) {

	if (configuration.getBackendType() == ProjectConfiguration::Local) {

		LOG_USER(pylog) << "[BackendClient] create local block manager" << std::endl;

		boost::shared_ptr<LocalBlockManager> localBlockManager = boost::make_shared<LocalBlockManager>(
				LocalBlockManager(
						configuration.getVolumeSize(),
						configuration.getBlockSize(),
						configuration.getCoreSize()));

		return localBlockManager;
	}

	if (configuration.getBackendType() == ProjectConfiguration::Django ||
	    configuration.getBackendType() == ProjectConfiguration::PostgreSql) {

		LOG_USER(pylog) << "[BackendClient] create django block manager" << std::endl;

		_djangoBlockManager = DjangoBlockManager::getBlockManager(
				configuration.getCatmaidHost(),
				configuration.getCatmaidRawStackId(),
				configuration.getCatmaidProjectId());

		return _djangoBlockManager;
	}

	UTIL_THROW_EXCEPTION(UsageError, "unknown backend type " << configuration.getBackendType());
}
#endif

boost::shared_ptr<StackStore>
BackendClient::createStackStore(const ProjectConfiguration& configuration, StackType type) {

	if (configuration.getBackendType() == ProjectConfiguration::Local) {

		LOG_USER(pylog) << "[BackendClient] create local stack store for membranes" << std::endl;

		return boost::make_shared<LocalStackStore>(type == Raw ? "./raw" : "./membranes");
	}

	if (configuration.getBackendType() == ProjectConfiguration::PostgreSql) {

		LOG_USER(pylog) << "[BackendClient] create catmaid stack store for membranes" << std::endl;

		if (type == Raw)
			return boost::make_shared<CatmaidStackStore>(
					configuration.getCatmaidHost(),
					configuration.getCatmaidProjectId(),
					configuration.getCatmaidRawStackId());
		else
			return boost::make_shared<CatmaidStackStore>(
					configuration.getCatmaidHost(),
					configuration.getCatmaidProjectId(),
					configuration.getCatmaidMembraneStackId());
	}

	UTIL_THROW_EXCEPTION(UsageError, "unknown backend type " << configuration.getBackendType());
}

boost::shared_ptr<SliceStore>
BackendClient::createSliceStore(const ProjectConfiguration& configuration) {

	if (configuration.getBackendType() == ProjectConfiguration::Local) {

		LOG_USER(pylog) << "[BackendClient] create local slice store" << std::endl;

		return boost::make_shared<LocalSliceStore>();
	}

#ifdef HAVE_PostgreSQL
	if (configuration.getBackendType() == ProjectConfiguration::PostgreSql) {

		LOG_USER(pylog) << "[BackendClient] create postgresql slice store" << std::endl;

		return boost::make_shared<PostgreSqlSliceStore>(configuration);
	}
#endif // HAVE_PostgreSQL

	UTIL_THROW_EXCEPTION(UsageError, "unknown backend type " << configuration.getBackendType());
}

boost::shared_ptr<SegmentStore>
BackendClient::createSegmentStore(const ProjectConfiguration& configuration) {

	if (configuration.getBackendType() == ProjectConfiguration::Local) {

		LOG_USER(pylog) << "[BackendClient] create local segment store" << std::endl;

		return boost::make_shared<LocalSegmentStore>();
	}

	if (configuration.getBackendType() == ProjectConfiguration::PostgreSql) {

		LOG_USER(pylog) << "[BackendClient] create postgresql segment store" << std::endl;

		UTIL_THROW_EXCEPTION(NotYetImplemented, "the postgresql segment store does not exist, yet");
	}

	UTIL_THROW_EXCEPTION(UsageError, "unknown backend type " << configuration.getBackendType());
}

} // namespace python
