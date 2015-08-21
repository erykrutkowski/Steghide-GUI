/* *********************************************************************** *
 * XINX                                                                    *
 * Copyright (C) 2009 by Ulrich Van Den Hekke                              *
 * ulrich.vdh@shadoware.org                                                *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 * *********************************************************************** */

// Xinx header
#include "categoryitemmodel.h"
#include "snipetmanager.h"

// Qt header
#include <QIcon>
#include <QColor>
#include <QFont>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>

/* CategoryItemModel */

CategoryItemModel::CategoryItemModel( QSqlDatabase db, QObject * parent ) : QAbstractProxyModel( parent ), m_db( db ) {
	// This will be automatically deleted.
	m_sourceModel = new QSqlQueryModel( this );
	setSourceModel( m_sourceModel );

	createMapping();
}

CategoryItemModel::~CategoryItemModel() {
	qDeleteAll( m_sourcesIndexMapping );
}

void CategoryItemModel::select() {
	// Set the query used all snipet
	m_sourceModel->setQuery(
			"SELECT id, parent_id, name "
			"FROM categories "
			"ORDER BY name", m_db
			);

	// Define name for header column
	m_sourceModel->setHeaderData( list_id, Qt::Horizontal, tr("Id") );
	m_sourceModel->setHeaderData( list_parentid, Qt::Horizontal, tr("Parent") );
	m_sourceModel->setHeaderData( list_name, Qt::Horizontal, tr("Name") );

	// Initialize the mapping
	createMapping();

	// Reset the layout
	reset();
}

/*! \internal
	Create the mapping of all index in the table.
*/
void CategoryItemModel::createMapping() {
	qDeleteAll( m_sourcesIndexMapping );
	m_sourcesIndexMapping.clear();
	m_categoryIdMapping.clear();

	int source_rows = m_sourceModel->rowCount();
	for( int i = -1; i < source_rows; ++i ) {
		Mapping * m = new Mapping;
		IndexMap::const_iterator it = IndexMap::const_iterator( m_sourcesIndexMapping.insert( i, m ) );
		m->index = i;
		m->parrentId = 0;
		m->parentIndex = 0;

		if( i >= 0 ) {
			QSqlRecord record = m_sourceModel->record( i );
			m_categoryIdMapping[ record.value( list_id ).toInt() ] = i;
			m->id = record.value( list_id ).toInt();
		} else { // Create the root Item
			m->id = 0;
			m_categoryIdMapping[ 0 ] = -1;
		}
	}

	for( int i = 0; i < source_rows; ++i ) {
		QSqlRecord record = m_sourceModel->record( i );

		int parentCategoryId = record.value( list_parentid ).toInt();
		int parentCategoryIndex = m_categoryIdMapping.value( parentCategoryId, -2 );
		Q_ASSERT( parentCategoryIndex > -2 );
		Mapping * mapping = m_sourcesIndexMapping.value( i );
		mapping->parentIndex = parentCategoryIndex;
		mapping->parrentId   = parentCategoryId;

		Mapping * categoryMapping = m_sourcesIndexMapping.value( parentCategoryIndex );
		categoryMapping->source_rows.append( i );
	}
}

int CategoryItemModel::proxyColumnToSource( int proxyColumn ) const {
	if( proxyColumn == 0 )
		return list_name;
	return -1;
}

int CategoryItemModel::sourceColumnToProxy( int sourceColumn ) const {
	if( sourceColumn == list_name )
		return 0;
	return -1;
}

/// For the given source index, this method return the corresponding index in the proxy
QModelIndex CategoryItemModel::mapFromSource ( const QModelIndex & sourceIndex ) const {
	if( ! sourceIndex.isValid() ) return QModelIndex();
	if( sourceIndex.model() != m_sourceModel ) {
		qWarning( "CategoryItemModel: index from wrong model passed to mapFromSource" );
		return QModelIndex();
	}

	int row = sourceIndex.row();
	IndexMap::const_iterator it = m_sourcesIndexMapping.constFind( row );
	Q_ASSERT( it != m_sourcesIndexMapping.constEnd() );

	int parentRow = it.value()->parentIndex;
	IndexMap::const_iterator parentIt = m_sourcesIndexMapping.constFind( parentRow );
	Q_ASSERT( parentIt != m_sourcesIndexMapping.constEnd() );

	Mapping * m = parentIt.value();

	int proxyRow = m->source_rows.indexOf( row ), proxyColumn = sourceColumnToProxy( sourceIndex.column() );
	if( proxyColumn == -1 ) return QModelIndex();

	return createIndex( proxyRow, proxyColumn, *parentIt );
}

