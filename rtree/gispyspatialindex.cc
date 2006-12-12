/*
# =============================================================================
# Rtree spatial index. Copyright (C) 2006 Ancient World Mapping Center
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the Free
# Software Foundation; either version 2 of the License, or (at your option)
# any later version.
#
# This program is distributed in the hope that it will be useful, but WITHOUT
# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
# details.
#
# You should have received a copy of the GNU General Public License along with
# this program; if not, write to the Free Software Foundation, Inc., 59 Temple
# Place, Suite 330, Boston, MA 02111-1307 USA
#
# Contact email: sgillies@frii.com
# =============================================================================
*/

#include <SpatialIndex.h>
#include "gispyspatialindex.h"

using namespace SpatialIndex;

GISPySpatialIndex::GISPySpatialIndex()
{
  // for now only memory manager
  mStorageManager = StorageManager::createNewMemoryStorageManager();

  // create buffer

  unsigned int capacity = 10;
  bool writeThrough = false;
  mStorage = StorageManager::createNewRandomEvictionsBuffer(*mStorageManager, capacity, writeThrough);

  // R-Tree parameters
  double fillFactor = 0.7;
  unsigned long indexCapacity = 10;
  unsigned long leafCapacity = 10;
  unsigned long dimension = 2;
  RTree::RTreeVariant variant = RTree::RV_RSTAR;

  // create R-tree
  long indexId;
  mRTree = RTree::createNewRTree(*mStorage, fillFactor, indexCapacity,
                                 leafCapacity, dimension, variant, indexId);
}

GISPySpatialIndex:: ~GISPySpatialIndex()
{
  delete mRTree;
  delete mStorage;
  delete mStorageManager;
}

