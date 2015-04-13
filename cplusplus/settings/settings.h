#ifndef SETTINGS_H
#define SETTINGS_H

//******************************************************//
// THIS IS THE GLOBAL VERSION STRING, ONCE DEFINED HERE //
//******************************************************//
#define VERSION "1.2"
//******************************************************//
//******************************************************//

#include <iostream>
#include <QObject>
#include <QSettings>
#include <QDir>
#include <QFileSystemWatcher>
#include <QtDebug>
#include <QTimer>

// Convenience class to access and change permanent settings

class Settings : public QObject {

	Q_OBJECT

public:
	explicit Settings(QObject *parent = 0) : QObject(parent) {
		verbose = false;
		readSettings();
		watcher = new QFileSystemWatcher;
		watcher->addPath(QDir::homePath() + "/.photoqt/settings");
		connect(watcher, SIGNAL(fileChanged(QString)), this, SLOT(readSettings()));

		saveSettingsTimer = new QTimer;
		saveSettingsTimer->setInterval(400);
		saveSettingsTimer->setSingleShot(true);
		connect(saveSettingsTimer, SIGNAL(timeout()), this, SLOT(saveSettings()));
	}

	bool verbose;

	// The current version
	QString version;

	// The language selected and available languages
	QString language;
	QString getLanguage() { return language; }
	void setLanguage(QString c) { language = c; saveSettingsTimer->start(); }
	Q_PROPERTY(QString language READ getLanguage WRITE setLanguage NOTIFY languageChanged)

	// Possibility to en-/disable animated fade-in
	bool myWidgetAnimated;
	bool getMyWidgetAnimated() { return myWidgetAnimated; }
	void setMyWidgetAnimated(bool c) { myWidgetAnimated = c; saveSettingsTimer->start(); }
	Q_PROPERTY(bool myWidgetAnimated READ getMyWidgetAnimated WRITE setMyWidgetAnimated NOTIFY myWidgetAnimatedChanged)

	// Possibility to en-/disable save/restore of window geometry on quit
	bool saveWindowGeometry;
	bool getSaveWindowGeometry() { return saveWindowGeometry; }
	void setSaveWindowGeometry(bool c) { saveWindowGeometry = c; saveSettingsTimer->start(); }
	Q_PROPERTY(bool saveWindowGeometry READ getSaveWindowGeometry WRITE setSaveWindowGeometry NOTIFY saveWindowGeometryChanged)

	// Keep PhotoQt on top of other windows?
	bool keepOnTop;
	// Is composite enabled?
	bool composite;
	bool getComposite() { return composite; }
	void setComposite(bool c) { composite = c; saveSettingsTimer->start(); }
	Q_PROPERTY(bool composite READ getComposite WRITE setComposite NOTIFY compositeChanged)

	// Set the background color
	int bgColorRed;
	int getBgColorRed() { return bgColorRed; }
	void setBgColorRed(int b) { bgColorRed = b; saveSettingsTimer->start(); }
	Q_PROPERTY(int bgColorRed READ getBgColorRed WRITE setBgColorRed NOTIFY bgColorRedChanged)

	int bgColorGreen;
	int getBgColorGreen() { return bgColorGreen; }
	void setBgColorGreen(int b) { bgColorGreen = b; saveSettingsTimer->start(); }
	Q_PROPERTY(int bgColorGreen READ getBgColorGreen WRITE setBgColorGreen NOTIFY bgColorGreenChanged)

	int bgColorBlue;
	int getBgColorBlue() { return bgColorBlue; }
	void setBgColorBlue(int b) { bgColorBlue = b; saveSettingsTimer->start(); }
	Q_PROPERTY(int bgColorBlue READ getBgColorBlue WRITE setBgColorBlue NOTIFY bgColorBlueChanged)

	int bgColorAlpha;
	int getBgColorAlpha() { return bgColorAlpha; }
	void setBgColorAlpha(int b) { bgColorAlpha = b; saveSettingsTimer->start(); }
	Q_PROPERTY(int bgColorAlpha READ getBgColorAlpha WRITE setBgColorAlpha NOTIFY bgColorAlphaChanged)


	// Background image in use?
	bool backgroundImageScreenshot;
	bool getBackgroundImageScreenshot() { return backgroundImageScreenshot; }
	void setBackgroundImageScreenshot(bool b) { backgroundImageScreenshot = b; saveSettingsTimer->start(); }
	Q_PROPERTY(bool backgroundImageScreenshot READ getBackgroundImageScreenshot WRITE setBackgroundImageScreenshot NOTIFY backgroundImageScreenshotChanged)

	bool backgroundImageUse;
	bool getBackgroundImageUse() { return backgroundImageUse; }
	void setBackgroundImageUse(bool b) { backgroundImageUse = b; saveSettingsTimer->start(); }
	Q_PROPERTY(bool backgroundImageUse READ getBackgroundImageUse WRITE setBackgroundImageUse NOTIFY backgroundImageUseChanged)

	QString backgroundImagePath;
	QString getBackgroundImagePath() { return backgroundImagePath; }
	void setBackgroundImagePath(QString b) { backgroundImagePath = b; saveSettingsTimer->start(); }
	Q_PROPERTY(QString backgroundImagePath READ getBackgroundImagePath WRITE setBackgroundImagePath NOTIFY backgroundImagePathChanged)

	bool backgroundImageScale;
	bool getBackgroundImageScale() { return backgroundImageScale; }
	void setBackgroundImageScale(bool b) { backgroundImageScale = b; saveSettingsTimer->start(); }
	Q_PROPERTY(bool backgroundImageScale READ getBackgroundImageScale WRITE setBackgroundImageScale NOTIFY backgroundImageScaleChanged)

	bool backgroundImageScaleCrop;
	bool getBackgroundImageScaleCrop() { return backgroundImageScaleCrop; }
	void setBackgroundImageScaleCrop(bool b) { backgroundImageScaleCrop = b; saveSettingsTimer->start(); }
	Q_PROPERTY(bool backgroundImageScaleCrop READ getBackgroundImageScaleCrop WRITE setBackgroundImageScaleCrop NOTIFY backgroundImageScaleCropChanged)

	bool backgroundImageStretch;
	bool getBackgroundImageStretch() { return backgroundImageStretch; }
	void setBackgroundImageStretch(bool b) { backgroundImageStretch = b; saveSettingsTimer->start(); }
	Q_PROPERTY(bool backgroundImageStretch READ getBackgroundImageStretch WRITE setBackgroundImageStretch NOTIFY backgroundImageStretchChanged)

	bool backgroundImageCenter;
	bool getBackgroundImageCenter() { return backgroundImageCenter; }
	void setBackgroundImageCenter(bool b) { backgroundImageCenter = b; saveSettingsTimer->start(); }
	Q_PROPERTY(bool backgroundImageCenter READ getBackgroundImageCenter WRITE setBackgroundImageCenter NOTIFY backgroundImageCenterChanged)

	bool backgroundImageTile;
	bool getBackgroundImageTile() { return backgroundImageTile; }
	void setBackgroundImageTile(bool b) { backgroundImageTile = b; saveSettingsTimer->start(); }
	Q_PROPERTY(bool backgroundImageTile READ getBackgroundImageTile WRITE setBackgroundImageTile NOTIFY backgroundImageTileChanged)



