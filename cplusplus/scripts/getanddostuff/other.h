#ifndef GETANDDOSTUFFOTHER_H
#define GETANDDOSTUFFOTHER_H

#include <QObject>
#include <QMovie>
#include <QFileInfo>
#include <QSize>
#include <QUrl>
#include <QGuiApplication>
#include <QCursor>
#include <QScreen>
#include <QColor>
#include <QDir>
#include <QTextStream>
#include "../../logger.h"

#ifdef GM
#include <GraphicsMagick/Magick++.h>
#include "../gmimagemagick.h"
#endif

class GetAndDoStuffOther : public QObject {

	Q_OBJECT

public:
	explicit GetAndDoStuffOther(QObject *parent = 0);
	~GetAndDoStuffOther();

	bool isImageAnimated(QString path);
	QSize getImageSize(QString path);
	QPoint getGlobalCursorPos();
	QColor addAlphaToColor(QString col, int alpha);
	bool amIOnLinux();
	QString trim(QString s) { return s.trimmed(); }
	int getCurrentScreen(int x, int y);
	QString getTempDir();
	QString getHomeDir();
	bool isExivSupportEnabled();
	bool isGraphicsMagickSupportEnabled();
	bool isLibRawSupportEnabled();
	QString getVersionString();

private:
	QImageReader reader;
#ifdef GM
	GmImageMagick imagemagick;
#endif

};

#endif // GETANDDOSTUFFOTHER_H
