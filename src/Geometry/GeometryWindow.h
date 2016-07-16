/******************************************************************************************************
 * (C) 2016 markummitchell@github.com. This file is part of Engauge Digitizer, which is released      *
 * under GNU General Public License version 2 (GPLv2) or (at your option) any later version. See file *
 * LICENSE or go to gnu.org/licenses for details. Distribution requires prior written permission.     *
 ******************************************************************************************************/

#ifndef GEOMETRY_WINDOW_H
#define GEOMETRY_WINDOW_H

#include "DocumentModelExportFormat.h"
#include "GeometryStrategyContext.h"
#include <QDockWidget>

class CmdMediator;
class Curve;
class QItemSelection;
class QStandardItemModel;
class QString;
class QTableView;
class Transformation;

/// Window that displays the geometry information, as a table, for the current curve
class GeometryWindow : public QDockWidget
{
  Q_OBJECT;

public:
  /// Single constructor. Parent is needed or else this widget cannot be redocked after being undocked
  GeometryWindow (QWidget *parent);
  virtual ~GeometryWindow ();

  /// Clear stale information
  void clear ();

  /// Catch close event so corresponding menu item in MainWindow can be updated accordingly
  virtual void closeEvent(QCloseEvent *event);

  /// Populate the table with the specified Curve
  void update (const CmdMediator &cmdMediator,
               const QString &curveSelected,
               const Transformation &transformation);

public slots:
  /// Prepare for copy after selection has changed
  void slotSelectionChanged (const QItemSelection &, const QItemSelection &);

signals:
  /// Signal that this QDockWidget was just closed
  void signalGeometryWindowClosed();

private:
  GeometryWindow();

  int fold2dIndexes (int row,
                     int col,
                     int rowLow,
                     int colLow,
                     int colHigh) const;
  void initializeHeader();
  void loadStrategies ();
  void resizeTable (int rowCount);

  enum ColumnsHeader {
    COLUMN_HEADER_LABEL,
    COLUMN_HEADER_VALUE,
    NUM_HEADER_COLUMNS
  };

  enum ColumnsBody {
    COLUMN_BODY_X,
    COLUMN_BODY_Y,
    COLUMN_BODY_INDEX,
    COLUMN_BODY_DISTANCE_GRAPH_FORWARD,
    COLUMN_BODY_DISTANCE_PERCENT_FORWARD,
    COLUMN_BODY_DISTANCE_GRAPH_BACKWARD,
    COLUMN_BODY_DISTANCE_PERCENT_BACKWARD,
    NUM_BODY_COLUMNS
  };

  enum HeaderRows {
    HEADER_ROW_NAME,
    HEADER_ROW_FUNC_AREA,
    HEADER_ROW_POLY_AREA,
    HEADER_ROW_COLUMN_NAMES,
    NUM_HEADER_ROWS
  };

  QTableView *m_view;
  QStandardItemModel *m_model;

  GeometryStrategyContext m_geometryStrategyContext;

  // Export format is updated after every CmdAbstractBase gets redone/undone
  DocumentModelExportFormat m_modelExport;
};

#endif // GEOMETRY_WINDOW_H
