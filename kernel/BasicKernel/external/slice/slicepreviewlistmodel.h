#ifndef _NULLSPACE_SLICEPREVIEWLISTMODEL_1589874729758_H
#define _NULLSPACE_SLICEPREVIEWLISTMODEL_1589874729758_H

#include <QAbstractListModel>
#include <QImage>

namespace creative_kernel
{
    class Printer;
    class SliceAttain;
    class SlicePreviewFlow;
    class ImageProvider;
    class SlicePreviewListModel : public QAbstractListModel
    {
        Q_OBJECT
    signals:
        void dataChanged();
        void updatePictureFinished();

    public:
        enum Role
        {
            PictureRole = Qt::UserRole + 1,
            IsSlicedRole,
            imageSourceRole
        };

        SlicePreviewListModel(QObject* parent = NULL);
        virtual ~SlicePreviewListModel();

        void setCaptureFlow(SlicePreviewFlow* captor) { m_captor = captor; }

        void update();

    // private slots:
        void updatePicture(int idx = -1);

        void beginModify();
        void endModify();

        void updateImageProvider();

        void setPicture(int idx, const QImage& img);
        QImage picture(int idx) const;

        void setIsSliced(int idx, bool isSliced);
        bool isSliced(int idx);

        void setAttain(int idx, SliceAttain* attain);
        SliceAttain* attain(int idx);

        int rowCount(const QModelIndex& parent = QModelIndex()) const override;

        void setEnabled(bool enabled);


    protected:
        QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
        virtual QHash<int, QByteArray> roleNames() const override;

    private:
        bool m_capturingPicture { false };
        bool m_isChanging{ false };
        bool m_enabled{ true };

        int m_imageBase {0};

        QList<ImageProvider*> m_pictureProviders;
        QList<Printer*> m_captureQueue;
        SlicePreviewFlow* m_captor;

    };
};

#endif // _NULLSPACE_SLICEPREVIEWLISTMODEL_1589874729758_H