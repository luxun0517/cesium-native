#include "Cesium3DTiles/WriterContext.h"
#include <algorithm>
#include <catch2/catch.hpp>
#include <cstddef>
#include <gsl/span>
#include <iostream>
#include <rapidjson/document.h>
#include <sstream>
#include <string>

using namespace Cesium3DTiles;
using namespace CesiumJsonWriter;

TEST_CASE("Write 3D Tiles Tileset", "[3DTilesWriter]") {
  using namespace std::string_literals;

  Cesium3DTiles::Tile t1, t2, t3;
  t1.boundingVolume.box = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  t1.geometricError = 15.0;
  t1.refine = Cesium3DTiles::Tile::Refine::ADD;

  t2.boundingVolume.box = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21};
  t2.viewerRequestVolume = Cesium3DTiles::BoundingVolume();
  t2.viewerRequestVolume
      ->box = {30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41};
  t2.geometricError = 25.0;
  t2.refine = Cesium3DTiles::Tile::Refine::REPLACE;

  t3.boundingVolume.box = {20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31};
  t3.geometricError = 35.0;
  t3.children = {t1, t2};

  Cesium3DTiles::Asset asset;
  asset.version = "version";

  Cesium3DTiles::TilesetProperties p1, p2;
  p1.maximum = 10.0;
  p1.minimum = 0.0;
  p2.maximum = 5.0;
  p2.minimum = 1.0;

  Cesium3DTiles::Tileset::Properties ps;
  ps.additionalProperties = {{"p1", p1}, {"p2", p2}};

  Cesium3DTiles::Tileset ts;
  ts.asset = asset;
  ts.root = t3;
  ts.extensionsUsed = {"ext1", "ext2"};
  ts.properties = ps;

  WriterContext context;
  std::stringstream sstream;
  context.writeTileset(sstream, ts);

  rapidjson::Document document;
  document.Parse(sstream.str().c_str());

  CHECK(document.IsObject());
  CHECK(document.HasMember("asset"));
  CHECK(document.HasMember("root"));
  CHECK(document.HasMember("extensionsUsed"));
  CHECK(document.HasMember("geometricError"));
  CHECK(document.HasMember("properties"));
  CHECK_FALSE(document.HasMember("extensionsRequired"));
  CHECK_FALSE(document.HasMember("extensions"));
  CHECK_FALSE(document.HasMember("extras"));

  CHECK(document["asset"].IsObject());
  CHECK(document["asset"].HasMember("version"));
  CHECK(document["asset"]["version"].GetString() == asset.version);
  CHECK_FALSE(document["asset"].HasMember("tilesetVersion"));
  CHECK_FALSE(document["asset"].HasMember("extensions"));
  CHECK_FALSE(document["asset"].HasMember("extras"));

  CHECK(document["extensionsUsed"].IsArray());
  CHECK(document["extensionsUsed"].Size() == ts.extensionsUsed->size());
  for (unsigned int i = 0; i < ts.extensionsUsed->size(); i++) {
    CHECK(
        document["extensionsUsed"][i].GetString() == ts.extensionsUsed->at(i));
  }

  CHECK(document["properties"].IsObject());
  CHECK(document["properties"]["p1"].IsObject());
  CHECK(document["properties"]["p1"]["maximum"].IsDouble());
  CHECK(document["properties"]["p1"]["maximum"] == p1.maximum);
  CHECK(document["properties"]["p1"]["minimum"].IsDouble());
  CHECK(document["properties"]["p1"]["minimum"] == p1.minimum);
  CHECK(document["properties"]["p2"].IsObject());
  CHECK(document["properties"]["p2"]["maximum"].IsDouble());
  CHECK(document["properties"]["p2"]["maximum"] == p2.maximum);
  CHECK(document["properties"]["p2"]["minimum"].IsDouble());
  CHECK(document["properties"]["p2"]["minimum"] == p2.minimum);

  CHECK(document["root"].IsObject());
  CHECK(document["root"].HasMember("boundingVolume"));
  CHECK(document["root"].HasMember("geometricError"));
  CHECK_FALSE(document["root"].HasMember("viewerRequestVolume"));
  CHECK_FALSE(document["root"].HasMember("refine"));
  CHECK_FALSE(document["root"].HasMember("content"));
  CHECK(document["root"].HasMember("children"));
  CHECK(document["root"]["children"].Size() == t3.children->size());

  const rapidjson::Value& child1 = document["root"]["children"][0];
  CHECK(child1.HasMember("boundingVolume"));
  CHECK(child1.HasMember("geometricError"));
  CHECK(child1.HasMember("refine"));
  CHECK(child1["refine"].IsString());
  CHECK(child1["refine"] == "ADD");
  CHECK_FALSE(child1.HasMember("content"));
  CHECK_FALSE(child1.HasMember("children"));
  CHECK_FALSE(child1.HasMember("viewerRequestVolume"));

  const rapidjson::Value& child2 = document["root"]["children"][1];
  CHECK(child2.HasMember("boundingVolume"));
  CHECK(child2.HasMember("geometricError"));
  CHECK(child2.HasMember("viewerRequestVolume"));
  CHECK(child2.HasMember("refine"));
  CHECK(child2["refine"].IsString());
  CHECK(child2["refine"] == "REPLACE");
  CHECK_FALSE(child2.HasMember("content"));
  CHECK_FALSE(child2.HasMember("children"));

  CHECK_FALSE(document.HasMember("extensions"));
}