	// Hide to tray icon?
	bool trayicon;
	bool getTrayicon() { return trayicon; }
	void setTayicon(bool t) { trayicon = t; saveSettingsTimer->start(); }
	Q_PROPERTY(bool trayicon READ getTrayicon WRITE setTayicon NOTIFY trayiconChanged)

	// Smooth Transition for changing images
	int transition;
	int getTransition() { return transition; }
	void setTransition(int t) { transition = t; saveSettingsTimer->start(); }
	Q_PROPERTY(int transition READ getTransition WRITE setTransition NOTIFY transitionChanged)

	// Loop through folder?
	bool loopthroughfolder;
	bool getLoopthroughfolder() { return loopthroughfolder; }
	void setLoopthroughfolder(bool l) { loopthroughfolder = l; saveSettingsTimer->start(); }
	Q_PROPERTY(bool loopthroughfolder READ getLoopthroughfolder WRITE setLoopthroughfolder NOTIFY loopthroughfolderChanged)

	// Menu sensitivity
	int menusensitivity;
	int getMenusensitivity() { return menusensitivity; }
	void setMenusensitivity(int m) { menusensitivity = m; saveSettingsTimer->start(); }
	Q_PROPERTY(int menusensitivity READ getMenusensitivity WRITE setMenusensitivity NOTIFY menusensitivityChanged)

	// Close on click on background exits?
	bool closeongrey;
	bool getCloseongrey() { return closeongrey; }
	void setCloseongrey(bool l) { closeongrey = l; saveSettingsTimer->start(); }
	Q_PROPERTY(bool closeongrey READ getCloseongrey WRITE setCloseongrey NOTIFY closeongreyChanged)

	// Border around big image
	int borderAroundImg;
	int getBorderAroundImg() { return borderAroundImg; }
	void setBorderAroundImg(int b) { borderAroundImg = b; saveSettingsTimer->start(); }
	Q_PROPERTY(int borderAroundImg READ getBorderAroundImg WRITE setBorderAroundImg NOTIFY borderAroundImgChanged)

	// Show Quick Settings on mouse movement
	bool quickSettings;
	bool getQuickSettings() { return quickSettings; }
	void setQuickSettings(bool l) { quickSettings = l; saveSettingsTimer->start(); }
	Q_PROPERTY(bool quickSettings READ getQuickSettings WRITE setQuickSettings NOTIFY quickSettingsChanged)

	// Sort images by
	QString sortby;
	QString getSortby() { return sortby; }
	void setSortby(QString s) { sortby = s; saveSettingsTimer->start(); }
	Q_PROPERTY(QString sortby READ getSortby WRITE setSortby NOTIFY sortbyChanged)

	bool sortbyAscending;
	bool getSortbyAscending() { return sortbyAscending; }
	void setSortbyAscending(bool s) { sortbyAscending = s; saveSettingsTimer->start(); }
	Q_PROPERTY(bool sortbyAscending READ getSortbyAscending WRITE setSortbyAscending NOTIFY sortbyAscendingChanged)

	// Mouse Wheel sensitivity
	int mouseWheelSensitivity;
	int getMouseWheelSensitivity() { return mouseWheelSensitivity; }
	void setMouseWheelSensitivity(int b) { mouseWheelSensitivity = b; saveSettingsTimer->start(); }
	Q_PROPERTY(int mouseWheelSensitivity READ getMouseWheelSensitivity WRITE setMouseWheelSensitivity NOTIFY mouseWheelSensitivityChanged)

	// Remember per session
	bool rememberRotation;
	bool getRememberRotation() { return rememberRotation; }
	void setRememberRotation(bool l) { rememberRotation = l; saveSettingsTimer->start(); }
	Q_PROPERTY(bool rememberRotation READ getRememberRotation WRITE setRememberRotation NOTIFY rememberRotationChanged)

	bool rememberZoom;
	bool getRememberZoom() { return rememberZoom; }
	void setRememberZoom(bool l) { rememberZoom = l; saveSettingsTimer->start(); }
	Q_PROPERTY(bool rememberZoom READ getRememberZoom WRITE setRememberZoom NOTIFY rememberZoomChanged)


	// If image is too small, zoom to fit in window
	bool fitInWindow;
	bool getFitInWindow() { return fitInWindow; }
	void setFitInWindow(bool f) { fitInWindow = f; saveSettingsTimer->start(); }
	Q_PROPERTY(bool fitInWindow READ getFitInWindow WRITE setFitInWindow NOTIFY fitInWindowChanged)

	// Are quickinfos hidden?
	bool hidecounter;
	bool getHidecounter() { return hidecounter; }
	void setHidecounter(bool h) { hidecounter = h; saveSettingsTimer->start(); }
	Q_PROPERTY(bool hidecounter READ getHidecounter WRITE setHidecounter NOTIFY hidecounterChanged)

	bool hidefilepathshowfilename;
	bool getHidefilepathshowfilename() { return hidefilepathshowfilename; }
	void setHidefilepathshowfilename(bool h) { hidefilepathshowfilename = h; saveSettingsTimer->start(); }
	Q_PROPERTY(bool hidefilepathshowfilename READ getHidefilepathshowfilename WRITE setHidefilepathshowfilename NOTIFY hidefilepathshowfilenameChanged)

	bool hidefilename;
	bool getHidefilename() { return hidefilename; }
	void setHidefilename(bool h) { hidefilename = h; saveSettingsTimer->start(); }
	Q_PROPERTY(bool hidefilename READ getHidefilename WRITE setHidefilename NOTIFY hidefilenameChanged)

	bool hidex;
	bool getHidex() { return hidex; }
	void setHidex(bool h) { hidex = h; saveSettingsTimer->start(); }
	Q_PROPERTY(bool hidex READ getHidex WRITE setHidex NOTIFY hidexChanged)

	// Size/Look of closing "x"
	int closeXsize;
	int getCloseXsize() { return closeXsize; }
	void setCloseXsize(int c) { closeXsize = c; saveSettingsTimer->start(); }
	Q_PROPERTY(int closeXsize READ getCloseXsize WRITE setCloseXsize NOTIFY closeXsizeChanged)

	bool fancyX;
	bool getFancyX() { return fancyX; }
	void setFancyX(bool f) { bool tmp = fancyX; fancyX = f; if(fancyX != tmp) emit fancyXChanged(f); saveSettingsTimer->start(); }
	Q_PROPERTY(bool fancyX READ getFancyX WRITE setFancyX NOTIFY fancyXChanged)

	// Some settings of the slideshow
	int slideShowTime;
	int slideShowTransition;
	QString slideShowMusicFile;
	bool slideShowShuffle;
	bool slideShowLoop;
	bool slideShowHideQuickinfo;

	// Some wallpaper settings
	QString wallpaperAlignment;
	QString wallpaperScale;



	// The Size of the thumbnail squares
	int thumbnailsize;
	int getThumbnailsize() { return thumbnailsize; }
	void setThumbnailsize(int t) { thumbnailsize = t; saveSettingsTimer->start(); }
	Q_PROPERTY(int thumbnailsize READ getThumbnailsize WRITE setThumbnailsize NOTIFY thumbnailsizeChanged)

