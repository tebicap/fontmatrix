/***************************************************************************
 *   Copyright (C) 2007 by Pierre Marchand   *
 *   pierre@oep-h.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef FONTITEM_H
#define FONTITEM_H

#include <QString>
#include <QStringList>
#include <QByteArray>
#include <QMap>
#include <QPointF>
#include <QPainterPath>
#include <QGraphicsPathItem>
#include <QIcon>

#include <ft2build.h>
#include FT_FREETYPE_H

class QGraphicsPixmapItem;
class QGraphicsScene;
class QGraphicsRectItem;
struct OTFSet;
class FmOtf;

/**
	@author Pierre Marchand <pierre@oep-h.com>

	(reminder) glyph data -> 1 = index, 2 = charcode
*/
class FontItem : public QObject
{

		Q_OBJECT
	public:
		FontItem ( QString path );

		~FontItem();
	private:
		QString m_path;
		QString m_afm;
		QString m_name;
		// Basically, we collect all infos that are in an FT_FaceRec
		QString m_faceFlags;
		QString m_type;
		QString m_styleFlags;
		QString m_family;
		QString m_variant;
		double m_size;
		int m_numGlyphs;
		int m_numFaces;
		QStringList m_charsets;
		QList<int> m_charLess;
		
		bool m_isOpenType;
		FmOtf *otf;

		QString m_author;
		QString m_foundry;

		QStringList m_tags;
		QString m_cacheInfo;

		FT_Error      ft_error;
		FT_Face m_face;
		int facesRef;
		FT_GlyphSlot m_glyph;
		
		QGraphicsPathItem* itemFromChar ( int charcode, double size );
		QGraphicsPathItem* itemFromGindex ( int index, double size );
		
		QGraphicsPixmapItem* itemFromCharPix ( int charcode, double size );
		QGraphicsPixmapItem* itemFromGindexPix ( int index, double size );
		
		bool m_rasterFreetype;
		
		bool ensureLibrary();
		bool ensureFace();
		void releaseFace();

		QString testFlag ( long flag , long against, QString yes, QString no );
		QByteArray pixarray ( uchar *b, int len );


		QList<QGraphicsPixmapItem *> pixList;
		QList<QGraphicsPathItem*> glyphList;
		QList<QGraphicsTextItem*> labList;
		QList<QGraphicsRectItem*> selList;
		QList<QGraphicsScene *> sceneList;


		bool allIsRendered;
		int m_glyphsPerRow;
		bool hasUnicode;
		int currentChar;

		bool m_lock;
// 		QMap<int,QPainterPath> contourCache;
		QMap<int,double> advanceCache;

		QIcon theOneLinePreviewIcon;
		QPixmap theOneLinePreviewPixmap;

		static QGraphicsScene *theOneLineScene;

		void moreInfo_sfnt();
		void moreInfo_type1();

		QMap<int,QMap<QString, QString> > moreInfo;
		void fillLangIdMap();


	public:
		static FT_Library theLibrary;
		static QMap<FT_Encoding, QString> charsetMap;

		QString path() {return m_path;};
		QString afm() {return m_afm;};
		void setAfm ( QString apath ) {m_afm = apath;};
		QString faceFlags() {return m_faceFlags;};
		QString family() {return m_family;};
		QString variant() {return m_variant;};
		QStringList tags() {return m_tags;};
		void setTags ( QStringList l );
		QString name();
		QString fancyName() {return m_family + " " + m_variant;};
		QString infoText ( bool fromcache = true );
		QString infoGlyph ( int index, int code = 0 );
		QString glyphName(int codepoint);

		QString value ( QString k );

		void renderLine ( QGraphicsScene *scene, QString spec,  QPointF origine, double fsize, bool record = true );
		void renderLine ( OTFSet set, QGraphicsScene *scene, QString spec,  QPointF origine, double fsize, bool record = true );
		void renderAll ( QGraphicsScene *scene, int begin_code, int end_code );
		int countCoverage ( int begin_code, int end_code );
		void deRender ( QGraphicsScene *scene );
		void deRenderAll();

		QString toElement();

		QGraphicsPathItem* hasCodepoint ( int code );

		QIcon oneLinePreviewIcon ( QString oneline );
		QPixmap oneLinePreviewPixmap ( QString oneline );

		bool isActivated();
		void setActivated ( bool act );

		// Relative to fontactionwidget
		void lock() {m_lock=true;};
		void unLock() {m_lock=false;};
		bool isLocked() {return m_lock;};

// 		int debug_size();

		void adjustGlyphsPerRow ( int width );

		static QMap<int, QString> langIdMap;
		
		bool isOpenType(){return m_isOpenType;};
		FmOtf *takeOTFInstance();
		void releaseOTFInstance(FmOtf * rotf);
		
		void setFTRaster(bool f){m_rasterFreetype = f;};
		bool rasterFreetype(){return m_rasterFreetype;};

};

#endif