TEST_CASE("Write 3D Tiles PntsFeatureTable", "[3DTilesWriter]") {
  using namespace std::string_literals;
  using namespace Cesium3DTiles;

  FeatureTable::BinaryBodyReference pos;
  pos.byteOffset = 1234;
  pos.componentType = FeatureTable::BinaryBodyReference::ComponentType::DOUBLE;

  FeatureTable::BinaryBodyReference color;
  pos.byteOffset = 5678;

  FeatureTable::GlobalPropertyCartesian3::Variant0 rtcCenter;
  rtcCenter.byteOffset = 9012;

  std::vector<double> qvo = {1.0, 2.0, 3.0};

  PntsFeatureTable pnts;
  pnts.POSITION = pos;
  pnts.RGBA = color;
  pnts.RTC_CENTER = rtcCenter;
  pnts.QUANTIZED_VOLUME_OFFSET = qvo;

  WriterContext context;
  std::stringstream sstream;
  context.writePnts(sstream, pnts);

  rapidjson::Document document;
  document.Parse(sstream.str().c_str());

  REQUIRE(document.IsObject());
  CHECK(document.HasMember("RTC_CENTER"));
  CHECK(document.HasMember("QUANTIZED_VOLUME_OFFSET"));
  CHECK(document.HasMember("POSITION"));
  CHECK(document.HasMember("RGBA"));
  CHECK_FALSE(document.HasMember("POSITION_QUANTIZED"));
  CHECK_FALSE(document.HasMember("RGB"));
  CHECK_FALSE(document.HasMember("RGB565"));
  CHECK_FALSE(document.HasMember("NORMAL"));
  CHECK_FALSE(document.HasMember("NORMAL_OCT16P"));
  CHECK_FALSE(document.HasMember("BATCH_ID"));
  CHECK_FALSE(document.HasMember("POINTS_LENGTH"));
  CHECK_FALSE(document.HasMember("QUANTIZED_VOLUME_SCALE"));
  CHECK_FALSE(document.HasMember("CONSTANT_RGBA"));
  CHECK_FALSE(document.HasMember("BATCH_LENGTH"));

  const rapidjson::Value& posJson = document["POSITION"];
  CHECK(posJson["byteOffset"] == pos.byteOffset);
  CHECK(posJson["componentType"] == "DOUBLE");

  const rapidjson::Value& colorJson = document["RGBA"];
  CHECK(colorJson["byteOffset"] == color.byteOffset);
  CHECK_FALSE(colorJson.HasMember("componentType"));

  const rapidjson::Value& rtcJson = document["RTC_CENTER"];
  CHECK(rtcJson.IsObject());
  CHECK(rtcJson["byteOffset"] == rtcCenter.byteOffset);

  const rapidjson::Value& qvoJson = document["QUANTIZED_VOLUME_OFFSET"];
  CHECK(qvoJson.IsArray());
  CHECK(qvoJson.Size() == qvo.size());
  for (unsigned int i = 0; i < qvoJson.Size(); i++) {
    CHECK(qvoJson[i] == qvo.at(i));
  }
}