	// Thumbnails at the bottom or top?
	QString thumbnailposition;
	QString getThumbnailposition() { return thumbnailposition; }
	void setThumbnailposition(QString t) { thumbnailposition = t; saveSettingsTimer->start(); }
	Q_PROPERTY(QString thumbnailposition READ getThumbnailposition WRITE setThumbnailposition NOTIFY thumbnailpositionChanged)

	// Enable thumbnail cache
	bool thumbnailcache;
	bool getThumbnailcache() { return thumbnailcache; }
	void setThumbnailcache(bool t) { thumbnailcache = t; saveSettingsTimer->start(); }
	Q_PROPERTY(bool thumbnailcache READ getThumbnailcache WRITE setThumbnailcache NOTIFY thumbnailcacheChanged)

	// Are files used for caching (use database if false)
	bool thbcachefile;
	bool getThbcachefile() { return thbcachefile; }
	void setThbcachefile(bool t) { thbcachefile = t; saveSettingsTimer->start(); }
	Q_PROPERTY(bool thbcachefile READ getThbcachefile WRITE setThbcachefile NOTIFY thbcachefileChanged)

	// Border between thumbnails
	int thumbnailSpacingBetween;
	int getThumbnailSpacingBetween() { return thumbnailSpacingBetween; }
	void setThumbnailSpacingBetween(int t) { thumbnailSpacingBetween = t; saveSettingsTimer->start(); }
	Q_PROPERTY(int thumbnailSpacingBetween READ getThumbnailSpacingBetween WRITE setThumbnailSpacingBetween NOTIFY thumbnailSpacingBetweenChanged)

	// Lift hovered/selected thumbnails by x pixels
	int thumbnailLiftUp;
	int getThumbnailLiftUp() { return thumbnailLiftUp; }
	void setThumbnailLiftUp(int t) { thumbnailLiftUp = t; saveSettingsTimer->start(); }
	Q_PROPERTY(int thumbnailLiftUp READ getThumbnailLiftUp WRITE setThumbnailLiftUp NOTIFY thumbnailLiftUpChanged)

	// Are the thumbnails fading out or always visible?
	bool thumbnailKeepVisible;
	bool getThumbnailKeepVisible() { return thumbnailKeepVisible; }
	void setThumbnailKeepVisible(bool t) { thumbnailKeepVisible = t; saveSettingsTimer->start(); }
	Q_PROPERTY(bool thumbnailKeepVisible READ getThumbnailKeepVisible WRITE setThumbnailKeepVisible NOTIFY thumbnailKeepVisibleChanged)

	// Enable dynamic thumbnail creation (1 = dynamic, 2 = smart)
	int thumbnailDynamic;
	int getThumbnailDynamic() { return thumbnailDynamic; }
	void setThumbnailDynamic(int t) { thumbnailDynamic = t; saveSettingsTimer->start(); }
	Q_PROPERTY(int thumbnailDynamic READ getThumbnailDynamic WRITE setThumbnailDynamic NOTIFY thumbnailDynamicChanged)

	// Always center on active thumbnails
	bool thumbnailCenterActive;
	bool getThumbnailCenterActive() { return thumbnailCenterActive; }
	void setThumbnailCenterActive(bool t) { thumbnailCenterActive = t; saveSettingsTimer->start(); }
	Q_PROPERTY(bool thumbnailCenterActive READ getThumbnailCenterActive WRITE setThumbnailCenterActive NOTIFY thumbnailCenterActiveChanged)

	// Don't load actual thumbnail but just display the filename
	bool thumbnailFilenameInstead;bool getThumbnailFilenameInstead() { return thumbnailFilenameInstead; }
	void setThumbnailFilenameInstead(bool t) { thumbnailFilenameInstead = t; saveSettingsTimer->start(); }
	Q_PROPERTY(bool thumbnailFilenameInstead READ getThumbnailFilenameInstead WRITE setThumbnailFilenameInstead NOTIFY thumbnailFilenameInsteadChanged)

	int thumbnailFilenameInsteadFontSize;
	int getThumbnailFilenameInsteadFontSize() { return thumbnailFilenameInsteadFontSize; }
	void setThumbnailFilenameInsteadFontSize(int t) { thumbnailFilenameInsteadFontSize = t; saveSettingsTimer->start(); }
	Q_PROPERTY(int thumbnailFilenameInsteadFontSize READ getThumbnailFilenameInsteadFontSize WRITE setThumbnailFilenameInsteadFontSize NOTIFY thumbnailFilenameInsteadFontSizeChanged)

	// Thumbnails can be disabled altogether
	bool thumbnailDisable;
	bool getThumbnailDisable() { return thumbnailDisable; }
	void setThumbnailDisable(bool t) { thumbnailDisable = t; saveSettingsTimer->start(); }
	Q_PROPERTY(bool thumbnailDisable READ getThumbnailDisable WRITE setThumbnailDisable NOTIFY thumbnailDisableChanged)

	// Preload full directory (no matter the size)
	bool thumbnailPreloadFullDirectory;
	bool getThumbnailPreloadFullDirectory() { return thumbnailPreloadFullDirectory; }
	void setThumbnailPreloadFullDirectory(bool t) { thumbnailPreloadFullDirectory = t; saveSettingsTimer->start(); }
	Q_PROPERTY(bool thumbnailPreloadFullDirectory READ getThumbnailPreloadFullDirectory WRITE setThumbnailPreloadFullDirectory NOTIFY thumbnailPreloadFullDirectoryChanged)

	// How many thumbnail shall be reloaded?
	int thumbnailPreloadNumber;
	int getThumbnailPreloadNumber() { return thumbnailPreloadNumber; }
	void setThumbnailPreloadNumber(int t) { thumbnailPreloadNumber = t; saveSettingsTimer->start(); }
	Q_PROPERTY(int thumbnailPreloadNumber READ getThumbnailPreloadNumber WRITE setThumbnailPreloadNumber NOTIFY thumbnailPreloadNumberChanged)


	bool thumbnailWriteFilename;
	bool getThumbnailWriteFilename() { return thumbnailWriteFilename; }
	void setThumbnailWriteFilename(bool t) { thumbnailWriteFilename = t; saveSettingsTimer->start(); }
	Q_PROPERTY(bool thumbnailWriteFilename READ getThumbnailWriteFilename WRITE setThumbnailWriteFilename NOTIFY thumbnailWriteFilenameChanged)

	bool thumbnailWriteResolution;
	bool getThumbnailWriteResolution() { return thumbnailWriteResolution; }
	void setThumbnailWriteResolution(bool t) { thumbnailWriteResolution = t; saveSettingsTimer->start(); }
	Q_PROPERTY(bool thumbnailWriteResolution READ getThumbnailWriteResolution WRITE setThumbnailWriteResolution NOTIFY thumbnailWriteResolutionChanged)

	int thumbnailFontSize;
	int getThumbnailFontSize() { return thumbnailFontSize; }
	void setThumbnailFontSize(int t) { thumbnailFontSize = t; saveSettingsTimer->start(); }
	Q_PROPERTY(int thumbnailFontSize READ getThumbnailFontSize WRITE setThumbnailFontSize NOTIFY thumbnailFontSizeChanged)

