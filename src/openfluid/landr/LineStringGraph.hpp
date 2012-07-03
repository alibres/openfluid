/*
 This file is part of OpenFLUID software
 Copyright (c) 2007-2010 INRA-Montpellier SupAgro


 == GNU General Public License Usage ==

 OpenFLUID is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 OpenFLUID is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with OpenFLUID.  If not, see <http://www.gnu.org/licenses/>.

 In addition, as a special exception, INRA gives You the additional right
 to dynamically link the code of OpenFLUID with code not covered
 under the GNU General Public License ("Non-GPL Code") and to distribute
 linked combinations including the two, subject to the limitations in this
 paragraph. Non-GPL Code permitted under this exception must only link to
 the code of OpenFLUID dynamically through the OpenFLUID libraries
 interfaces, and only for building OpenFLUID plugins. The files of
 Non-GPL Code may be link to the OpenFLUID libraries without causing the
 resulting work to be covered by the GNU General Public License. You must
 obey the GNU General Public License in all respects for all of the
 OpenFLUID code and other code used in conjunction with OpenFLUID
 except the Non-GPL Code covered by this exception. If you modify
 this OpenFLUID, you may extend this exception to your version of the file,
 but you are not obligated to do so. If you do not wish to provide this
 exception without modification, you must delete this exception statement
 from your version and license this OpenFLUID solely under the GPL without
 exception.


 == Other Usage ==

 Other Usage means a use of OpenFLUID that is inconsistent with the GPL
 license, and requires a written agreement between You and INRA.
 Licensees for Other Usage of OpenFLUID may use this file in accordance
 with the terms contained in the written agreement between You and INRA.
 */

/**
 \file LineStringGraph.hpp
 \brief Header of ...

 \author Aline LIBRES <aline.libres@gmail.com>
 */

#ifndef LINESTRINGGRAPH_HPP_
#define LINESTRINGGRAPH_HPP_

#include <geos/planargraph/PlanarGraph.h>

#include <openfluid/landr/LineStringUnit.hpp>

#include <vector>

namespace geos {
namespace geom {
class LineString;
class Coordinate;
}
namespace planargraph {
class Node;
class Edge;
class DirectedEdge;
}
}

namespace openfluid {
namespace core {
class GeoVectorValue;
}
}

namespace openfluid {
namespace landr {

class LineStringGraph: public geos::planargraph::PlanarGraph
{
  private:

    geos::planargraph::Node* getNode(const geos::geom::Coordinate& Coordinate);

    std::vector<geos::planargraph::Node*> m_NewNodes;

    std::map<int, openfluid::landr::LineStringUnit*> m_UnitsBySelfId;

    std::vector<openfluid::landr::LineStringUnit*> m_Units;

    std::vector<geos::planargraph::DirectedEdge*> m_NewDirEdges;

    void addAttribute(std::string AttributeName, LineStringUnit& Unit);

    void removeAttribute(std::string AttributeName, LineStringUnit& Unit);

  public:

    LineStringGraph();

    LineStringGraph(const openfluid::core::GeoVectorValue& Val);

    LineStringGraph(openfluid::landr::LineStringGraph& Other);

    LineStringGraph(
        const std::vector<openfluid::landr::LineStringUnit*>& Units);

    /**
     * Takes ownership of LineString and Feature
     */
    openfluid::landr::LineStringUnit* addEdge(
        const geos::geom::LineString* LineString, OGRFeature* Feat);

    virtual ~LineStringGraph();

    openfluid::landr::LineStringUnit* getLastLineStringUnit();

    std::vector<openfluid::landr::LineStringUnit*> getEndLineStringUnits();

    std::vector<openfluid::landr::LineStringUnit*> getStartLineStringUnits();

    unsigned int getSize();

    openfluid::landr::LineStringUnit* getUnit(int SelfId);

    std::vector<openfluid::landr::LineStringUnit*> getUnits();

    /**
     * Doesn't reset if the AttributeName already exists.
     */
    void addAttribute(std::string AttributeName);

    /**
     * Does nothing if AttributeName doesn't exist.
     */
    void removeAttribute(std::string AttributeName);

};

} // namespace landr
} /* namespace openfluid */

#endif /* LINESTRINGGRAPH_HPP_ */
