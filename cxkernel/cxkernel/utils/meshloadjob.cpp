#include "meshloadjob.h"

#include "qtusercore/module/progressortracer.h"
#include "qtusercore/string/resourcesfinder.h"

#include "cxkernel/interface/modelninterface.h"
#include "cxkernel/data/trimeshutils.h"

namespace cxkernel
{
	MeshLoadJob::MeshLoadJob(QObject* parent)
		: MeshJob(parent)
	{
	}

	MeshLoadJob::~MeshLoadJob()
	{
	}

	void MeshLoadJob::setFileName(const QString& fileName)
	{
		m_fileName = fileName;
	}

	QString MeshLoadJob::name()
	{
		return "Load Mesh";
	}

	QString MeshLoadJob::description()
	{
		return "Load Mesh.";
	}

	void MeshLoadJob::setModelNDataProcessor(ModelNDataProcessor* processor)
	{
		m_processor = processor;
	}

	void MeshLoadJob::failed()
	{
		qDebug() << "MeshLoadJob::failed.";
		if (m_processor)
		{
			m_processor->onMeshLoadFail();
		}

		notifyObserver(&MeshJobObserver::onFinished);
	}

	void MeshLoadJob::successed(qtuser_core::Progressor* progressor)
	{
		QString shortName = m_fileName;
		QStringList stringList = shortName.split("/");
		if (stringList.size() > 0)
			shortName = stringList.back();

		ModelCreateInput input;
		input.mesh = m_mesh;
		input.fileName = m_fileName;
		input.name = shortName;
		input.type = ModelNDataType::mdt_file;
		addModelFromCreateInput(input);

		notifyObserver(&MeshJobObserver::onFinished);
	}

	void MeshLoadJob::work(qtuser_core::Progressor* progressor)
	{
		qtuser_core::ProgressorTracer tracer(progressor);

		m_mesh = loadMeshFromName(m_fileName, &tracer);
	}
}