	// Window Mode
	bool windowmode;
	bool getWindowmode() { return windowmode; }
	void setWindowmode(bool w) { windowmode = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool windowmode READ getWindowmode WRITE setWindowmode NOTIFY windowmodeChanged)
	// w/ or w/o decoration
	bool windowDecoration;
	bool getWindowDecoration() { return windowDecoration; }
	void setWindowDecoration(bool w) { windowDecoration = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool windowDecoration READ getWindowDecoration WRITE setWindowDecoration NOTIFY windowDecorationChanged)

	// The currently known filetypes (only extra Qt filetypes)
	QString knownFileTypesQtExtras;


	// Some exif settings
	bool exifenablemousetriggering;
	bool getExifenablemousetriggering() { return exifenablemousetriggering; }
	void setExifenablemousetriggering(bool w) { exifenablemousetriggering = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifenablemousetriggering READ getExifenablemousetriggering WRITE setExifenablemousetriggering NOTIFY exifenablemousetriggeringChanged)

	QString exifrotation;
	QString getExifrotation() { return exifrotation; }
	void setExifrotation(QString w) { exifrotation = w; saveSettingsTimer->start(); }
	Q_PROPERTY(QString exifrotation READ getExifrotation WRITE setExifrotation NOTIFY exifrotationChanged)

	QString exifgpsmapservice;
	QString getExifgpsmapservice() { return exifgpsmapservice; }
	void setExifgpsmapservice(QString w) { exifgpsmapservice = w; saveSettingsTimer->start(); }
	Q_PROPERTY(QString exifgpsmapservice READ getExifgpsmapservice WRITE setExifgpsmapservice NOTIFY exifgpsmapserviceChanged)


	int exiffontsize;
	int getExiffontsize() { return exiffontsize; }
	void setExiffontsize(int e) { exiffontsize = e; saveSettingsTimer->start(); }
	Q_PROPERTY(int exiffontsize READ getExiffontsize WRITE setExiffontsize NOTIFY exiffontsizeChanged)


	// Which Exif data is shown?
	bool exiffilename;
	bool getExiffilename() { return exiffilename; }
	void setExiffilename(bool w) { exiffilename = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exiffilename READ getExiffilename WRITE setExiffilename NOTIFY exiffilenameChanged)

	bool exiffiletype;
	bool getExiffiletype() { return exiffiletype; }
	void setExiffiletype(bool w) { exiffiletype = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exiffiletype READ getExiffiletype WRITE setExiffiletype NOTIFY exiffiletypeChanged)

	bool exiffilesize;
	bool getExiffilesize() { return exiffilesize; }
	void setExiffilesize(bool w) { exiffilesize = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exiffilesize READ getExiffilesize WRITE setExiffilesize NOTIFY exiffilesizeChanged)

	bool exifdimensions;
	bool getExifdimensions() { return exifdimensions; }
	void setExifdimensions(bool w) { exifdimensions = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifdimensions READ getExifdimensions WRITE setExifdimensions NOTIFY exifdimensionsChanged)

	bool exifmake;
	bool getExifmake() { return exifmake; }
	void setExifmake(bool w) { exifmake = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifmake READ getExifmake WRITE setExifmake NOTIFY exifmakeChanged)

	bool exifmodel;
	bool getExifmodel() { return exifmodel; }
	void setExifmodel(bool w) { exifmodel = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifmodel READ getExifmodel WRITE setExifmodel NOTIFY exifmodelChanged)

	bool exifsoftware;
	bool getExifsoftware() { return exifsoftware; }
	void setExifsoftware(bool w) { exifsoftware = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifsoftware READ getExifsoftware WRITE setExifsoftware NOTIFY exifsoftwareChanged)

	bool exifphototaken;
	bool getExifphototaken() { return exifphototaken; }
	void setExifphototaken(bool w) { exifphototaken = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifphototaken READ getExifphototaken WRITE setExifphototaken NOTIFY exifphototakenChanged)

	bool exifexposuretime;
	bool getExifexposuretime() { return exifexposuretime; }
	void setExifexposuretime(bool w) { exifexposuretime = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifexposuretime READ getExifexposuretime WRITE setExifexposuretime NOTIFY exifexposuretimeChanged)

	bool exifflash;
	bool getExifflash() { return exifflash; }
	void setExifflash(bool w) { exifflash = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifflash READ getExifflash WRITE setExifflash NOTIFY exifflashChanged)

	bool exifiso;
	bool getExifiso() { return exifiso; }
	void setExifiso(bool w) { exifiso = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifiso READ getExifiso WRITE setExifiso NOTIFY exifisoChanged)

	bool exifscenetype;
	bool getExifscenetype() { return exifscenetype; }
	void setExifscenetype(bool w) { exifscenetype = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifscenetype READ getExifscenetype WRITE setExifscenetype NOTIFY exifscenetypeChanged)

	bool exifflength;
	bool getExifflength() { return exifflength; }
	void setExifflength(bool w) { exifflength = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifflength READ getExifflength WRITE setExifflength NOTIFY exifflengthChanged)

	bool exiffnumber;
	bool getExiffnumber() { return exiffnumber; }
	void setExiffnumber(bool w) { exiffnumber = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exiffnumber READ getExiffnumber WRITE setExiffnumber NOTIFY exiffnumberChanged)

	bool exiflightsource;
	bool getExiflightsource() { return exiflightsource; }
	void setExiflightsource(bool w) { exiflightsource = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exiflightsource READ getExiflightsource WRITE setExiflightsource NOTIFY exiflightsourceChanged)

	bool iptckeywords;
	bool getIptckeywords() { return iptckeywords; }
	void setIptckeywords(bool w) { iptckeywords = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool iptckeywords READ getIptckeywords WRITE setIptckeywords NOTIFY iptckeywordsChanged)

	bool iptclocation;
	bool getIptclocation() { return iptclocation; }
	void setIptclocation(bool w) { iptclocation = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool iptclocation READ getIptclocation WRITE setIptclocation NOTIFY iptclocationChanged)

	bool iptccopyright;
	bool getIptccopyright() { return iptccopyright; }
	void setIptccopyright(bool w) { iptccopyright = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool iptccopyright READ getIptccopyright WRITE setIptccopyright NOTIFY iptccopyrightChanged)

	bool exifgps;
	bool getExifgps() { return exifgps; }
	void setExifgps(bool w) { exifgps = w; saveSettingsTimer->start(); }
	Q_PROPERTY(bool exifgps READ getExifgps WRITE setExifgps NOTIFY exifgpsChanged)