QModelIndex CategoryItemModel::mapToSource ( const QModelIndex & proxyIndex ) const {
	if( ! proxyIndex.isValid() ) return QModelIndex();
	if( proxyIndex.model() != this ) {
		qWarning( "CategoryItemModel: index from wrong model passed to mapToSource" );
		return QModelIndex();
	}

	Mapping * m = static_cast<Mapping*>( proxyIndex.internalPointer() );

	int sourceColumn = proxyColumnToSource( proxyIndex.column() );
	if( sourceColumn == -1 ) return QModelIndex();

	int sourceRow = m->source_rows.at( proxyIndex.row() );

	return m_sourceModel->index( sourceRow, sourceColumn );
}

QModelIndex CategoryItemModel::index( int row, int column, const QModelIndex & parent ) const {
	if( ( row < 0 ) || ( column < 0 ) ) return QModelIndex();

	IndexMap::const_iterator it = m_sourcesIndexMapping.constFind( -1 );

	QModelIndex sourceParent = mapToSource( parent );
	if( sourceParent.isValid() ) {
		it = m_sourcesIndexMapping.constFind( sourceParent.row() );
	}

	Q_ASSERT( it != m_sourcesIndexMapping.constEnd() );
	if( it.value()->source_rows.count() <= row )
		return QModelIndex();

	return createIndex( row, column, *it );
}

QModelIndex CategoryItemModel::index( int categoryId ) {
	int sourceRow = m_categoryIdMapping.value( categoryId, -1 );
	if( sourceRow >= 0 ) {
		Mapping * m = m_sourcesIndexMapping.value( sourceRow );

		int parentRow = m->parentIndex;
		IndexMap::const_iterator parentIt = m_sourcesIndexMapping.constFind( parentRow );
		Q_ASSERT( parentIt != m_sourcesIndexMapping.constEnd() );

		Mapping * parrentMapping = parentIt.value();

		int proxyRow = parrentMapping->source_rows.indexOf( m->index );

		return createIndex( proxyRow, 0, *parentIt );
	}
	return QModelIndex();
}

QModelIndex CategoryItemModel::parent( const QModelIndex & index ) const {
	if( ! index.isValid() ) return QModelIndex();

	Mapping * m = static_cast<Mapping*>( index.internalPointer() );

	int sourceRow = m->index;
	if( sourceRow == -1 ) return QModelIndex();

	QModelIndex sourceParent = m_sourceModel->index( sourceRow, proxyColumnToSource( 0 ) );
	QModelIndex proxyParent = mapFromSource( sourceParent );

	return proxyParent;
}

int CategoryItemModel::rowCount( const QModelIndex & index ) const {
	if( index.column() > 0 ) return 0;
	if( ! index.isValid() ) {
		Mapping * rootMapping = m_sourcesIndexMapping.value( -1 );
		return rootMapping->source_rows.count();
	} else {
		Mapping * parrentMapping = static_cast<Mapping*>( index.internalPointer() );
		int sourceRowIndex = parrentMapping->source_rows.at( index.row() );
		Mapping * rowMapping = m_sourcesIndexMapping.value( sourceRowIndex );

		return rowMapping->source_rows.count();
	}
}

int CategoryItemModel::columnCount( const QModelIndex & index ) const {
	Q_UNUSED( index );

	return 1;
}

QVariant CategoryItemModel::data( const QModelIndex & index, int role ) const {
	if( ! index.isValid() ) return QVariant();

	if( role == Qt::DecorationRole ) {
		if( index.column() == 0 ) {
			return QIcon( ":/images/folder.png" );
		}
	} else if( role == CategoryItemModel::CategoryIdRole ) {
		QModelIndex sourceIndex = mapToSource( index );
		QSqlRecord record = m_sourceModel->record( sourceIndex.row() );
		return record.value( list_id );
	}

	return QAbstractProxyModel::data( index, role );
}

