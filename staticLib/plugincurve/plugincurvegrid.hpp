#ifndef PLUGINCURVEGRID_HPP
#define PLUGINCURVEGRID_HPP

#include "plugincurveview.hpp"
#include "plugincurvemap.hpp"
#include <QGraphicsObject>


class PluginCurveGrid : public QGraphicsObject
{

Q_OBJECT
/*!
*  This class represent the grid.
*  Permits to paint the grid. @n
*
*  @brief Grid
*  @author Simon Touchard, Myriam Desainte-Catherine
*  @date 2014
*/

// Attributes
private:
    PluginCurveMap *_pMap; /*!< Permit to transform devices from paint coordinate to scale coordinate and vice versa. */
    PluginCurveMap *_pDefaultMap; /*!< The default map if no map is giving.*/
public:
    //! Constructor.
    /*!
        \param parent The parent item.
        \param map The map used for transform coordinates.
    */
    PluginCurveGrid(PluginCurveView *parent,PluginCurveMap *map);
    /*! Set the coordinate system according to the new map. */
    void setMap(PluginCurveMap *map);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

signals:

public slots:
    void mapChanged(); //! The map changed, redraw the grid.

};

#endif // PLUGINCURVEGRID_HPP