	// Set the default settings
	void setDefault() {

		version = QString::fromStdString(VERSION);

		knownFileTypesQtExtras = "";

		sortby = "name";
		sortbyAscending = true;

		windowmode = false;
		windowDecoration = false;
		myWidgetAnimated = true;
		saveWindowGeometry = true;
		keepOnTop = true;

		language = "";
		bgColorRed = 0;
		bgColorGreen = 0;
		bgColorBlue = 0;
		bgColorAlpha = 190;

//#ifdef Q_OS_WIN32
//		backgroundImageScreenshot = (QtWin::isCompositionEnabled() ? false : true);
//#else
		backgroundImageScreenshot = false;
//#endif
		backgroundImageUse = false;
		backgroundImagePath = "";
		backgroundImageScale = true;
		backgroundImageScaleCrop = false;
		backgroundImageStretch = false;
		backgroundImageCenter = false;
		backgroundImageTile = false;

//#ifdef Q_OS_WIN32
//		composite = (QtWin::isCompositionEnabled() ? true : false);
//#else
		composite = true;
//#endif
		trayicon = false;
		transition = 0;
		loopthroughfolder = true;
		menusensitivity = 4;
		closeongrey = false;
		borderAroundImg = 5;
		quickSettings = true;
		mouseWheelSensitivity = 1;
		rememberRotation = true;
		rememberZoom = true;
		fitInWindow= false;

		hidecounter = false;
		hidefilepathshowfilename = true;
		hidefilename = false;
		hidex = false;

		closeXsize = 10;
		fancyX = false;

		thumbnailsize = 80;
		thumbnailposition = "Bottom";
		thumbnailcache = true;
		thbcachefile = false;
		thumbnailSpacingBetween = 0;
		thumbnailLiftUp = 6;
		thumbnailKeepVisible = false;
		thumbnailDynamic = 2;
		thumbnailCenterActive = false;
		thumbnailDisable = false;
		thumbnailWriteFilename = true;
		thumbnailWriteResolution = false;
		thumbnailFontSize = 7;
		thumbnailPreloadFullDirectory = false;
		thumbnailPreloadNumber = 400;

		thumbnailFilenameInstead = false;
		thumbnailFilenameInsteadFontSize = 8;

		slideShowTime = 5;
		slideShowTransition = 4;
		slideShowMusicFile = "";
		slideShowShuffle = false;
		slideShowLoop = true;
		slideShowHideQuickinfo = true;

		wallpaperAlignment = "center";
		wallpaperScale = "noscale";


		exifenablemousetriggering = true;
		exiffontsize = 8;
		exiffilename = true;
		exiffiletype = true;
		exiffilesize = true;
		exifdimensions = true;
		exifmake = true;
		exifmodel = true;
		exifsoftware = true;
		exifphototaken = true;
		exifexposuretime = true;
		exifflash = true;
		exifiso = true;
		exifscenetype = true;
		exifflength = true;
		exiffnumber = true;
		exiflightsource = true;
		iptckeywords = true;
		iptclocation = true;
		iptccopyright = true;
		exifgps = true;
		exifrotation = "Never";
		exifgpsmapservice = "openstreetmap.org";
	}


public slots:
	// Save settings
	void saveSettings() {

		QFile file(QDir::homePath() + "/.photoqt/settings");

		if(!file.open(QIODevice::ReadWrite))

			std::cerr << "ERROR saving settings" << std::endl;

		else {

			if(verbose) std::cout << "Save Settings" << std::endl;

			file.close();
			file.remove();
			file.open(QIODevice::ReadWrite);

			QTextStream out(&file);

			QString cont = "Version=" + version + "\n";
			cont += QString("Language=%1\n").arg(language);
			cont += QString("WindowMode=%1\n").arg(int(windowmode));
			cont += QString("WindowDecoration=%1\n").arg(int(windowDecoration));
			cont += QString("MyWidgetAnimated=%1\n").arg(int(myWidgetAnimated));
			cont += QString("SaveWindowGeometry=%1\n").arg(int(saveWindowGeometry));
			cont += QString("KeepOnTop=%1\n").arg(int(keepOnTop));
			cont += QString("KnownFileTypesQtExtras=%1\n").arg(knownFileTypesQtExtras);

			cont += "\n[Look]\n";

			cont += QString("Composite=%1\n").arg(int(composite));
			cont += QString("BgColorRed=%1\n").arg(bgColorRed);
			cont += QString("BgColorGreen=%1\n").arg(bgColorGreen);
			cont += QString("BgColorBlue=%1\n").arg(bgColorBlue);
			cont += QString("BgColorAlpha=%1\n").arg(bgColorAlpha);
			cont += QString("BackgroundImageScreenshot=%1\n").arg(backgroundImageScreenshot);
			cont += QString("BackgroundImageUse=%1\n").arg(backgroundImageUse);
			cont += QString("BackgroundImagePath=%1\n").arg(backgroundImagePath);
			cont += QString("BackgroundImageScale=%1\n").arg(backgroundImageScale);
			cont += QString("BackgroundImageScaleCrop=%1\n").arg(backgroundImageScaleCrop);
			cont += QString("BackgroundImageStretch=%1\n").arg(backgroundImageStretch);
			cont += QString("BackgroundImageCenter=%1\n").arg(backgroundImageCenter);
			cont += QString("BackgroundImageTile=%1\n").arg(backgroundImageTile);

			cont += "\n[Behaviour]\n";

			cont += QString("TrayIcon=%1\n").arg(int(trayicon));
			cont += QString("Transition=%1\n").arg(transition);
			cont += QString("LoopThroughFolder=%1\n").arg(int(loopthroughfolder));
			cont += QString("MenuSensitivity=%1\n").arg(menusensitivity);
			cont += QString("CloseOnGrey=%1\n").arg(int(closeongrey));
			cont += QString("BorderAroundImg=%1\n").arg(borderAroundImg);
			cont += QString("QuickSettings=%1\n").arg(int(quickSettings));
			cont += QString("SortImagesBy=%1\n").arg(sortby);
			cont += QString("SortImagesAscending=%1\n").arg(int(sortbyAscending));
			cont += QString("MouseWheelSensitivity=%1\n").arg(mouseWheelSensitivity);
			cont += QString("RememberRotation=%1\n").arg(int(rememberRotation));
			cont += QString("RememberZoom=%1\n").arg(int(rememberZoom));
			cont += QString("FitInWindow=%1\n").arg(int(fitInWindow));

			cont += "\n[Quickinfo]\n";

			cont += QString("HideCounter=%1\n").arg(int(hidecounter));
			cont += QString("HideFilepathShowFilename=%1\n").arg(int(hidefilepathshowfilename));
			cont += QString("HideFilename=%1\n").arg(int(hidefilename));
			cont += QString("HideX=%1\n").arg(int(hidex));
			cont += QString("FancyX=%1\n").arg(int(fancyX));
			cont += QString("CloseXSize=%1\n").arg(closeXsize);

			cont += "\n[Thumbnail]\n";

			cont += QString("ThumbnailSize=%1\n").arg(thumbnailsize);
			cont += QString("ThumbnailPosition=%1\n").arg(thumbnailposition);
			cont += QString("ThumbnailCache=%1\n").arg(int(thumbnailcache));
			cont += QString("ThbCacheFile=%1\n").arg(int(thbcachefile));
			cont += QString("ThumbnailSpacingBetween=%1\n").arg(thumbnailSpacingBetween);
			cont += QString("ThumbnailLiftUp=%1\n").arg(thumbnailLiftUp);
			cont += QString("ThumbnailKeepVisible=%1\n").arg(thumbnailKeepVisible);
			cont += QString("ThumbnailDynamic=%1\n").arg(thumbnailDynamic);
			cont += QString("ThumbnailCenterActive=%1\n").arg(int(thumbnailCenterActive));
			cont += QString("ThumbnailFilenameInstead=%1\n").arg(int(thumbnailFilenameInstead));
			cont += QString("ThumbnailFilenameInsteadFontSize=%1\n").arg(thumbnailFilenameInsteadFontSize);
			cont += QString("ThumbnailDisable=%1\n").arg(int(thumbnailDisable));
			cont += QString("ThumbnailWriteFilename=%1\n").arg(int(thumbnailWriteFilename));
			cont += QString("ThumbnailWriteResolution=%1\n").arg(int(thumbnailWriteResolution));
			cont += QString("ThumbnailFontSize=%1\n").arg(thumbnailFontSize);
			cont += QString("ThumbnailPreloadFullDirectory=%1\n").arg(int(thumbnailPreloadFullDirectory));
			cont += QString("ThumbnailPreloadNumber=%1\n").arg(thumbnailPreloadNumber);

			cont += "\n[Slideshow]\n";

			cont += QString("SlideShowTime=%1\n").arg(slideShowTime);
			cont += QString("SlideShowTransition=%1\n").arg(slideShowTransition);
			cont += QString("SlideShowMusicFile=%1\n").arg(slideShowMusicFile);
			cont += QString("SlideShowShuffle=%1\n").arg(int(slideShowShuffle));
			cont += QString("SlideShowLoop=%1\n").arg(int(slideShowLoop));
			cont += QString("SlideShowHideQuickinfo=%1\n").arg(int(slideShowHideQuickinfo));

			cont += "\n[Wallpaper]\n";

			cont += QString("WallpaperAlignment=%1\n").arg(wallpaperAlignment);
			cont += QString("WallpaperScale=%1\n").arg((wallpaperScale));

			cont += "\n[Exif]\n";

			cont += QString("ExifEnableMouseTriggering=%1\n").arg(int(exifenablemousetriggering));
			cont += QString("ExifFontSize=%1\n").arg(exiffontsize);
			cont += QString("ExifFilename=%1\n").arg(int(exiffilename));
			cont += QString("ExifFiletype=%1\n").arg(int(exiffiletype));
			cont += QString("ExifFilesize=%1\n").arg(int(exiffilesize));
			cont += QString("ExifDimensions=%1\n").arg(int(exifdimensions));
			cont += QString("ExifMake=%1\n").arg(int(exifmake));
			cont += QString("ExifModel=%1\n").arg(int(exifmodel));
			cont += QString("ExifSoftware=%1\n").arg(int(exifsoftware));
			cont += QString("ExifPhotoTaken=%1\n").arg(int(exifphototaken));
			cont += QString("ExifExposureTime=%1\n").arg(int(exifexposuretime));
			cont += QString("ExifFlash=%1\n").arg(int(exifflash));
			cont += QString("ExifIso=%1\n").arg(int(exifiso));
			cont += QString("ExifSceneType=%1\n").arg(int(exifscenetype));
			cont += QString("ExifFLength=%1\n").arg(int(exifflength));
			cont += QString("ExifFNumber=%1\n").arg(int(exiffnumber));
			cont += QString("ExifLightSource=%1\n").arg(int(exiflightsource));
			cont += QString("ExifGps=%1\n").arg(int(exifgps));
			cont += QString("ExifRotation=%1\n").arg(exifrotation);
			cont += QString("ExifGPSMapService=%1\n").arg(exifgpsmapservice);

			cont += "\n[Iptc]\n";
			cont += QString("IptcKeywords=%1\n").arg(int(iptckeywords));
			cont += QString("IptcLocation=%1\n").arg(int(iptclocation));
			cont += QString("IptcCopyright=%1\n").arg(int(iptccopyright));

			out << cont;
			file.close();

		}

	}

