#ifndef CREATIVE_KERNEL_MODEL_TOO_TALL_MESSAGE_202403041954_H
#define CREATIVE_KERNEL_MODEL_TOO_TALL_MESSAGE_202403041954_H

#include <QObject>
#include "basickernelexport.h"
#include "external/message/messageobject.h"

namespace creative_kernel
{
	class ModelN;
	class ModelTooTallMessage : public MessageObject
	{
		Q_OBJECT

	public:
		ModelTooTallMessage(QList<ModelN*> models, QObject* parent = NULL);
		~ModelTooTallMessage();
	protected:
		virtual int codeImpl() override;
		virtual int levelImpl() override;
		virtual QString messageImpl() override;
		virtual QString linkStringImpl() override;
		virtual void handleImpl() override;

	private:
		QList<ModelN*> m_models;
		int m_level{ 2 };
	};

};


#endif // !CREATIVE_KERNEL_MODEL_TOO_TALL_MESSAGE_202403041954_H