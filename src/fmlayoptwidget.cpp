//
// C++ Implementation: fmlayoptwidget
//
// Description: 
//
//
// Author: Pierre Marchand <pierremarc@oep-h.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include "fmlayoptwidget.h"
#include <QDebug>

FMLayOptWidget::FMLayOptWidget(QWidget * parent)
	:QWidget(parent)
{
	setupUi(this);
	
	connect(beforeSlid,SIGNAL(valueChanged( int )),this,SLOT(bChanged(int)));
	connect(fitSlid,SIGNAL(valueChanged( int )),this,SLOT(exChanged(int)));
	connect(afterSlid,SIGNAL(valueChanged( int )),this,SLOT(aChanged(int)));
	connect(endSlid,SIGNAL(valueChanged( int )),this,SLOT(enChanged(int)));
	connect(hyphSlid,SIGNAL(valueChanged( int )),this,SLOT(hChanged(int)));
	
	connect(beforeSlid,SIGNAL(sliderReleased ()),this,SLOT(bEdited()));
	connect(fitSlid,SIGNAL(sliderReleased ()),this,SLOT(exEdited()));
	connect(afterSlid,SIGNAL(sliderReleased ()),this,SLOT(aEdited()));
	connect(endSlid,SIGNAL(sliderReleased ()),this,SLOT(enEdited()));
	connect(hyphSlid,SIGNAL(sliderReleased ()),this,SLOT(hEdited()));
}

void FMLayOptWidget::bChanged(int cv)
{
	bScore->setText(QString::number(cv));
}

void FMLayOptWidget::exChanged(int cv)
{
	eScore->setText(QString::number(cv));
}

void FMLayOptWidget::aChanged(int cv)
{
	aScore->setText(QString::number(cv));
}

void FMLayOptWidget::enChanged(int cv)
{
	endScore->setText(QString::number(cv));
}

void FMLayOptWidget::hChanged(int cv)
{
	hPenalty->setText(QString::number((double)cv/10.0));
}

void FMLayOptWidget::bEdited()
{
		emit valueChanged(BEFORE);
}

void FMLayOptWidget::exEdited()
{
		emit valueChanged(EXACT);
}

void FMLayOptWidget::aEdited()
{
		emit valueChanged(AFTER);
}

void FMLayOptWidget::enEdited()
{
		emit valueChanged(END);
}

void FMLayOptWidget::hEdited()
{
		emit valueChanged(HYPHEN);
}

void FMLayOptWidget::setRange(V v, int min, int max)
{
	switch (v)
	{
		case BEFORE:beforeSlid->setRange(min,max);
		break;
		case EXACT:fitSlid->setRange(min,max);
		break;
		case AFTER:afterSlid->setRange(min,max);
		break;
		case END:endSlid->setRange(min,max);
		break;
		case HYPHEN:hyphSlid->setRange(min,max);
		break;
		default:break;
	}
}

void FMLayOptWidget::setValue(V v, int value)
{
	switch (v)
	{
		case BEFORE:beforeSlid->setValue(value);
		bScore->setText(QString::number(value));
		break;
		case EXACT:fitSlid->setValue(value);
		eScore->setText(QString::number(value));
		break;
		case AFTER:afterSlid->setValue(value);
		aScore->setText(QString::number(value));
		break;
		case END:endSlid->setValue(value);
		endScore->setText(QString::number(value));
		break;
		case HYPHEN:hyphSlid->setValue(value);
		hPenalty->setText(QString::number((double)value/10));
		break;
		default:break;
	}
}

double FMLayOptWidget::getValue(V v)
{
	switch (v)
	{
		case BEFORE:return beforeSlid->value();
		break;
		case EXACT:return fitSlid->value();
		break;
		case AFTER:return afterSlid->value();
		break;
		case END:return endSlid->value();
		break;
		case HYPHEN:return hyphSlid->value();
		break;
		default:break;
	}
	return 0.0;
}

