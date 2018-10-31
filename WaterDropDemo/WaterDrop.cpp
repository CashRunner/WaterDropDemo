#include "WaterDrop.h"
#include <QPainter>

// ˮ�ε�Ĭ�ϰ뾶;
#define WATER_DROP_RADIUS 15

WaterDrop::WaterDrop(QWidget *parent)
	: QWidget(parent)
	, m_waterDropAnimation(NULL)
	, m_animationRadius(0)
	, m_waterDropColor(QColor(255, 120, 0, 150))    // Ĭ��Ϊ�ٻ�ɫ;
    , m_waterDropRadisu(WATER_DROP_RADIUS)
{
	this->setFixedSize(QSize(WATER_DROP_RADIUS * 2, WATER_DROP_RADIUS * 2));
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
	this->setAttribute(Qt::WA_TranslucentBackground);

	// �ؼ���ʾ��رպ��Զ�ɾ��;
	this->setAttribute(Qt::WA_DeleteOnClose);

	m_waterDropAnimation = new QVariantAnimation(this);
}

WaterDrop::~WaterDrop()
{
}

// ����ˮ�ε���ɫ;
void WaterDrop::setColor(QColor color)
{
	m_waterDropColor = color;
}

// ����ˮ�ΰ뾶;
void WaterDrop::setRadius(int radius)
{
    m_waterDropRadisu = radius;
    this->setFixedSize(QSize(m_waterDropRadisu * 2, m_waterDropRadisu * 2));
}

void WaterDrop::showWaterDrop(const QPoint &point)
{
    // ͨ�������಻�Ͻ����ػ�;
    m_waterDropAnimation->setStartValue(0);
    m_waterDropAnimation->setEndValue(m_waterDropRadisu);
    m_waterDropAnimation->setDuration(350);

    connect(m_waterDropAnimation, &QVariantAnimation::valueChanged, this, &WaterDrop::onRaduisChanged);
    connect(m_waterDropAnimation, &QVariantAnimation::finished, this, &WaterDrop::close);
    m_waterDropAnimation->start();

    // ����Ҫ��������ĵ�ת��ΪԲ�ĵ�����;
    QPoint translatePoint = point - QPoint(m_waterDropRadisu, m_waterDropRadisu);
    __super::move(translatePoint);
    __super::show();
}

// ��������ˮ�ε��Ч��;
void WaterDrop::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QBrush(m_waterDropColor));

	// ˼·�����Ȼ���һ���̶���С��ԲA��Ȼ�����ͬһԲ�ĵ�͸����ԲB��Ȼ��ͨ����������ԲB�İ뾶��0������m_waterDropRadisu�����¸��ǹ̶���ԲA;
	QPainterPath waterDropPath;
	waterDropPath.addEllipse(QPoint(m_waterDropRadisu, m_waterDropRadisu), m_waterDropRadisu, m_waterDropRadisu);
	QPainterPath hidePath;
	hidePath.addEllipse(QPoint(m_waterDropRadisu, m_waterDropRadisu), m_animationRadius, m_animationRadius);

	waterDropPath -= hidePath;
	painter.drawPath(waterDropPath);
}

void WaterDrop::onRaduisChanged(QVariant value)
{
	// ��������ԲB�İ뾶ֵ,���ػ�;
	m_animationRadius = value.toInt();
	update();
}