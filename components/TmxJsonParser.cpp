
#include "TmxJsonParser.h"
#include <cstdlib>
#include <cstdio>
#include <string>
#include <sstream>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>

namespace tmxparser
{


std::string GetChildValue_string(QJsonObject &parent, QString childName)
{
    if (!parent.contains(childName))
        return "";

    return parent[childName].toString().toStdString();
}

int GetChildValue_int(QJsonObject &parent, QString childName, int defaultValue)
{
    if (!parent.contains(childName))
        return defaultValue;

    return parent[childName].toInt(defaultValue);
}

double GetChildValue_double(QJsonObject &parent, QString childName, double defaultValue)
{
    if (!parent.contains(childName))
        return defaultValue;

    return parent[childName].toDouble(defaultValue);
}


void json_parsePropertyNode(QJsonObject& parent, PropertyMap_t* outPropertyMap)
{
    if (!parent.contains("properties"))
        return;
    QJsonObject properties = parent["properties"].toObject();

    for(QString propertyName: properties.keys())
    {
        std::string valuestring = properties[propertyName].toString().toStdString();
        (*outPropertyMap)[propertyName.toStdString()] = valuestring;
    }
}

void json_parsePointsArray(QJsonArray &points, PointCollection_t* outPoints)
{
    for(QJsonValueRef pointRef : points)
    {
        if (!pointRef.isNull())
        {
            QJsonObject point = pointRef.toObject();
            if (point.contains("x") && point.contains("y"))
            {
                QPoint p( point["x"].toInt(), point["y"].toInt() );
                outPoints->push_back( p );
            }
        }
	}
}

void json_parseObjectNode(QJsonObject &item, Object_t* outObj)
{
	outObj->name = GetChildValue_string(item, "name");;
	outObj->type = GetChildValue_string(item, "type");

	outObj->x = GetChildValue_int(item, "x", 0);
	outObj->y = GetChildValue_int(item, "y", 0);
	outObj->width		= GetChildValue_int(item, "width", 0);
	outObj->height		= GetChildValue_int(item, "height", 0);
	outObj->rotation	= GetChildValue_double(item, "rotation", 0.0);
	outObj->visible		= GetChildValue_int(item, "visible", 1);
	outObj->referenceGid = GetChildValue_int(item, "gid", 0);

	json_parsePropertyNode(item, &outObj->propertyMap);

    if (item.contains("ellipse"))
		outObj->shapeType = kEllipse;
    else if (item.contains("polyline"))
    {
        outObj->shapeType = kPolyline;
        QJsonArray polylinePoints = item["polyline"].toArray();
        json_parsePointsArray(polylinePoints, &outObj->shapePoints);
    }
    else if (item.contains("polygon"))
	{
		outObj->shapeType = kPolygon;
        QJsonArray polygonPoints = item["polygon"].toArray();
        json_parsePointsArray(polygonPoints, &outObj->shapePoints);
	}
	else if (outObj->referenceGid>0)
		outObj->shapeType = kSprite;
	else	outObj->shapeType = kSquare;
}

void json_parseLayer(QJsonObject &item, Layer_t* outLayer)
{
    outLayer->name = GetChildValue_string(item, "name");
	outLayer->opacity = GetChildValue_double(item, "opacity", 0.0);
	outLayer->visible = GetChildValue_int(item, "visible", 1);
    outLayer->offset.setX( GetChildValue_int(item, "offsetx", 0) );
    outLayer->offset.setY( GetChildValue_int(item, "offsety", 0) );
    outLayer->size.setX( GetChildValue_int(item, "width", 0) );
    outLayer->size.setY( GetChildValue_int(item, "height", 0) );

	json_parsePropertyNode(item, &outLayer->propertyMap);
}

void json_parseLayerTiles(QJsonObject &item, Layer_t* outLayer)
{
    if (!item.contains("data"))
        return;
    QJsonArray data = item["data"].toArray();
    for(QJsonValueRef value : data)
	{
        if (!value.isNull())
            outLayer->tiles.push_back( value.toInt() );
	}
}


void json_parseLayerObjects(QJsonObject &item, Layer_t* outLayer)
{
    if (!item.contains("objects"))
        return;
    QJsonArray objects = item["objects"].toArray();

    for(QJsonValueRef objectRef : objects)
	{
		Object_t obj;
        if (!objectRef.isNull())
        {
            QJsonObject object = objectRef.toObject();
            json_parseObjectNode(object, &obj);
            outLayer->objects.push_back(obj);
        }
	}
}

void json_parseTilesetNode(QJsonObject &item, Tileset_t* outTileset)
{
    outTileset->firstgid = GetChildValue_int(item, "firstgid", -1);
    outTileset->tileCount= GetChildValue_int(item, "tilecount", 0);
	outTileset->tileWidth = GetChildValue_int(item, "tilewidth", 0);
	outTileset->tileHeight = GetChildValue_int(item, "tileheight", 0);
	outTileset->imageWidth = GetChildValue_int(item,"imagewidth", 0);
	outTileset->imageHeight = GetChildValue_int(item,"imageheight", 0);
	outTileset->tileSpacingInImage = GetChildValue_int(item, "spacing", 0);
	outTileset->tileMarginInImage = GetChildValue_int(item, "margin", 0);

	outTileset->name = GetChildValue_string(item, "name");
	outTileset->imagePath = GetChildValue_string(item, "image");
}


void json_parseMapNode(QJsonDocument &doc, Map_t* outMap)
{
    if (doc.isEmpty() || !doc.isObject())
        return;

    auto item = doc.object();

    outMap->version = GetChildValue_int(item,"version", 0);
    outMap->orientation = GetChildValue_string(item, "orientation");
    outMap->numTilesX = GetChildValue_int(item, "width",0);
    outMap->numTilesY = GetChildValue_int(item,"height",0);
    outMap->tileWidth = GetChildValue_int(item,"tilewidth", 0);
    outMap->tileHeight = GetChildValue_int(item,"tileheight",0);
	outMap->backgroundColor = GetChildValue_string(item,"backgroundcolor");

	json_parsePropertyNode(item, &outMap->propertyMap);

    auto tilesets = item["tilesets"];
    if (!tilesets.isNull() && tilesets.isArray())
	{
        auto array = tilesets.toArray();
        for(QJsonValueRef tilesetRef :array)
        {
            if (!tilesetRef.isNull())
            {
                Tileset_t set;
                QJsonObject tileset = tilesetRef.toObject();
                json_parseTilesetNode( tileset, &set);
                outMap->tilesets.push_back(set);
            }
        }
	}

    QJsonValueRef layersRef = item["layers"];
    if (!layersRef.isNull() && layersRef.isArray())
	{
        QJsonArray layers = layersRef.toArray();
        for(QJsonValueRef layerRef : layers)
        {
            QJsonObject layer  = layerRef.toObject();
			Layer_t tmxLayer;
			json_parseLayer(layer, &tmxLayer);

            std::string typeStr = GetChildValue_string(layer, "type");
			if (typeStr=="tilelayer")				json_parseLayerTiles(layer, &tmxLayer);
			else if (typeStr=="objectgroup")		json_parseLayerObjects(layer, &tmxLayer);

			outMap->layers.push_back(tmxLayer);
        }
	}
}


void parseTmxFromJSON_file(const QString& filename, tmxparser::Map_t* outMap)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray buffer = file.readAll();
        //buffer.append(char(0)); //null terminate
        file.close();
	
        QJsonParseError parseError;
        QJsonDocument doc( QJsonDocument::fromJson( buffer, &parseError) );
        if (parseError.error==QJsonParseError::NoError)
        {
            json_parseMapNode(doc, outMap);
        }
        else
        {
            qDebug() << "Error: " << parseError.error << " at character: " << parseError.offset << " while parsing TMX file: " << filename;
        }
    }
}

int CountLayerTilesetUsage(Map_t &map, int layerIndex, int tilesetIndex)
{
    unsigned int firstIndex = map.tilesets[tilesetIndex].firstgid;
    unsigned int lastIndex = UINT_MAX;
    if (tilesetIndex>=0 && tilesetIndex<map.tilesets.size())
        lastIndex = map.tilesets[tilesetIndex+1].firstgid;

    auto tiles = map.layers[layerIndex].tiles;
    int count=0;
    for(unsigned int tileIndex : tiles)
    {
        if (tileIndex>=firstIndex && tileIndex<lastIndex)
            count++;
    }
    return count;
}

}
