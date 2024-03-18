#include "gtest/gtest.h"
#include "smesh/config/config.h"
#include <QtVariantPropertyManager>
#include <QVector3D>
#include <qvariant.h>
#include <qvector3d.h>
#include <QDebug>

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(PropertyDef, Construtor)
{
  smesh::PropertyDef def_0;
  EXPECT_TRUE(!def_0.IsValid());
  smesh::PropertyDef def_1(QVariant::Int);
  EXPECT_TRUE(def_1.IsValid());
  EXPECT_TRUE(def_1.type() == QVariant::Int);
}

TEST(PropertyDef, SetValue)
{
  smesh::PropertyDef def(QVariant::Double);
  EXPECT_EQ(def.type(), QVariant::Double);
  def.set_default_value(0.5);
  EXPECT_DOUBLE_EQ(def.default_value().toDouble(), 0.5);
  def.set_attribute_value("max", 10.0);
  def.set_attribute_value("min", 0.0);
  EXPECT_DOUBLE_EQ(def.attribute_value("max").toDouble(), 10.0);
  EXPECT_DOUBLE_EQ(def.attribute_value("min").toDouble(), 0.0);
  def.set_attribute_value("tooltip", "test_tool_tip");
  EXPECT_TRUE(def.attribute_value("tooltip").toString() == "test_tool_tip");
}