	// Read the current settings
	void readSettings() {

		setDefault();

		QFile file(QDir::homePath() + "/.photoqt/settings");

		if(!file.open(QIODevice::ReadOnly))

			std::cerr << "ERROR reading settings" << std::endl;

		else {

			if(verbose) std::cerr << "Read Settings from File" << std::endl;

			// Read file
			QTextStream in(&file);
			QString all = in.readAll();

			if(all.contains("Language="))
				language = all.split("Language=").at(1).split("\n").at(0);

			if(all.contains("KnownFileTypesQtExtras="))
				knownFileTypesQtExtras = all.split("KnownFileTypesQtExtras=").at(1).split("\n").at(0);

			if(all.contains("SortImagesBy="))
				sortby = all.split("SortImagesBy=").at(1).split("\n").at(0);

			if(all.contains("SortImagesAscending=1"))
				sortbyAscending = true;
			else if(all.contains("SortImagesAscending=0"))
				sortbyAscending = false;

			if(all.contains("WindowMode=1"))
				windowmode = true;
			else if(all.contains("WindowMode=0"))
				windowmode = false;

			if(all.contains("WindowDecoration=1"))
				windowDecoration = true;
			else if(all.contains("WindowDecoration=0"))
				windowDecoration = false;

			if(all.contains("MyWidgetAnimated=1"))
				myWidgetAnimated = true;
			else if(all.contains("MyWidgetAnimated=0"))
				myWidgetAnimated = false;

			if(all.contains("SaveWindowGeometry=1"))
				saveWindowGeometry = true;
			else if(all.contains("SaveWindowGeometry=0"))
				saveWindowGeometry = false;

			if(all.contains("KeepOnTop=1"))
				keepOnTop = true;
			else if(all.contains("KeepOnTop=0"))
				keepOnTop = false;

			if(all.contains("Composite=1"))
				composite = true;
			else if(all.contains("Composite=0"))
				composite = false;


			if(all.contains("QuickSettings=1"))
				quickSettings = true;
			else if(all.contains("QuickSettings=0"))
				quickSettings = false;


			if(all.contains("BgColorRed="))
				bgColorRed = all.split("BgColorRed=").at(1).split("\n").at(0).toInt();
			if(all.contains("BgColorGreen="))
				bgColorGreen = all.split("BgColorGreen=").at(1).split("\n").at(0).toInt();
			if(all.contains("BgColorBlue="))
				bgColorBlue = all.split("BgColorBlue=").at(1).split("\n").at(0).toInt();
			if(all.contains("BgColorAlpha="))
				bgColorAlpha = all.split("BgColorAlpha=").at(1).split("\n").at(0).toInt();

			if(all.contains("BackgroundImageScreenshot="))
				backgroundImageScreenshot = bool(all.split("BackgroundImageScreenshot=").at(1).split("\n").at(0).toInt());

			if(all.contains("BackgroundImagePath="))
				backgroundImagePath = all.split("BackgroundImagePath=").at(1).split("\n").at(0);
			if(all.contains("BackgroundImageUse="))
				backgroundImageUse = bool(all.split("BackgroundImageUse=").at(1).split("\n").at(0).toInt());
			if(all.contains("BackgroundImageScale="))
				backgroundImageScale = bool(all.split("BackgroundImageScale=").at(1).split("\n").at(0).toInt());
			if(all.contains("BackgroundImageScaleCrop="))
				backgroundImageScaleCrop = bool(all.split("BackgroundImageScaleCrop=").at(1).split("\n").at(0).toInt());
			if(all.contains("BackgroundImageStretch="))
				backgroundImageStretch = bool(all.split("BackgroundImageStretch=").at(1).split("\n").at(0).toInt());
			if(all.contains("BackgroundImageCenter="))
				backgroundImageCenter = bool(all.split("BackgroundImageCenter=").at(1).split("\n").at(0).toInt());
			if(all.contains("BackgroundImageTile="))
				backgroundImageTile = bool(all.split("BackgroundImageTile=").at(1).split("\n").at(0).toInt());


			if(all.contains("TrayIcon=1"))
				trayicon = true;
			else if(all.contains("TrayIcon=0"))
				trayicon = false;

			if(all.contains("Transition="))
				transition = all.split("Transition=").at(1).split("\n").at(0).toInt();

			if(all.contains("LoopThroughFolder=1"))
				loopthroughfolder = true;
			else if(all.contains("LoopThroughFolder=0"))
				loopthroughfolder = false;

			if(all.contains("MenuSensitivity="))
				menusensitivity = all.split("MenuSensitivity=").at(1).split("\n").at(0).toInt();

			if(all.contains("CloseOnGrey=1"))
				closeongrey = true;
			else if(all.contains("CloseOnGrey=0"))
				closeongrey = false;

			if(all.contains("BorderAroundImg="))
				borderAroundImg = all.split("BorderAroundImg=").at(1).split("\n").at(0).toInt();

			if(all.contains("MouseWheelSensitivity=")) {
				mouseWheelSensitivity = all.split("MouseWheelSensitivity=").at(1).split("\n").at(0).toInt();
				if(mouseWheelSensitivity < 1) mouseWheelSensitivity = 1;
			}

			if(all.contains("RememberRotation=1"))
				rememberRotation = true;
			else if(all.contains("RememberRotation=0"))
				rememberRotation = false;

			if(all.contains("RememberZoom=1"))
				rememberZoom = true;
			else if(all.contains("RememberZoom=0"))
				rememberZoom = false;

			if(all.contains("FitInWindow=1"))
				fitInWindow = true;
			else if(all.contains("FitInWindow=0"))
				fitInWindow = false;

			if(all.contains("HideCounter=1"))
				hidecounter = true;
			else if(all.contains("HideCounter=0"))
				hidecounter = false;

			if(all.contains("HideFilepathShowFilename=1"))
				hidefilepathshowfilename = true;
			else if(all.contains("HideFilepathShowFilename=0"))
				hidefilepathshowfilename = false;

			if(all.contains("HideFilename=1"))
				hidefilename = true;
			else if(all.contains("HideFilename=0"))
				hidefilename = false;

			if(all.contains("HideX=1"))
				hidex = true;
			else if(all.contains("HideX=0"))
				hidex = false;

			if(all.contains("CloseXSize="))
				closeXsize = all.split("CloseXSize=").at(1).split("\n").at(0).toInt();

			if(all.contains(("FancyX=1")))
				fancyX = true;
			else if(all.contains("FancyX=0"))
				fancyX = false;

			if(all.contains("ThumbnailSize="))
				thumbnailsize = all.split("ThumbnailSize=").at(1).split("\n").at(0).toInt();

			if(all.contains("ThumbnailPosition="))
				thumbnailposition = all.split("ThumbnailPosition=").at(1).split("\n").at(0);

			if(all.contains("ThumbnailCache=1"))
				thumbnailcache = true;
			else if(all.contains("ThumbnailCache=0"))
				thumbnailcache = false;

			if(all.contains("ThbCacheFile=1"))
				thbcachefile = true;
			else if(all.contains("ThbCacheFile=0"))
				thbcachefile = false;

			if(all.contains("ThumbnailSpacingBetween="))
				thumbnailSpacingBetween = all.split("ThumbnailSpacingBetween=").at(1).split("\n").at(0).toInt();
			// That below is the old property
			else if(all.contains("ThumbnailBorderAround="))
				thumbnailSpacingBetween = all.split("ThumbnailBorderAround=").at(1).split("\n").at(0).toInt();

			if(all.contains("ThumbnailLiftUp="))
				thumbnailLiftUp = all.split("ThumbnailLiftUp=").at(1).split("\n").at(0).toInt();

			if(all.contains("ThumbnailKeepVisible=1"))
				thumbnailKeepVisible = true;
			else if(all.contains("ThumbnailKeepVisible=0"))
				thumbnailKeepVisible = false;

			if(all.contains("ThumbnailDynamic="))
				thumbnailDynamic = all.split("ThumbnailDynamic=").at(1).split("\n").at(0).toInt();

			if(all.contains("ThumbnailCenterActive=1"))
				thumbnailCenterActive = true;
			else if(all.contains("ThumbnailCenterActive=0"))
				thumbnailCenterActive = false;

			if(all.contains("ThumbnailFilenameInstead=1"))
				thumbnailFilenameInstead = true;
			else if(all.contains("ThumbnailFilenameInstead=0"))
				thumbnailFilenameInstead = false;

			if(all.contains("ThumbnailFilenameInsteadFontSize="))
				thumbnailFilenameInsteadFontSize = all.split("ThumbnailFilenameInsteadFontSize=").at(1).split("\n").at(0).toInt();

			if(all.contains("ThumbnailDisable=1"))
				thumbnailDisable = true;
			else if(all.contains("ThumbnailDisable=0"))
				thumbnailDisable = false;

			if(all.contains("ThumbnailWriteFilename=1"))
				thumbnailWriteFilename = true;
			else if(all.contains("ThumbnailWriteFilename=0"))
				thumbnailWriteFilename = false;

			if(all.contains("ThumbnailWriteResolution=1"))
				thumbnailWriteResolution = true;
			else if(all.contains("ThumbnailWriteResolution=0"))
				thumbnailWriteResolution = false;

			if(all.contains("ThumbnailFontSize="))
				thumbnailFontSize = all.split("ThumbnailFontSize=").at(1).split("\n").at(0).toInt();

			if(all.contains("ThumbnailPreloadFullDirectory=1"))
				thumbnailPreloadFullDirectory = true;
			else if(all.contains("ThumbnailPreloadFullDirectory=0"))
				thumbnailPreloadFullDirectory = false;

			if(all.contains("ThumbnailPreloadNumber="))
				thumbnailPreloadNumber = all.split("ThumbnailPreloadNumber=").at(1).split("\n").at(0).toInt();


			if(all.contains("SlideShowTime="))
				slideShowTime = all.split("SlideShowTime=").at(1).split("\n").at(0).toInt();

			if(all.contains("SlideShowTransition="))
				slideShowTransition = all.split("SlideShowTransition=").at(1).split("\n").at(0).toInt();

			if(all.contains("SlideShowMusicFile="))
				slideShowMusicFile = all.split("SlideShowMusicFile=").at(1).split("\n").at(0).trimmed();

			if(all.contains("SlideShowShuffle=1"))
				slideShowShuffle = true;
			else if(all.contains("SlideShowShuffle=0"))
				slideShowShuffle = false;

			if(all.contains("SlideShowLoop=1"))
				slideShowLoop = true;
			else if(all.contains("SlideShowLoop=0"))
				slideShowLoop = false;

			if(all.contains("SlideShowHideQuickinfo="))
				slideShowHideQuickinfo = bool(all.split("SlideShowHideQuickinfo=").at(1).split("\n").at(0).toInt());

			if(all.contains("WallpaperAlignment="))
				wallpaperAlignment =  all.split("WallpaperAlignment=").at(1).split("\n").at(0);
			if(all.contains("WallpaperScale="))
				wallpaperScale = all.split("WallpaperScale=").at(1).split("\n").at(0);


			if(all.contains("ExifEnableMouseTriggering=1"))
				exifenablemousetriggering = true;
			else if(all.contains("ExifEnableMouseTriggering=0"))
				exifenablemousetriggering = false;

			if(all.contains("ExifFontSize="))
				exiffontsize = all.split("ExifFontSize=").at(1).split("\n").at(0).toInt();

			if(all.contains("ExifFilename=1"))
				exiffilename = true;
			else if(all.contains("ExifFilename=0"))
				exiffilename = false;

			if(all.contains("ExifFiletype=1"))
				exiffiletype = true;
			else if(all.contains("ExifFiletype=0"))
				exiffiletype = false;

			if(all.contains("ExifFilesize=1"))
				exiffilesize = true;
			else if(all.contains("ExifFilesize=0"))
				exiffilesize = false;

			if(all.contains("ExifDimensions=1"))
				exifdimensions = true;
			else if(all.contains("ExifDimensions=0"))
				exifdimensions = false;

			if(all.contains("ExifMake=1"))
				exifmake = true;
			else if(all.contains("ExifMake=0"))
				exifmake = false;

			if(all.contains("ExifModel=1"))
				exifmodel = true;
			else if(all.contains("ExifModel=0"))
				exifmodel = false;

			if(all.contains("ExifSoftware=1"))
				exifsoftware = true;
			else if(all.contains("ExifSoftware=0"))
				exifsoftware = false;

			if(all.contains("ExifPhotoTaken=1"))
				exifphototaken = true;
			else if(all.contains("ExifPhotoTaken=0"))
				exifphototaken = false;

			if(all.contains("ExifExposureTime=1"))
				exifexposuretime = true;
			else if(all.contains("ExifExposureTime=0"))
				exifexposuretime = false;

			if(all.contains("ExifFlash=1"))
				exifflash = true;
			else if(all.contains("ExifFlash=0"))
				exifflash = false;

			if(all.contains("ExifIso=1"))
				exifiso = true;
			else if(all.contains("ExifIso=0"))
				exifiso = false;

			if(all.contains("ExifSceneType=1"))
				exifscenetype = true;
			else if(all.contains("ExifSceneType=0"))
				exifscenetype = false;

			if(all.contains("ExifFLength=1"))
				exifflength = true;
			else if(all.contains("ExifFLength=0"))
				exifflength = false;

			if(all.contains("ExifFNumber=1"))
				exiffnumber = true;
			else if(all.contains("ExifFNumber=0"))
				exiffnumber = false;

			if(all.contains("ExifLightSource=1"))
				exiflightsource = true;
			else if(all.contains("ExifLightSource=0"))
				exiflightsource = false;

			if(all.contains("ExifGps=1"))
				exifgps = true;
			else if(all.contains("ExifGps=0"))
				exifgps = false;

			if(all.contains("IptcKeywords=1"))
				iptckeywords = true;
			else if(all.contains("IptcKeywords=0"))
				iptckeywords = false;

			if(all.contains("IptcLocation=1"))
				iptclocation = true;
			else if(all.contains("IptcLocation=0"))
				iptclocation = false;

			if(all.contains("IptcCopyright=1"))
				iptccopyright = true;
			else if(all.contains("IptcCopyright=0"))
				iptccopyright = false;

			if(all.contains("ExifRotation="))
				exifrotation = all.split("ExifRotation=").at(1).split("\n").at(0);

			if(all.contains("ExifGPSMapService="))
				exifgpsmapservice = all.split("ExifGPSMapService=").at(1).split("\n").at(0);

			file.close();

		}

	}


private:
	QFileSystemWatcher *watcher;
	QTimer *saveSettingsTimer;

signals:
	void languageChanged(QString l);
	void thumbnailsizeChanged(int s);
	void thumbnailcacheChanged(bool cache);
	void thbcachefileChanged(bool type);
	void thumbnailSpacingBetweenChanged(int spacing);
	void thumbnailLiftUpChanged(int liftup);
	void thumbnailKeepVisibleChanged(bool vis);
	void thumbnailFontSizeChanged(int s);
	void exiffontsizeChanged(int s);
	void fancyXChanged(bool f);
	void closeXsizeChanged(int s);
	void loopthroughfolderChanged(bool l);
	void fitInWindowChanged(bool f);
	void hidecounterChanged(bool h);
	void hidefilepathshowfilenameChanged(bool h);
	void hidefilenameChanged(bool h);
	void hidexChanged(bool h);
	void sortbyAscendingChanged(bool s);
	void sortbyChanged(QString s);
	void windowmodeChanged(bool w);
	void windowDecorationChanged(bool w);
	void trayiconChanged(bool t);
	void compositeChanged(bool c);
	void bgColorRedChanged(int b);
	void bgColorGreenChanged(int b);
	void bgColorBlueChanged(int b);
	void bgColorAlphaChanged(int b);
	void backgroundImageScreenshotChanged(bool b);
	void backgroundImageUseChanged(bool b);
	void backgroundImagePathChanged(QString b);
	void backgroundImageScaleChanged(bool b);
	void backgroundImageScaleCropChanged(bool b);
	void backgroundImageStretchChanged(bool b);
	void backgroundImageCenterChanged(bool b);
	void backgroundImageTileChanged(bool b);
	void transitionChanged(int t);
	void menusensitivityChanged(int m);
	void closeongreyChanged(bool c);
	void borderAroundImgChanged(int b);
	void quickSettingsChanged(bool q);
	void mouseWheelSensitivityChanged(int m);
	void rememberRotationChanged(bool r);
	void rememberZoomChanged(bool r);
	void knownFileTypesQtChanged(QString k);
	void myWidgetAnimatedChanged(bool c);
	void saveWindowGeometryChanged(bool c);
	void thumbnailDynamicChanged(int t);
	void thumbnailCenterActiveChanged(bool c);
	void thumbnailpositionChanged(QString k);
	void thumbnailFilenameInsteadChanged(bool c);
	void thumbnailFilenameInsteadFontSizeChanged(int t);
	void thumbnailDisableChanged(bool c);
	void thumbnailPreloadFullDirectoryChanged(bool c);
	void thumbnailPreloadNumberChanged(int t);
	void thumbnailWriteFilenameChanged(bool c);
	void thumbnailWriteResolutionChanged(bool c);
	void exifenablemousetriggeringChanged(bool e);
	void exifrotationChanged(QString e);
	void exifgpsmapserviceChanged(QString e);
	void exiffilenameChanged(bool e);
	void exiffiletypeChanged(bool e);
	void exiffilesizeChanged(bool e);
	void exifdimensionsChanged(bool e);
	void exifmakeChanged(bool e);
	void exifmodelChanged(bool e);
	void exifsoftwareChanged(bool e);
	void exifphototakenChanged(bool e);
	void exifexposuretimeChanged(bool e);
	void exifflashChanged(bool e);
	void exifisoChanged(bool e);
	void exifscenetypeChanged(bool e);
	void exifflengthChanged(bool e);
	void exiffnumberChanged(bool e);
	void exiflightsourceChanged(bool e);
	void iptckeywordsChanged(bool i);
	void iptclocationChanged(bool i);
	void iptccopyrightChanged(bool i);
	void exifgpsChanged(bool e);

};

#endif // SETTINGS_H
